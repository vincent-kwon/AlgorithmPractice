/*
 * =====================================================================================
 *
 *       Filename:  m.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016년 11월 16일 14시 36분 16초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Dr. Fritz Mehner (mn), mehner@fh-swf.de
 *        Company:  FH Südwestfalen, Iserlohn
 *
 * =====================================================================================
 */

#include <iostream>
#include <stdlib.h>
#include <memory.h>
#include <time.h>
#include <fstream>
#include <sstream>

using namespace std;


class DataProvider {
 public:
  const static int EMPTY = -1;
  DataProvider(int* startAddress, int size, int part_index) : memory(startAddress), size_(size), currentIndex(EMPTY)  {
    maxIndex = size / 4 - 1;
    stringstream ss;
    ss <<  "sub_" << part_index << ".txt";
    fileInputPtr = new ifstream(ss.str().c_str());
    cout << "DP: " << ss.str().c_str() << endl;
    fileInputPtr->seekg(0, ios::beg);
  }

  void pop() {
    currentIndex--;
  }
  
  bool getNext(int& outValue) {
    if (currentIndex > EMPTY) {
      outValue = memory[currentIndex];
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
        outValue =  memory[currentIndex];
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


void quickSort(int *intArray, int startIndex, int endIndex) {
  int smallerIndex = startIndex - 1;
  int pivot = intArray[endIndex];

  if (startIndex > endIndex) return;
  // select endIndex for the pivot
  for (int i = startIndex; i < endIndex; i++) {
    if (pivot >= intArray[i]) {
      smallerIndex++;
      int tmp = intArray[smallerIndex];
      intArray[smallerIndex] = intArray[i];
      intArray[i] = tmp;
    }
  }
  
  int tmp = intArray[smallerIndex+1];
  intArray[smallerIndex+1] = pivot;
  intArray[endIndex] = tmp;
  quickSort(intArray, startIndex, smallerIndex);
  quickSort(intArray, smallerIndex+2, endIndex); // skip pivot index smallIndex+1
}

int sortLocal(string& inputFileName, const int memSize, const int dataSize, string& outputFile) {
  ifstream fileInput(inputFileName.c_str(), ios_base::in);
  int value;
  int numOfInt = dataSize / 4;
  int index = 0;
  int* intArray = (int*)malloc(numOfInt * sizeof(int));
  if (intArray == NULL) cout << "memory alloc fail: " << endl;
  fileInput >> value;
  while (!fileInput.eof()) {
    intArray[index] = value;
    fileInput >> value;      
    index++;
  }
  cout << "Last Index: " << index << ", numOfInt: " << numOfInt << endl;
  quickSort(intArray, 0, index-1);
  ofstream fileout(outputFile.c_str(), ios_base::out);
  for (int i = 0; i < numOfInt; i++) fileout << intArray[i] << endl;
  return 0;
}

string generateIntData(int dataSize) {
  int numOfInt = dataSize / 4;
 
  if (dataSize % 4) 
    cout << "Warning, data should be multiple of 4. Reminder will be ignored" << endl; 

  cout << "Num of integers to generate: " << numOfInt << endl;
  time_t rawTime;
  struct tm *timeinfo;
  time(&rawTime);
  timeinfo = localtime(&rawTime);
  char buff[30];
  strftime(buff, 30, "tmp-%y-%m-%d-%H:%M:%S.txt", timeinfo);
  ofstream fileout(buff, ios_base::out);
  srand(time(NULL));
  for (int i=0; i < numOfInt; i++) {
    fileout << rand() << endl;
  }
  
  cout << buff << endl;
  string retString(buff);
  return retString;
}

void writeFile(int *memory, int startIndex, int endIndex, int partno) {
  stringstream ss;
  ss << "sub_" << partno << ".txt";
  string outputFile = ss.str();
  ofstream fileout(outputFile.c_str(), ios_base::out);
  for (int i = startIndex; i <= endIndex; i++) fileout << memory[i] << endl;
}

int sortLimited(string& inputFileName, int memSize, int dataSize, int* memory) {
  ifstream fileInput(inputFileName.c_str(), ios_base::in);
  int value;
  int numOfInt = dataSize / 4;
  int index = 0;
  int filePart = 0;
  int maxIntOnMemory = memSize / sizeof(int);

  fileInput >> value;
  while (!fileInput.eof()) {
    if (index < maxIntOnMemory) {
      memory[index] = value;
    }
    else {
      quickSort(memory, 0, index-1);
      writeFile(memory, 0, index-1, filePart++);

      index = 0;
      memory[index] = value;
    }
    fileInput >> value;
    index++;
  }
  quickSort(memory, 0, index);
  writeFile(memory, 0, index, filePart);
  return filePart;
}

bool mergeFiles(int lastFilePartIndex, int memSize, int* memory, string outputFile) {
  // use half for input and output
  int outBufferSize = memSize / 2;
  int inBufferSize = memSize / 2;
  int* inBufferStartAddress = memory;
  int* outBufferStartAddress = inBufferStartAddress + inBufferSize / sizeof (int);
  int numOfFiles = lastFilePartIndex + 1;
  int chunkSize = inBufferSize / numOfFiles;

  int perChunkMemory = chunkSize; // in buffer chunk size

  DataProvider** chunkArray = (DataProvider**)malloc(sizeof(DataProvider*) * numOfFiles);
  for (int i = 0; i < numOfFiles; i++) {
    chunkArray[i] = new DataProvider(memory + i , perChunkMemory, i);
  }
  bool anyActive;
  do {
    anyActive = false;
    int selectIndex = -1;
    int selectValue = 987654321;
    cout << "get next one: " << endl;
    for (int i = 0; i < numOfFiles; i++) {
      int outValue;
      if (chunkArray[i]->getNext(outValue)) {
	  if (outValue < selectValue) {
          anyActive = true;
          selectIndex = i;
	    selectValue = outValue;
	  }
      }
    }
    if (anyActive) {
	chunkArray[selectIndex]->pop();
	cout << selectValue << endl;
    }
  } while (anyActive);
  
  return 0;
}


int main() {
  int dataSize, memSize;

  cout << "Data Size(M): " << endl;
  cin >> dataSize;
  cout << "Memory (K): " << endl;
  cin >> memSize;

  string outputFile = "sort.out.txt";
  
  dataSize = dataSize * 1024 * 1024;
  memSize = memSize * 1024;

  string s = generateIntData(dataSize);
  //int ret = sortLocal(s, memSize, dataSize, outputFile);

  //now consider memory 
  int *memory = (int *) malloc(memSize);

  if (!memory) throw bad_alloc();
  memset(memory, 0, memSize);
  
  int lastFilePartIndex = sortLimited(s, memSize, dataSize, memory);
  
  //merge them into one
  if (mergeFiles(lastFilePartIndex, memSize, memory, outputFile)) {
    cout << "out: " << outputFile << endl;
  } else {
    cout << "failed: " << endl;
  }

  return 0;
}
