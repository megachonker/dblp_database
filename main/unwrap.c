#include <stdio.h>
#include <stdlib.h>
#include "parsing.h"
#include "list.h"
#include "unwrap.h"
#include <string.h>

#include "macro.h"


/**
 * @brief Stoque tout les auteur
 * 
 * @param [in] a object A
 * @param [in] b object B
 * @return int 
 */
int comphauteur(const void * a, const void * b){
    //moche
    Paire_Article_auteur * aa = (Paire_Article_auteur*)a;
    Paire_Article_auteur * bb = (Paire_Article_auteur*)b;
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
    Paire_auteur_oeuvre * aa = (Paire_auteur_oeuvre*)a;
    Paire_auteur_oeuvre * bb = (Paire_auteur_oeuvre*)b;
    int result = strcmp(aa->nom_auteur,bb->nom_auteur);
    return result;
}

int SwapStruct(tableaux_fiche input, Paire_auteur_oeuvre * arrayout ){
    int indice = 0;
    for (int i = 0; i < input.taille; i++)
    {
        for (int u = 0; u < input.fiche[i]->nombre_auteur; u++)
        {   
            arrayout[indice].oeuvre = input.fiche[i];
            arrayout[indice].nom_auteur = input.fiche[i]->liste_auteur[u];
            indice++;
        }
    }
    return indice;
}


int SwapPaire_HauteurHeurvreToPaire_HauteurHeurvre(const tab_auteur_struct * input, Paire_Article_auteur * Article_auteur_Array ){
    DEBUG("SWAP: SwapPaire_HauteurHeurvreToPaire_HauteurHeurvre")
    int indice = 0;
    for (int i = 0; i < input->taille; i++)
    {
        for (int u = 0; u < input->tab_auteur[i].size; u++)
        {   
            Article_auteur_Array[indice].article = input->tab_auteur[i].tab_ptr_fiche_min[u]->titre;
            Article_auteur_Array[indice].pointeur_Auteur = &input->tab_auteur[i];
            // Article_auteur_Array[indice].article = *input.tab_auteur[input.tab_auteur[i].DECALAGE].oeuvre;
            // Article_auteur_Array[indice].pointeur_Auteur = &input.tab_auteur[i].tab_ptr_fiche_min[u];
            indice++;
        }
    }
    return indice;
}
/**
 * @brief Trie Paire_auteur_oeuvre Par noms d'auteur
 * 
 * trie le tableaux Paire_auteur_oeuvre par auteur
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
void sort_tableaux_fiche(Paire_auteur_oeuvre * HauteurHeuvre,int sizeHauteurHeuvre ){
    qsort(HauteurHeuvre,sizeHauteurHeuvre ,sizeof(Paire_auteur_oeuvre),comphauteur);
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
void sort_tableaux_Article(Paire_Article_auteur * ArticleuHauteur,int sizeArticleHauteur ){
    qsort(ArticleuHauteur,sizeArticleHauteur ,sizeof(Paire_Article_auteur),comparticle);
}


/**
 * @brief add_titre_to_auteur
 * 
 * 
 * @param [in,out] list  
 * @param [in] HtH       
 */
void add_titre_to_auteur(auteur_struct * list,const Paire_auteur_oeuvre HtH){//ces plus logic comme ça mais pluslent ?
    fiche_minimale ** temparray = reallocarray(list->tab_ptr_fiche_min,list->size+1,8); //8 taille d'un pointeur 
    exitIfNull(temparray,"add_titre_to_auteur realockarrayfail\n");
    list->tab_ptr_fiche_min = temparray;
    list->tab_ptr_fiche_min[list->size] = HtH.oeuvre;
    list->size++;
}



void printPaire_HeurvreHauteur(Paire_Article_auteur * OwI,int sizeHauteurHeuvre ){
    for (int i = 0; i < sizeHauteurHeuvre ; i++)
    {
        printf("%s => %s\n",OwI[i].article,OwI[i].pointeur_Auteur->nom_auteur);
    }
}

