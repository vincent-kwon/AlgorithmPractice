/*
 * =====================================================================================
 *
 *       Filename:  main.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017년 07월 05일 16시 18분 15초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hobum (Vincent) Kwon (mn), hobum.kwon@gmail.com
 *        Company:  Samsung Electornics
 *
 * =====================================================================================
 */

/*
 *       0
 *   1      2
 * 3   4  5   6 

   1 2 3 4 (max heap)

=> 1 : none
=> 2
   1
        (1) 2 only: 
 2 

   2

1

=> 3

  2
1   3 (1) 3 only: 1

=>4

     3
   1  2    (2) 4 only: 2
 4

    4
  3   2
1 

=> 5

    4
  3   2
1   5     (2) 5 only 2

   5 
 4   2
1  3

=> 6

          (2) 6 only 2
     6
  4    5
1  3  2  

==> 7    (2) 7 only 2

1~7 = 8 10 1~7 => 10 8,9,10,11,12,13,14,15 2
           1~16 => 27 + 10 => 37

Memo: how to get child, how to parent

  parent of left  x/2, 
  parent of right x/2 - 1,
 
  child of left  p * 2 + 1,
  child of right p * 2 + 2,

Memo: 
 
 build: make first k elements of given arrary [memo] O(k)
 add 
 delete
 max
 decrease all in logn 

Memo:

 1) first k heap build Min Heap MH

 2) compare it with root ?? k max heap <-- if bigger then k then it can't be never kth element
    if bigger, heapify for MH (adding one more) 
 3) 

 *  
 */

#include <iostream>
#include <climits>

using namespace std;

void swap(int *x, int *y);

class MinHeap
{
 private:
  int *harr;
  int capacity;
  int heap_size;
 public:
  MinHeap(int capacity);

  void MinHeapify(int);
  
  int parent(int i) { return (i-1)/2; }

  int left(int i) { return (2*i+1); }

  int right(int i) { return (2*i+2); }

  int extractMin();

  void decreaseKey(int i, int new_val);

  int getMin() { return harr[0]; }

  void deleteKey(int i);

  void insertKey(int k);
};

MinHeap::MinHeap(int cap) {
  heap_size = 0;
  capacity = cap;
  harr = new int[cap];
}

void MinHeap::insertKey(int k) {
  if (heap_size == capacity) {
    cout << "Overflow: could not insert key" << endl;
  }

  heap_size++;
  int i = heap_size - 1;
  harr[i] = k;

  while (i != 0 && harr[parent(i)] > harr[i]) {
    swap(&harr[i], &harr[parent(i)]);
    i = parent(i);
  }
}

void MinHeap::decreaseKey(int i, int new_val) {
  harr[i] = new_val;
  while (i != 0 && harr[parent(i)] > harr[i]) {
    swap(&harr[i], &harr[parent(i)]);
    i = parent(i);
  }
}

int MinHeap::extractMin() {
  if (heap_size <= 0) return INT_MAX;
  if (heap_size == 1) {
    heap_size--;
    return harr[0];
  }
  int root = harr[0];
  harr[0] = harr[heap_size-1];
  heap_size--;
  MinHeapify(0);
  return root;
}

void MinHeap::deleteKey(int i) {
  decreaseKey(i, INT_MIN);
  extractMin();
}

void MinHeap::MinHeapify(int i) {
  int l = left(i);
  int r = right(i);
  int smallest = i;
  if (l < heap_size && harr[l] < harr[i]) smallest = l;
  if (r < heap_size && harr[r] < harr[smallest]) smallest = r; 
  if (smallest != i) {
    swap(&harr[i], &harr[smallest]);
    MinHeapify(smallest);
  }
}
void swap(int *x, int *y) {
  int temp = *x;
  *x = *y;
  *y = temp;
}

int main() {
  MinHeap h(11);
  h.insertKey(3);
  h.insertKey(2);
  h.deleteKey(1);
  h.insertKey(15);
  h.insertKey(5);
  h.insertKey(4);
  h.insertKey(45);
  cout << h.extractMin() << " ";
  cout << h.getMin() << " ";
  h.decreaseKey(2,1);
  cout << h.getMin();
  return 0;
}
