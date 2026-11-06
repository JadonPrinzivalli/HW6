
#include <iostream>
#include <cassert>
#include <random>
#include "RedBlackTree.h"

/**
 * 
 * This "First Step" tests file is useful to get your project started
 * 
 * To run this code you only need to implement
 * 	+ The Constructor
 * 	+ The Insert() function to insert only one node
 * 	+ The ToInfixString() function to print a tree containing only one node
 * 
**/

using namespace std;

void TestSimpleConstructor(){
	cout << "Testing Simple Constructor... " << endl;
	RedBlackTree rbt = RedBlackTree();
	//cout << "empty r-b-tree: " << rbt.ToInfixString() << endl;
	assert(rbt.ToInfixString() == "");
	
	cout << "PASSED!"<< endl << endl;
}


void TestInsertFirstNode(){
	cout << "Testing Insert One Node..." << endl;
	RedBlackTree rbt = RedBlackTree();
	rbt.Insert(30);
	//cout << "rbt: " << rbt.ToPrefixString() << endl;
	assert(rbt.ToInfixString() == " B30 ");
	assert(rbt.ToPrefixString() == " B30 ");
    assert(rbt.ToPostfixString() == " B30 ");
	assert(rbt.Contains(30) == true);
	assert(rbt.Contains(15) == false);
	assert(rbt.GetMin() == 30);
	assert(rbt.GetMax() == 30);
	assert(rbt.Size() == 1);

	cout << "PASSED!" << endl << endl;
}

void TestMultipleInsert() {
    RedBlackTree rbt;

    rbt.Insert(30);
    rbt.Insert(15);
    rbt.Insert(45);
    rbt.Insert(10);

    assert(rbt.Size() == 4);
    assert(rbt.Contains(30));
    assert(rbt.Contains(15));
    assert(rbt.Contains(45));
    assert(rbt.Contains(10));
    assert(!rbt.Contains(99));

    assert(rbt.GetMin() == 10);
    assert(rbt.GetMax() == 45);

    assert(rbt.ToInfixString() == " R10  B15  B30  B45 ");

    bool duplicateThrown = false;

    try {
        rbt.Insert(15);
    } catch (const std::invalid_argument&) {
        duplicateThrown = true;
    }

    assert(duplicateThrown);
    assert(rbt.Size() == 4);

    cout << "Multiple insert PASSED!" << endl;
}

void TestRotationCases() {
    // Each insertion order should produce the same balanced tree:

    // Left-left: needs a right rotation.
    RedBlackTree ll;
    ll.Insert(30);
    ll.Insert(20);
    ll.Insert(10);
    assert(ll.ToPrefixString() == " B20  R10  R30 ");

    // Left-right: needs a left rotation, then a right rotation.
    RedBlackTree lr;
    lr.Insert(30);
    lr.Insert(10);
    lr.Insert(20);
    assert(lr.ToPrefixString() == " B20  R10  R30 ");

    // Right-right: needs a left rotation.
    RedBlackTree rr;
    rr.Insert(10);
    rr.Insert(20);
    rr.Insert(30);
    assert(rr.ToPrefixString() == " B20  R10  R30 ");

    // Right-left: needs a right rotation, then a left rotation.
    RedBlackTree rl;
    rl.Insert(10);
    rl.Insert(30);
    rl.Insert(20);
    assert(rl.ToPrefixString() == " B20  R10  R30 ");

    cout << "Rotation cases PASSED!" << endl;
}

int main(){	
	TestSimpleConstructor();
	TestInsertFirstNode();
	TestMultipleInsert();
	TestRotationCases();

	cout << "ALL TESTS PASSED!!" << endl;
	return 0;
}
