#pragma once

#include <iostream>
#include <string>
using namespace std;

struct StackNode {
    string timestamp;
    int day;
    string event;
    string officer_note;
    StackNode* next;

    StackNode(string ts, int d, string ev, string note)
        : timestamp(ts), day(d), event(ev), officer_note(note), next(nullptr) {}
};

class Stack {
private:
    StackNode* top;
    int size;

public:
    Stack() : top(nullptr), size(0) {}

    ~Stack() {
        while (top) {
            StackNode* temp = top;
            top = top->next;
            delete temp;
        }
    }

    void push(string timestamp, int day, string event, string note) {
        StackNode* node = new StackNode(timestamp, day, event, note);
        node->next = top;
        top = node;
        size++;
    }

    StackNode* pop() {
        if (!top) return nullptr;
        StackNode* temp = top;
        top = top->next;
        size--;
        return temp;
    }

    StackNode* peek() {
        return top;
    }

    bool isEmpty() {
        return top == nullptr;
    }

    int getSize() {
        return size;
    }

    void display() {
        if (!top) {
            cout << "   No events recorded.\n";
            return;
        }
        StackNode* curr = top;
        int count = 1;
        while (curr) {
            cout << "   [" << count++ << "] Day " << curr->day
                 << " | " << curr->timestamp
                 << " | " << curr->event
                 << "\n       Note: " << curr->officer_note << "\n";
            curr = curr->next;
        }
    }
};
