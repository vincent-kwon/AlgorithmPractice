/*
 * =====================================================================================
 *
 *       Filename:  main.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017년 06월 14일 23시 06분 53초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Dr. Fritz Mehner (mn), mehner@fh-swf.de
 *        Company:  FH Südwestfalen, Iserlohn
 *
 * =====================================================================================
 */

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable> // last_visit: condition variable
#include <unistd.h>

using namespace std;

int main()  {
  mutex mMutex;
  condition_variable mCondvar;
  
  // one producer
  thread th1([&] {
      int count = 10;
	  while (true) {
        cout << "[pdd] entering lock " << endl;
		unique_lock<mutex> lock(mMutex); // last_visit: unique_lock<mutex> lock(mMutex); 
		mCondvar.notify_all(); // last_visit: m.nofity_all
		count--;
		if (count < 0) break;
		lock.unlock();
		sleep(2);
	  	}});
  
  // one consumer
  thread th2([&] {
	  while (true) {
        cout << "[css] condwait.wait" << endl;
		unique_lock<mutex> lock(mMutex);
  	    mCondvar.wait(lock); // last_visit: condiva.wait(mutex)
  	    // if got here, notified
		cout << "[css] lock.unlock(); .... " << endl;
		cout << "[css] Consume:: take care of queue exclusively .... " << endl;
		lock.unlock();
  	}});
  th1.join();
  th2.join();
  return 0;
}:

