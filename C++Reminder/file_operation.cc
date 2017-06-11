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
  ifstream inFile("file.txt");
  ofstream outFile("out.txt", ios_base::app);

  if (inFile.fail()) {
    throw invalid_argument("bad file name");
  }
  int nextToken;
  while(inFile >> nextToken) {
    cout << "next: " << nextToken << endl;
    outFile << nextToken << ":";
  }
  inFile.close();
  outFile.close();
  return 0;
}
