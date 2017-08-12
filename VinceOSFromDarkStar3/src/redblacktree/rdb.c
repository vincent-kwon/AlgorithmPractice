/*
 * =====================================================================================
 *
 *       Filename:  rdb.c
 *
 *    Description:  Red-Black Tree implementation 
 *
 *        Version:  1.0
 *        Created:  12/02/2013 09:53:08 PM in Boston
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hobum (Vincent) Kwon (mn), hobum.kwon@gmail.com
 *        Company:  Samsung Electornics
 *
 * =====================================================================================
 */

/*-----------------------------------------------------------------------------
 * Rule of RDB tree
 *
 * 1. Root MUST be black
 * 2. Leaf MUST be black (inserted node with one of link null MUST point a common leaf)
 * 3. Black after Red
 * 4. Root to any leaf MUST have same number of black node
 *-----------------------------------------------------------------------------*/

#include <memory.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "rdb.h" 


/*-----------------------------------------------------------------------------
 *  TODO:where is good place to initialize static variable and why?
 *-----------------------------------------------------------------------------*/
static rdb_node_s* rdb_root_ptr = NULL; 
static rdb_node_s* rdb_leaf_ptr = NULL;
static int num_of_blacks = -1; 

<<<<<<< HEAD
rdb_node_s*
__get_parent_sibling(rdb_node_s* current_ptr)
{
	if (current_ptr->parent == current_ptr->parent->parent->left_child)
		return current_ptr->parent->parent->right_child;
	else
		return current_ptr->parent->parent->left_child;
}

rdb_tree_shift_e 
__get_shift_direction(rdb_node_s* current_ptr)
{
	assert(current_ptr);
	printf("current_ptr->value  %d\n", current_ptr->value);
	assert(current_ptr->parent);
	
	if (current_ptr == current_ptr->parent->left_child)
		return RDB_TREE_SHIFT_RIGHT;
	else 
		return RDB_TREE_SHIFT_LEFT;
}


/* Tree shift can be divided into following steps:
 * 1. parent's parent become parent of current.
 *     current->parent = current->parent->parent; 
 * 2. parent's parent points to current (left or right)
       __skip_parent(current); //check parent(left or right) do appropriate things
 * 3. parent's left child sets to current's right (right turn) or parent's right sets to current's left (left turn)
       __send_current_child_to_parent(current); // check parent(left or right) do appropriate things
 *     3.1 current->right->parent = parent, parent->left = current->right
 *     3.2 current->left->parent = parent, parent->right = current->left
 * 4. switch color between parent and current
 * 5. parent->parent sets to current
 */
=======
// parent null check must be performed in caller. 
rdb_child_e
__check_which_child(rdb_node_s* current_ptr)
{
	if (current_ptr->parent == NULL)
		return RDB_CHILD_NULL;
	else if (current_ptr->parent->left_child == current_ptr)
		return RDB_CHILD_LEFT;
	else if (current_ptr->parent->right_child == current_ptr) 
		return RDB_CHILD_RIGHT;
}

>>>>>>> d883a446285b332474bdf422b53a9272ed11a333
void 
__shift_tree(rdb_node_s* current_ptr) 
{
	printf("Enter shift tree %d\n", current_ptr->value);

	assert(current_ptr);
	assert(current_ptr->parent);
	rdb_node_s *temp_ptr;
	rdb_color_e temp_color;
	rdb_node_s *old_parent = current_ptr->parent;
	rdb_tree_shift_e current_direction = __get_shift_direction(current_ptr);
	rdb_tree_shift_e parent_direction;

	//current's parent parent care
	if (current_ptr->parent->parent) 
	{
	
		parent_direction = __get_shift_direction(current_ptr->parent);
		if (parent_direction == RDB_TREE_SHIFT_RIGHT) 
		{
			current_ptr->parent->parent->left_child = current_ptr;
		}
		else 
		{
			current_ptr->parent->parent->right_child= current_ptr;
		}
		//current_ptr->parent was backed up in old_parent variable, so safe to change to parent's parent
		current_ptr->parent = current_ptr->parent->parent;
	}
	else 
	{
		rdb_root_ptr = current_ptr;
		current_ptr->parent = NULL;
	}

	//current's parent and child care
	old_parent->parent = current_ptr;
	
	if (current_direction == RDB_TREE_SHIFT_RIGHT) 
	{
		old_parent->left_child = current_ptr->right_child;			
		current_ptr->right_child = old_parent;
	}
	else 
	{
		old_parent->right_child = current_ptr->left_child;
		current_ptr->left_child = old_parent;
	}

	//switch color
	temp_color = current_ptr->color;
	current_ptr->color = old_parent->color;
	old_parent->color = temp_color;
	
	printf("Exit shift tree %d\n", current_ptr->value);
}

