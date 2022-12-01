#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <cstdlib>
#include <string>
#include "bst.h"

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    char getBalance () const;
    void setBalance (char balance);
    void updateBalance(char diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    char balance_;
};

/*
--------------------------------------------
Begin implementations for the AVLNode class.
--------------------------------------------
*/

/**
* Constructor for an AVLNode. Nodes are initialized with a balance of 0.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent)
    : Node<Key, Value>(key, value, parent),
      balance_(0)
{

}

/**
* Destructor.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
char AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(char balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(char diff)
{
    balance_ += diff;
}

/**
* Getter function for the parent. Used since the node inherits from a base node.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key,Value>*>(this->mParent);
}

/**
* Getter function for the left child. Used since the node inherits from a base node.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key,Value>*>(this->mLeft);
}

/**
* Getter function for the right child. Used since the node inherits from a base node.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key,Value>*>(this->mRight);
}

/*
------------------------------------------
End implementations for the AVLNode class.
------------------------------------------
*/

/**
* A templated balanced binary search tree implemented as an AVL tree.
*/
template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    // Methods for inserting/erasing (removing) elements from the tree. 
    // You must implement both of these methods.
    virtual void insert(const std::pair<Key, Value>& keyValuePair) override;
    virtual void erase(const Key& key);

private:
    /* Helper functions are strongly encouraged to help separate the problem
       into smaller pieces. You should not need additional data members. */

    /* You should write these helpers for sure.  You may add others. */
    void rotateLeft (AVLNode<Key, Value> *n);
    void rotateRight (AVLNode<Key, Value> *n);

    /* A provided helper function to swap 2 nodes location in the tree */
    void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    void insertFix(AVLNode<Key, Value> *p, AVLNode<Key, Value> *n);
    void eraseFix(AVLNode<Key,Value> *n, int diff);

};

/*
--------------------------------------------
Begin implementations for the AVLTree class.
--------------------------------------------
*/

/**
* Insert function for a key value pair. Finds location to insert the node and then balances the tree.
*/
template<typename Key, typename Value>
void AVLTree<Key, Value>::insert(const std::pair<Key, Value>& keyValuePair)
{
    // TODO
    typename BinarySearchTree<Key, Value>::iterator it = this->find(keyValuePair.first);
    if( it != this->end() ){
        (*it).second = keyValuePair.second;
        return;
    }

    AVLNode<Key,Value>* n = new AVLNode<Key, Value>(keyValuePair.first, keyValuePair.second, NULL);
    if(this->mRoot == NULL){
    	this->mRoot = n;
    	return;
    }

    AVLNode<Key,Value>* temp = static_cast<AVLNode<Key,Value>*>(this->mRoot);
    while(1){
        if( keyValuePair.first < temp->getKey() && temp->getLeft() != NULL){
            temp = temp->getLeft();
        }
        else if(keyValuePair.first > temp->getKey() && temp->getRight() != NULL){
            temp = temp->getRight();
        }
        else if(keyValuePair.first < temp->getKey() && temp->getLeft() == NULL){
            n->setParent(temp);
            temp->setLeft(n);
            if(temp->getBalance() == 0){
            	temp->updateBalance(-1);
                insertFix(temp, n);
            }
            else{
                temp->updateBalance(-1);
            }
            break;
        }
        else if(keyValuePair.first > temp->getKey() && temp->getRight() == NULL){
            n->setParent(temp);
            temp->setRight(n);
            if(temp->getBalance() == 0){
            	temp->updateBalance(1);
                insertFix(temp, n);
            }
            else{
                temp->updateBalance(1);
            }
            break;
        }
    }
}


