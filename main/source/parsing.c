#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../header/parsing.h"

#include "../header/macro.h"

void print_titre_fiche_minimal(fiche_minimale OwO){
    printf("titre:    %s",OwO.titre);
}

void print_liste_auteur_fiche_minimal(fiche_minimale UwU){
    printf("auteurs:\n\t");
    for (int i = 0; i < UwU.nombre_auteur; i++)
    {
        printf("%s",UwU.liste_auteur[i]);
        if (i+1<UwU.nombre_auteur)
            printf("\n\t");
    }
    printf("\n");
}

void print_fiche_minimal(fiche_minimale OwU){
    print_titre_fiche_minimal(OwU);
    printf("\n");
    print_liste_auteur_fiche_minimal(OwU);   
}

void printTabmeaux(tableaux_fiche UwO){

    for (int i = 0; i < UwO.taille; i++)
    {
        print_fiche_minimal(UwO.fiche[i]);
    }
}

/**
 * @brief extrait un string entre les balise
 * 
 * @param [in] recherche noms de balise  
 * @param [in] ligne dans l'aquellle rechercher la balise 
 * @return char* renvoit l'élément entre les balise
 */
char * getanchor(char * recherche, char * ligne){
    //on crée la balise a chercher ATENTION tailel de la baslise limiter a 18caractere
    char critaire[20] = "<";
    strcat(critaire,recherche);
    //si la balise existe
    if(strstr(ligne,critaire)){ //slow ?
        //on chercher quand la balise prend fin
        char * start = strchr(ligne,'>');
        //on ce déplace apres l'acolade fermante
        start++;
        //vérifie que nous ne somme pas au 2ème >
        if (*start=='\n') //Peut etre omis si ralentis beaucoup
        {
            fprintf(stderr,"que une balise fermantge dans la ligne\n");
            return NULL;
        }
        //on chercher la prochaine acolade ouvrante (donc la fin de la balise)
        int diff = strcspn(start,"<");
        if (diff == 0)
        {
            return NULL;
        }
        start[diff] = '\0';
        char * out = strdup(start);//<ça fait des duplication
        exitIfNull(out,"getchar: stdrup imposible");
        return out;
    }
    return NULL;
}

//renomer IMPORTANT
/**
 * @brief ajoute un nouvel auteur a ma fiche_minimale
 * 
 * fonction clef utiliser des buffer pour diminuer les réaloc ?
 * 
 * @param [in,out] mafiche chiche a modifier
 * @param [in] nomsauteur addrese de la chaine de caractere
 */
void appendAuteurM(fiche_minimale * mafiche,char * nomsauteur){
    char ** addrListeauteur = NULL;                                                    
    addrListeauteur = reallocarray(mafiche->liste_auteur,(mafiche->nombre_auteur+1),sizeof(char*));//MALOC

    exitIfNull(addrListeauteur,"appendAuteurM: allocation imposible")

    if (mafiche->liste_auteur != addrListeauteur){//plus opti que d'assigner dirrectment ?
        YOLO("%p VS %p",mafiche->liste_auteur,addrListeauteur);     

        mafiche->liste_auteur = addrListeauteur;
    }

    mafiche->liste_auteur[mafiche->nombre_auteur] = nomsauteur;
    mafiche->nombre_auteur++;
}

/**
 * @brief Ajoute une nouvelle fiche au tableaux
 * 
 * attention réaloc ?
 * 
 * @param [in,out] table table des fiche 
 * @param [in] a_ajouter nouvelle fiche
 */
void appendTabmeaux(tableaux_fiche * table, fiche_minimale a_ajouter){
    table->fiche = realloc(table->fiche,sizeof(fiche_minimale)*(table->taille+1));//MLOC
    exitIfNull(table->fiche,"appendTabmeaux: allocation imposible")
    table->fiche[table->taille] = a_ajouter;
    table->taille++;   
}

/**
 * @brief initialise le champ ADDR de tableaux_fiche
 * 
 * permet d'aceder a une fiche avec ADDR comme un inded // MALDI
 * l'id est l'indice pour acceder a la fiche dpuis la structure  tableaux_fiche
 * 
 * @param [in,out] tableaux_allfiche 
 */
