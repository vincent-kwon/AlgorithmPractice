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

#define NODE_NUM 5
#define INF 987654321

int m[NODE_NUM][NODE_NUM] = {
 // 0, 1,  2, 3, 4, 5
  { 0, 4,  5, 8, 0 },
  { 0, 0, -3, 0, 0 },
  { 0, 0,  0, 0, 4 }, 
  { 0, 0,  0, 0, 2 },
  { 0, 0,  0, 1, 0 },
};

int dt[NODE_NUM] = {0, INF, INF, INF, INF};

// TODO: negative cycle
//
int main() {
  for (int i = 0; i < NODE_NUM; i++) {
    for (int adj = 0; adj < NODE_NUM; adj++) {
      if (m[i][adj] != 0) { // for convenience, consider 0 means no connect
        if (dt[adj] > (dt[i] + m[i][adj])) {
          dt[adj] = dt[i] + m[i][adj];
        }
      }
    }    
  }

 
  for (int i = 0; i < NODE_NUM; i++) cout << "dis[" << i << "] = " << dt[i] << endl; 
  return 0; 
}
