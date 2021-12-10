
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

/**
 * @brief Affiche la chaine de caractere pour chaque élément
 * interprete la premierre valeur de chaque node comme un (char)
 * donc si une structure commence par une chaine de caractere
 * je peut l'afficher
 * @param list 
 */
void ll_print_list_as_char(ll_list *list);

/**
 * @brief concatène une liste chainer avec un Tableaux de char
 * 
 * Fonction optimiser pour car:
 * elle ne parchour pas a chaque foit la liste chainer pour l'ajout
 * 
 * @param list liste chainer qui sera concaténée
 * @param buffer tableaux des chaine de caractere a ajouter
 * @param arraysize nombre de chaine de caracter dans buffer
 */
void stack_append(ll_list * list,char ** buffer,int arraysize);

/**
 * @brief ajoute un élément a la liste chainer a partire du dernier élément donnée
 * 
 * Si ll_node_address est NULL allor toute la liste sera parcourue 
 * 
 * @param lisstapparien liste chainer pour l'opération
 * @param ll_node_address addresse de la dernierre node
 * @param address_a_add élément a ajouter
 * @return void* retourne l'adresse de la dernierre NODE de la liste chainer
 */
void * ll_append_fromAddr(ll_list * lisstapparien, void * ll_node_address, void * address_a_add);

// /**
//  * @brief retourne l'adress du dernier neud
//  * 
//  * @param list 
//  * @return void* 
//  */
// void * ll_last_addr(ll_list *list);


void ll_list_link(ll_list * list_chainer_auteur);
void print_liste_chainer_Auteur_titre(ll_list * list_chainer_auteur);

/**
 * @brief concatène 2 liste chainer
 * 
 * a + b = a
 * 
 * @param a liste résultante
 * @param b liste a ajouter a A
 */
void ll_concat(ll_list * a, ll_list * b);


#endif