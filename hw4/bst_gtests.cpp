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
 	g++ -g -Wall -std=c++11 bst_gtests.cpp -I /usr/include/gtest/ -l gtest -l gtest_main -pthread -o bstg

 Thanks.
 - Jamie
 **/

TEST(BSTTest, EmptyRemove){
	BinarySearchTree<string, int> test;
	EXPECT_NO_THROW(test.remove("jerry"));
}

TEST(BSTTest, EmptyClear){
	BinarySearchTree<string, int> test;
	EXPECT_NO_THROW(test.clear());
}

TEST(BSTTest, IteratorCheck){
	BinarySearchTree<string, int> test;
	EXPECT_EQ(test.end(), test.begin());
}

TEST(BSTTest, AddNominal1){
	BinarySearchTree<string, int> test;
	test.insert(make_pair("JJ", 1));
	test.insert(make_pair("Allison", 2));
	test.insert(make_pair("Luke", 3));
	test.insert(make_pair("Hari", 4));
	test.insert(make_pair("Justin", 5));
	test.insert(make_pair("Cam", 6));

	BinarySearchTree<string, int>::iterator it = test.begin();

	EXPECT_EQ("Allison", it->first);
}

TEST(BSTTest, AddNominal2){
	BinarySearchTree<int, int> test;
	test.insert(make_pair(1, 1));
	test.insert(make_pair(2, 2));
	test.insert(make_pair(3, 3));
	test.insert(make_pair(4, 4));
	test.insert(make_pair(5, 5));
	test.insert(make_pair(6, 6));

	BinarySearchTree<int, int>::iterator it = test.begin();

	EXPECT_EQ(NULL, (it.current_)->getLeft());
}

TEST(BSTTest, AddNominal3){
	BinarySearchTree<int, int> test;
	test.insert(make_pair(1, 1));
	test.insert(make_pair(1, 0));
	test.insert(make_pair(1, 3));
	test.insert(make_pair(1, 5));

	BinarySearchTree<int, int>::iterator it = test.begin();

	EXPECT_EQ(5, (it.current_)->getValue());

}

TEST(BSTTest, RemoveNominal1){
	BinarySearchTree<int, int> test;
	test.insert(make_pair(1, 1));
	test.insert(make_pair(2, 2));
	test.insert(make_pair(3, 3));
	test.insert(make_pair(4, 4));

	test.remove(1);

	BinarySearchTree<int, int>::iterator it = test.begin();

	EXPECT_EQ(2, (it.current_)->getKey());
}

TEST(BSTTest, RemoveNominal3){
	BinarySearchTree<int, int> test;
	test.insert(make_pair(1, 1));
	test.insert(make_pair(2, 2));
	test.insert(make_pair(3, 3));
	test.insert(make_pair(4, 4));

	test.remove(4);

	BinarySearchTree<int, int>::iterator it = test.begin();
	++it;
	++it;

	EXPECT_EQ(3, (it.current_)->getKey());
}

TEST(BSTTest, RemoveNominal4){
	BinarySearchTree<int, int> test;
	test.insert(make_pair(1, 1));
	test.insert(make_pair(2, 2));
	test.insert(make_pair(3, 3));
	test.insert(make_pair(4, 4));

	test.remove(4);

	BinarySearchTree<int, int>::iterator it = test.begin();
	++it;
	++it;

	EXPECT_EQ(NULL, (it.current_)->getRight());
}

TEST(BSTTest, RemoveNominal5){
	BinarySearchTree<int, int> test;
	test.insert(make_pair(1, 1));
	test.insert(make_pair(2, 2));
	test.insert(make_pair(3, 3));
	test.insert(make_pair(4, 4));

	test.remove(3);

	BinarySearchTree<int, int>::iterator it = test.begin();
	++it;
	++it;

	EXPECT_EQ(4, (it.current_)->getKey());
}

TEST(BSTTest, RemoveNominal6){
	BinarySearchTree<int, int> test;
	test.insert(make_pair(2, 2));
	test.insert(make_pair(1, 1));
	test.insert(make_pair(3, 3));
	test.insert(make_pair(4, 4));

	test.remove(3);

	BinarySearchTree<int, int>::iterator it = test.begin();
	++it;
	++it;

	EXPECT_EQ(4, (it.current_)->getKey());
}

TEST(BSTTest, RemoveNominal7){
	BinarySearchTree<int, int> test;
	test.insert(make_pair(5, 5));
	test.insert(make_pair(6, 6));
	test.insert(make_pair(7, 7));
	test.insert(make_pair(3, 3));
	test.insert(make_pair(2, 2));
	test.insert(make_pair(4, 4));

	test.remove(5);
	test.remove(4);

	BinarySearchTree<int, int>::iterator it = test.begin();
	++it;

	EXPECT_EQ(NULL, (it.current_)->getParent());

}

TEST(BSTTest, IsBalancedTest1){
	BinarySearchTree<int, int> test;
	test.insert(make_pair(5, 5));
	test.insert(make_pair(6, 6));
	test.insert(make_pair(7, 7));
	test.insert(make_pair(3, 3));
	test.insert(make_pair(2, 2));
	test.insert(make_pair(4, 4));

	EXPECT_TRUE(test.isBalanced() == true);
}

TEST(BSTTest, IsBalancedTest2){
	BinarySearchTree<int, int> test;
	test.insert(make_pair(18, 18));
	test.insert(make_pair(21, 21));
	test.insert(make_pair(22, 22));
	test.insert(make_pair(19, 19));
	test.insert(make_pair(96, 96));
	test.insert(make_pair(51, 51));
	test.insert(make_pair(53, 53));
	test.insert(make_pair(4, 4));
	test.insert(make_pair(3, 3));
	test.insert(make_pair(72, 72));
	test.insert(make_pair(61, 61));

	EXPECT_TRUE(test.isBalanced() == false);
}

TEST(BSTTest, LightStress){
	BinarySearchTree<int, int> test;
	test.insert(make_pair(18, 18));
	test.insert(make_pair(21, 21));
	test.insert(make_pair(22, 22));
	test.insert(make_pair(19, 19));
	test.insert(make_pair(96, 96));
	test.insert(make_pair(51, 51));
	test.insert(make_pair(53, 53));
	test.insert(make_pair(4, 4));
	test.insert(make_pair(3, 3));
	test.insert(make_pair(72, 72));
	test.insert(make_pair(61, 61));

	test.clear();

	EXPECT_EQ(test.end(), test.begin());
}