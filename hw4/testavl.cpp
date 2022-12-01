#include "avlbst.h"
#include "bst.h"
#include "gtest/gtest.h"
#include "print_bst.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <map>
#include <stdexcept>
#include <stdlib.h>
#include <string>
#include <vector>

using namespace std;

// set to 0 if you do not want to check balance after every insert/remove in the stress tests. (Checking balance will
// take a bit of time).
#define CHECK_BALANCE_IN_STRESS_TESTS 1

/* assumes (does not check/care about) both trees have valid links (i.e. parent pointers are set up properly) */
template<typename Key, typename Value>
bool operator==(const AVLNode<Key, Value>& root1, const AVLNode<Key, Value>& root2);

/* compares two tree pointers to check for equality in tree structure */
template<typename Key, typename Value>
bool compTreePtrs(AVLNode<Key, Value> const* root1, AVLNode<Key, Value> const* root2);

/* checks whether or not parent pointers are correct, assuming correct left and right children pointers*/
template<typename Key, typename Value>
bool correctParentPtrs(AVLNode<Key, Value> const* root);

template<typename Key, typename Value>
void cleanup(AVLNode<Key, Value>* root);

TEST(AVLTest, AddAndUpdate) {
    AVLTree<int, string> test;
    test.insert(make_pair(3, "a"));
    EXPECT_TRUE(test.isBalanced());
    test.insert(make_pair(4, "b"));
    EXPECT_TRUE(test.isBalanced());
    test.insert(make_pair(23, "c"));
    EXPECT_TRUE(test.isBalanced());
    test.insert(make_pair(2, "d"));
    EXPECT_TRUE(test.isBalanced());
    test.insert(make_pair(15, "e"));
    EXPECT_TRUE(test.isBalanced());
    test.insert(make_pair(19, "f"));
    EXPECT_TRUE(test.isBalanced());

    test.insert(make_pair(2, "update1"));
    EXPECT_TRUE(test.isBalanced());
    test.insert(make_pair(15, "update2"));
    EXPECT_TRUE(test.isBalanced());

    AVLNode<int, string>* expected = new AVLNode<int, string>(4, "b", NULL);
    expected->setHeight(3);

    expected->setLeft(new AVLNode<int, string>(3, "a", expected));
    expected->getLeft()->setHeight(2);
    expected->getLeft()->setLeft(new AVLNode<int, string>(2, "update1", expected->getLeft()));

    expected->setRight(new AVLNode<int, string>(19, "f", expected));
    expected->getRight()->setHeight(2);
    expected->getRight()->setLeft(new AVLNode<int, string>(15, "update2", expected->getRight()));
    expected->getRight()->setRight(new AVLNode<int, string>(23, "c", expected->getRight()));

    EXPECT_EQ(*expected, test.root());
    EXPECT_TRUE(correctParentPtrs(&test.root()));
    cleanup(expected);
}

TEST(AVLTest, RemoveNominal) {
    AVLTree<int, string> test;
    test.insert(make_pair(5, "a"));
    EXPECT_TRUE(test.isBalanced());
    test.insert(make_pair(2, "b"));
    EXPECT_TRUE(test.isBalanced());
    test.insert(make_pair(1, "c"));
    EXPECT_TRUE(test.isBalanced());
    test.insert(make_pair(7, "d"));
    EXPECT_TRUE(test.isBalanced());
    test.insert(make_pair(9, "e"));
    EXPECT_TRUE(test.isBalanced());
    test.insert(make_pair(13, "f"));
    EXPECT_TRUE(test.isBalanced());
    test.remove(13);
    EXPECT_TRUE(test.isBalanced());
    test.remove(9);
    EXPECT_TRUE(test.isBalanced());
    test.remove(2);

    AVLNode<int, string>* expected = new AVLNode<int, string>(5, "a", NULL);
    expected->setHeight(2);

    expected->setLeft(new AVLNode<int, string>(1, "c", expected));
    expected->setRight(new AVLNode<int, string>(7, "d", expected));

    EXPECT_EQ(*expected, test.root());
    EXPECT_TRUE(correctParentPtrs(&test.root()));

    cleanup(expected);
}

