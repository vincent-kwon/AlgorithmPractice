/*
 * =====================================================================================
 *
 *       Filename:  disconnectPoint.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017년 07월 04일 14시 05분 00초
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

using namespace std;

#define NODE_NUM 8

vector<vector<int> > adj;
vector<int> discovered; // should init to -1
vector<bool> isCutVertex; // should init to false

int counter = 0;

// return min value of counter from this node
int findCutVertex(int here, bool isRoot) { 
  discovered[here] = counter++; // increase counter 
  int ret = discovered[here]; // -1 initially
  int children = 0;

  for (int i = 0; i < adj[here].size(); ++i) {
    int there = adj[here][i]; // for all adjacent nodes
    if (discovered[there] == -1) { // if not yet visited (cached or not)
      ++children;
      int subtree = findCutVertex(there, false); // get min of counter
      if (!isRoot && subtree >= discovered[here]) isCutVertex[here] = true; // no upward connect
      ret = min(ret, subtree); // keep min as possible
    }
    else ret = min(ret, discovered[there]); // cached. 
  }
  if (isRoot) isCutVertex[here] = (children >= 2); // if root should check more than 1 to become cut vertex
  return ret;
}

int main() {
  discovered.resize(NODE_NUM);
  isCutVertex.resize(NODE_NUM);
  for (int i = 0; i < NODE_NUM; i++) {
    discovered[i] = -1;
    isCutVertex[i] = false;  
  }

  adj.resize(NODE_NUM);

  adj[0].push_back(1);

  adj[1].push_back(0);
  adj[1].push_back(2);
  adj[1].push_back(3);
  
  adj[2].push_back(1);
  adj[2].push_back(3);
  adj[2].push_back(5);

  adj[3].push_back(1);
  adj[3].push_back(2);
  adj[3].push_back(4);
  adj[3].push_back(5);

  adj[4].push_back(3);

  adj[5].push_back(2);
  adj[5].push_back(3);
  adj[5].push_back(6);
  adj[5].push_back(7);

  adj[6].push_back(5);
  adj[7].push_back(5);

  int r = findCutVertex(0,true);
  //cout << "cut vertex = " << r << endl;
  //
  for (int i = 0; i < NODE_NUM; i++) if (isCutVertex[i]) cout << i << endl;
  return 0;
}
