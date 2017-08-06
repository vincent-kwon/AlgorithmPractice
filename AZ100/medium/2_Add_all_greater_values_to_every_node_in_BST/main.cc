/*
 * =====================================================================================
 *
 *       Filename:  main.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017년 07월 05일 05시 06분 50초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hobum (Vincent) Kwon (mn), hobum.kwon@gmail.com
 *        Company:  Samsung Electornics
 *
 * =====================================================================================
 */

#include <iostream>

using namespace std;

typedef struct _Node {
  int value;
  int sum;
  struct _Node *left;
  struct _Node *right;
} Node;

bool isBst(Node* node, int& min, int& max) {
  int rmin, rmax, lmin, lmax;
  bool lbst, rbst;

  if (node == NULL) return false;

  max = min = node->value;

  if (node->left != NULL) {
    lbst = isBst(node->left, lmin, lmax);
    if (lbst == false) return false;
    if (node->value < lmax) return false;
    min = lmin;
  }

  if (node->right != NULL) {
    rbst = isBst(node->right, rmin, rmax);
    if (rbst == false) return false;
    if (node->value > rmin) return false;
    max = rmax;
  }
  return true;
}
Node* root;

int lastVisitSum = 0; // memo: this is Money Ball. Keeping track of values

void reverseInorderTraverse(Node* node) { // return sum value of next big
  if (node == NULL) return;
  
  // sum = lower bigger + upper bigger
  reverseInorderTraverse(node->right);
  lastVisitSum = node->value + lastVisitSum;
  cout << "visit: " << lastVisitSum << endl;
  //node->sum = lastVisitSum;
  reverseInorderTraverse(node->left);
}
/* when going right, value to get is next close node's sum
 * when going left,  
 *
 *
 *        50
 *    30      70
 *  20   40  
 * 
 *  should be modified to 
 *
 *       120
 *    190    70     
 * 210   160
 */

int main() {
  // recursively 
  //  A
  // B C => subtreeMax(left) max <= A && A subtreeMin(right) 
  //
  root = new Node();
  root->value = 50;
  root->left = new Node();
  root->right = new Node();

  Node* level2_left = root->left;
  level2_left->value = 30;

  Node* level2_right = root->right;  
  level2_right->value = 70;
  level2_right->left = level2_right->right = NULL;

  level2_left->left = new Node();
  level2_left->left->value = 20;
  level2_left->left->left = level2_left->left->right = NULL;

  level2_left->right = new Node();
  level2_left->right->value = 40;
  level2_left->right->left = level2_left->right->right = NULL;
 
  cout << "reverse inorder " << endl;
  reverseInorderTraverse(root);
  return 0; 
}