//GARDER
//print est test de profondeur 1
// for (int i = 0; i < matable->nombre_Article ; i++)
// {
//         printf("%s ==> %d\n",matable->tab_Article[i].nom_Article, matable->tab_Article[i].nombre_auteur);
//         for (int u = 0; u < matable->tab_Article[i].nombre_auteur; u++)
//         {
//             printf("\t%s ==> %d\n",matable->tab_Article[i].tab_ptr_auteur[u]->nom_auteur,matable->tab_Article[i].tab_ptr_auteur[u]->nbelementmagi);
//             for (int pp = 0; pp < matable->tab_Article[i].tab_ptr_auteur[u]->nbelementmagi; pp++)
//             {
//                 if (matable->tab_Article[i].tab_ptr_auteur[u]->tab_ptr_Article[pp]->nombre_auteur > 0 && matable->tab_Article[i].tab_ptr_auteur[u]->tab_ptr_Article[pp]->tab_ptr_auteur[0])
//                 {
//                     printf("\t\t%s ==> %d\n",matable->tab_Article[i].tab_ptr_auteur[u]->tab_ptr_Article[pp]->nom_Article,matable->tab_Article[i].tab_ptr_auteur[u]->tab_ptr_Article[pp]->nombre_auteur); 
//                     for (int UI = 0; UI < matable->tab_Article[i].tab_ptr_auteur[u]->tab_ptr_Article[pp]->nombre_auteur; UI++)
//                     {
//                         printf("\t\t\t%s\n",matable->tab_Article[i].tab_ptr_auteur[u]->tab_ptr_Article[pp]->tab_ptr_auteur[UI]->nom_auteur); 
//                     }
                                    
//                 }else{
//                     printf("NOPE\n");
//                 }
//             }           
//         }
// }

tab_auteur_struct* gen_List_Auteur(const Paire_auteur_oeuvre * liste,int sizeHauteurHeuvre){
    tab_auteur_struct * listes_Auteur_arrTitre = malloc(sizeof(tab_auteur_struct));
    exitIfNull(listes_Auteur_arrTitre,"Erreur création liste de tab_auteur_struct\n")
    int * nb_auteur = &listes_Auteur_arrTitre->taille; 

    (*nb_auteur)=0;

    listes_Auteur_arrTitre->tab_auteur = NULL;

    int j = 0;
    //on parcoure liste
    while (j < sizeHauteurHeuvre)
    {
        auteur_struct * tb_Somet_h = reallocarray(listes_Auteur_arrTitre->tab_auteur,(*nb_auteur)+1,sizeof(auteur_struct));//fasink alocate error
        exitIfNull(tb_Somet_h,"Erreur création de auteur_struct\n")
        listes_Auteur_arrTitre->tab_auteur = tb_Somet_h;
            
        //initialisation de l'auteur crée
        listes_Auteur_arrTitre->tab_auteur[(*nb_auteur)].size=0                         ;
        listes_Auteur_arrTitre->tab_auteur[(*nb_auteur)].nbelementmagi = 0              ;
        listes_Auteur_arrTitre->tab_auteur[(*nb_auteur)].nom_auteur = NULL              ;
        listes_Auteur_arrTitre->tab_auteur[(*nb_auteur)].tab_ptr_Article = NULL         ;    //ducoup malloc le code 
        listes_Auteur_arrTitre->tab_auteur[(*nb_auteur)].tab_ptr_fiche_min = NULL       ;
        listes_Auteur_arrTitre->tab_auteur[(*nb_auteur)].nom_auteur=liste[j].nom_auteur ;

        int i = 0;
        //tant le prochain est le meme auteur et que on attein pas la fin de la liste
        while (i+j < sizeHauteurHeuvre && strcmp(liste[j].nom_auteur,liste[j+i].nom_auteur) == 0)//ordre important
        {
            add_titre_to_auteur(&listes_Auteur_arrTitre->tab_auteur[(*nb_auteur)],liste[i+j]);
            i++;// truc de simon ?
        }
        j+=i;//mais ici

        (*nb_auteur)++;
    }
    return listes_Auteur_arrTitre;
}

/**
 * @brief generer tab_Article_struct*
 * 
 * @param [in] liste 
 * @param [in] sizeArticleHauteur nombre de structure Paire_Article_auteur
 * @param [in] nombretotalarticle nombre d'article total
 * @return tab_Article_struct* 
 */
