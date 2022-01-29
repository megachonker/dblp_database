#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>
#include "../header/macro.h"
#include "../header/unwrap.h"
#include "../header/search.h"
#include "../header/Dijkstra.h"
#include <signal.h>
#include <stdlib.h>

/** \mainpage Document d'information
 *   
 * \section Résumé_général Résumé général
 * **1ère étape**:
 * 
 * -parsing: fonction parse(), retourne tableaux_fiche (fiches contenants chaqu'une un nom d'Article et les noms des auteurs associés)
 * -serialisation du tableau_fiche (serialisation_tableaux_fiche()).
 * (la serialisation permet de stocker les informations du parsing pour ne pas à avoir à le refaire)
 * 
 * traité dans *parsing.c*
 * 
 *  **2ème étape**:
 * 
 * -Desserialisation du tableau_fiche (deserialisation_tableaux_fiche())
 * -Création de la jointure entre les fiches de tableaux_fiche et les noms des auteurs associés (sous condition que l'auteur appartient à la fiche).
 * -Cette opération pourra être appelée dépliage, et sert à construire le tableau des Paire_auteur_oeuvre (deplier_fiche())
 * -Ce tableau sera trié par nom d'auteur de manière a récupérer tous les articles pour chaque auteur, on peut alors construire les auteur_struct (gen_List_auteur()).
 * 
 * -Ensuite sera opérée une 2ème jointure, cette fois entre les auteurs_struct et les fiches de tableau_fiche, (sous condition que les auteurs soient bien dans les Articles des fiches)
 * -Ce nouveau "dépliage" mène à la création du tableau des Paire_Article_auteur (deplier_auteur()).
 * -On peut alors génèrer les Article_struct en triant la jointure par nom d'Article en ce faisant, on peut aussi set up le champs tab_ptr_Article des auteurs_struct. (convertTab_auteur2Article())
 * - **l'ordre de création** des fiche_minimale sera un **identifiant unique**
 * 
 * -Le tableau des auteur_struct et celui des Article_struct seron stocké dans graphe_struct_Konqui.
 * -Pour finir, un tableau de pointeur vers les auteurs_struct est crée, et rangé dans graphe_Katie (fonction dans *fonctions_garphe.c*). 
 * -Les attributs des auteur_struct utiles à Dijkstra sont alors initialisés (comme par exemple la distance à l'auteur_depart, initialisé à -1).
 * 
 * -Cette partie se déroule dans *unwrap.c*
 * 
 *  **3ème étape**:
 * 
 * -Il ne reste plus qu'à appliquer la fonction do_Dijkstra() (*Dijkstra.c*) au graphe_Katie, avec 2 noms d'auteur de la base de donnée.
 * -Pour cela, on relache les arrêtes de tous les auteurs rangés dans un tableau indiquant les auteurs à traiter à l'étape courante du parcours en largeur.
 * (Ce tableau s'appelant pile_courante)
 * -En ce faisant, on enregistre les auteurs à traiter à l'étape suivante dans un autre tableau (pile_suivante).
 * -De même, on initialise l'attribut auteur_predecesseur et Article_predecesseur de l'auteur_struct en cours de traitement.
 * -A la fin de l'étape courante (une couche du parcours en largeur) on remplace le contenu de pile_courante par celui de pile_suivante et on vide la pile_suivante.
 * 
 * -En répétant ce procédé jusqu'a trouver l'auteur_destination ou avoir parcouru toute la composante connexe,
 * il est possible d
 * 
 * 
 * 
 * \section Pour_plus_de_détailles Pour plus de détailles
 * 
 * \subsection fiche_gene Génération fiche
 * la structure fiche_minimale contient les informations d'un Article, elle est aloueée dynamiquement. On peut retrouver les fiche_minimale dans tableaux_fiche et auteur_struct.
 * 
 * traité dans *paring.c*
 * \subsubsection parse_xml Parsing XML
 *  - le parsing ce fait en admétant qu'il y a **une paire de balise par ligne** (plus rapide et simple sachant que le format du fichier ne changera pas).
 *  - le noms de l'Article et les auteur sont gardé.
 *  - **l'ordre de création** des fiche_minimale sera un **identifiant unique** (comme une clef primaire).
 * \subsubsection serialisation_xml Sérialisation XML
 * La sérialisation est faite pour avoir un fichier plus petit (tmps de lecture) comportant déja les structure (en binaire) nous utilison fwread et fwrite qui sont simplifier avec la macro writestrfile() et readstrfile() pour gagner en temps est en clartée
 * \subsection generation_auteur Génération auteur
 * 
 * Pour générer un tab_auteur_struct qui contient nos auteur_struct il va falloir **joindre** les *fiche_minimale*  avec les *noms des auteur* de cette manière les couples Paire_auteur_oeuvre sont générés.
 * En triant le tableau de Paire_auteur_oeuvre par nom d'auteur, tous les occurences d'un meme nom d'auteur dans la jointure se suivront !
 * Il ne restera plus qu'a associer les X fiche_minimale qui on les memes auteurs pour se ramener à un tableau d'auteur unique.
 *
 * - **sérialisation** ne pouvant sérialiser les fiche_minimale il suffit juste d'inscrire l'id de la fiche (son indice dans l'ordre de création)
 * - **désérialisation** On récupère ici la fiche, grace a l'id lu (l'id étant l'emplacement dans le tableaux, et les tableaux étant de meme taille est de meme donnée) il faut cependant désérialiser les fiche_minimale.
 * 
 * En désérialisant les fiches on économise le temps de parsage et de lecture.
 * 
 * La relation entre les noms d'auteur est les fiche_minimale est décrite dans une structure Paire_auteur_oeuvre afin de pouvoir la passer en argument dans la fonction qsort (built in optimiser pour faire un trie rapide).  
 * On peut ensuite construire les auteur_struct uniques à l'aide de cette relation.
 * 
 * Se déroule dans *unwrap.c*
 * 
 * \subsection generation_article Génération Article
 * A présent nous avons une relation auteur_struct vers fiche_minimale mais pas le contraire,  
 * la structure Article_struct modélisera ce lien en ayant pour attribut, pour chaque Article_struct, les auteur_struct associés.
 * 
 *    ça, ça me semble pas clair        //La relation n'est pas inscrite dans la structure fiche_minimale car supposont que nous stockons plus d'information comme la date,le cite web ect ce fichier deviendra plus gros est donc plus lent a parser et deviendra le bottleneck
 *    et on peut l'enlever je pense     //il faut donc bien isoler la biblioteque est ses structures liées au **parsing** et celle lier au **traitment**.
 * 
 * A la création des Article_struct (apres avoir joint, trié et fusioner Paire_Article_auteur) un id de création y est inscrit.
 * A chaque Article crée, à l'ajout des auteur_struct on va ajouter un pointeur de l'Article_struct parent a auteur_struct cible (on set up auteur_struct.tab_ptr_Article)
 * 
 * Il faudra faire attention a ce q'un auteur_struct ne soit pas plusieurs fois ajouté dans le meme Article_struct !
 * 
 * - **serialisation** on sérialise les id de création de la structure et non les adresses des auteur_struct 
 * - **désérialisation** en ayant désérialisser au préalable auteur_struct on peut asocier les pointeur a Article_struct
 * 
 * une structure finale  graphe_struct_Konqui regroupant toutes les structures désérialisées/crées est générée pour simplifier les free et l'utilisation
 * 
 * \subsection Dijkstra
 * 
 * do_Dijkstra() s'applique sur un tableau de pointeur vers les auteurs_struct, situé dans graphe_struct_Katie. 
 * (Pour les noms d'auteur passés en argument, veuillez respecter les conventions HTML renseignées ici https://sites.psu.edu/symbolcodes/codehtml/#accent)
 * fonctionnement de do_Dijkstra() (*Dijkstra.c*):
 *  
 * On relache les arrêtes de tous les auteurs rangés dans un tableau indiquant les auteurs à traiter à l'étape courante du parcours en largeur.
 * (Ce tableau s'appelant pile_courante)
 * En ce faisant, on enregistre les auteurs à traiter à l'étape suivante dans un autre tableau (pile_suivante).
 * De même, on initialise l'attribut auteur_predecesseur et Article_predecesseur de l'auteur_struct en cours de traitement.
 * A la fin de l'étape courante (une couche du parcours en largeur) on remplace le contenu de pile_courante par celui de pile_suivante et on vide la pile_suivante.
 * 
 * En répétant ce procédé jusqu'a trouver l'auteur_destination ou avoir parcouru toute la composante connexe,
 * il est possible d'enregistrer le plus court chemin dans plus_court_chemin_struct en partant de l'auteur_destination et en remontant la chaine des prédecesseurs.
 * 
 * \subsection executable programme utilisateur
 * \subsubsection main Main
 * 2 mode un mode ligne de commande est un mode interractif
 * Le mode interactif utilise une librairie externe de regex mais permet de réefectuer une recherche en ce basant sur les resulats précédents.
 * \subsubsection abenchsh scripte abench
 * Permet de chronometrer le temps sur un nombre donné de réexecution, et en fait une moyenne.
 * 
 * Il faut avoir time installé (l'ajout des couleur a rendu le script instable) //WHAT? le scripte est instable?
 * 
 * \subsubsection bench Benchmarking
 * permet d'executer des fonctions du programme en fonction des arguments pour:
 * -    débuguer
 * -    profiler
 * -    benchmarking
 * -    cache généré a l'apelle de make 
 * -    **Tester le programe** avant de commmit.
 * \subsubsection macro macro
 * Utilisant les macro pour la gestion des couleurs et des erreurs. 
 * 
 * 
 * \subsection makefile make
 * \subsubsection update updating
 * Permet vérifier si la base de donnée utilisée est la dernière qui a été uploadée sur les serveurs et de la télécharger si ce n'est pas le cas.
 * \subsubsection cache generation cache
 * Je comprend pas la phrase, il faut reformuler je pense //dans la premierre version j'utiliser le programe bench pour regénérée le cache intermediere lier au code source modifier avec une fonction présice, très performant en vérifiant la coérance des cache entre eux je n'ais pas eux besoin de coder cette fonctionaliter
 * 
 * La génération se fait en un bloque, avec des fonctions généralistes générant les 3 caches en meme temps.
 * 
 * \subsubsection kkachgrind Profiler
 * Permet de générer des fichiers callgrind pour kcachgrind pour des fonctions du programme
 * 
 *  Tu peux laisser cette phrase mais on est pas sensé raconter ce genre de truc dans le rapport je pense //(Konqui:)j'ai pris l'habitude de profiler le programe au fure et à mesure de sont avancement pour mieux comprendre le fonctionement est les optimisations
 * \subsubsection lcoverapport Lcov
 * Le rapport est utile pour detecter les parcelles de code inutiles
 * 
 * Le raport lcove fonctionne sur arch linux mais pas sur ubuntu (erreur imposible a diagnostiquer).
 * 
 * 
 * 
 * 
 *
 */


