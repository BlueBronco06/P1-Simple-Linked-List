#include "lab.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    void *data;
    struct Node *prev;
    struct Node *next;
} Node;

typedef struct List {
  Node *sentinel;
  Node *head;
  Node *tail; 
  size_t size;
} List;

/**
* Creates a List Object
* AI Use: No AI
*/
List *list_create(ListType type) {
  // Create List Object
  List *list = malloc(sizeof(List));
  if (!list) {
    return NULL;
  }

  if(type == LIST_LINKED_SENTINEL) {
    // Create senitnel Node
    Node *sentinelNode = malloc(sizeof(Node));
    if (!sentinelNode) {
      free(list);
      return NULL;
    }

    // Setup sentinel Node
    sentinelNode->data = NULL;
    sentinelNode->prev = sentinelNode;
    sentinelNode->next = sentinelNode;
    list->sentinel = sentinelNode;
    list->size = 0;

    return list;
  } else {
    return NULL;
  }
}

/**
* Destroys a List Object
* AI Use: Assisted by AI
*/
void list_destroy(List *list, FreeFunc free_func) {
  Node *current = list->sentinel->next;
  while (current != list->sentinel) {
    Node *nextNode = current->next;
    if (free_func) {
      int *ptr_1 = current->data;
      free_func(ptr_1);
    }
    free(current);
    current = nextNode;
  }
  free(list->sentinel);
  free(list);
}

/**
* Appends to the end of the List
* AI Use: Assisted by AI
*/
bool list_append(List *list, void *data) {
  // Initialize new node
  Node *newNode = malloc(sizeof(Node));
  if (!newNode) {
    return false;
  }
  newNode->data = data;

  // Append new node  
  Node *sentinel = list->sentinel;
  Node *tailNode = sentinel->prev;
  newNode->next = sentinel;
  newNode->prev = tailNode;
  tailNode->next = newNode;
  sentinel->prev = newNode;

  list->size++;
  return true;
}

/**
* Inserts an Object into a List
* AI Use: Assisted by AI
*/
bool list_insert(List *list, size_t index, void *data) {
  // Check out-of-bounds errors
  if (index > list->size) {
    return false;
  }
  
  // Initialize node
  Node *newNode = malloc(sizeof(Node));
  if (!newNode) {
    return false;
  }

  newNode->data = data;

  // Find index
  Node *current = list->sentinel->next;
  for (size_t i = 0; i < index; i++) {
    current = current->next;
  }

    // Insert node before 'current'
    newNode->prev = current->prev;
    newNode->next = current;
    current->prev->next = newNode;
    current->prev = newNode;

    list->size++;
    return 0;
}

/**
* Removes an Object from a List
* AI Use: No AI
*/
void *list_remove(List *list, size_t index) {
  // Check if index is out-of-bounds
  if (index >= list->size) {
      return NULL;
  }

  // Traverse to Node by index
  Node *current = list->sentinel->next;
  for (size_t i = 0; i < index; i++) {
    current = current->next;
  }

  // Remove Node at the index
  current->prev->next = current->next;
  current->next->prev = current->prev;
  void *data = current->data;
  free(current);

  list->size--;
  return data; // This is a pointer to the removed element!
}


/**
* Gets the Object at an index of a List
* AI Use: Assisted by AI
*/
void *list_get(const List *list, size_t index) {
  // Check index out-of-bounds errors
  if (index >= list->size) {
    return NULL;
  }
    
  // Determine fastest direction to index (forwards/backwards)
  Node *currentNode; size_t i;
  
  if (index < list->size / 2) {
    currentNode = list->sentinel->next;
    for (i = 0; i < index; i++) {
      currentNode = currentNode->next;
    }
  } else {
    currentNode = list->sentinel->prev;
    for (i = list->size - 1; i > index; i--) {
      currentNode = currentNode->prev;
    }
  }

  return currentNode->data;
}

/**
 * Gets the size of a List
 * AI Use: No AI
 */
size_t list_size(const List *list) {
    return list->size;
}

/**
 * Gets the size of a List
 * AI Use: No AI
 */
bool list_is_empty(const List *list) {
  if (list->size==0) {
    return true;
  } 
  return false;
}
