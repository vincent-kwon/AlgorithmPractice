/*
 * =====================================================================================
 *
 *       Filename:  main.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017년 07월 17일 23시 44분 46초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hobum (Vincent) Kwon (mn), hobum.kwon@gmail.com
 *        Company:  Samsung Electornics
 *
 * =====================================================================================
 */

// memo: good to practice
//
#include <iostream>

using namespace std;

typedef struct _Node {
  int value;
  struct _Node *left;
  struct _Node *right;
} Node;

int gMax = -987654321;

Node* insert(Node* root, int value, bool leftChild) {
  if (root == NULL) {
    root = new Node;
    root->left = NULL;
    root->right = NULL;
    root->value = value;
    return root;
  }
  if (leftChild) {
    root->left = new Node;
    root->left->left = root->left->right = NULL;
    root->left->value = value;
    return root->left;
  }
  else {
    root->right= new Node;
    root->right->left = root->right->right = NULL;
    root->right->value = value; 
    return root->right;
  }
} 

int getMaxMinSubTree(Node* tmp, int& min, int& max) {
  int minL; int maxL;
  int minR; int maxR;

  if (tmp == NULL) return 0;

  int ans1, ans2; 
  int ret = 0;

  if (tmp->left != NULL) {
    ans1 = getMaxMinSubTree(tmp->left, minL, maxL);
 
    if (ans1 == -1 || (!(maxL <= tmp->value))) {
      ret = -1;
    }
    //else cout << tmp->value << "'s left return " << ans1 << "," << minL << "," << maxL <<  endl;
  }
  else {
    ans1 = 0;  
  }

  if (tmp->right != NULL) {
    ans2 = getMaxMinSubTree(tmp->right, minR, maxR);

    if (ans2 == -1 || (!(minR > tmp->value))) {
      ret = -1;
    }
    //else cout << tmp->value << "'s right return " << ans2 << "," << minR << "," << maxR <<  endl;
  }
  else {
    ans2 = 0;
  }

  if (ret == -1) return -1;

  if (ans1 == 0 && ans2 == 0) {
    min = max = tmp->value;
    return 1;
  } 
  else if (ans1 == 0) { 
    min = tmp->value;
    max = maxR;
    ret = 1 + ans2;
  }
  else if (ans2 == 0) {
    min = minL;
    max = tmp->value;
    ret = 1 + ans1;
  }
  else {
    min = minL;
    max = maxR;
    // cout << tmp->value << "ans 1 " << ans1 << ", ans2 " << ans2 << endl;
    // cout << tmp->value << " return should : " << ans1 + ans2 + 1 << endl;
    ret =  ans1 + ans2 + 1;
  }

  if (ret > gMax) gMax = ret;
  return ret;
}

int findBiggestBst(Node* root) {
  int ret = 0; 
  int min; 
  int max;
  if (root == NULL) return 0;
  else return getMaxMinSubTree(root, min, max);
}

int main() {
  Node *root = NULL; Node *tmp;
  root = insert(root, 50, true);
  tmp = insert(root, 30, true);
  insert(tmp, 5, true);
  insert(tmp, 20, false);

  tmp = insert(root, 60, false);  
  insert(tmp, 45, true);
  tmp = insert(tmp, 70, false);
  insert(tmp, 65, true);
  insert(tmp, 80, false);

  int i = findBiggestBst(root);
  cout << "ret: " << i << ", gMax: " << gMax << endl;
  return 0;
}
