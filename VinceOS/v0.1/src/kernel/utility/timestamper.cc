/*
 * =====================================================================================
 *
 *       Filename:  timestamper.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017년 08월 13일 01시 34분 11초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hobum (Vincent) Kwon (mn), hobum.kwon@gmail.com
 *        Company:  Samsung Electornics
 *
 * =====================================================================================
 */

#include <iostream>
#include <map>
#include <string>
#include "timestamper.h"

using namespace std;

Timestamper::Timestamper() {
  cout << "const" << endl;
}

Timestamper::~Timestamper() { // memo-20170812: no need to add virtual in implemetation
  cout << "dest" << endl;
}

void Timestamper::enter(string mark) {
  cout << "enter:" << endl;
}

void Timestamper::exit(string mark, bool printResult) {
  cout << "exit:" << endl;
}

void Timestamper::print(string mark) {
  cout << "print: " << endl;
}

void Timestamper::printAll() {
  cout << "printAll:" << endl;
}

