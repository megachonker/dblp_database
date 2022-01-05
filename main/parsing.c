#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "parsing.h"



#define exitIfNull(p,msg)\
if (!p)\
{\
    fprintf(stderr,msg);\
}\



void enlever_retour_a_la_ligne(char * ligne){
    ligne[strcspn(ligne, "\n")]=0;    
}

void printM_titre(fiche_minimal OwO){
    printf("titre:    %s",OwO.titre);
}
void printM_liste_auteur(fiche_minimal UwU){
    printf("auteurs:\n\t");
    for (int i = 0; i < UwU.nombre_auteur; i++)
    {
        printf("%s",UwU.liste_auteur[i]);
        if (i+1<UwU.nombre_auteur)
            printf("\n\t");
    }
    printf("\n");
}

void printM(fiche_minimal OwU){
    printM_titre(OwU);
    printf("\n");
    printM_liste_auteur(OwU);   
}

void printTabmeaux(tableaux_fiche UwO){

    for (int i = 0; i < UwO.taille; i++)
    {
        printM(*(UwO.fiche[i]));
    }
}

//fonction qui cherche le string dans ldes <>

char * getanchor(char * recherche, char * ligne){
    char critaire[20] = "<";
    strcat(critaire,recherche);
    if(strstr(ligne,critaire)){ //slow ?
        char * start = strchr(ligne,'>');
        exitIfNull(start,"getanchor: pas de start")
        start++;
        int diff = strcspn(start,"<");
        char * out  = calloc(1,diff);
        if (!out)
        {
            fprintf(stderr,"pas de match");
            return NULL;
        }
        memcpy(out,start,diff);
        return out;
    }
    return NULL;
}

void appendAuteurM(fiche_minimal * mafiche,char * nomsauteur){
    void * addrListeauteur = realloc(mafiche->liste_auteur,sizeof(fiche_minimal)*(mafiche->nombre_auteur+1));
 
    if (!addrListeauteur)
    {
        fprintf(stderr,"appendAuteurM: allocation imposible");
    }else if (mafiche->liste_auteur != addrListeauteur)
    {
        mafiche->liste_auteur = addrListeauteur;
    }
    mafiche->liste_auteur[mafiche->nombre_auteur] = nomsauteur;
    mafiche->nombre_auteur++;
}

void appendTabmeaux(tableaux_fiche * table, fiche_minimal * a_ajouter){

    void * addrListFiche = realloc(table->fiche,sizeof(tableaux_fiche)*(table->taille+1));
 
    if (!addrListFiche)
    {
        fprintf(stderr,"appendTabmeaux: allocation imposible");
        exit(1);
    }else if (table != addrListFiche)
    {
        table->fiche = addrListFiche;
    }
    table->fiche[table->taille] = a_ajouter;
    table->taille++;   
}


/**
 * @brief chaque fiche a sont id
 * 
 * l'id est l'indice pour acceder a la fiche dpuis la structure  tableaux_fiche
 * 
 * @param [in,out] tableaux_allfiche 
 */
void gen_id_fiche(tableaux_fiche * tableaux_allfiche){
    for (int i = 0; i < tableaux_allfiche->taille; i++)
    {
        tableaux_allfiche->fiche[i]->ADDR = i;
    }
}


static int cmptabfiche(const void * maficheA,const void * maficheB){
    //MAGIE NOIIIIIIIIIIIIIIIIIIIIIREEE
    struct fiche_minimal* maficheAA = *(struct fiche_minimal**) maficheA;
    struct fiche_minimal* maficheBB = *(struct fiche_minimal**) maficheB;
    // printf("%s <=> %s\n",maficheAA->titre,maficheAA->titre);
    return strcmp(maficheAA->titre,maficheBB->titre);
}

void sortlist(tableaux_fiche * mesfiche ){
    // fiche_minimal * start  =  *mesfiche->fiche;
    qsort(mesfiche->fiche,mesfiche->taille,sizeof(mesfiche->fiche),cmptabfiche);   
}

