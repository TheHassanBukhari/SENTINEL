#include <iostream>
#include <string>
#include <ctime>
#include "Queue.h"
#include "Heap.h"
#include "AVLTree.h"
#include "HashMap.h"
#include "Graph.h"
#include "Dijkstra.h"
#include "Prims.h"
#include "DataLoader.h"
using namespace std;

Queue caseQueue;
Heap riskHeap;
AVLTree patientTree;
HashMap patientMap;
Graph contactGraph;
Dijkstra dijkstra;
Prims prims;

void printHeader() {
    cout << "\n";
    cout << "   ============================================\n";
    cout << "       SENTINEL - Epidemic Tracking System    \n";
    cout << "      Spread and Exposure Network for         \n";
    cout << "   Tracking, Isolation & Neutralizing         \n";
    cout << "             Epidemic Linked Nodes            \n";
    cout << "   ============================================\n";
}

void printMenu() {
    cout << "\n   ============ MAIN MENU ============\n";
    cout << "   1.  View All Patients\n";
    cout << "   2.  Search Patient by ID\n";
    cout << "   3.  Add New Patient\n";
    cout << "   4.  Update Patient Status\n";
    cout << "   5.  View Case Investigation Log\n";
    cout << "   6.  Add Investigation Event to Case\n";
    cout << "   7.  View Patients by Day\n";
    cout << "   8.  View Patients by Area\n";
    cout << "   9.  View Patients in Day Range (AVL Tree)\n";
    cout << "   10. View High Risk Patients (Heap)\n";
    cout << "   11. View Area Case Distribution (HashMap)\n";
    cout << "   12. View Contact Network (Graph)\n";
    cout << "   13. Simulate Outbreak Spread (BFS Queue)\n";
    cout << "   14. Trace Transmission Path (Dijkstra)\n";
    cout << "   15. Find Minimum Containment Network (Prim's)\n";
    cout << "   16. View Sorted Timeline (AVL Tree)\n";
    cout << "   0.  Exit\n";
    cout << "   ===================================\n";
    cout << "   Choice: ";
}

string getCurrentTime() {
    time_t now = time(0);
    char buf[80];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M", localtime(&now));
    return string(buf);
}

int calculateScore(bool fv, bool cg, bool bd, bool lg, bool hcj, bool kc, bool com) {
    int score = 0;
    if (fv) score += 20;
    if (cg) score += 15;
    if (bd) score += 25;
    if (lg) score += 10;
    if (hcj) score += 15;
    if (kc) score += 25;
    if (com) score += 20;
    return score;
}

void addNewPatient() {
    string id, name, area, status;
    int age, day;

    cout << "\n   === ADD NEW PATIENT ===\n";
    cout << "   Patient ID  : "; cin >> id;

    if (patientMap.getPerson(id)) {
        cout << "   Patient ID already exists.\n";
        return;
    }

    cout << "   Name        : "; cin.ignore(); getline(cin, name);
    cout << "   Age         : "; cin >> age;
    cout << "   Area Code   : "; cin >> area;
    cout << "   Day         : "; cin >> day;
    cout << "   Status (positive/negative/quarantined): "; cin >> status;

    cout << "\n   Answer Yes(1) or No(0) for each:\n";
    bool fv, cg, bd, lg, hcj, kc, com;
    cout << "   Fever                   : "; cin >> fv;
    cout << "   Cough                   : "; cin >> cg;
    cout << "   Breathing difficulty    : "; cin >> bd;
    cout << "   Attended large gathering: "; cin >> lg;
    cout << "   High contact job        : "; cin >> hcj;
    cout << "   Known contact with case : "; cin >> kc;
    cout << "   Age above 60/comorbid   : "; cin >> com;

    Case* c = new Case(id, name, age, area, day, fv, cg, bd, lg, hcj, kc, com, status);
    c->investigation_log.push(getCurrentTime(), day, "Patient registered manually.", "Added via system menu.");

    caseQueue.enqueue(c);
    riskHeap.insert(id, c->risk_score);
    patientTree.insert(id, day);
    patientMap.insertPerson(id, c);
    patientMap.insertLocation(area, id);
    contactGraph.addNode(id);

    cout << "\n   Patient added. Risk Score: " << c->risk_score << "/130\n";
}

