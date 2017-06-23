/*
 * =====================================================================================
 *
 *       Filename:  heap.cc
/remove
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017년 06월 21일 07시 29분 42초
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
#include <vector>

using namespace std;

class Heap {
 public:
  Heap(int length) {
    // only needed for array version: cout << "length: " << length << endl;
    //array = new int(length);
    //for (int i = 0; i < length; i++) array[i] = 0;
    
  }
  virtual ~Heap() {
    cout << "destructor: " << endl;
  } 
  virtual void add(int i) {
    //cout << "add to heap" << endl;
    _arr.push_back(i);
    // now move up ( n / 2 - 1 ) 
    int parent = getParent(_arr.size()-1);
    int node = _arr.size()-1;
    while (parent != -1) {
      //int parent = getParent(node);
      cout << "Parent of " << i << " : " << parent << endl;
      if (_arr[node] > _arr[parent]) {
        swap(_arr[node], _arr[parent]);
        node = parent;
        parent = getParent(node);
      }
      else {
        break;
      }
    }  
  }
  virtual void removeTop() {
    cout << "removed top:" << endl;
    swap(_arr[0], _arr[_arr.size()-1]);
 
    int node = 0; // root 

    while (true) {
      int leftIndex = getChild(node, true);
      int rightIndex = getChild(node, false);
      int biggerIndex =  (_arr[leftIndex] > _arr[rightIndex]) ? leftIndex : rightIndex;;
      if (_arr[node] < _arr[biggerIndex]) {
        swap(_arr[node], _arr[biggerIndex]);
        node = biggerIndex; 
      }
      else {
        break;
      }
    }
    cout << "To remove: " << _arr[_arr.size()-1] << endl;
    _arr.resize(_arr.size()-1);
  } 
  int size() {
    return _arr.size();
  }
  int getElement(int index) {
    return _arr[index];
  }
 private: 
  Heap() = delete;
  int getParent(int index) {
    if (index == 0) return -1; 
    if (index == 1) return 0;
    return (index % 2) ? index / 2 : index / 2  - 1;
  } 
  int getChild(int index, bool left) {
    if (left) {
       return index * 2 + 1; 
    }
    else {
      return index * 2 + 2;
    }
  }
  //int* array;
  vector<int> _arr;
  void swap(int& a, int& b) {
    cout << "Swapping " << a << "," << b << endl;
    int tmp = a;
    a = b;
    b = tmp;
  }
  Heap& operator=(const Heap& rhs) = delete;
};
 return 0;
}
#endif
 
#include <iostream>
#include <vector>

using namespace std;

class Heap {
 public:

 Heap(int size) {
   // ignore size;  
 }

 virtual ~Heap() {

 }

 int getParentIndex(int i) {
   if (i == 0) return -1;
   
   if (i % 2) return i / 2;
   else return i / 2 - 1; 
 }

 int getChildIndex(bool left, int current) {
   int r; 
   if (left == true) r =  current * 2 + 1;
   else r = current * 2 + 2; 
   if (r >= v.size()) return -1;
   else return r; 
 }

 void add(int i) {
   // push back to the last of heap
   v.push_back(i);
   // now check the parent 
   int pIndex = getParentIndex(v.size()-1);
   int cIndex = v.size()-1;
   while (pIndex >= 0) {
     if (v[pIndex] < v[cIndex]) {
       swap(v[pIndex], v[cIndex]);
       cIndex = pIndex;
       pIndex = getParentIndex(cIndex);
     }
     else break;
   }
 }

 void removeTop() {
   swap(v[0], v[v.size()-1]);
   cout << "return: " << v[v.size()-1];
   int current = 0; // top   
   int toCheck;

   v.resize(v.size()-1);
   while (true) {
     int leftIndex = getChildIndex(true, current);
     if (leftIndex == -1) {
       break;
     }
     int rightIndex = getChildIndex(false, current); 
     if (rightIndex == -1) {
       toCheck = leftIndex;        
     }
     else {
       toCheck = (v[leftIndex] > v[rightIndex])? leftIndex : rightIndex;
     }
     if (v[toCheck] > v[current]) {
       swap(v[toCheck], v[current]);
       current = toCheck; 
     }
     else break;
   }
 }
 
 int getElement(int index) {
   return v[index];
 }

 int size() {
   return v.size(); 
 }

 private:
  vector<int> v;
};

int main() {
  Heap h(10); 
  h.add(10);
  h.add(20);
  h.add(30);
  h.add(100);
  h.add(200);
  h.add(300);
  h.add(400);
  h.add(500);
  h.add(600);
  h.add(700);
  h.add(800);

  h.removeTop();
  for (int i = 0; i < h.size(); i++) {
    cout << h.getElement(i) << " " ; 
  }

#if 0
              800 
       700           300 
   400      600    20    200 
  10 100  30   500
   
          700 
     600       300
  400   500  20   200
10 100 30 

#endif
 
}
