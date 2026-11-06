#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#include <string>
#include <stdexcept>

using namespace std;

#define COLOR_RED 0
#define COLOR_BLACK 1

struct RBTNode {
    int data;
    int color;

    RBTNode* left;
    RBTNode* right;
    RBTNode* parent;
};

class RedBlackTree {

public:

    RedBlackTree();
    RedBlackTree(int value);
    int GetMin() const;
    int GetMax() const;

    void Insert(int value);
    unsigned long long int Size() const;
    bool Contains(int value) const;

    string ToInfixString() const {
        return ToInfixString(root);
    }

    string ToPrefixString() const {
        return ToPrefixString(root);
    }

    string ToPostfixString() const {
        return ToPostfixString(root);
    }

private:

    unsigned long long int numItems = 0;
    RBTNode* root = nullptr;
    void FixInsert(RBTNode* node);
    void LeftRotate(RBTNode* node);
    void RightRotate(RBTNode* node);

    string ToInfixString(RBTNode* node) const;
    string ToPrefixString(RBTNode* node) const;
    string ToPostfixString(RBTNode* node) const;
};

#endif