/*
 * =====================================================================================
 *
 *       Filename:  ListGraph.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017년 06월 13일 04시 54분 27초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hobum (Vincent) Kwon (mn), hobum.kwon@gmail.com
 *        Company:  Samsung Electornics
 *
 * =====================================================================================
 */

#include <iostream>
#include <queue>
#include <list>
#include <stdexcept>
#include <algorithm>
#include <vector>

using namespace std;

class Edge;

class Node {
 public:
	int value;
	int visited;
	list<Edge> edgeList;
};

class Edge {
 public: 
	int weight;
	int toNodeNum;
	int fromNode;
	int accumulate;
};

class ListGraph {
 public:
   ListGraph(int node_count) : _max_bucket(node_count) {
     if (node_count == 0) throw invalid_argument("zero is not allowed");
	 //nodeArray.resize(node_count); // memo-201706: resize reserve and more importantly create a default object in each reserved area
	 cout << nodeArray.size() << endl;
   }

   virtual ~ListGraph() {
   }

   void printBucket(int h) {

   }
 
   void addNode(Node& nodeRef) {
	   nodeArray.push_back(nodeRef);
	   cout << nodeArray.back().value << endl; // memo-201706 : Truth: nodeArray[no] == *(nodeArray + no)
   }

  vector<Node> nodeArray;

  void resetAllNotVisited() {
	  vector<Node>::iterator itor = nodeArray.begin();
	  for (itor; itor != nodeArray.end(); itor++) {
		  itor->visited = 0;
	  }
  }

  void visitDFS(Node &n) {

	  if (n.visited == 0) return;
	  else {
		  n.visited = 2;
		  cout << "[visitDFS] n value: " << n.value << endl;
		  // start visit
		  list<Edge>::iterator itor = n.edgeList.begin();
		  for (itor; itor != n.edgeList.end(); itor++) {
			  if (nodeArray[itor->toNodeNum].visited != 0) continue;
			  else {
				  visitDFS(nodeArray[itor->toNodeNum]);
			  }
		  }
	  }
  }

  void visitBFS(int n) {
	  Node* tmp = &nodeArray[n];
	  queue<Node*> q;
	  q.push(tmp);

	  while (!q.empty()) {
		  Node* n = q.front();
		  q.pop();
		  if (n->visited == 2) continue; // if already visited
		  else {
			  cout << "visit:" << n->value << endl;
			  n->visited = 2;
			  list<Edge>::iterator itor = n->edgeList.begin();
			  for (itor; itor != n->edgeList.end(); itor++) {
				  if (nodeArray[itor->toNodeNum].visited == 0) {
					  //cout << "non visit:" << nodeArray[itor->toNodeNum].value << endl;
					  nodeArray[itor->toNodeNum].visited = 1;
					  q.push(&nodeArray[itor->toNodeNum]);
				  }
			  }
		  }
	  }
  }

  void traverseDFS(int startNode) {
	  resetAllNotVisited();
	  visitDFS(nodeArray[startNode]);
  }

  void traverseBFS(int startNode) {
	  resetAllNotVisited();
	  visitBFS(startNode);
  }
 private:
  int _max_bucket;
};

int main() {
  ListGraph lg(10);
  Node n;
  Edge e;
  n.value = 0;
  n.visited = false;

  // add node
  lg.addNode(n);
  n.value++;
  lg.addNode(n);
  n.value++;
  lg.addNode(n);
  n.value++;
  lg.addNode(n);

  e.weight = 1;
  e.accumulate = 0;

  // add edge
  e.fromNode = 0;
  e.toNodeNum = 1;
  lg.nodeArray[0].edgeList.push_back(e);
  e.toNodeNum = 2;
  lg.nodeArray[0].edgeList.push_back(e);

  e.fromNode = 1;
  e.toNodeNum = 2;
  lg.nodeArray[1].edgeList.push_back(e);
  e.toNodeNum = 3;
  lg.nodeArray[1].edgeList.push_back(e);

  e.fromNode = 2;
  e.toNodeNum = 1;
  lg.nodeArray[2].edgeList.push_back(e);
  e.toNodeNum = 3;
  lg.nodeArray[2].edgeList.push_back(e);

  e.fromNode = 3;
  e.toNodeNum = 0;
  lg.nodeArray[3].edgeList.push_back(e);

  for (int i = 0; i < 4; i++) {
	  list<Edge>::iterator itor = lg.nodeArray[i].edgeList.begin();
	  for (itor; itor != lg.nodeArray[i].edgeList.end(); itor++) {
		  cout << " Edge: from " << itor->fromNode << "," << itor->toNodeNum << endl;
	  }
  }

  lg.traverseDFS(3);

  cout << "Now BFS: " << endl;
  lg.traverseBFS(0);

  return 0;
}
