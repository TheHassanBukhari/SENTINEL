#pragma once
#include <iostream>
#include <string>
#include "Graph.h"
using namespace std;

struct HeapNode {
    string patient_id;
    int risk_score;
};

class Heap {
private:
    HeapNode data[MAX_PATIENTS];
    int size;

    int parent(int i) { return (i - 1) / 2; }
    int left(int i)   { return 2 * i + 1; }
    int right(int i)  { return 2 * i + 2; }

    void swap(int i, int j) {
        HeapNode temp = data[i];
        data[i] = data[j];
        data[j] = temp;
    }

    void bubbleUp(int i) {
        while (i > 0 && data[i].risk_score > data[parent(i)].risk_score) {
            swap(i, parent(i));
            i = parent(i);
        }
    }

    void bubbleDown(int i) {
        int largest = i;
        int l = left(i);
        int r = right(i);
        if (l < size && data[l].risk_score > data[largest].risk_score) largest = l;
        if (r < size && data[r].risk_score > data[largest].risk_score) largest = r;
        if (largest != i) {
            swap(i, largest);
            bubbleDown(largest);
        }
    }

public:
    Heap() : size(0) {}

    void insert(string id, int score) {
        if (size >= MAX_PATIENTS) {
            cout << "   Heap is full.\n";
            return;
        }
        data[size] = {id, score};
        bubbleUp(size);
        size++;
    }

    HeapNode extractMax() {
        HeapNode maxNode = data[0];
        data[0] = data[--size];
        bubbleDown(0);
        return maxNode;
    }

    HeapNode peekMax() { return data[0]; }
    bool isEmpty() { return size == 0; }
    int getSize() { return size; }

    void display(int topN = 10) {
        if (size == 0) {
            cout << "   Heap is empty.\n";
            return;
        }
        // copy and extract to display in order without destroying original
        HeapNode temp[MAX_PATIENTS];
        int tempSize = size;
        for (int i = 0; i < size; i++) temp[i] = data[i];

        cout << "   Top High Risk Patients:\n";
        for (int count = 1; count <= topN && size > 0; count++) {
            cout << "   " << count << ". " << data[0].patient_id
                 << " | Risk Score: " << data[0].risk_score << "/130\n";
            data[0] = data[--size];
            bubbleDown(0);
        }

        // restore
        for (int i = 0; i < tempSize; i++) data[i] = temp[i];
        size = tempSize;
    }

    void updateScore(string id, int newScore) {
        for (int i = 0; i < size; i++) {
            if (data[i].patient_id == id) {
                data[i].risk_score = newScore;
                bubbleUp(i);
                bubbleDown(i);
                return;
            }
        }
        insert(id, newScore);
    }
};
