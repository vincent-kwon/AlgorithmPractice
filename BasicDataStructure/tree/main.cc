#include <iostream>
#include <queue>

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


Node<int>* findPredicate(Node<int> *n, int  t);

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
						cout << "P {" << tmp  << "} Add " << t << " left of " << tmp->value1 << endl;
						return true;
					}
                    else {
						tmp = tmp->leftChild;
                    }
				}
				else {
		        	if (tmp->rightChild == NULL) {
						tmp->rightChild = n;
						cout << "P {" << tmp  << "} Add " << t << " right of " << tmp->value1 << endl;
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
  	// check if root

	// if leaf, easy

	// if has one child easy

	// if has two child find next big
  }
  
  Node<T>* Find(T t, bool bfs_prefered, Node<T>* (*fn)(Node<T> *n, T t)) 
  {
        Node<T>* res; 
        if (bfs_prefered) {

        }
        else {
          if ((res = Visit(root, PRE_ORDER, t, fn)) != NULL) return  res;
  	  return NULL; 
        }
  }
  void Traverse(bool bfs_preferered, NodeOrder nodeOrder) { 
  	if (bfs_preferered) {
  	    Traverse_BFS();
  	}
	else {
		Traverse_DFS(nodeOrder);
	}
  }
 protected:
  Node<T> *root;
  queue<Node<T>*> queueBfs;

  void Visit_BFS(Node<T> *n) {
      if (n == NULL) return;

      Node<T>* tmp = n;

      queueBfs.push(tmp);

      while (!queueBfs.empty()) {
        tmp = queueBfs.front(); 
        queueBfs.pop();
        cout << "BFS: " << tmp->value1 << endl;
        if (tmp->leftChild != NULL) queueBfs.push(tmp->leftChild);
        if (tmp->rightChild != NULL) queueBfs.push(tmp->rightChild);
      }
  }

  void Visit_DFS(Node<T> *n, NodeOrder nodeOrder) {

	  if (n == NULL) return;

	  if (nodeOrder == PRE_ORDER) cout << n->value1 << endl;
	  if (n->leftChild != NULL) Visit_DFS(n->leftChild, nodeOrder);
  	  if (nodeOrder == IN_ORDER) cout << n->value1 << endl;
 	  if (n->rightChild != NULL) Visit_DFS(n->rightChild, nodeOrder);
          if (nodeOrder == POST_ORDER) cout << n->value1 << endl;
  }

  Node<T>* Visit(Node<T> *n, NodeOrder nodeOrder, T t, Node<T>* (*fn)(Node<T> *n, T t)) {
          Node<T>* res = NULL;

          if (n == NULL) return NULL;

	  if (nodeOrder == PRE_ORDER) {
            if ((res = fn(n, t)) != NULL) {
              return res;
            }
          }

	  if (n->leftChild != NULL) {
            if ((res = Visit(n->leftChild, nodeOrder, t, fn)) != NULL) {
              return res;
            }
          }

  	  if (nodeOrder == IN_ORDER) {
            if ((res = fn(n, t)) != NULL) {
              return res;
            }
          }

	  if (n->rightChild != NULL) {
            if ((res = Visit(n->rightChild, nodeOrder, t, fn)) != NULL) {
              return res;
            }
          }

          if (nodeOrder == POST_ORDER) {
            if ((res = fn(n, t)) != NULL) {
              return res;
            }
          }
          return NULL;
  }

  void Traverse_DFS(NodeOrder nodeOrder) { 
	Visit_DFS(root, nodeOrder);
  }

  void Traverse_BFS() {
    Visit_BFS(root);
  }
 private:
 	
};
Node<int>* findPredicate(Node<int> *n, int  t) {
   if (n == NULL) return NULL;
   if (n->value1 == t) return n;
   else return NULL;
}

int main() {
  Tree<int> t;
  t.Add(300);
  t.Add(200);
  t.Add(100);
  t.Add(500);
  t.Add(400);
  t.Add(600);
  t.Traverse(true, POST_ORDER);

  Node<int>* res = t.Find(400, PRE_ORDER, findPredicate);
  cout << "400: " <<  res->value1 << ":" << res << endl;
  Node<int>* res2 = t.Find(300, PRE_ORDER, findPredicate);
  cout << "300: " << res2->value1 << ":" << res << endl;
  Node<int>* res3 = t.Find(100, PRE_ORDER, findPredicate);
  cout << "100: " << res3->value1 << ":" << res << endl;
  res3 = t.Find(500, PRE_ORDER, findPredicate);
  cout << "500: " << res3 << endl;

  //t.Traverse_BFS();
  return 0;
}

