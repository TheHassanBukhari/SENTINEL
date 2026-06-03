#pragma once
#include <iostream>
#include <string>
#include "Graph.h"
using namespace std;

class Prims {
public:
    void findMinContainmentNetwork(Graph& g) {
        int n = g.getNodeCount();
        if (n == 0) { cout << "   Graph is empty.\n"; return; }

        bool inMST[MAX_PATIENTS] = {false};
        int key[MAX_PATIENTS];
        string parent[MAX_PATIENTS];

        for (int i = 0; i < n; i++) {
            key[i] = INF;
            parent[i] = "";
        }

        key[0] = 0;
        int totalCost = 0;

        cout << "\n   Minimum Containment Network (Critical Contact Links):\n";

        for (int iter = 0; iter < n; iter++) {
            int u = -1;
            for (int i = 0; i < n; i++)
                if (!inMST[i] && (u == -1 || key[i] < key[u])) u = i;

            if (u == -1 || key[u] == INF) break;
            inMST[u] = true;

            string uId = g.getNodeId(u);
            if (parent[u] != "") {
                int w = g.getWeight(parent[u], uId);
                cout << "   " << parent[u] << " <-> " << uId << " | Risk Weight: " << w << "\n";
                totalCost += w;
            }

            AdjNode* neighbor = g.getNeighbors(uId);
            while (neighbor) {
                int v = -1;
                for (int i = 0; i < n; i++)
                    if (g.getNodeId(i) == neighbor->patient_id) { v = i; break; }

                if (v != -1 && !inMST[v] && neighbor->risk_weight < key[v]) {
                    key[v] = neighbor->risk_weight;
                    parent[v] = uId;
                }
                neighbor = neighbor->next;
            }
        }

        cout << "   Total Network Risk Score: " << totalCost << "\n";
        cout << "   Quarantine these contact links to contain the outbreak.\n";
    }
};