template<typename Key, typename Value>
void AVLTree<Key, Value>::insertFix(AVLNode<Key, Value> *parent, AVLNode<Key, Value> *n){
    if(parent == NULL ){
        return;
    }
    if(parent->getParent() == NULL){
        return;
    }

    AVLNode<Key, Value> *grandParent = parent->getParent();
    if(grandParent->getLeft() == parent){
        grandParent->updateBalance(-1);
        
        /*std::cout << grandParent->getKey() << ": ";
        std::cout << int(grandParent->getBalance()) << std::endl;*/

        if(grandParent->getBalance() == 0){
            return;
        }

        else if(grandParent->getBalance() == -1){
            insertFix(grandParent,parent);
        }
        else if(grandParent->getBalance() == -2){
        	// zig-zig
            if(parent->getLeft() == n){
                rotateRight(grandParent);
                grandParent->setBalance(0);
                parent->setBalance(0);

                /*std::cout << parent->getRight() << std::endl;
                std::cout << grandParent->getKey() << ": ";
        		std::cout << int(grandParent->getBalance()) << std::endl;*/

                /*if(parent->getParent() == NULL){
                	this->mRoot = parent;
                }*/
            }
            else{
                rotateLeft(parent);
                rotateRight(grandParent);
                if(n->getBalance() == -1){
                    parent->setBalance(0);
                    grandParent->setBalance(1);
                    n->setBalance(0);
                }
                else if(n->getBalance() == 0){
                    parent->setBalance(0);
                    grandParent->setBalance(0);
                    n->setBalance(0);
                }
                else if(n->getBalance() == 1){
                    parent->setBalance(-1);
                    grandParent->setBalance(0);
                    n->setBalance(0);
                }
            }
        }
    }
    else{
        grandParent->updateBalance(1);
        if(grandParent->getBalance() == 0){
            return;
        }
        else if(grandParent->getBalance() == 1){
            insertFix(grandParent,parent);
        }
        else if(grandParent->getBalance() == 2){
            if(parent->getRight() == n){
                rotateLeft(grandParent);
                grandParent->setBalance(0);
                parent->setBalance(0);
            }
            else{
                rotateRight(parent);
                rotateLeft(grandParent);
                if(n->getBalance() == 1){
                    parent->setBalance(0);
                    grandParent->setBalance(-1);
                    n->setBalance(0);
                }
                else if(n->getBalance() == 0){
                    parent->setBalance(0);
                    grandParent->setBalance(0);
                    n->setBalance(0);
                }
                else if(n->getBalance() == -1){
                    parent->setBalance(1);
                    grandParent->setBalance(0);
                    n->setBalance(0);
                }
            }
        }
    }

}


/**
* Erase function for a given key. Finds the node, reattaches pointers, and then balances when finished.
*/
template<typename Key, typename Value>
void AVLTree<Key, Value>::erase(const Key& key)
{
    // TODO
    if(this->mRoot == NULL){
    	return;
    }

    typename BinarySearchTree<Key, Value>::iterator it = this->find(key);
    if( it == this->end()){
        return;
    }

    AVLNode<Key, Value>* n = static_cast<AVLNode<Key, Value>*>(it.getNode()); 

    if(n->getLeft() != NULL && n->getRight() != NULL){
        AVLNode<Key, Value>* nSuccessor = static_cast<AVLNode<Key, Value>*>((++it).getNode());
        nodeSwap(n, nSuccessor);
    }


    AVLNode<Key,Value>* parent = n->getParent();
    int diff;
    AVLNode<Key, Value>* child = n->getLeft();

    if(child == NULL){
        child = n->getRight();
    }

    if(child != NULL){
        child->setParent(parent);
    }

    if(parent->getLeft() == n){
        diff = 1;
        parent->setLeft(child);
    }
    else{
        diff = -1;
        parent->setRight(child);
    }

    delete n;
    eraseFix(parent,diff);
}

