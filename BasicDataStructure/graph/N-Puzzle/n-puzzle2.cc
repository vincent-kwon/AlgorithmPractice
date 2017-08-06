#include <iostream>
#include <queue>
#include <vector>
#include <stdlib.h>
#include <map>

using namespace std;

#define MAX_VAL 16

class State {
 public: 
  vector<State> getAdjacent(map<State, int> &c) {
    vector<State> v;
    int index = getZero();
    //swap top
    if (index >= 0 && index <= 3) {}
    else {
      swap2(index-4, index);
      State ns;
      ns.setLValue(lvalue);
      if (c.count(ns) == 0) v.push_back(ns);
      swap2(index-4, index);
    } 
    //swap bottom
    if (index >= 12 && index <= 15) {}
    else {
      swap2(index+4, index);
      State ns;
      ns.setLValue(lvalue);
      if (c.count(ns) == 0) v.push_back(ns);
      swap2(index+4, index);
    }
    //swap left
    if (index == 0 || index == 4 || index == 8 || index == 12) {}
    else {
      swap2(index-1, index);
      State ns;
      ns.setLValue(lvalue);
      if (c.count(ns) == 0) v.push_back(ns);
      swap2(index-1, index);
    }
    //swap right
    if (index == 3 || index == 7 || index == 11 || index == 15) {} 
    else {
      swap2(index+1, index);
      State ns;
      ns.setLValue(lvalue);
      if (c.count(ns) == 0) v.push_back(ns);
      swap2(index+1, index);
    }
    return v;
  }

  bool operator< (const State& rhs) const {
    if (lvalue < rhs.lvalue) return true;
    else return false;
  }

  bool operator> (const State& rhs) const {
    if (lvalue > rhs.lvalue) return true;
    else false;
  }

  bool operator() (const State& lhs, const State& rhs) const {
    if (lhs.lvalue == rhs.lvalue) return true;
    else return false;
  }

  bool operator==(const State& rhs) const {
    if (lvalue == rhs.lvalue) return true;
    else return false;
  }

  void setArray(int *tmp) {
    for (int i = 0; i < MAX_VAL; i++) {
      a[i] = tmp[i];
    }
  }

  void setLValue(long l) {
    lvalue = l;
  }

  long getLongValue(int *a) {
    long l = 0;
    for (int i = 0; i < MAX_VAL; i++) {
      long along = a[i];
      l = l | (along << (i*4));
      //cout << i << ":" << along << ", s:" << (along << (i*4)) << ", l=" << l << endl;
    }
    return l;
  }
 
  int getValue(int index) {
    long l;
    long mask = (1L << 4) - 1;
    mask = mask << index*4; 
    l = lvalue & mask;
    int r = l >> index*4 ;
    return r;
  }

  void setValue(int index, int value) {
    long mask = (1L << 4) -1;
    long valueToLong = value;
    mask = mask << index*4;
    mask = ~mask;
    lvalue = lvalue & mask; // deleted
    lvalue = lvalue | (valueToLong << index*4); 
  }

  void setArray(long l) {
    lvalue = l;
  }

  int getZero() {
#ifdef AR
    for (int i = 0; i < MAX_VAL; i++) {
      if (a[i] == 0) return i;
    }
    return -1;
#else
    for (int i = 0; i < MAX_VAL; i++) {
      if (getValue(i) == 0) return i;
    }
    return -1;
#endif
  }

  void print() {
#ifdef AR
    for (int i = 0; i < MAX_VAL; i++) {
      cout << a[i] << ", ";
    }
    cout << "" << endl;
#else

#endif
  }
  void swap(int first, int second) {
#ifdef AR
    int tmp = a[first];
    a[first] = a[second];
    a[second] = tmp;
#else

#endif
  }

  void swap2(int first, int second) {
    int tmp = getValue(first);
    setValue(first, getValue(second));
    setValue(second, tmp);
  }

  int a[MAX_VAL];
  long lvalue;
};


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
  queue<State> q; // last_visit: one queue different length

  if (start == finish) return 0; // last_visit: start condition

  q.push(start); c[start] = 1;
  q.push(finish); c[finish] = -1; // last_visit: visited map with sign

  while (!q.empty()) {
    State here = q.front();
    q.pop();
    vector<State> adjacent = here.getAdjacent(c);
    for (int i = 0; i < adjacent.size(); i++) {
      map<State, int>::iterator it = c.find(adjacent[i]); // last_visit: map iterator itor->first, itor->second
      if (it == c.end()) {
        c[adjacent[i]] = incr(c[here]);
        q.push(adjacent[i]);
      }
      // already visited. why compare c[adj] == c[here]???
      else if (sgn(it->second) != sgn(c[here])) return abs(it->second) + abs(c[here]) - 1;
    }
  }
 
  return -1;
}

int bfs(State start, State finish) {

  if (start == finish) {
    return 0;
  }

  map<State,int> c;

  queue<State> q;

  q.push(start); c[start] = 1;
 
  int count = 0;
  while (!q.empty()) {
    State here = q.front();
    q.pop();
    count++;
    int cost = c[here];
    vector<State> adjacent = here.getAdjacent(c);
    //cout << "adjacent:" << adjacent.size() << endl;

    for (int i = 0; i < adjacent.size(); ++i) {
      //adjacent[i].print();
      if (c.count(adjacent[i]) == 0) {
        if (adjacent[i] == finish) return cost + 1;
        c[adjacent[i]] = cost + 1;
        q.push(adjacent[i]);
      } // else cout << "Visitied!!!" << endl;
    }
  }

  return -1;
}

int main() {
  State s;
  State e;

  int i = 1;
  long sum = 1;
  for (i; i <= 16; i++) {
   sum = sum * i;
  }
  cout << "factorial 16 " << sum << endl;

  int a[] = { 0, 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 };
  int b[] = { 15,14,13,12,11,10,9,8,7,6,5,4,3,0,2,1 };
  s.setArray(s.getLongValue(a));
  e.setArray(s.getLongValue(b));
  int r = bfs(s,e);
  //int r  = bidirectional(s,e);
  cout << "r: " << r << endl;
  return 0;
}
