#pragma once
#include <iostream>
#include <string>
#include "Case.h"
using namespace std;

const int TABLE_SIZE = 101;

struct PersonEntry {
    string key;
    Case* casePtr;
    PersonEntry* next;
    PersonEntry(string k, Case* c) : key(k), casePtr(c), next(nullptr) {}
};

struct LocationEntry {
    string area_code;
    string patient_ids[200];
    int count;
    LocationEntry* next;
    LocationEntry(string area) : area_code(area), count(0), next(nullptr) {}
    void addPatient(string id) {
        patient_ids[count++] = id;
    }
};

class HashMap {
private:
    PersonEntry* personTable[TABLE_SIZE];
    LocationEntry* locationTable[TABLE_SIZE];

    int hashFn(string key) {
        int hash = 0;
        for (char c : key) hash = (hash * 31 + c) % TABLE_SIZE;
        return hash;
    }

public:
    HashMap() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            personTable[i] = nullptr;
            locationTable[i] = nullptr;
        }
    }

    void insertPerson(string id, Case* c) {
        int idx = hashFn(id);
        PersonEntry* entry = new PersonEntry(id, c);
        entry->next = personTable[idx];
        personTable[idx] = entry;
    }

    Case* getPerson(string id) {
        int idx = hashFn(id);
        PersonEntry* curr = personTable[idx];
        while (curr) {
            if (curr->key == id) return curr->casePtr;
            curr = curr->next;
        }
        return nullptr;
    }

    void insertLocation(string area, string patient_id) {
        int idx = hashFn(area);
        LocationEntry* curr = locationTable[idx];
        while (curr) {
            if (curr->area_code == area) {
                curr->addPatient(patient_id);
                return;
            }
            curr = curr->next;
        }
        LocationEntry* entry = new LocationEntry(area);
        entry->addPatient(patient_id);
        entry->next = locationTable[idx];
        locationTable[idx] = entry;
    }

    void displayLocation(string area) {
        int idx = hashFn(area);
        LocationEntry* curr = locationTable[idx];
        while (curr) {
            if (curr->area_code == area) {
                cout << "   Area " << area << " has " << curr->count << " case(s):\n";
                for (int i = 0; i < curr->count; i++)
                    cout << "   " << i+1 << ". " << curr->patient_ids[i] << "\n";
                return;
            }
            curr = curr->next;
        }
        cout << "   No cases found in area " << area << ".\n";
    }

    void displayAllLocations() {
        cout << "   Area wise case distribution:\n";
        for (int i = 0; i < TABLE_SIZE; i++) {
            LocationEntry* curr = locationTable[i];
            while (curr) {
                cout << "   Area " << curr->area_code << ": " << curr->count << " case(s)\n";
                curr = curr->next;
            }
        }
    }
};
