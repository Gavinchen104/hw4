#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>
#include <cmath>

/**
 * A templated class for a Node in a search tree.
 * The getters for parent/left/right are virtual so
 * that they can be overridden for future kinds of
 * search trees, such as Red Black trees, Splay trees,
 * and AVL trees.
 */
template <typename Key, typename Value>
class Node
{
public:
    Node(const Key& key, const Value& value, Node<Key, Value>* parent);
    virtual ~Node();

    const std::pair<const Key, Value>& getItem() const;
    std::pair<const Key, Value>& getItem();
    const Key& getKey() const;
    const Value& getValue() const;
    Value& getValue();

    virtual Node<Key, Value>* getParent() const;
    virtual Node<Key, Value>* getLeft() const;
    virtual Node<Key, Value>* getRight() const;

    void setParent(Node<Key, Value>* parent);
    void setLeft(Node<Key, Value>* left);
    void setRight(Node<Key, Value>* right);
    void setValue(const Value &value);

protected:
    std::pair<const Key, Value> item_;
    Node<Key, Value>* parent_;
    Node<Key, Value>* left_;
    Node<Key, Value>* right_;
};

/*
  -----------------------------------------
  Begin implementations for the Node class.
  -----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent) :
    item_(key, value),
    parent_(parent),
    left_(NULL),
    right_(NULL)
{

}

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed by the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node()
{

}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<const Key, Value>& Node<Key, Value>::getItem() const
{
    return item_;
}

/**
* A non-const getter for the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& Node<Key, Value>::getItem()
{
    return item_;
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const
{
    return item_.first;
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const
{
    return item_.second;
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
    return item_.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const
{
    return parent_;
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const
{
    return left_;
}

/**
* An implementation of the virtual function for retreiving the right child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const
{
    return right_;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent)
{
    parent_ = parent;
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left)
{
    left_ = left;
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right)
{
    right_ = right;
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value)
{
    item_.second = value;
}

/*
  ---------------------------------------
  End implementations for the Node class.
  ---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree
{
public:
    BinarySearchTree(); //TODO
    virtual ~BinarySearchTree(); //TODO
    virtual void insert(const std::pair<const Key, Value>& keyValuePair); //TODO  yes 
    virtual void remove(const Key& key); //TODO
    void clear(); //TODO
    bool isBalanced() const; //TODO. yes 
    void print() const;
    bool empty() const;

    template<typename PPKey, typename PPValue>
    friend void prettyPrintBST(BinarySearchTree<PPKey, PPValue> & tree);
public:
    /**
    * An internal iterator class for traversing the contents of the BST.
    */
    class iterator  // TODO
    {
    public:
        iterator();

        std::pair<const Key,Value>& operator*() const;
        std::pair<const Key,Value>* operator->() const;

        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;

        iterator& operator++();

    protected:
        friend class BinarySearchTree<Key, Value>;
        iterator(Node<Key,Value>* ptr);
        Node<Key, Value> *current_;
    };

public:
    iterator begin() const;
    iterator end() const;
    iterator find(const Key& key) const;
    Value& operator[](const Key& key);
    Value const & operator[](const Key& key) const;

protected:
    // Mandatory helper functions
    Node<Key, Value>* internalFind(const Key& k) const; // TODO. yes
    Node<Key, Value> *getSmallestNode() const;  // TODO. yes
    static Node<Key, Value>* predecessor(Node<Key, Value>* current); // TODO  yes 
    // Note:  static means these functions don't have a "this" pointer
    //        and instead just use the input argument.

    // Provided helper functions
    virtual void printRoot (Node<Key, Value> *r) const;
    virtual void nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2) ;

    // Add helper functions here
		static Node<Key, Value>* successor(Node<Key, Value>* current); // TODO yes
    void delete_(Node<Key, Value>* root_);
    int calculateHeightIfBalanced(Node<Key, Value>* root_) const; 
		

protected:
    Node<Key, Value>* root_;
    // You should not need other data members
};

/*
--------------------------------------------------------------
Begin implementations for the BinarySearchTree::iterator class.
---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value> *ptr)
{
    // TODO
    current_ = ptr;
}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator() 
{
    // TODO
    current_ = NULL;

}

/**
* Provides access to the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> &
BinarySearchTree<Key, Value>::iterator::operator*() const
{
    return current_->getItem();
}

/**
* Provides access to the address of the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> *
BinarySearchTree<Key, Value>::iterator::operator->() const
{
    return &(current_->getItem());
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator==(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
    return current_ == rhs.current_;
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator!=(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
    return current_ != rhs.current_;

}


/**
* Advances the iterator's location using an in-order sequencing
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator&
BinarySearchTree<Key, Value>::iterator::operator++()
{
    // TODO
    current_ = successor(current_);
    return *this;

}

template<typename Key, typename Value> 
Node<Key, Value>* 
BinarySearchTree<Key, Value>::successor(Node<Key, Value>* current){
		//base case 
		if(current == NULL) return nullptr;
		Node<Key, Value>* rightchild = current->getRight();
		//if a right child exists
		if(rightchild != NULL){
			while(rightchild->getLeft()!= NULL){
				rightchild = rightchild->getLeft();
        if(!rightchild) break;
			}
			return rightchild;
		}
		//if a right child does not exist
		else{
      Node<Key, Value>* temp = current;
			Node<Key, Value>* parent = current->getParent();
			while(parent!=NULL && temp ==parent->getRight()){
				temp = parent;
				parent = parent->getParent() ;
			}
			return parent;

		}
}


/*
-------------------------------------------------------------
End implementations for the BinarySearchTree::iterator class.
-------------------------------------------------------------
*/

