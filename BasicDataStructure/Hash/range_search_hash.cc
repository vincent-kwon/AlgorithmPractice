/*
 * =====================================================================================
 *
 *       Filename:  range_search_hash.cc
 *
 *    Description:  Search query for hashes
 *
 *        Version:  1.0
 *        Created:  2017년 06월 23일 07시 17분 26초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hobum (Vincent) Kwon (mn), hobum.kwon@gmail.com
 *        Company:  Samsung Electornics
 *
 * =====================================================================================
 */
#if 0
#include <iostream>
#include <list>

using namespace std;

// should be able to search by range
//
// for example 0~999, 1000~1999, 2000~2999, 3000~3999
// 10,000 cars
// search query would be 900 ~ 2100
//
class Record {
 public:
  int age;
  int name;
  int price;
  int sex;
  Record(int _age, int _name, int _price, int _sex) : age(_age), name(_name), price(_price), sex(_sex) {
  }
};

class PriceRangeHash {
 public: 
  PriceRangeHash(int max, int perSlotUnits) {
    _perSlot = perSlotUnits;
    _numBuckets = max / perSlotUnits + 1;

    cout << "bucket count: " << _numBuckets << endl;

    hashBuckets = new list<Record*>[_numBuckets];
    int startPoint = 0; 
    int endPoint = -1;

    while (true) {
      startPoint = endPoint + 1; 
      endPoint = startPoint + perSlotUnits - 1;
      if (endPoint > max) {
        endPoint = max;
      }
      // add to bucket: bucket * perSlotUnit (start), 
      // end = start + perSlotUnit -1  perSlotUnits => 0(0~999), 1(1000~1999), 2(2000~2999) 
      int bucketIndex = startPoint / perSlotUnits; 
      cout << bucketIndex << ": " << startPoint << "~" << endPoint << endl;

      if (endPoint == max) break;
    }
  }
  virtual ~PriceRangeHash() {

  }
  
  int getBucketNumber(int value) {
    return value / _perSlot;
  }

  int searchAll(int startValue, int endValue) {
    // multiple buckets how to add only borders should be checked and others should be just added
    int beginBucket = startValue / _perSlot;
    int endBucket = endValue / _perSlot; 
    int tmp = beginBucket;
    while (tmp <= endBucket) {
      if (beginBucket == tmp) {
        for (auto v : hashBuckets[tmp]) {
          if (v->price >= startValue) {
            cout << v->price << endl;
          } 
        }
      }
      else if (endBucket == tmp) {
        for (auto v : hashBuckets[tmp]) {
          if (v->price <= endValue) {
            cout << v->price << endl;
          }
          else break;
        }
      }
      else {
        for (auto v : hashBuckets[tmp]) {
           cout << v->price << endl;
        }
      }
     // cout << "search: " << tmp << endl;
     
      tmp++;
    }
  }

  void add(Record* record) {
    int b = getBucketNumber(record->price);

    if (hashBuckets[b].size() == 0) hashBuckets[b].push_back(record);
    else {
      list<Record*>::iterator itor = hashBuckets[b].begin();
      for (itor; itor != hashBuckets[b].end(); itor++) {
        Record* current = *itor;
        if (current->price > record->price) {
          hashBuckets[b].insert(itor, record);
          break;
        }
        else {
          continue;
        }
      }
      if (itor == hashBuckets[b].end()) {
        // nothing bigger than record, then end of bucket
        hashBuckets[b].push_back(record);
      }
    }
  }    
  void print() {
    int index = 0;
    //for (auto i : hashBuckets) {
    for (int i = 0; i < _numBuckets; i++) {
      for (auto v : hashBuckets[i]) {
        cout <<"[" << index << "]" << v->price << " "; 
      }  
      cout << "" << endl;
      index++;
    }
  }
 private:
  list<Record*> *hashBuckets;
  int _perSlot;
  int _numBuckets;
};
 
#endif

// 23 minutes to complete it
// extends to search for all four types
//
#include <iostream>
#include <vector>
#include <list>

using namespace std;

