#pragma once
#include <iostream>
#include <string>
using namespace std;

const int MAX_PATIENTS = 100;
const int INF = 99999;

struct AdjNode {
    string patient_id;
    int risk_weight;
    int day;
    string location_type;
    AdjNode* next;

    AdjNode(string id, int w, int d, string loc)
        : patient_id(id), risk_weight(w), day(d), location_type(loc), next(nullptr) {}
};

struct GraphNode {
    string patient_id;
    AdjNode* head;
    GraphNode() : head(nullptr) {}
};

class Graph {
private:
    GraphNode nodes[MAX_PATIENTS];
    string nodeIds[MAX_PATIENTS];
    int nodeCount;

    int getIndex(string id) {
        for (int i = 0; i < nodeCount; i++)
            if (nodeIds[i] == id) return i;
        return -1;
    }

public:
    Graph() : nodeCount(0) {}

    void addNode(string id) {
        if (getIndex(id) != -1) return;
        nodeIds[nodeCount] = id;
        nodes[nodeCount].patient_id = id;
        nodeCount++;
    }

    void addEdge(string id1, string id2, int weight, int day, string locType) {
        int i = getIndex(id1);
        int j = getIndex(id2);
        if (i == -1 || j == -1) return;

        AdjNode* n1 = new AdjNode(id2, weight, day, locType);
        n1->next = nodes[i].head;
        nodes[i].head = n1;

        AdjNode* n2 = new AdjNode(id1, weight, day, locType);
        n2->next = nodes[j].head;
        nodes[j].head = n2;
    }

    void displayGraph() {
        cout << "   Contact Network:\n";
        for (int i = 0; i < nodeCount; i++) {
            cout << "   " << nodeIds[i] << " -> ";
            AdjNode* curr = nodes[i].head;
            while (curr) {
                cout << curr->patient_id << "(w:" << curr->risk_weight << ") ";
                curr = curr->next;
            }
            cout << "\n";
        }
    }

    AdjNode* getNeighbors(string id) {
        int i = getIndex(id);
        if (i == -1) return nullptr;
        return nodes[i].head;
    }

    int getWeight(string id1, string id2) {
        int i = getIndex(id1);
        if (i == -1) return 0;
        AdjNode* curr = nodes[i].head;
        while (curr) {
            if (curr->patient_id == id2) return curr->risk_weight;
            curr = curr->next;
        }
        return 0;
    }

    int getNodeCount() { return nodeCount; }
    string getNodeId(int i) { return nodeIds[i]; }
    bool nodeExists(string id) { return getIndex(id) != -1; }

    void bfsWaveSimulation(string startId) {
        bool visited[MAX_PATIENTS] = {false};
        string bfsQueue[MAX_PATIENTS];
        int dayQueue[MAX_PATIENTS];
        int front = 0, rear = 0;

        int startIdx = getIndex(startId);
        if (startIdx == -1) {
            cout << "   Patient not found.\n";
            return;
        }

        visited[startIdx] = true;
        bfsQueue[rear] = startId;
        dayQueue[rear] = 0;
        rear++;

        cout << "   Outbreak Wave Simulation from " << startId << ":\n";
        int currentDay = -1;

        while (front < rear) {
            string curr = bfsQueue[front];
            int day = dayQueue[front];
            front++;

            if (day != currentDay) {
                currentDay = day;
                cout << "\n   Wave " << currentDay << ":\n";
            }
            cout << "   " << curr << " ";

            AdjNode* neighbor = getNeighbors(curr);
            while (neighbor) {
                int ni = getIndex(neighbor->patient_id);
                if (ni != -1 && !visited[ni]) {
                    visited[ni] = true;
                    bfsQueue[rear] = neighbor->patient_id;
                    dayQueue[rear] = day + 1;
                    rear++;
                }
                neighbor = neighbor->next;
            }
        }
        cout << "\n";
    }
};
