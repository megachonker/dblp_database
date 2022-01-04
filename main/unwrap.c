#include <stdio.h>
#include <stdlib.h>
#include "parsing.h"
#include "list.h"
#include "unwrap.h"
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



/**
 * @brief fonction de comparaison des auteur pour qsort
 * 
 * elle pourait être mieux
 * 
 * @param [in] a object A
 * @param [in] b object B
 * @return int 
 */
int comphauteur(const void * a, const void * b){
    //moche
    Paire_ArticleHauteur * aa = (Paire_ArticleHauteur*)a;
    Paire_ArticleHauteur * bb = (Paire_ArticleHauteur*)b;
    int result = strcmp(aa->article,bb->article);
    return result;
}

/**
 * @brief fonction de comparaison des article pour qsort
 * 
 * elle pourait être mieux
 * 
 * @param [in] a object A
 * @param [in] b object B
 * @return int 
 */
int 
comparticle(const void * a, const void * b){
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


int SwapPaire_HauteurHeurvreToPaire_HauteurHeurvre(const List_Auteur * input, Paire_ArticleHauteur * Article_auteur_Array ){
    int indice = 0;
    for (int i = 0; i < input->taille; i++)
    {
        for (int u = 0; u < input->tableaux_Somet_hauteur[i].size; u++)
        {   
            Article_auteur_Array[indice].article = input->tableaux_Somet_hauteur[i].heuvre[u]->titre;
            Article_auteur_Array[indice].pointeur_Auteur =  &input->tableaux_Somet_hauteur[i];
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
 * auteurA => hoeuvreB\n
 * auteurA => hoeuvreA\n
 * auteurA => hoeuvreU\n
 * auteurA => hoeuvreT\n
 * auteurB => hoeuvreB\n
 * auteurB => hoeuvreA\n
 * auteurB => hoeuvreU\n
 * auteurB => hoeuvreT\n
 * 
 * @param [in,out]  HauteurHeuvre     Structure a trier
 * @param [in]      sizeHauteurHeuvre taille de la tructure
 */
void sort_tableaux_fiche(Paire_HauteurHeurvre * HauteurHeuvre,int sizeHauteurHeuvre ){
    qsort(HauteurHeuvre,sizeHauteurHeuvre ,sizeof(Paire_HauteurHeurvre),comphauteur);
}
/**
 * @brief 
 * 
 * 
 * hoeuvreA => auteurA \n
 * hoeuvreA => auteurD \n
 * hoeuvreA => auteurZ \n
 * hoeuvreA => auteurA \n
 * hoeuvreB => auteurB \n
 * hoeuvreB => auteurB \n
 * hoeuvreB => auteurY \n
 * hoeuvreB => auteurB \n
 * 
 * @param ArticleuHauteur 
 * @param sizeArticleHauteur 
 */
void sort_tableaux_Article(Paire_ArticleHauteur * ArticleuHauteur,int sizeArticleHauteur ){
    qsort(ArticleuHauteur,sizeArticleHauteur ,sizeof(Paire_ArticleHauteur),comparticle);
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



void printPaire_HeurvreHauteur(Paire_ArticleHauteur * OwI,int sizeHauteurHeuvre ){
    for (int i = 0; i < sizeHauteurHeuvre ; i++)
    {
        printf("%s => %s\n",OwI[i].article,OwI[i].pointeur_Auteur->hauteur);
    }
}

List_Auteur* gen_List_Auteur(const Paire_HauteurHeurvre * liste,int sizeHauteurHeuvre){
    List_Auteur * listes_Auteur_arrTitre = malloc(sizeof(List_Auteur));
    exitIfNull(listes_Auteur_arrTitre,"Erreur création liste de List_Auteur\n")
    listes_Auteur_arrTitre->taille=-1;//moche !
    int indiceSommet = 0;
    listes_Auteur_arrTitre->tableaux_Somet_hauteur = malloc(sizeof(Sommet_Auteur_TableauxD)); //comment ça pouvais marcher au paravent ???
    exitIfNull(listes_Auteur_arrTitre->tableaux_Somet_hauteur,"Erreur création de 1 Sommet_Auteur_TableauxD\n")

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
        //nombre délément
        listes_Auteur_arrTitre->tableaux_Somet_hauteur[listes_Auteur_arrTitre->taille].nbelementmagi = 0;
        listes_Auteur_arrTitre->tableaux_Somet_hauteur[listes_Auteur_arrTitre->taille].pointeur_Article = NULL;
        // indiceSommet++;
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

List_Article* gen_List_Article(Paire_ArticleHauteur * liste,int sizeArticleHauteur){
    List_Article * ListDesArticle = malloc(sizeof(List_Article));
    exitIfNull(ListDesArticle,"Erreur création liste de List_Article\n")
    ListDesArticle->nombre_Article=-1;//moche !

    //on parcoure liste
    for (int j = 0; j < sizeArticleHauteur; j=j)//on incrémenta pas la
    {
        ListDesArticle->nombre_Article++;
        Sommet_Article_TableauxD * tb_Somet_h = reallocarray(ListDesArticle->pointeur_Article_tableaux,ListDesArticle->nombre_Article+1,sizeof(Sommet_Article_TableauxD));
        exitIfNull(tb_Somet_h,"Erreur création de Sommet_Auteur_TableauxD\n")
        ListDesArticle->pointeur_Article_tableaux = tb_Somet_h;

        //on add le premier Article
        ListDesArticle->pointeur_Article_tableaux[ListDesArticle->nombre_Article].Article=liste[j].article;
        ListDesArticle->pointeur_Article_tableaux[ListDesArticle->nombre_Article].nombre_Auteur=0;
        
        ListDesArticle->pointeur_Article_tableaux[ListDesArticle->nombre_Article].pointeur_Auteur_tableaux = malloc(sizeof(Sommet_Auteur_TableauxD)); //maloc pour ladresse qui contiendra le tableaux ?
        exitIfNull(ListDesArticle->pointeur_Article_tableaux[ListDesArticle->nombre_Article].pointeur_Auteur_tableaux,"pointeur_Auteur_tableaux imposible");

        int i = 1;
        //tant le prochain est le meme auteur et que on attein pas la fin de la liste
        while (i+j < sizeArticleHauteur && strcmp(liste[j].article,liste[j+i].article) == 0)//ordre important
        {
            Sommet_Article_TableauxD * dernierarticle = &ListDesArticle->pointeur_Article_tableaux[ListDesArticle->nombre_Article];
            int * last_auteur  = &dernierarticle->nombre_Auteur;
            
            Sommet_Auteur_TableauxD * temparray = reallocarray(dernierarticle->pointeur_Auteur_tableaux,*last_auteur+1,8); //8 taille d'un pointeur 
            exitIfNull(temparray,"gen_List_Article Sommet_Auteur_TableauxD realockarrayfail\n");
            
            
            dernierarticle->pointeur_Auteur_tableaux = (Sommet_Auteur_TableauxD**)temparray;
            dernierarticle->pointeur_Auteur_tableaux[*last_auteur] = liste[i+j].pointeur_Auteur;
            int f=0;

            //on vérifie pas de douvbon avand d'ajouter
            for (int o = 0; o < dernierarticle->pointeur_Auteur_tableaux[*last_auteur]->nbelementmagi; o++)
            {
                if (dernierarticle->pointeur_Auteur_tableaux[*last_auteur]->pointeur_Article[o] == dernierarticle){
                    f = 1;
                    break;
                }
            }

            if (f == 0)
            {
                Sommet_Article_TableauxD ** tmptest  = reallocarray(dernierarticle->pointeur_Auteur_tableaux[*last_auteur]->pointeur_Article,
                dernierarticle->pointeur_Auteur_tableaux[*last_auteur]->nbelementmagi+1,sizeof(Sommet_Article_TableauxD**));
                exitIfNull(tmptest,"imposible alouer dernierarticle->pointeur_Auteur_tableaux[*last_auteur]->pointeur_Article[i]\n");
                dernierarticle->pointeur_Auteur_tableaux[*last_auteur]->pointeur_Article = tmptest;
                //on boucle 
                dernierarticle->pointeur_Auteur_tableaux[*last_auteur]->pointeur_Article[dernierarticle->pointeur_Auteur_tableaux[*last_auteur]->nbelementmagi] = dernierarticle;
                dernierarticle->pointeur_Auteur_tableaux[*last_auteur]->nbelementmagi++;
            }


            (*last_auteur)++;
            i++;// truc de simon ?
        }

        j+=i;//mais ici

        // Sommet_Article_TableauxD Sometgenere = ListDesArticle->pointeur_Article_tableaux[ListDesArticle->nombre_Article];
        // fprintf(stderr,"%s\n",Sometgenere.Article);
        // fprintf(stderr,"\tnombre d'auteur %d\n",Sometgenere.nombre_Auteur); ///BIZARD BUG ?
        // for (int ii = 0; ii < Sometgenere.nombre_Auteur; ii++)
        // {
        //     fprintf(stderr,"\t%s\n",Sometgenere.pointeur_Auteur_tableaux[ii]->hauteur);
        //     fprintf(stderr,"\t\tnombre d'Article %d\n",Sometgenere.pointeur_Auteur_tableaux[ii]->nbelementmagi); ///BIZARD BUG ?
        //     for (int Uu = 0; Uu < Sometgenere.pointeur_Auteur_tableaux[ii]->nbelementmagi; Uu++)
        //     {
        //         fprintf(stderr,"\t\t%s\n",Sometgenere.pointeur_Auteur_tableaux[ii]->pointeur_Article[Uu]->Article);
        //     }
         
        // }

    }
    // for (int i = 0; i < ListDesArticle->nombre_Article; i++)
    // {
    //     fprintf(stderr,"%s\n",ListDesArticle->pointeur_Article_tableaux[i].pointeur_Auteur_tableaux[0]->pointeur_Article[0]->Article);
    // }
    


    return ListDesArticle;
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


void printList_Article(List_Article * OwO){
    for (int i = 0; i < OwO->nombre_Article; i++)
    {
        printf("%s:\n",OwO->pointeur_Article_tableaux[i].Article);    
        for (int j = 0; j < OwO->pointeur_Article_tableaux[i].nombre_Auteur; j++)
        {
            printf("    %s\n",OwO->pointeur_Article_tableaux[i].pointeur_Auteur_tableaux[j]->hauteur);
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

// void unwrap_Serilise(const List_Auteur * List_des_Auteur, FILE * output){
//     //fonction d'qui fait la moyenne des hauteur pour pouvoir fair un maloque que une foit en moyenne
//     fprintf(output,"%d\n",count_isolate_autor(List_des_Auteur));
//     for (int i = 0; i < List_des_Auteur->taille; i++)
//     {
//         if(List_des_Auteur->tableaux_Somet_hauteur[i].size > 0){
//             fprintf(output,"%s\n",List_des_Auteur->tableaux_Somet_hauteur[i].hauteur);
//             fprintf(output,"%d\n",List_des_Auteur->tableaux_Somet_hauteur[i].size);
//             for (int j = 0; j < List_des_Auteur->tableaux_Somet_hauteur[i].size; j++)
//             {
//                 fprintf(output,"%s\n",List_des_Auteur->tableaux_Somet_hauteur[i].heuvre[j]->titre);
//             }
//         }

//     }
// }

void unwrap_Serilise_Index(const List_Auteur * List_des_Auteur, FILE * output){
    //fonction d'qui fait la moyenne des hauteur pour pouvoir fair un maloque que une foit en moyenne
    fprintf(output,"%d\n",count_isolate_autor(List_des_Auteur));
    for (int i = 0; i < List_des_Auteur->taille; i++)
    {
        if(List_des_Auteur->tableaux_Somet_hauteur[i].size > 0){
            // List_des_Auteur->tableaux_Somet_hauteur[i].
            // fprintf(output,"%d\n",List_des_Auteur->tableaux_Somet_hauteur[i].DECALAGE);
            fprintf(output,"%s\n",List_des_Auteur->tableaux_Somet_hauteur[i].hauteur);//char 1o addresse 8o
            fprintf(output,"%d\n",List_des_Auteur->tableaux_Somet_hauteur[i].size);
            for (int j = 0; j < List_des_Auteur->tableaux_Somet_hauteur[i].size; j++)
            {
                //ma fiche minimal est contenue dans Sommet_Auteur_TableauxD et dans tableaux fiche 
                fprintf(output,"%d\n",List_des_Auteur->tableaux_Somet_hauteur[i].heuvre[j]->ADDR);
            }
        }

    }
}


//DOUBLON DE PARSING FAIR UN FICHIER UTILS OU ON LE MET
void enlever_retour_a_la_ligne(char * ligne);

// List_Auteur * unwrap_Deserilise(FILE * input){
//     char ligne[BALISESIZE];
//     List_Auteur * master_List_Auteur = malloc(sizeof(List_Auteur));
//     master_List_Auteur->taille=0;
//     fgets(ligne,BALISESIZE,input);
//         exitIfNull(sscanf(ligne,"%i\n",&master_List_Auteur->taille),"nombre de structure manquand ...")

//     //optimiser car on alloue tout en un malloc ! par contre ça peut echouer a voir
//     Sommet_Auteur_TableauxD * Sommet_Auteur_Tableaux =  malloc(sizeof(Sommet_Auteur_TableauxD)*master_List_Auteur->taille);  //<= je fait une liste de quoi ?
//     exitIfNull(Sommet_Auteur_Tableaux, "creation des sommet auteur tableaxD malloc null")
//     master_List_Auteur->tableaux_Somet_hauteur = Sommet_Auteur_Tableaux; //<=associasioin bonne ?

//     int i = 0;
//     while (fgets(ligne,BALISESIZE,input))
//     {
//         if (feof(input))
//         {
//             fprintf(stderr,"fin fichier");
//             exit(3);
//         }
//         enlever_retour_a_la_ligne(ligne);
//         master_List_Auteur->tableaux_Somet_hauteur[i].hauteur = strdup(ligne);
//         fgets(ligne,BALISESIZE,input);
//         exitIfNull(sscanf(ligne,"%i\n", &master_List_Auteur->tableaux_Somet_hauteur[i].size),"auteur qui n'om pas d'article\n");
        
//         master_List_Auteur->tableaux_Somet_hauteur[i].heuvre = malloc(master_List_Auteur->tableaux_Somet_hauteur[i].size*sizeof(Sommet_Auteur_TableauxD)); //<= bon type ?
//         exitIfNull(master_List_Auteur->tableaux_Somet_hauteur[i].heuvre,"allocation master_List_Auteur->tableaux_Somet_hauteur[i].heuvre echouser...");

//         for (int u = 0; u < master_List_Auteur->tableaux_Somet_hauteur[i].size; u++)
//         {
//             fgets(ligne,BALISESIZE,input);
//             enlever_retour_a_la_ligne(ligne);
            
//             //on va crée un pointeur dynamique qui pointe sur une fiche Je sais pas si ces bon choix ...
//             master_List_Auteur->tableaux_Somet_hauteur[i].heuvre[u] = malloc(sizeof(8));
//             exitIfNull(master_List_Auteur->tableaux_Somet_hauteur[i].heuvre[u],"allocation nouvel fiche_minimal echouer")
//             /* //! \\ On va fair stoquer le noms de l'oteur dans une addresse structure pas encore lier  //!\\ */
//             master_List_Auteur->tableaux_Somet_hauteur[i].heuvre[u]->titre = strdup(ligne);//<= générée un tableaux?
//         }
//         i++;
//     }

//     //Fonction pour associer ces valeur au structure ?
//     //master_List_Auteur[i].tableaux_Somet_hauteur[u]

//     return master_List_Auteur;
// }


List_Auteur * unwrap_Deserilise_Index(const tableaux_fiche * tableaux_fiche,FILE * input){
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
                                                                /// STR JE VEUx iNDICE
        master_List_Auteur->tableaux_Somet_hauteur[i].hauteur = strdup(ligne);
        // //on catch l'id du char
        // exitIfNull(sscanf(ligne,"%i\n", &master_List_Auteur->tableaux_Somet_hauteur[i].DECALAGE),"auteur qui n'om pas d'article\n");
        // //rename par le bon noms d'auteur la fiche crée 
        // master_List_Auteur->tableaux_Somet_hauteur[i].hauteur = tableaux_fiche->fiche[master_List_Auteur->tableaux_Somet_hauteur[i].DECALAGE];
        // on initialise le compteur d'élément 
        master_List_Auteur->tableaux_Somet_hauteur[i].nbelementmagi = 0;
        master_List_Auteur->tableaux_Somet_hauteur[i].pointeur_Article = NULL;

        fgets(ligne,BALISESIZE,input);
        exitIfNull(sscanf(ligne,"%i\n", &master_List_Auteur->tableaux_Somet_hauteur[i].size),"auteur qui n'om pas d'article\n");
        
        master_List_Auteur->tableaux_Somet_hauteur[i].heuvre = malloc(master_List_Auteur->tableaux_Somet_hauteur[i].size*sizeof(Sommet_Auteur_TableauxD)); //<= bon type ?
        exitIfNull(master_List_Auteur->tableaux_Somet_hauteur[i].heuvre,"allocation master_List_Auteur->tableaux_Somet_hauteur[i].heuvre echouser...");

        for (int u = 0; u < master_List_Auteur->tableaux_Somet_hauteur[i].size; u++)
        {
            fgets(ligne,BALISESIZE,input);
            enlever_retour_a_la_ligne(ligne);
            
            int a = 0;
            //on fait des sscanf de fgets ... on peut le faire directement 37% de perte perf a cause du sscanf !
            sscanf(ligne,"%d",&a);
            exitIfNull(tableaux_fiche->fiche[a],"serialise index pointeur sur heuvre introuvable\n")
            master_List_Auteur->tableaux_Somet_hauteur[i].heuvre[u] = tableaux_fiche->fiche[a];
        }
        i++;
    }
    return master_List_Auteur;
}




// void unwrap_sinc(List_Auteur * List_des_Auteur ,const tableaux_fiche input){
//     for (int i = 0; i < List_des_Auteur->taille; i++)
//     {
//         for (int u = 0; u < List_des_Auteur->tableaux_Somet_hauteur[i].size; u++)
//         {
//             for (int j = 0; j < input.taille; j++)
//             {
//                 if (strcmp(List_des_Auteur->tableaux_Somet_hauteur[i].heuvre[u]->titre,input.fiche[j]->titre)==0)
//                 {
//                     List_des_Auteur->tableaux_Somet_hauteur[i].heuvre[u] = input.fiche[j];
//                     break;
//                 } 
//             }
//             // printf("%d/%d et %d/%d\n",i,List_des_Auteur->taille,u,List_des_Auteur->tableaux_Somet_hauteur[i].size);
//         }
//     }
    
// }

// /**
//  * @brief 
//  * 
//  * 
//  * n'ayant pas les object Euvre/auteur
//  *  apres la décérialisation
//  *  ajout fonction résolution qui va ajouterune entrée a chaque foit qu'on l'interroge
//  *  de magnierre a ce qu'il soit possible d'executer l'algo sans avoir tout résolut
//  *
//  *  néamoins recalculer depuit from file est plus rapide ...
//  * 
//  * @param List_des_Auteur 
//  * @param resove 
//  * @param input 
//  */
// void unwrap_resolve(List_Auteur * List_des_Auteur, Sommet_Auteur_TableauxD * resove, const tableaux_fiche * input){
//     int i = 0;
//     int b = 0;
//     while (i < List_des_Auteur->taille)
//     {
//         if(strcmp(List_des_Auteur->tableaux_Somet_hauteur[i].hauteur,resove->hauteur)==0){
//             b = 1;
//             break;
//         }
//         i++;
//     }
//     if (b == 0)
//     {
//         fprintf(stderr,"L'ors de la résolution je n'ais pas trouver l'autaure qui corespond a %s",List_des_Auteur->tableaux_Somet_hauteur[i].hauteur);
//         exit(3);
//     }
    
//     for (int u = 0; u < List_des_Auteur->tableaux_Somet_hauteur[i].size; u++)
//     {
//         for (int j = 0; j < input->taille; j++)
//         {
//             if (strcmp(List_des_Auteur->tableaux_Somet_hauteur[i].heuvre[u]->titre,input->fiche[j]->titre)==0)
//             {
//                 List_des_Auteur->tableaux_Somet_hauteur[i].heuvre[u] = input->fiche[j];
//                 break;
//             } 
//         }
//         // printf("%d/%d\n",u,List_des_Auteur->tableaux_Somet_hauteur[i].size);
//     }
// }

//PABIEN
#define MAXarraySIZE 21143793
Paire_HauteurHeurvre HauteurHeuvre[MAXarraySIZE];

List_Auteur * unwrap_from_tabfich(tableaux_fiche * mesfiches){
    int sizeHauteurHeuvre = SwapStruct(*mesfiches,HauteurHeuvre);
    sort_tableaux_fiche(HauteurHeuvre,sizeHauteurHeuvre);
    List_Auteur * malistedauteur = gen_List_Auteur(HauteurHeuvre,sizeHauteurHeuvre);
    return malistedauteur;
}

List_Auteur * unwrap_from_file(FILE * inputFile){

    tableaux_fiche * mesfiches = deserialisation(inputFile);
    int sizeHauteurHeuvre = SwapStruct(*mesfiches,HauteurHeuvre);
    sort_tableaux_fiche(HauteurHeuvre,sizeHauteurHeuvre);
    List_Auteur * malistedauteur = gen_List_Auteur(HauteurHeuvre,sizeHauteurHeuvre);
    return malistedauteur;
}

List_Article * gen_ListaArticle(const List_Auteur * Malistauteur){
    //compte le nombre de structure pour le maloc
    int nbstructure = 0;
    for (int i = 0; i < Malistauteur->taille; i++)
    {
        nbstructure+=Malistauteur->tableaux_Somet_hauteur[i].size;/// lerreur etait la
    }
    Paire_ArticleHauteur * Paire_HauteurHeurvre = calloc(nbstructure,sizeof(Sommet_Article_TableauxD));
    exitIfNull(Paire_HauteurHeurvre,"imposible de crée Paire_HauteurHeurvre");
    int sizeHauteurHeuvre = SwapPaire_HauteurHeurvreToPaire_HauteurHeurvre(Malistauteur,Paire_HauteurHeurvre);
    sort_tableaux_Article(Paire_HauteurHeurvre,sizeHauteurHeuvre);
    List_Article * malistedauteur = gen_List_Article(Paire_HauteurHeurvre,sizeHauteurHeuvre);
    return malistedauteur;
}


unwrap_Graph gen_unwrap_Graph(FILE * dblpxml, FILE * inverted){
    tableaux_fiche * matablefiche = deserialisation(dblpxml);
    List_Auteur * malistaauteur =   unwrap_Deserilise_Index(matablefiche,inverted);
    List_Article * malistearticle = gen_ListaArticle(malistaauteur);
    unwrap_Graph graph  = {malistaauteur, malistearticle,matablefiche};
    return graph;
}



void unwrap_List_Auteur_free(List_Auteur * afree){
    for (int i = 0; i < afree->taille; i++)
    {
        free(afree->tableaux_Somet_hauteur[i].hauteur);   
    }
    free(afree->tableaux_Somet_hauteur);
}

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




    // listes_Auteur_arrTitre->taille++;
    // Sommet_Auteur_TableauxD * new_array = calloc((listes_Auteur_arrTitre->taille+1),sizeof(Sommet_Auteur_TableauxD));
    // exitIfNull(new_array,"Newarray fail alloc !\n");
    // memcpy(new_array,listes_Auteur_arrTitre->tableaux_Somet_hauteur,(listes_Auteur_arrTitre->taille)*sizeof(Sommet_Auteur_TableauxD)); // < ne déplace pas ...
    // free(listes_Auteur_arrTitre->tableaux_Somet_hauteur); // < double free or corruption (out)
    // listes_Auteur_arrTitre->tableaux_Somet_hauteur = new_array;
    // free(new_array);