#define MAX_MAG 1000
#define MAX_NUM_ELEM 1000

/* could catch memory leaks */
TEST(AVLTest, StressTest1) {
    srand(time(NULL));  // random seed

    AVLTree<int, string> test;
    for (int i = -MAX_MAG; i < MAX_MAG; ++i) {
        test.insert(make_pair(i, "a"));
        if (CHECK_BALANCE_IN_STRESS_TESTS) {
            EXPECT_TRUE(test.isBalanced());
        }
    }

    for (int i = 0; i < 10 * MAX_MAG; ++i) {  // upper bound on loop can be changed however you would like
        int rand_idx = (rand() % (2 * MAX_MAG)) - MAX_MAG;
        test.remove(rand_idx);
        if (CHECK_BALANCE_IN_STRESS_TESTS) {
            // std::cout << "rand_idx: " << rand_idx << std::endl;
            EXPECT_TRUE(test.isBalanced());
        }
    }

    // now cleanup
    for (int i = -MAX_MAG; i < MAX_MAG; ++i) {
        test.remove(i);
        if (CHECK_BALANCE_IN_STRESS_TESTS) {
            EXPECT_TRUE(test.isBalanced());
        }
    }

    test.insert(make_pair(3, "filler for empty tree"));
    AVLNode<int, string>* expected = new AVLNode<int, string>(3, "filler for empty tree", NULL);

    EXPECT_EQ(*expected, test.root());
    EXPECT_TRUE(correctParentPtrs(&test.root()));

    cleanup(expected);
}

TEST(AVLTest, IteratorTest) {
    srand(time(NULL));  // random seed

    AVLTree<int, int> test;
    map<int, int> expected;

    // add some random values
    for (int i = 0; i < MAX_NUM_ELEM; ++i) {
        int rand_idx = rand() % MAX_NUM_ELEM;
        int rand_val = (rand() % (2 * MAX_MAG)) - MAX_MAG;
        test.insert(make_pair(rand_idx, rand_val));
        if (CHECK_BALANCE_IN_STRESS_TESTS) {
            EXPECT_TRUE(test.isBalanced());
        }
        expected[rand_idx] = rand_val;
    }

    AVLTree<int, int>::iterator it1 = test.begin();
    map<int, int>::iterator it2 = expected.begin();
    while (it1 != test.end() && it2 != expected.end()) {
        EXPECT_EQ(*it1, *it2);
        ++it1;
        ++it2;
    }

    EXPECT_EQ(it1, test.end());
    EXPECT_EQ(it2, expected.end());
    EXPECT_TRUE(correctParentPtrs(&test.root()));

    // remove some random values
    for (int i = 0; i < MAX_NUM_ELEM; ++i) {
        int rand_idx = rand() % MAX_NUM_ELEM;
        test.remove(rand_idx);
        if (CHECK_BALANCE_IN_STRESS_TESTS) {
            EXPECT_TRUE(test.isBalanced());
        }
        expected.erase(rand_idx);
    }

    // iterate again and make sure things still match
    it1 = test.begin();
    it2 = expected.begin();
    while (it1 != test.end() && it2 != expected.end()) {
        EXPECT_EQ(*it1, *it2);
        ++it1;
        ++it2;
    }

    EXPECT_EQ(it1, test.end());
    EXPECT_EQ(it2, expected.end());
    EXPECT_TRUE(correctParentPtrs(&test.root()));
}

AVLNode<int, string>* tempFunc(int i, AVLNode<int, string>* parent) {
    return new AVLNode<int, string>(i, string(1, 'a' + i), parent);
}