tab_Article_struct* gen_List_Article(Paire_Article_auteur * liste,int sizeArticleHauteur,int nombretotalarticle){
    INFO("genration Liste Article")

    tab_Article_struct * ListDesArticle = malloc(sizeof(tab_Article_struct));
    exitIfNull(ListDesArticle,"Erreur création liste de tab_Article_struct\n")
    int * nbarticle =  &ListDesArticle->nombre_Article;

    //combien d'article je doit faire ?
    ListDesArticle->tab_Article = NULL;
    DEBUG("Génération tableaux de %lu octer",nombretotalarticle*sizeof(Article_struct))
    ListDesArticle->tab_Article = malloc(nombretotalarticle*sizeof(Article_struct));
    exitIfNull(ListDesArticle->tab_Article,"genarticlelist: Imposible d'allouer tout les tableaux ")
    (*nbarticle) = 0;

    int j = 0;
    INFO("on parcoure liste")
    while (j < sizeArticleHauteur)
    {   
        #ifdef WARN_ON
        progressbar(j,sizeArticleHauteur);
                #endif
        //on add le premier nom_Article
        ListDesArticle->tab_Article[(*nbarticle)].nombre_auteur=0;
        ListDesArticle->tab_Article[(*nbarticle)].nom_Article=liste[j].article;
        ListDesArticle->tab_Article[(*nbarticle)].tab_ptr_auteur = NULL;
        // for (int i = 0; i < *nbarticle+1; i++)
        // {
        //     printf("%d %p:\n",i,&ListDesArticle->tab_Article[i]);
        // }
        

        int i = 0;
        //tant le prochain est le meme auteur et que on attein pas la fin de la liste
        while (i+j < sizeArticleHauteur && strcmp(liste[j].article,liste[j+i].article) == 0)//ordre important
        {
            Article_struct * dernierarticle = &ListDesArticle->tab_Article[(*nbarticle)];
            int * last_auteur  = &dernierarticle->nombre_auteur;

            //DEBUG
            // printf("dernierarticle:%p %p\n",dernierarticle,&ListDesArticle->tab_Article[(*nbarticle)]);

            //création d'auteur struct
            auteur_struct * temparray = reallocarray(dernierarticle->tab_ptr_auteur,(*last_auteur)+1,8); //8 taille d'un pointeur 
            exitIfNull(temparray,"gen_List_Article auteur_struct realockarrayfail\n");            
            dernierarticle->tab_ptr_auteur = (auteur_struct**)temparray;
            dernierarticle->tab_ptr_auteur[*last_auteur] = liste[i+j].pointeur_Auteur;// < nbelementmagi ?
            //DEBUG
            YOLO("hauteur:\t%s\n",dernierarticle->tab_ptr_auteur[*last_auteur]->nom_auteur);

            int found=0;
                                                                                //pASInitialiser ?
            int *localnbelementmaj = &dernierarticle->tab_ptr_auteur[*last_auteur]->nbelementmagi ;

            //on vérifie pas de douvbon avand d'ajouter
            for (int o = 0; o < *localnbelementmaj; o++)
            {
                if (dernierarticle->tab_ptr_auteur[*last_auteur]->tab_ptr_Article[o] == dernierarticle){
                    found = 1;
                    break;
                }
            }

            if (found == 0)
            {
                //20% du temps d'execution
                //array plus grand
                //la taille est égale a .size au lieux des element ?
                Article_struct ** tmptest  = reallocarray(
                    dernierarticle->tab_ptr_auteur[*last_auteur]->tab_ptr_Article,
                    (*localnbelementmaj)+1, ///< sur a 0 ?  
                    sizeof(Article_struct**));
                exitIfNull(tmptest,"imposible alouer dernierarticle->tab_ptr_auteur[*last_auteur]->tab_ptr_Article[i]\n");
                dernierarticle->tab_ptr_auteur[*last_auteur]->tab_ptr_Article = tmptest;

                //on boucle indicemagique
                dernierarticle->tab_ptr_auteur[*last_auteur]->tab_ptr_Article[*localnbelementmaj] = dernierarticle;
                // for (int y = 0; y < *localnbelementmaj+1; y++)
                // {
                //     printf("article:\t\t%p\n",dernierarticle->tab_ptr_auteur[*last_auteur]->tab_ptr_Article[y]);
                // }
                

                (*localnbelementmaj)++;
            }
            //fichierxml 2 article avec alice bob && alice bob && alice 
            (*last_auteur)++;
            i++;// truc de simon ?
        }

        j+=i;//mais ici

        (*nbarticle)++;
    }
    return ListDesArticle;
}

