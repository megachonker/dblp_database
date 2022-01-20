#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>
#include "../header/macro.h"
#include "../header/unwrap.h"
#include "../header/search.h"
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
• -p AUT1;AUT2      plus court chemin auteurs indiqués.\n\
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
    int caluleadv;
    int distanceN;
    char fileInput[100], output[100],auteur_selectioner[100],search[100],lmot[100]; 
    char couple_auteur[2][100];
    struct listeChemain chemais;
}all_options;

all_options gen_Struct_option(int argc, char *argv[]){
    all_options parsed_option = {.lmot="", .auteur_selectioner=""};
    int option;
    if (argc == 1)
    {
        printf("essayer -h pour les option.");
        sdfault();
    }
    

    listeChemain chemains = {
        .XML       = smallorigineXML,
        .DBfiche   = small_fiche_cache,
        .DBauteur  = small_auteur_cache,
        .DBArticle = small_Article_cache
    };

    while((option = getopt(argc, argv, "hc:p:l:a:o:f:n")) != -1){
        switch(option){
            case 'h':
                dfault();
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
            case 'p':
                strcpy(parsed_option.couple_auteur[0],optarg);
                *strchr(parsed_option.couple_auteur[0],';') = '\0';
                strcpy(parsed_option.couple_auteur[1],strchr(optarg,';')+1);
                break;
            case 'f': //here f is used for some file name
                strcpy(parsed_option.fileInput,optarg);
                break;
            case 'o': //here f is used for some file name
                strcpy(parsed_option.fileInput,optarg);
                break;
            case '?': //used for some unknown options
                switch (optopt)
                {
                case 'c':
                    printf("-c correspond au calcul du nombre de composantes connexes avec leur diamètre.");
                    break;
                case 'p':
                    printf("-p AUTEUR1 -p AUTEUR2 permet de calculer un plus court chemin entre les deux auteurs indiqués.");
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

    parsed_option.chemais = chemains;
    return parsed_option;
}


void printAll_option(all_options OwI){
    printf("printAll_option:\n\
    auteur_selectioner=%s\n\
    caluleadv=%i\n\
    couple_auteur1=%s,\n\
    couple_auteur2=%s\n\
    distanceN=%i\n\
    fileInput=%s\n\
    output=%s\n\
    search=%s\n"\
    ,OwI.auteur_selectioner,OwI.caluleadv,OwI.couple_auteur[0],OwI.couple_auteur[1],OwI.distanceN,OwI.fileInput,OwI.output,OwI.search);
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
            printSearch(retour,verbeux);
        }
    }
    DEBUG("%s",oui.lmot)

    if (*oui.lmot)
    {
        ll_list * retour = stringSearch(&graph,searchArticle,oui.auteur_selectioner);
        if (retour->size == 0){
            ERROR("recherche echouer");
        }else{
            printSearch(retour,verbeux);
        }
    }
    
    

    return 0;
}