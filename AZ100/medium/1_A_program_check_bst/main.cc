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
  struct _Node *left;
  struct _Node *right;
} Node;

bool isBst(Node* node, int& min, int& max) {
  int rmin, rmax, lmin, lmax;
  bool lbst, rbst;

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
/*
 *       21
 *    4      35
 * 2    30 
 */
int main() {
  // recursively 
  //  A
  // B C => subtreeMax(left) max <= A && A subtreeMin(right) 
  //
  root = new Node();
  root->value = 21;
  root->left = new Node();
  root->right = new Node();

  Node* level2_left = root->left;
  level2_left->value = 4;

  Node* level2_right = root->right;  
  level2_right->value = 35;
  level2_right->left = level2_right->right = NULL;

  level2_left->left = new Node();
  level2_left->left->value = 2;
  level2_left->left->left = level2_left->left->right = NULL;

  level2_left->right = new Node();
  level2_left->right->value = 3;
  level2_left->right->left = level2_left->right->right = NULL;
 
  int m, n;

  if (isBst(root, m, n)) cout << "this is BST !!! " << endl;
  else cout << "No shit" << endl;
  return 0; 
}
