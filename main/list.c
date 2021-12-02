#include "list.h"
#include <stdio.h>
#include <stdlib.h>

#define exitIfNull(p,msg,e)\
if (!p)\
{\
    fprintf(stderr,msg);\
    exit(e);\
}\



typedef struct ll_node {
    void *value;
    struct ll_node *next;
} ll_node;

struct ll_list {
    struct ll_node *first;
    int size;
};


typedef struct Sommet_Auteur
{
    char * auteur;
    ll_list * titre_article;
}Sommet_Auteur;




ll_list * ll_create(void) {
    ll_list * list = malloc(sizeof(ll_list));
    list->first = NULL;
    list->size = 0;
    return list;
}

void ll_append(ll_list *list, void *value) {
    ll_node * new_element = malloc(sizeof(ll_node));
    if(new_element == NULL) {
        fprintf(stderr, "Allocation error in ll_append\n");
        exit(1);
    }
    new_element->next = NULL;
    new_element->value = value;

    list->size++;

    if(list->first == NULL) {
        list->first = new_element;
        return;
    }

    ll_node *it = list->first;
    while(it->next != NULL) {
        it = it->next;
    }
    it->next = new_element;
}


void ll_prepend(ll_list *list, void *value) {

    ll_node *new_element = malloc(sizeof(ll_node));
    if(!new_element)
        exit(1);

    new_element->value=value;
    new_element->next=list->first;

    list->first=new_element;
    list->size++;  
}

void ll_insert(ll_list*list, void * value, int idx)
{
    if(list->first==NULL)
    {    
        ll_append(list,value); 
    }
    else if(idx==0)
    {   
        ll_prepend(list,value);
    }
    else
    {
        list->size++;
    
        ll_node *new_node_ptr=malloc(sizeof(ll_node));
    
        if(new_node_ptr==NULL)
        {
            exit(1);
        }

        new_node_ptr->value=value;
        new_node_ptr->next=NULL;

        ll_node *place=list->first;
        for(int i=0; i<idx-1; i++)
        {
            place=place->next;
        }

        new_node_ptr->next=place->next;
        place->next=new_node_ptr;
    }
}



void ll_pop_first(ll_list *list){
    ll_node * second = list->first->next;
    free(list->first);
    list->first = second;
    list->size--;
}

void ll_pop_last(ll_list*list){

    exitIfNull(list,"pointeur liste null",1)
    exitIfNull(list->first,"liste vide",1)

    // si la liste n'a qu'un element, je le libère et je fait pointer first vers NULL 
    if(!list->first->next)
    {
        free(list->first);
        list->first=NULL;
    }

    ll_node *it = list->first;
    while(it->next->next) {
        it = it->next;
    }
    free(it->next);
    it->next = NULL;
    list->size--;
}


void ll_remove(ll_list*list, int idx)
{
    exitIfNull(list,"erreur list n'existe pas",1)
    exitIfNull(list->first,"erreur aucun element dans la list",1)

    list->size--;
    
    if(idx==0)
    {   
        ll_pop_first(list);
    }
    else if(((size_t)idx==list->size-1))
    {
        ll_pop_last(list);
    }
    else
    {
        ll_node *it = list->first;
        for(int i = 0; i < idx-1; i++) {
            it = it->next;
        }
        ll_node old = *it;
        it->next=it->next->next;
        free(old.next);
    }
}

void *ll_get(const ll_list *list, unsigned int value_idx) {

    ll_node *it = list->first;

    for(unsigned int i = 0; i < value_idx; i++) {
        it = it->next;
    }
    return it->value;
}

void * ll_first(ll_list *list){
    return list->first->value;
}

void * ll_last(ll_list *list){
    return ll_get(list,ll_size(list)-1);
}

size_t ll_size(ll_list*list) {
    return list->size;
}

void ll_free(ll_list *list) {
    if(list == NULL) return;

    while(list->size) {
        ll_pop_first(list);
    }
    free(list);
}


// void *ll_find(ll_list *list, int (*match)(void*)) {
//     ll_node *pointeur = list->first;
//     while(pointeur->next != NULL) {
//         pointeur = pointeur->next;

//         if(match(pointeur->value) != 0){
//             return pointeur->value;
//         }
//     }
//     return NULL;
// }


// void *ll_find_data(ll_list *list, int (*match)(void*,void*), void *data){

//     ll_node *pointeur = list->first;
//     while(pointeur->next != NULL) {
//         pointeur = pointeur->next;

//         if(match(pointeur->value,data) != 0){
//             return pointeur->value;
//         }
//     }
//     return NULL;

//     return NULL;
// }

// int ll_match_char_equals(void *el, void *data){
//     if (*(int*)el == *(int*)data)
//     {
//         return 1;
//     }
    
//     return 0;
// }


ll_node * ll_search_auteur(ll_list* list,char * address){
    ll_node *it = list->first;

    for(unsigned int i = 0; i < list->size; i++) {
        Sommet_Auteur * a = (Sommet_Auteur*)it->value;
        char * b = a->auteur;
        printf("b: %c, addr %c",b,address);
        if( b == address){
            return it;
        }
        it = it->next;
    }
    return NULL;
}

void add_entry(ll_list * list_chainer_auteur,char * auteur, char* titre){
    ll_node *list_chainer_article = ll_search_auteur(list_chainer_auteur,auteur);

    if (list_chainer_article)
    {       
        ll_append(list_chainer_article,titre);
    }else{
        Sommet_Auteur new_sommet;
        new_sommet.auteur = auteur;
        new_sommet.titre_article = ll_create();
        ll_append(new_sommet.titre_article,titre);
        ll_append(list_chainer_auteur,&new_sommet);
    }
}