bool 
__preshift_tree(rdb_node_s* current_ptr) 
{
	rdb_tree_shift_e current_direction = __get_shift_direction(current_ptr);
	rdb_tree_shift_e parent_direction = __get_shift_direction(current_ptr->parent);

	if (current_direction == parent_direction)
	{
		return false;
	}
	else 
	{
		__shift_tree(current_ptr);
		return true;
	}
}

static rdb_node_s* 
__create_new_node(int value_to_insert) 
{

    rdb_node_s* new_node_ptr = (rdb_node_s*)malloc(sizeof(rdb_node_s));

    if (!new_node_ptr)                                              
    {
		ERROR_HANDLE_REQUIRED; 
		return NULL;                                                 
	}
	else 
	{
		//node initialization 
		new_node_ptr->color = RDB_NODE_RED;
		new_node_ptr->left_child = NULL;
		new_node_ptr->right_child = NULL;
		new_node_ptr->parent = NULL;
		new_node_ptr->value = value_to_insert;	
		return new_node_ptr;
	}
}

void
__apply_rdb_policies(rdb_node_s* current_ptr)
{
//Precondition: current node is red. previously this tree was complete tree
//1. if parent of current is black, do nothing
//2. if parent is red, red-red-red => black-red-black, and apply_rdb_policies(parent)
//3. if parent is red, sibling is black, if necessary, preshift tree. then shift tree

	assert(current_ptr);
	assert(current_ptr->color == RDB_NODE_RED);

	printf("appy %d\n", current_ptr->value); 
	
	if (current_ptr->parent == NULL)
	{
		//make this root and return;
		current_ptr->color = RDB_NODE_BLACK;
		rdb_root_ptr = current_ptr;
		return;
	}
	else if (current_ptr->parent->color == RDB_NODE_BLACK) 
	{
		//do nothing
		return;
	}
<<<<<<< HEAD
	else if (current_ptr->parent->color == RDB_NODE_RED) 
	{
		assert(current_ptr->parent->parent); //since parent is red, parent's parent must exist. otherwise, tree corrupted
		rdb_node_s* sibling_ptr = __get_parent_sibling(current_ptr);
		if ((sibling_ptr == NULL) || (sibling_ptr->color == RDB_NODE_BLACK))
=======

	//printf("\t\t\t[COMP] parent, parent setting done.\n");
	
	if ((parent_ptr->color == RDB_NODE_RED) &&
	   	(parent_parent_ptr != NULL) &&
		(parent_sibling_ptr == NULL))
	{
		printf("\t\t[COMP] P(RED), PP(Non-null), PS(NULL)\n");
		rdb_child_e parent_child_type = __check_which_child(parent_ptr);
		rdb_child_e current_child_type = __check_which_child(new_node_ptr); 
		printf(" %d, %d \n", parent_child_type, current_child_type);  
		if (parent_child_type == RDB_CHILD_LEFT) 
>>>>>>> d883a446285b332474bdf422b53a9272ed11a333
		{
			if (__preshift_tree(current_ptr))
			{
<<<<<<< HEAD
				printf("preshifted....\n");
				__shift_tree(current_ptr);
=======
				//right turn on parent
				__turn_right_switch_color(parent_ptr);
				printf("\t\t\t[COMP] turn right \n");
>>>>>>> d883a446285b332474bdf422b53a9272ed11a333
			}
			else 
			{
<<<<<<< HEAD
				printf("205 curent -value %d, current_ptr->parent %d\n", current_ptr->value, current_ptr->parent->value); 
				__shift_tree(current_ptr->parent);
			}
		}
		else if (sibling_ptr->color == RDB_NODE_RED) 
		{
			current_ptr->parent->color = RDB_NODE_BLACK;
			sibling_ptr->color = RDB_NODE_BLACK;
			current_ptr->parent->parent->color = RDB_NODE_RED;
			__apply_rdb_policies(current_ptr->parent->parent);
=======
				__turn_left_switch_color(new_node_ptr); 
				__turn_right_switch_color(parent_ptr);
				printf("\t\t\t[COMP] turn left and turn right\n");
				//left turn current and then right turn on parent  and switch color
			}
		}
		else if (parent_child_type == RDB_CHILD_RIGHT)
		{
			if (current_child_type == RDB_CHILD_LEFT)
			{
				__turn_right_switch_color(new_node_ptr);
				__turn_left_switch_color(parent_ptr);
				printf("\t\t\t[COMP] turn right and turn left\n");
				//right turn on current  and then left turn on parent and switch color
			}
			else if (current_child_type == RDB_CHILD_RIGHT)
			{
				//left turn on parent and switch color
				__turn_left_switch_color(parent_ptr);
				printf("\t\t\t[COMP] turn left\n");
			}
		}	

	}
	//check insert case 1 (parent and parent's sibling is all red)
	else if ((parent_ptr->color == RDB_NODE_RED) && 
		(parent_parent_ptr != NULL) && 
		(parent_sibling_ptr != NULL) && 
            	(parent_sibling_ptr->color == RDB_NODE_RED))
	{
		//printf("Insertion Case 1: Red-Red parent and sibling\n"); 
		
		printf("\t\t[COMP] P(RED), PP(Non-null), PS(RED)\n");
		parent_ptr->color = parent_sibling_ptr->color = RDB_NODE_BLACK;
		printf("\t\t\t[COMP] turn P and PS black\n");
		if (parent_parent_ptr == rdb_root_ptr) 
		{
			//printf("parent parent is root! just color black (fair)\n");
			parent_parent_ptr->color = RDB_NODE_BLACK;
			printf("\t\t\t[COMP] turn PP(BLACK)\n");
			//printf("Done for handle insert compromization\n");
>>>>>>> d883a446285b332474bdf422b53a9272ed11a333
		}
		else
		{
<<<<<<< HEAD
			assert(0);
		}
=======
			parent_parent_ptr->color = RDB_NODE_RED;
		
			if (parent_parent_ptr->parent != NULL && 
				parent_parent_ptr->parent->color == RDB_NODE_RED)
			{
				//printf("Yes ppp and pp are red. break Rule 3\n");
				__handle_insert_compromizing(parent_parent_ptr);	
			}
		}

	} 
	//else if (parent_pt
		
	
	else 
	{
		//printf("Not known insertion case\n"); 
>>>>>>> d883a446285b332474bdf422b53a9272ed11a333
	}
}