/**
 * @brief permet de conserver tout les chemain des cache
 * 
 */
typedef struct listeChemain
{
    char *XML;
    char *DBfiche;
    char *DBauteur;
    char *DBArticle;
} listeChemain;


/**
 * @brief conserve tout les argument pour les passer au fonction
 * 
 */
typedef struct total
{
    char ligne[BALISESIZE];
    char * argv[5];
    graphe_struct_Konqui graph;
    listeChemain chem;          ///< tout les chemain 
    int verb;                   ///< énume de la verbositer
    ll_list * recherche;        ///< conserve la recherche en coure 
}total;


/**
 * @brief génère le graph a partire de listeChemain
 * 
 * @param chemains 
 * @return graphe_struct_Konqui 
 */
graphe_struct_Konqui gen_graph(listeChemain chemains)
{

    FILE *DBxml = fopen(chemains.XML, "r");
    FILE *DBinverse = fopen(chemains.DBfiche, "r");
    FILE *DBauteur = fopen(chemains.DBauteur, "r");
    FILE *DBarticle = fopen(chemains.DBArticle, "r");

    exitIfNull(DBxml, "INPUT PAS CHEMAIN %s", chemains.XML)
        exitIfNull(DBinverse, "INPUT PAS CHEMAIN %s", chemains.DBfiche)
            exitIfNull(DBauteur, "INPUT PAS CHEMAIN %s", chemains.DBauteur)
                exitIfNull(DBarticle, "INPUT PAS CHEMAIN %s", chemains.DBArticle)

                    fseek(DBxml, 0, SEEK_END);
    fseek(DBinverse, 0, SEEK_END);
    fseek(DBauteur, 0, SEEK_END);
    fseek(DBarticle, 0, SEEK_END);

    if (!ftell(DBxml) || !ftell(DBinverse) || !ftell(DBauteur) || !ftell(DBarticle))
    {
        exitIfNull(0, "Un fichier de db est vide")
    }

    fseek(DBxml, 0, SEEK_SET);
    fseek(DBinverse, 0, SEEK_SET);
    fseek(DBauteur, 0, SEEK_SET);
    fseek(DBarticle, 0, SEEK_SET);

    graphe_struct_Konqui graph = deserialise_Graph(DBinverse, DBauteur, DBarticle);
    if (!graph.tab_Article_struct.nombre_Article || !graph.tab_auteur_struct.nombre_auteur || !graph.tableaux_de_fiche.taille)
    {
        exitIfNull(0, "Une des structure est vide");
    }
    INFO("Graphe Générée !")
    return graph;
}

