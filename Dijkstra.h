#pragma once
#include <iostream>
#include <string>
#include "Graph.h"
using namespace std;


class Dijkstra {
public:
    void findPath(Graph& g, string srcId, string destId) {
        int n = g.getNodeCount();
        if (n == 0) { cout << "   Graph is empty.\n"; return; }

        if (!g.nodeExists(srcId) || !g.nodeExists(destId)) {
            cout << "   One or both patients not found in contact network.\n";
            return;
        }

        int dist[MAX_PATIENTS];
        bool visited[MAX_PATIENTS] = {false};
        int parent[MAX_PATIENTS];
        string parentId[MAX_PATIENTS];

        for (int i = 0; i < n; i++) {
            dist[i] = INF;
            parent[i] = -1;
            parentId[i] = "";
        }

        int srcIdx = -1;
        for (int i = 0; i < n; i++)
            if (g.getNodeId(i) == srcId) { srcIdx = i; break; }

        dist[srcIdx] = 0;

        for (int iter = 0; iter < n; iter++) {
            int u = -1;
            for (int i = 0; i < n; i++)
                if (!visited[i] && (u == -1 || dist[i] < dist[u])) u = i;

            if (u == -1 || dist[u] == INF) break;
            visited[u] = true;

            string uId = g.getNodeId(u);
            AdjNode* neighbor = g.getNeighbors(uId);
            while (neighbor) {
                int v = -1;
                for (int i = 0; i < n; i++)
                    if (g.getNodeId(i) == neighbor->patient_id) { v = i; break; }

                if (v != -1 && !visited[v]) {
                    int newDist = dist[u] + (10 - neighbor->risk_weight);
                    if (newDist < dist[v]) {
                        dist[v] = newDist;
                        parent[v] = u;
                        parentId[v] = uId;
                    }
                }
                neighbor = neighbor->next;
            }
        }

        int destIdx = -1;
        for (int i = 0; i < n; i++)
            if (g.getNodeId(i) == destId) { destIdx = i; break; }

        if (dist[destIdx] == INF) {
            cout << "   No transmission path found between " << srcId << " and " << destId << ".\n";
            return;
        }

        string path[MAX_PATIENTS];
        int pathLen = 0;
        int curr = destIdx;
        while (curr != -1) {
            path[pathLen++] = g.getNodeId(curr);
            curr = parent[curr];
        }

        cout << "\n   Transmission Path from " << srcId << " to " << destId << ":\n   ";
        for (int i = pathLen - 1; i >= 0; i--) {
            cout << path[i];
            if (i > 0) cout << " -> ";
        }
        cout << "\n   Transmission Risk Distance: " << dist[destIdx] << "\n";
    }
};
