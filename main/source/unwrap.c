#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../header/parsing.h"
#include "../header/unwrap.h"
#include "../header/macro.h"


enum{
    from_XML,
    from_deserialisation
};

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
        for (int u = 0; u < input.fiche[i].nombre_auteur; u++)
        {   
            arrayout[indice].oeuvre = &input.fiche[i];
            arrayout[indice].nom_auteur = input.fiche[i].liste_auteur[u];
            indice++;
        }
    }
    return indice;
}

int deplier_auteur(const tab_auteur_struct * input, Paire_Article_auteur * Article_auteur_Array ){
    DEBUG("deplier_auteur:")
    int indice = 0;
    for (int i = 0; i < input->nombre_auteur; i++){
        PROGRESSBAR(i,input->nombre_auteur);
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
    INFO("Trie tableaux auteur")
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
    DEBUG("QSORT (si echoue visualcode gourmand mémoire)")
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
tab_auteur_struct gen_List_auteur(const Paire_auteur_oeuvre * liste,int sizeHauteurHeuvre){
    INFO("gen_List_auteur:")
    tab_auteur_struct listes_Auteur_arrTitre;
    int * nb_auteur = &listes_Auteur_arrTitre.nombre_auteur; 

    listes_Auteur_arrTitre.nombre_auteur = 0;
    listes_Auteur_arrTitre.tab_auteur = NULL;

    int id = 0;
    int posTabPaireaA = 0;
    //on parcoure liste
    while (posTabPaireaA < sizeHauteurHeuvre)
    {
        PROGRESSBAR(posTabPaireaA,sizeHauteurHeuvre);

        auteur_struct * tb_Somet_h = reallocarray(listes_Auteur_arrTitre.tab_auteur,(*nb_auteur)+1,sizeof(auteur_struct));//fasink alocate error
        exitIfNull(tb_Somet_h,"Erreur création de auteur_struct\n")
        listes_Auteur_arrTitre.tab_auteur = tb_Somet_h;
            
        //initialisation de l'auteur crée
        listes_Auteur_arrTitre.tab_auteur[(*nb_auteur)].size=0                         ;
        listes_Auteur_arrTitre.tab_auteur[(*nb_auteur)].nbArticlecontenue = 0              ;
        listes_Auteur_arrTitre.tab_auteur[(*nb_auteur)].nom_auteur = NULL              ;
        listes_Auteur_arrTitre.tab_auteur[(*nb_auteur)].tab_ptr_Article = NULL         ;    //ducoup malloc le code 
        listes_Auteur_arrTitre.tab_auteur[(*nb_auteur)].tab_ptr_fiche_min = NULL       ;
        listes_Auteur_arrTitre.tab_auteur[(*nb_auteur)].nom_auteur=liste[posTabPaireaA].nom_auteur ;
        listes_Auteur_arrTitre.tab_auteur[(*nb_auteur)].indiceDeCreation = id; //id qui est utilise le graph pour explorer 
        id++;

        int noArticle = 0;
        //tant le prochain auteur est et que l'on n'attein pas la fin de la liste
        while (posTabPaireaA+noArticle < sizeHauteurHeuvre &&
            strcmp(liste[posTabPaireaA].nom_auteur,liste[posTabPaireaA+noArticle].nom_auteur) == 0)//ordre important
        {
            add_titre_to_auteur(&listes_Auteur_arrTitre.tab_auteur[(*nb_auteur)],liste[posTabPaireaA+noArticle]);
            noArticle++;
        }
        //on passe les noArticle auteur au posTabPaireaA article  dans le tableaux Paire_auteur_oeuvre
        posTabPaireaA+=noArticle;
        //on incrémente pour passer au prochain auteur 
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
tab_Article_struct assemble_tab_Article(Paire_Article_auteur * liste,int sizeArticleHauteur,int nombretotalarticle){
    INFO("Génération Liste Article")

    tab_Article_struct ListDesArticle;
    int * nbarticle =  &ListDesArticle.nombre_Article;

    //combien d'article je doit faire ?
    ListDesArticle.tab_Article = NULL;
    DEBUG("Génération tableaux de %lu octer",nombretotalarticle*sizeof(Article_struct))
    ListDesArticle.tab_Article = malloc(nombretotalarticle*sizeof(Article_struct));
    exitIfNull(ListDesArticle.tab_Article,"genarticlelist: Imposible d'allouer tout les tableaux ")
    (*nbarticle) = 0;

    int posTabPairAa = 0;
    DEBUG("Parcour de la liste des article")
    while (posTabPairAa < sizeArticleHauteur)
    {   
        #ifdef WARN_ON
        PROGRESSBAR(posTabPairAa,sizeArticleHauteur);
        #endif

        //on add le premier nom_Article
        ListDesArticle.tab_Article[(*nbarticle)].nombre_auteur=0;
        ListDesArticle.tab_Article[(*nbarticle)].nom_Article=liste[posTabPairAa].article;
        ListDesArticle.tab_Article[(*nbarticle)].tab_ptr_auteur = NULL;


        Article_struct * dernierarticle = &ListDesArticle.tab_Article[(*nbarticle)];
        int * nb_auteur  = &dernierarticle->nombre_auteur;  //utiliser un compteur local pourgagner du temps ?

        //tant le prochain auteur et le meme et que on attein pas la fin de la liste
        while (posTabPairAa+(*nb_auteur) < sizeArticleHauteur && 
            strcmp(liste[posTabPairAa].article,liste[posTabPairAa+(*nb_auteur)].article) == 0)  //ordre important
        {
            YOLO("dernierarticle:%p %p\n",dernierarticle,&ListDesArticle.tab_Article[(*nbarticle)]);

            //création d'auteur struct
            auteur_struct * temparray = reallocarray(dernierarticle->tab_ptr_auteur,(*nb_auteur)+1,8); //8 taille d'un pointeur 
            exitIfNull(temparray,"assemble_tab_Article auteur_struct realockarrayfail\n");            
            dernierarticle->tab_ptr_auteur = (auteur_struct**)temparray;
            dernierarticle->tab_ptr_auteur[*nb_auteur] = liste[(*nb_auteur)+posTabPairAa].pointeur_Auteur;// < nbArticlecontenue ?

            YOLO("hauteur:\t%s\n",dernierarticle->tab_ptr_auteur[*nb_auteur]->nom_auteur);

            //flag pour passer au prochain article
            int found=0;
                                                                                //pASInitialiser ?
            int *localnbelementmaposTabPairAa = &dernierarticle->tab_ptr_auteur[*nb_auteur]->nbArticlecontenue ;

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

void printList_auteur(tab_auteur_struct OwO){
    DEBUG("il y a %d auteur a print ", OwO.nombre_auteur)
    for (int i = 0; i < OwO.nombre_auteur; i++)
    {
        PROGRESSBAR(i,OwO.nombre_auteur);
        BLUE()
        printf("%s (%d):\n",OwO.tab_auteur[i].nom_auteur,OwO.tab_auteur[i].size);    
        GREY()
        for (int j = 0; j < OwO.tab_auteur[i].size; j++)
        {
            printf("\t%s\n",OwO.tab_auteur[i].tab_ptr_fiche_min[j]->titre);
        }
        printf("\n");
    }
    CLRCOLOR()
}


void printList_Article(tab_Article_struct OwO){
    DEBUG("il y a %d article a print ", OwO.nombre_Article)
    for (int i = 0; i < OwO.nombre_Article; i++)
    {
        BLUE()
        printf("%s (%d):\n",OwO.tab_Article[i].nom_Article,OwO.tab_Article[i].nombre_auteur);    
        GREY()
        // DEBUG("Print: %d/%d",i,OwO.nombre_Article)
        for (int j = 0; j < OwO.tab_Article[i].nombre_auteur; j++)
        {
            printf("\t%s\n",OwO.tab_Article[i].tab_ptr_auteur[j]->nom_auteur);
        }
        printf("\n");
    }
    CLRCOLOR()
    
}

int count_isolate_autor(const tab_auteur_struct * List_des_Auteur){
    int compteur = 0;
    for (int i = 0; i < List_des_Auteur->nombre_auteur; i++)
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
    INFO("\tsérialisation des auteur:")
    //fonction d'qui fait la moyenne des nom_auteur pour pouvoir fair un maloque que une foit en moyenne
    fprintf(output,"%d\n",count_isolate_autor(List_des_Auteur));// est egale a List_des_Auteur->taille
    for (int i = 0; i < List_des_Auteur->nombre_auteur; i++)
    {
        #ifdef WARN_ON
        PROGRESSBAR(i+1,List_des_Auteur->nombre_auteur);
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
tab_auteur_struct deserialise_tab_auteur_struct(const tableaux_fiche * tableaux_fiche,FILE * input){
    INFO("\tdeserialise tab auteur")

    char ligne[BALISESIZE];
    tab_auteur_struct master_List_Auteur = {.origine=from_deserialisation,
                                            .nombre_auteur=0};

    fgets(ligne,BALISESIZE,input);
    master_List_Auteur.nombre_auteur = atoi(ligne);
    exitIfNull(master_List_Auteur.nombre_auteur,"nombre d'auteur ilisible")
    DEBUG("Il y a %d auteur unique",master_List_Auteur.nombre_auteur)

    DEBUG("Malloc de %lu octer",sizeof(auteur_struct)*master_List_Auteur.nombre_auteur)
    auteur_struct * Sommet_Auteur_Tableaux =  calloc(master_List_Auteur.nombre_auteur,sizeof(auteur_struct));
    exitIfNull(Sommet_Auteur_Tableaux, "deserialise_tab_auteur_struct: maloc echouer")
    master_List_Auteur.tab_auteur = Sommet_Auteur_Tableaux;

    int nbauteur = 0;
    while (fgets(ligne,BALISESIZE,input))
    {
        PROGRESSBAR(nbauteur,master_List_Auteur.nombre_auteur);

        enlever_retour_a_la_ligne(ligne);
        //on génère le noms
        master_List_Auteur.tab_auteur[nbauteur].nom_auteur = strdup(ligne);

        // on initialise le compteur d'élément 
        master_List_Auteur.tab_auteur[nbauteur].nbArticlecontenue = 0;
        // master_List_Auteur.tab_auteur[nbauteur].nbmembreTabarticleALOUER = 0;
        master_List_Auteur.tab_auteur[nbauteur].tab_ptr_Article = NULL;

        fgets(ligne,BALISESIZE,input);
        master_List_Auteur.tab_auteur[nbauteur].size = atoi(ligne);
        exitIfNull(master_List_Auteur.tab_auteur[nbauteur].size,"nombre d'auteur incorect !")

        master_List_Auteur.tab_auteur[nbauteur].tab_ptr_fiche_min = calloc(master_List_Auteur.tab_auteur[nbauteur].size,sizeof(auteur_struct)); //<= bon type ?
        exitIfNull(master_List_Auteur.tab_auteur[nbauteur].tab_ptr_fiche_min,"allocation master_List_Auteur.tab_auteur[nbauteur].tab_ptr_fiche_min echouser...");

        for (int u = 0; u < master_List_Auteur.tab_auteur[nbauteur].size; u++)
        {
            fgets(ligne,BALISESIZE,input);
            enlever_retour_a_la_ligne(ligne);
            int indiceFiche = atoi(ligne);
            exitIfNull(&tableaux_fiche->fiche[indiceFiche],"serialise index pointeur sur nom_auteur introuvable\n")
            master_List_Auteur.tab_auteur[nbauteur].tab_ptr_fiche_min[u] = &tableaux_fiche->fiche[indiceFiche]; //On n'es pas obliger de lire la fiche
        }
        nbauteur++;
    }
    master_List_Auteur.nombre_article = tableaux_fiche->taille;
    return master_List_Auteur;
}



tab_auteur_struct convertTab_fiche2auteur(tableaux_fiche mesfiche);

tab_auteur_struct gen_tab_auteur_from_xml(FILE * dbinput){
    INFO("Generation Tab auteur:")
    return convertTab_fiche2auteur(parse(dbinput));
}

tab_auteur_struct tab_auteur_from_file(FILE * inputFile){
    INFO("Génération tableaux auteur FROMFILE")
    return convertTab_fiche2auteur(deserialisation_tableaux_fiche(inputFile));
}

tab_auteur_struct convertTab_fiche2auteur(tableaux_fiche mesfiche){
    INFO("Convert tableaux fiche to auteur")

    int nbPaire_auteur_oeuvre = mesfiche.nbAuteurXarticle;
    DEBUG("%d auteur*Article, size %lu",nbPaire_auteur_oeuvre,sizeof(Paire_auteur_oeuvre)*mesfiche.nbAuteurXarticle)

    Paire_auteur_oeuvre * HauteurHeuvre = calloc(nbPaire_auteur_oeuvre,sizeof(Paire_auteur_oeuvre));
    exitIfNull(HauteurHeuvre,"caloc imposible")

    int sizeHauteurHeuvre = deplier_fiche(mesfiche,HauteurHeuvre);
    sort_tableaux_auteur(HauteurHeuvre,sizeHauteurHeuvre);

    tab_auteur_struct malistedauteur = gen_List_auteur(HauteurHeuvre,sizeHauteurHeuvre);
    malistedauteur.nombre_article = mesfiche.taille;
    malistedauteur.origine        = from_XML;

    free(HauteurHeuvre);
    return malistedauteur;
}

int count_NeedednbPaire_auteur_oeuvre(const tab_auteur_struct * Malistauteur){
    DEBUG("compte le nombre de structure pour le maloc")
    int nbstructure = 0;
    for (int i = 0; i < Malistauteur->nombre_auteur; i++)
    {
        PROGRESSBAR(i,Malistauteur->nombre_auteur);
        nbstructure+=Malistauteur->tab_auteur[i].size;
    }
    DEBUG("il y a %d structure a générée",nbstructure)
    return nbstructure;
}

tab_Article_struct convertTab_auteur2Article(const tab_auteur_struct * Malistauteur){
    INFO("Convertion des auteur en Article :")

    int nbstructure = count_NeedednbPaire_auteur_oeuvre(Malistauteur);
    DEBUG("Calloc de %lu octer",nbstructure*sizeof(Article_struct))
    Paire_Article_auteur * Paire_auteur_oeuvre = calloc(nbstructure,sizeof(Article_struct));
    exitIfNull(Paire_auteur_oeuvre,"imposible de crée Paire_auteur_oeuvre");

    int sizeHauteurHeuvre = deplier_auteur(Malistauteur,Paire_auteur_oeuvre);
    sort_tableaux_Article(Paire_auteur_oeuvre,sizeHauteurHeuvre);
    tab_Article_struct malistedauteur = assemble_tab_Article(Paire_auteur_oeuvre,sizeHauteurHeuvre,Malistauteur->nombre_article);

    free(Paire_auteur_oeuvre);
    return malistedauteur;
}


void serialisation_tab_Article_struct(tab_Article_struct * inputlist, FILE * outputfile){
    INFO("\tSérialisation des Article:")
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
            int indiceAuteur = article.tab_ptr_auteur[u]->indiceDeCreation;
            YOLO("%d don? %s",indiceAuteur,article.tab_ptr_auteur[u]->nom_auteur)
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

    if (monauteur->nbmembreTabarticleALOUER<=monauteur->nbArticlecontenue)
    {
        monauteur->nbmembreTabarticleALOUER=(monauteur->nbArticlecontenue+2)*2;
        Article_struct ** tmptest = reallocarray(monauteur->tab_ptr_Article,monauteur->nbmembreTabarticleALOUER,sizeof(Article_struct*));
        exitIfNull(tmptest,"ajout article erreur realockarray")
        monauteur->tab_ptr_Article = tmptest;
    }

    monauteur->tab_ptr_Article[monauteur->nbArticlecontenue] = monArticle;
    monauteur->nbArticlecontenue++;
    YOLO("\t\t tableauxd d'article %p nb element %d ",monauteur->tab_ptr_Article,monauteur->nbArticlecontenue)
    YOLO("%d",monauteur->nbArticlecontenue)
}

//faire une interface pour sérialiser deserialiser ?
tab_Article_struct deserialisation_tab_Article_struct(tab_auteur_struct * mesauteur, FILE * inputfile){
    INFO("\tdeserailisation Article")

    char ligne[BALISESIZE];
    tab_Article_struct mon_tab_Article_struct;
    mon_tab_Article_struct.nombre_Article=0;
    int * nombretotalarticle = & mon_tab_Article_struct.nombre_Article;

    fgets(ligne,BALISESIZE,inputfile);
    *nombretotalarticle = atoi(ligne);

    DEBUG("il y a %d Article",*nombretotalarticle)
    DEBUG("Malloc de %luocter",sizeof(Article_struct)**nombretotalarticle)

    //optimiser car on alloue tout en un malloc ! par contre ça peut echouer a voir
    Article_struct * listedesArticle =  malloc(sizeof(Article_struct)**nombretotalarticle);
    exitIfNull(listedesArticle, "creation des sommet auteur tableaxD malloc null")
    mon_tab_Article_struct.tab_Article = listedesArticle;

    for (int j = 0; j < *nombretotalarticle; j++)
    {
        PROGRESSBAR(j,*nombretotalarticle);

        Article_struct * monArticle = &mon_tab_Article_struct.tab_Article[j];
        
        //pas si utile .... Peut faire autrement
        fgets(ligne,BALISESIZE,inputfile);
        enlever_retour_a_la_ligne(ligne);
        YOLO("ligneNomsarticle=%s",ligne)
        monArticle->nom_Article = strdup(ligne);

        //nombre d'auteur sur cette structure
        fgets(ligne,BALISESIZE,inputfile);
        int nbauteur = 0;
        nbauteur = atoi(ligne);
        monArticle->nombre_auteur = nbauteur;
        exitIfNull(nbauteur,"il y a 0 article")
        enlever_retour_a_la_ligne(ligne);
        YOLO("nombre dauteur %d",nbauteur);


        monArticle->tab_ptr_auteur = NULL;
        auteur_struct ** structauteur = calloc(sizeof(auteur_struct*),nbauteur);
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
            YOLO("nombre ID auteur %d",indexmagie)
            //je cherche dans le tab auteur en fc de l'index trouver
            structauteur[i] = &(mesauteur->tab_auteur[indexmagie]);
            YOLO("noms de l'auteur %s",structauteur[i]->nom_auteur)
            ajout_Article_in_auteur(structauteur[i],monArticle);
        }

        #ifdef YOLO_ON
        INFO("Noms article %s",monArticle->nom_Article)
        INFO("Nombre d'article %d",monArticle->nombre_auteur)
        for (int i = 0; i < monArticle->nombre_auteur; i++)
        {
            DEBUG("\tAddresse alouer: %p",monArticle->tab_ptr_auteur[i])
            DEBUG("\tNoms auteur %s",monArticle->tab_ptr_auteur[i]->nom_auteur)
            WARNING("-----")
        }
        #endif 
    }
    return mon_tab_Article_struct;
}

/**
 * @brief article depuit le xml de base
 * 
 * @param dbinput 
 * @return tab_Article_struct* 
 */
tab_Article_struct gen_tab_Article_from_xml(FILE * dbinput){
    INFO("gen_tab_Article_from_xml:")
    tab_auteur_struct   malistauteur   = gen_tab_auteur_from_xml(dbinput);//la
    tab_Article_struct  malistaarticle = convertTab_auteur2Article(&malistauteur);
    INFO("tab_Article_struct générée")
    return malistaarticle ;
}

/**
 * @brief genere tout
 * 
 * utilise convertTab_auteur2Article
 * 
 * @param dbxmlCache 
 * @param inverted 
 * @return graphe_struct_Konqui 
 */
graphe_struct_Konqui deserialise_Graph(FILE * dbxmlCache, FILE * auteurCache, FILE * ArticleCache){
    INFO("Désérialisation du Graph:")
    tableaux_fiche      mesfiche    =   deserialisation_tableaux_fiche(dbxmlCache);
    tab_auteur_struct   mes_auteur   =   deserialise_tab_auteur_struct(&mesfiche,auteurCache);
    tab_Article_struct  mes_Article  =   deserialisation_tab_Article_struct(&mes_auteur,ArticleCache);
    mes_Article.origine = from_deserialisation;
    graphe_struct_Konqui graph  = {mes_auteur, mes_Article,mesfiche};
    return graph;
}

graphe_struct_Konqui gen_Graph_from_XML(FILE * dbxmlCache){
    INFO("Génération du graph (XML)")
    tableaux_fiche      mesfiche    = parse(dbxmlCache);
    tab_auteur_struct   mes_auteur  = convertTab_fiche2auteur(mesfiche);
    tab_Article_struct  mes_Article = convertTab_auteur2Article(&mes_auteur);
    mes_Article.origine = from_XML;
    graphe_struct_Konqui graph  = {mes_auteur, mes_Article,mesfiche};
    return graph;
}

void serialise_Graph(graphe_struct_Konqui graph, FILE * dbxmlCache, FILE * auteurCache, FILE * ArticleCache){
    INFO("Sérialisation du graph:")
    serialisation_tableaux_fiche(graph.tableaux_de_fiche,dbxmlCache);
    serialise_tab_auteur_struct(&graph.tab_auteur_struct,auteurCache);
    serialisation_tab_Article_struct(&graph.tab_Article_struct,ArticleCache);
}


void free_auteur(auteur_struct auteur,int contexte){
    if (contexte == from_deserialisation)
    {
        free(auteur.nom_auteur); 
    }
    free(auteur.tab_ptr_Article);
    free(auteur.tab_ptr_fiche_min);
}

void free_Article(Article_struct Article, int contexte){
    if (contexte == from_deserialisation)
    {
        //le strdup n'es pas lier au fiche
        free(Article.nom_Article); 
    }
    free(Article.tab_ptr_auteur);
}

void free_tab_auteur(tab_auteur_struct afree){
    INFO("Free tab auteur")
    for (int i = 0; i < afree.nombre_auteur; i++)
    {
        PROGRESSBAR(i,afree.nombre_auteur);
        free_auteur(afree.tab_auteur[i],afree.origine);
    }
    free(afree.tab_auteur);
}

void free_tab_Article(tab_Article_struct afree){
    INFO("Free tab Article")
    for (int i = 0; i < afree.nombre_Article; i++)
    {
        PROGRESSBAR(i,afree.nombre_Article);
        free_Article(afree.tab_Article[i],afree.origine);
    }
    free(afree.tab_Article);
}

void free_Graph_struct(graphe_struct_Konqui afree){
    //les 3 peuve être faite en paralèle
    free_tab_fiche(afree.tableaux_de_fiche);
    free_tab_auteur(afree.tab_auteur_struct);
    free_tab_Article(afree.tab_Article_struct);
}