void dfault()
{
    printf("\
// • -c                calculer les composantes connexes & diamètre.\n\
• -p AUT1,AUT2      plus court chemin auteurs indiqués.\n\
• -l MOT            Lister les auteurs qui contiennent le mot donné.\n\
• -a auteur         Fnformations d'un auteur (liste des articles).\n\
• -A Article        Liste les co-auteurs à distance N (ou moins) d'un auteur.\n\
• -f INPUT          cache d\'entrée. small full custom \n\
// • -o OUTPUT         Sauvegarder la structure dans un fichier binaire (indiqué avec une option -o OUTPUT_FILE)\n");
}

void sdfault()
{
    printf("\n -c -p AUT1,AUT2 -l MOT -a auteur -A article -f INPUT");
}

typedef struct all_options
{
    int caluleadv, distanceN, verbose;
    char output[100], auteur_selectioner[100], search[100], lmot[100], searchAll[100];
    char couple_auteur[2][100];
    struct listeChemain chemais;
} all_options;


/**
 * @brief charge des chemain des fichier a partire des enum
 * 
 * @param choix 
 * @return listeChemain 
 */
listeChemain chose_path(short choix)
{

    listeChemain chemains[3];

    listeChemain smal = {
        .XML = smallorigineXML,
        .DBfiche = small_fiche_cache,
        .DBauteur = small_auteur_cache,
        .DBArticle = small_Article_cache};

    listeChemain ful = {
        .XML = origineXML,
        .DBfiche = cache_fiche,
        .DBauteur = auteur_cache,
        .DBArticle = Article_cache};

    listeChemain cust = {
        .XML = customXML,
        .DBfiche = custom_fiche_cache,
        .DBauteur = custom_auteur_cache,
        .DBArticle = custom_Article_cache};

    chemains[small] = smal;
    chemains[full] = ful;
    chemains[custom] = cust;

    return chemains[choix];
}