template<typename Key, typename Value>
void AVLTree<Key, Value>::eraseFix(AVLNode<Key,Value> *n, int diff){
	if(n == NULL){
   		return;
   	}

   	int ndiff;
   	AVLNode<Key, Value> * tallerChild;
   	AVLNode<Key, Value> * grandChild;

   	AVLNode<Key, Value> *parent = n->getParent();
   	if(parent != NULL){
   		if(parent->getLeft() == n){
   			ndiff = 1;
   		}
   		else{
   			ndiff = -1;
   		}
   	}
   	else{
   		ndiff = 0;
   	}

   	if(diff == -1){
   	if(n->getBalance() + diff == -2){
   		tallerChild = n->getLeft();
   		if(tallerChild->getBalance() < 1){

   			rotateRight(n);

   			if(tallerChild->getBalance() == -1){
   				n->setBalance(0);
   				tallerChild->setBalance(0);
   				eraseFix(parent, ndiff);
   			}
   			else if(tallerChild->getBalance() == 0){
   				n->setBalance(-1);
   				tallerChild->setBalance(1);
   			}
   		}
   		else if(tallerChild->getBalance() == 1){

   			grandChild = tallerChild->getRight();
   			rotateLeft(tallerChild);
   			rotateRight(n);

   			if(grandChild->getBalance() == 1){
   				n->setBalance(0);
   				tallerChild->setBalance(-1);
   				grandChild->setBalance(0);
   			}
   			else if(grandChild->getBalance() == 0){
   				n->setBalance(0);
   				tallerChild->setBalance(0);
   				grandChild->setBalance(0);
   			}
   			else if(grandChild->getBalance() == -1){
   				n->setBalance(1);
   				tallerChild->setBalance(0);
   				grandChild->setBalance(0);
   			}
   			eraseFix(parent->getParent(), ndiff);
   		}
   	}
   	else if(n->getBalance() + diff == -1){
   		n->updateBalance(diff);
   	}
   	else{
   		n->setBalance(0);
   		eraseFix(parent, ndiff);
   	}

   }
   else if(diff == 1){
   	
   	if(n->getBalance()+ diff == 2){
   	
   		tallerChild = n->getRight();

   		if(tallerChild->getBalance() > -1){

   			rotateLeft(n);

   			if(tallerChild->getBalance() == +1){
   				n->setBalance(0);
   				tallerChild->setBalance(0);
   				eraseFix(parent, ndiff);
   			}
   			else if(tallerChild->getBalance() == 0){
   				n->setBalance(+1);
   				tallerChild->setBalance(1);
   			}
   		}
   		else if(tallerChild->getBalance() == -1){
   			grandChild = tallerChild->getLeft();
   			rotateRight(tallerChild);
   			rotateLeft(n);

   			
   			if(grandChild->getBalance() == -1){
   				n->setBalance(0);
   				tallerChild->setBalance(1);
   				grandChild->setBalance(0);
   			}
   			else if(grandChild->getBalance() == 0){
   				n->setBalance(0);
   				tallerChild->setBalance(0);
   				grandChild->setBalance(0);
   			}
   			else if(grandChild->getBalance() == 1){
   				n->setBalance(-1);
   				tallerChild->setBalance(0);
   				grandChild->setBalance(0);
   			}
   			eraseFix(parent->getParent(), ndiff);
   		}
   	}
   	else if(n->getBalance() + diff == 1){
   		n->updateBalance(diff);
   	}
   	else{
   		n->setBalance(0);
   		eraseFix(parent, ndiff);
   	}
   }


}


/**
* Rotates n down and to the left
*/
template<typename Key, typename Value>
void AVLTree<Key, Value>::rotateLeft (AVLNode<Key, Value> *n)
{
    // TODO
    if(n == NULL ){
        return;
    }

    if(n->getRight() == NULL){
        return;
    }

    AVLNode<Key, Value>* rightChild = n->getRight();
    AVLNode<Key, Value>* grandParent = n->getParent();
    AVLNode<Key, Value>* leftGrandChild = rightChild->getLeft();


    rightChild->setLeft(n);
    n->setParent(rightChild);

    n->setRight(leftGrandChild);
    if(leftGrandChild != NULL){
    	leftGrandChild->setParent(n);
    }

    rightChild->setParent(grandParent);
    if(grandParent != NULL){
    	if(grandParent->getLeft() == n){
    		grandParent->setLeft(rightChild);
    	}
    	else{
    		grandParent->setRight(rightChild);
    	}
    }
    else{
    	this->mRoot = rightChild;
    }   
}

