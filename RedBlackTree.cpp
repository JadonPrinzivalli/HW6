#include "RedBlackTree.h"
#include <stdexcept>

RedBlackTree::RedBlackTree() {
    root = nullptr;
    numItems = 0;
}

RedBlackTree::RedBlackTree(int value) {
    root = nullptr;
    numItems = 0;

    // Reuse Insert so we only need one place for node setup.
    Insert(value);
}

unsigned long long int RedBlackTree::Size() const {
    return numItems;
}

bool RedBlackTree::Contains(int value) const {
    RBTNode* current = root;

    // Smaller values are on the left; larger values are on the right.
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

    // Reaching nullptr means the value was not found.
    return false;
}

int RedBlackTree::GetMin() const {
    // Assumes the tree is not empty.
    RBTNode* current = root;

    // The smallest value is at the far left.
    while (current->left != nullptr) {
        current = current->left;
    }

    return current->data;
}

int RedBlackTree::GetMax() const {
    // Assumes the tree is not empty.
    RBTNode* current = root;

    // The largest value is at the far right.
    while (current->right != nullptr) {
        current = current->right;
    }

    return current->data;
}

void RedBlackTree::Insert(int value) {
    RBTNode* current = root;
    RBTNode* parent = nullptr;

    // Find an empty position, remembering the last node visited.
    // That last node will become the new node's parent.
    while (current != nullptr) {
        parent = current;

        if (value < current->data) {
            current = current->left;
        } else if (value > current->data) {
            current = current->right;
        } else {
            // Reject duplicates before allocating memory or changing size.
            throw std::invalid_argument("Value already exists");
        }
    }

    RBTNode* newNode = new RBTNode;
    newNode->data = value;

    // Starting red avoids adding a black node to just one path.
    // We will fix any red-red connection afterward.
    newNode->color = COLOR_RED;
    newNode->left = nullptr;
    newNode->right = nullptr;
    newNode->parent = parent;

    if (parent == nullptr) {
        // No parent means the tree was empty.
        root = newNode;
        root->color = COLOR_BLACK;
    } else if (value < parent->data) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }

    numItems++;

    // The node is in BST order. Now repair the red-black rules.
    FixInsert(newNode);
}

void RedBlackTree::LeftRotate(RBTNode* node) {
    // The right child moves up. This helper requires a right child.
    RBTNode* child = node->right;

    // This subtree has values between node and child.
    // Moving it to node's right preserves BST order.
    node->right = child->left;

    if (child->left != nullptr) {
        child->left->parent = node;
    }

    // Connect child to the rest of the tree in node's old position.
    child->parent = node->parent;

    if (node->parent == nullptr) {
        root = child;
    } else if (node == node->parent->left) {
        node->parent->left = child;
    } else {
        node->parent->right = child;
    }

    // node is smaller than child, so it goes on child's left.
    child->left = node;
    node->parent = child;
}

void RedBlackTree::RightRotate(RBTNode* node) {
    // The left child moves up. This helper requires a left child.
    RBTNode* child = node->left;

    // This subtree has values between child and node.
    // Moving it to node's left preserves BST order.
    node->left = child->right;

    if (child->right != nullptr) {
        child->right->parent = node;
    }

    // Connect child to the rest of the tree in node's old position.
    child->parent = node->parent;

    if (node->parent == nullptr) {
        root = child;
    } else if (node == node->parent->left) {
        node->parent->left = child;
    } else {
        node->parent->right = child;
    }

    // node is larger than child, so it goes on child's right.
    child->right = node;
    node->parent = child;
}

void RedBlackTree::FixInsert(RBTNode* node) {
    // Repair only when a red node has a red parent.
    // Check node != root first because the root has no parent.
    while (node != root && node->parent->color == COLOR_RED) {
        RBTNode* parent = node->parent;

        // A red parent cannot be the black root, so grandparent exists.
        RBTNode* grandparent = parent->parent;

        if (parent == grandparent->left) {
            // The uncle is the parent's sibling.
            RBTNode* uncle = grandparent->right;

            if (uncle != nullptr && uncle->color == COLOR_RED) {
                // Red uncle: make parent and uncle black.
                // Making grandparent red keeps the black count unchanged
                // on every path through this subtree.
                parent->color = COLOR_BLACK;
                uncle->color = COLOR_BLACK;
                grandparent->color = COLOR_RED;

                // Grandparent may now have a red parent.
                // Move upward and check again.
                node = grandparent;
            } else {
                // A missing uncle counts as black.
                // With a black uncle, use rotations and recoloring.

                if (node == parent->right) {
                    // Left-right is bent. Rotate it into left-left.
                    LeftRotate(parent);

                    // Update our pointers after their positions changed.
                    node = parent;
                    parent = node->parent;
                }

                // Left-left: parent will move above grandparent.
                // Recolor so the new subtree root is black.
                parent->color = COLOR_BLACK;
                grandparent->color = COLOR_RED;

                RightRotate(grandparent);
            }
        } else {
            // Parent is on the right.
            // These cases mirror the left-side cases above.
            RBTNode* uncle = grandparent->left;

            if (uncle != nullptr && uncle->color == COLOR_RED) {
                // Recolor while preserving the black count on each path.
                parent->color = COLOR_BLACK;
                uncle->color = COLOR_BLACK;
                grandparent->color = COLOR_RED;

                // Check whether the problem moved higher in the tree.
                node = grandparent;
            } else {
                if (node == parent->left) {
                    // Right-left is bent. Rotate it into right-right.
                    RightRotate(parent);

                    node = parent;
                    parent = node->parent;
                }

                // Right-right: parent will move above grandparent.
                parent->color = COLOR_BLACK;
                grandparent->color = COLOR_RED;

                LeftRotate(grandparent);
            }
        }
    }

    // Recoloring may have turned the root red.
    // Making it black affects every root-to-null path equally.
    root->color = COLOR_BLACK;
}

string RedBlackTree::ToInfixString(RBTNode* node) const {
    // An empty subtree contributes no text and stops recursion.
    if (node == nullptr) {
        return "";
    }

    // Infix: left subtree, current node, right subtree.
    string result = "";

    result += ToInfixString(node->left);

    if (node->color == COLOR_BLACK) {
        result += " B" + to_string(node->data) + " ";
    } else {
        result += " R" + to_string(node->data) + " ";
    }

    result += ToInfixString(node->right);

    return result;
}

string RedBlackTree::ToPrefixString(RBTNode* node) const {
    if (node == nullptr) {
        return "";
    }

    // Prefix: current node, left subtree, right subtree.
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

    // Postfix: left subtree, right subtree, current node.
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