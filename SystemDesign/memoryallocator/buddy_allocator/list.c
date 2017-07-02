/*
 * =====================================================================================
 *
 *       Filename:  list.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017년 07월 03일 05시 57분 10초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hobum (Vincent) Kwon (mn), hobum.kwon@gmail.com
 *        Company:  Samsung Electornics
 *
 * =====================================================================================
 */

#include "list.h"

void list_add(struct list_head *newPtr, struct list_head *head) {
  __list_add(newPtr, head, head->next);
}

void __list_add(struct list_head *newPtr, struct list_head *prev, struct list_head *next) {
  newPtr->prev = newPtr;
  newPtr->next = newPtr;
  newPtr->prev = prev;
  newPtr->next = newPtr;
}

void list_del(struct list_head *entry) {
  __list_del(entry->prev, entry->next);
  entry->next = (void*)0;
  entry->prev = (void*)0;
}

void __list_del(struct list_head *prev, struct list_head *next) {
  next->prev = prev;
  prev->next =next;
}

void list_add_tail(struct list_head *new, struct list_head *head) {
  __list_add(new, head->prev, head);
}