void
rdb_init (void)
{
	//Leaf may not actually exist. 
	//TODO: What will be an issue if leaf just exits in theory.
	return;
}

void
rdb_insert_node (int value_to_insert)
{
        rdb_node_s* new_node_ptr;
	printf("[INSERT] insert new node %d\n", value_to_insert);
	//if root is null, then set it as root
	if (!rdb_root_ptr) 
	{
		new_node_ptr = __create_new_node(value_to_insert);
		if (!new_node_ptr)
		{
			ERROR_HANDLE_REQUIRED;
			return;
		}
		rdb_root_ptr = new_node_ptr;
		//meet rule No.1
		new_node_ptr->color = RDB_NODE_BLACK;
	}
	else 
	{
		//binary search in the tree 
		rdb_node_s* current_ptr = rdb_root_ptr;

		while(true) 
		{	
			if (current_ptr->value > value_to_insert) 
			{
				if (!current_ptr->left_child) //if left child is null 
				{
					new_node_ptr = __create_new_node(value_to_insert);
					if (!new_node_ptr) 
					{
						ERROR_HANDLE_REQUIRED;
						return;
					}
					current_ptr->left_child = new_node_ptr;
					new_node_ptr->parent = current_ptr;
<<<<<<< HEAD
					__apply_rdb_policies(new_node_ptr);
=======
					printf("\t[INSERT] new node %d is now left of %d\n", new_node_ptr->value, current_ptr->value);
					//check rule No. 3 (rule No.4 is not hurt because it is complete tree until now)
					__handle_insert_compromizing(new_node_ptr);
>>>>>>> d883a446285b332474bdf422b53a9272ed11a333
					break;
				}
				else //if left child is non-null
				{
					current_ptr = current_ptr->left_child;
					continue;
				}
			}
			else if (current_ptr->value < value_to_insert)
			{

				if (!current_ptr->right_child) //if right child is null 
				{
					
					new_node_ptr = __create_new_node(value_to_insert);
					if (!new_node_ptr) 
					{
						ERROR_HANDLE_REQUIRED;
						return;
					}
					current_ptr->right_child = new_node_ptr;
					new_node_ptr->parent = current_ptr;
<<<<<<< HEAD
					__apply_rdb_policies(new_node_ptr);
=======
					printf("\t[INSERT] new node %d is now right of %d\n", new_node_ptr->value, current_ptr->value);
					
					__handle_insert_compromizing(new_node_ptr);
>>>>>>> d883a446285b332474bdf422b53a9272ed11a333
					break;
				}
				else //if right child is non-null
				{
					current_ptr = current_ptr->right_child;
					continue;
				}
			}
			// If existing value is asked to inserted, just ignore it. 
			else 
			{
				//ERROR_HANDLE_REQUIRED;
				printf("\t[INSERT] Value %d is already existing. Do nothing. \n", value_to_insert);
				return; 
			}

		}
	}
	
	//Now, adjust may required. Check this now.
	//Rule No. 1 and No.2 
	//Nothing to do
	
	//Rule No. 3: Red - Red
	
	
	//Rule No. 3
	//Rule No. 4
	rdb_integrity_check();
 	//printf("RDB Tree integrity fine for insertion (%d)\n", value_to_insert);
}		
/* -----  end of function rdb_insert node  ----- */