/*
-----------------------------------------------------
Begin implementations for the BinarySearchTree class.
-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::BinarySearchTree() 
{
    // TODO
		root_= NULL;
		
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
    // TODO
		clear();
}

/**
 * Returns true if tree is empty
*/
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::empty() const
{
    return root_ == NULL;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{
    printRoot(root_);
    std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::begin() const
{
    BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
    return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::end() const
{
    BinarySearchTree<Key, Value>::iterator end(NULL);
    return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::find(const Key & k) const
{
    Node<Key, Value> *curr = internalFind(k);
    BinarySearchTree<Key, Value>::iterator it(curr);
    return it;
}

/**
 * @precondition The key exists in the map
 * Returns the value associated with the key
 */
template<class Key, class Value>
Value& BinarySearchTree<Key, Value>::operator[](const Key& key)
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}
template<class Key, class Value>
Value const & BinarySearchTree<Key, Value>::operator[](const Key& key) const
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}

/**
* An insert method to insert into a Binary Search Tree.
* The tree will not remain balanced when inserting.
* Recall: If key is already in the tree, you should 
* overwrite the current value with the updated value.
*/
template<class Key, class Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value> &keyValuePair)
{
    // TODO
		//if root is NULL
		if(root_ == NULL){
			Node<Key, Value>* new_root_ = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, NULL);
			root_ = new_root_;
			// this->print();
			return;
		}
		//if the key is in the tree
		else if(internalFind(keyValuePair.first) != NULL){
			internalFind(keyValuePair.first)->setValue(keyValuePair.second);
			// this->print();
			return;
		}

		//if the key is not in the tree
		
		else{
			Node<Key, Value>* temp_root = root_;
			while(temp_root!=NULL){
				//if the value is smaller than root_
				if(temp_root->getKey()> keyValuePair.first){
					Node<Key, Value>* temp = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, temp_root);
					
					if(temp_root->getLeft()!=NULL){
						temp_root = temp_root->getLeft();
					}
					else{
						temp_root->setLeft(temp);
						temp->setParent(temp_root);	
						return;
					}

				}
				//if the value is bigger than root_
				else if (temp_root->getKey()< keyValuePair.first){
					Node<Key, Value>* temp = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, temp_root);
					
					if(temp_root->getRight()!=NULL){
						temp_root = temp_root->getRight();
					}
					else{
						temp_root->setRight(temp);
						temp->setParent(temp_root);				
						return;
					}
				}
			}
		}
		

}