/**
 * @brief fait une regerche 
 * 
 * @param search expression regulierre
 * @param graph  graph pour rechercher
 * @param verbose énume du degrer de verbositer
 */
void find_all(char *search, graphe_struct_Konqui *graph, int verbose)
{
    ll_list *retoura = stringSearch(graph, searchauteur, search);
    ll_list *retour = stringSearch(graph, searchArticle, search);
    if (retoura->size == 0)
    {
        ERROR("recherche auteur 0");
    }
    else
    {
        printSearch(retoura, verbose);
    }
    if (retour->size == 0)
    {
        ERROR("recherche Article 0");
    }
    else
    {
        printSearch(retour, verbose);
    }
}

/**
 * @brief convertie la chaine de caractere en énume
 * 
 * @param compstr 
 * @param chemain 
 * @return int 
 */
int chose_db(char *compstr, listeChemain *chemain)
{
    if (compstr==NULL)
    {
        ERROR("mauvais choix de base de donner, Essayer:\t\n\t- full\t\n\t- custom\t\n\t- small")
        return 1;
    }

    if (NULL)
    {
    STR("full")
    *chemain = chose_path(full);
    STR("custom")
    *chemain = chose_path(custom);
    STR("small")
    *chemain = chose_path(small);
    }else
    {
        ERROR("mauvais choix de base de donner, Essayer:\t\n\t- full\t\n\t- custom\t\n\t- small")
        return 1;
    }
    INFO("DB %s selectioner:", compstr)
    return 0;
}

