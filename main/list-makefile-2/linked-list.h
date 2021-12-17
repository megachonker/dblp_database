#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdio.h>


typedef struct ll_list {
    struct ll_node *first;
    size_t size;
}ll_list;

typedef struct ll_node {
    void* value;
    struct ll_node *next;
} ll_node;

/**
 * create a node with the given value
 * 
 */
ll_list * ll_create(void);

/** 
 * append an element to the list with the 
 * given value
 */
void ll_append(ll_list *list, void* value);
/** 
 * prepend an element to the list with the 
 * given value
 */
void ll_prepend(ll_list *list, void* value);


/** 
 * return the value at index i from the list. 
 * The behavior is undefined if there are less
 * than i+1 elements in the list.
 */
void* ll_get(const ll_list *list, unsigned int idx);


// retourne un pointeur vers le ième node de la list
void *ll_get_node(const ll_list *list, int idx);

/** 
 * return 1 if the function succeed
 * 0 if there is an error
 */
void *ll_get_safe(const ll_list *list, unsigned int idx, void **value);


/** free the list
 */
void ll_free(ll_list *list);


/** return the first value
 */
void *ll_first(ll_list *list);

/** return the last value
 */
void *ll_last(ll_list *list);

/**
 * return  the size of the list
 */
size_t ll_size(ll_list*list);

/**
 * remove the last element
 */
void ll_pop_last(ll_list*list);
/**
 * remove the first element
 */
void ll_pop_first(ll_list*list);

/**
 * insert an element `value` in the list at index `idx`
 */
void ll_insert(ll_list*list, void* value, int idx);

/**
 * remove the element at index `idx`
 */
void ll_remove(ll_list*list, int idx);


#endif