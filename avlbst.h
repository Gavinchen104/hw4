#ifndef RBBST_H
#define RBBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include "bst.h"

struct KeyError { };

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
    int8_t getBalance () const;
    void setBalance (int8_t balance);
    void updateBalance(int8_t diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int8_t balance_;    // effectively a signed char
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
    Node<Key, Value>(key, value, parent), balance_(0)
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
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff)
{
    balance_ += diff;
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
    void leftrotate(AVLNode<Key,Value>* n);
    void rightrotate(AVLNode<Key,Value>* n);
    void insert_fix(AVLNode<Key,Value>* n, AVLNode<Key,Value>* p);
    void remove_fix(AVLNode<Key,Value>* n, int diff);


    


};

/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */

template<class Key, class Value>
void AVLTree<Key, Value>::leftrotate(AVLNode<Key,Value>* n){
    AVLNode<Key,Value>* n_r = n->getRight();

    AVLNode<Key,Value>* n_r_l = n_r->getLeft();

    AVLNode<Key,Value>* n_p = n->getParent();
		n_r->setParent(n_p);
		//if n does not have a parent
    if(n_p==NULL) this->root_ = n_r;

    //if n is the left child 
    else if(n_p->getLeft() == n){
        n_p->setLeft(n_r);
    }
    
    //if n is the right child
    else if(n_p->getRight() == n){
        n_p->setRight(n_r);
    }

    n->setParent(n_r);

    n->setRight(n_r_l);

    n_r->setLeft(n);

    if(n_r_l != NULL) n_r_l->setParent(n);
    
   
}

template<class Key, class Value>
void AVLTree<Key, Value>::rightrotate(AVLNode<Key,Value>* n){
    AVLNode<Key,Value>* n_l = n->getLeft();

    AVLNode<Key,Value>* n_l_r = n_l->getRight();

    AVLNode<Key,Value>* n_p = n->getParent();
		n_l->setParent(n_p);
		//if n does not have a parent
    if(n_p==NULL) this->root_ = n_l;		

		
    //if n is the left child 
    else if(n_p->getLeft() == n){
        n_p->setLeft(n_l);
    }
    
    //if n is the right child
    else if(n_p->getRight() == n){
        n_p->setRight(n_l);
    }

    n->setParent(n_l);

    n->setLeft(n_l_r);

    n_l->setRight(n);

    if(n_l_r != NULL) n_l_r->setParent(n);	

    
}
template<class Key, class Value> 
void AVLTree<Key, Value>::insert_fix(AVLNode<Key,Value>* n, AVLNode<Key,Value>* p){
    //base case
    if(p == NULL || p->getParent() == NULL)  return;
    AVLNode<Key,Value>* g = p->getParent();

    //if p is the left child 
    if(g->getLeft() == p){
        g->updateBalance(-1);

        //case 1
        if(g->getBalance() == 0) return;

        //case 2
        else if(g->getBalance()==-1){
            insert_fix(p,g);
        }

        //case 3
        else if(g->getBalance()==-2){
            //zig zig
            if(n == p->getLeft()){							
              rightrotate(g);
              p->setBalance(0);
              g->setBalance(0);
            }
            //zig zag
            else if(n == p->getRight()){
              leftrotate(p);
              rightrotate(g);
              //case A
              if(n->getBalance() == -1){
                  p->setBalance(0);
                  g->setBalance(1);
							}

                //case B
              else if(n->getBalance() ==0){
									p->setBalance(0);
									g->setBalance(0);
							}

                //case C 
              else if(n->getBalance()==1){
									p->setBalance(-1);
									g->setBalance(0);
							}
              n->setBalance(0);
            }
						return;
        }
    }

    //if p is the right child
    else if(g->getRight()==p){
        g->updateBalance(1);

        //case 1
        if(g->getBalance() == 0) return;

        //case 2
        else if(g->getBalance()==1){	
            insert_fix(p,g);
        }

        //case 3
        else if(g->getBalance()==2){
            //zig zig
            if(n == p->getRight()){
                leftrotate(g);
                p->setBalance(0);
                g->setBalance(0);
            }
            //zig zag
            else if(n == p->getLeft()){
                rightrotate(p);
                leftrotate(g);
                //case A
                if(n->getBalance() == 1){
                    p->setBalance(0);
                    g->setBalance(-1);
                }

                //case B
                else if(n->getBalance() ==0){
                    p->setBalance(0);
                    g->setBalance(0);
                }

                //case C 
                else if(n->getBalance()==-1){
                    p->setBalance(1);
                    g->setBalance(0);
                }
                n->setBalance(0);
            }
						return;
        }
    }
}



