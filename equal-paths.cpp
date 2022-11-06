#include "equal-paths.h"
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <cmath>
using namespace std;



//helper function
bool equalPaths_(Node* root, int height, int height_){
    //base case for this recursion
    if(root == NULL) return true;

    //when a leaf node
    if(root->left == NULL && root->right == NULL){
        //when the first leaf node
        if(height_ == 0){
            height_ = height;
            return true;
        }
        //when not the first node, compare it with the first node
        return height == height_;
    }
    //recursion
    return equalPaths_(root->left, height+1, height_) &&
           equalPaths_(root->right, height+1, height_);
}

bool equalPaths(Node * root)
{
    int height = 0;
    int height_ = 0;
    return equalPaths_(root, height, height_);

}

