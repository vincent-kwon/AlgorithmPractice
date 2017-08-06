/*
 * =====================================================================================
 *
 *       Filename:  floy.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016년 11월 11일 07시 05분 09초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hobum (Vincent) Kwon (mn), hobum.kwon@gmail.com
 *        Company:  Samsung Electornics
 *
 * =====================================================================================
 */

#include <iostream>

#define VC_MAX 4
#define INF 987544321
using namespace std;

int m[VC_MAX][VC_MAX] = { // last_visit: map vector, previous vector 
  {0,  3,  6, 15},
  {INF, 0, -2, INF},
  {INF, INF, 0, 2},
  {1,  INF, INF, 0},
};

int p[VC_MAX][VC_MAX] = {
  {-1, 0, 0, 0},
  {-1, -1, 1, -1},
  {-1, -1, -1, 2},
  {3, -1, -1, -1}, 
};

void printArray() {
  for (int i = 0; i < VC_MAX; i++) {
    for (int j = 0; j < VC_MAX; j++) {
      cout << i << "," << j << ":" << m[i][j] << endl;
    }
  }
}

void printPath() {
  for (int i = 0; i < VC_MAX; i++) {
    for (int j = 0; j < VC_MAX; j++) {
      cout << i << "," << j << ":" << p[i][j] << endl;
    }
  }
}
void getFloyWarshall() {

  for (int k = 0; k < VC_MAX; k++)
    for (int i = 0; i < VC_MAX; i++) 
      for (int j = 0; j < VC_MAX; j++) {
        cout << i << "," << j << "," << k << ":" << m[i][j] << "," << m[i][k] << "," << m[k][j] << endl;
        if (m[i][k] == INF || m[k][j] == INF) continue;
        if (m[i][j] > (m[i][k] + m[k][j])) { // last_visit: if small, update
          m[i][j] = m[i][k] + m[k][j]; // last_visit: update directly
          p[i][j] = p[k][j];           // update path to indicate what is last visit
          cout << "   swap " << endl;
        }
      }
}

int main() {
  getFloyWarshall();
  printArray();
  cout << "print path: " << endl;
  printPath();
  return 0;
}