//faire

// parse arg

/**
 * @brief message d'aide full pour le mode interactif
 * 
 */
void interactive_help(){
printf("\
    * help    print this help\n\
    * file    [full/small/custom] input file (small default value)\n\
    * compute permet de générer le graph en fonction de file\n\
    * search  [A/a/b] [querry] (permet deffectuer une recherche regex)\n\
            -   A pour les article\n\
            -   a pour les auteur\n\
            -   b pour both donc les 2\n\
    * top [number] [A/a]\n\
            -   A pour les article\n\
            -   a pour les auteur\n\
    * v       alterne entre les 3 niveaux de verbositer\n\
    * exit,q  quite...\n");
}

void interactive_chort_help(){printf("commande are: help, file, compute, search, top, v, exit/q\n");}



/**
 * @brief gros switch permetant d'executer un programe en fonction de la ligne entrée par l'utilisateur
 * 
 * @param [in] argc nombre d'argument
 * @param [in] argv tableaux d'argument
 * @param [in] graph graph générer ou non
 * @param [in] chem structure de chemain
 * @param [in] verb verbositer désirer
 * @return int état de la commande
 */
int switchAndExec(total * variable)
{
    char *compstr = variable->argv[0];

    if
    (NULL){
    STR("exit")
        exit(0);
    STR("dik")
        if (variable->graph.tab_Article_struct.nombre_Article == 0)
        {
            ERROR("graph vide veuiller le calculer (compute)")
            return 1;
        }
        CHK3ARG(variable->argv,"dik auteur1 auteur2")
        djikstrasearch(variable->argv[1], variable->argv[2], variable->graph);
    STR("q")
        exit(0);
    STR("help")
        interactive_help();
    STR("file")
        return chose_db(variable->argv[1], &variable->chem);
    STR("compute")
        variable->graph = gen_graph(variable->chem);
    STR("c")
        variable->graph = gen_graph(variable->chem);
    STR("v")
        if (variable->verb == silence)
        {
            INFO("verbeux")
            variable->verb = verbeux;
        }
        else if (variable->verb == verbeux)
        {
            INFO("VraimentTropVerbeux")
            variable->verb = VraimentTropVerbeux;
        }
        else
        {
            INFO("silence")
            variable->verb = silence;
        }
    // STR("flush")
    // STR("s")
    //     if (&variable->graph.tab_Article_struct == NULL)
    //     {
    //         ERROR("graph vide veuiller le calculer (compute)")
    //         return 1;
    //     }
    //DIKstra
    STR("p")
        return printSearch(variable->recherche,variable->verb);
    STR("research")
        if (variable->recherche == NULL){
            WARNING("veiller éfectuer une recherche avant de l'affiner")
            return 1;
        }
        CHK3ARG(variable->argv,"pas assez d'argument\nS/d Save/delet\n\t\t - d suprime les match\n\t\t - s garde les match");
        char *compstr = variable->argv[1];
        if (NULL)
        {
            STR("s")
                restringSearch(variable->recherche, whitelist, variable->argv[2]);
            STR("d")
                restringSearch(variable->recherche, blacklist, variable->argv[2]);
            }else{
                WARNING("mauvais argument\nS/d Save/delet\n\t\t - d suprime les match\n\t\t - s garde les match")
            }
        if (variable->verb != silence)
        {
            return printSearch(variable->recherche,variable->verb);
        }
    STR("search")
        if (!variable->graph.tab_Article_struct.tab_Article->nom_Article)
        {
            ERROR("graph vide veuiller le calculer (compute)")
            return 1;
        }
        CHK2ARG(variable->argv,"search: A/a/b Auteur, article, both (les 2)");
        CHK3ARG(variable->argv,"rentrer un terme de recherche (regex)");

    char *compstr = variable->argv[1];
        if (NULL)
        {
            
            STR("A")
                variable->recherche = stringSearch(&variable->graph, searchArticle, variable->argv[2]);
            STR("a")
                variable->recherche = stringSearch(&variable->graph, searchauteur, variable->argv[2]);
            STR("b")
                variable->recherche = stringSearch(&variable->graph, searchBoth, variable->argv[2]);
        }
        if (variable->verb != silence)
        {
            printSearch(variable->recherche,variable->verb);
        }
        
    STR("top")
        if (variable->graph.tab_Article_struct.nombre_Article == 0)
        {
            ERROR("graph vide veuiller le calculer (compute)")
            return 1;
        }
        if(variable->argv[1] == NULL){
            ERROR("pas de nombre passer")
            return 1;
        }
        if (variable->argv[2] == NULL)
        {
            ERROR("Choisisez A/a Article/auteur")
            return 1;
        }
        
        int top = atoi(variable->argv[1]);

        char *compstr = variable->argv[2];
        if (NULL)
        {
            STR("A")
            // variable->recherche = 
            scoarboard(&variable->graph, TOP_Article, top, variable->verb);
            STR("a")
            // variable->recherche = 
            scoarboard(&variable->graph, TOP_auteur, top, variable->verb);
        }
    }else{
        interactive_chort_help();  
    }
    return 0;
}


