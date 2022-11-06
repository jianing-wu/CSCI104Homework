#include "bst.h"
#include "avlbst.h"
#include <iostream>
#include <stdlib.h>
#include <utility>
#include <ctime>
#include "gtest/gtest.h"

using namespace std;

/**
 * ATTENTION: For the purposes of this test file, please
 move your Node<Key, Value> *current_ (line 225, bst.h) to
 the iterator class's public members. Nothing else needs to
 be done to run this test file.

 PLEASE MAKE SURE TO CHANGE IT BACK TO BEING A PROTECTED
 VARIABLE WHEN YOU'RE DONE.

 COMPILE COMMAND:
 	g++ -g -Wall -std=c++11 avl_gtests.cpp -I /usr/include/gtest/ -l gtest -l gtest_main -pthread -o avlg

 Thanks.
 - Jamie
 **/

TEST(AVLTest, EmptyRemove){
	AVLTree<string, int> test;
	EXPECT_NO_THROW(test.remove("jerry"));
}

TEST(AVLTest, EmptyClear){
	AVLTree<string, int> test;
	EXPECT_NO_THROW(test.clear());
}

TEST(AVLTest, IteratorCheck){
	AVLTree<string, int> test;
	EXPECT_EQ(test.end(), test.begin());
}

TEST(AVLTest, FindTest1){
	AVLTree<string, int> test;

	test.insert(make_pair("billy", 1));
	AVLTree<string, int>::iterator it = test.find("billy");
	AVLNode<string, int> *curr = static_cast<AVLNode<string, int>*>(it.current_);

	EXPECT_EQ("billy", curr->getKey());
}

TEST(AVLTest, FindTest2){
	AVLTree<string, int> test;

	AVLTree<string, int>::iterator it = test.find("billy");
	AVLNode<string, int> *curr = static_cast<AVLNode<string, int>*>(it.current_);

	EXPECT_EQ(NULL, curr);
}

TEST(AVLTest, IsBalancedEmpty){
	AVLTree<int, int> test;
	EXPECT_TRUE(test.isBalanced() == true);
}

TEST(AVLTest, AddNominal1){
	AVLTree<int, int> test;
	
	test.insert(make_pair(1, 1));
	test.insert(make_pair(2, 2));
	test.insert(make_pair(3, 3));
	test.insert(make_pair(4, 4));

	AVLTree<int, int>::iterator it = test.begin();
	++it;

	EXPECT_EQ(NULL, (it.current_)->getParent());
}

TEST(AVLTest, AddNominal2){
	AVLTree<int, int> test;
	
	test.insert(make_pair(5, 5));
	test.insert(make_pair(1, 1));
	test.insert(make_pair(2, 2));
	test.insert(make_pair(32, 32));
	test.insert(make_pair(51, 51));
	test.insert(make_pair(12, 12));
	test.insert(make_pair(10, 10));
	test.insert(make_pair(35, 35));

	AVLTree<int, int>::iterator it = test.find(5);

	EXPECT_EQ(NULL, (it.current_)->getParent());
}

TEST(AVLTest, AddNominal3){
	AVLTree<int, int> test;
	
	test.insert(make_pair(5, 5));
	test.insert(make_pair(1, 1));
	test.insert(make_pair(2, 2));
	test.insert(make_pair(32, 32));
	test.insert(make_pair(51, 51));
	test.insert(make_pair(12, 12));
	test.insert(make_pair(10, 10));
	test.insert(make_pair(35, 35));

	AVLTree<int, int>::iterator it = test.find(5);
	AVLNode<int, int> *curr = static_cast<AVLNode<int, int>*>((it.current_)->getParent());

	EXPECT_EQ(NULL, curr);
}

TEST(AVLTest, AddNominal4){
	AVLTree<int, int> test;
	
	test.insert(make_pair(5, 5));
	test.insert(make_pair(1, 1));
	test.insert(make_pair(2, 2));
	test.insert(make_pair(32, 32));
	test.insert(make_pair(51, 51));
	test.insert(make_pair(12, 12));
	test.insert(make_pair(10, 10));
	test.insert(make_pair(35, 35));

	AVLTree<int, int>::iterator it = test.find(5);
	AVLNode<int, int> *curr = static_cast<AVLNode<int, int>*>(it.current_);

	EXPECT_EQ(4, curr->getHeight());
}

