#include "list.h"
#include <stdio.h>
#include <stdlib.h>

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

void *ll_get(const ll_list *list, unsigned int value_idx) {

    ll_node *it = list->first;

    for(unsigned int i = 0; i < value_idx; i++) {
        it = it->next;
    }
    return it->value;
}

void ll_pop_first(ll_list *list){
    ll_node * second = list->first->next;
    free(list->first);
    list->first = second;
    list->size--;
}

//pop last

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
