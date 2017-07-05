/*
 * =====================================================================================
 *
 *       Filename:  main.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017년 07월 06일 07시 20분 19초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hobum (Vincent) Kwon (mn), hobum.kwon@gmail.com
 *        Company:  Samsung Electornics
 *
 * =====================================================================================
 */

#include <iostream>
#include <vector>

/*
 * if n nodes, then n! combination path possible. Of course A B C ... only feasible A->B->C exists
 * 
 * check hamiltonial circle by checking outbound, inbound 
 *
 * except start, end nodes, all oubound == inbound
 *
 * start has 1 difference and end -1 different 
 *
 * so plus1++, minus1++ if (plus1 == 1 && minux1 == 1 || plus1 == 0 && minus1 == 0)
 * 
 */
using namespace std;

int array[5][5] = {
 {0,1,0,1,0},
 {1,0,1,1,1},
 {0,1,0,0,1},
 {1,1,0,0,1},
 {0,1,1,1,0},
};

void getEulerCircuit(int here, vector<int>& circuit) {
  for (int i = 0; i < 5; i++) {
    while (array[here][i] > 0) {
      array[here][i]--;
      array[i][here]--;
      getEulerCircuit(i, circuit);
    }
  }
  circuit.push_back(here);
}

void printSolution(int path[]) {
  cout << "Solution exists" << endl;
  for (int i = 0; i < 5; i++) cout << path[i]  << " ";
  cout << path[0] << endl;
}

bool isSafe(int v, int s[5][5], int path[], int pos) {
  if (s[path[pos-1]][v] == 0) return false;
  for (int i = 0; i < pos; i++) {
    if (path[i] == v) return false;
  }
  return true;
}

bool hamCycleUtil(int s[5][5], int path[], int pos) {
  if (pos == 5) {
    if (s[path[pos-1]][path[0]] == 1) {
      return true;
    }
    else return false;
  }

  for (int v = 1; v < 5; v++) {
    if (isSafe(v, s, path, pos)) {
      path[pos] = v;

      if (hamCycleUtil(s, path, pos+1) == true) {
        return true;
      }

      path[pos] = -1;
    }
  }
  return false;
}

bool hamCycle(int s[5][5]) {
  int *path = new int[5];
  for (int i = 0; i < 5; i++) {
    path[i] = -1;
  }
  path[0] = 0;
  if ((hamCycleUtil, s, path, 1) == false) {
    cout << "Solution does not exist..." << endl;
    return false;
  }
  printSolution(path);
  return true;
}

int main() {
#if 0
  vector<int> circuit;
  getEulerCircuit(0, circuit);
  
  for (auto i : circuit) cout << i << " " << endl;
#endif
  // other way
  hamCycle(array);
  return 0;
}
