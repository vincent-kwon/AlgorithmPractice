/*
 * =====================================================================================
 *
 *       Filename:  queue.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017년 06월 12일 08시 49분 46초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hobum (Vincent) Kwon (mn), hobum.kwon@gmail.com
 *        Company:  Samsung Electornics
 *
 * =====================================================================================
 */

#include <iostream>
#include <queue>
#include <stdexcept>

using namespace std;

int main() {
  queue<int> q;

  q.push(1);
  q.push(2);
  cout << "now fron: " << q.front() << endl;;
  cout << "size: " << q.size() << endl;
  q.pop();
  cout << "now fron: " << q.front() << endl;;
  q.pop();

  if (q.empty()) throw out_of_range("buffer is empty");
}

