#include <stdio.h>
#include <stdlib.h>
#include "parsing.h"
#include "list.h"

#include <string.h>

/**
 * @def macro tester si p est null et retourne un message
 * 
 */
#define exitIfNull(p,msg)\
if (!p)\
{\
    fprintf(stderr,msg);\
}\


//soucis sommet auteur pointeur sur des auteur tot heuvre 
//soucis check que les tab d'addresse sont nu dans les for if

//2go de tableaux ?


/**
 * @brief couple Hauteur <=> Heuvre
 */
typedef struct Paire_HauteurHeurvre
{
    char * hauteur;
    fiche_minimal * heuvre;
}Paire_HauteurHeurvre;


/**
 * @brief Un hauteur plusieur heuvre
 * 
 */
typedef struct Sommet_Auteur_TableauxD
{
    char * hauteur;
    fiche_minimal ** heuvre;///<tableaux dynamique d'adresse pointant sur des pointeur de structure contenant oeuvre
    int size;               ///<taille du tableaux dynamique
}Sommet_Auteur_TableauxD;


/**
 * @brief Stoque tout les Sommet_Auteur_TableauxD
 * 
 * sous forme de tableaux DYNAMIQUE d'adresse pointant sur Sommet_Auteur_TableauxD
 * ainsie que le nombre d'élément (Sommet_Auteur_TableauxD) stoquer dans le tableaux 
 */
typedef struct List_Auteur
{
    Sommet_Auteur_TableauxD * tableaux_Somet_hauteur;
    int taille;
}List_Auteur;




// #define MAXarraySIZE 21143793
// Paire_HauteurHeurvre HauteurHeuvre[MAXarraySIZE];

/**
 * @brief fonction de comparaison pour qsort
 * 
 * elle pourait être mieux
 * 
 * @param [in] a object A
 * @param [in] b object B
 * @return int 
 */
int comphauteur(const void * a, const void * b){
    //moche
    Paire_HauteurHeurvre * aa = (Paire_HauteurHeurvre*)a;
    Paire_HauteurHeurvre * bb = (Paire_HauteurHeurvre*)b;
    int result = strcmp(aa->hauteur,bb->hauteur);
    return result;
}

int SwapStruct(tableaux_fiche input, Paire_HauteurHeurvre * arrayout ){
    int indice = 0;
    for (int i = 0; i < input.taille; i++)
    {
        for (int u = 0; u < input.fiche[i]->nombre_auteur; u++)
        {   
            arrayout[indice].heuvre = input.fiche[i];
            arrayout[indice].hauteur = input.fiche[i]->liste_auteur[u];
            indice++;
        }
    }
    return indice;
}

void sort_tableaux_fiche(Paire_HauteurHeurvre * HauteurHeuvre,int sizeHauteurHeuvre ){
    qsort(HauteurHeuvre,sizeHauteurHeuvre ,sizeof(Paire_HauteurHeurvre),comphauteur);
}


/**
 * @brief add_titre_to_auteur
 * 
 * 
 * @param [in,out] list  
 * @param [in] HtH       
 */
void add_titre_to_auteur(Sommet_Auteur_TableauxD * list,const Paire_HauteurHeurvre HtH){//ces plus logic comme ça mais pluslent ?
    fiche_minimal ** temparray = reallocarray(list->heuvre,list->size+1,8); //8 taille d'un pointeur 
    exitIfNull(temparray,"add_titre_to_auteur realockarrayfail\n");
    list->heuvre = temparray;
    list->heuvre[list->size] = HtH.heuvre;
    list->size++;
}


