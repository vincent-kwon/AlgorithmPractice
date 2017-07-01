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

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <setjmp.h>
#include <malloc.h>
#include <memory.h>
#include <sys/time.h>
#include "schedule.h"

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

TaskInfo task_get_runningtask();

void task_insert(TaskInfo taskinfo);
void task_delete(TaskInfo taskinfo);
void task_next();
void scheduler();
void parent_task();

TaskInfo thread_creae(TaskFunc callback, void *context) {
  TaskInfo taskinfo;
  taskinfo = malloc(sizeof(*taskinfo));
  memset(taskinfo, 0x00, sizeof(*taskinfo));

  {
    struct frame *f = (struct frame *)&taskinfo->stack[THREAD_STACKSIZE - sizeof (struct frame)/4];
    int i;
    for (i = 0; i < THREAD_STACKSIZE; i++) {
      taskinfo->stack[i] = i;
    }
    memset(f, 0, sizeof(struct frame));
    f->retaddr = (unsigned long) callback;
    f->retaddr2 = (usingned long) thread_kill;
    f->data = (unsigned long) context;
    taskinfo->sp = (unsigned long)&f->flags;
    f->ebp = (unsigned long)&f->eax;
  }
}
