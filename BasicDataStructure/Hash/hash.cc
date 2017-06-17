/*
 * =====================================================================================
 *
 *       Filename:  hash.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017년 06월 13일 04시 54분 27초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hobum (Vincent) Kwon (mn), hobum.kwon@gmail.com
 *        Company:  Samsung Electornics
 *
 * =====================================================================================
 */

#include <iostream>
#include <queue>
#include <list>
#include <stdexcept>
#include <algorithm>

using namespace std;

class Hash {
 public:
   Hash(int bucket_size) : _max_bucket(bucket_size) {
     if (bucket_size == 0) throw invalid_argument("zero is not allowed");
     lists = new list<int>[bucket_size];
   }

   virtual ~Hash() {
   }

   int getHashValue(int i) {
     return i % _max_bucket;
   }

   void printBucket(int h) {
     list<int>::iterator itor = lists[h].begin();

     for (itor; itor != lists[h].end(); itor++) {
       cout << *itor << ", ";
     }
     cout << "" << endl;
   }
 
   void add(int i) {
     int h = getHashValue(i);
     if (lists[h].size() == 0) cout <<"First element for " << h << endl;

     //lists[h].push_back(i);
     list<int>::iterator itor = lists[h].begin();
     for (; itor != lists[h].end(); itor++) {
       if (*itor > i) break;
     }
     if (itor == lists[h].end()) lists[h].push_back(i);
     else lists[h].insert(itor, i);
     
     printBucket(h);
   }

   list<int>::iterator search(int i) {
     int h = getHashValue(i);
     return find(lists[h].begin(), lists[h].end(), i);
   }

   void remove(int i) {
     int h = getHashValue(i);
     cout << "size before delete " << lists[h].size() << endl;
     list<int>::iterator itor = search(i);
     if (itor != lists[h].end()) {
       cout << "Found key at hash : " << h << endl;
       lists[h].erase(itor);
     }
     cout << "size after delete : " << lists[h].size() << endl;
  }

 private:
   int _max_bucket;
   list<int> *lists;
};

int main() {
  // hash map with priority queue 
  Hash h(10);
  h.add(12);
  h.add(7);
  h.add(22);
  h.add(2);
  h.remove(22);
  return 0;
}
