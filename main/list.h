
#ifndef LIST_HEADER_GUARD
#define LIST_HEADER_GUARD

struct ll_list;
typedef struct ll_list ll_list;

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







// //cette fonction retourne le premier élément `el` de la liste tel que `match(el)` est vrai (est différent de 0). Si aucun élément n'est trouvé, la fonction retourne `NULL`.
// void *ll_find(ll_list *list, int (*match)(void*));

// //similaire à `ll_find` mais cette fois l'argument data est envoyé en deuxième argument de la fonction match à chaque appel de celle-ci. 
// void *ll_find_data(ll_list *list, int (*match)(void*,void*), void *data);

// int ll_match_char_equals(void *el, void *data);

// int ll_match_Sommet_Auteur(void *el, void *data);

void add_entry(ll_list * list_chainer_auteur,char * auteur, char* titre);
#endif