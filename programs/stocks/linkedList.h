/* 
 * File: linkedList.h
 * Purpose: Structures and prototypes for a singly linked list.
 */
#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "stock.h"

typedef struct list_node
{
   stock_t data;    //data item of the node
   struct list_node *next;  //the next node
} list_node;

//return a dummy node (beginning of a new list)
list_node *list_init();

////fundamental list operations (FLO's)////

//insert a new node after the prev and return a poniter to the new node
list_node *list_insert(list_node *prev, stock_t item);   

//delete the next node
void list_delete(list_node *prev);


//destroy the entire list
void list_destroy(list_node *dummy);
#endif
