/*
 * =====================================================================================
 *
 *       Filename:  mm.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016년 11월 18일 07시 42분 52초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hobum (Vincent) Kwon (mn), hobum.kwon@gmail.com
 *        Company:  Samsung Electornics
 *
 * =====================================================================================
 */

#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;
  
class DataProvider {
 public:
  const static int EMPTY = -1;
  DataProvider(int* startAddress, int size, int part_index) : memory(startAddress), size_(size), currentIndex(EMPTY)  {
    maxIndex = size / 4 - 1;
    stringstream ss;
    ss << "chunk_" << part_index << ".txt";
    fileInputPtr = new ifstream(ss.str().c_str());
    cout << "DP: " << ss.str().c_str() << endl;
    fileInputPtr->seekg(0, ios::beg);
  }
  
  bool getNext(int& outValue) {
    if (currentIndex > EMPTY) {
      outValue = memory[currentIndex--];
      return true;
    } 
    else {
      int value;
      *fileInputPtr >> value;
      while (!fileInputPtr->eof()) {
        if (currentIndex < maxIndex) {
          currentIndex++;
          memory[currentIndex] = value;
          if (currentIndex == maxIndex) break;
          else (*fileInputPtr) >> value;
        } 
      }
      if (currentIndex == EMPTY) {
        return false;
      }
      else {
        outValue =  memory[currentIndex--];
        return true;
      }
    } 
  }

 private:
  ifstream* fileInputPtr;
  int currentIndex;
  int maxIndex;  
  int *memory;
  int size_;
};

int main() {
  int mem_size;
  cin >> mem_size;
  int chunk_num;
  cin >> chunk_num;
  srand(time(NULL));
  for (int i = 0; i < chunk_num; i++) {
    stringstream ss;
    ss << "chunk_" << i << ".txt";
    string s = ss.str();
    ofstream outfile(s.c_str());
    for (int j = 0; j < 30 + i; j++) {
      int v = rand();
      outfile << v % 1000 << endl;   
    }  
  }
  DataProvider** chunkArray = (DataProvider**)malloc(sizeof(DataProvider*) * chunk_num);
  int* memory = (int *) malloc (mem_size);
  int perChunkMemory = mem_size / chunk_num;
  cout << "mem (int) : " << mem_size / 4 << endl;
  cout << "chunk num : " << chunk_num << endl;
  for (int i = 0; i < chunk_num; i++) {
    chunkArray[i] = new DataProvider(memory + i , perChunkMemory, i);
  }
  bool anyActive;
  int count = 0; 
  do {
    anyActive = false;
    for (int i = 0; i < chunk_num; i++) {
      int outValue;
      if (chunkArray[i]->getNext(outValue)) {
        count++;
        anyActive = true;
      }
    }
  } while (anyActive);
  cout << count << endl; 
  return 0;
}
