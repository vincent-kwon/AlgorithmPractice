/*
 * =====================================================================================
 *
 *       Filename:  test.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016년 11월 18일 09시 58분 39초
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
#include <sstream>

using namespace std;

int main() {
  stringstream ss;
  ss << "fuck" << 1 << ".txt";
  ofstream *outptr;
  outptr = new ofstream(ss.str().c_str());
  *outptr << "Good morning 2" << endl;
  outptr->flush();
  outptr->close();
  ifstream infile("hello.txt");

  // in int : MSB     LSB
  //          0  1  2  3
  // to char LSB comes first 
  //          3  2  1  0 (little endian, LSB is first element byte array in memroy)
  int a[2] = { 0x30313233, 0x35363738 };
  char *cstr = (char *)a;
  for (int i = 0; i < 8; i++) 
    cout << cstr[i] << endl;
  return 0;
}
