#include "bst.h"
//#include "print_bst.h"
#include <iostream>
#include <vector>
#include <utility>

using namespace std;

int main() {

	BinarySearchTree<int, int> btree;

	pair<int, int> node1;
	pair<int,int> node2;
	pair<int, int> node3;
	pair<int, int> node4;
	pair<int, int> node5;
	pair<int, int> node6;
	pair<int,int> node7;
	pair<int,int> node8;

	node1.first = 6;
	node1.second = 6;

	node2.first = 5;
	node2.second = 5;

	node3.first = 12;
	node3.second = 12;

	node4.first = 3;
	node4.second = 3;

	node5.first = 8;
	node5.second = 8;

	node6.first = 10;
	node6.second = 10;

	node7.first = 13;
	node7.second = 13;

	node8.first = 9;
	node8.second = 9;

	cout << "First test: " << endl;
	btree.insert(node1);
	btree.insert(node2);
	btree.insert(node3);
	btree.insert(node4);
	btree.insert(node5);
	btree.insert(node6);
	btree.insert(node7);
	btree.insert(node8);

	//btree.print();
	//btree.remove(node6.first);
	//btree.remove(node4.first);
	//btree.print();
	/*
	if (btree.isBalanced()) {
		cout << "Balanced" << endl;
	}
	else {
		cout << "Not Balanced" << endl;
	}
	*/
	btree.print();

	if (btree.isBalanced()) {
		cout << "Balanced" << endl << endl;
	}
	else {
		cout << "Not Balanced" << endl;
	}

	cout << endl << "Second test: " << endl;
	btree.remove(node1.first);
	//btree.remove(node3.first);

	btree.print();

	if (btree.isBalanced()) {
		cout << "Balanced" << endl;
	}
	else {
		cout << "Not Balanced" << endl;
	}

	cout << endl << "Third test: " << endl;
	btree.remove(node2.first);

	//btree.remove(node6.first);
	//btree.remove(node8.first);

	btree.print();

	if (btree.isBalanced()) {
		cout << "Balanced" << endl;
	}
	else {
		cout << "Not Balanced" << endl;
	}

	cout << endl << "Fourth test: " << endl;
	btree.remove(node3.first);

	btree.print();

	if (btree.isBalanced()) {
		cout << "Balanced" << endl;
	}
	else {
		cout << "Not Balanced" << endl;
	}

	cout << endl << "Fifth test: " << endl;
	btree.remove(node4.first);

	btree.print();

	if (btree.isBalanced()) {
		cout << "Balanced" << endl;
	}
	else {
		cout << "Not Balanced" << endl;
	}

	cout << endl << "Sixth test: " << endl;
	btree.remove(node5.first);

	btree.print();

	return 0;
}
