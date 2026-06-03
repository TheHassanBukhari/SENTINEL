#pragma once
#include <string>
#include <iostream>
#include "Stack.h"
using namespace std;

struct Case {
    string patient_id;
    string name;
    int age;
    string area_code;
    int day_registered;
    int risk_score;
    string status;

    bool fever;
    bool cough;
    bool breathing_difficulty;
    bool large_gathering;
    bool high_contact_job;
    bool known_contact;
    bool above_60_or_comorbid;

    Stack investigation_log;

    Case* next;

    Case() : age(0), day_registered(0), risk_score(0), next(nullptr),
             fever(false), cough(false), breathing_difficulty(false),
             large_gathering(false), high_contact_job(false),
             known_contact(false), above_60_or_comorbid(false) {}

    Case(string id, string n, int a, string area, int day,
         bool fv, bool cg, bool bd, bool lg, bool hcj, bool kc, bool com, string st)
        : patient_id(id), name(n), age(a), area_code(area), day_registered(day),
          fever(fv), cough(cg), breathing_difficulty(bd), large_gathering(lg),
          high_contact_job(hcj), known_contact(kc), above_60_or_comorbid(com),
          status(st), next(nullptr) {
        risk_score = calculateRiskScore();
    }

    int calculateRiskScore() {
        int score = 0;
        if (fever) score += 20;
        if (cough) score += 15;
        if (breathing_difficulty) score += 25;
        if (large_gathering) score += 10;
        if (high_contact_job) score += 15;
        if (known_contact) score += 25;
        if (above_60_or_comorbid) score += 20;
        return score;
    }

    void display() {
        cout << "\n   Patient  : " << patient_id << " | " << name << "\n";
        cout << "   Age      : " << age << "\n";
        cout << "   Area     : " << area_code << "\n";
        cout << "   Day      : " << day_registered << "\n";
        cout << "   Status   : " << status << "\n";
        cout << "   Risk     : " << risk_score << "/130\n";
        cout << "   Symptoms : ";
        if (fever) cout << "Fever ";
        if (cough) cout << "Cough ";
        if (breathing_difficulty) cout << "Breathing ";
        if (!fever && !cough && !breathing_difficulty) cout << "None";
        cout << "\n";
    }
};
