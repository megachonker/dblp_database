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

/** \mainpage My Personal Index Page
 * \section fiche_gene Génération fiche
 * les pointeur fiche_minimale sont contenue dans tableaux_fiche et auteur_struct Article_struct
 * \subsection parse_xml Parsing XML
 *  le parsing ce fait en partant du principe qu'il y a **une paire de balise par ligne**
 *  pour le parsing on ne s'interresse juste au noms de l'article est a ces auteur (pas assez de temps pour traiter les date)
 *  on remplie la structure fiche_minimale avec les information ainsie que  fiche_minimale.ADDR qui est l'ordre de création car plus tard fiche_minimale sera indépandant de la structure 
 * tableaux_fiche dans laquelle elle est contenue
 * \subsection serialisation_xml Sérialisation XML
 * pour la sérialisation on va utiliser des fwread et fwrite qui sont simplifier avec la macro writestrfile() et readstrfile()
 * a 
 * \section generation_auteur Génération auteur
 * ce déroule dans unwrap.c en désérialisant les fiche on économise le parsage. pour générée tab_auteur_struct qui contien auteur_struct il va falloir dans un premier temps trier tableaux_fiche
 * on va ensuite déplier le tableau de fiche pour crée une liste des paire auteur : article
 * cette liste sera trier par noms d'auteur de magnierre a récupérée tout les article pour chaque auteur
 * 
 * \section generation_article Génération Article
 * générée les article est facile mais il va faloire faire le lien avec les auteur pour ce faire a la création des Article (apres avoir déplier les auteur)
 * a chaque article crée a l'ajout des auteur on va ajouter l'article parent a l'auteur cible
 * 
 * 
 * 
 * \section Résumé général graphe_struct_Konqui
 * le but principal de unwrap.c est de fournire graphe_struct_Konqui qui fournis tab_auteur_struct tab_Article_struct tableaux_fiche
 * Une fois que des structures auteur_struct et Article_struct ont été générées et initialisées pour chaque auteur/Article de la base de donnée,
 * elles sont stockées dans des tableaux dans la structure graphe_struct_Konqui.
 * 
 * Ensuite, un tableau de pointeur vers les auteurs_struct est crée (fonctions_garphe.c). 
 * Ce tableau est stocké dans la structure graphe_Katie.
 * Les attributs des auteur_struct utiles à Dijkstra sont alors initialisés (comme par exemple la distance à l'auteur_depart, initialisé à -1).
 * 
 * Il ne reste plus qu'à appliquer la fonction do_Dijkstra (Dijkstra.c) au graphe_Katie, avec 2 noms d'auteur de la base de donnée.
 * Pour cela, on relache les arrêtes de tous les auteurs rangés dans un tableau indiquant les auteurs à traiter à l'étape courante du parcours en largeur.
 * (Ce tableau s'appelant pile_courante)
 * En ce faisant, on enregistre les auteurs à traiter à l'étape suivante dans un autre tableau (pile_suivante).
 * De même, on initialise l'attribut auteur_predecesseur et Article_predecesseur de l'auteur en cours de traitement.
 * A la fin de l'étape courante (une couche du parcours en largeur) on remplace le contenu de pile_courante par celui de pile_suivante et on vide la pile_suivante.
 * 
 * En répétant ce procédé jusqu'a trouver l'auteur_destination ou avoir parcouru toute la composante connexe,
 * il est possible d'enregistrer le plus court chemin dans un tableau en partant de l'auteur_destination et en remontant la chaine des prédecesseurs.
 * 
 * 
 * 
 * 
 * 
 * 
 *
 * \section install_sec Installation
 * \sa <gen_graph>"()"
 * 
 * gen_graph()
 * 
 *  dans listeChemain on a les chemain
 * \subsection step1 Step 1: Opening the box
 *
 * etc...
 */

// #include <stdarg.h>


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