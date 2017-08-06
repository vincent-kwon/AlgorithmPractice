/*
 * =====================================================================================
 *
 *       Filename:  file_operation.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017년 06월 12일 03시 18분 58초
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
#include <stdexcept>

using namespace std;

int main() {
  ifstream inFile2("name");
  ofstream outFile2("name2", ios_base::in);
  if (outFile2.fail()) throw invalid_argument("test");
  ifstream inFile("file.txt"); // revisit
  ofstream outFile("out.txt", ios_base::app); // revisit: ios_base:app, in, out

  if (inFile.fail()) { // revisit
    throw invalid_argument("bad file name"); // revisit: exceptions
  }
  int nextToken;
  while(inFile >> nextToken) { // revisit: file read inFile returns NULL when no data available
    cout << "next: " << nextToken << endl;
    outFile << nextToken << ":";
  }
  inFile.close();
  outFile.close();
  return 0;
}
