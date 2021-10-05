/*
 * File: linkedList.c
 * Purpose: Implementation of a simple singly linked list
 */
#include <stdlib.h>
#include "stock.h"
#include "linkedList.h"


//return a dummy node
list_node* 
list_init()
{
    list_node *node;
    node = malloc(sizeof(list_node));

    node->next = NULL;
    return node;
}


//insert a new node after the prev
list_node *
list_insert(list_node *prev, stock_t item)
{
    list_node *node;  //the new node

    // Allocate the node
    node = malloc(sizeof(list_node));
    node->data = item;
    node->next = NULL;

    return node;
}


//delete the next node
void 
list_delete(list_node *prev)
{
    list_node *doomed;  //the doomed node (let its name be stricken from our hearts)

    //get a pointer to the doomed
    doomed = prev->next;
    if(!doomed) return;

    //unlink the doomed node
    prev->next = doomed->next;
    
    //destroy the node 
    free(doomed);
}


//destroy the entire list
void 
list_destroy(list_node *dummy)
{
    while(dummy->next) {
       list_delete(dummy);
    }
}