/**
 * @brief "main" de la partie interactive
 * 
 */
void interactive()
{
    init_signal();
    total variable = {.chem=chose_path(small), .verb=silence,.recherche=NULL};
    variable.graph = gen_graph(variable.chem);
    while (fgets(variable.ligne, BALISESIZE, stdin))
    {

        int argc = parse_arg(variable.ligne, variable.argv);
        if (argc > 4)
        {
            ERROR("trop d'argument fournis")
            continue;
        }
        else if (argc < 0)
        {
            ERROR("pas assez d'argument")
            continue;
        }

        switchAndExec(&variable);

        variable.argv[0] = NULL;
        variable.argv[1] = NULL;
        variable.argv[2] = NULL;
        variable.argv[3] = NULL;

    }
}

/**
 * @brief fait une recherche dikstra
 * 
 * @param a auteur départ 
 * @param b auteur d'arriver
 * @param graph graph en argument
 */
void djikstrasearch(char *a, char *b, graphe_struct_Konqui graph)
{
    graphe_struct_Katie graphe_Katie = faire_graphe_ptr_auteur(graph);
    plus_court_chemin_struct *plus_court_chemin_ptr = do_Dijkstra(graphe_Katie, a, b);
    if (plus_court_chemin_ptr != NULL)
    {
        print_chemins_auteur_et_Article(plus_court_chemin_ptr);
    }
    else
    {
        ERROR("PAS DE CHEMIN")
    }
    free_Dijkstra(graphe_Katie, plus_court_chemin_ptr);
}


