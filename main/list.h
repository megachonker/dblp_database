
#ifndef LIST_HEADER_GUARD
#define LIST_HEADER_GUARD
#include <stddef.h>
struct ll_list;
typedef struct ll_list ll_list;
typedef struct Sommet_Auteur
{
    char * auteur;
    ll_list * titre_article;
}Sommet_Auteur;


/**
 * create a node with the given value
 * 
 */
ll_list * ll_create(void);

/** 
 * append an element to the list with the 
 * given value
 */
void ll_append(ll_list *list, void *value);


/** 
 * prepend an element to the list with the 
 * given value
 */
void ll_prepend(ll_list *list, void *value);



/**
 * insert an element `value` in the list at index `idx`
 */
void ll_insert(ll_list*list, void * value, int idx);


/** 
 * remove the first element of the list.
 * The behavior is undefined if the list is empty
 */
void ll_pop_first(ll_list *list);

/**
 * remove the last element
 */
void ll_pop_last(ll_list*list);

/**
 * remove the element at index `idx`
 */
void ll_remove(ll_list*list, int idx);


/** 
 * return the value at index i from the list. 
 * The behavior is undefined if there are less
 * than i+1 elements in the list.
 */
void * ll_get(const ll_list *list, unsigned int i);


/** return the first value
 */
void * ll_first(ll_list *list);


/** return the last value
 */
void * ll_last(ll_list *list);

/**
 * return  the size of the list
 */
size_t ll_size(ll_list*list);


/** free the list
 */
void ll_free(ll_list *list);

void add_entry(ll_list * list_chainer_auteur,char * auteur, char* titre);

// void ll_print_auteur_titre(ll_list *list);

void ll_print_list_as_char(ll_list *list);


void stack_append(ll_list * list,char ** buffer,int arraysize);

#endif