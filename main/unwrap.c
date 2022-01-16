#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parsing.h"
#include "unwrap.h"
#include "macro.h"


/**
 * @brief Compare le titre de 2 article
 * 
 *  générée par ....
 *  *utiliser par qsort*
 * 
 * @param [in] a object A
 * @param [in] b object B
 * @return int décalage pour qsort
 */
int qsort_compare_Article(const void * a, const void * b){
    return strcmp(((Paire_Article_auteur*)a)->article,((Paire_Article_auteur*)b)->article);
}

/**
 * @brief fonction de comparaison des article pour qsort
 * 
 * 
 * @param [in] a object A
 * @param [in] b object B
 * @return int décalage pour qsort 
 */
int 
qsort_compare_auteur(const void * a, const void * b){
    return strcmp(((Paire_auteur_oeuvre*)a)->nom_auteur,((Paire_auteur_oeuvre*)b)->nom_auteur);
}

/**
 * @brief génère un tableaux d' auteurToHeurvre 
 * 
 * déplie tableaux_fiche pour généré unt tableaux
 * d'élément Paire_auteur_oeuvre
 * qui est une association auteur <=> oeuvre unique
 * 
 * @param [in]  input toute les fiche des oeuvre qui comporte les liste auteur  
 * @param [out] arrayout liste qui associe un auteur a une oeuvre
 * @return nombre d'élément du tableaux
 */
int deplier_fiche(tableaux_fiche input, Paire_auteur_oeuvre * arrayout ){
    INFO("deplier les fiche")
    int indice = 0;
    for (int i = 0; i < input.taille; i++){
        PROGRESSBAR(i,input.taille);
        for (int u = 0; u < input.fiche[i]->nombre_auteur; u++)
        {   
            arrayout[indice].oeuvre = input.fiche[i];
            arrayout[indice].nom_auteur = input.fiche[i]->liste_auteur[u];
            indice++;
        }
    }
    return indice;
}

