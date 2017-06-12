/*
 * =====================================================================================
 *
 *       Filename:  priority_queue.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017년 06월 12일 08시 59분 29초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hobum (Vincent) Kwon (mn), hobum.kwon@gmail.com
 *        Company:  Samsung Electornics
 *
 * =====================================================================================
 */

#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

int main() {
  priority_queue<int> pq;
  pq.push(100);
  pq.push(300);
  pq.push(1000);
  pq.push(200);

  int i = pq.top();
  cout << "pq front: " << i << endl;
  pq.pop();
  i = pq.top();
  cout << " next : " << i << endl;
  return 0;
}
