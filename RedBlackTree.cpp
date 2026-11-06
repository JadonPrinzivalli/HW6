#include "RedBlackTree.h"

RedBlackTree::RedBlackTree() {
    root = nullptr;
    numItems = 0;
}

string RedBlackTree::ToInfixString(RBTNode* node) const {

    if (node == nullptr) {
        return "";
    }

    string result = "";

    result += ToInfixString(node->left);

    if (node->color == COLOR_BLACK) {
        result += " B" + to_string(node->data) + " ";
    }
    else {
        result += " R" + to_string(node->data) + " ";
    }

    result += ToInfixString(node->right);

    return result;
}

string RedBlackTree::ToPrefixString(RBTNode* node) const {
    if (node == nullptr) {
        return "";
    }

    string result = "";

    if (node->color == COLOR_BLACK) {
        result += " B" + to_string(node->data) + " ";
    } else {
        result += " R" + to_string(node->data) + " ";
    }

    result += ToPrefixString(node->left);
    result += ToPrefixString(node->right);

    return result;
}

string RedBlackTree::ToPostfixString(RBTNode* node) const {
    if (node == nullptr) {
        return "";
    }

    string result = "";

    result += ToPostfixString(node->left);
    result += ToPostfixString(node->right);

    if (node->color == COLOR_BLACK) {
        result += " B" + to_string(node->data) + " ";
    } else {
        result += " R" + to_string(node->data) + " ";
    }

    return result;
}

bool RedBlackTree::Contains(int value) const {
    RBTNode* current = root;

    while (current != nullptr) {
        if (value == current->data) {
            return true;
        }

        if (value < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    return false;
}

int RedBlackTree::GetMin() const {
    RBTNode* current = root;

    while (current->left != nullptr) {
        current = current->left;
    }

    return current->data;
}

int RedBlackTree::GetMax() const {
    RBTNode* current = root;

    while (current->right != nullptr) {
        current = current->right;
    }

    return current->data;
}

void RedBlackTree::Insert(int value) {

    if (root == nullptr) {

        root = new RBTNode;

        root->data = value;
        root->color = COLOR_BLACK;

        root->left = nullptr;
        root->right = nullptr;
        root->parent = nullptr;

        numItems++;

        return;
    }
}

unsigned long long int RedBlackTree::Size() const {
    return numItems;
}

RedBlackTree::RedBlackTree(int value) {

    root = new RBTNode;

    root->data = value;
    root->color = COLOR_BLACK;

    root->left = nullptr;
    root->right = nullptr;
    root->parent = nullptr;

    numItems = 1;
}