void gen_id_fiche(tableaux_fiche * tableaux_allfiche){
    DEBUG("début de genereation des id:");
    for (int i = 0; i < tableaux_allfiche->taille; i++)
    {
        PROGRESSBAR(i,tableaux_allfiche->taille);
        tableaux_allfiche->fiche[i].ADDR = i;
        tableaux_allfiche->nbAuteurXarticle+=tableaux_allfiche->fiche[i].nombre_auteur;
    }
}

/**
 * @brief fonction comparer les fiches utilser par sortlist
 * 
 * @param [in] maficheA fiche a comparer
 * @param [in] maficheB fiche a comparer
 * @return int indice utilser par quicksort
 */
static int cmptabfiche(const void * maficheA,const void * maficheB){
    return strcmp(((fiche_minimale*)maficheA)->titre,((fiche_minimale*)maficheB)->titre);
}

/**
 * @brief quick sort du tableaux de fiche par titre
 * 
 * @param mesfiche 
 */
void sortlist(tableaux_fiche * mesfiche ){
    DEBUG("trie des liste parsing")
    qsort(mesfiche->fiche,mesfiche->taille,sizeof(fiche_minimale),cmptabfiche);   
}

/**
 * @brief Parse un fichier XML DBLP
 * 
 *  Va générée un tableaux_fiche ainsie que ces fiche_minimale
 * -    Article
 * -    auteur
 *  
 *  mais aussi
 *  - génère ADDR de chaque fiche
 *  - trie les fiche
 *  
 * ## Doit pouvoir utiliser les date !
 * 
 * @param inputDB 
 * @return tableaux_fiche 
 */
tableaux_fiche parse(FILE * inputDB){ /// a besoin detre un pointeur pour le free ?? ? genr maloc
    INFO("début du parsing:");
    char ligne[BALISESIZE];

    PROGRESSBAR_DECL(inputDB)

    //génère le tablaux
    tableaux_fiche tableaux_allfiche;
    tableaux_allfiche.taille = 0;
    tableaux_allfiche.fiche = NULL;
    tableaux_allfiche.nbAuteurXarticle = 0;

    //premierre fiche
    fiche_minimale fichelocalM;
    fichelocalM.ADDR = 0;
    fichelocalM.nombre_auteur = 0;
    fichelocalM.titre = NULL;
    fichelocalM.liste_auteur = NULL;

    //prend masse temps le remplacer par un buffer ? (simple ici a faire)
    while (fgets(ligne,BALISESIZE,inputDB))
    {

        PROGRESSBAR_FILE_PRINT(inputDB)

        int flagt = 0;
        //passer une liste des argument interresant est recherer ??
        // DEBUG("get auteur %s",ligne)
        char * tmpauteur = getanchor("author",ligne);
        if (tmpauteur)
        {
            appendAuteurM(&fichelocalM,tmpauteur);
        }else{
            fichelocalM.titre = getanchor("title",ligne);
            if (fichelocalM.titre)
            {
                flagt = 1;
            }
            // else{
            //     // getanchor("date",ligne);
            // }
        }
        // DATE!
        if (flagt == 1)
        {
            //moche ajouter l'exclusion Preface. Editorial. (faire une blackliste a importer ? voir qand trie)
            if (strcmp(fichelocalM.titre,"Home Page")!=0 
            && fichelocalM.nombre_auteur != 0 
            && strcmp(fichelocalM.titre,"")!=0)//ces con mais fichelocalM.titre ou fichelocalM->titre != '' devrais fonctioner..
            {
                //DEGUG ajout de 
                // print_titre_fiche_minimal(*fichelocalM);
                appendTabmeaux(&tableaux_allfiche,fichelocalM);
            }else{
                free_fiche_minimale(fichelocalM);
            }
            fichelocalM.ADDR = 0;
            fichelocalM.nombre_auteur = 0;
            fichelocalM.titre = NULL;
            fichelocalM.liste_auteur = NULL;
        }        
    }
    sortlist(&tableaux_allfiche);
    gen_id_fiche(&tableaux_allfiche);
    return tableaux_allfiche;
}