void printList_Auteur(tab_auteur_struct * OwO){
    for (int i = 0; i < OwO->taille; i++)
    {
        printf("%s:\n",OwO->tab_auteur[i].nom_auteur);    
        for (int j = 0; j < OwO->tab_auteur[i].size; j++)
        {
            printf("    %s\n",OwO->tab_auteur[i].tab_ptr_fiche_min[j]->titre);
        }
        printf("\n");
    }
    
}


void printList_Article(tab_Article_struct * OwO){
    for (int i = 0; i < OwO->nombre_Article; i++)
    {
        printf("%s:\n",OwO->tab_Article[i].nom_Article);    
        for (int j = 0; j < OwO->tab_Article[i].nombre_auteur; j++)
        {
            printf("\t%s\n",OwO->tab_Article[i].tab_ptr_auteur[j]->nom_auteur);
        }
        printf("\n");
    }
    
}

void printPaire_HauteurHeurvre(Paire_auteur_oeuvre * OwI,int sizeHauteurHeuvre ){
    for (int i = 0; i < sizeHauteurHeuvre ; i++)
    {
        printf("%s => %s\n",OwI[i].nom_auteur,OwI[i].oeuvre->titre);
    }
}


int count_isolate_autor(const tab_auteur_struct * List_des_Auteur){
    int compteur = 0;
    for (int i = 0; i < List_des_Auteur->taille; i++)
    {
        if(List_des_Auteur->tab_auteur[i].size > 0){
            compteur++;
        }
    }
    return compteur;
}

/**
 * @brief 
 * 
 * 
 * 
 * @param List_des_Auteur 
 * @param output 
 */
void unwrap_Serilise_Index(const tab_auteur_struct * List_des_Auteur, FILE * output){
    INFO("génération unwrap_Serilise_Index")
    DEBUG("unwrap:unwrap_Serilise_Index")
    //fonction d'qui fait la moyenne des nom_auteur pour pouvoir fair un maloque que une foit en moyenne
    fprintf(output,"%d\n",count_isolate_autor(List_des_Auteur));// est egale a List_des_Auteur->taille
    for (int i = 0; i < List_des_Auteur->taille; i++)
    {
        #ifdef WARN_ON
        progressbar(i+1,List_des_Auteur->taille);
        #endif
        if(List_des_Auteur->tab_auteur[i].size > 0){
            // List_des_Auteur->tab_auteur[i].
            // fprintf(output,"%d\n",List_des_Auteur->tab_auteur[i].DECALAGE);
            fprintf(output,"%s\n",List_des_Auteur->tab_auteur[i].nom_auteur);//char 1o addresse 8o
            fprintf(output,"%d\n",List_des_Auteur->tab_auteur[i].size);
            for (int j = 0; j < List_des_Auteur->tab_auteur[i].size; j++)
            {
                //ma fiche minimal est contenue dans auteur et dans tableaux fiche 
                fprintf(output,"%d\n",List_des_Auteur->tab_auteur[i].tab_ptr_fiche_min[j]->ADDR);
            }
        }

    }
}

//DOUBLON DE PARSING FAIR UN FICHIER UTILS OU ON LE MET
void enlever_retour_a_la_ligne(char * ligne);

//rename pour indiquer qu'on fait des auteur 
tab_auteur_struct * unwrap_Deserilise_Index(const tableaux_fiche * tableaux_fiche,FILE * input){
    INFO("deserialise tab auteur")
    char ligne[BALISESIZE];
    tab_auteur_struct * master_List_Auteur = malloc(sizeof(tab_auteur_struct));
    master_List_Auteur->taille=0;
    fgets(ligne,BALISESIZE,input);
        exitIfNull(sscanf(ligne,"%i\n",&master_List_Auteur->taille),"nombre de structure manquand ...")

    //optimiser car on alloue tout en un malloc ! par contre ça peut echouer a voir
    auteur_struct * Sommet_Auteur_Tableaux =  malloc(sizeof(auteur_struct)*master_List_Auteur->taille);  //<= je fait une liste de quoi ? 
    exitIfNull(Sommet_Auteur_Tableaux, "creation des sommet auteur tableaxD malloc null")
    master_List_Auteur->tab_auteur = Sommet_Auteur_Tableaux;

    // i compteur nombre auteur 
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
        master_List_Auteur->tab_auteur[i].nom_auteur = strdup(ligne);

        // on initialise le compteur d'élément 
        master_List_Auteur->tab_auteur[i].nbelementmagi = 0;
        master_List_Auteur->tab_auteur[i].tab_ptr_Article = NULL;

        fgets(ligne,BALISESIZE,input);
        exitIfNull(sscanf(ligne,"%i\n", &master_List_Auteur->tab_auteur[i].size),"auteur qui n'om pas d'article\n");
        
        #ifdef WARN_ON
        progressbar(i,master_List_Auteur->taille);
        #endif

        master_List_Auteur->tab_auteur[i].tab_ptr_fiche_min = malloc(master_List_Auteur->tab_auteur[i].size*sizeof(auteur_struct)); //<= bon type ?
        exitIfNull(master_List_Auteur->tab_auteur[i].tab_ptr_fiche_min,"allocation master_List_Auteur->tab_auteur[i].tab_ptr_fiche_min echouser...");

        for (int u = 0; u < master_List_Auteur->tab_auteur[i].size; u++)
        {
            fgets(ligne,BALISESIZE,input);
            enlever_retour_a_la_ligne(ligne);
            int indiceFiche = atoi(ligne);
            exitIfNull(tableaux_fiche->fiche[indiceFiche],"serialise index pointeur sur nom_auteur introuvable\n")
            master_List_Auteur->tab_auteur[i].tab_ptr_fiche_min[u] = tableaux_fiche->fiche[indiceFiche]; //On n'es pas obliger de lire la fiche
        }
        i++;
    }
    return master_List_Auteur;
}

