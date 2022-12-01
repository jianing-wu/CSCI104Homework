#ifndef RBBST_H
#define RBBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the height as a data member, plus
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
    int getHeight () const;
    void setHeight (int height);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int height_;

};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor and setting
* the color to red since every new node will be red when it is first inserted.
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), height_(1)
{
    
}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the height of a AVLNode.
*/
template<class Key, class Value>
int AVLNode<Key, Value>::getHeight() const
{
    return height_;
}

/**
* A setter for the height of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setHeight(int height)
{
    height_ = height;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO

protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
private:
    //bool update_height(AVLNode<Key,Value>* node);
    void rotateRight(AVLNode<Key,Value>* node);
    void rotateLeft(AVLNode<Key,Value>* node);
    void insertFix(AVLNode<Key, Value>* p, AVLNode<Key, Value>* n);
    void removeFix(AVLNode<Key,Value>* n);

    bool isLeftChild(AVLNode<Key, Value>* p, AVLNode<Key, Value>* n);
    bool isRightChild(AVLNode<Key, Value>* p, AVLNode<Key, Value>* n);
    void updateHeight(AVLNode<Key, Value>* n);
};

/*
 If empty tree => set n as root, h(n) = 1, done!
 Else insert n (by walking the tree to a leaf, p, and inserting the new node as its child), set height to 1, and look at its parent, p
 If h(p) was 2, then no change. Done!
 If h(p) was 1, then update h(p) = 2, and call insert-fix(p, n)
*/
template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
    // TODO
    //typename BinarySearchTree<Key, Value>::iterator it = this->find(new_item.first);
    
    AVLNode<Key,Value>* n = static_cast<AVLNode<Key, Value>*>(BinarySearchTree<Key,Value>::internalFind(new_item.first));
    
    if(n != NULL)  //already exists, update
    {
        n->setValue(new_item.second);
        return;
    }
    
    //doesn't exist, insert
    n = new AVLNode<Key,Value>(new_item.first, new_item.second, NULL);
    
    if (this->root_ == NULL)  //empty, insert as the root
    {
        this->root_ = n;
        n->setHeight(1);
        return;
    }
    
    //not empty, start with the root
    AVLNode<Key, Value>* temp = static_cast<AVLNode<Key,Value>*>(this->root_);
    bool inserted = false;
    
    while (!inserted)
    {
        if (new_item.first < temp->getKey() && temp->getLeft() != NULL)
        {
            temp = temp->getLeft();
        }
        else if (new_item.first < temp->getKey() && temp->getLeft() == NULL)
        {
            temp->setLeft(n);
            n->setParent(temp);
            n->setHeight(1);
            if (temp->getHeight() == 2)
            {
                inserted = true;
            } else if (temp->getHeight() == 1) {
                temp->setHeight(2);
                insertFix(temp, n);
                inserted = true;
            }
        }
        else if (new_item.first > temp->getKey() && temp->getRight() != NULL)
        {
            temp = temp->getRight();
        }
        else if (new_item.first > temp->getKey() && temp->getRight() == NULL)
        {
            temp->setRight(n);
            n->setParent(temp);
            n->setHeight(1);
            if (temp->getHeight() == 2)
            {
                inserted = true;
            } else if (temp->getHeight() == 1) {
                temp->setHeight(2);
                insertFix(temp, n);
                inserted = true;
            }
        }
    }
   
}






