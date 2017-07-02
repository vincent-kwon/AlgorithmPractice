/*
 * =====================================================================================
 *
 *       Filename:  scheduler.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017년 07월 02일 01시 14분 52초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hobum (Vincent) Kwon (mn), hobum.kwon@gmail.com
 *        Company:  Samsung Electornics
 *
 * =====================================================================================
 */

#ifndef SCHEDULER_H
#define SCHEDULER_H

#define THREAD_STACKSIZE 1024

typedef enum {
  TASK_READY = 0,
  TASK_RUN,
  TASK_YIELD, 
  TASK_SLEEP,
  TASK_KILL
} TaskStatus;

typedef struct TaskInfo_ {
  unsigned long stack[THREAD_STACKSIZE];
  unsigned long sp;
  int task_id;
  TaskStatus status;
  struct TaskInfo_ *next;
  struct TaskInfo_ *prev;
} *TaskInfo;

typedef void (*TaskFunc)(void *context);

TaskInfo thread_create(TaskFunc callback, void *context);

void thread_init(void);
void thread_wait(void);
void thread_uninit(void);
void thread_switch(void);
void thread_kill(void);

#endif
