/*
 * =====================================================================================
 *
 *       Filename:  fileStream.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017년 06월 28일 05시 36분 00초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hobum (Vincent) Kwon (mn), hobum.kwon@gmail.com
 *        Company:  Samsung Electornics
 *
 * =====================================================================================
 */

#include <iostream>
#include <fstream>
using namespace std;

int main() {
  ifstream infile;
  infile.open("abc.txt");
  int i;

  while (infile >> i) {
    cout << i << endl;
  }
  return 0;
}
