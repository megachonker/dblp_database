#include "macro.h"

#include <stdio.h>
#include <stdlib.h>


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
    indice++;//pour eviter div 0
    int taille = 20; //taille de l'écrant a faire plus tard

    if(indice%((total/8)+1))//+1 pour eviter division par zero
        return;
    //afficher que 8 foit donc a chaque changement de bare
    //que quand l'égaliter fait avancer la bar

    char arrow[100];//taille max de la flech
    float rapport = (float)indice/total;
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
    WARNING("[%s] %d/%d",arrow,indice,total);
}
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
