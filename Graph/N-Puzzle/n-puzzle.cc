#include <iostream>
#include <queue>
#include <vector>
#include <stdlib.h>
#include <map>

using namespace std;

#define MAX_VAL 16

class State {
 public: 
  vector<State> getAdjacent() {
    vector<State> v;
    int index = getZero();
    //swap top
    if (index >= 0 && index <= 3) {}
    else {
      swap(index-4, index);
      State ns;
      ns.setArray(a);
      v.push_back(ns);
      swap(index-4, index);
    } 
    //swap bottom
    if (index >= 12 && index <= 15) {}
    else {
      swap(index+4, index);
      State ns;
      ns.setArray(a);
      v.push_back(ns);
      swap(index+4, index);
    }
    //swap left
    if (index == 0 || index == 4 || index == 8 || index == 12) {}
    else {
      swap(index-1, index);
      State ns;
      ns.setArray(a);
      v.push_back(ns);
      swap(index-1, index);
    }
    //swap right
    if (index == 3 || index == 7 || index == 11 || index == 15) {} 
    else {
      swap(index+1, index);
      State ns;
      ns.setArray(a);
      v.push_back(ns);
      swap(index+1, index);
    }
    return v;
  }

  bool operator< (const State& rhs) const {
    for (int i = 0; i < MAX_VAL; i++) {
      if (a[i] < rhs.a[i]) return true;
      else if (a[i] > rhs.a[i]) return false;
      else continue;
    }
    return false;
  }

  bool operator> (const State& rhs) const {
    for (int i = 0; i < MAX_VAL; i++) {
      if (a[i] > rhs.a[i]) return true;
      else if (a[i] < rhs.a[i]) return false;
      else continue;
    }
    return false;
  }

  bool operator() (const State& lhs, const State& rhs) const {
    //cout << "Yes called () " << endl;
    if(lhs == rhs) return true;
    else return false;
  }

  bool operator==(const State& rhs) const {
    //cout << "Yes called ==" << endl;
    for (int i = 0; i < MAX_VAL; i++) {
      if (a[i] != rhs.a[i]) {
         //cout << "   false " << endl;
        return false;
      }
    }
    return true;
  }
  void setArray(int *tmp) {
    for (int i = 0; i < MAX_VAL; i++) {
      a[i] = tmp[i];
    }
  }

  int getZero() {
    for (int i = 0; i < MAX_VAL; i++) {
      if (a[i] == 0) return i;
    }
    return -1;
  }

  void print() {
    for (int i = 0; i < MAX_VAL; i++) {
      cout << a[i] << ", ";
    }
    cout << "" << endl;
  }
  void swap(int first, int second) {
    int tmp = a[first];
    a[first] = a[second];
    a[second] = tmp;
  }
  int a[MAX_VAL];
};

typedef map<State, int> StateMap;

int sgn(int x) { 
  if (!x) return 0;
  return x > 0 ? 1 : -1;
}

int incr(int x) {
  if (x < 0) return x - 1; 
  return x + 1; 
}

int bidirectional(State start, State finish) {
  map<State, int> c;
  queue<State> q;

  if (start == finish) return 0;

  q.push(start); c[start] = 1;
  q.push(finish); c[finish] = -1;

  while (!q.empty()) {
    State here = q.front();
    q.pop();
    vector<State> adjacent = here.getAdjacent();
    for (int i = 0; i < adjacent.size(); i++) {
      map<State, int>::iterator it = c.find(adjacent[i]);
      if (it == c.end()) {
        c[adjacent[i]] = incr(c[here]);
        q.push(adjacent[i]);
      }

      else if (sgn(it->second) != sgn(c[here])) return abs(it->second) + abs(c[here]) - 1;
    }
  }
 
  return -1;
}

int bfs(State start, State finish) {

  if (start == finish) {
    return 0;
  }

  StateMap c;

  queue<State> q;

  q.push(start); c[start] = 1;
 
  while (!q.empty()) {
    State here = q.front();
    q.pop();
    int cost = c[here];
    vector<State> adjacent = here.getAdjacent();
    for (int i = 0; i < adjacent.size(); ++i) {
      //adjacent[i].print();
      if (c.count(adjacent[i]) == 0) {
        if (adjacent[i] == finish) return cost + 1;
        c[adjacent[i]] = cost + 1;
        q.push(adjacent[i]);
      } else cout << "Visitied!!!" << endl;
    }
  }

  return -1;
}

int main() {
  State s;
  State e;

  int a[] = { 15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0 };
  int b[] = { 15,14,13,12,11,10,9,8,7,6,5,4,3,0,2,1 };
//  int b[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 };    
  s.setArray(a);
  e.setArray(b);
  int r = bfs(s,e);

  cout << "r: " << r << endl;

  return 0;
}
