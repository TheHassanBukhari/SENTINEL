#pragma once
#include <iostream>
#include <string>
using namespace std;

struct AVLNode {
    string patient_id;
    int day;
    int height;
    AVLNode* left;
    AVLNode* right;

    AVLNode(string id, int d) : patient_id(id), day(d), height(1), left(nullptr), right(nullptr) {}
};

class AVLTree {
private:
    AVLNode* root;

    int height(AVLNode* n) { return n ? n->height : 0; }

    int balanceFactor(AVLNode* n) {
        return n ? height(n->left) - height(n->right) : 0;
    }

    void updateHeight(AVLNode* n) {
        if (n) n->height = 1 + max(height(n->left), height(n->right));
    }

    AVLNode* rotateRight(AVLNode* y) {
        AVLNode* x = y->left;
        AVLNode* T = x->right;
        x->right = y;
        y->left = T;
        updateHeight(y);
        updateHeight(x);
        return x;
    }

    AVLNode* rotateLeft(AVLNode* x) {
        AVLNode* y = x->right;
        AVLNode* T = y->left;
        y->left = x;
        x->right = T;
        updateHeight(x);
        updateHeight(y);
        return y;
    }

    AVLNode* balance(AVLNode* n) {
        updateHeight(n);
        int bf = balanceFactor(n);
        if (bf > 1) {
            if (balanceFactor(n->left) < 0) n->left = rotateLeft(n->left);
            return rotateRight(n);
        }
        if (bf < -1) {
            if (balanceFactor(n->right) > 0) n->right = rotateRight(n->right);
            return rotateLeft(n);
        }
        return n;
    }

    AVLNode* insert(AVLNode* node, string id, int day) {
        if (!node) return new AVLNode(id, day);
        if (day < node->day) node->left = insert(node->left, id, day);
        else node->right = insert(node->right, id, day);
        return balance(node);
    }

    void rangeSearch(AVLNode* node, int d1, int d2) {
        if (!node) return;
        if (node->day >= d1) rangeSearch(node->left, d1, d2);
        if (node->day >= d1 && node->day <= d2)
            cout << "   Patient: " << node->patient_id << " | Day: " << node->day << "\n";
        if (node->day <= d2) rangeSearch(node->right, d1, d2);
    }

    void inorder(AVLNode* node) {
        if (!node) return;
        inorder(node->left);
        cout << "   Day " << node->day << " | " << node->patient_id << "\n";
        inorder(node->right);
    }

public:
    AVLTree() : root(nullptr) {}

    void insert(string id, int day) {
        root = insert(root, id, day);
    }

    void searchRange(int d1, int d2) {
        cout << "   Patients registered between day " << d1 << " and day " << d2 << ":\n";
        rangeSearch(root, d1, d2);
    }

    void displayAll() {
        cout << "   All patients sorted by registration day:\n";
        inorder(root);
    }
};
