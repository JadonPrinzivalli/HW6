
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

    assert(rbt.ToInfixString() == " R10  R15  B30  R45 ");

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


int main(){	
	TestSimpleConstructor();
	TestInsertFirstNode();
	TestMultipleInsert();

	cout << "ALL TESTS PASSED!!" << endl;
	return 0;
}
