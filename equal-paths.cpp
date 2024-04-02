#ifndef RECCHECK
//if you want to add any #includes like <iostream> you must do them here (before the next endif)
#include <algorithm>

#endif

#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here
//helper function to find the maximum depth of the tree
int maxpathLength(Node * root, int maxHeight, int sum)
{
  if(root == nullptr)//base case
  {
      return sum;
  }
  if(root->left)//checking if a left node exists
  {
    maxHeight = max(maxHeight,maxpathLength(root->left,maxHeight,sum+1));//recursing by incrementing sum
  }
  if(root->right)//checking if a right node exists
  {
    maxHeight = max(maxHeight, maxpathLength(root->right,maxHeight,sum+1));//recursing by incrementing sum
  }
  if(!root->left&&!root->right)//checking if a leaf node is reached
  {
    maxHeight= max(maxHeight,sum);//updating max height
  }
 
  return maxHeight;
  

}
//helper function to find the mainimum depth of the tree
int minpathLength(Node * root, int minHeight, int sum)
{
  if(root == nullptr)//base case
  {
      return sum;
  }
  if(root->left)//checking if a left node exists
  {
    minHeight = min(minHeight,minpathLength(root->left,minHeight,sum+1));//recursing by incrementing sum
  }
  if(root->right)//checking if a right node exists
  {
    minHeight = min(minHeight, minpathLength(root->right,minHeight,sum+1));//recursing by incrementing sum
  }
  if(!root->left&&!root->right)//checking if a leaf node is reached
  {
    minHeight= min(minHeight,sum);//updating max height
  }
 
  return minHeight;
}
bool equalPaths(Node * root)
{
    // Add your code below
  if(root == nullptr)//checking if root node is null
  {
      return true;
  }
  int maxHeight = 0;
  int sum = 0;
  int minHeight =10000;
  int max = maxpathLength(root,maxHeight,sum);//calling maxpath length function
  int min = minpathLength(root, minHeight,sum);//calling minpath length function
  if(min==max)//checking if all paths in the tree are equal
  {
    return true;
  }
  else
  {
    return false;
  }
}