/*
 Precondition: p and n are balanced.
 Postcondition: g, p, and n are balanced.
 If p is null or parent(p) is null, return
 Let g = parent(p)
 Calculate height of g: max(h(left), h(right))+1
 Case 1: g’s height doesn’t change, done!
 Case 2: g is balanced, insertFix(g, p)
 Case 3: g is unbalanced
         If zig-zig then rotateRight(g) or rotateLeft(g).
         - Recalculate height of g and p.
         If zig-zag then (rotateLeft(p) followed by rotateRight(g))
         or (rotateRight(p) followed by rotateLeft(g))
         - Recalculate height of g, p, and n.
*/
template<typename Key, typename Value>
void AVLTree<Key, Value>::insertFix(AVLNode<Key, Value>* parent, AVLNode<Key, Value>* n)
{
    if (parent == NULL || parent->getParent() == NULL)
    {
        return;
    }

    AVLNode<Key, Value>* grandParent = parent->getParent();
    
    AVLNode<Key, Value>* gLeft = grandParent->getLeft();
    AVLNode<Key, Value>* gRight = grandParent->getRight();
    int gLeftHeight = gLeft == NULL ? 0 : gLeft->getHeight();
    int gRightHeight = gRight == NULL ? 0 : gRight->getHeight();

    int newGrandParentHeight = std::max(gLeftHeight, gRightHeight) + 1; 

    // g's height does not change
    if (newGrandParentHeight == grandParent->getHeight()) {
        return;
    }

    // g is balanced
    if (std::abs(gLeftHeight - gRightHeight) <= 1) 
    {   
        grandParent->setHeight(newGrandParentHeight);
        insertFix(grandParent, parent);
    } else  // g is unbalanced
    {
        // zig-zig left
        if (isLeftChild(grandParent, parent) && isLeftChild(parent, n)) {
            rotateRight(grandParent);
            
        } else if (isRightChild(grandParent, parent) && isRightChild(parent, n)) // zig-zig right
        {
            rotateLeft(grandParent);
        } else if (isLeftChild(grandParent, parent) && isRightChild(parent, n)) // zig-zag 
        {
            rotateLeft(parent);
            rotateRight(grandParent);
        } else // zig-zag 
        {
            rotateRight(parent);
            rotateLeft(grandParent);
        }
        updateHeight(grandParent);
        updateHeight(parent);
        updateHeight(n);
    }
}


template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
    // TODO
    if (this->root_ == NULL) //empty
    {
        return;
    }
    
    AVLNode<Key,Value>* n = static_cast<AVLNode<Key, Value>*>(BinarySearchTree<Key,Value>::internalFind(key));
    if (n == NULL) //doesn't exists, do nothing
    {
        return;
    }

    if (n->getLeft() != NULL && n->getRight() != NULL) //two children
    {
        nodeSwap(n, static_cast<AVLNode<Key, Value>*>(BinarySearchTree<Key,Value>::predecessor(n)));
    }

    AVLNode<Key, Value>* parent = n->getParent();
    AVLNode<Key, Value>* child = n->getLeft();

    if (child == NULL)
    {
        child = n->getRight();
    }

    if (child != NULL)
    {
        child->setParent(parent);
    }
    
    if (parent != NULL)
    {
        if (parent->getLeft() == n)
        {
            parent->setLeft(child);
        } else
        {
            parent->setRight(child);
        }
    } else
    {
        this->root_ = child;
    }
    
    delete n;
    
    removeFix(parent);
}

/*
 If n is null, return
 Case 1: n is out of balance
         Let c = the taller of the children (there cannot be ties)
         Let g = the taller of c’s children (important: break ties in preference of a zig-zig!)
         Case 1: zig-zig case
            rotateRight(n) or rotateLeft(n), update h(n) and h(c), removeFix(p)
         Case 2: zig-zag case
            (rotateLeft(c) then rotateRight(n)) or (rotateRight(c) then rotateLeft(n))
            Update h(n), h(c), h(g)
            removeFix(p);
 Case 2: n’s height is unchanged: Done!
 Case 3: otherwise: update h(n), removeFix(p)
*/
template<class Key, class Value>
void AVLTree<Key, Value>::removeFix(AVLNode<Key,Value>* n)
{
    if (n == NULL)
    {
        return;
    }
    // std::cout << "remove fix: " << n->getKey() << std::endl;

    AVLNode<Key, Value>* left = n->getLeft();
    AVLNode<Key, Value>* right = n->getRight();
    int leftHeight = left == NULL ? 0 : left->getHeight();
    // std::cout << "leftHeight: " << leftHeight << std::endl;
    int rightHeight = right == NULL ? 0 : right->getHeight();
    // std::cout << "rightHeight: " << rightHeight << std::endl;
    int newHeight = std::max(leftHeight, rightHeight) + 1;

    AVLNode<Key, Value>* tallerChild;
    AVLNode<Key, Value>* tallerGrandChild;
    

    if (std::abs(leftHeight - rightHeight) > 1)
    {
        if (leftHeight > rightHeight)
        {
            tallerChild = n->getLeft();
        } else {
            tallerChild = n->getRight();
        }
        // std::cout << "tallerChild: " << tallerChild->getKey() << std::endl;

        AVLNode<Key, Value>* childLeft = tallerChild->getLeft();
        AVLNode<Key, Value>* childRight = tallerChild->getRight();
        int cLeftHeight = childLeft == NULL ? 0 : childLeft->getHeight();
        int cRightHeight = childRight == NULL ? 0 : childRight->getHeight();

        if (cLeftHeight == cRightHeight) {
            tallerGrandChild = isLeftChild(n, tallerChild) ? childLeft : childRight;
        } else if (cLeftHeight > cRightHeight) {
            tallerGrandChild = childLeft;
        } else {
            tallerGrandChild = childRight;
        }

        // std::cout << "tallerGrandChild: " << tallerGrandChild->getKey() << std::endl;
        
        if (isLeftChild(n, tallerChild) && isLeftChild(tallerChild, tallerGrandChild)) // zig-zig left
        {
            // std::cout << "zig-zig left" << std::endl;
            rotateRight(n);
        } else if (isRightChild(n, tallerChild) && isRightChild(tallerChild, tallerGrandChild)) // zig-zig right
        {
            // std::cout << "zig-zig right" << std::endl;
            rotateLeft(n);
        } else if (isLeftChild(n, tallerChild) && isRightChild(tallerChild, tallerGrandChild)) // zig-zag left-right
        {
            // std::cout << "zig-zag left-right" << std::endl;
            rotateLeft(tallerChild);
            rotateRight(n);
        } else // zig-zag right-left
        {
            // std::cout << "zig-zag right-left" << std::endl;
            rotateRight(tallerChild);
            rotateLeft(n);
        }
        updateHeight(n);
        updateHeight(tallerChild);
        updateHeight(tallerGrandChild);
    } else if (n->getHeight() == newHeight) {
        return;
    }else  
    {
        n->setHeight(newHeight);
    }

    removeFix(n->getParent());    
}


