/*
 * =====================================================================================
 *
 *       Filename:  array.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017년 06월 12일 05시 53분 25초
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

class Simple {
 public:
  Simple() { cout << "create simple " << endl; }
  virtual ~Simple() { cout << "destruct simple " << endl; }
  void Print() { cout << "print..." << endl; }
};

int main () {
  Simple *s = new Simple();

  cout << "now array of 4 " << endl;

  Simple *sarr = new Simple[4];

  s->Print();
  sarr[1].Print(); // memo-201706 : Hmmm [] makes *(sarr+1) 
  (sarr+1)->Print();
  return 0;
}
