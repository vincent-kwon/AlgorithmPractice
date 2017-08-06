/*
 * =====================================================================================
 *
 *       Filename:  unique_ptr_second.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017년 08월 04일 03시 36분 11초
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
#include <memory>
#include <cstdio>
#include <fstream>
#include <cassert>
#include <functional>
using namespace std;

struct B {
  virtual void bar() { std::cout << "B::bar" << endl; }
  virtual ~B() = default; // TODO: default
};

struct D : B {
  D() { std::cout << "D::D" << endl; }
  ~D() { std::cout << "D::~D" << endl; }
  void bar() override { std::cout << "D::bar" << endl; }
};

template<typename T, typename... Ts> // ... in c++
unique_ptr<T> make_unique(Ts&&... params) { // && in c++
  return unique_ptr<T>(new T(forward<Ts>(params)...)); // forward in c++
}

std::unique_ptr<D> pass_through(std::unique_ptr<D> p) {
  p->bar();
  return p;
}

int main() {
  cout << "unique ownersip semantics demo" << endl;
  {
    auto p = make_unique<D>(); // easier
    auto q = pass_through(move(p)); // move to pass unique_ptr
    assert(!p); // assert in c++
    q->bar();
  }
  cout << "runtime polymorphism" << endl;
  {
    unique_ptr<B> p = make_unique<D>();
    cout << "Expect D" << endl;
    p->bar();
    vector<unique_ptr<B>> v;
    v.push_back(make_unique<D>());
    v.push_back(move(p));
    v.emplace_back(new D); // TODO: emplace_back ???
    cout << "now for loop....." << endl;
    cout << "expect: D, D, D " << endl;
    for (auto& p : v) p->bar();
  }
  cout << "custom deleter demo" << endl;
  ofstream("demo.txt") << 'x';
  {
    unique_ptr<FILE, decltype(&fclose)> fp(std::fopen("demo.txt", "r"), &std::fclose); // TODO: function reference for return
    if (fp) cout << fgetc(fp.get()) << endl;
  }

  cout << "custom lambda-expression delete demo" << endl;
  {
    unique_ptr<D, std::function<void(D*)>> p(new D, [](D* ptr) { // just anonimouse with this type : remeber function to be function pointer
      std::cout << "Destroying from a custom delete.... " << endl;
      delete ptr;
      });
    p->bar();
  }

  cout << "Array form of unique_ptr demo" << endl;
  {
    unique_ptr<D[]> p{new D[3]};
  }
  return 0;
}