void
rdb_delete_node (void)
{
	return ;
}		
/* -----  end of function rdb_delete_node  ----- */

void
__visit_node_dfs(rdb_node_s* current_ptr, int current_black_count)
{
	bool isLeafParent = false;

	//null check
	if (current_ptr) 
	{
		printf("[visit] enter  %d(%d)\n", current_ptr->value, current_ptr->color);

		if (current_ptr->color == RDB_NODE_RED)
		{
			//parent shouldn't be RED
			if (current_ptr->parent == NULL) 
			{
				if (current_ptr == rdb_root_ptr) 
				{
					printf("\t\t[VISIT] Rule No.1 is compromised. Root is red.\n");
					exit(1);
				}
				else 
				{
					printf("\t\t[VISIT] Wrong Tree. Parent MUST be non-null except root.\n");
					exit(1);
				}
			}
			//parent exits
			else 
			{
				if (current_ptr->parent->color == RDB_NODE_RED)
				{
					printf("\t\t[VISIT] Rule No. 3 is compromised. Red - Red.\n");
					exit(1); 
				}
				else 
				{
					//if parent is black, nothing to do
				}
			}
		}
		else if (current_ptr->color == RDB_NODE_BLACK) 
		{
			current_black_count++; 			
			printf("\t\t[VISIT] current blacks(%d)\n", current_black_count);
		}
		else 
		{
			printf("\t\t[VISIT] Wrong Tree. Color other than black and red\n");
			exit(1);
		}
		
		
		/*-----------------------------------------------------------------------------
		 *  Now visit childrent from left and right
		 *-----------------------------------------------------------------------------*/
		if (current_ptr->left_child)
		{
			printf("[visit] go to left child from (%d)\n", current_ptr->value);
			__visit_node_dfs(current_ptr->left_child, current_black_count);
		}
		else 
		{
			isLeafParent = true;
		}

		if (current_ptr->right_child)
		{
			printf("[visit] go to right child from (%d)\n", current_ptr->value);
			__visit_node_dfs(current_ptr->right_child, current_black_count);
		}	
		else 
		{
			isLeafParent = true;
		}

		//if leaf's parent, check current black with the global num of black.
		//it is -1 at the beginning.
		if (isLeafParent) 
		{
		
			//if not initialized yet
			if (num_of_blacks == -1) 
			{
				num_of_blacks = current_black_count;
				//printf("\t\t[VISIT] Initailization of num of blacks to %d\n", num_of_blacks);
				//printf("\t\t[VISIT] [End of Node] (%d)\n", current_ptr->value);
			}
			//if initialized already
			else 
			{
				if (num_of_blacks != current_black_count) 
				{
<<<<<<< HEAD
					printf("Rule No.4 is compromised %d and %d(now)\n", num_of_blacks, current_black_count);
=======
					printf("\t\t[VISIT] Rule No.4 is compromised %d and %d(now)\n", num_of_blacks, current_black_count);			
>>>>>>> d883a446285b332474bdf422b53a9272ed11a333
					exit(1);
				}
				else 
				{
					//printf("\t\t[VISIT] [End of Node] (%d)\n", current_ptr->value);
				}
			}
		}
		else
		{
			//if no leaf parent, then do nothing. 
			//printf("\t\t[VISIT] [End of Node] (%d)\n", current_ptr->value);
		}
		
	}
	else //if current_ptr is NULL, something is 
	{
		printf("\t\t[VISIT] Visited node is NULL. Something wrong\n");
		exit(1);
	}	
}

void
rdb_integrity_check (void)
{
	//node existence check 
	if (!rdb_root_ptr)
	{
		printf("\t\t[INTEGRITY] No node to check integrity of rdb tree");
		return;
	}
	
	//rule No.1 check
	if (rdb_root_ptr->color != RDB_NODE_BLACK)
	{
		printf("\t\t[INTEGRITY] Rule No 1 is broken");
		return; 
	}
	
	//rule No.2 check
	//Well, leaf is not really existing so we assume they are all black 
	//So, just assume it is satisfied
	
	//rule No.3 black node after red and No.4 all num of blacks are same for all leaf
	//Both check requires traversing the tree
	num_of_blacks = -1; 
	__visit_node_dfs(rdb_root_ptr, 0);
/* -----  end of function rdb_integrity_check  ----- */
}

void
rdb_insert_adjust (void)
{
	return ;
}		
/* -----  end of function rdb_insert_adjust  ----- */


void
rdb_delete_adjust (void)
{
	return ;
}		
/* -----  end of function rdb_delete_adjust  ----- */

rdb_node_s* 
rdb_search_value (int value_to_search)
{
	return NULL;
}		
/* -----  end of function rdb_search_value  ----- */
