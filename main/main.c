#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>
/*
• l'option -c pourra correspondre au calcul du nombre de composantes connexes avec leur diamètre.
• l'option -p AUTEUR1 -p AUTEUR2 permettra de calculer un plus court chemin entre les deux auteurs indiqués.
• l'option -l MOT permettra de lister les auteurs qui contiennent le mot donné.
• l-option -a AUTEUR permet d'obtenir les informations d'un auteur (liste des articles).
• l-option -a AUTEUR -n N permet d'obtenir les co-auteurs à distance N (ou moins) d'un auteur.
• l-option -o sauvegarder la structure dans un fichier binaire (indiqué avec une option -o OUTPUT_FILE)
*/

void dfault(){
    printf("\
• -c                calculer les composantes connexes & diamètre.\n\
• -p AUT1 AUT2      plus court chemin auteurs indiqués.\n\
• -l MOT            Lister les auteurs qui contiennent le mot donné.\n\
• -a AUTEUR         Fnformations d'un auteur (liste des articles).\n\
• -a AUTEUR -n N    Liste les co-auteurs à distance N (ou moins) d'un auteur.\n\
• -f INPUT          cache d\'entrée.\n\
• -o OUTPUT         Sauvegarder la structure dans un fichier binaire (indiqué avec une option -o OUTPUT_FILE)\n");
}

void sdfault(){
    printf("\n -c -p AUT1 AUT2 -l MOT -a AUTEUR -a AUTEUR -n N -f INPUT -o OUTPUT");
}

typedef struct all_options
{
    int caluleadv;
    int distanceN;
    char fileInput[100], output[100],auteur_selectioner[100],search[100]; 
    char couple_auteur[2][100];
}all_options;

all_options gen_Struct_option(int argc, char *argv[]){
    all_options parsed_option;
    int option;
    if (argc == 1)
    {
        printf("essayer -h pour les option.");
        sdfault();
    }
    
    while((option = getopt(argc, argv, "hc:p:l:a:o:f:n")) != -1){
        switch(option){
            case 'h':
                dfault();
                break;
            case 'n':
                parsed_option.distanceN = optarg;
                break;
            case 'c':
                parsed_option.caluleadv = 1;
                break;
            case 'a':
                strcpy(parsed_option.auteur_selectioner,optarg);
                break;
            case 'p':
                parsed_option.couple_auteur[0];
                parsed_option.couple_auteur[0];
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
                    printf("-a AUTEUR permet d'obtenir les informations d'un auteur (liste des articles).");
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
            case ':':
                printf(" need VALUE \n",optarg);
                break;

            default:
                dfault();
                break;
        }
    }
    for(; optind < argc; optind++){ //when some extra arguments are passed
        printf("Given extra arguments: %s\n", argv[optind]);
    }
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


main(int argc, char *argv[]) {
    all_options oui = gen_Struct_option(argc,argv);
    return 0;
}