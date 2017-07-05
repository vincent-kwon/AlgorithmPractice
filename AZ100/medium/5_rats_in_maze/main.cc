/*
 * =====================================================================================
 *
 *       Filename:  main.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017년 07월 05일 15시 41분 38초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hobum (Vincent) Kwon (mn), hobum.kwon@gmail.com
 *        Company:  Samsung Electornics
 *
 * 0 - 1 - 2
 * |  / \  |
 * 3      4
 * 
 * {0, 1, 0, 1, 0},
 * {1, 0, 1, 1, 1},
 * {0, 1, 0, 0, 1},
 * {1, 1, 0, 0, 1}, 
 * {0, 1, 1, 1, 0}
 *
 * {0, 1, 0, 1, 0},
 * {1, 0, 1, 1, 1},
 * {0, 1, 0, 0, 1},
 * {1, 1, 0, 0, 0},
 * {0, 1, 1, 0, 0}
 *
 * find Hamiltonian circle or path 
 * =====================================================================================
 */

#include <iostream>
#include <vector>
#include <utility>

#define MAX_NUM 4
using namespace std;

int array[MAX_NUM][MAX_NUM] = {
 { 1, 0, 0, 0 },
 { 1, 1, 0, 1 },
 { 0, 1, 0, 0 },
 { 1, 1, 1, 1 }, 
};

int visited[MAX_NUM][MAX_NUM] = { 
 {0, 0, 0, 0},
 {0, 0, 0, 0},
 {0, 0, 0, 0},
 {0, 0, 0, 0}
};


vector<pair<int, int>> path;

bool findPath(int row, int col) {
  if (row >= MAX_NUM || col >= MAX_NUM) return false;
  if (array[row][col] == 0) return false;
  if (row == MAX_NUM-1 && col == MAX_NUM-1) {
    path.push_back(make_pair(row, col));
    return true;
  }
  bool ret = false;

  ret = findPath(row, col+1);
  if (ret) {
    path.push_back(make_pair(row, col));
    return true;
  }
  else {
    ret = findPath(row+1, col);
    if (ret) {
      path.push_back(make_pair(row, col));
      return true;
    }
    return false;
  }
}

int main() {
  bool ret = findPath(0, 0);
  
  for (auto i : path) {
     cout << i.first << "," << i.second << endl;
  }
  return 0; 
}
