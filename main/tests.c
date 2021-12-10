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
#define MAXarraySIZE 21143793

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
    fiche_minimal ** heuvre;///<tableaux dynamique d'adresse pointant sur des structure contenant oeuvre
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


Paire_HauteurHeurvre HauteurHeuvre[MAXarraySIZE];

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
    // printf("r %i",result);
    // if (aa->hauteur==bb->hauteur)
    // {
    //     return 0;
    // }
    
    
    // if ( result == 0)
    // {
        // optimisation de la mort
    // }
    return result;
}

/**
 * @brief Affiche hauteur <=> Heuvre
 * 
 * @param [in] OwI  Paire_HauteurHeurvre
 * @param [in] sizeHauteurHeuvre nombre d'élément 
 */
void printPaire_HauteurHeurvre(Paire_HauteurHeurvre * OwI,int sizeHauteurHeuvre ){
    for (int i = 0; i < sizeHauteurHeuvre ; i++)
    {
        printf("%s => %s\n",OwI[i].hauteur,OwI[i].heuvre->titre);
    }
}

/**
 * @brief génère un tableaux d' HauteurToHeurvre 
 * 
 * déplie tableaux_fiche pour généré unt tableaux
 * d'élément Paire_HauteurHeurvre
 * qui est une association auteur <=> heuvre unique
 * 
 * @param [in]  input toute les fiche des oeuvre qui comporte les liste auteur  
 * @param [out] arrayout liste qui associe un auteur a une oeuvre
 * @return nombre d'élément du tableaux
 */
int convertStruct(tableaux_fiche input, Paire_HauteurHeurvre * arrayout ){
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

/**
 * @brief Trie Paire_HauteurHeurvre Par noms d'auteur
 * 
 * trie le tableaux Paire_HauteurHeurvre par auteur
 * de facon a avoir toute les oeuvre du meme auteur facilement
 * 
 * auteurA => hoeuvreB 
 * auteurA => hoeuvreA
 * auteurA => hoeuvreU
 * auteurA => hoeuvreT
 * auteurB => hoeuvreB 
 * auteurB => hoeuvreA
 * auteurB => hoeuvreU
 * auteurB => hoeuvreT
 * 
 * @param [in,out]  HauteurHeuvre     Structure a trier
 * @param [in]      sizeHauteurHeuvre taille de la tructure
 */
void sort_tableaux_fiche(Paire_HauteurHeurvre * HauteurHeuvre,int sizeHauteurHeuvre ){
    qsort(HauteurHeuvre,sizeHauteurHeuvre ,sizeof(Paire_HauteurHeurvre),comphauteur);
}

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

void printList_Auteur(List_Auteur OwO){
    for (int i = 0; i < OwO.taille; i++)
    {
        printf("%s:\n",OwO.tableaux_Somet_hauteur[i].hauteur);    
        for (int j = 0; j < OwO.tableaux_Somet_hauteur[i].size; j++)
        {
            printf("    %s\n",OwO.tableaux_Somet_hauteur[i].heuvre[j]->titre);
        }
        printf("\n");
    }
    
} 

int main()
{
    //lire tout le fichier pour le metrte en maloc est faire un vieux fseek

    FILE * out = fopen("DATA/SerializedStruc.data","w");
    exitIfNull(out,"INPUT PAS CHEMAIN")
    FILE * inputDB1 = fopen("DATA/dblp.xml","r");
    exitIfNull(inputDB1,"INPUT PAS CHEMAIN")
    tableaux_fiche mesfiches1 = parse(inputDB1);
    serialize(mesfiches1,out);


    // FILE * inputDB = fopen("DATA/SerializedStruc.data","r");
    // exitIfNull(inputDB,"INPUT PAS CHEMAIN")
    // tableaux_fiche mesfiches = deserialisation(inputDB);

    // ll_list * Liste_chainer = deserialisation_Liste(inputDB);
    // ll_list_link(Liste_chainer);
    // print_liste_chainer_Auteur_titre(Liste_chainer);


    // int sizeHauteurHeuvre = convertStruct(mesfiches,HauteurHeuvre);
    // // printPaire_HauteurHeurvre(HauteurHeuvre);
    // sort_tableaux_fiche(HauteurHeuvre,sizeHauteurHeuvre );
    // List_Auteur * malistedauteur = gen_List_Auteur(HauteurHeuvre,sizeHauteurHeuvre);

    // printList_Auteur(*malistedauteur);
    // // printTabmeaux(mesfiches);

    // ll_list * Liste_chainer = ll_create();
    // Sommet_Auteur_ListChainer new_sommet;
    // new_sommet.auteur = mesfiches.fiche[0]->liste_auteur[0];
    // new_sommet.titre_article = ll_create();
    // ll_append(new_sommet.titre_article,mesfiches.fiche[0]->titre);
    // ll_append(Liste_chainer,&new_sommet);

    // convertStruct(mesfiches,Liste_chainer);

    // print_liste_chainer_Auteur_titre(Liste_chainer);

    

    // printPaire_HauteurHeurvre(Liste_chainer);
    // printPaire_HauteurHeurvre(Liste_chainer,sizeHauteurHeuvre );


    //liste des hauteur trier
    //dans la fonction de trie si 2 foit meme hauteur crée un structure SommetHauteur qui liste les hauteur
    //a chaque comparaison qui match on suprime les occurance le mieux est de décaler 
    //on peut faire une pille de comparaison pour en faire en paralle

    //si  tableaux fiche est déja full trier pour il faudra chercher que les premierre occurance donc gain de tems ?

    // creation_de_la_liste_des_listes_de_sommet_des_sous_graphes_connexes(mesfiches);


    //auteur ===> liste cooauteur 
        // list auteur liste article => liste cooteur

    //les hash avec des chiffreeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeemlkjmlkjmlkjmlkjlmkjlmkjlmklmkjmlkjlkmjlmkjlmkjmlkmlkjmlkjmlkjmlkjmlkjmlkjlmkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkmdv

    return 0;
}