//PABIEN
#define MAXarraySIZE 21143793
Paire_auteur_oeuvre HauteurHeuvre[MAXarraySIZE];

tab_auteur_struct * unwrap_ListAuteur_from_xml(FILE * dbinput,int * nbauteur){
    INFO("Generation Tab auteur:")
    tableaux_fiche mesfiche =  parse(dbinput);// ici au parisng
    *nbauteur = mesfiche.taille;
    //faire une fonciton pour sacoir la taille total verifier le temps
    int sizeHauteurHeuvre = SwapStruct(mesfiche,HauteurHeuvre);
    DEBUG("DEBUGGG ARRAY %d, %d",MAXarraySIZE,sizeHauteurHeuvre);
    // exit(0);
    // Paire_auteur_oeuvre HauteurHeuvre = malloc(sizeHauteurHeuvre*sizeof(Paire_auteur_oeuvre));
    // exitIfNull(HauteurHeuvre,"erreur allocation HauteurHeuvre");
    sort_tableaux_fiche(HauteurHeuvre,sizeHauteurHeuvre);
    tab_auteur_struct * malistedauteur = gen_List_Auteur(HauteurHeuvre,sizeHauteurHeuvre);
    return malistedauteur;
}


tab_auteur_struct * unwrap_from_tabfich(tableaux_fiche * mesfiches){
    int sizeHauteurHeuvre = SwapStruct(*mesfiches,HauteurHeuvre);
        DEBUG("DEBUGGG ARRAY %d, %d",MAXarraySIZE,sizeHauteurHeuvre);    

    sort_tableaux_fiche(HauteurHeuvre,sizeHauteurHeuvre);
    tab_auteur_struct * malistedauteur = gen_List_Auteur(HauteurHeuvre,sizeHauteurHeuvre);
    return malistedauteur;
}

tab_auteur_struct * unwrap_from_file(FILE * inputFile){
    INFO("generation tableaux auteur FROMFILE")
    tableaux_fiche * mesfiches = deserialisation(inputFile);
    int sizeHauteurHeuvre = SwapStruct(*mesfiches,HauteurHeuvre);
        DEBUG("DEBUGGG ARRAY %d, %d",MAXarraySIZE,sizeHauteurHeuvre);    

    sort_tableaux_fiche(HauteurHeuvre,sizeHauteurHeuvre);
    tab_auteur_struct * malistedauteur = gen_List_Auteur(HauteurHeuvre,sizeHauteurHeuvre);
    return malistedauteur;
}