template<typename Key, typename Value>
bool AVLTree<Key, Value>::isLeftChild(AVLNode<Key, Value>* p, AVLNode<Key, Value>* n) 
{
    if (p == NULL) {
        return false;
    }
    return p->getLeft() == n;
}

template<typename Key, typename Value>
bool AVLTree<Key, Value>::isRightChild(AVLNode<Key, Value>* p, AVLNode<Key, Value>* n) 
{
    if (p == NULL) {
        return false;
    }
    return p->getRight() == n;
}

template<typename Key, typename Value>
void AVLTree<Key, Value>::updateHeight(AVLNode<Key, Value>* n) {
    if (n == NULL) {
        return;
    }
    AVLNode<Key, Value>* left = n->getLeft();
    AVLNode<Key, Value>* right = n->getRight();
    int leftHeight = left == NULL ? 0 : left->getHeight();
    int rightHeight = right == NULL ? 0 : right->getHeight();
    n->setHeight(std::max(leftHeight, rightHeight) + 1);
}

/*
 Rotates n down and to the left
*/
template<typename Key, typename Value>
void AVLTree<Key, Value>::rotateLeft(AVLNode<Key, Value>* n)
{
    if (n == NULL || n->getRight() == NULL) {
        return;
    }

    AVLNode<Key, Value>* parent = n->getParent();
    AVLNode<Key, Value>* rightChild = n->getRight();
    AVLNode<Key, Value>* rightChildLeft = rightChild->getLeft();

    rightChild->setLeft(n);
    n->setParent(rightChild);

    n->setRight(rightChildLeft);
    if (rightChildLeft != NULL)
    {
        rightChildLeft->setParent(n);
    }
    
    if (parent != NULL)
    {
        if (isLeftChild(parent, n))
        {
            parent->setLeft(rightChild);
        }
        else
        {
            parent->setRight(rightChild);
        }
    }
    else
    {
        this->root_ = rightChild;
    }
    rightChild->setParent(parent);
}


/**
* Rotates n down and to the right
*/
template<typename Key, typename Value>
void AVLTree<Key, Value>::rotateRight(AVLNode<Key, Value>* n)
{
    if (n == NULL || n->getLeft() == NULL) {
        return;
    }

    AVLNode<Key, Value>* parent = n->getParent();
    AVLNode<Key, Value>* leftChild = n->getLeft();
    AVLNode<Key, Value>* leftChildRight = leftChild->getRight();

    leftChild->setRight(n);
    n->setParent(leftChild);
    
    n->setLeft(leftChildRight);
    if (leftChildRight != NULL) {
        leftChildRight->setParent(n);
    }
    
    if (parent != NULL)
    {
        if (isRightChild(parent, n))
        {
            parent->setRight(leftChild);
        }
        else
        {
            parent->setLeft(leftChild);
        }
    }
    else
    {
        this->root_ = leftChild;
    }
    leftChild->setParent(parent);
}


template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int tempH = n1->getHeight();
    n1->setHeight(n2->getHeight());
    n2->setHeight(tempH);
}


#endif