TEST(AVLTest, AddNominal5){
	AVLTree<int, int> test;
	
	test.insert(make_pair(5, 5));
	test.insert(make_pair(1, 1));
	test.insert(make_pair(2, 2));
	test.insert(make_pair(32, 32));
	test.insert(make_pair(51, 51));
	test.insert(make_pair(12, 12));
	test.insert(make_pair(10, 10));
	test.insert(make_pair(35, 35));
	test.insert(make_pair(2, 5));
	test.insert(make_pair(2, 3));

	AVLTree<int, int>::iterator it = test.find(2);
	AVLNode<int, int> *curr = static_cast<AVLNode<int, int>*>(it.current_);

	EXPECT_EQ(3, curr->getValue());
}

TEST(AVLTest, RemoveNominal1){
	AVLTree<int, int> test;
	
	test.insert(make_pair(5, 5));
	test.insert(make_pair(1, 1));
	test.insert(make_pair(2, 2));
	test.insert(make_pair(32, 32));
	test.insert(make_pair(51, 51));
	test.insert(make_pair(12, 12));
	test.insert(make_pair(10, 10));
	test.insert(make_pair(35, 35));
	test.insert(make_pair(57, 57));
	test.insert(make_pair(92, 92));

	test.remove(32);

	AVLTree<int, int>::iterator it = test.find(12);
	AVLNode<int, int> *curr = static_cast<AVLNode<int, int>*>(it.current_);

	EXPECT_EQ(NULL, curr->getParent());
}

TEST(AVLTest, RemoveNominal2){
	AVLTree<int, int> test;
	
	test.insert(make_pair(5, 5));
	test.insert(make_pair(1, 1));
	test.insert(make_pair(2, 2));
	test.insert(make_pair(32, 32));
	test.insert(make_pair(51, 51));
	test.insert(make_pair(12, 12));
	test.insert(make_pair(10, 10));
	test.insert(make_pair(35, 35));
	test.insert(make_pair(57, 57));
	test.insert(make_pair(92, 92));

	test.remove(32);
	test.remove(12);

	AVLTree<int, int>::iterator it = test.find(10);
	AVLNode<int, int> *curr = static_cast<AVLNode<int, int>*>(it.current_);

	EXPECT_EQ(NULL, curr->getParent());
}

TEST(AVLTest, RemoveNominal3){
	AVLTree<int, int> test;
	
	test.insert(make_pair(5, 5));
	test.insert(make_pair(1, 1));
	test.insert(make_pair(2, 2));
	test.insert(make_pair(32, 32));
	test.insert(make_pair(51, 51));
	test.insert(make_pair(12, 12));
	test.insert(make_pair(10, 10));
	test.insert(make_pair(35, 35));
	test.insert(make_pair(57, 57));
	test.insert(make_pair(92, 92));
	test.insert(make_pair(2, 5));

	test.remove(32);
	test.remove(12);

	AVLTree<int, int>::iterator it = test.find(10);
	AVLNode<int, int> *leftChild = static_cast<AVLNode<int, int>*>((it.current_)->getLeft());

	EXPECT_EQ(5, leftChild->getValue());
}

TEST(AVLTest, RemoveNominal4){
	AVLTree<int, int> test;
	
	test.insert(make_pair(5, 5));
	test.insert(make_pair(1, 1));
	test.insert(make_pair(2, 2));
	test.insert(make_pair(32, 32));
	test.insert(make_pair(51, 51));
	test.insert(make_pair(12, 12));
	test.insert(make_pair(10, 10));
	test.insert(make_pair(35, 35));
	test.insert(make_pair(57, 57));
	test.insert(make_pair(92, 92));

	test.remove(32);
	test.remove(12);

	AVLTree<int, int>::iterator it = test.find(10);
	AVLNode<int, int> *rightChild = static_cast<AVLNode<int, int>*>((it.current_)->getRight());

	EXPECT_EQ(51, rightChild->getKey());
}

TEST(AVLTest, Stress){
	srand(time(0));

	AVLTree<int, int> test;
	vector<int> nums;

	for(int i = 0; i < 300; i++){
		int number = rand() % 1000;
		while(test.find(number) != test.end()){
			number = rand() % 1000;
		}
		nums.push_back(number);
		test.insert(make_pair(number, i));
	}

	for(int i = 0; i < 299; i++){
		int key = nums[i];
		test.remove(key);
	}

	AVLTree<int, int>::iterator it = test.begin();

	EXPECT_EQ(nums[299], (it.current_)->getKey());
}