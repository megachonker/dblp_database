#include "../header/macro.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief progresse bar
 * 
 * utile pour les fonction for
 *  premier carac peut buguer ??
 * Un nouvaux argument TITRE pour avoir le context
 * @param indice 
 * @param total 
 */
void progressbar(int indice, int total)
{
    exitIfNull(total    ,"progress bar total  0 or null")    
    int taille = SIZEBAR; //taille de l'écrant a faire plus tard
    if (total<taille)
        taille = total;

    //check division par zer
    if (indice%(total/taille))
        return;

    char arrow[2*SIZEBAR];//taille max de la fleche
    float rapport = (float)indice/total;
    if (!rapport)
        arrow[0] = '>';
    
    for (int i = 0; i < taille; i++)
    {
        float progression = rapport * taille;
        if ((float)i < progression){
            arrow[i] = '=';
            arrow[i+1] = '>';    
        }
        else{
            arrow[i+1] = ' ';
        }
    }
    arrow[taille+1] = '\0';
    YELLO()
    fprintf(stderr,"\t\t[%s] (%d / %d)",arrow,indice,total);
    CLRCOLOR()
    fprintf(stderr,"\033[%dD",3*SIZEBAR);
}

//prend du temps l'utiliser directement ?
void enlever_retour_a_la_ligne(char * ligne){
    ligne[strcspn(ligne, "\n")]=0;    
}

void tabulation(int nombre){
    for (int i = 0; i < nombre; i++)
    {
        printf("\t");
    }
}

void repchar(char carac,size_t nb){
    for (size_t i = 0; i < nb; i++)
        printf("%c",carac);
}

//fonction pour convertire
// int octerToMega(int taille){

// }

// #include <unistd.h>

// int main(int argc, char const *argv[])
// {
//     DEBUG("moaarr")
//     for (int b = 0; b < 100000; b++)
//     {
//         sleep(0.1);        
//         progressbar(b,100000);
//     }
//     DEBUG("fuck me dady")
//     return 0;
// }

// clear   \033[K
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
