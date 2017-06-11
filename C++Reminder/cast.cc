/*
 * =====================================================================================
 *
 *       Filename:  cast.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017년 06월 12일 06시 57분 48초
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

class A {
 public: 
  virtual void Print() { cout << "A: " << endl; }
};

class Sub : public A {
 public:
  virtual void Print() { cout << "Sub: " << endl; }
};

void pass(void* v) {
  Sub* ss = static_cast<Sub*>(v); // memo-201706 : const_cast to remove const, reinterpret_cast to just cast (not safe)
  ss->Print();
  ss->A::Print();
} 
int main() {
  Sub* s = new Sub();
  pass ((void*)s);
}
