#include <iostream>
#include <exception>

using namespace std;

class vqueue {
 public: 
  int size;
  int front;
  int back;
  int MAX;
  int array[5];

  vqueue() {
    size = 0; 
    front = -1;
    back = -1;
    MAX = 5;
  }

  void push(int num) {
    if (size >= MAX) throw "full";
    else {
      if (front == -1 && back == -1) {
        front = 0;
        back = 0;
        size++;
        array[back] = num;
      }
      else {
        back++;
        if (back == MAX) back = 0;
        size++;
        array[back] = num;
      }
      cout << "pushed at " << back << " for " << array[back] << endl;
    }
  }

  int pop() {
    if (size == 0) throw "empty"; 
    else {
      int r = array[front];
      front++;
      if (front == MAX) front = 0;
      size--;
      return r;
    }
  }
};

int main() {
  vqueue vq;
  vq.push(100);
  vq.push(200);
  vq.push(300);
  vq.push(400);
  vq.push(500);
  int i = vq.pop();
  int j = vq.pop();
  int k = vq.pop();
  int m = vq.pop();
  int x = vq.pop();

  cout << i << endl;
  
  cout << j << endl;
  cout << k << endl;
  cout << m << endl;
  cout << x << endl;

  //vq.pop();
 
  vq.push(1);
  cout << vq.pop() << endl; 
  cout << vq.size << endl;
  return 0;
}