tab_Article_struct * gen_ListaArticle(const tab_auteur_struct * Malistauteur, int nbArticle){
    //compte le nombre de structure pour le maloc
    INFO("Generation Tab Article:")
    DEBUG("unwrap:gen_ListaArticle")
    int nbstructure = 0;
    for (int i = 0; i < Malistauteur->taille; i++)
    {
        nbstructure+=Malistauteur->tab_auteur[i].size;/// lerreur etait la
    }
    DEBUG("il y a %d structure a générée",nbstructure)
    DEBUG("Calloc de %lu octer",nbstructure*sizeof(Article_struct))
    Paire_Article_auteur * Paire_auteur_oeuvre = calloc(nbstructure,sizeof(Article_struct));
    exitIfNull(Paire_auteur_oeuvre,"imposible de crée Paire_auteur_oeuvre");
    int sizeHauteurHeuvre = SwapPaire_HauteurHeurvreToPaire_HauteurHeurvre(Malistauteur,Paire_auteur_oeuvre);
    DEBUG("QSORT ( si echoue visualcode prend beaucoup de mémoir)")
    sort_tableaux_Article(Paire_auteur_oeuvre,sizeHauteurHeuvre);
    tab_Article_struct * malistedauteur = gen_List_Article(Paire_auteur_oeuvre,sizeHauteurHeuvre,nbArticle);
    return malistedauteur;
}



void serialisation_tab_Article_struct(tab_Article_struct * inputlist, FILE * outputfile){
    INFO("Sérialisation des Article: Start")
    DEBUG("unwrap:serialisation_tab_Article_struct")
    int nombreArticle = inputlist->nombre_Article;
    fprintf(outputfile,"%d\n",inputlist->nombre_Article);
    DEBUG("j'ai %d article",nombreArticle)

    for (int i = 0; i < nombreArticle; i++)
    {
        #ifdef WARN_ON
        progressbar(i,nombreArticle);
        #endif

        Article_struct article = inputlist->tab_Article[i];
        //le noms de l'article sera obtenue a la désérialisation....
        fprintf(outputfile,"%s\n",article.nom_Article); ///pas glope
        int nombreauteur = article.nombre_auteur;
        // DEBUG("%s %d",article.nom_Article,nombreauteur);
        fprintf(outputfile,"%d\n",nombreauteur);
        for (int u = 0; u < nombreauteur; u++)
        {
            int indiceAuteur = article.tab_ptr_auteur[u]->nbelementmagi;
            // DEBUG("%d",indiceAuteur)
            fprintf(outputfile,"%d\n",indiceAuteur);
        } 
    }
    INFO("Sérialisation des Article: Terminer")
}

/**
 * @brief Ajouter un article a l'auteur
 * ## a faire
 *  si trier par ordre alpahbétique allor les doublon doive ce suivre DONC tester la dernierre valeur ?
 * \nfontion utiliser beaucoup ?
 * @param monauteur 
 * @param monArticle 
 */
void ajout_Article_in_auteur(auteur_struct * monauteur,Article_struct * monArticle){
    // Check doublon
    // for (int i = 0; i < monauteur->nbelementmagi; i++)
    // {
    //     if(monauteur->tab_ptr_Article[i] == monArticle){
    //         return;
    //     }
    // }
    Article_struct ** tmptest = reallocarray(monauteur->tab_ptr_Article,monauteur->nbelementmagi+1,sizeof(Article_struct*));
    exitIfNull(tmptest,"ajout article erreur realockarray")
    tmptest[monauteur->nbelementmagi] = monArticle;
    monauteur->tab_ptr_Article = tmptest;
    monauteur->nbelementmagi++;
    DEBUG("\t\t tableauxd d'article %p nb element %d ",monauteur->tab_ptr_Article,monauteur->nbelementmagi)
    // DEBUG("%d",monauteur->nbelementmagi)
}