//on retourne pas l'original mais une copie ?
tableaux_fiche parse(FILE * inputDB){
    printf("début du parsing:\n");
    char ligne[BALISESIZE];
    fiche_minimal * fichelocalM = calloc(1,sizeof(fiche_minimal));
    fichelocalM->nombre_auteur = 0;
    fichelocalM->ADDR = 0;
    tableaux_fiche tableaux_allfiche;// ce n'es pas maloc donc a la sortie de la fonction l'object est détruit ? ? ??
    tableaux_allfiche.taille = 0;
    tableaux_allfiche.fiche = NULL;

    while (fgets(ligne,BALISESIZE,inputDB))
    {
        int flagt = 0;
        
        if (!fichelocalM)
        {
            fprintf(stderr,"création de la zone de mémoir pour ficheloca1m compromis calloc");
        }
        
        char * tmpauteur = getanchor("author",ligne);
        if (tmpauteur)
        {
            appendAuteurM(fichelocalM,tmpauteur);
        }else{
            fichelocalM->titre = getanchor("title",ligne);
            if (fichelocalM->titre)
            {
                flagt = 1;
            }
        }

        if (flagt == 1)
        {
            // printM_titre(*fichelocalM);
            // printM_liste_auteur(*fichelocalM);

            if (strcmp(fichelocalM->titre,"Home Page")!=0 
            && fichelocalM->nombre_auteur != 0 
            && strcmp(fichelocalM->titre,"")!=0)//ces con mais fichelocalM->titre ou fichelocalM->titre != '' devrais fonctioner..
            {
                printM_titre(*fichelocalM);
                appendTabmeaux(&tableaux_allfiche,fichelocalM);
            }

            fichelocalM = calloc(1,sizeof(fiche_minimal));
            exitIfNull(fichelocalM, "new calloc null")
            fichelocalM->nombre_auteur = 0;
        }        
    }
    // printTabmeaux(tableaux_allfiche);

    printf("PARSE OK\ndébut du trie:\n");
    sortlist(&tableaux_allfiche);
    printf("Trie OK\ndébut de genereation des id:\n");
    gen_id_fiche(&tableaux_allfiche);
    printf("Id générée!\n");
    return tableaux_allfiche;
}




//utiliser l'addresse pour pas copier ?
void serialize(const tableaux_fiche mastertab, FILE * output){
    for (int i = 0; i < mastertab.taille; i++)
    {
        fprintf(output,"%s\n",mastertab.fiche[i]->titre);
        fprintf(output,"%i\n",mastertab.fiche[i]->nombre_auteur);
        for (int  u = 0; u < mastertab.fiche[i]->nombre_auteur; u++)
        {
            fprintf(output,"%s\n",mastertab.fiche[i]->liste_auteur[u]);
        }       
    }
}

//gratter en efficience en donneant au début les taille des structure
//grater en fesant une structure avec des dico est des referancement

/**
 * @brief génère tableaux_fiche depuis un cache générée par serialize 
 * 
 * test avec des maloc 
 * 
 * @param [in] input générée par serialize 
 * @return tableaux_fiche 
 */
tableaux_fiche * deserialisation(FILE * input){

    char ligne[BALISESIZE];
    fiche_minimal * fichelocalM = calloc(1,sizeof(fiche_minimal));
    fichelocalM->nombre_auteur = 0;
    tableaux_fiche * tableaux_allfiche = malloc(sizeof(tableaux_fiche));
    exitIfNull(tableaux_allfiche,"tableaux all fiche null dans deserialisation\n")
    tableaux_allfiche->taille = 0;
    tableaux_allfiche->fiche = NULL;
    int indice = 0;
    while (fgets(ligne,BALISESIZE,input))
    {
        if (feof(input))
        {
            fprintf(stderr,"fin fichier deserialisation\n");
            exit(3);
        }
        enlever_retour_a_la_ligne(ligne);
        fichelocalM->ADDR = indice;
        fichelocalM->titre = strdup(ligne);
        fgets(ligne,BALISESIZE,input);
        enlever_retour_a_la_ligne(ligne);
        int nbhauteur = atoi(ligne);
        for (int i = 0; i < nbhauteur; i++)
        {
            fgets(ligne,BALISESIZE,input);
            enlever_retour_a_la_ligne(ligne);
            appendAuteurM(fichelocalM,strdup(ligne));
        }
        appendTabmeaux(tableaux_allfiche,fichelocalM);
        fichelocalM = calloc(1,sizeof(fiche_minimal));
        exitIfNull(fichelocalM, "new calloc null")
        fichelocalM->nombre_auteur = 0;
        indice++;
    }
    return tableaux_allfiche;
}

