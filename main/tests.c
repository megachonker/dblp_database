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
    INFO("exection de tests")

    FILE * XML               = fopen(origineXML      ,"r");
    
    exitIfNull(XML  ,"erreur ouverture bd")

    unwrap_Graph_struct graph= gen_Graph_from_XML(XML);

    FILE * DBficheEcriture   = fopen(cache_fiche     ,"w");
    FILE * DBauteurEcriture  = fopen(auteur_cache    ,"w");
    FILE * DBArticleEcriture = fopen(Article_cache   ,"w");

    serialise_Graph(graph   ,DBficheEcriture
                            ,DBauteurEcriture
                            ,DBArticleEcriture);

    fclose(DBficheEcriture);
    fclose(DBauteurEcriture);
    fclose(DBArticleEcriture);


    FILE * DBficheLecture   = fopen(cache_fiche     ,"r");
    FILE * DBauteurLecture  = fopen(auteur_cache    ,"r");
    FILE * DBArticleLecture = fopen(Article_cache   ,"r");


    unwrap_Graph_struct graph2 = deserialise_Graph(DBficheLecture
                                    ,DBauteurLecture
                                    ,DBArticleLecture);

    exitIfNull(DBficheLecture  ,"erreur ouverture bd")
    exitIfNull(DBauteurLecture ,"erreur ouverture bd")
    exitIfNull(DBArticleLecture,"erreur ouverture bd")


    test_exploration_Article(graph2.tab_Article_struct);



//     FILE * DBxml            = fopen(customXML,"r");
//     // FILE * DBinverse        = fopen(auteur_cache,"r");
//     // FILE * CacheArticleW    = fopen(Article_cache,"r");
// //custom_Article_cache


//     FILE * custominverarti            = fopen(custom_Article_cache,"w");

//     FILE * ouputDB = fopen(custom_auteur_cache,"w");
//     exitIfNull(ouputDB,"imposible d'ouvrire "custom_auteur_cache)

//     tab_auteur_struct * malistauteur = gen_tab_auteur_from_xml(DBxml);
//     serialise_tab_auteur_struct(malistauteur,ouputDB);
    
//     fclose(ouputDB);
//     //custom_auteur_cache

//     FILE * inn = fopen(custom_auteur_cache,"r");
//     exitIfNull(inn,"imposible d'ouvrire "custom_auteur_cache)

// // ces bon
//     fseek(DBxml,0,SEEK_SET);
//     tab_Article_struct * azerazer = gen_tab_Article_from_xml(DBxml);
//     serialisation_tab_Article_struct(azerazer,custominverarti);

//     fclose(custominverarti);
//     FILE * aaaaaaa            = fopen(custom_Article_cache,"r");

//     // tab_auteur_struct * malistaauteur = deserialise_tab_auteur_struct(matablefiche,DBinverse);

//     // FILE * CacheArticleW    = fopen(Article_cache,"r");
//     // exitIfNull(CacheArticleW,"INPUT PAS CHEMAIN")

//     tab_Article_struct * matable = deserialisation_tab_Article_struct(malistauteur,aaaaaaa);
//     INFO("deserialisation terminer")

//     // Article_cache

//     //gérée la création

//     // FILE * DBxml = fopen(origineXML,"r");

//     // tab_Article_struct * matable = gen_tab_Article_from_xml(DBxml);




    return 0;
}

