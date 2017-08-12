/*
 * =====================================================================================
 *
 *       Filename:  main.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017년 08월 11일 22시 01분 39초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hobum (Vincent) Kwon (mn), hobum.kwon@gmail.com
 *        Company:  Samsung Electornics
 *
 * =====================================================================================
 */
#include <iostream>
#include "Process.h"
using namespace std;

int main() {
  Process p;
  cout << "[main] start.... " << endl;
  p.info();
  cout << "[main] end...." << endl;
  return 0;
}
