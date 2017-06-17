/*
 * =====================================================================================
 *
 *       Filename:  doublelist.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017년 06월 11일 20시 51분 14초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hobum (Vincent) Kwon (mn), hobum.kwon@gmail.com
 *        Company:  Samsung Electornics
 *
 * =====================================================================================
 */

#include <iostream>
using namespace std;

class Node {
 public:
   int _value;
   Node* _next;
   Node(int value, Node* next) : _value(value), _next(next) {

   };
   ~Node() {
     cout << "Dispose !! " << _value << endl;
   };
 private:
};

class List {
 public:
  Node* _head;

  List() : _head (NULL) {
    
  };

  ~List() {
  };

  void Add(Node* node) {
    if (_head != NULL) {
      node->_next = _head;
      _head = node;
    }
    else _head = node;
  };
  void Print() {
    Node* tmp = _head;

    if (tmp == NULL) cout << "Empty !!!" << endl;

    while (tmp != NULL) {
      cout << tmp->_value << " , ";
      tmp = tmp->_next;
    }
    cout << "" << endl;
  }; 
  
  void Remove(int value) {
    if (_head == NULL) return;
    Node* tmp = _head;
    Node* prv = NULL;

    while (tmp != NULL) {
      if (tmp->_value == value) {
        if (tmp == _head) {
          _head = tmp->_next;
        }
        else if (tmp->_next == NULL) {
          prv->_next = NULL; 
        }
        else {
          prv->_next = tmp->_next;
        }
        delete tmp;
        break;
        // if tail
      }
      else {
        prv = tmp;
        tmp = tmp->_next;
      }
    }
  };
 private:
};

int main() {
  List* l =  new List();
  l->Add(new Node(100, NULL));
  l->Add(new Node(200, NULL));
  l->Add(new Node(300, NULL));
  l->Print();
  l->Remove(200);
  l->Print();
  l->Remove(100);
  l->Print();
  l->Remove(300);
  l->Print();
  return 0; 
}