// ll_list * deserialisation_Liste(FILE * input){
//     // fseek(input,0,SEEK_END);
//     // int maxline = ftell(input);
//     // fseek(input,0,SEEK_SET);

//     char ligne[BALISESIZE];
//     ll_list * list_hauteur_heuvre = ll_create();
//     Sommet_Auteur_ListChainer * sommet_titre =  malloc(sizeof(Sommet_Auteur_ListChainer));
//     exitIfNull(sommet_titre, "new calloc null")
//     sommet_titre->titre_article = ll_create();
//     void * addresse_node = NULL;
//     while (fgets(ligne,BALISESIZE,input))
//     {
//         if (feof(input))
//         {
//             fprintf(stderr,"fin fichier deserialisation\n");
//             exit(3);
//         }
//         enlever_retour_a_la_ligne(ligne);
//         sommet_titre->auteur = strdup(ligne);
//         fgets(ligne,BALISESIZE,input);
//         enlever_retour_a_la_ligne(ligne);
//         int nbhauteur = atoi(ligne);
//         //fast append prend une node en entrée et fait plus 1

//         char * burst[960810];


//         fgets(ligne,BALISESIZE,input);
//         enlever_retour_a_la_ligne(ligne);
//         ll_append(sommet_titre->titre_article,strdup(ligne));
//         //on fait un buffer
//         for (int i = 0; i < nbhauteur-1; i++)
//         {
//             fgets(ligne,BALISESIZE,input);
//             enlever_retour_a_la_ligne(ligne);
//             burst[i] = strdup(ligne);
//         }
//         stack_append(sommet_titre->titre_article,burst,nbhauteur);

//         addresse_node = ll_append_fromAddr(list_hauteur_heuvre,addresse_node,sommet_titre);
//         // printf("%f:TITRE: %s\n",(((float)ftell(input)+1)/(float)maxline)*100,sommet_titre->auteur);
//         // printf("%d\n",ll_size(sommet_titre->titre_article));       
//         // ll_print_list_as_char(sommet_titre->titre_article);       
//         sommet_titre = calloc(1,sizeof(sommet_titre));
//         exitIfNull(sommet_titre, "new calloc null")
//         sommet_titre->titre_article = ll_create();
//     }
//     return list_hauteur_heuvre;
// }



void parsing_free(tableaux_fiche * DEGAGE){
    for (int i = 0; i < DEGAGE->taille; i++)
    {
        free(DEGAGE->fiche[i]->titre);
        for (int u = 0; u < DEGAGE->fiche[i]->nombre_auteur; u++)
        {
            free(DEGAGE->fiche[i]->liste_auteur[u]);
        }
        free(DEGAGE->fiche[i]);
    }
    free(DEGAGE);

}



// int main(){


// #define originedb           "DATA/dblp.xml"
// #define smalloriginedb      "DATA/dblp1sur8.xml"
// #define serializedb         "DATA/SerializedStruc.data"
// #define smallserializedb    "DATA/Serialzed1000.data"
// #define serializedbunwrap   "DATA/SerializedStrucInverse.data"

//     FILE * in = fopen(originedb,"r");
//     exitIfNull(in,"imposible d'ouvrire "originedb);
//     tableaux_fiche coucou = parse(in); //utiliser des address pour eviter la copie ?? 
//     FILE * out = fopen(serializedb,"w");
//     exitIfNull(out,"imposible d'ouvrire "serializedb);
//     serialize(coucou,out); //utiliser des address pour eviter la copie ?? 
//     printTabmeaux(coucou);
// }