/*
 * =====================================================================================
 *
 *       Filename:  factory.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017년 06월 12일 05시 19분 19초
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

class Car 
{
  public:
    virtual void info() = 0;
};

class Ford : public Car {
  public:
    virtual void info() {
      cout << "Ford..." << endl;
    }
};

class Toyota : public Car {
  public:
    virtual void info() {
      cout << "Totyota" << endl;
    }
};

class CarFactory {
 public:
  CarFactory() {

  };
  Car* requestCar() {
    return createCar();
  }
 protected:
  virtual Car* createCar() = 0;
};

class FordCarFactory : public CarFactory {
 protected:
  virtual Car* createCar() {
    return new Ford();
  }
};

// memo_201706 : may provide build(string type) {
//   if (type == "Ford") {
//     return FordCarFactory().createCar();
//   }
// }
//
// or 
//  
// build(CarFactory cf) {
//   return cf.createCar();
// }
int main() {
  CarFactory* cf = new FordCarFactory();
  Car* car = cf->requestCar();
  car->info();
}
