#include <stdio.h>
#include <stdlib.h>
#include "unwrap.h"

#include <string.h>
// #include <pthread.h>
#include <assert.h>


#include "macro.h"

//écrire des int dans un fichier

//bench la vitese des comparaison een fonction de la taille des var

int main()
{
//     INFO("exection de tests")

    FILE * DBxml            = fopen(serializedb,"r");
//     // FILE * DBinverse        = fopen(serializedbunwrap,"r");
//     // FILE * CacheArticleW    = fopen(serialised_Article,"r");



    // FILE * DBxml            = fopen(customxml,"r");
//     // FILE * DBinverse        = fopen(serializedbunwrap,"r");
//     // FILE * CacheArticleW    = fopen(serialised_Article,"r");
// //serialised_Articlecustom


//     FILE * custominverarti            = fopen(serialised_Articlecustom,"w");

//     FILE * ouputDB = fopen(customserializedbunwrap,"w");
//     exitIfNull(ouputDB,"imposible d'ouvrire "customserializedbunwrap)
//     int nbauteur = -1;
//     int * pointeurnbauteur = &nbauteur ;
//     tab_auteur_struct * malistauteur = gen_tab_auteur_from_xml(DBxml);
//     serialise_tab_auteur_struct(malistauteur,ouputDB);
    
//     fclose(ouputDB);
//     //customserializedbunwrap

//     FILE * inn = fopen(customserializedbunwrap,"r");
//     exitIfNull(inn,"imposible d'ouvrire "customserializedbunwrap)

// // ces bon
//     fseek(DBxml,0,SEEK_SET);
//     tab_Article_struct * azerazer = gen_tab_Article_from_xml(DBxml);
//     serialisation_tab_Article_struct(azerazer,custominverarti);

//     fclose(custominverarti);
//     FILE * aaaaaaa            = fopen(serialised_Articlecustom,"r");

//     // tab_auteur_struct * malistaauteur = deserialise_tab_auteur_struct(matablefiche,DBinverse);

//     // FILE * CacheArticleW    = fopen(serialised_Article,"r");
//     // exitIfNull(CacheArticleW,"INPUT PAS CHEMAIN")

//     tab_Article_struct * matable = deserialisation_tab_Article_struct(malistauteur,aaaaaaa);
//     INFO("deserialisation terminer")

    // serialised_Article

    //gérée la création

    // FILE * DBxml = fopen(originedb,"r");

    tab_Article_struct * matable = gen_tab_Article_from_xml(DBxml);

    test_exploration_Article(matable);

    return 0;
}

