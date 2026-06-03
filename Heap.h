#pragma once
#include <iostream>
#include "Case.h"
using namespace std;

struct HeapNode {
    string patient_id;
    int risk_score;
    HeapNode* next;
    HeapNode(string id, int score) : patient_id(id), risk_score(score), next(nullptr) {}
};

class Heap {
private:
    HeapNode* head;
    int size;

public:
    Heap() : head(nullptr), size(0) {}

    void insert(string id, int score) {
        HeapNode* node = new HeapNode(id, score);
        if (!head || score > head->risk_score) {
            node->next = head;
            head = node;
        } else {
            HeapNode* curr = head;
            while (curr->next && curr->next->risk_score >= score) {
                curr = curr->next;
            }
            node->next = curr->next;
            curr->next = node;
        }
        size++;
    }

    HeapNode* extractMax() {
        if (!head) return nullptr;
        HeapNode* temp = head;
        head = head->next;
        size--;
        return temp;
    }

    HeapNode* peekMax() { return head; }
    bool isEmpty() { return head == nullptr; }
    int getSize() { return size; }

    void display(int topN = 10) {
        if (!head) {
            cout << "   Heap is empty.\n";
            return;
        }
        HeapNode* curr = head;
        int count = 1;
        cout << "   Top High Risk Patients:\n";
        while (curr && count <= topN) {
            cout << "   " << count++ << ". " << curr->patient_id
                 << " | Risk Score: " << curr->risk_score << "/130\n";
            curr = curr->next;
        }
    }

    void updateScore(string id, int newScore) {
        HeapNode* curr = head;
        HeapNode* prev = nullptr;
        while (curr) {
            if (curr->patient_id == id) {
                if (prev) prev->next = curr->next;
                else head = curr->next;
                delete curr;
                size--;
                break;
            }
            prev = curr;
            curr = curr->next;
        }
        insert(id, newScore);
    }
};