all_options gen_Struct_option(int argc, char *argv[])
{
    all_options parsed_option = {.lmot = "", .auteur_selectioner = "", .searchAll = "", .couple_auteur[0] = "", .couple_auteur[1] = ""};
    int option;
    if (argc == 1)
    {
        printf("essayer -h pour les option.");
        sdfault();
    }
    parsed_option.chemais = chose_path(small);
    parsed_option.verbose = silence;
    while ((option = getopt(argc, argv, "ihvVc:p:l:a:A:o:f:n")) != -1)
    {
        switch (option)
        {
        case 'h':
            dfault();
            break;
        case 'i':
            interactive();
            break;
        case 'v':
            parsed_option.verbose = verbeux;
            break;
        case 'V':
            parsed_option.verbose = VraimentTropVerbeux;
            break;
        case 'n':
            parsed_option.distanceN = atoi(optarg);
            break;
        case 'l':
            strcpy(parsed_option.lmot, optarg);
            break;
        case 'c':
            parsed_option.caluleadv = 1;
            break;
        case 'a':
            strcpy(parsed_option.auteur_selectioner, optarg);
            break;
        case 'A': //alll
            strcpy(parsed_option.searchAll, optarg);
            break;
        case 'p':
            strcpy(parsed_option.couple_auteur[0], optarg);
            *strchr(parsed_option.couple_auteur[0], ',') = '\0';
            strcpy(parsed_option.couple_auteur[1], strchr(optarg, ',') + 1);
            break;
        case 'f':
            chose_db(optarg, &parsed_option.chemais);
            break;
        case 'o': //here f is used for some file name
            // strcpy(parsed_option.fileInput,optarg);
            break;
        case '?': //used for some unknown options
            switch (optopt)
            {
            case 'c':
                printf("-c correspond au calcul du nombre de composantes connexes avec leur diamètre.");
                break;
            case 'p':
                printf("-p AUTEUR1,AUTEUR2 permet de calculer un plus court chemin entre les deux auteurs indiqués.");
                break;
            case 'l':
                printf("-l MOT permet de lister les auteurs qui contiennent le mot donné.");
                break;
            case 'a':
                printf("-a auteur permet d'obtenir les informations d'un auteur (liste des articles).");
                break;
            case 'o':
                printf("-o sauvegarder la structure dans un fichier binaire (indiqué avec une option -o OUTPUT_FILE).");
                break;
            case 'f':
                printf("-f attend un chemain ver un fichier cache.");
                break;
            default:
                printf("Option inconue");
                break;
            }
            break;
        case ':':
            printf(" need VALUE %s\n", optarg);
            break;

        default:
            dfault();
            break;
        }
    }
    for (; optind < argc; optind++)
    { //when some extra arguments are passed
        printf("Given extra arguments: %s\n", argv[optind]);
    }
    return parsed_option;
}

void printAll_option(all_options OwI)
{
    printf("printAll_option:\n\
    auteur_selectioner=%s\n\
    caluleadv=%i\n\
    couple_auteur1=%s,\n\
    couple_auteur2=%s\n\
    distanceN=%i\n\
    output=%s\n\
    search=%s\n",
           OwI.auteur_selectioner, OwI.caluleadv, OwI.couple_auteur[0], OwI.couple_auteur[1], OwI.distanceN, OwI.output, OwI.search);
}

int main(int argc, char *argv[])
{

    init_signal();

    all_options oui = gen_Struct_option(argc, argv);

    graphe_struct_Konqui graph = gen_graph(oui.chemais);
    DEBUG("%s", oui.auteur_selectioner)
    if (*oui.auteur_selectioner)
    {
        ll_list *retour = stringSearch(&graph, searchauteur, oui.auteur_selectioner);
        if (retour->size == 0)
        {
            ERROR("recherche echouer");
        }
        else
        {
            printSearch(retour, oui.verbose);
        }
    }
    DEBUG("%s", oui.lmot)

    if (*oui.lmot)
    {
        ll_list *retour = stringSearch(&graph, searchArticle, oui.lmot);
        if (retour->size == 0)
        {
            ERROR("recherche echouer");
        }
        else
        {
            printSearch(retour, oui.verbose);
        }
    }

    // if (*oui.searchAll)
    // {
    //     ll_list * retoura = stringSearch(&graph,searchauteur,oui.auteur_selectioner);
    //     ll_list * retour = stringSearch(&graph,searchArticle,oui.lmot);
    //     if (retour->size == 0){
    //         ERROR("recherche echouer");
    //     }else{
    //         printSearch(retoura,oui.verbose);
    //         printSearch(retour,oui.verbose);
    //     }
    // }

    if (*oui.searchAll)
    {
        find_all(oui.searchAll, &graph, oui.verbose);
    }

    if (*oui.couple_auteur[0] || *oui.couple_auteur[1])
    {
        if (*oui.couple_auteur[0] && *oui.couple_auteur[1])
        {

            char *aa = ((auteur_struct *)find_auteur(oui.couple_auteur[0], &graph.tab_auteur_struct)->first->value)->nom_auteur;
            char *bb = ((auteur_struct *)find_auteur(oui.couple_auteur[1], &graph.tab_auteur_struct)->first->value)->nom_auteur;
            WARNING("Recherche entre %s et %s", aa, bb)

            djikstrasearch(aa, bb, graph);
        }
        else if (!*oui.couple_auteur[0])
        {
            ERROR("auteur 1 non set")
        }
        else
        {
            ERROR("auteur 2 non set")
        }
    }

    return 0;
}

//INTEGRER TOP  