class Record {
 public:
  Record(int age, int name, int price, int sex) : age_(age), name_(name), price_(price), sex_(sex) {

  }
  virtual ~Record() { };
  int age_;
  int sex_;
  int name_;
  int price_;
 private:
  Record() = delete;
  Record& operator=(const Record& rhs) = delete;
};

class PriceRangeHash {
 public:
  PriceRangeHash(int max, int unit) : max_(max), unit_(unit) {
    buk_num_ = max / unit + 1;
    buk = new list<Record*>[buk_num_];
  }
  virtual ~PriceRangeHash() {

  }
  int getBucketNumber(int value) {
    return value / unit_;
  }

  void add(Record *r) { 
    int value = r->price_;
    int toadd = getBucketNumber(r->price_);
    list<Record*>::iterator itor = buk[toadd].begin();
    for (itor; itor != buk[toadd].end(); itor++) {
      Record* tmp = *itor;
      if (tmp->price_ <= value) {
        continue;
      }
      else {
        buk[toadd].insert(itor, r);
        break;
      }
    }
    if (itor == buk[toadd].end()) {
      buk[toadd].push_back(r);
    }
  }

  vector<Record*> searchAll(int start, int end) {
    int sb = getBucketNumber(start);
    int eb = getBucketNumber(end);
    
    int tmp = sb;
    vector<Record*> result;
 
    while (tmp <= eb) {
      if (tmp == sb)  {
        for (auto v : buk[tmp]) {
          if (v->price_ >= start) result.push_back(v); //cout << v->price_ << endl;
        }
      }
      else if (tmp == eb) {
        for (auto v : buk[tmp]) {
          if (v->price_ <= end) result.push_back(v); //cout << v->price_ << endl;
          else break;
        }
      }
      else {
        for (auto v : buk[tmp]) result.push_back(v); //cout << v->price_ << endl;
      }
      tmp++; 
    } 
    return result;
  }

  void print() {
    for (int i = 0; i < buk_num_; i++) {
      for (auto v : buk[i]) {
        cout << v->price_ << endl; 
      }
    }
  }

 private: 
  int max_;
  int unit_;
  int buk_num_;
  list<Record*> *buk;
  PriceRangeHash() = delete;
  PriceRangeHash& operator=(const PriceRangeHash& rhs) = delete;
};


class AgeRangeHash {
 public:
  AgeRangeHash(int max, int unit) : max_(max), unit_(unit) {
    buk_num_ = max / unit + 1;
    buk = new list<Record*>[buk_num_];
  }
  virtual ~AgeRangeHash() {

  }
  int getBucketNumber(int value) {
    return value / unit_;
  }

  void add(Record *r) { 
    int value = r->age_;
    int toadd = getBucketNumber(r->age_);
    list<Record*>::iterator itor = buk[toadd].begin();
    for (itor; itor != buk[toadd].end(); itor++) {
      Record* tmp = *itor;
      if (tmp->age_ <= value) {
        continue;
      }
      else {
        buk[toadd].insert(itor, r);
        break;
      }
    }
    if (itor == buk[toadd].end()) {
      buk[toadd].push_back(r);
    }
  }

  vector<Record *> searchAll(int start, int end) {
    int sb = getBucketNumber(start);
    int eb = getBucketNumber(end);
    vector<Record*> result;
    int tmp = sb; 
    while (tmp <= eb) {
      if (tmp == sb)  {
        for (auto v : buk[tmp]) {
          if (v->age_ >= start) result.push_back(v);//cout << v->age_ << endl;
        }
      }
      else if (tmp == eb) {
        for (auto v : buk[tmp]) {
          if (v->age_ <= end) result.push_back(v);// cout << v->age_ << endl;
          else break;
        }
      }
      else {
        for (auto v : buk[tmp]) result.push_back(v); //cout << v->age_ << endl;
      }
      tmp++; 
    } 
    return result;
  }

  void print() {
    for (int i = 0; i < buk_num_; i++) {
      for (auto v : buk[i]) {
        cout << v->age_ << endl; 
      }
    }
  }

