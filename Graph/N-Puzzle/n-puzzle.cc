#include <iostream>

using namepsace std;

class State {
  vector<State> getAdjacent() const;

  bool operator < (const State& rhs) const;

  bool operator = (const State& hrs) const;
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

  while (!.q.empty()) {
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
 
  while (!.q.empty()) {
    State here = q.front();
    q.pop();
    int cost = c[here];

    vector<State> adjacent = here.getAdjacent();
    for (int i = 0; i < adjacent.size(); ++i) {
      if (c.count(adjacent[i]) == 0) {
        if (adjacent[i] == finish) return cost + 1;
        c[adjacent[i]] = cost + 1;
        q.push(adjacent[i]);
      }
    }
  }

  return -1;
}

int main() {
  
}
