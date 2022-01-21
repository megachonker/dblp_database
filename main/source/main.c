
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>
#include "../header/macro.h"
#include "../header/unwrap.h"
#include "../header/search.h"
#include "../header/Dijkstra.h"
#include <stdarg.h>


/*! \mainpage My Personal Index Page
 *
 * \section Résumé général
 * **a compléter avec ce que t'as fais**
 * ...
 * ...
 * ...
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
typedef struct listeChemain
{
    char * XML;
    char * DBfiche;
    char * DBauteur;
    char * DBArticle;
}listeChemain;

graphe_struct_Konqui gen_graph(listeChemain chemains){
    
    FILE * DBxml =      fopen(chemains.XML,"r");
    FILE * DBinverse =  fopen(chemains.DBfiche,"r");
    FILE * DBauteur =   fopen(chemains.DBauteur,"r");
    FILE * DBarticle =  fopen(chemains.DBArticle,"r");
    
    exitIfNull(DBxml,    "INPUT PAS CHEMAIN %s",chemains.XML)
    exitIfNull(DBinverse,"INPUT PAS CHEMAIN %s",chemains.DBfiche)
    exitIfNull(DBauteur, "INPUT PAS CHEMAIN %s",chemains.DBauteur)
    exitIfNull(DBarticle,"INPUT PAS CHEMAIN %s",chemains.DBArticle)
    
    fseek(DBxml,    0, SEEK_END);
    fseek(DBinverse,0, SEEK_END);
    fseek(DBauteur, 0, SEEK_END);
    fseek(DBarticle,0, SEEK_END);

    if (!ftell(DBxml) || !ftell(DBinverse) || !ftell(DBauteur) || !ftell(DBarticle))
    {
        exitIfNull(0,"Un fichier de db est vide")
    }
    
    fseek(DBxml,    0, SEEK_SET);
    fseek(DBinverse,0, SEEK_SET);
    fseek(DBauteur, 0, SEEK_SET);
    fseek(DBarticle,0, SEEK_SET);


    graphe_struct_Konqui graph = deserialise_Graph(DBinverse,DBauteur,DBarticle);
    if (!graph.tab_Article_struct.nombre_Article||!graph.tab_auteur_struct.nombre_auteur||!graph.tableaux_de_fiche.taille)
    {
        exitIfNull(0,"Une des structure est vide");
    }
    return graph;
}

void dfault(){
    printf("\
• -c                calculer les composantes connexes & diamètre.\n\
• -p AUT1,AUT2      plus court chemin auteurs indiqués.\n\
• -l MOT            Lister les auteurs qui contiennent le mot donné.\n\
• -a auteur         Fnformations d'un auteur (liste des articles).\n\
• -a auteur -n N    Liste les co-auteurs à distance N (ou moins) d'un auteur.\n\
• -f INPUT          cache d\'entrée.\n\
• -o OUTPUT         Sauvegarder la structure dans un fichier binaire (indiqué avec une option -o OUTPUT_FILE)\n");
}

void sdfault(){
    printf("\n -c -p AUT1 AUT2 -l MOT -a auteur -a auteur -n N -f INPUT -o OUTPUT");
}

typedef struct all_options
{
    int caluleadv, distanceN, verbose;
    char output[100],auteur_selectioner[100],search[100],lmot[100],searchAll[100]; 
    char couple_auteur[2][100];
    struct listeChemain chemais;
}all_options;

listeChemain chose_path(short choix){

    listeChemain chemains[3];

    listeChemain smal = {
        .XML       = smallorigineXML,
        .DBfiche   = small_fiche_cache,
        .DBauteur  = small_auteur_cache,
        .DBArticle = small_Article_cache
    };

    listeChemain ful = {
        .XML       = origineXML,
        .DBfiche   = cache_fiche,
        .DBauteur  = auteur_cache,
        .DBArticle = Article_cache
    };

    listeChemain cust = {
        .XML       = customXML,
        .DBfiche   = custom_fiche_cache,
        .DBauteur  = custom_auteur_cache,
        .DBArticle = custom_Article_cache
    };

    chemains[small] = smal;
    chemains[full] = ful;
    chemains[custom] = cust;

    return chemains[choix];
}

void find_all(char * search,graphe_struct_Konqui * graph,int verbose){
    ll_list * retoura = stringSearch(graph,searchauteur,search);
    ll_list * retour = stringSearch(graph,searchArticle,search);
    if (retoura->size == 0){
        ERROR("recherche auteur 0");
    }else{
        printSearch(retoura,verbose);
    }
    if (retour->size == 0){
        ERROR("recherche Article 0");
    }else{
        printSearch(retour,verbose);
    }
}

void chose_db(char * compstr, listeChemain * chemain){
    if(NULL){
    STR("full")
        *chemain = chose_path(full);
    STR("custom")
        *chemain = chose_path(custom);
    STR("small")
        *chemain = chose_path(small);}
}
void interactive(){
    char ligne[BALISESIZE];
    char *arg=ligne;
    listeChemain chem = chose_path(small);
    graphe_struct_Konqui graph;
    int verb = silence;
    while (fgets(ligne,BALISESIZE,stdin)){
        char * pts = strchr(ligne,' ');
        *strchr(ligne,'\n') = '\0';
        if (pts){
            *pts='\0';
            if (pts+1)
            {
                arg = pts+1;
            }else{            *arg = '\0';}
        }else{
            *arg = '\0';
        }

        DEBUG("APRES[%s] et [%s] ",ligne,arg);

        char * compstr = ligne;if(NULL){
        STR("exit")
            exit(0);
        STR("help")
            dfault();
        STR("file")
            chose_db(arg,&chem);
        STR("compute")
            graph = gen_graph(chem);
        STR("v")
            if (verb == silence)
            {
                INFO("verbeux")
                verb = verbeux;
            }else if(verb == verbeux){
                INFO("VraimentTropVerbeux")
                verb = VraimentTropVerbeux;
            }else{
                INFO("silence")
                verb = silence;
            }
        STR("full")
            find_all(arg,&graph,verb);
        }
    } 
}


void djikstrasearch(char * a,char * b,graphe_struct_Konqui graph){
    graphe_struct_Katie graphe_Katie = faire_graphe_ptr_auteur(graph);
    plus_court_chemin_struct* plus_court_chemin_ptr= do_Dijkstra(graphe_Katie, a, b);
    if(plus_court_chemin_ptr!= NULL)
    {
        print_chemins_auteur_et_Article(plus_court_chemin_ptr);

    }else{
        ERROR("PAS DE CHEMIN")
    }
    free_Dijkstra(graphe_Katie,plus_court_chemin_ptr);
}

all_options gen_Struct_option(int argc, char *argv[]){
    all_options parsed_option = {.lmot="", .auteur_selectioner="",.searchAll="",.couple_auteur[0]="",.couple_auteur[1]=""};
    int option;
    if (argc == 1)
    {
        printf("essayer -h pour les option.");
        sdfault();
    }
    parsed_option.chemais = chose_path(small);
    parsed_option.verbose = silence;
    while((option = getopt(argc, argv, "ihvVc:p:l:a:A:o:f:n")) != -1){
        switch(option){
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
                strcpy(parsed_option.lmot,optarg);
                break;
            case 'c':
                parsed_option.caluleadv = 1;
                break;
            case 'a':
                strcpy(parsed_option.auteur_selectioner,optarg);
                break;
            case 'A'://alll
                strcpy(parsed_option.searchAll,optarg);
                break;
            case 'p':
                strcpy(parsed_option.couple_auteur[0],optarg);
                *strchr(parsed_option.couple_auteur[0],',') = '\0';
                strcpy(parsed_option.couple_auteur[1],strchr(optarg,',')+1);
                break;
            case 'f':
                chose_db(optarg,&parsed_option.chemais);
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
                printf(" need VALUE %s\n",optarg);
                break;

            default:
                dfault();
                break;
        }
    }
    for(; optind < argc; optind++){ //when some extra arguments are passed
        printf("Given extra arguments: %s\n", argv[optind]);
    }
    return parsed_option;
}


void printAll_option(all_options OwI){
    printf("printAll_option:\n\
    auteur_selectioner=%s\n\
    caluleadv=%i\n\
    couple_auteur1=%s,\n\
    couple_auteur2=%s\n\
    distanceN=%i\n\
    output=%s\n\
    search=%s\n"\
    ,OwI.auteur_selectioner,OwI.caluleadv,OwI.couple_auteur[0],OwI.couple_auteur[1],OwI.distanceN,OwI.output,OwI.search);
}


int main(int argc, char *argv[]) {
    all_options oui = gen_Struct_option(argc,argv);
    
    graphe_struct_Konqui graph = gen_graph(oui.chemais);
    DEBUG("%s",oui.auteur_selectioner)
    if (*oui.auteur_selectioner)
    {
        ll_list * retour = stringSearch(&graph,searchauteur,oui.auteur_selectioner);
        if (retour->size == 0){
            ERROR("recherche echouer");
        }else{
            printSearch(retour,oui.verbose);
        }
    }
    DEBUG("%s",oui.lmot)

    if (*oui.lmot)
    {
        ll_list * retour = stringSearch(&graph,searchArticle,oui.lmot);
        if (retour->size == 0){
            ERROR("recherche echouer");
        }else{
            printSearch(retour,oui.verbose);
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
        find_all(oui.searchAll,&graph,oui.verbose);
    }

    if (*oui.couple_auteur[0]||*oui.couple_auteur[1])
    {
        if (*oui.couple_auteur[0]&&*oui.couple_auteur[1])
        {
            
            char * aa = ((auteur_struct*)find_auteur(oui.couple_auteur[0], &graph.tab_auteur_struct)->first->value)->nom_auteur;
            char * bb = ((auteur_struct*)find_auteur(oui.couple_auteur[1], &graph.tab_auteur_struct)->first->value)->nom_auteur;
            WARNING("Recherche entre %s et %s",aa,bb)

            djikstrasearch(aa,bb,graph);
        }else if (!*oui.couple_auteur[0])
        {
            ERROR("auteur 1 non set")
        }else{
            ERROR("auteur 2 non set")
        }
    }
    
    
    return 0;
}


