/*
 * =====================================================================================
 *
 *       Filename:  bellford.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016년 11월 11일 08시 41분 23초
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

#define NODE_NUM 4
#define INF 987654321

#if 0
int m[NODE_NUM][NODE_NUM] = {
 // 0, 1,  2, 3, 4, 5
  { 0, 4,  5, 8, 0 },
  { 0, 0, -3, 0, 0 },
  { 0, 0,  0, 0, 4 }, 
  { 0, 0,  0, 0, 2 },
  { 0, 0,  0, 1, 0 },
};

     1        -2   
  0 ---> 1 <-------
  |      ^        | 
  |      |-7      |
   ----> 2------->3
     3       -6

  0 = 0 
  1 = -5
  2 = 3
  3 = -3
  
#endif

int m[NODE_NUM][NODE_NUM] = {
  { 0,  1, 3,  0 },
  { 0,  0, 0,  0 },
  { 0, -7, 0, -6 }, 
  { 0, -2, 0,  0 } 
};

int dt[NODE_NUM] = {0, INF, INF, INF}; // last_visit

// TODO: negative cycle
//
int main() {
  for (int node = 0; node < NODE_NUM-1; node++) // last_visit: order can be an issue but number of edge try will eventually get to this point
    for (int i = 0; i < NODE_NUM; i++) {
      for (int j = 0; j < NODE_NUM; j++) {
        cout << i << " -> " << j << " : m[i][j] = " << m[i][j] << " dt[j] : " << dt[j] << ", dt[i] + m[i][j] = " << (dt[i] + m[i][j]) << endl;
        if (m[i][j] != 0 && (dt[j] > (dt[i] + m[i][j]))) { // last_visit:
          dt[j] = dt[i] + m[i][j];
        }
        else cout << i << " -> " << j << " no path " << endl;
    }
  }
  for (int i = 0; i < NODE_NUM; i++) cout << dt[i] << endl;
  return 0;
}
