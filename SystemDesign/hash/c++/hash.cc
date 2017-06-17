/*
 * =====================================================================================
 *
 *       Filename:  hash.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016년 10월 17일 05시 09분 46초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hobum (Vincent) Kwon (mn), hobum.kwon@gmail.com
 *        Company:  Samsung Electornics
 *
 *
 *  push_front, pop_front, for_each, erase(itor), itor find, auto i : list, vector <100, >
 *  front, back, clear, remvoe(value), size(), sort(compare), 
 *  splice(it, mylist2); // mylist2 will be empty
 *  emplace(itor.begin(), 100); // add to the iterator position
 *
 * =====================================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
using namespace std;

class HashBucket {
 public: 
  HashBucket();
  const static int MAX_SIZE = 100;
  void Add(int value);
  bool Has(int value);
  int Hash(int value);
  void Delete(int value);
  void PrintBucket(int value); 
  int MaxSize;
  int Size;
 private:
  vector < list<int>* > _listV;
  int _getHash(int value);
};

HashBucket::HashBucket() : Size(0), MaxSize(MAX_SIZE) {
  _listV = vector< list<int>* >(MAX_SIZE, static_cast< list<int>* >(NULL));
}

void HashBucket::Add(int value) {
  int hash = Hash(value); 
  cout << "Hash: " << hash << endl;
  if (_listV[hash] == NULL) {
    _listV[hash] = new list<int>();
    _listV[hash]->push_back(value);
    cout << "New Added: " << value << endl;
  } 
  else {
    if (find(_listV[hash]->begin(), _listV[hash]->end(), value) != _listV[hash]->end()) {
      cout << "Exit:" << value << endl; 
    } 
    else {
      _listV[hash]->push_back(value);
      cout << "Added:" << value << endl;
    }
  }
}

bool HashBucket::Has(int value) {
  int hash = Hash(value); 
  if (_listV[hash] == NULL) {
    return false;
  } 
  else {
    list<int>::iterator itor = find(_listV[hash]->begin(), _listV[hash]->end(), value);
    if ( itor != _listV[hash]->end()) {
      _listV[hash]->erase(itor);
      _listV[hash]->push_front(value);
      return true;
    } 
    else return false;
  }
}

int HashBucket::Hash(int value) { 
  return _getHash(value);
}

void HashBucket::PrintBucket(int value) {
  int hash = Hash(value);

  if (_listV[hash] == NULL) return;
  else {
    for_each(_listV[hash]->begin(), _listV[hash]->end(), [] (int& i) {
      cout << i << " ";
    });
    cout << "" << endl;
  }
}

void HashBucket::Delete(int value) {
  int hash = Hash(value);
  if (_listV[hash] == NULL) return;
  else {
    auto itor = _listV[hash]->begin();
    for (auto i : *_listV[hash]) {
      cout << "auto: " << i << " ";
    }
    cout << "" << endl;
    for (itor; itor != _listV[hash]->end(); itor++) {
      if (*itor == value) {
        cout << "delete : " << value << endl;
        _listV[hash]->erase(itor);
       break;
      }
    }
  }
}

int HashBucket::_getHash(int value) {
  int v = value % MAX_SIZE;
  return v;
}

int main() {
  HashBucket h; 
  h.Add(1);
  h.Add(2);
  h.Add(101);
  h.Add(201);
  cout << "has 1 : " << h.Has(101) << endl;
  h.PrintBucket(1);
  h.Delete(1);
  h.PrintBucket(101);
  return 0;
}
