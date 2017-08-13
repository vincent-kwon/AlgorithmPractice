/*
 * =====================================================================================
 *
 *       Filename:  main.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017년 08월 11일 22시 01분 39초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hobum (Vincent) Kwon (mn), hobum.kwon@gmail.com
 *        Company:  Samsung Electornics
 *
 * =====================================================================================
 */
#include <iostream>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>
#include "Process.h"
#include <stdio.h>
#include "../utility/timestamper.h"

using namespace std;

void* create_shared_memory(size_t size) {
  int protection = PROT_READ | PROT_WRITE;
  int visibility = MAP_ANONYMOUS | MAP_SHARED;
  return mmap(NULL, size, protection, visibility, 0,0);
}

int main() {
  Process p;
  char parent_message[256] = "Hello";
  char child_message[256] = "goodbye";
  void * shmem = create_shared_memory(128);
  cout << "size of char* : " << sizeof(child_message) << endl;

  Timestamper ts;

  ts.enter("1");  
  memcpy(shmem, parent_message, 256);
  ts.exit("1");

  int pid = fork();
  if (pid == 0) {
    cout << "child read: " << static_cast<char*>(shmem) << endl;
    memcpy(shmem, child_message, 256);
  }
  else {
    //cout << "parent read: " << static_cast<char*>(shmem) << endl;
    printf("Parent read: %s\n", (char*)shmem);
    sleep(1);
    cout << "After 1s parent read: " << static_cast<char*>(shmem) << endl;
  }
#if 0
  cout << "[main] what main system init may need ?? " << endl;
  cout << "Initialize scheduler/process manager... " << endl;
  cout << "Initialize memory manager... " << endl;
  cout << "Initialize file manager... " << endl;
  p.info();
  cout << "[main] end...." << endl;
#endif
  return 0;
}
