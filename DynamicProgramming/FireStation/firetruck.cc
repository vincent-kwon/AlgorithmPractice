/*
 * =====================================================================================
 *
 *       Filename:  firetruck.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016년 11월 24일 17시 28분 47초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hobum (Vincent) Kwon (mn), hobum.kwon@gmail.com
 *        Company:  Samsung Electornics
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int V, E, N, M;
#define V_SIZE 1001
#define VC_MAX 987654321
#define VC_INVALID -1

int Map[V_SIZE][V_SIZE];
int Dik[V_SIZE];

int H_array[V_SIZE]; 
int F_array[V_SIZE]; 

void addElement(vector<int>& Set, int num) {
  Set.push_back(num);
  for (int i = 1; i <= V; i++) {
    if (Map[num][i] != VC_MAX && (Dik[i] > (Dik[num]+Map[num][i]))) {
      Dik[i] = Dik[num] + Map[num][i];
    }
  }
}

bool isSet(vector<int> &Set, int num) {
  for (int i = 0; i < Set.size(); i++) {
    if (Set[i] == num) return true;
  }
  return false;
}

int getMinFromNode(vector<int>&Set, int num) {
  int minValue = VC_MAX;
  int minNode = VC_INVALID;
  
  for (int i = 1; i <= V; i++) {
    if (Map[num][i] != VC_MAX && !isSet(Set,i) && (minValue > Dik[i])) {
      minValue = Dik[i];
      minNode = i;
    }
  }
  return minNode;
}

int getNextVisit(vector<int>& Set) {
  int minValue = VC_MAX;
  int minNode = VC_INVALID;

  for (int i = 0; i < Set.size(); i++) {
    int tmp = getMinFromNode(Set, Set[i]);   
    if (tmp != VC_INVALID) {
      if (minValue > Dik[tmp]) {
        minValue = Dik[tmp];
        minNode = tmp;
      }
    }
  }

  return minNode;
}

bool isFinished(vector<int>& Set) {
  for (int i = 0; i < N; i++) {
    if (find(Set.begin(), Set.end(), H_array[i]) == Set.end()) {
      return false;
    }
  }
  return true;
}

int dikstra(int start) {
  int ret;
  vector<int> Set;
  Dik[start] = 0;
  addElement(Set, start);

  while (!isFinished(Set)) {
    int nextNode = getNextVisit(Set);
    if (nextNode == VC_INVALID) {
      return -1;
    }
    else {
      addElement(Set, nextNode);
    }
  }
  return 0;
}

void dikstra2(int start) {
  int min;
  int i,j,v;
  int visited[V_SIZE] = {0, };
  Dik[start] = 0;
  for (i = 1; i <= V; i++) {
    min = VC_MAX;
    for (j = 1; j <= V; j++) {
      if (visited[j] == 0 && min > Dik[j]) {
        min = Dik[j];
        v = j;
      }
    }
    visited[v] = 1;
    for (j = 1; j <= V; j++) {
      if (Dik[j] > Dik[v] + Map[v][j]) {
        Dik[j] = Dik[v] + Map[v][j];
      }
    }
  } 
}

int main() {
  freopen("input.txt", "r", stdin);
  int test;
  cin >> test;

  while (test-- > 0) {
    cin >> V;
    cin >> E;
    cin >> N;
    cin >> M;

    for (int i = 0; i <= V; i++) {
      Dik[i] = VC_MAX;
      for (int j = 0; j <= V; j++) {
        Map[i][j] = VC_MAX; 
      }
    }      
 
    for (int i = 0; i < E; i++) {
      int s, e, c;
      cin >> s;
      cin >> e;
      cin >> c;
      Map[s][e] = c;
      Map[e][s] = c;
    }

    for (int i = 0; i < N; i++) cin >> H_array[i];

    for (int i = 0; i < M; i++) cin >> F_array[i];

    // add 0 to all House
    for (int i = 0; i < M; i++) Map[0][F_array[i]] = 0;

    dikstra2(0);

    int ret = 0;

    for (int i = 0; i < N; i++) {
      ret += Dik[H_array[i]];
    }
    cout << "r: " << ret << endl;
  }
  return 0;
}
