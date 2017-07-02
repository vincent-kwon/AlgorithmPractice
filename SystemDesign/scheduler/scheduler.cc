/*
 * =====================================================================================
 *
 *       Filename:  scheduler.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017년 07월 01일 17시 47분 07초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hobum (Vincent) Kwon (mn), hobum.kwon@gmail.com
 *        Company:  Samsung Electornics
 *
 * =====================================================================================
 */

// TODO: how to get highest priority of queue with O(1) time? 
// each CPU has active and expired bit map ???? Need to understand it

#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <setjmp.h>
#include <malloc.h>
#include <memory.h>
#include <sys/time.h>
#include "scheduler.h"

using namespace std;

struct frame {
  unsigned long flags;
  unsigned long ebp;
  unsigned long edi;
  unsigned long esi;
  unsigned long edx;
  unsigned long ecx;
  unsigned long ebx;
  unsigned long eax;
  unsigned long retaddr;
  unsigned long retaddr2;
  unsigned long data;
};

typedef struct sch_handle_tag {
  int child_task;
  TaskInfo running_task;
  TaskInfo root_task;
} SchHandle;

SchHandle gh_sch;

unsigned long spsave, sptmp;

TaskInfo task_get_runningtask();

void task_insert(TaskInfo taskinfo);
void task_delete(TaskInfo taskinfo);
void task_next();
void scheduler();
void parent_task(void *context);

TaskInfo thread_create(TaskFunc callback, void *context) {
  cout << "create thread...." << endl;
  TaskInfo taskinfo;
  taskinfo = (TaskInfo) malloc(sizeof(*taskinfo));
  memset(taskinfo, 0x00, sizeof(*taskinfo));

  {
    struct frame *f = (struct frame *)&taskinfo->stack[THREAD_STACKSIZE - sizeof (struct frame)/4];
    int i;
    for (i = 0; i < THREAD_STACKSIZE; i++) {
      taskinfo->stack[i] = i;
    }
    memset(f, 0, sizeof(struct frame));
    f->retaddr = (unsigned long) callback;
    f->retaddr2 = (unsigned long) thread_kill;
    f->data = (unsigned long) context;
    taskinfo->sp = (unsigned long)&f->flags;
    f->ebp = (unsigned long)&f->eax;
  }

  gh_sch.child_task++;
  taskinfo->task_id = gh_sch.child_task;
  taskinfo->status = TASK_READY;
  task_insert(taskinfo);
  return taskinfo;
}
 
void thread_init() {
  gh_sch.root_task = NULL;
  gh_sch.running_task = NULL;
  gh_sch.child_task = 0; 
  thread_create(parent_task, NULL); 
}


void thread_switch() {
  asm("pushl %eax");
  asm("pushl %ebx");
  asm("pushl %ecx");
  asm("pushl %edx");
  asm("pushl %esi");
  asm("pushl %edi");
  asm("pushl %ebp");
  asm("pushl %ebp");

  asm("movl %esp, spsave");

  gh_sch.running_task->sp = spsave;

  scheduler();

  sptmp = gh_sch.running_task->sp;

  asm("movl sptmp, %esp");

  asm("popl %ebp");
  asm("popl %ebp");
  asm("popl %edi");
  asm("popl %esi");
  asm("popl %edx");
  asm("popl %ecx");
  asm("popl %ebx");
  asm("popl %eax");
}

void scheduler(void) {
  TaskInfo task;
  task = task_get_runningtask();
  cout << "scheduler is running " << endl;
  switch(task->status) {
    case TASK_RUN:
    case TASK_SLEEP:
      cout <<" now running" << endl;
      break;
    case TASK_KILL:
      cout <<" delete task " << endl;
      task_delete(task);
      scheduler();
      break;
    case TASK_YIELD:
      task->status = TASK_RUN;
      break;
    case TASK_READY:
      task->status = TASK_RUN;
      break;
  }
  // above make all ready to run 
  // however actual scheduler will not work in this way.
  // and task_next is round robin implementation.
  // this should be pluggable so other schedule policy can be applied
  task_next();
}

void thread_wait() {
  parent_task(NULL);
}

void thread_kill() {
  TaskInfo task;
  task = task_get_runningtask();
  task->status = TASK_KILL;
  thread_switch();
}

void thread_switch_caller(int i) {
  cout <<"Signal heandler called............................." << endl;
  thread_switch();
}
void parent_task(void *context) {
  cout << "Enter parent task ...." << endl;
  struct sigaction act;
  sigset_t masksets;
  pid_t pid;

  sigemptyset(&masksets); // sigfillset is to block everything
  act.sa_handler = thread_switch_caller;
  act.sa_mask = masksets;
  act.sa_flags = SA_NODEFER; // SA_NOMASK is not to block while handling received signal
 
  sigaction(SIGUSR1, &act, NULL);
 
  if ( (pid = fork()) == 0) {
    while (1) {
      sleep(1);
      cout << "In child: kill to " << getppid() << endl;
      kill(getppid(), SIGUSR1);
    }
  }
  else {
    while (1) {
      if (gh_sch.child_task == 1) {
        kill(pid, SIGINT);
        break;
      }
    };
  }
}

void task_insert(TaskInfo taskinfo) {
  // tasks has linked list to next
  if (gh_sch.root_task == NULL) {
    gh_sch.root_task = taskinfo; // root <-> taskinfo 1 <-> taskinfo 2....... 
    gh_sch.running_task = taskinfo;
  }
  else {
    TaskInfo temp;
    temp = gh_sch.root_task; // from root, go to end of task info list
    while (temp->next != NULL) {
      temp = temp->next;
    }
    temp->next = taskinfo; // add to the last
    taskinfo->prev = temp;
  }
}

TaskInfo task_get_runningtask(void) {
  return gh_sch.running_task;
}

// TODO: now it is just searching next in the task linked list
void task_next(void) {
  TaskInfo temp;
  temp = gh_sch.running_task;
  cout <<"change running_task in task_next "<< endl;
  if (temp->next != NULL) {
    gh_sch.running_task = temp->next;
  }
  else { // if null, go back to root task
    gh_sch.running_task = gh_sch.root_task;
  }
  cout << " running task now :" << gh_sch.running_task << endl;
}

void task_delete(TaskInfo taskinfo) {
  TaskInfo temp = taskinfo->prev;
  if (gh_sch.root_task == taskinfo) {
    gh_sch.root_task = NULL;
    gh_sch.running_task = NULL;
    gh_sch.child_task = 0;
  }
  else {
    temp->next = taskinfo->next;
    // handle running task
    if (taskinfo == gh_sch.running_task) {
      if (temp->next != NULL) { // if the task to delete has next, make this task running
        (taskinfo->next)->prev = temp;
        gh_sch.running_task = temp->next;
      }
      else {
        gh_sch.running_task = temp; // if no task after this, then make previous task to be allocated
      }
      gh_sch.child_task--;
    }
  }
  free(taskinfo);
}
