#include "list.h"
#include <stdio.h>
#include <stdlib.h>

#include <stddef.h>

#include <string.h>


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
    size_t size;
};





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
ll_node *ll_get_addr(const ll_list *list, unsigned int value_idx) {
    if (value_idx+1 == 0)
    {
        return list->first;
    }
    
    ll_node *it = list->first;

    for(unsigned int i = 0; i < value_idx; i++) {
        it = it->next;
    }
    return it;
}

// void ll_concat(ll_list * a, ll_list * b){
    
//     ll_node * fin_A = ll_get_addr(a,ll_size(a)-1);
//     a->size+=b->size;
//     fin_A->next = b->first;
//     free(b);
// }



void stack_append(ll_list * list,char ** buffer,int arraysize){
    ll_node * fin_A = ll_get_addr(list,ll_size(list)-1);

    for (int u = 0; u < arraysize; u++)
    {
        ll_node * new_element = malloc(sizeof(ll_node));
        exitIfNull(new_element,"stackappendmalockfail\n",1)

        new_element->next = NULL;
        new_element->value = buffer[u];

        fin_A->next = new_element;

        fin_A = fin_A->next;
    }

    list->size+=arraysize;
}

void * ll_append_fromAddr(ll_list * lisstapparien, void * ll_node_address, void * address_a_add){

    if (ll_node_address == NULL)
    {
        ll_append(lisstapparien,address_a_add);
        return ll_last_addr(lisstapparien);
    }
    
    ll_node * new_element = malloc(sizeof(ll_node));
    exitIfNull(new_element,"stackappendmalockfail\n",1)

    new_element->next = NULL;
    new_element->value = address_a_add;

    ((ll_node*)ll_node_address)->next = new_element;
    lisstapparien->size++;
    return new_element;
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

void * ll_last_addr(ll_list *list){
    return ll_get_addr(list,ll_size(list)-1);    
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

void ll_print_list_as_char(ll_list *list){
    ll_node *it = list->first;
    while(it->next->next) {
        Sommet_Auteur * bouboule = it->value;
        printf("char*:%s\n",bouboule->auteur);
        it = it->next;
    }
}

ll_node * ll_search_auteur(ll_list* list,char * address){
    ll_node *it = list->first;
    while(it->next != NULL) {
        char *  lfranbnnnce_wuuuuie = ((Sommet_Auteur*)it->value)->auteur;
        // if(address[0]!='\0'){
        if(strcmp(lfranbnnnce_wuuuuie,address)==0){
            // printf("b: %s;%s\n",lfranbnnnce_wuuuuie,address);
            return it;
        }
        // }
        it = it->next;
    }
    return NULL;
}


void add_entry(ll_list * list_chainer_auteur,char * auteur, char* titre){
    ll_node *list_chainer_article = ll_search_auteur(list_chainer_auteur,auteur);
    if (list_chainer_article)
    {
        Sommet_Auteur * list_chainer_Somet_hauteur = list_chainer_article->value;
        // printf("append: %s to %s\n",titre,auteur);
        ll_append(list_chainer_Somet_hauteur->titre_article,strdup(titre));
    }else{
        Sommet_Auteur * new_sommet = malloc(sizeof(Sommet_Auteur));
        if(new_sommet == NULL) {
            fprintf(stderr, "Allocation error in add_entry\n");
            exit(1);
        }

        new_sommet->auteur =  strdup(auteur);
        auteur[0] = '\0';
        
        new_sommet->titre_article = ll_create();
        ll_append(new_sommet->titre_article,titre);
        ll_append(list_chainer_auteur,new_sommet);
    }
}
