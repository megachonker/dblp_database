#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parsing.h"

#include "macro.h"

//prend du temps l'utiliser directement ?
void enlever_retour_a_la_ligne(char * ligne){
    ligne[strcspn(ligne, "\n")]=0;    
}

//renomer
void printM_titre(fiche_minimale OwO){
    printf("titre:    %s",OwO.titre);
}

//renomer
void printM_liste_auteur(fiche_minimale UwU){
    printf("auteurs:\n\t");
    for (int i = 0; i < UwU.nombre_auteur; i++)
    {
        printf("%s",UwU.liste_auteur[i]);
        if (i+1<UwU.nombre_auteur)
            printf("\n\t");
    }
    printf("\n");
}

//renomer
void printM(fiche_minimale OwU){
    printM_titre(OwU);
    printf("\n");
    printM_liste_auteur(OwU);   
}

//renomer
void printTabmeaux(tableaux_fiche UwO){

    for (int i = 0; i < UwO.taille; i++)
    {
        printM(*(UwO.fiche[i]));
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
        start[diff] = '\0';
        char * out = strdup(start);
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
    addrListeauteur = realloc(mafiche->liste_auteur,sizeof(fiche_minimale)*(mafiche->nombre_auteur+1));

    exitIfNull(addrListeauteur,"appendAuteurM: allocation imposible")

    if (mafiche->liste_auteur != addrListeauteur)//plus opti que d'assigner dirrectment ?
        mafiche->liste_auteur = addrListeauteur;

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
void appendTabmeaux(tableaux_fiche * table, fiche_minimale * a_ajouter){
    fiche_minimale ** addrListFiche = NULL;
    addrListFiche = realloc(table->fiche,sizeof(fiche_minimale*)*(table->taille+1));
    exitIfNull(addrListFiche,"appendTabmeaux: allocation imposible")

    if (table->fiche != addrListFiche)  //cout du check de cette fonction ?
        table->fiche = addrListFiche;

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
    for (int i = 0; i < tableaux_allfiche->taille; i++)
    {
        progressbar(i,tableaux_allfiche->taille);
        tableaux_allfiche->fiche[i]->ADDR = i;
    }
}

//renomer les variable
/**
 * @brief fonction comparer les fiches utilser par sortlist
 * 
 * @param [in] maficheA fiche a comparer
 * @param [in] maficheB fiche a comparer
 * @return int indice utilser par quicksort
 */
static int cmptabfiche(const void * maficheA,const void * maficheB){
    //MAGIE NOIIIIIIIIIIIIIIIIIIIIIREEE
    struct fiche_minimale* maficheAA = *(struct fiche_minimale**) maficheA;
    struct fiche_minimale* maficheBB = *(struct fiche_minimale**) maficheB;
    // DEBUG => printf("%s <=> %s\n",maficheAA->titre,maficheAA->titre);
    return strcmp(maficheAA->titre,maficheBB->titre);
}

void sortlist(tableaux_fiche * mesfiche ){
    DEBUG("trie des liste parsing")
    qsort(mesfiche->fiche,mesfiche->taille,sizeof(mesfiche->fiche),cmptabfiche);   
}

//on retourne pas l'original mais une copie ? <= pourquoi ?? ?
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
tableaux_fiche parse(FILE * inputDB){
    INFO("début du parsing:");
    char ligne[BALISESIZE];

    //génère le tablaux
    tableaux_fiche tableaux_allfiche;// DOIT ETRE DUPLIQUER A LA SORTIE ???
    tableaux_allfiche.taille = 0;
    tableaux_allfiche.fiche = NULL;

    //premierre fiche
    fiche_minimale * fichelocalM = NULL;
    fichelocalM = calloc(1,sizeof(fiche_minimale)); //initialiser a 0 pas opti ?
    exitIfNull(fichelocalM,"parse: imposible d'alouer crée fichelocalM");
    fichelocalM->ADDR = 0;
    fichelocalM->nombre_auteur = 0;

    //chargement
    while (fgets(ligne,BALISESIZE,inputDB))// <================ prend masse temps le remplacer par un buffer ? (simple ici a faire)
    {
        int flagt = 0;
        exitIfNull(fichelocalM,"création de la zone de mémoir pour ficheloca1m compromis calloc")

        //passer une liste des argument interresant est recherer ??
        char * tmpauteur = getanchor("author",ligne);
        if (tmpauteur)
        {
            appendAuteurM(fichelocalM,tmpauteur);
        }else{
            fichelocalM->titre = getanchor("title",ligne);
            if (fichelocalM->titre)
            {
                flagt = 1;
            }
            // else{
            //     getanchor("date",ligne);
            // }
        }
        // DATE!
        //PASBEAUX
        if (flagt == 1)
        {
            //DEBUG
            // printM_titre(*fichelocalM);
            // printM_liste_auteur(*fichelocalM);

            //moche ajouter l'exclusion Preface. Editorial. (faire une blackliste a importer ? voir qand trie)
            if (strcmp(fichelocalM->titre,"Home Page")!=0 
            && fichelocalM->nombre_auteur != 0 
            && strcmp(fichelocalM->titre,"")!=0)//ces con mais fichelocalM->titre ou fichelocalM->titre != '' devrais fonctioner..
            {
                //DEGUG ajout de 
                // printM_titre(*fichelocalM);
                appendTabmeaux(&tableaux_allfiche,fichelocalM);
            }

            fichelocalM = calloc(1,sizeof(fiche_minimale));//maloc ?
            fichelocalM->nombre_auteur = 0;
        }        
    }
    //WARNING
    // printTabmeaux(tableaux_allfiche);

    INFO("PARSE OK\ndébut du trie:");
    sortlist(&tableaux_allfiche);
    INFO("Trie OK\ndébut de genereation des id:");
    gen_id_fiche(&tableaux_allfiche);
    INFO("Id générée!");
    return tableaux_allfiche;
}


//utiliser l'addresse pour pas copier ?
/**
 * @brief Sérialisation du XML
 * 
 *  ajouter un truc pour la validitée checksum du programe qui la compiler ?
 * 
 * @param [in] mastertab structure tableaux_fiche a sérialiser
 * @param [out] output    fichier de sortie 
 */
void serialize(const tableaux_fiche mastertab, FILE * output){
    //une sorte de header du fichier ici !
        //taille de la structure
        //validitée
    for (int i = 0; i < mastertab.taille; i++)
    {
        progressbar(i,mastertab.taille);
        fprintf(output,"%s\n",mastertab.fiche[i]->titre);
        fprintf(output,"%i\n",mastertab.fiche[i]->nombre_auteur); //fusioner les 2 en une écritur ?
        for (int  u = 0; u < mastertab.fiche[i]->nombre_auteur; u++)//tout concaténée
        {
            progressbar(i,mastertab.taille);
            fprintf(output,"%s\n",mastertab.fiche[i]->liste_auteur[u]);
        }
        //une soeule écriture ici
    }
}

//grater en fesant une structure avec des dico est des referancement < ?

/**
 * @brief génère tableaux_fiche depuis un cache générée par serialize 
 * 
 * test avec des maloc 
 * 
 * @param [in] input générée par serialize 
 * @return pointeur ver tableaux_fiche 
 */
tableaux_fiche * deserialisation(FILE * input){
    fseek(input,0,SEEK_END);
    int nombreligne = ftell(input);
    fseek(input,0,SEEK_SET);


    //INFO début de la désérialisation
    char ligne[BALISESIZE];

    //valide read du checksum

    //read tailletotal

    tableaux_fiche * tableaux_allfiche = malloc(sizeof(tableaux_fiche));
    exitIfNull(tableaux_allfiche,"deserialisation:imposible d'alouer le tableaux de toute les fiche\n")
    tableaux_allfiche->taille = 0;//<=  = tailletotal
    //AFAIRE un soeule maloc tableaux_allfiche->taille*sizeof !!
    tableaux_allfiche->fiche = NULL;


    fiche_minimale * fichelocalM = calloc(1,sizeof(fiche_minimale));
    fichelocalM->nombre_auteur = 0;


    //check la validitée ?

    int indice = 0;
    while (fgets(ligne,BALISESIZE,input))                           //<============= un soeul gros buffer ?
    {
        progressbar(ftell(input),nombreligne);
        //progesse bar?
        if (feof(input))
        {
            fprintf(stderr,"fin fichier deserialisation\n");
            exit(3);//jamais etait triguerre donc pas utile ?
        }

        enlever_retour_a_la_ligne(ligne);
        fichelocalM->ADDR = indice;     //<=== explicitée
        fichelocalM->titre = strdup(ligne);

        fgets(ligne,BALISESIZE,input);
        enlever_retour_a_la_ligne(ligne);
        int nbauteur = atoi(ligne);
        for (int i = 0; i < nbauteur; i++)
        {
            fgets(ligne,BALISESIZE,input);
            enlever_retour_a_la_ligne(ligne);
            appendAuteurM(fichelocalM,strdup(ligne));// ICI on doit réloc pour iren
        }
        appendTabmeaux(tableaux_allfiche,fichelocalM);
        fichelocalM = calloc(1,sizeof(fiche_minimale));
        exitIfNull(fichelocalM, "new calloc null")
        fichelocalM->nombre_auteur = 0;
        indice++;
    }

    DEBUG("Deseraialisation %d FAIRE UN MALOC",indice);
    return tableaux_allfiche;
}

//renomer
/**
 * @brief free tableaux_fiche
 * 
 * @param DEGAGE 
 */
void parsing_free(tableaux_fiche * DEGAGE){
    INFO("Free parsing")
    for (int i = 0; i < DEGAGE->taille; i++)
    {
        progressbar(i,DEGAGE->taille);
        free(DEGAGE->fiche[i]->titre);
        for (int u = 0; u < DEGAGE->fiche[i]->nombre_auteur; u++)
        {
            free(DEGAGE->fiche[i]->liste_auteur[u]);
        }
        free(DEGAGE->fiche[i]);
    }
    free(DEGAGE);
}