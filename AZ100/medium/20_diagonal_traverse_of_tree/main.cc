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

// revisit
#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

typedef struct _Node {
  int value;
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
/*
 *         21
 *    4         35
 * 2    8   23
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

  Node* oneMore = new Node();
  oneMore->value = 23;
  level2_right->left = oneMore;


  level2_left->left = new Node();
  level2_left->left->value = 2;
  level2_left->left->left = level2_left->left->right = NULL;

  level2_left->right = new Node();
  level2_left->right->value = 8;
  level2_left->right->left = level2_left->right->right = NULL;

  // while visiting, if left existing, adding queue of next level visit
  // two queue
  // when visit to right, adding left to next queue;
  // now from next queue, 
  queue<Node*>* q = new queue<Node*>[2];
 
  Node* tmp = root;
  while (tmp != NULL) {
    q[0].push(tmp);
    tmp = tmp->right;
  }

  int current = 0;
  while (!q[0].empty() || !q[1].empty()) {
    int alternative = (current == 0) ? 1 : 0;
    while (!q[current].empty()) {
      Node* nextNode = q[current].front(); 
      cout << nextNode->value << endl;
      q[current].pop();
      if (nextNode->left != NULL) {
        Node* tt = nextNode->left;
        while (tt) {
          q[alternative].push(tt);
          tt = tt->right;
        }
      }
    }
    current = alternative;
  }

  return 0; 
}
