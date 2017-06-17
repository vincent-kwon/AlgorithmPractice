/*
 * =====================================================================================
 *
 *       Filename:  lambda.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017년 06월 12일 09시 21분 04초
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

int main() {
  auto fn = [](string str) { return "hello " + str; };
  int x = 1000;
  cout << fn("call 1") << endl;
  cout << fn("call 2") << endl;

  auto fn2 = [=](string str) -> int { return  2 * x; };
  cout << fn2("good") << endl; 
  return 0;
}
