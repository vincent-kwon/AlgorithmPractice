#include <iostream>
#include <fstream>
#include <stdexcept>
#include <exception>
#include <sstream>
#include <limits.h>

#define MAX_DATA   1024*1024*1024
#define MAX_MEMORY 1024*1024

using namespace std;
int num_of_data;
int num_of_data_in_memory;
int num_of_chunk;
int num_of_slot;
int size_of_slot;
int *ram;

class Slot {
 public:
  Slot() {

  }
  virtual ~Slot() {

  }
  int startIndex;
  int endIndex;
  int curPosIndex;
  int curReadIndex;
  ifstream infile;
 private: 
};

void swap(int& a, int& b) 
{
  int tmp = a;
  a = b;
  b = tmp;
}
void quick_sort(const int startIndex, const int endIndex, int* array) {
  if (startIndex >= endIndex) return; // memo

  int endOfSmallIndex = startIndex - 1;
  int size = endIndex - startIndex + 1; 
  int current;

  for (int current = startIndex; current < endIndex; current++) {
    if (array[current] < array[endIndex]) {
      endOfSmallIndex++;
      swap(array[endOfSmallIndex], array[current]);
    }
  }
  int mid = endOfSmallIndex + 1;
  swap(array[mid], array[endIndex]); 
  quick_sort(startIndex, mid - 1, array); // revisit: if all big end < start
  quick_sort(mid + 1, endIndex, array); // revisit: if all small start > end
}

int main() {
#if 1 
  num_of_data = MAX_DATA / sizeof(int); // 2 of 30 - 2 of 2 = 2 of 28 integers
  num_of_data_in_memory = MAX_MEMORY / sizeof(int); // 2 of 20 - 2 of 2 = 2 of 18 per memory
  num_of_chunk = num_of_data / num_of_data_in_memory;

  ram = new int[num_of_data_in_memory];

  if (ram == NULL) throw bad_alloc(); //last_visit:
  
  for (int i = 0; i < num_of_chunk ; i++) {
    ifstream infile;
    stringstream ss; // last_visit: stringstream ss; 
    ss << "sub_" << i << ".txt"; // last_visit: samsung ss go <<<
    infile.open(ss.str());
    //if (infile.fail()) cout << "failed..." << endl;
    int value;
    int startIndex = 0;
    int endIndex = 0;
    while (infile >> value) {
      ram[endIndex] = value;
      endIndex++;
    }
    endIndex--;
    quick_sort(startIndex, endIndex, ram);

    stringstream sout; 
    sout << "big_" << i << ".txt";
    ofstream outfile(sout.str());
    for (int i = 0; i <= endIndex; i++) {
      outfile << ram[i] << endl;
    } 
  }

  num_of_slot = 10;  
  Slot* slots = new Slot[num_of_slot];
  //cout << "num of " << num_of_data_in_memory << "," << num_of_data_in_memory % num_of_slot << endl;
  if (num_of_data_in_memory % num_of_slot == 0) {
    size_of_slot = num_of_data_in_memory / num_of_slot; // left brain issue
    //cout << "size of slot " << size_of_slot << endl;
  }
  else {
    size_of_slot = num_of_data_in_memory / (num_of_slot - 1);
    //cout << "size of slot: " << size_of_slot << endl;
  }
  // memo: 20170628 
  //  
  // 100 div 10 slot => per 10 
  // 50 div 12 slot ?? per 4 will waste 2. In other words, 50 div 13 will give [0-12] [13-25] [26-38] [39-49] // only 11
  // if ( % == 0 ) = per size 10
  // else 100 / 13 = 7 ==> 
  
  int startIndex = 0;
  int endIndex = -1;

  //cout << "ram: 0 ~ " << num_of_data_in_memory << endl;

  for (int j = 0; j < num_of_slot; j++) {
    startIndex = endIndex + 1;
    slots[j].startIndex = startIndex;
    slots[j].curPosIndex = slots[j].startIndex - 1;
    slots[j].curReadIndex = -1;
    if (j != (num_of_slot - 1)) {
      slots[j].endIndex = size_of_slot + startIndex - 1;
      endIndex = slots[j].endIndex;
      //slots[j].maxCount = size_of_slot;
    }
    else {
      slots[j].endIndex = num_of_data_in_memory - 1;
      //slots[j].maxCount = slots[j].endIndex - slots[j].startIndex + 1; 
    }
    // cout << "slot : " << j << ", start: " << slots[j].startIndex << ", end: " << slots[j].endIndex << ", max: " << slots[j].maxCount << endl;
  }
  
  int file_value = -1;

  while (true) {
    // next turn
    // fill slot if nothing to read
    for (int i = 0; i < num_of_slot; i++) {
      if (slots[i].curReadIndex == -1) {
        if (!slots[i].infile.is_open()){
          // no file
          stringstream ss;
          ss << "big_" << ++file_value << ".txt";
          string fileChunk = ss.str();
          slots[i].infile.open(fileChunk.c_str());
          if (slots[i].infile.fail()) { // no more 
            break; 
          }
          // cout << "open new file at slot " << i << " file success " << fileChunk.c_str() << endl;
        }
        int value;
        while (slots[i].curPosIndex < slots[i].endIndex && slots[i].infile >> value) {
          slots[i].curPosIndex++; // this indicates last filled
          ram[slots[i].curPosIndex] = value;
          // cout << "Fill ram at " << slots[i].curPosIndex << " with value " << value <<endl;
        }
        if (slots[i].infile.eof()) slots[i].infile.close();
        if (slots[i].curPosIndex >= slots[i].startIndex) {
          slots[i].curReadIndex = slots[i].startIndex; // this indicates to read
        } 
      }
      //cout << "slot " << i << ": readIndex = " << slots[i].curReadIndex << " value = " << ram[slots[i].curReadIndex] << endl;
    }
    // compare 
    int tocompare = INT_MAX;
    int todelete = -1;

    for (int i = 0; i < num_of_slot; i++) {
      if (slots[i].curReadIndex != -1) {
        //cout << "tocompare : " << ram[slots[i].curReadIndex] << " with " << tocompare << " i = " << i << endl;
        if (tocompare > ram[slots[i].curReadIndex]) {
          todelete = i;
          tocompare = ram[slots[i].curReadIndex];
        }
      } 
    }
    if (todelete == -1) return 0;
    else {
      slots[todelete].curReadIndex++;
      cout << "Pop: " << todelete << ", value: " << tocompare << endl;
      if (slots[todelete].curReadIndex > slots[todelete].curPosIndex) {
        slots[todelete].curReadIndex = -1;
        slots[todelete].curPosIndex = slots[todelete].startIndex - 1;
      }
    }
  }
#endif
  return 0;
}
