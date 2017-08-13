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
#include <exception>
#include <stdexcept>
#include <fcntl.h>
#include <semaphore.h>
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
#if 0
int binary_semaphore_allocation(key_t key, int sem_flags)
{
  return semget (key, 1, sem_flags);
}

int binary_semaphore_deallocate(int semid)
{
  union semun ignored_argument;
  return semctl (semid, 1, IPC_RMID, ignored_argument);
}

int binary_semaphore_initialize(int semid)
{
  union semun argument;
  unsigned short values[1];
  values[0] = 1;
  argument.array = values;
  return semctl(semid, 0, SETALL, argument);
}

int binary_semaphore_wait(int semid)
{
  struct sembuf operations[1];
  operations[0].sem_num = 0;
  operations[0].sem_op = -1;
  operations[0].sem_flg = SEM_UNDO;
  cout << "just before semaphore wait...." << endl;
  return semop(semid, operations, 1);
}

int binary_semaphore_post (int semid)
{
  struct sembuf operations[1];
  operations[0].sem_num = 0;
  operations[0].sem_op = 1;
  operations[0].sem_flg = SEM_UNDO;
  cout << "just before semaphore post..." << endl;
  return semop(semid, operations, 1);
}
#endif

int main() {
  Process p;
  char parent_message[256] = "Hello";
  char child_message[256] = "goodbye";
  void * shmem = create_shared_memory(128);
  Timestamper ts;

  ts.enter("1");  
  memcpy(shmem, parent_message, 256);
  ts.exit("1");
#if 0
  int sem_id = binary_semaphore_allocation(IPC_PRIVATE, IPC_CREAT | 0666);
  binary_semaphore_initialize(sem_id);
#endif
  // semaphore with shared memory
  sem_t *sema = (sem_t*)mmap(NULL, sizeof(*sema), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0); // memo-20170812: -1? 0?
  if (sema == MAP_FAILED) throw runtime_error("semaphore map failed");
  if (sem_init(sema, 1, 0) < 0) throw runtime_error("semaphore init failed");
  int nloop = 10;

  int pid = fork();
  if (pid == 0) {
    cout << "[child] shared memory read:" << static_cast<char*>(shmem) << endl;
    memcpy(shmem, child_message, 256);
    sleep(1);
#if 0
    binary_semaphore_wait(sem_id);
#endif
    for (int i = 0; i < nloop; i++) {
      cout << "[child] unlock semaphore: " << i << endl;
      if (sem_post(sema) < 0) throw runtime_error("post error");
      sleep(1);
    }
  }
  else {
    printf("[parent] shared memory read: %s\n", (char*)shmem);
    sleep(1);
    cout << "[parent] shared memory read after sleep:" << static_cast<char*>(shmem) << endl;
#if 0
    binary_semaphore_post(sem_id);
#endif
    for (int i = 0; i < nloop; i++) {
      if (sem_wait(sema) < 0) throw runtime_error("parent wait error");
      cout << "[parent] waked up at " << i << endl;
    }
    if (sem_destroy(sema) < 0) throw runtime_error("sem destroy failed");
    if (munmap(sema, sizeof(sema)) < 0) throw runtime_error("munmap failed");
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