int deplier_auteur(const tab_auteur_struct * input, Paire_Article_auteur * Article_auteur_Array ){
    DEBUG("deplier_auteur:")
    int indice = 0;
    for (int i = 0; i < input->taille; i++){
        PROGRESSBAR(i,input->taille);
        for (int u = 0; u < input->tab_auteur[i].size; u++)
        {   
            Article_auteur_Array[indice].article = input->tab_auteur[i].tab_ptr_fiche_min[u]->titre;
            Article_auteur_Array[indice].pointeur_Auteur = &input->tab_auteur[i];
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
void sort_tableaux_auteur(Paire_auteur_oeuvre * HauteurHeuvre,int sizeHauteurHeuvre ){
    qsort(HauteurHeuvre,sizeHauteurHeuvre ,sizeof(Paire_auteur_oeuvre),qsort_compare_Article);
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
    DEBUG("QSORT (si echoue visualcode gourmant mémoir)")
    qsort(ArticleuHauteur,sizeArticleHauteur ,sizeof(Paire_Article_auteur),qsort_compare_auteur);
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

void test_exploration_Article(const tab_Article_struct * mesarticle){
    for (int i = 0; i < mesarticle->nombre_Article ; i++)
    {
        printf("%s ==> %d\n",mesarticle->tab_Article[i].nom_Article, mesarticle->tab_Article[i].nombre_auteur);
        for (int u = 0; u < mesarticle->tab_Article[i].nombre_auteur; u++)
        {
            printf("\t%s ==> %d\n",mesarticle->tab_Article[i].tab_ptr_auteur[u]->nom_auteur,mesarticle->tab_Article[i].tab_ptr_auteur[u]->nbelementmagi);
            for (int pp = 0; pp < mesarticle->tab_Article[i].tab_ptr_auteur[u]->nbelementmagi; pp++)
            {
                if (mesarticle->tab_Article[i].tab_ptr_auteur[u]->tab_ptr_Article[pp]->nombre_auteur > 0 && mesarticle->tab_Article[i].tab_ptr_auteur[u]->tab_ptr_Article[pp]->tab_ptr_auteur[0])
                {
                    printf("\t\t%s ==> %d\n",mesarticle->tab_Article[i].tab_ptr_auteur[u]->tab_ptr_Article[pp]->nom_Article,mesarticle->tab_Article[i].tab_ptr_auteur[u]->tab_ptr_Article[pp]->nombre_auteur); 
                    for (int UI = 0; UI < mesarticle->tab_Article[i].tab_ptr_auteur[u]->tab_ptr_Article[pp]->nombre_auteur; UI++)
                    {
                        printf("\t\t\t%s\n",mesarticle->tab_Article[i].tab_ptr_auteur[u]->tab_ptr_Article[pp]->tab_ptr_auteur[UI]->nom_auteur); 
                    }
                                    
                }else{
                    printf("NOPE\n");
                }
            }           
        }
    }
}


/**
 * @brief génère tab_auteur_struct
 * 
 *  va parser une liste de Paire_auteur_oeuvre trier par auteur
 *  ajoute tout les article pour le meme auteur a une fiche auteur_struct
 *  ajoute les fiche a tab_auteur_struct
 * 
 * @param [in] liste 
 * @param [in] sizeHauteurHeuvre 
 * @return tab_auteur_struct* 
 */
tab_auteur_struct* gen_List_auteur(const Paire_auteur_oeuvre * liste,int sizeHauteurHeuvre){
    INFO("gen_List_auteur:")
    tab_auteur_struct * listes_Auteur_arrTitre = malloc(sizeof(tab_auteur_struct));
    exitIfNull(listes_Auteur_arrTitre,"Erreur création liste de tab_auteur_struct\n")
    int * nb_auteur = &listes_Auteur_arrTitre->taille; 

    listes_Auteur_arrTitre->taille = 0;
    listes_Auteur_arrTitre->tab_auteur = NULL;

    int posTabPaireaA = 0;
    //on parcoure liste
    while (posTabPaireaA < sizeHauteurHeuvre)
    {
        PROGRESSBAR(posTabPaireaA,sizeHauteurHeuvre);

        auteur_struct * tb_Somet_h = reallocarray(listes_Auteur_arrTitre->tab_auteur,(*nb_auteur)+1,sizeof(auteur_struct));//fasink alocate error
        exitIfNull(tb_Somet_h,"Erreur création de auteur_struct\n")
        listes_Auteur_arrTitre->tab_auteur = tb_Somet_h;
            
        //initialisation de l'auteur crée
        listes_Auteur_arrTitre->tab_auteur[(*nb_auteur)].size=0                         ;
        listes_Auteur_arrTitre->tab_auteur[(*nb_auteur)].nbelementmagi = 0              ;
        listes_Auteur_arrTitre->tab_auteur[(*nb_auteur)].nom_auteur = NULL              ;
        listes_Auteur_arrTitre->tab_auteur[(*nb_auteur)].tab_ptr_Article = NULL         ;    //ducoup malloc le code 
        listes_Auteur_arrTitre->tab_auteur[(*nb_auteur)].tab_ptr_fiche_min = NULL       ;
        listes_Auteur_arrTitre->tab_auteur[(*nb_auteur)].nom_auteur=liste[posTabPaireaA].nom_auteur ;

        int noArticle = 0;
        //tant le prochain auteur est et que l'on n'attein pas la fin de la liste
        while (posTabPaireaA+noArticle < sizeHauteurHeuvre &&
            strcmp(liste[posTabPaireaA].nom_auteur,liste[posTabPaireaA+noArticle].nom_auteur) == 0)//ordre important
        {
            add_titre_to_auteur(&listes_Auteur_arrTitre->tab_auteur[(*nb_auteur)],liste[posTabPaireaA+noArticle]);
            noArticle++;
        }
        //on passe les noArticle auteur au posTabPaireaA article  dans le tableaux Paire_auteur_oeuvre
        posTabPaireaA+=noArticle;
        //on incrémente pour passer au prochain auteur 
        (*nb_auteur)++;
    }
    DEBUG("Pareil ?? NOMBRE sizeHauteurHeuvre %d, listes_Auteur_arrTitre->taille %d", sizeHauteurHeuvre, listes_Auteur_arrTitre->taille)
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
tab_Article_struct* assemble_tab_Article(Paire_Article_auteur * liste,int sizeArticleHauteur,int nombretotalarticle){
    INFO("Génération Liste Article")

    tab_Article_struct * ListDesArticle = malloc(sizeof(tab_Article_struct));
    exitIfNull(ListDesArticle,"Erreur création liste de tab_Article_struct\n")
    int * nbarticle =  &ListDesArticle->nombre_Article;

    //combien d'article je doit faire ?
    ListDesArticle->tab_Article = NULL;
    DEBUG("Génération tableaux de %lu octer",nombretotalarticle*sizeof(Article_struct))
    ListDesArticle->tab_Article = malloc(nombretotalarticle*sizeof(Article_struct));
    exitIfNull(ListDesArticle->tab_Article,"genarticlelist: Imposible d'allouer tout les tableaux ")
    (*nbarticle) = 0;

    int posTabPairAa = 0;
    DEBUG("Parcour de la liste des article")
    while (posTabPairAa < sizeArticleHauteur)
    {   
        #ifdef WARN_ON
        PROGRESSBAR(posTabPairAa,sizeArticleHauteur);
        #endif

        //on add le premier nom_Article
        ListDesArticle->tab_Article[(*nbarticle)].nombre_auteur=0;
        ListDesArticle->tab_Article[(*nbarticle)].nom_Article=liste[posTabPairAa].article;
        ListDesArticle->tab_Article[(*nbarticle)].tab_ptr_auteur = NULL;


        Article_struct * dernierarticle = &ListDesArticle->tab_Article[(*nbarticle)];
        int * nb_auteur  = &dernierarticle->nombre_auteur;  //utiliser un compteur local pourgagner du temps ?

        //tant le prochain auteur et le meme et que on attein pas la fin de la liste
        while (posTabPairAa+(*nb_auteur) < sizeArticleHauteur && 
            strcmp(liste[posTabPairAa].article,liste[posTabPairAa+(*nb_auteur)].article) == 0)  //ordre important
        {
            YOLO("dernierarticle:%p %p\n",dernierarticle,&ListDesArticle->tab_Article[(*nbarticle)]);

            //création d'auteur struct
            auteur_struct * temparray = reallocarray(dernierarticle->tab_ptr_auteur,(*nb_auteur)+1,8); //8 taille d'un pointeur 
            exitIfNull(temparray,"assemble_tab_Article auteur_struct realockarrayfail\n");            
            dernierarticle->tab_ptr_auteur = (auteur_struct**)temparray;
            dernierarticle->tab_ptr_auteur[*nb_auteur] = liste[(*nb_auteur)+posTabPairAa].pointeur_Auteur;// < nbelementmagi ?

            YOLO("hauteur:\t%s\n",dernierarticle->tab_ptr_auteur[*nb_auteur]->nom_auteur);

            //flag pour passer au prochain article
            int found=0;
                                                                                //pASInitialiser ?
            int *localnbelementmaposTabPairAa = &dernierarticle->tab_ptr_auteur[*nb_auteur]->nbelementmagi ;

            //on vérifie qu'il n'existe pas déja un article 
            for (int o = 0; o < *localnbelementmaposTabPairAa; o++)
            {
                if (dernierarticle->tab_ptr_auteur[*nb_auteur]->tab_ptr_Article[o] == dernierarticle){
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
                    dernierarticle->tab_ptr_auteur[*nb_auteur]->tab_ptr_Article,
                    (*localnbelementmaposTabPairAa)+1, ///< sur a 0 ?  
                    sizeof(Article_struct**));
                exitIfNull(tmptest,"imposible alouer dernierarticle->tab_ptr_auteur[*nb_auteur]->tab_ptr_Article[(*nb_auteur)]\n");
                dernierarticle->tab_ptr_auteur[*nb_auteur]->tab_ptr_Article = tmptest;

                //on boucle indicemagique
                dernierarticle->tab_ptr_auteur[*nb_auteur]->tab_ptr_Article[*localnbelementmaposTabPairAa] = dernierarticle;
                (*localnbelementmaposTabPairAa)++;
            }
            //on incrémente le nombre d'auteur
            (*nb_auteur)++;
        }
        //on ce déplace dans Paire_Article_auteur
        posTabPairAa+=(*nb_auteur);
        //on passe au prochain article
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
 * @brief génère un binaire contenant tab_auteur_struct
 * 
 *  a besoin que l'auteur soit relier au fiche minimal
 *  pour pouvoir passer le no l'index pour retrouver
 * 
 * 
 *  -   nombre d'auteur
 *      -   noms de l'auteur
 *      -   nombre article
 *          -   Indice/addresse de la fiche
 *          
 * 
 * @param List_des_Auteur 
 * @param output 
 */
void serialise_tab_auteur_struct(const tab_auteur_struct * List_des_Auteur, FILE * output){
    INFO("sérialisation des auteur:")
    //fonction d'qui fait la moyenne des nom_auteur pour pouvoir fair un maloque que une foit en moyenne
    fprintf(output,"%d\n",count_isolate_autor(List_des_Auteur));// est egale a List_des_Auteur->taille
    for (int i = 0; i < List_des_Auteur->taille; i++)
    {
        #ifdef WARN_ON
        PROGRESSBAR(i+1,List_des_Auteur->taille);
        #endif
        if(List_des_Auteur->tab_auteur[i].size > 0){
            fprintf(output,"%s\n",List_des_Auteur->tab_auteur[i].nom_auteur);//char 1o addresse 8o //FPRINTF PASBIEN
            fprintf(output,"%d\n",List_des_Auteur->tab_auteur[i].size);
            for (int j = 0; j < List_des_Auteur->tab_auteur[i].size; j++)
            {
                //indice pour acceder a la fiche minimal a la désérialisation
                fprintf(output,"%d\n",List_des_Auteur->tab_auteur[i].tab_ptr_fiche_min[j]->ADDR);//on pourait y utiliser des addresse stoquer dans un fichier 
            }
        }

    }
}

//rename pour indiquer qu'on fait des auteur 

/**
 * @brief génération tab_auteur_struct a partire d'un binaire
 * 
 * 
 * @param [in] tableaux_fiche on en a besoin mais on pourait s'en passer 
 * @param [in] input fichier binaire 
 * @return tab_auteur_struct* 
 */
tab_auteur_struct * deserialise_tab_auteur_struct(const tableaux_fiche * tableaux_fiche,FILE * input){
    INFO("deserialise tab auteur")

    char ligne[BALISESIZE];
    tab_auteur_struct * master_List_Auteur = malloc(sizeof(tab_auteur_struct));
    master_List_Auteur->taille=0;

    fgets(ligne,BALISESIZE,input);
    master_List_Auteur->taille = atoi(ligne);
    exitIfNull(master_List_Auteur->taille,"nombre d'auteur ilisible")
    DEBUG("Il y a %d auteur unique",master_List_Auteur->taille)

    DEBUG("Malloc de %lu octer",sizeof(auteur_struct)*master_List_Auteur->taille)
    auteur_struct * Sommet_Auteur_Tableaux =  malloc(sizeof(auteur_struct)*master_List_Auteur->taille);
    exitIfNull(Sommet_Auteur_Tableaux, "deserialise_tab_auteur_struct: maloc echouer")
    master_List_Auteur->tab_auteur = Sommet_Auteur_Tableaux;

    int nbauteur = 0;
    while (fgets(ligne,BALISESIZE,input))
    {
        enlever_retour_a_la_ligne(ligne);
        master_List_Auteur->tab_auteur[nbauteur].nom_auteur = strdup(ligne);

        // on initialise le compteur d'élément 
        master_List_Auteur->tab_auteur[nbauteur].nbelementmagi = 0;
        master_List_Auteur->tab_auteur[nbauteur].tab_ptr_Article = NULL;

        fgets(ligne,BALISESIZE,input);
        master_List_Auteur->tab_auteur[nbauteur].size = atoi(ligne);
        exitIfNull(master_List_Auteur->tab_auteur[nbauteur].size,"nombre d'auteur incorect !")

        #ifdef WARN_ON
        PROGRESSBAR(nbauteur,master_List_Auteur->taille);
        #endif

        master_List_Auteur->tab_auteur[nbauteur].tab_ptr_fiche_min = malloc(master_List_Auteur->tab_auteur[nbauteur].size*sizeof(auteur_struct)); //<= bon type ?
        exitIfNull(master_List_Auteur->tab_auteur[nbauteur].tab_ptr_fiche_min,"allocation master_List_Auteur->tab_auteur[nbauteur].tab_ptr_fiche_min echouser...");

        for (int u = 0; u < master_List_Auteur->tab_auteur[nbauteur].size; u++)
        {
            fgets(ligne,BALISESIZE,input);
            enlever_retour_a_la_ligne(ligne);
            int indiceFiche = atoi(ligne);
            exitIfNull(tableaux_fiche->fiche[indiceFiche],"serialise index pointeur sur nom_auteur introuvable\n")
            master_List_Auteur->tab_auteur[nbauteur].tab_ptr_fiche_min[u] = tableaux_fiche->fiche[indiceFiche]; //On n'es pas obliger de lire la fiche
        }
        nbauteur++;
    }
    master_List_Auteur->nombre_article = tableaux_fiche->taille;
    return master_List_Auteur;
}

//PABIEN
#define MAXarraySIZE 21143793
Paire_auteur_oeuvre HauteurHeuvre[MAXarraySIZE];

tab_auteur_struct * gen_tab_auteur_from_xml(FILE * dbinput){
    INFO("Generation Tab auteur:")
    tableaux_fiche mesfiche =  parse(dbinput);// ici au parisng
    //faire une fonciton pour sacoir la taille total verifier le temps
    int sizeHauteurHeuvre = deplier_fiche(mesfiche,HauteurHeuvre);
    // DEBUG("Taille du tableaux MAXarraySIZE %d, %d",MAXarraySIZE,sizeHauteurHeuvre);
    INFO("Trie:")
    sort_tableaux_auteur(HauteurHeuvre,sizeHauteurHeuvre);
    tab_auteur_struct * malistedauteur = gen_List_auteur(HauteurHeuvre,sizeHauteurHeuvre);
    malistedauteur->nombre_article = mesfiche.taille;
    // DEBUG("tab auteur str ?? %d et %d",malistedauteur->taille,*nbauteur);
    return malistedauteur;
}


// tab_auteur_struct * unwrap_from_tabfich(tableaux_fiche * mesfiches){
//     int sizeHauteurHeuvre = deplier_fiche(*mesfiches,HauteurHeuvre);
//     DEBUG("DEBUGGG ARRAY %d, %d",MAXarraySIZE,sizeHauteurHeuvre);    
//     sort_tableaux_auteur(HauteurHeuvre,sizeHauteurHeuvre);
//     tab_auteur_struct * malistedauteur = gen_List_auteur(HauteurHeuvre,sizeHauteurHeuvre);
//     return malistedauteur;
// }

tab_auteur_struct * tab_auteur_from_file(FILE * inputFile){
    INFO("Génération tableaux auteur FROMFILE")
    tableaux_fiche * mesfiches = deserialisation_tableaux_fiche(inputFile);
    int sizeHauteurHeuvre = deplier_fiche(*mesfiches,HauteurHeuvre);
    DEBUG("DEBUGGG ARRAY %d, %d",MAXarraySIZE,sizeHauteurHeuvre);    
    sort_tableaux_auteur(HauteurHeuvre,sizeHauteurHeuvre);
    tab_auteur_struct * malistedauteur = gen_List_auteur(HauteurHeuvre,sizeHauteurHeuvre);
    return malistedauteur;
}

tab_Article_struct * convertTab_Article2auteur(const tab_auteur_struct * Malistauteur){
    //compte le nombre de structure pour le maloc
    INFO("Convertion des auteur en Article :")
    int nbstructure = 0;
    for (int i = 0; i < Malistauteur->taille; i++)
    {
        PROGRESSBAR(i,Malistauteur->taille);
        nbstructure+=Malistauteur->tab_auteur[i].size;/// lerreur etait la
    }

    DEBUG("il y a %d structure a générée",nbstructure)
    DEBUG("Calloc de %lu octer",nbstructure*sizeof(Article_struct))
    Paire_Article_auteur * Paire_auteur_oeuvre = calloc(nbstructure,sizeof(Article_struct));

    exitIfNull(Paire_auteur_oeuvre,"imposible de crée Paire_auteur_oeuvre");
    int sizeHauteurHeuvre = deplier_auteur(Malistauteur,Paire_auteur_oeuvre);
    sort_tableaux_Article(Paire_auteur_oeuvre,sizeHauteurHeuvre);
    tab_Article_struct * malistedauteur = assemble_tab_Article(Paire_auteur_oeuvre,sizeHauteurHeuvre,Malistauteur->nombre_article);
    return malistedauteur;
}

void serialisation_tab_Article_struct(tab_Article_struct * inputlist, FILE * outputfile){
    INFO("Sérialisation des Article:")
    int nombreArticle = inputlist->nombre_Article;
    DEBUG("sérialisation de  %d article",nombreArticle)
    fprintf(outputfile,"%d\n",inputlist->nombre_Article);

    for (int i = 0; i < nombreArticle; i++)
    {
        #ifdef WARN_ON
        PROGRESSBAR(i,nombreArticle);
        #endif

        Article_struct article = inputlist->tab_Article[i];
        //le noms de l'article sera obtenue a la désérialisation....
        fprintf(outputfile,"%s\n",article.nom_Article); ///pas glope
        int nombreauteur = article.nombre_auteur;
        YOLO("%s %d",article.nom_Article,nombreauteur);
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
    // DEBUG("\t\t tableauxd d'article %p nb element %d ",monauteur->tab_ptr_Article,monauteur->nbelementmagi)
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
        PROGRESSBAR(j,*nombretotalarticle);
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
        monArticle->tab_ptr_auteur = structauteur;//pointer ?
        //je parcoure tout mes auteur
        for (int i = 0; i < nbauteur; i++)
        {
            int indexmagie = 0;
            fgets(ligne,BALISESIZE,inputfile);
            enlever_retour_a_la_ligne(ligne);
            indexmagie = atoi(ligne);
            exitIfNull(indexmagie,"indexmagienule")
            //je cherche dans le tab auteur en fc de l'index trouver
            structauteur[i] = mesauteur->tab_auteur[indexmagie];

            //je doit  associer a mon auteur de quoi joindre mon article

            //pas obligatoir
            // structauteur[i].nbelementmagi = indexmagie;
            // DEBUG("size %d nombre element maj %d", structauteur[i].size,structauteur[i].nbelementmagi)
            // YOLO("hauteur: %s",structauteur[i].nom_auteur);
            // DEBUG("Ajout de l'article a  %s",monArticle->nom_Article)
            ajout_Article_in_auteur(&structauteur[i],monArticle);
            // DEBUG("!!! addresse %p, nombre d'article contenue %d, %s",structauteur[i].tab_ptr_Article,structauteur[i].nbelementmagi,structauteur[i].nom_auteur)
        }

        //le réalock fout la merde 

        // INFO("Noms article %s",monArticle->nom_Article)
        // INFO("Nombre d'article %d",monArticle->nombre_auteur)
        // for (int i = 0; i < monArticle->nombre_auteur; i++)
        // {
        //     DEBUG("\tAddresse alouer: %p",monArticle->tab_ptr_auteur[i])
        //     DEBUG("\tNoms auteur %s",monArticle->tab_ptr_auteur[i]->nom_auteur)
        //     WARNING("-----")
        // }
        
        
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
tab_Article_struct * gen_tab_Article_from_xml(FILE * dbinput){
    INFO("gen_tab_Article_from_xml:")
    tab_auteur_struct * malistauteur = gen_tab_auteur_from_xml(dbinput);//la
    tab_Article_struct * malistaarticle = convertTab_Article2auteur(malistauteur);
    INFO("tab_Article_struct générée")
    return malistaarticle ;
}

/**
 * @brief genere tout
 * 
 * utilise convertTab_Article2auteur
 * 
 * @param dblpxml 
 * @param inverted 
 * @return unwrap_Graph_struct 
 */
unwrap_Graph_struct gen_unwrap_Graph(FILE * dblpxml, FILE * inverted){
    //check si les cache sont la 
    tableaux_fiche * matablefiche = deserialisation_tableaux_fiche(dblpxml);
    tab_auteur_struct * malistaauteur =   deserialise_tab_auteur_struct(matablefiche,inverted);
    //ajouter la désérialisation
    tab_Article_struct * malistearticle = convertTab_Article2auteur(malistaauteur);
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