//faire une interface pour sérialiser deserialiser ?
tab_Article_struct * deserialisation_tab_Article_struct(tab_auteur_struct * mesauteur, FILE * inputfile){
    INFO("deserailisation Article")
    char ligne[BALISESIZE];
    tab_Article_struct * mon_tab_Article_struct = malloc(sizeof(tab_Article_struct));
    mon_tab_Article_struct->nombre_Article=0;
    int * nombretotalarticle = & mon_tab_Article_struct->nombre_Article; 
    fgets(ligne,BALISESIZE,inputfile);
    sscanf(ligne,"%d",nombretotalarticle);
    exitIfNull(*nombretotalarticle,"nombre de structure manquand ...")
    DEBUG("il y a %d Article",*nombretotalarticle)
    DEBUG("Malloc de %luocter",sizeof(Article_struct)**nombretotalarticle)

    //optimiser car on alloue tout en un malloc ! par contre ça peut echouer a voir
    Article_struct * listedesArticle =  malloc(sizeof(Article_struct)**nombretotalarticle);
    exitIfNull(listedesArticle, "creation des sommet auteur tableaxD malloc null")
    mon_tab_Article_struct->tab_Article = listedesArticle;

    for (int j = 0; j < *nombretotalarticle; j++)
    {
        Article_struct * monArticle = &mon_tab_Article_struct->tab_Article[j];
        #ifdef WARN_ON
        progressbar(j,*nombretotalarticle);
        #endif
        
        //pas si utile .... Peut faire autrement
        fgets(ligne,BALISESIZE,inputfile);
        // DEBUG("%s",ligne)
        monArticle->nom_Article = strdup(ligne);

        //nombre d'auteur sur cette structure
        fgets(ligne,BALISESIZE,inputfile);
        int nbauteur = 0;
        sscanf(ligne,"%d\n",&nbauteur);
        monArticle->nombre_auteur = nbauteur;
        YOLO("nombre dauteur %d",nbauteur);


        monArticle->tab_ptr_auteur = NULL;
        auteur_struct * structauteur = calloc(sizeof(auteur_struct),nbauteur);
        exitIfNull(structauteur,"deserialisation article maloc fail, %dauteur %luocter"
        ,nbauteur,sizeof(auteur_struct)*nbauteur)
        monArticle->tab_ptr_auteur = structauteur;
        //je parcoure tout mes auteur
        for (int i = 0; i < nbauteur; i++)
        {
            int indexmagie = 0;
            fgets(ligne,BALISESIZE,inputfile);
            sscanf(ligne,"%d\n",&indexmagie);
            //je cherche dans le tab auteur en fc de l'index trouver
            structauteur[i] = mesauteur->tab_auteur[indexmagie];

            //je doit  associer a mon auteur de quoi joindre mon article

            //pas obligatoir
            // structauteur[i].nbelementmagi = indexmagie;
            // DEBUG("size %d nombre element maj %d", structauteur[i].size,structauteur[i].nbelementmagi)
            // YOLO("hauteur: %s",structauteur[i].nom_auteur);
            DEBUG("Ajout de l'article a  %")
            ajout_Article_in_auteur(&structauteur[i],monArticle);
            DEBUG("!!! addresse %p, nombre d'article contenue %d, %s",structauteur[i].tab_ptr_Article,structauteur[i].nbelementmagi,structauteur[i].nom_auteur)
        }

        //le réalock fout la merde 

        INFO("Noms article %s",monArticle->nom_Article)
        INFO("Nombre d'article %d",monArticle->nombre_auteur)
        for (int i = 0; i < monArticle->nombre_auteur; i++)
        {
            DEBUG("\tAddresse alouer: %p",monArticle->tab_ptr_auteur[i])
            DEBUG("\tNoms auteur %s",monArticle->tab_ptr_auteur[i]->nom_auteur)
            WARNING("-----")
        }
        
        
    }

    //tester ici? 




    return mon_tab_Article_struct;
}

/**
 * @brief article depuit le xml de base
 * 
 * @param dbinput 
 * @return tab_Article_struct* 
 */
tab_Article_struct * unwrap_ListArticle_from_xml(FILE * dbinput){
    DEBUG("unwrap_ListArticle_from_xml:")
    int nbauteur = -1;
    int * pointeurnbauteur = &nbauteur ;
    tab_auteur_struct * malistauteur = unwrap_ListAuteur_from_xml(dbinput,pointeurnbauteur);//la
    tab_Article_struct * malistaarticle = gen_ListaArticle(malistauteur,*pointeurnbauteur);
    INFO("tab_Article_struct générée")
    return malistaarticle ;
}

/**
 * @brief genere tout
 * 
 * @param dblpxml 
 * @param inverted 
 * @return unwrap_Graph_struct 
 */
unwrap_Graph_struct gen_unwrap_Graph(FILE * dblpxml, FILE * inverted){
    //check si les cache sont la 
    tableaux_fiche * matablefiche = deserialisation(dblpxml);
    tab_auteur_struct * malistaauteur =   unwrap_Deserilise_Index(matablefiche,inverted);
    tab_Article_struct * malistearticle = gen_ListaArticle(malistaauteur,matablefiche->taille);
    unwrap_Graph_struct graph  = {malistaauteur, malistearticle,matablefiche};
    return graph;
}

void unwrap_List_Auteur_free(tab_auteur_struct * afree){
    for (int i = 0; i < afree->taille; i++)
    {
        free(afree->tab_auteur[i].nom_auteur);   
    }
    free(afree->tab_auteur);
}