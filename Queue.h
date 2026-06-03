#pragma once
#include <iostream>
#include "Case.h"
using namespace std;

class Queue {
private:
    Case* front;
    Case* rear;
    int size;

public:
    Queue() : front(nullptr), rear(nullptr), size(0) {}

    ~Queue() {
        while (front) {
            Case* temp = front;
            front = front->next;
            delete temp;
        }
    }

    void enqueue(Case* c) {
        c->next = nullptr;
        if (!rear) {
            front = rear = c;
        } else {
            rear->next = c;
            rear = c;
        }
        size++;
    }

    Case* dequeue() {
        if (!front) return nullptr;
        Case* temp = front;
        front = front->next;
        if (!front) rear = nullptr;
        size--;
        return temp;
    }

    Case* getFront() { return front; }
    int getSize() { return size; }
    bool isEmpty() { return front == nullptr; }

    Case* findById(string id) {
        Case* curr = front;
        while (curr) {
            if (curr->patient_id == id) return curr;
            curr = curr->next;
        }
        return nullptr;
    }

    void displayAll() {
        if (!front) {
            cout << "   No cases in system.\n";
            return;
        }
        Case* curr = front;
        int count = 1;
        while (curr) {
            cout << "   " << count++ << ". ";
            curr->display();
            curr = curr->next;
        }
    }

    void displayByDay(int day) {
        Case* curr = front;
        bool found = false;
        while (curr) {
            if (curr->day_registered == day) {
                curr->display();
                found = true;
            }
            curr = curr->next;
        }
        if (!found) cout << "   No cases on day " << day << ".\n";
    }

    void displayByArea(string area) {
        Case* curr = front;
        bool found = false;
        while (curr) {
            if (curr->area_code == area) {
                curr->display();
                found = true;
            }
            curr = curr->next;
        }
        if (!found) cout << "   No cases in area " << area << ".\n";
    }
};
