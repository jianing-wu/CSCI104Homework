#include "avlbst.h"
#include <iostream>
#include <vector>
#include <utility>

using namespace std;

int main(){

/*
	cout << endl << "Test one: zig-zig right and zig-zag right." << endl;
	AVLTree<int, int> sample;
	sample.insert(make_pair(1, 1));
	sample.insert(make_pair(2, 2));
	sample.insert(make_pair(3, 3));
	sample.insert(make_pair(6, 6));
	sample.insert(make_pair(5, 5));
	sample.print();

	cout << "Test two: zig-zig left and zig-zag left." << endl;
	AVLTree<int, int> sample2;
	sample2.insert(make_pair(6, 6));
	sample2.insert(make_pair(5, 5));
	sample2.insert(make_pair(4, 4));
	sample2.insert(make_pair(1, 1));
	sample2.insert(make_pair(3, 3));
	sample2.print();

	cout << "Test three: zig-zag left and zig-zag right." << endl;
	AVLTree<int, int> sample3;
	sample3.insert(make_pair(6, 6));
	sample3.insert(make_pair(5, 5));
	sample3.insert(make_pair(1, 1));
	sample3.insert(make_pair(4, 4));
	sample3.insert(make_pair(3, 3));
	sample3.print();

*/
	cout << "Test four: some stressors." << endl;
	AVLTree<int, int> sample4;
	sample4.insert(make_pair(10, 10));
	sample4.insert(make_pair(20, 20));
	sample4.insert(make_pair(30, 30));
	sample4.insert(make_pair(15, 15));
	sample4.insert(make_pair(25, 25));
	sample4.insert(make_pair(12, 12));
	sample4.insert(make_pair(5, 5));
	sample4.insert(make_pair(3, 3));
	sample4.insert(make_pair(8, 8));
	sample4.print();

	cout << "Test five: Insertion and removal." << endl;

	AVLTree<int, int> avltree;

	pair<int, int> node1;
	pair<int,int> node2;
	pair<int, int> node3;
	pair<int, int> node4;
	pair<int, int> node5;
	pair<int, int> node6;
	pair<int, int> node7;
	pair<int, int> node8;
	pair<int,int> node9;
	pair<int,int> node10;
	pair<int,int> node11;
	pair<int,int> node12;

	node1.first = 6;
	node1.second = 6;

	node2.first = 5;
	node2.second = 5;

	node3.first = 12;
	node3.second = 12;

	node4.first = 19;
	node4.second = 19;

	node5.first = 20;
	node5.second = 20; 

	node6.first = 11;
	node6.second = 11;

	node7.first = 10;
	node7.second = 10;

	node8.first = 3;
	node8.second = 3;

	node9.first = 2;
	node9.second = 2;

	node10.first = 30;
	node10.second = 30;

	node11.first = 28;
	node11.second = 28;

	node12.first = 24;
	node12.second = 24;

	
	avltree.insert(node1);
	avltree.insert(node2);
	avltree.insert(node3);
	avltree.insert(node4);
	avltree.insert(node5);
	
	avltree.insert(node6);
	avltree.insert(node12);
	avltree.insert(node11);
	avltree.insert(node10);
	avltree.insert(node8);
	avltree.insert(node9);
	//avltree.insert(node7);
	//avltree.insert(node8);
	//avltree.insert(node6);
	//avltree.insert(node9);
	//avltree.insert(node10);
	//avltree.insert(node11);
	//avltree.insert(node7);
	//avltree.insert(node12);
	//avltree.insert(node7);


	//node1.first = 7;
	//node1.second = 7;

	//node2.first = 5;
	//node2.second = 5;

	//node3.first = 3;
	//node3.second = 3;

	//avltree.insert(node3);
	//avltree.insert(node2);
	//avltree.insert(node1);
	//avltree.insert(node12);
	//avltree.insert(node7);

	cout << "Start: " << endl;
	avltree.print();

	cout << "Removing 30..." << endl;
	avltree.remove(node10.first);
	cout << "Done!" << endl;
	avltree.print();

	cout << "Removing 24..." << endl;
	avltree.remove(node12.first);
	cout << "Done!" << endl;
	avltree.print();

	cout << "Removing 20..." << endl;
	avltree.remove(node5.first);
	cout << "Done!" << endl;
	avltree.print();

	cout << "Removing 6..." << endl;
	avltree.remove(node1.first);
	cout << "Done!" << endl;
	avltree.print();

	cout << "Removing 28..." << endl;
	avltree.remove(node11.first);
	cout << "Done!" << endl;
	avltree.print();

	cout << "Removing 5..." << endl;
	avltree.remove(node2.first);
	cout << "Done!" << endl;
	avltree.print();

	cout << "Removing 2..." << endl;
	avltree.remove(node9.first);
	cout << "Done!" << endl;
	avltree.print();

	cout << "Removing 12..." << endl;
	avltree.remove(node3.first);
	cout << "Done!" << endl;
	avltree.print();

	cout << "Removing 11..." << endl;
	avltree.remove(node6.first);
	cout << "Done!" << endl;
	avltree.print();

	//avltree.remove(node4.first);

	//avltree.print();

	cout << "Removing 3..." << endl;
	avltree.remove(node8.first);
	cout << "Done!" << endl;
	avltree.print();

	if (avltree.isBalanced()) {
		cout << "Balanced" << endl;
	}
	else {
		cout << "Not Balanced" << endl;
	}
	return 0;
}