List_Auteur* gen_List_Auteur(const Paire_HauteurHeurvre * liste,int sizeHauteurHeuvre){
    List_Auteur * listes_Auteur_arrTitre = malloc(sizeof(List_Auteur));
    exitIfNull(listes_Auteur_arrTitre,"Erreur création liste de List_Auteur\n")
    listes_Auteur_arrTitre->taille=-1;//moche !

    //on parcoure liste
    for (int j = 0; j < sizeHauteurHeuvre; j=j)//on incrémenta pas la
    {
        listes_Auteur_arrTitre->taille++;
        Sommet_Auteur_TableauxD * tb_Somet_h = reallocarray(listes_Auteur_arrTitre->tableaux_Somet_hauteur,listes_Auteur_arrTitre->taille+1,sizeof(Sommet_Auteur_TableauxD));
        exitIfNull(tb_Somet_h,"Erreur création de Sommet_Auteur_TableauxD\n")
        listes_Auteur_arrTitre->tableaux_Somet_hauteur = tb_Somet_h;

        //on add le premier hauteure
        listes_Auteur_arrTitre->tableaux_Somet_hauteur[listes_Auteur_arrTitre->taille].hauteur=liste[j].hauteur;
        listes_Auteur_arrTitre->tableaux_Somet_hauteur[listes_Auteur_arrTitre->taille].size=0;
        listes_Auteur_arrTitre->tableaux_Somet_hauteur[listes_Auteur_arrTitre->taille].heuvre = NULL;
        int i = 1;
        //tant le prochain est le meme auteur et que on attein pas la fin de la liste
        while (i+j < sizeHauteurHeuvre && strcmp(liste[j].hauteur,liste[j+i].hauteur) == 0)//ordre important
        {
            add_titre_to_auteur(&listes_Auteur_arrTitre->tableaux_Somet_hauteur[listes_Auteur_arrTitre->taille],liste[i+j]);
            i++;// truc de simon ?
        }

        j+=i;//mais ici
    }
    return listes_Auteur_arrTitre;
}




void printList_Auteur(List_Auteur * OwO){
    for (int i = 0; i < OwO->taille; i++)
    {
        printf("%s:\n",OwO->tableaux_Somet_hauteur[i].hauteur);    
        for (int j = 0; j < OwO->tableaux_Somet_hauteur[i].size; j++)
        {
            printf("    %s\n",OwO->tableaux_Somet_hauteur[i].heuvre[j]->titre);
        }
        printf("\n");
    }
    
} 

void printPaire_HauteurHeurvre(Paire_HauteurHeurvre * OwI,int sizeHauteurHeuvre ){
    for (int i = 0; i < sizeHauteurHeuvre ; i++)
    {
        printf("%s => %s\n",OwI[i].hauteur,OwI[i].heuvre->titre);
    }
}

int count_isolate_autor(const List_Auteur * List_des_Auteur){
    int compteur = 0;
    for (int i = 0; i < List_des_Auteur->taille; i++)
    {
        if(List_des_Auteur->tableaux_Somet_hauteur[i].size > 0){
            compteur++;
        }
    }
    return compteur;
}

void unwrap_Serilise(const List_Auteur * List_des_Auteur, FILE * output){
    //fonction d'qui fait la moyenne des hauteur pour pouvoir fair un maloque que une foit en moyenne
    fprintf(output,"%d\n",count_isolate_autor(List_des_Auteur));
    for (int i = 0; i < List_des_Auteur->taille; i++)
    {
        if(List_des_Auteur->tableaux_Somet_hauteur[i].size > 0){
            fprintf(output,"%s\n",List_des_Auteur->tableaux_Somet_hauteur[i].hauteur);
            fprintf(output,"%d\n",List_des_Auteur->tableaux_Somet_hauteur[i].size);
            for (int j = 0; j < List_des_Auteur->tableaux_Somet_hauteur[i].size; j++)
            {
                fprintf(output,"%s\n",List_des_Auteur->tableaux_Somet_hauteur[i].heuvre[j]->titre);
            }
        }

    }
}


//DOUBLON DE PARSING FAIR UN FICHIER UTILS OU ON LE MET
void enlever_retour_a_la_ligne(char * ligne);

