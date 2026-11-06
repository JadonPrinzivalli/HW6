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
    RBTNode* current = root;
    RBTNode* parent = nullptr;

    // Find an empty spot for the new node.
    while (current != nullptr) {
        parent = current;

        if (value < current->data) {
            current = current->left;
        } else if (value > current->data) {
            current = current->right;
        } else {
            throw std::invalid_argument("Value already exists");
        }
    }

    RBTNode* newNode = new RBTNode;
    newNode->data = value;
    newNode->color = COLOR_RED;
    newNode->left = nullptr;
    newNode->right = nullptr;
    newNode->parent = parent;

    // Attach the new node.
    if (parent == nullptr) {
        root = newNode;
        root->color = COLOR_BLACK;
    } else if (value < parent->data) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }

    numItems++;
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