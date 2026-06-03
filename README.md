# SENTINEL
### Spread and Exposure Network for Tracking, Isolation & Neutralizing Epidemic Linked Nodes

> 3rd Semester Data Structures & Algorithms Project
> BS Computer Science, COMSATS University Islamabad
> Spring 2025

---

## What is SENTINEL

SENTINEL is a console-based epidemic contact tracing and containment system built in C++. It models a disease outbreak as a living graph of human contacts and uses seven core data structures to track, prioritize, and contain the spread.

The system is inspired by real-world epidemic response challenges highlighted during COVID-19, where contact tracing, risk prioritization, and containment decisions needed to be made fast and accurately.

---

## Data Structures Used

| Structure | Role in SENTINEL |
|-----------|-----------------|
| **Stack** | Per-patient investigation log. Each case carries its own stack of timestamped events. |
| **Queue** | Master case pipeline. Patients enter in registration order and can be filtered by day or area. |
| **Heap** | Risk priority engine. Patients are scored on 7 symptom and exposure criteria. Highest risk always on top. |
| **AVL Tree** | Date-indexed patient records. Enables range queries like "all cases between day 5 and day 12". |
| **HashMap** | Dual system. One maps patient ID to full profile. One maps area codes to case lists for hotspot detection. |
| **Graph** | Contact network. Patients are nodes. Contacts are weighted edges based on duration, location type, and proximity. |
| **Dijkstra** | Traces the most probable transmission path from patient zero to any given case. |
| **Prim's** | Finds the minimum set of contact links holding a cluster together. Breaking these links surgically contains the outbreak. |

All structures are implemented from scratch using linked lists. No STL containers used.

---

## Features

- Load patient and contact data from CSV files
- Register new patients with automatic risk scoring
- View full investigation log per patient (stack events)
- Simulate outbreak spread wave by wave from any source (BFS)
- Trace transmission chain between any two patients (Dijkstra)
- Find minimum containment network for active clusters (Prim's)
- Filter cases by day, area code, or date range
- View high risk patients ranked by score
- Geographic hotspot detection via area code hashmap

---

## Project Structure

```
SENTINEL/
├── data/
│   ├── patients.csv
│   └── contacts.csv
├── docs/
│   ├── part1_foundations.html
│   ├── part2_data_structures.html
│   ├── part3_graphs_algorithms.html
│   ├── part4_sentinel_context.html
│   └── part5_project_structure.html
├── main.cpp
├── Stack.h
├── Case.h
├── Queue.h
├── Heap.h
├── AVLTree.h
├── HashMap.h
├── Graph.h
├── Dijkstra.h
├── Prims.h
├── DataLoader.h
└── README.md
```

---

## How to Run

```bash
git clone https://github.com/yourusername/SENTINEL.git
cd SENTINEL
g++ main.cpp -o sentinel
./sentinel
```

Requires g++ with C++11 or later.

---

## Risk Scoring System

Each patient is evaluated on 7 criteria at registration:

| Criteria | Points |
|----------|--------|
| Breathing difficulty | 25 |
| Known contact with confirmed case | 25 |
| Fever | 20 |
| Age above 60 or comorbidity | 20 |
| Cough | 15 |
| High contact job | 15 |
| Attended large gathering | 10 |
| **Maximum** | **130** |

---

## License

This project is licensed under the MIT License.