void updateStatus() {
    string id, newStatus;
    cout << "\n   Patient ID : "; cin >> id;
    Case* c = patientMap.getPerson(id);
    if (!c) { cout << "   Patient not found.\n"; return; }

    cout << "   New Status (positive/negative/quarantined/recovered): "; cin >> newStatus;
    string oldStatus = c->status;
    c->status = newStatus;

    c->investigation_log.push(getCurrentTime(), c->day_registered,
        "Status updated from " + oldStatus + " to " + newStatus + ".",
        "Updated via system menu.");

    int newScore = c->calculateRiskScore();
    riskHeap.updateScore(id, newScore);

    cout << "   Status updated successfully.\n";
}

void viewCaseLog() {
    string id;
    cout << "\n   Patient ID : "; cin >> id;
    Case* c = patientMap.getPerson(id);
    if (!c) { cout << "   Patient not found.\n"; return; }

    cout << "\n   Investigation Log for " << c->name << " (" << id << "):\n";
    c->investigation_log.display();
}

void addEvent() {
    string id, event, note;
    int day;
    cout << "\n   Patient ID    : "; cin >> id;
    Case* c = patientMap.getPerson(id);
    if (!c) { cout << "   Patient not found.\n"; return; }

    cout << "   Day           : "; cin >> day;
    cin.ignore();
    cout << "   Event         : "; getline(cin, event);
    cout << "   Officer Note  : "; getline(cin, note);

    c->investigation_log.push(getCurrentTime(), day, event, note);
    cout << "   Event added to case log.\n";
}

void traceTransmission() {
    string src, dest;
    cout << "\n   Source Patient ID      : "; cin >> src;
    cout << "   Destination Patient ID : "; cin >> dest;
    dijkstra.findPath(contactGraph, src, dest);
}

int main() {
    printHeader();

    cout << "\n   Loading data...\n";
    DataLoader loader;
    loader.loadPatients("data/patients.csv", caseQueue, riskHeap, patientTree, patientMap, contactGraph);
    loader.loadContacts("data/contacts.csv", contactGraph);

    int choice;
    string input;

    do {
        printMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "\n   === ALL PATIENTS ===\n";
                caseQueue.displayAll();
                break;

            case 2: {
                string id;
                cout << "\n   Patient ID : "; cin >> id;
                Case* c = patientMap.getPerson(id);
                if (c) c->display();
                else cout << "   Patient not found.\n";
                break;
            }

            case 3:
                addNewPatient();
                break;

            case 4:
                updateStatus();
                break;

            case 5:
                viewCaseLog();
                break;

            case 6:
                addEvent();
                break;

            case 7: {
                int day;
                cout << "\n   Enter day : "; cin >> day;
                caseQueue.displayByDay(day);
                break;
            }

            case 8: {
                string area;
                cout << "\n   Enter area code : "; cin >> area;
                caseQueue.displayByArea(area);
                break;
            }

            case 9: {
                int d1, d2;
                cout << "\n   From day : "; cin >> d1;
                cout << "   To day   : "; cin >> d2;
                patientTree.searchRange(d1, d2);
                break;
            }

            case 10:
                cout << "\n   === HIGH RISK PATIENTS ===\n";
                riskHeap.display();
                break;

            case 11:
                cout << "\n   === AREA DISTRIBUTION ===\n";
                patientMap.displayAllLocations();
                break;

            case 12:
                cout << "\n   === CONTACT NETWORK ===\n";
                contactGraph.displayGraph();
                break;

            case 13: {
                string startId;
                cout << "\n   Start from Patient ID : "; cin >> startId;
                contactGraph.bfsWaveSimulation(startId);
                break;
            }

            case 14:
                traceTransmission();
                break;

            case 15:
                prims.findMinContainmentNetwork(contactGraph);
                break;

            case 16:
                cout << "\n   === PATIENT TIMELINE ===\n";
                patientTree.displayAll();
                break;

            case 0:
                cout << "\n   SENTINEL shutting down. Stay safe.\n\n";
                break;

            default:
                cout << "   Invalid choice.\n";
        }

    } while (choice != 0);

    return 0;
}
