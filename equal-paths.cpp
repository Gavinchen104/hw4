#include "equal-paths.h"
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <cmath>
using namespace std;



//helper function

int maxheight(Node* root) {
	// Base case: an empty tree is always balanced and has a height of 0
	if (root == nullptr) return 0;
	if (root->left == NULL && root->right == NULL) return 0;
	int l,r;
	l = maxheight(root->left);
	r = maxheight(root->right);
	return std::max(l,r)+1;

}

int minheight(Node* root) {
	if (root == NULL) return 0;
  if (root->left == NULL && root->right == NULL) return 0;
   
  int l=0,r=0;
  if (root->left){
    l = minheight(root->left);
	}
  if (root->right){
    r = minheight(root->right);
	}
  return min(l,r)+1;
}

bool equalPaths(Node * root)
{
    if(minheight(root) == maxheight(root)) return true;
    return false;
}

