#include "linked-list.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct ll_node {
    void* value;
    struct ll_node *next;
} ll_node;

struct ll_list {
    struct ll_node *first;
    size_t size;
};


ll_list * ll_create(void) {
    ll_list * list = malloc(sizeof(ll_list));
    
    if(list==NULL)
        return NULL;
    
    list->first = NULL;
    list->size=0;
    return list;
}

void ll_append(ll_list *list, void* value) {
    
    list->size=list->size + 1;
    
    ll_node * new_element = malloc(sizeof(ll_node));
    if(new_element == NULL) {
        fprintf(stderr, "Allocation error in ll_append\n");
        exit(1);
    }
    new_element->next = NULL;
    new_element->value = value;

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

void* ll_get(const ll_list *list, unsigned int value_idx) 
{

    ll_node *it = list->first;

    for(unsigned int i = 0; i < value_idx; i++) {
        it = it->next;
    }
    return it->value;
}

void ll_free(ll_list *list) {
    
     if(list==NULL)
        free(list);
    
    else
    {
        size_t size=ll_size(list);
        for(size_t i=0; i<size; i++ )
        {
            ll_pop_first(list);
        }
    }
    free(list);

    return;
}

void ll_prepend(ll_list *list, void *value) {

    ll_node *new_element = malloc(sizeof(ll_node));
    if(new_element == NULL) {
        exit(1);
    }

    new_element->value=value;
    new_element->next=list->first;

    list->first=new_element;
    list->size++;
    
}

size_t ll_size(ll_list*list) {
     
    return list->size;
}

void* ll_first(ll_list *list) {
    
    return list->first->value;
}

void* ll_last(ll_list *list) {
    
    size_t size=ll_size(list);
    ll_node *pointeur_element_parcour=list->first;

    for(size_t i=0; i<size-1; i++)
    {
        pointeur_element_parcour=pointeur_element_parcour->next;
    }
    return pointeur_element_parcour->value;
}

void ll_pop_last(ll_list*list) {
        
    if(list==NULL)
    {
        exit(1);
    }
        
    if(list->first == NULL) {  //si la liste est vide je m'arrete là
        exit(1);
    }
        
    if(list->first->next==NULL) // si la liste n'a qu'un element, je le libère et je fait pointer first vers NULL
    {
        free(list->first);
        list->first=NULL;

    }
        
    size_t size=ll_size(list);
    ll_node *pointeur_avant=list->first;    
    ll_node *pointeur_arriere=NULL;
        


    for(size_t i=0; i<size-1; i++) {

        pointeur_arriere=pointeur_avant;        //Je construis un pointeur qui pointe vers l'avant dernier element (pointeur_arriere)
        pointeur_avant=pointeur_avant->next;    //Je construis un pointeur qui pointe vers le dernier element (pointeur_avant)
    }

    pointeur_arriere->next=NULL; // Je met le next de l'avant dernier element NULL

    free (pointeur_avant);          //Je libere le dernier element
    list->size--;
}

    void ll_pop_first(ll_list*list) {

        
        if(list==NULL)
            exit(1);
        
        
        if(list->first==NULL)
        {

            exit(1); 
        }
        
        ll_node *premier_element=list->first;
        list->first=list->first->next;
        free(premier_element);
        list->size--;

    }




void ll_insert(ll_list*list, void *value, int idx)
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


void ll_remove(ll_list*list, int idx)
{
   
    if(list->first==NULL)
    {
        printf("%s\n", "erreur aucun element dans la list");
        exit(1);
    }

    if(list==NULL)
    {
        printf("%s\n", "erreur list n'existe pas");
        exit(1);
    }
    
    
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
    
    
        ll_node *place=list->first;
        ll_node *intermediaire_ptr;

            for(int i=0; i<idx-1; i++)
            {
                place=place->next;
            }
        intermediaire_ptr=place->next;
        place->next=place->next->next;
        free(intermediaire_ptr);
    }
}


void *ll_get_node(const ll_list *list, int idx)
{
    ll_node *it = list->first;

    for(int i = 0; i <idx; i++) {
        it = it->next;
    }
    return it;
}