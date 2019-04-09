/* * * * * * *
 * Deque module (i.e., double ended queue) for Assignment 1
 * Referenced largely part from week 2 Design of Alogithms "linked list and birthdays" solutions
 * created for COMP20007 Design of Algorithms 2019
 * template by Tobias Edwards <tobias.edwards@unimelb.edu.au>
 * implementation by <Xicheng Fan>
 */

//                   WRITE YOUR IMPLEMENTATION HERE
//
// You should fill in the function definitions for
//  - new_deque()
//  - free_deque()
//  - deque_push()
//  - deque_insert()
//  - deque_pop()
//  - deque_remove()
//  - deque_size()
//
// Don't be shy to add any extra functions or types you may need.

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "deque.h"
#include "point.h"

// a struct that represents the data type node  which holds pointer to the previous and next node 

typedef struct node Node;
struct node{
  Node *prev;
  Node *next;
  Point data;
};
// the deque that uses a double linked list quene that holds the nodes in it 
struct deque{
  Node *head;
  Node *tail;
  int size;
};

// Create a new empty Deque and return a pointer to it
Deque *new_deque()
{
  Deque *deque = malloc(sizeof(Deque));
  deque->head = NULL;
  deque->tail = NULL;
  deque->size = 0;
  return deque;
}

// Free the memory associated with a Deque

void free_deque(Deque *deque)
{
  Node *node = deque->head;
  Node *next;
  while (node)
  {
    next = node->next;
    free(node);
    node = next;
  }
  free(deque);
}

// Add a Point to the top of a Deque
// Runtime: O(1)
void deque_push(Deque *deque, Point data)
{
  // new node malloced to contained the point data that will be pushed to the top of deque
  Node *node = malloc(sizeof(Node));
  node->prev = NULL;
  node->next = NULL;
  node->data = data;
  //if tail is NULL, the new node is tail;
  if (deque->tail == NULL)
  {
    deque->tail = node;
  }
  // if head is not null,this node becomes the head's prev node as well as the new node
  if (deque->head != NULL)
  {
    deque->head->prev = node;
  }
  node->next = deque->head;
  deque->head = node;
  //update deque size
  deque->size++;
}

// Add a Point to the bottom of a Deque
// Runtime: O(1)

void deque_insert(Deque *deque, Point data)
{
  // new node to be inserted into the que
  Node *node = malloc(sizeof(Node));
  node->data = data;
  node->next = NULL;
  node->prev = NULL;
  // if head is null, node ->head
  if (deque->head == NULL)
  {
    deque->head = node;
  }
  //if tail is not null,node is tail's next node
  if (deque->tail != NULL)
  {
    deque->tail->next = node;
  }
  node->prev = deque->tail;
  deque->tail = node;
  //update size
  deque->size++;
}

// Remove and return the top Point from a Deque
// Runtime:O(1)

Point deque_pop(Deque *deque)
{
  //Runtime: O(1)
  Node *node = deque->head;
// if the node poped is tail, tail is null
  if (node == deque->tail)
  {
    deque->tail = NULL;
  }
  deque->head = node->next;
  deque->size--;
  Point data;
  data = node->data;
  // free memory used
  free(node);
  return data;
}

// Remove and return the bottom Point from a Deque
// Runtime: O(1)

Point deque_remove(Deque *deque)
{
  // store the data in a new node to be returned
  Node *node = deque->tail;
  Point data;
  if (node == deque->head)
  {
    deque->head = NULL;
  }

  deque->tail = node->prev;
  deque->size--;

  data = node->data;
  // free memory used 
  free(node);

  return data;
}

// Return the number of Points in a Deque
// Runtime:O(1)

int deque_size(Deque *deque)
{
  return deque->size;
}

// a series of get_data functions to get data needed in convex-hell.c 
Point get_head_data(Deque *deque){
  return deque->head->data;
}
Point get_tail_data(Deque *deque){
  return deque->tail->data;
}
Point get_head_next_data(Deque *deque){
  return deque->head->next->data;
}
Point get_tail_prev_data(Deque *deque){
  return deque->tail->prev->data;
}