/**
 * @brief Sérialisation du XML
 * 
 *  ajouter un truc pour la validitée checksum du programe qui la compiler ?
 * 
 * @param [in] mastertab structure tableaux_fiche a sérialiser
 * @param [out] output    fichier de sortie 
 */
void serialisation_tableaux_fiche(const tableaux_fiche mastertab, FILE * output){
    INFO("\tSerialisation des fiche")
    fwrite(&mastertab.taille,sizeof(int),1,output);
    DEBUG("Il y a %d fiche",mastertab.taille)
    for (int i = 0; i < mastertab.taille; i++)
    {
        PROGRESSBAR(i,mastertab.taille);
        YOLO("Titre: %s",mastertab.fiche[i].titre)
        writestrfile(mastertab.fiche[i].titre,output);
        fwrite(&mastertab.fiche[i].nombre_auteur,sizeof(int),1,output);
        YOLO("nombre auteur: %d",mastertab.fiche[i].nombre_auteur)
        for (int  u = 0; u < mastertab.fiche[i].nombre_auteur; u++)//tout concaténée
        {
            writestrfile(mastertab.fiche[i].liste_auteur[u],output);
        }
    }
}

//grater en fesant une structure avec des dico est des referancement < ?

/**
 * @brief génère tableaux_fiche depuis un cache générée par serialisation_tableaux_fiche 
 * 
 * test avec des maloc 
 * 
 * @param [in] input générée par serialisation_tableaux_fiche 
 * @return pointeur ver tableaux_fiche 
 */
tableaux_fiche deserialisation_tableaux_fiche(FILE * input){
    INFO("\tDeserialisation tableaux fiche DBXML")

    tableaux_fiche tableaux_allfiche;
    tableaux_allfiche.nbAuteurXarticle = 0;
    fread(&tableaux_allfiche.taille,sizeof(int),1,input);//verifier?
    tableaux_allfiche.fiche = NULL;
    DEBUG("il y a %d fiche a calloc",tableaux_allfiche.taille)

    tableaux_allfiche.fiche = calloc(tableaux_allfiche.taille,sizeof(fiche_minimale));
    exitIfNull(tableaux_allfiche.fiche,"calloc des fiche imposible")

    for (int UwU = 0; UwU < tableaux_allfiche.taille; UwU++)
    {
        PROGRESSBAR(UwU,tableaux_allfiche.taille)
        tableaux_allfiche.fiche[UwU].ADDR = UwU;
        tableaux_allfiche.fiche[UwU].titre =readstrfile(input);
        fread(&tableaux_allfiche.fiche[UwU].nombre_auteur,sizeof(int),1,input);
        YOLO("il y a %d auteur",tableaux_allfiche.fiche[UwU].nombre_auteur)
        tableaux_allfiche.fiche[UwU].liste_auteur = calloc(tableaux_allfiche.fiche[UwU].nombre_auteur,sizeof(char *));
        exitIfNull(tableaux_allfiche.fiche[UwU].liste_auteur,"calloc echouer")
        for (int i = 0; i < tableaux_allfiche.fiche[UwU].nombre_auteur; i++)
        {
            tableaux_allfiche.fiche[UwU].liste_auteur[i] = readstrfile(input);
            tableaux_allfiche.nbAuteurXarticle++;
        }
    }
    return tableaux_allfiche;
}


/**
 * @brief free tout char auteur, est la fiche
 * 
 * @param fiche 
 */
void free_fiche_minimale(fiche_minimale fiche){
    free(fiche.titre);
    for (int i = 0; i < fiche.nombre_auteur; i++)
    {
        free(fiche.liste_auteur[i]);
    }
    
    free(fiche.liste_auteur);
}

/**
 * @brief free tableaux_fiche
 * 
 * @param DEGAGE 
 */
void free_tab_fiche(tableaux_fiche DEGAGE){
    INFO("Free parsing")
    for (int i = 0; i < DEGAGE.taille; i++)
    {
        PROGRESSBAR(i,DEGAGE.taille);
        free_fiche_minimale(DEGAGE.fiche[i]);
    }
    free(DEGAGE.fiche);
}

