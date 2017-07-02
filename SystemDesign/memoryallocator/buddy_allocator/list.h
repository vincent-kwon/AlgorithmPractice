/*
 * =====================================================================================
 *
 *       Filename:  list.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017년 07월 03일 04시 10분 58초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hobum (Vincent) Kwon (mn), hobum.kwon@gmail.com
 *        Company:  Samsung Electornics
 *
 * =====================================================================================
 */

struct list_head {
  struct list_head* next;
  struct list_head* prev;
};

#define INIT_LIST_HEAD(ptr) (ptr)->next = (ptr); (ptr)->prev = (ptr);

#define list_entry(ptr, type, member) ((type*)((char*)(ptr)-(unsigned long)(&((type *)0)->member)))

void list_add(struct list_head*, struct list_head*);
void __list_add(struct list_head*, struct list_head*, struct list_head*);
void list_del(struct list_head*);
void __list_del(struct list_head*, struct list_head *);
void list_add_tail(struct list_head*, struct list_head *);
