#include <iostream>

using namespace std;

typedef enum NodeOrder__ {
  PRE_ORDER, IN_ORDER, POST_ORDER
} NodeOrder;

template <typename T>
class Node {
 public:
  T value1;
  T value2;
  Node *leftChild;
  Node *rightChild;
};

template <typename T>
class Tree {
 public:
  Tree() : root(NULL) { 

  }

  virtual ~Tree() { 

  }
  
  bool Add(T t) { 
  	Node<T>* n = new Node<T>();
	n->value1 = t;

	Node<T>*tmp = root;

	if (tmp == NULL) {
		root = n;
		return true;
	}
	else {
		while (tmp != NULL) {
			if (tmp->value1 == n->value1) return false;
			else {
				if (tmp->value1 > n->value1) {
					if (tmp->leftChild == NULL) {
						tmp->leftChild = n;
						cout << "Add " << t << " left of " << tmp->value1 << endl;
						return true;
					}
                    else {
						tmp = tmp->leftChild;
                    }
				}
				else {
		        	if (tmp->rightChild == NULL) {
						tmp->rightChild = n;
						cout << "Add " << t << " right of " << tmp->value1 << endl;
						return true;
					}
					else {
						tmp = tmp->rightChild;
					}
				}
			}
		}
		return false;
	}
  }
  
  bool Remove(T t) { 
  	return true; 
  }
  
  Node<T>* Find(T t, bool bfs_prefered) 
  { 
  	return NULL; 
  }
  void Traverse(bool bfs_preferered, NodeOrder nodeOrder) { 
  	if (bfs_preferered) {
  	}
	else {
		Traverse_DFS(nodeOrder);
	}
  }
 protected:
  Node<T> *root;
  void Visit_DFS(Node<T> *n, NodeOrder nodeOrder) {
	  if (n == NULL) return;

	  if (nodeOrder == PRE_ORDER) cout << n->value1 << endl;
	  if (n->leftChild != NULL) Visit_DFS(n->leftChild, nodeOrder);
  	  if (nodeOrder == IN_ORDER) cout << n->value1 << endl;
	  if (n->rightChild != NULL) Visit_DFS(n->rightChild, nodeOrder);
      if (nodeOrder == POST_ORDER) cout << n->value1 << endl;
  }
  void Traverse_DFS(NodeOrder nodeOrder) { 
	Visit_DFS(root, nodeOrder);
  }
 private:
 	
};

int main() {
  Tree<int> t;
  t.Add(300);
  t.Add(200);
  t.Add(100);
  t.Add(500);
  t.Add(400);
  t.Add(600);
  t.Traverse(false, POST_ORDER);
  return 0;
}