List_Auteur * unwrap_Deserilise(FILE * input){
    char ligne[BALISESIZE];
    List_Auteur * master_List_Auteur = malloc(sizeof(List_Auteur));
    master_List_Auteur->taille=0;
    fgets(ligne,BALISESIZE,input);
        exitIfNull(sscanf(ligne,"%i\n",&master_List_Auteur->taille),"nombre de structure manquand ...")

    //optimiser car on alloue tout en un malloc ! par contre ça peut echouer a voir
    Sommet_Auteur_TableauxD * Sommet_Auteur_Tableaux =  malloc(sizeof(Sommet_Auteur_TableauxD)*master_List_Auteur->taille);  //<= je fait une liste de quoi ?
    exitIfNull(Sommet_Auteur_Tableaux, "creation des sommet auteur tableaxD malloc null")
    master_List_Auteur->tableaux_Somet_hauteur = Sommet_Auteur_Tableaux; //<=associasioin bonne ?

    int i = 0;
    while (fgets(ligne,BALISESIZE,input))
    {
        if (feof(input))
        {
            fprintf(stderr,"fin fichier");
            exit(3);
        }
        enlever_retour_a_la_ligne(ligne);
        master_List_Auteur->tableaux_Somet_hauteur[i].hauteur = strdup(ligne);
        fgets(ligne,BALISESIZE,input);
        exitIfNull(sscanf(ligne,"%i\n", &master_List_Auteur->tableaux_Somet_hauteur[i].size),"auteur qui n'om pas d'article\n");
        
        master_List_Auteur->tableaux_Somet_hauteur[i].heuvre = malloc(master_List_Auteur->tableaux_Somet_hauteur[i].size*sizeof(Sommet_Auteur_TableauxD)); //<= bon type ?
        exitIfNull(master_List_Auteur->tableaux_Somet_hauteur[i].heuvre,"allocation master_List_Auteur->tableaux_Somet_hauteur[i].heuvre echouser...");

        for (int u = 0; u < master_List_Auteur->tableaux_Somet_hauteur[i].size; u++)
        {
            fgets(ligne,BALISESIZE,input);
            enlever_retour_a_la_ligne(ligne);
            
            //on va crée un pointeur dynamique qui pointe sur une fiche Je sais pas si ces bon choix ...
            master_List_Auteur->tableaux_Somet_hauteur[i].heuvre[u] = malloc(sizeof(8));
            exitIfNull(master_List_Auteur->tableaux_Somet_hauteur[i].heuvre[u],"allocation nouvel fiche_minimal echouer")
            /* //! \\ On va fair stoquer le noms de l'oteur dans une addresse structure pas encore lier  //!\\ */
            master_List_Auteur->tableaux_Somet_hauteur[i].heuvre[u]->titre = strdup(ligne);//<= générée un tableaux?
        }
        i++;
    }

    //Fonction pour associer ces valeur au structure ?
    //master_List_Auteur[i].tableaux_Somet_hauteur[u]    
    return master_List_Auteur;
}

//PABIEN
#define MAXarraySIZE 21143793
Paire_HauteurHeurvre HauteurHeuvre[MAXarraySIZE];

List_Auteur * unwrap_from_file(FILE * inputFile){

    tableaux_fiche mesfiches = deserialisation(inputFile);
    int sizeHauteurHeuvre = SwapStruct(mesfiches,HauteurHeuvre);
    sort_tableaux_fiche(HauteurHeuvre,sizeHauteurHeuvre);
    List_Auteur * malistedauteur = gen_List_Auteur(HauteurHeuvre,sizeHauteurHeuvre);
    return malistedauteur;
}

// List_Auteur * unwrap_de_serilise(FILE * input){

// }


// void convertStruct(tableaux_fiche input, ll_list * list_chainer_auteur ){
//     for (int i = 0; i < input.taille; i++)
//     {
//         for (int u = 0; u < input.fiche[i]->nombre_auteur; u++)
//         {
//             add_entry(list_chainer_auteur,input.fiche[i]->liste_auteur[u],input.fiche[i]->titre);
//         }
//         float avancement = ((float)(i+1)/(float)input.taille)*100;
//         printf("avancement: %f\n",avancement);
//     }
// }

