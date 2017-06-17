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
  int* outBufferStartAddress = memory + inBufferSize / sizeof (int);
  int numOfFiles = lastFilePartIndex + 1;
  int chunkSize = inBufferSize / numOfFiles;
  ifstream** ifArray = (ifstream**) malloc(sizeof(ifstream*) * numOfFiles);
  bool* completed = (bool*)malloc(sizeof(bool) * numOfFiles);

  for (int partno = 0; partno < numOfFiles; partno++) {
    // open file descriptor
    stringstream ss;
    ss << "sub_" << partno << ".txt";

    ifArray[partno] = new ifstream(ss.str().c_str(),ios_base::in);
    //fillChunk(partno, memory, ifArray, completed);
    // ifstream tmp
    // and connect
  }

  
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
