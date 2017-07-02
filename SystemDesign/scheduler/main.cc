/*
 * =====================================================================================
 *
 *       Filename:  main.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017년 07월 02일 04시 16분 06초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hobum (Vincent) Kwon (mn), hobum.kwon@gmail.com
 *        Company:  Samsung Electornics
 *
 * =====================================================================================
 */
#include <iostream>

#include <unistd.h>
#include <stdio.h>
#include "scheduler.h"

using namespace std;

void test_func_one(void *context) {
  int i = 0; 
  cout << "XXXXXXXXXXXXXXXXX FUCK " << endl;
  while (true) {
    i++;
    cout << " task one is running......" << endl;
    printf("Task 1: %5d\n", i);
    sleep(1);
    if (i == 15) {
      break;
    }
  }
}

void test_func_two(void* context) {
  int i = 500;
  while (true) {
    i = i + 10;
    printf("Task : %3d\n", i);
    sleep(1);
    if (i == 600) {
      break;
    }
  }
}

void test_func_three(void *context) {
  int i = 1000;

  while (true) {
    i++;
    printf("\n\n\n\nTask 3: %4d\n", i);
    sleep(1);
    if (i == 1005) {
      break;
    }
  }
}

int main(void) {
  thread_init();
  thread_create(test_func_one, NULL);
  //thread_create(test_func_two, NULL);
  //thread_create(test_func_three, NULL);
  thread_wait();
  return 0; 
}
