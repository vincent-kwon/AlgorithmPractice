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

  bool hasNext() {
    // how to detect has next has really next??????`
    if (fileInputPtr->eof()) {
      return false;
    }
    else return true;
  }

  int getNext() {
    if (currentIndex != EMPTY) {
      return memory[currentIndex--];
    } 
    else {
      int value;
      *fileInputPtr >> value;
      while (!fileInputPtr->eof() && currentIndex < maxIndex){
        currentIndex++;
        memory[currentIndex] = value;
        (*fileInputPtr) >> value;
      }
      if (currentIndex == EMPTY) {
        //throw NoDataException();
      }
      else {
        return memory[currentIndex--];
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
  do {
    anyActive = false;
    for (int i = 0; i < chunk_num; i++) {
      if (chunkArray[i]->hasNext()) {
        cout << i << ":" << chunkArray[i]->getNext() << endl;
        anyActive = true;
      }
    }
  } while (anyActive);
  return 0;
}
