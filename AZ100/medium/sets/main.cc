/*
 * =====================================================================================
 *
 *       Filename:  main.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017년 07월 25일 16시 17분 41초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hobum (Vincent) Kwon (mn), hobum.kwon@gmail.com
 *        Company:  Samsung Electornics
 *
 * =====================================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int arrayA[5] = {1, 2, 5, 6, 8};

void getSubsetUtil(int start, int digitNum, int n, vector<int> newSet, vector<vector<int>>&answer) {
  if (digitNum == n) {
      answer.push_back(newSet);
  }
  else {
    for (int i = start ; i < 5 ; i++) { 
      newSet.push_back(arrayA[i]);
      getSubsetUtil(i+1, digitNum+1, n, newSet, answer);
      newSet.pop_back();
    }
  }
}

void getSubsets(int n, vector<vector<int>>& answers) {
  vector<int> newSet;
  getSubsetUtil(0,0, n,newSet,answers);
}
int main() {
  //cout << "each size: " << sizeof(arrayA)/sizeof(arrayA[0]) << endl;
  vector<vector<int>> answers;
  getSubsets(2, answers);
  for(vector<int>& v : answers) {
    for(int& i : v) { 
      cout << i << " ";
    };
    cout << "" << endl;
  };
  return 0;
}
