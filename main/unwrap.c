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

tab_auteur_struct* gen_List_Auteur(const Paire_auteur_oeuvre * liste,int sizeHauteurHeuvre){
    tab_auteur_struct * listes_Auteur_arrTitre = malloc(sizeof(tab_auteur_struct));
    exitIfNull(listes_Auteur_arrTitre,"Erreur création liste de tab_auteur_struct\n")
    int * nb_auteur = &listes_Auteur_arrTitre->taille; 

    (*nb_auteur)=0;

    int indiceSommet = 0;
    listes_Auteur_arrTitre->tab_auteur = NULL;

    int j = 0;
    //on parcoure liste
    while (j < sizeHauteurHeuvre)
    {
        auteur_struct * tb_Somet_h = reallocarray(listes_Auteur_arrTitre->tab_auteur,(*nb_auteur)+1,sizeof(auteur_struct));//fasink alocate error
        exitIfNull(tb_Somet_h,"Erreur création de auteur_struct\n")
        listes_Auteur_arrTitre->tab_auteur = tb_Somet_h;
            
        //initialisation de l'auteur crée
        listes_Auteur_arrTitre->tab_auteur[(*nb_auteur)].size=0;
        listes_Auteur_arrTitre->tab_auteur[(*nb_auteur)].nbelementmagi = 0;
        listes_Auteur_arrTitre->tab_auteur[(*nb_auteur)].nom_auteur = NULL;
        listes_Auteur_arrTitre->tab_auteur[(*nb_auteur)].tab_ptr_Article = NULL;
        listes_Auteur_arrTitre->tab_auteur[(*nb_auteur)].tab_ptr_fiche_min = NULL;
        listes_Auteur_arrTitre->tab_auteur[(*nb_auteur)].nom_auteur=liste[j].nom_auteur;

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
    //INFO genration ...

    tab_Article_struct * ListDesArticle = malloc(sizeof(tab_Article_struct));
    exitIfNull(ListDesArticle,"Erreur création liste de tab_Article_struct\n")
    int * nbarticle =  &ListDesArticle->nombre_Article;

    //combien d'article je doit faire ?
    ListDesArticle->tab_Article = NULL;
    ListDesArticle->tab_Article = malloc(nombretotalarticle*sizeof(Article_struct));
    exitIfNull(ListDesArticle->tab_Article,"genarticlelist: Imposible d'allouer tout les tableaux ")
    (*nbarticle) = 0;

    int j = 0;
    //on parcoure liste
    while (j < sizeArticleHauteur)
    {   

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
            // printf("hauteur:\t%s\n",dernierarticle->tab_ptr_auteur[*last_auteur]->nom_auteur);

            int found=0;

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
                //array plus grand
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

        // Article_struct Sometgenere = ListDesArticle->tab_Article[ListDesArticle->nombre_Article];
        // fprintf(stderr,"%s\n",Sometgenere.nom_Article);
        // fprintf(stderr,"\tnombre d'auteur %d\n",Sometgenere.nombre_auteur); ///BIZARD BUG ?
        // for (int ii = 0; ii < Sometgenere.nombre_auteur; ii++)
        // {
        //     fprintf(stderr,"\t%s\n",Sometgenere.tab_ptr_auteur[ii]->nom_auteur);
        //     fprintf(stderr,"\t\tnombre d'nom_Article %d\n",Sometgenere.tab_ptr_auteur[ii]->nbelementmagi); ///BIZARD BUG ?
        //     for (int Uu = 0; Uu < Sometgenere.tab_ptr_auteur[ii]->nbelementmagi; Uu++)
        //     {
        //         fprintf(stderr,"\t\t%s\n",Sometgenere.tab_ptr_auteur[ii]->tab_ptr_Article[Uu]->nom_Article);
        //     }
         
        // }
        (*nbarticle)++;
    }
    // for (int i = 0; i < ListDesArticle->nombre_Article; i++)
    // {
    //     fprintf(stderr,"%s\n",ListDesArticle->tab_Article[i].tab_ptr_auteur[0]->tab_ptr_Article[0]->nom_Article);
    // }
    
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

void unwrap_Serilise_Index(const tab_auteur_struct * List_des_Auteur, FILE * output){
    //fonction d'qui fait la moyenne des nom_auteur pour pouvoir fair un maloque que une foit en moyenne
    fprintf(output,"%d\n",count_isolate_autor(List_des_Auteur));
    for (int i = 0; i < List_des_Auteur->taille; i++)
    {
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

tab_auteur_struct * unwrap_Deserilise_Index(const tableaux_fiche * tableaux_fiche,FILE * input){
    char ligne[BALISESIZE];
    tab_auteur_struct * master_List_Auteur = malloc(sizeof(tab_auteur_struct));
    master_List_Auteur->taille=0;
    fgets(ligne,BALISESIZE,input);
        exitIfNull(sscanf(ligne,"%i\n",&master_List_Auteur->taille),"nombre de structure manquand ...")

    //optimiser car on alloue tout en un malloc ! par contre ça peut echouer a voir
    auteur_struct * Sommet_Auteur_Tableaux =  malloc(sizeof(auteur_struct)*master_List_Auteur->taille);  //<= je fait une liste de quoi ?
    exitIfNull(Sommet_Auteur_Tableaux, "creation des sommet auteur tableaxD malloc null")
    master_List_Auteur->tab_auteur = Sommet_Auteur_Tableaux; //<=associasioin bonne ?

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
        
        master_List_Auteur->tab_auteur[i].tab_ptr_fiche_min = malloc(master_List_Auteur->tab_auteur[i].size*sizeof(auteur_struct)); //<= bon type ?
        exitIfNull(master_List_Auteur->tab_auteur[i].tab_ptr_fiche_min,"allocation master_List_Auteur->tab_auteur[i].tab_ptr_fiche_min echouser...");

        for (int u = 0; u < master_List_Auteur->tab_auteur[i].size; u++)
        {
            fgets(ligne,BALISESIZE,input);
            enlever_retour_a_la_ligne(ligne);
            
            int a = 0;
            //on fait des sscanf de fgets ... on peut le faire directement 37% de perte perf a cause du sscanf !
            sscanf(ligne,"%d",&a);
            exitIfNull(tableaux_fiche->fiche[a],"serialise index pointeur sur nom_auteur introuvable\n")
            master_List_Auteur->tab_auteur[i].tab_ptr_fiche_min[u] = tableaux_fiche->fiche[a];
        }
        i++;
    }
    return master_List_Auteur;
}

//PABIEN
#define MAXarraySIZE 21143793
Paire_auteur_oeuvre HauteurHeuvre[MAXarraySIZE];

tab_auteur_struct * unwrap_ListAuteur_from_xml(FILE * dbinput,int * nbauteur){
    tableaux_fiche mesfiche =  parse(dbinput);
    *nbauteur = mesfiche.taille;
    int sizeHauteurHeuvre = SwapStruct(mesfiche,HauteurHeuvre);
    sort_tableaux_fiche(HauteurHeuvre,sizeHauteurHeuvre);
    tab_auteur_struct * malistedauteur = gen_List_Auteur(HauteurHeuvre,sizeHauteurHeuvre);
    return malistedauteur;
}


tab_auteur_struct * unwrap_from_tabfich(tableaux_fiche * mesfiches){
    int sizeHauteurHeuvre = SwapStruct(*mesfiches,HauteurHeuvre);
    sort_tableaux_fiche(HauteurHeuvre,sizeHauteurHeuvre);
    tab_auteur_struct * malistedauteur = gen_List_Auteur(HauteurHeuvre,sizeHauteurHeuvre);
    return malistedauteur;
}

tab_auteur_struct * unwrap_from_file(FILE * inputFile){

    tableaux_fiche * mesfiches = deserialisation(inputFile);
    int sizeHauteurHeuvre = SwapStruct(*mesfiches,HauteurHeuvre);
    sort_tableaux_fiche(HauteurHeuvre,sizeHauteurHeuvre);
    tab_auteur_struct * malistedauteur = gen_List_Auteur(HauteurHeuvre,sizeHauteurHeuvre);
    return malistedauteur;
}

tab_Article_struct * gen_ListaArticle(const tab_auteur_struct * Malistauteur, int nbArticle){
    //compte le nombre de structure pour le maloc
    int nbstructure = 0;
    for (int i = 0; i < Malistauteur->taille; i++)
    {
        nbstructure+=Malistauteur->tab_auteur[i].size;/// lerreur etait la
    }
    Paire_Article_auteur * Paire_auteur_oeuvre = calloc(nbstructure,sizeof(Article_struct));
    exitIfNull(Paire_auteur_oeuvre,"imposible de crée Paire_auteur_oeuvre");
    int sizeHauteurHeuvre = SwapPaire_HauteurHeurvreToPaire_HauteurHeurvre(Malistauteur,Paire_auteur_oeuvre);
    sort_tableaux_Article(Paire_auteur_oeuvre,sizeHauteurHeuvre);
    tab_Article_struct * malistedauteur = gen_List_Article(Paire_auteur_oeuvre,sizeHauteurHeuvre,nbArticle);
    return malistedauteur;
}

/**
 * @brief article depuit le xml de base
 * 
 * @param dbinput 
 * @return tab_Article_struct* 
 */
tab_Article_struct * unwrap_ListArticle_from_xml(FILE * dbinput){
    int nbauteur = -1;
    int * pointeurnbauteur = &nbauteur ;
        printf("Generation Tab auteur:\n");
    tab_auteur_struct * malistauteur = unwrap_ListAuteur_from_xml(dbinput,pointeurnbauteur);
        printf("Generation Tab Article:\n");
    tab_Article_struct * malistaarticle = gen_ListaArticle(malistauteur,*pointeurnbauteur);
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