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