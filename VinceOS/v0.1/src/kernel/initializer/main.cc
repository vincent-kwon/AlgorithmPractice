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
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include "../utility/timestamper.h"

using namespace std;

union semun {
  int val;
  struct semid_ds *buf;
  unsigned short int *array;
  struct seminfo *__buf;
};

void* create_shared_memory(size_t size) {
  int protection = PROT_READ | PROT_WRITE;
  int visibility = MAP_ANONYMOUS | MAP_SHARED;
  return mmap(NULL, size, protection, visibility, 0,0);
}

int binary_semaphore_allocation (key_t key, int sem_flags)
{
  return semget (key, 1, sem_flags);
}

int binary_semaphore_deallocate (int semid)
{
  union semun ignored_argument;
  return semctl (semid, 1, IPC_RMID, ignored_argument);
}

int binary_semaphore_initialize (int semid)
{
  union semun argument;
  unsigned short values[1];
  values[0] = 1;
  argument.array = values;
  return semctl (semid, 0, SETALL, argument);
}

int binary_semaphore_wait (int semid)
{
  struct sembuf operations[1];
  operations[0].sem_num = 0;
  operations[0].sem_op = -1;
  operations[0].sem_flg = SEM_UNDO;
  return semop (semid, operations, 1);
}

int binary_semaphore_post (int semid)
{
  struct sembuf operations[1];
  operations[0].sem_num = 0;
  operations[0].sem_op = 1;
  operations[0].sem_flg = SEM_UNDO;
  return semop (semid, operations, 1);
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
