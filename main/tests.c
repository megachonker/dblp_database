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

#define MaxTitre 5
#define MaxHauteur 2994451

/**
 * @brief couple Hauteur <=> Heuvre
 */
typedef struct hauteurToHeurvre
{
    char * hauteur;
    fiche_minimal * heuvre;
}hauteurToHeurvre;

/**
 * @brief Stoque tout les Sommet_hauteur
 * 
 * sous forme de tableaux DYNAMIQUE d'adresse pointant sur Sommet_hauteur
 * ainsie que le nombre d'élément (Sommet_hauteur) stoquer dans le tableaux 
 */
typedef struct List_Auteur
{
    Sommet_hauteur ** tableaux_Somet_hauteur;
    int taille;
}List_Auteur;

typedef struct Sommet_hauteur
{
    char * hauteur;
    fiche_minimal * heuvre[MAXarraySIZE];//faire une liste chainer ou des malloc
    // int size;
}Sommet_hauteur;


hauteurToHeurvre HauteurHeuvre[MAXarraySIZE];
// Sommet_hauteur list_sommet[MaxHauteur];

/**
 * @brief fonction de comparaison pour qsort
 * 
 * elle pourait être mieux
 * 
 * @param a 
 * @param b 
 * @return int 
 */
int comphauteur(const void * a, const void * b){
    //moche
    hauteurToHeurvre * aa = (hauteurToHeurvre*)a;
    hauteurToHeurvre * bb = (hauteurToHeurvre*)b;
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
 * @param OwI 
 * @param sizeHauteurHeuvre 
 */
void printHauteur_Heuvre(hauteurToHeurvre * OwI,int sizeHauteurHeuvre ){
    for (int i = 0; i < sizeHauteurHeuvre ; i++)
    {
        printf("%s => %s\n",OwI[i].hauteur,OwI[i].heuvre->titre);
    }
}

/**
 * @brief génère un tableaux d' HauteurToHeurvre 
 * 
 * déplie tableaux_fiche pour généré unt tableaux
 * d'élément hauteurToHeurvre
 * qui est une association auteur <=> heuvre unique
 * 
 * @param [in]  input toute les fiche des oeuvre qui comporte les liste auteur  
 * @param [out] arrayout liste qui associe un auteur a une oeuvre
 * @return nombre d'élément du tableaux
 */
int convertStruct(tableaux_fiche input, hauteurToHeurvre * arrayout ){
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
 * @brief Trie hauteurToHeurvre Par noms d'auteur
 * 
 * trie le tableaux hauteurToHeurvre par auteur
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
void sort_tableaux_fiche(hauteurToHeurvre * HauteurHeuvre,int sizeHauteurHeuvre ){
    qsort(HauteurHeuvre,sizeHauteurHeuvre ,sizeof(hauteurToHeurvre),comphauteur);
}

void add_titre_to_auteur(Sommet_hauteur * list,const hauteurToHeurvre HtH){//ces plus logic comme ça mais pluslent ?
    //on enumere tout les somet
    for (int i = 0; i < MaxHauteur; i++)
    {
        //on match quand un sommet hauteur match avec l'auteur qu'on veux add
        if(list[i].hauteur == HtH.hauteur){
            //on detecte la fin du tableaux  est on add
            for (int u = 0; u < MaxTitre; u++)// on cherche a chaque foit sinon on doit stoquer uen variable de taille de tab est ces chian
            {
                //quand ces vide ?
                if (!list[i].heuvre[u])
                {
                    list[i].heuvre[u] = HtH.heuvre;
                }
            }  
        }
    }
    
}

List_Auteur* unique_HtH(const hauteurToHeurvre * liste,int sizeHauteurHeuvre){
    List_Auteur * list_sommet = malloc(sizeof(List_Auteur));
    list_sommet->taille=0;
    exitIfNull(list_sommet,"Erreur création liste de sommet\n")
    for (int j = 0; j < sizeHauteurHeuvre; j=j)//on incrémenta pas la
    {
        //on add le premier hauteur a notre 
        list_sommet->tableaux_Somet_hauteur[list_sommet->taille]->hauteur=&liste[j].hauteur;
        int i = 1;
        //tant le prochain est le meme auteur
        while (liste[j].hauteur == liste[j+i].hauteur && i+j < sizeHauteurHeuvre)
        {
            add_titre_to_auteur(list_sommet,liste[i+j]);
            i++;// truc de simon ?
        }
        
        j+=i;//mais ici
    }
}




int main()
{
    //lire tout le fichier pour le metrte en maloc est faire un vieux fseek

    // FILE * out = fopen("DATA/SerializedStruc.data","w");
    // exitIfNull(out,"INPUT PAS CHEMAIN")
    // FILE * inputDB = fopen("DATA/dblp.xml","r");
    // exitIfNull(inputDB,"INPUT PAS CHEMAIN")
    // tableaux_fiche mesfiches = parse(inputDB);
    // serialize(mesfiches,out);


    FILE * inputDB = fopen("DATA/SerializedStruc.data","r");
    exitIfNull(inputDB,"INPUT PAS CHEMAIN")
    tableaux_fiche mesfiches = deserialisation(inputDB);

    // ll_list * Liste_chainer = deserialisation_Liste(inputDB);
    // ll_list_link(Liste_chainer);
    // print_liste_chainer_Auteur_titre(Liste_chainer);


    int sizeHauteurHeuvre = convertStruct(mesfiches,HauteurHeuvre);
    // printHauteur_Heuvre(HauteurHeuvre);
    sort_tableaux_fiche(HauteurHeuvre,sizeHauteurHeuvre );
    printHauteur_Heuvre(HauteurHeuvre,sizeHauteurHeuvre );
    List_Auteur * malistedauteur = unique_HtH(HauteurHeuvre,sizeHauteurHeuvre);
   
    // printTabmeaux(mesfiches);

    // ll_list * Liste_chainer = ll_create();
    // Sommet_Auteur new_sommet;
    // new_sommet.auteur = mesfiches.fiche[0]->liste_auteur[0];
    // new_sommet.titre_article = ll_create();
    // ll_append(new_sommet.titre_article,mesfiches.fiche[0]->titre);
    // ll_append(Liste_chainer,&new_sommet);

    // convertStruct(mesfiches,Liste_chainer);

    // print_liste_chainer_Auteur_titre(Liste_chainer);

    

    // printHauteur_Heuvre(Liste_chainer);
    // printHauteur_Heuvre(Liste_chainer,sizeHauteurHeuvre );


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