template<class Key, class Value> 
void AVLTree<Key, Value>::remove_fix(AVLNode<Key,Value>* n, int diff){
	
	//base case
	if(n == NULL) return;
	AVLNode<Key,Value>* p = n->getParent();
	int ndiff = -1;
	if(p!=NULL && n==p->getLeft()) ndiff = 1;
	
	//if diff = -1
	if(diff == -1){
		//case 1
		if(n->getBalance() + diff == -2){
			AVLNode<Key,Value>* c = n->getLeft();
			//case 1a
			if(c->getBalance()==-1){
				rightrotate(n);
				n->setBalance(0);
				c->setBalance(0);
				remove_fix(p, ndiff);
			}
			//case 1b
			else if(c->getBalance() == 0){
				rightrotate(n);
				n->setBalance(-1);
				c->setBalance(1);
				return;
			}
			else if(c->getBalance() == 1){
				AVLNode<Key,Value>* g = c->getRight();
				leftrotate(c);
				rightrotate(n);
				if(g->getBalance()==1){
					n->setBalance(0);
					c->setBalance(-1);
				}
				else if(g->getBalance()==0){
					n->setBalance(0);
					c->setBalance(0);
				}
				else if(g->getBalance()==-1){
					n->setBalance(1);
					c->setBalance(0);
				}
				g->setBalance(0);
				remove_fix(p,ndiff);
			}
		}
		//case 2
		else if (n->getBalance()+ diff == -1){
			n->setBalance(-1);
			return;
		}
		else if(n->getBalance()+ diff ==0){
				n->setBalance(0);
				remove_fix(p, ndiff);
		}
	}
	else if(diff ==1){
		//case 1
		if(n->getBalance() + diff == 2){
			AVLNode<Key,Value>* c = n->getRight();
			//case 1a
			if(c->getBalance()==1){
				leftrotate(n);
				n->setBalance(0);
				c->setBalance(0);
				remove_fix(p, ndiff);
			}
			//case 1b
			else if(c->getBalance() == 0){
				leftrotate(n);
				n->setBalance(1);
				c->setBalance(-1);
				return;
			}
			else if(c->getBalance() == -1){
				AVLNode<Key,Value>* g = c->getLeft();
				rightrotate(c);
				leftrotate(n);

				if(g->getBalance()==-1){
					n->setBalance(0);
					c->setBalance(1);
				}
				else if(g->getBalance()==0){
					n->setBalance(0);
					c->setBalance(0);
				}
				else if(g->getBalance()==1){
					n->setBalance(-1);
					c->setBalance(0);
				}
				g->setBalance(0);
				remove_fix(p,ndiff);
			}
		}
		//case 2
		else if (n->getBalance()+ diff == 1){
			n->setBalance(1);
			return;
		}
		else if(n->getBalance()+ diff ==0){
			n->setBalance(0);
			remove_fix(p, ndiff);
		}
	}
}



template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
    // TODO
    // AVLNode<Key, Value>* avl_root = static_cast<AVLNode<Key,Value>*>(this->root_);
    //if root is NULL. no need to fix
		if(this->root_ == NULL){
			AVLNode<Key, Value>* new_root = new AVLNode<Key, Value>(new_item.first, new_item.second, NULL);
			new_root->setBalance(0);
			new_root->setLeft(NULL);
			new_root->setRight(NULL);
			this->root_ = new_root;
			return;
		}

		//if the key is in the tree. no need to fix
		else if(this->internalFind(new_item.first) != NULL){
			this->internalFind(new_item.first)->setValue(new_item.second);
			return;
		}

		//if the key is not in the tree
		else if(this->internalFind(new_item.first) == NULL){
			AVLNode<Key, Value>* avl_root = static_cast<AVLNode<Key,Value>*>(this->root_);
			while(avl_root!=NULL){
				//if the value is smaller than root_
				if(avl_root->getKey() > new_item.first){
					AVLNode<Key, Value>* temp = new AVLNode<Key, Value>(new_item.first, new_item.second, avl_root);
					//if the left leaf is not empty
					if(avl_root->getLeft()!=NULL){
						avl_root = avl_root->getLeft();					
					}
					//if the left leaf is empty
					else{
						avl_root->setLeft(temp);
						temp->setParent(avl_root);
						temp->setBalance(0);
						//balance is 1 or -1
						if(avl_root->getBalance()==1||avl_root->getBalance()==-1){
							avl_root->setBalance(0);
						}
						//balance is 0
						else if(avl_root->getBalance()==0){
							avl_root->updateBalance(-1);
							insert_fix(temp, avl_root);
						}
						return;
					}
				}
				//if the value is bigger than root_
				else if (avl_root->getKey()< new_item.first){
					AVLNode<Key, Value>* temp = new AVLNode<Key, Value>(new_item.first, new_item.second, avl_root);
					// the right leaf is not empty
					if(avl_root->getRight()!=NULL){
						avl_root = avl_root->getRight();
					}
					//the right leaf is empty
					else{
						avl_root->setRight(temp);
						temp->setParent(avl_root);				
						temp->setBalance(0);
						//balance is 1 or -1
						if(avl_root->getBalance()==1||avl_root->getBalance()==-1){
							avl_root->setBalance(0);
						}
						//balance is 0
						else if(avl_root->getBalance()==0){
							avl_root->updateBalance(1);
							insert_fix(temp, temp->getParent());
						}
						return;
					}
				}
			}
		}
}

/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::remove(const Key& key)
{
		AVLNode<Key, Value>* temp = static_cast<AVLNode<Key,Value>*>(this->internalFind(key));
		//if not found
    if(temp == NULL) return;// the value is not in the BST
    if (temp->getLeft() != NULL && temp->getRight() != NULL) {
      AVLNode<Key, Value>* pred_temp = static_cast<AVLNode<Key,Value>*>(this->predecessor(temp));
			nodeSwap(temp, pred_temp);
    }
		//now there is only one child or no child under temp
		//no need to consider 0 child case except for setting the new parent of child

		//determine the child of temp
    AVLNode<Key, Value> *temp_child = temp->getLeft();
    if(temp->getRight()!= NULL) {
      temp_child = temp->getRight();
    }

		//set the pointers for the child 
    AVLNode<Key, Value>* parent = temp->getParent();
    if(temp_child != NULL){
      temp_child->setParent(parent);
    }

    int diff;
		//if temp is the root
    if(parent == NULL) this->root_ = temp_child;

		//if not the root
    else{
			// temp is the left child
			if(temp == parent->getLeft()) {
				parent->setLeft(temp_child);
				diff = 1;
			} 
			//temp is the right child
			else{
				parent->setRight(temp_child);
				diff = -1;
			}
    }

    delete temp;
    remove_fix(parent, diff);
}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}


#endif
