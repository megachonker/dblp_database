#include "../header/macro.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

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


void writestrfile(char * str, FILE * fichier){
    int intlongeur = strlen(str);
    if (intlongeur > 0x1<<16)
    {
        exitIfNull(0,"ERREUR plus long qu'un chort")
    }
    
    short size = (short)intlongeur;
    YOLO("%s!(%d)",str,size)
    fwrite(&size,sizeof(short),1,fichier);
    fwrite(str,sizeof(char),size,fichier);
}

char * readstrfile(FILE * fichier){
    short taille;
    fread(&taille,sizeof(short),1,fichier);
    char * buffer = calloc(taille+1,sizeof(char));
    fread(buffer,sizeof(char),taille,fichier);
    exitIfNull(buffer,"imposible malloc buffer");
    buffer[taille]='\0';
    YOLO("%s!(%d)",buffer,taille);
    return buffer ;
}


static void catch_function() {
    puts("Sure ? [Y/n]: ");
    if(getc(stdin)!='n')
        exit(0);
    return;
}

void init_signal(){
    if (signal(SIGINT, catch_function) == SIG_ERR) {
        WARNING("Terminal SIG_ERR")
        exit(1);
    }
    return;
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
