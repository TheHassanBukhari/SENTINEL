#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Queue.h"
#include "Heap.h"
#include "AVLTree.h"
#include "HashMap.h"
#include "Graph.h"
using namespace std;

class DataLoader {
public:
    void loadPatients(string filename, Queue& q, Heap& h, AVLTree& avl, HashMap& hmap, Graph& g) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "   ERROR: Cannot open " << filename << "\n";
            return;
        }

        string line;
        getline(file, line);

        while (getline(file, line)) {
            if (line.empty()) continue;
            stringstream ss(line);
            string token;
            string fields[13];
            int i = 0;

            while (getline(ss, token, ',') && i < 13)
                fields[i++] = token;

            if (i < 13) continue;

int age = 0, day = 0;
try { age = stoi(fields[2]); day = stoi(fields[4]); }
catch (...) { continue; }

Case* c = new Case(
    fields[0], fields[1], age, fields[3], day,
                fields[5] == "1", fields[6] == "1", fields[7] == "1",
                fields[8] == "1", fields[9] == "1", fields[10] == "1",
                fields[11] == "1", fields[12]
            );

            c->investigation_log.push(
                "Day " + to_string(c->day_registered),
                c->day_registered,
                "Patient registered. Status: " + c->status,
                "Initial intake from CSV data."
            );

            q.enqueue(c);
            h.insert(c->patient_id, c->risk_score);
            avl.insert(c->patient_id, c->day_registered);
            hmap.insertPerson(c->patient_id, c);
            hmap.insertLocation(c->area_code, c->patient_id);
            g.addNode(c->patient_id);
        }

        file.close();
        cout << "   Patients loaded successfully.\n";
    }

    void loadContacts(string filename, Graph& g) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "   ERROR: Cannot open " << filename << "\n";
            return;
        }

        string line;
        getline(file, line);

        while (getline(file, line)) {
            if (line.empty()) continue;
            stringstream ss(line);
            string token;
            string fields[7];
            int i = 0;

            while (getline(ss, token, ',') && i < 7)
                fields[i++] = token;

            if (i < 7) continue;

            int weight = 0, day = 0;
try { weight = stoi(fields[6]); day = stoi(fields[2]); }
catch (...) { continue; }
g.addEdge(fields[0], fields[1], weight, day, fields[4]);
        }

        file.close();
        cout << "   Contacts loaded successfully.\n";
    }
};
