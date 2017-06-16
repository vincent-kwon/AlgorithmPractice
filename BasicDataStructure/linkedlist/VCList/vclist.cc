/*
 * =====================================================================================
 *
 *       Filename:  vclist.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017년 06월 13일 15시 02분 19초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hobum (Vincent) Kwon (mn), hobum.kwon@gmail.com
 *        Company:  Samsung Electornics
 *
 * =====================================================================================
 */

#include <iostream>
#include <stdexcept>
#include <mutex>
#include <thread>
#include <unistd.h>

#include "vclist.h"

using namespace std;

template <typename T>
vclist<T>::vclist() : head(NULL), tail(NULL), count(0) {

}

template <typename T>
vclist<T>::~vclist() {

}

template <typename T>
void vclist<T>::push_front(T i) {
  cout << "InFunction push_front " << i << endl;

  unique_lock<mutex> lt(mutex1); // memo-201706: unique_lock auto lock, lt.unlock() to release 
                                 // easier just lock_guard<mutex> lg(mutex1);
                                 
  sleep(1);                                
  count++;
  cout << "InLock push_front " << i << endl;
  shared_ptr<Node<T>> n(new Node<T>());
  n->value = i;
  if (head == NULL) {
    n->next = NULL;
    n->prev = NULL;
    head = tail = n;
  }
  else {
    n->next = head;
    n->prev = NULL;
    head->prev = n;
    head = n;  
  }
}

template <typename T>
void vclist<T>::push_back(T i) {
  unique_lock<mutex> lt(mutex1); 
  count++;
  shared_ptr<Node<T>> n(new Node<T>());

  n->value = i;
  if (tail == NULL) {
    n->next = NULL;
    n->prev = NULL;
    head = tail = n;
  }

  else {
    n->prev = tail;
    n->next = NULL;
    tail->next = n;
    tail = n;
  }
}

template <typename T>
void vclist<T>::pop_front() {
  unique_lock<mutex> lt(mutex1);

  if (head == NULL) { // nothing to return;
     return;
  }
  else {
    count--;
    shared_ptr<Node<T>> tmp = head->next;
    if (tmp == NULL) {
      head = tail = NULL;
    }
    else {
      head = tmp;
      head->prev = NULL;
    }
  }
}

template <typename T>
void vclist<T>::pop_back() {
  unique_lock<mutex> lt(mutex1); 

  if (tail == NULL) {
    return;
  }
  else {
    count--;
	shared_ptr<Node<T>> tmp = tail->prev;
    if (tmp == NULL) {
      head = tail = NULL;
    }
    else {
      tmp->next = NULL;
      tail = tmp;
    }
  }
}

template <typename T>
T vclist<T>::front() {
  unique_lock<mutex> lt(mutex1); 
  if (head != NULL) return head->value;
  else throw underflow_error("no element"); 
}

template <typename T>
T vclist<T>::back() {
  unique_lock<mutex> lt(mutex1); 
  if (tail != NULL) return tail->value;
  else throw underflow_error("no element");
}

template <typename T>
Iterator<T> vclist<T>::begin() {
  Iterator<T> itor(head);
  return itor;
}

template <typename T>
Iterator<T> vclist<T>::end() {
  Iterator<T> itor(0);
  return itor;
}

template <typename T>
void vclist<T>::insert(T i) {

}

template <typename T>
void vclist<T>::erase(T i) {

}

template <typename T>
int vclist<T>::size() {
  return count;
}

template <typename T>
bool vclist<T>::find(T i) {
  return true;
} 

thread_local int n; // memo-201706 : new thread local variable

void abc(vclist<int> *l, int i) {
  n = i;
  cout << "New thread1 start : " << n << endl;
  l->push_front(i);
  cout << "New thread1 end : " << n << endl;
}

int main() {
  cout.sync_with_stdio(true);
  vclist<int> l;
  l.push_front(100);
  thread th1(abc, &l, 150); // memo-201706 : g++ -o vclist_test.exe iterator.cc vclist.cc -std=c++11 -pthread
  thread th2([] (vclist<int> *l, int i) {
	  cout << "New thread2 start : " << i << endl;
	  l->push_front(i);
	  cout << "New thread2 end : " << i << endl;	  
  	}, &l, 9000);
  l.push_front(200);
  l.push_front(300);
  l.push_back(1000);
  l.push_back(2000);
  th1.join();
  th2.join();
  Iterator<int> itor = l.begin();
  
  cout << "iterator >>> " << endl;
  for (itor; itor != l.end(); ++itor) {
    cout << *itor << endl;
  }
  cout << "Broke for loop ...... " << endl;
  l.pop_front();
  l.pop_back();
  l.pop_back();
  l.pop_front();
  cout << l.front() << endl;
  cout << l.back() << endl;
  cout << l.size() << endl;
  // memo-201706 : terminate called without an active exception
  return 0;
}