/**
* Rotates n down and to the right
*/
template<typename Key, typename Value>
void AVLTree<Key, Value>::rotateRight (AVLNode<Key, Value> *n)
{
    // TODO
    if(n == NULL){
        return;
    }

    if(n->getLeft() == NULL){
        return;
    }

    AVLNode<Key, Value>* leftChild = n->getLeft();
    AVLNode<Key, Value>* grandParent = n->getParent();
    AVLNode<Key, Value>* rightGrandChild = leftChild->getRight();

    leftChild->setRight(n);
    n->setParent(leftChild);

    n->setLeft(rightGrandChild);
    if(rightGrandChild != NULL){
    	rightGrandChild->setParent(n);
    }

    leftChild->setParent(grandParent);

    if(grandParent != NULL){
    	if(grandParent->getLeft() == n){
    		grandParent->setLeft(leftChild);
    	}
    	else{
    		grandParent->setRight(leftChild);
    	}
    }
    else{
    	this->mRoot = leftChild;
    }
}

/**
 * Given a correct AVL tree, this functions relinks the tree in such a way that
 * the nodes swap positions in the tree.  Balances are also swapped.
 */
template<typename Key, typename Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    if((n1 == n2) || (n1 == NULL) || (n2 == NULL) ) {
        return;
    }
    Node<Key, Value>* n1p = n1->getParent();
    Node<Key, Value>* n1r = n1->getRight();
    Node<Key, Value>* n1lt = n1->getLeft();
    bool n1isLeft = false;
    if(n1p != NULL && (n1 == n1p->getLeft())) n1isLeft = true;
    Node<Key, Value>* n2p = n2->getParent();
    Node<Key, Value>* n2r = n2->getRight();
    Node<Key, Value>* n2lt = n2->getLeft();
    bool n2isLeft = false;
    if(n2p != NULL && (n2 == n2p->getLeft())) n2isLeft = true;


    Node<Key, Value>* temp;
    temp = n1->getParent();
    n1->setParent(n2->getParent());
    n2->setParent(temp);

    temp = n1->getLeft();
    n1->setLeft(n2->getLeft());
    n2->setLeft(temp);

    temp = n1->getRight();
    n1->setRight(n2->getRight());
    n2->setRight(temp);

    char temp2 = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(temp2);

    if( (n1r != NULL && n1r == n2) ) {
        n2->setRight(n1);
        n1->setParent(n2);
    }
    else if( n2r != NULL && n2r == n1) {
        n1->setRight(n2);
        n2->setParent(n1);

    }
    else if( n1lt != NULL && n1lt == n2) {
        n2->setLeft(n1);
        n1->setParent(n2);

    }
    else if( n2lt != NULL && n2lt == n1) {
        n1->setLeft(n2);
        n2->setParent(n1);

    }


    if(n1p != NULL && n1p != n2) {
        if(n1isLeft) n1p->setLeft(n2);
        else n1p->setRight(n2);
    }
    if(n1r != NULL && n1r != n2) {
        n1r->setParent(n2);
    }
    if(n1lt != NULL && n1lt != n2) {
        n1lt->setParent(n2);
    }

    if(n2p != NULL && n2p != n1) {
        if(n2isLeft) n2p->setLeft(n1);
        else n2p->setRight(n1);
    }
    if(n2r != NULL && n2r != n1) {
        n2r->setParent(n1);
    }
    if(n2lt != NULL && n2lt != n1) {
        n2lt->setParent(n1);
    }


    if(this->mRoot == n1) {
        this->mRoot = n2;
    }
    else if(this->mRoot == n2) {
        this->mRoot = n1;
    }

}

/*
------------------------------------------
End implementations for the AVLTree class.
------------------------------------------
*/

#endif