 private: 
  int max_;
  int unit_;
  int buk_num_;
  list<Record*> *buk;
  AgeRangeHash() = delete;
  AgeRangeHash& operator=(const AgeRangeHash& rhs) = delete;
};

class SexRangeHash {
 public:
  SexRangeHash(int max, int unit) : max_(max), unit_(unit) {
    buk_num_ = max / unit + 1;
    buk = new list<Record*>[buk_num_];
  }
  virtual ~SexRangeHash() {

  }
  int getBucketNumber(int value) {
    return value / unit_;
  }

  void add(Record *r) { 
    int value = r->sex_;
    int toadd = getBucketNumber(r->sex_);
    list<Record*>::iterator itor = buk[toadd].begin();
    for (itor; itor != buk[toadd].end(); itor++) {
      Record* tmp = *itor;
      if (tmp->sex_ <= value) {
        continue;
      }
      else {
        buk[toadd].insert(itor, r);
        break;
      }
    }
    if (itor == buk[toadd].end()) {
      buk[toadd].push_back(r);
    }
  }

  vector<Record*> searchAll(int start, int end) {
    int sb = getBucketNumber(start);
    int eb = getBucketNumber(end);
    vector<Record*> result; 
    int tmp = sb; 
    while (tmp <= eb) {
      if (tmp == sb)  {
        for (auto v : buk[tmp]) {
          if (v->sex_ >= start) result.push_back(v);//cout << v->sex_ << endl;
        }
      }
      else if (tmp == eb) {
        for (auto v : buk[tmp]) {
          if (v->sex_ <= end) result.push_back(v); //cout << v->sex_ << endl;
          else break;
        }
      }
      else {
        for (auto v : buk[tmp]) result.push_back(v); // cout << v->sex_ << endl;
      }
      tmp++; 
    } 
    return result;
  }


  void print() {
    for (int i = 0; i < buk_num_; i++) {
      for (auto v : buk[i]) {
        cout << v->sex_ << endl; 
      }
    }
  }

 private: 
  int max_;
  int unit_;
  int buk_num_;
  list<Record*> *buk;
  SexRangeHash() = delete;
  SexRangeHash& operator=(const SexRangeHash& rhs) = delete;
};

int main() {
  PriceRangeHash pr(7000, 2000); 
  cout << "expect 0: " << pr.getBucketNumber(0) << endl;
  cout << "0: " << pr.getBucketNumber(999) << endl;
  cout << "1: " << pr.getBucketNumber(2000) << endl;
  cout << "1: " << pr.getBucketNumber(3000) << endl;
  cout << "3: " << pr.getBucketNumber(7000) << endl;
  Record* tmp;
  pr.add(tmp = new Record(19, 1, 500, 0));
  AgeRangeHash ar(100, 10);
  SexRangeHash sr(2,1);
  ar.add(tmp);
  sr.add(tmp);
  pr.add(tmp = new Record(29, 2, 999, 0));
  ar.add(tmp);
  sr.add(tmp);
  pr.add(tmp = new Record(35, 3, 2000, 1));
  ar.add(tmp);
  sr.add(tmp);
  pr.add(tmp = new Record(32, 4, 4000, 0));
  ar.add(tmp);
  sr.add(tmp);
  pr.add(tmp = new Record(40, 5, 5000, 1));
  ar.add(tmp);
  sr.add(tmp);
  pr.add(tmp = new Record(50, 6, 7000, 0 ));
  ar.add(tmp);
  sr.add(tmp);
  vector<Record*> r1 = pr.searchAll(999, 5001);
  vector<Record*> r2 = ar.searchAll(6, 40);
  vector<Record*> r3 = sr.searchAll(0,0);
  
  for (auto v1 : r1) {
    for (auto v2 : r2) {
      for (auto v3 : r3) {
        if (v1 == v2 && v2 == v3) cout << v1->price_ << ", " << v1->age_ << ", " << v1->sex_ << endl;
      }
    }
  }
 
  // intersect
  // union 
  return 0; 
}