TEST(AVLTest, MoreRemoveCases) {
    AVLTree<int, string> test;
    for (int i = 0; i < 10; ++i) {
        test.insert(make_pair(i, string(1, 'a' + i)));
        EXPECT_TRUE(test.isBalanced());
    }
    for (int i = 19; i >= 10; --i) {
        test.insert(make_pair(i, string(1, 'a' + i)));
        EXPECT_TRUE(test.isBalanced());
    }
    test.remove(8);
    EXPECT_TRUE(test.isBalanced());
    test.remove(7);
    EXPECT_TRUE(test.isBalanced());
    test.remove(6);
    EXPECT_TRUE(test.isBalanced());
    test.remove(4);
    EXPECT_TRUE(test.isBalanced());
    test.remove(12);
    EXPECT_TRUE(test.isBalanced());
    test.remove(13);
    EXPECT_TRUE(test.isBalanced());
    test.remove(17);
    EXPECT_TRUE(test.isBalanced());
    test.remove(10);
    EXPECT_TRUE(test.isBalanced());
    test.remove(3);
    EXPECT_TRUE(test.isBalanced());
    test.remove(1);
    EXPECT_TRUE(test.isBalanced());

    EXPECT_NO_THROW(test.remove(1));

    AVLNode<int, string>* expected = tempFunc(14, NULL);
    expected->setHeight(4);
    expected->setLeft(tempFunc(5, expected));
    expected->getLeft()->setHeight(3);
    expected->getLeft()->setLeft(tempFunc(0, expected->getLeft()));
    expected->getLeft()->getLeft()->setHeight(2);
    expected->getLeft()->getLeft()->setRight(tempFunc(2, expected->getLeft()->getLeft()));

    expected->getLeft()->setRight(tempFunc(9, expected->getLeft()));
    expected->getLeft()->getRight()->setHeight(2);
    expected->getLeft()->getRight()->setRight(tempFunc(11, expected->getLeft()->getRight()));

    expected->setRight(tempFunc(16, expected));
    expected->getRight()->setHeight(3);
    expected->getRight()->setLeft(tempFunc(15, expected->getRight()));
    expected->getRight()->setRight(tempFunc(18, expected->getRight()));
    expected->getRight()->getRight()->setHeight(2);
    expected->getRight()->getRight()->setRight(tempFunc(19, expected->getRight()->getRight()));

    EXPECT_EQ(*expected, test.root());
    EXPECT_TRUE(correctParentPtrs(&test.root()));

    cleanup(expected);
}

/* checks if the parent pointers of all children of root are correctly set up */
template<typename Key, typename Value>
bool correctParentPtrs(AVLNode<Key, Value> const* root) {
    if (root == NULL) {
        return true;
    }
    bool left_correct = true;
    bool right_correct = true;
    if (root->getLeft() != NULL) {
        left_correct = root->getLeft()->getParent() == root;
    }
    if (root->getRight() != NULL) {
        right_correct = root->getRight()->getParent() == root;
    }
    return left_correct && right_correct && correctParentPtrs(root->getLeft()) && correctParentPtrs(root->getRight());
}

template<typename Key, typename Value>
bool operator==(const AVLNode<Key, Value>& root1, const AVLNode<Key, Value>& root2) {
    return compTreePtrs(&root1, &root2);
}

template<typename Key, typename Value>
bool compTreePtrs(AVLNode<Key, Value> const* root1, AVLNode<Key, Value> const* root2) {
    if (root1 == NULL && root2 == NULL) {
        return true;
    } else if (root1 != NULL and root2 != NULL) {
        bool root_node_eq = (root1->getItem() == root2->getItem()) && (root1->getHeight() == root2->getHeight());
        return root_node_eq && compTreePtrs(root1->getLeft(), root2->getLeft())
               && compTreePtrs(root1->getRight(), root2->getRight());
    } else {
        return false;
    }
}

template<typename Key, typename Value>
void cleanup(AVLNode<Key, Value>* root) {
    if (root == NULL) {
        return;
    } else {
        cleanup(root->getLeft());
        cleanup(root->getRight());
        delete root;
    }
}