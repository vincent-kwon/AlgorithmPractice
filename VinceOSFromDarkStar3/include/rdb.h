/*
 * =====================================================================================
 *
 *       Filename:  rdb.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/02/2013 10:56:54 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hobum (Vincent) Kwon (mn), hobum.kwon@gmail.com
 *        Company:  Samsung Electornics
 *
 * =====================================================================================
 */

#ifndef _RDB_H_
#define _RDB_H_

#define ERROR_HANDLE_REQUIRED \
	printf("Error Handling Required (at %d in %s)\n", __LINE__, __FILE__);	

typedef enum { RDB_NODE_BLACK, RDB_NODE_RED } rdb_color_e;

typedef enum  { RDB_TREE_SHIFT_RIGHT, RDB_TREE_SHIFT_LEFT } rdb_tree_shift_e;

typedef enum { RDB_CHILD_LEFT, RDB_CHILD_NULL, RDB_CHILD_RIGHT } rdb_child_e;

/*-----------------------------------------------------------------------------
 *  Interesting decision. Is is necessary to have a link to parent? 
 *  If it is not required, can save 4 bytes for every node   
 *-----------------------------------------------------------------------------*/
typedef struct _rdb_node_s {
        rdb_color_e color;
        struct _rdb_node_s* left_child;
        struct _rdb_node_s* right_child;
        struct _rdb_node_s* parent;
        int value;
} rdb_node_s;

void
rdb_init (void);

void
rdb_insert_node (int value_to_insert);

void
rdb_delete_node (void);

void
rdb_integrity_check (void);

void
rdb_insert_adjust (void);

void
rdb_delete_adjust (void);

rdb_node_s*                                                                                                      
rdb_search_value (int value_to_search);

#endif