/**
* A remove method to remove a specific key from a Binary Search Tree.
* Recall: The writeup specifies that if a node has 2 children you
* should swap with the predecessor and then remove.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{
    // TODO

		//search for the key
		Node<Key, Value>* temp1 = internalFind(key);

		//if it is not on the tree ignore
		if(temp1 == NULL) return;

		//if it is on the tree
		else{

			//0 child case: delete the node and null the pointers
			if(temp1->getLeft()==NULL && temp1->getRight()==NULL){
				//if temp1 is the root
				if(temp1 == root_){
					delete temp1;
					root_ = NULL;
					return;
				}
				//if temp1 is the leftchild of its parent
				else if(temp1->getParent()->getLeft() ==temp1){
					temp1->getParent()->setLeft(NULL);
				}
				//if temp1 is the rightchild of its parent
				else if(temp1->getParent()->getRight() ==temp1){
					temp1->getParent()->setRight(NULL);
				}
			}



			//2 child case : swap with the predecessor then do the either the case above
			else if(temp1->getLeft()!=NULL && temp1->getRight()!=NULL){
				//swap 
				nodeSwap(temp1, predecessor(temp1));

				// after swap temp1 has 0 children
				if(temp1->getLeft()==NULL && temp1->getRight()==NULL){
					//temp1 is on the left of its parent
					if(temp1->getParent()->getLeft() == temp1){
						temp1->getParent()->setLeft(NULL);
					}
					//temp1 is on the right of its parent
					else if(temp1->getParent()->getRight() == temp1){
						temp1->getParent()->setRight(NULL);						
					}
				}


				//after swap temp1 has 1 child. (the child has to be on the left of temp1)
				else{
					//temp1 is on the left of its parent
					if(temp1->getParent()->getLeft() == temp1){
						temp1->getParent()->setLeft(temp1->getLeft());
					}
					//temp1 is on the right of its parent
					else if(temp1->getParent()->getRight() == temp1){
						temp1->getParent()->setRight(temp1->getLeft());
					}
						temp1->getLeft()->setParent(temp1->getParent());						
					}					
				}
			
			


			//1 child case : promote not the same as swap
			else{
				//if leftchild exists  
				if(temp1->getLeft()!=NULL){
					//if temp is the root
					if(temp1 == root_){
						temp1->getLeft()->setParent(NULL);
						root_= temp1->getLeft();

					}
					else{
						// temp is the leftchild of its parent
						if(temp1->getParent()->getLeft() == temp1){
							temp1->getParent()->setLeft(temp1->getLeft());
						}
						// temp is the rightchild of its parent
						else{
							temp1->getParent()->setRight(temp1->getLeft());
						}
        		temp1->getLeft()->setParent(temp1->getParent());
					}
				}

				//if rightchild exists
				else if(temp1->getRight()!=NULL){
					//if temp is the root
					if(temp1 == root_){
						temp1->getRight()->setParent(NULL);
						root_= temp1->getRight();
					}
					else{
						// temp is the leftchild of its parent
						if(temp1->getParent()->getLeft() == temp1){
							temp1->getParent()->setLeft(temp1->getRight());
						}
						// temp is the rightchild of its parent
						else{
							temp1->getParent()->setRight(temp1->getRight());
						}
          	temp1->getRight()->setParent(temp1->getParent());
					}
				}
			}
		}
		temp1 = NULL;
		delete temp1;
		return;
		
}


template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::predecessor(Node<Key, Value>* current)
{
    // TODO

		//base case
		if(current == NULL) return NULL;

		Node<Key, Value>* leftchild = current->getLeft();
		//if a left child exists
		if(leftchild != NULL){
			while(leftchild->getRight()!= NULL){
				leftchild = leftchild->getRight();
        if(!leftchild) break;
			}
			return leftchild;
		}
		//if a left child does not exist
		else{
			Node<Key, Value>*  temp = current;
      Node<Key, Value>*  parent = current->getParent();
			while(parent!= NULL && temp == parent->getLeft()){
				temp = parent;
				parent = parent->getParent();
			}
			return parent;
		}
}




/**
* A method to remove all contents of the tree and
* reset the values in the tree for use again.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
    // TODO
		
		delete_(root_);
		root_ = NULL;
		// delete root_;
		return;

		// Node<Key, Value>* temp = getSmallestNode();
		// while(temp){
		// 	Node<Key, Value>* temp_next = successor(temp);
		// 	remove(temp->getKey());
		// 	temp = temp_next;
		// }
		// root_ = nullptr;
		// return;
}




//helper function for clear()
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::delete_(Node<Key, Value>* root_){
	if(root_ == NULL) return;
	delete_(root_->getLeft());
	delete_(root_->getRight());
	delete root_;
	// remove(root_->getKey());
	return;
}

/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::getSmallestNode() const
{
		
    // TODO
		
		if(root_ == NULL) return NULL;
		Node<Key, Value>* temp = root_;
		while(temp->getLeft()!=NULL){
			temp = temp->getLeft();
		}
		return temp;
}

/**
* Helper function to find a node with given key, k and
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{
    // TODO
		if(root_==NULL) return NULL;
		Node<Key, Value>* temp = root_;
		while(temp!=NULL ){
			if(temp->getKey() == key ){return temp;}
			else if (temp->getKey() > key ) {temp = temp->getLeft();}
			else{temp = temp->getRight();}
		}
		return NULL;
}

/**
 * Return true iff the BST is balanced.
 */
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() const
{
    // TODO
	if(calculateHeightIfBalanced(root_)<0) return false;
	else{return true;}
}

template<typename Key, typename Value>
int BinarySearchTree<Key, Value>::calculateHeightIfBalanced(Node<Key, Value>* root_) const{
	// Base case: an empty tree is always balanced and has a height of 0
	if (root_ == nullptr) return 0;
	int l = calculateHeightIfBalanced(root_->getLeft());
	if(l==-1) return -1;
	int r = calculateHeightIfBalanced(root_->getRight());
	if(r == -1) return -1;
	if(abs(l-r)>1) return -1;
	return std::max(l,r)+1;

	
}



template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2)
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


    if(this->root_ == n1) {
        this->root_ = n2;
    }
    else if(this->root_ == n2) {
        this->root_ = n1;
    }

}

/**
 * Lastly, we are providing you with a print function,
   BinarySearchTree::printRoot().
   Just call it with a node to start printing at, e.g:
   this->printRoot(this->root_) // or any other node pointer

   It will print up to 5 levels of the tree rooted at the passed node,
   in ASCII graphics format.
   We hope it will make debugging easier!
  */

// include print function (in its own file because it's fairly long)
#include "print_bst.h"

/*
---------------------------------------------------
End implementations for the BinarySearchTree class.
---------------------------------------------------
*/

#endif
