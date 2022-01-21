#include <stdio.h>
#include <stdlib.h>
#include "../header/unwrap.h"

#include <string.h>
// #include <pthread.h>
#include <assert.h>


#include "../header/macro.h"

#include "../header/search.h"

#include "../header/list.h"

//écrire des int dans un fichier

//bench la vitese des comparaison een fonction de la taille des var



// exploration(auteur_struct * monauteur){

//     for (int i = 0; i < monauteur->nbelementmagi ; i++)
//     {
//             monauteur;
//             printf("%s ==> %d\n",monauteur->tab_ptr_Article[i],monauteur->tab_ptr_Article[i] );
//             for (int u = 0; u < monauteur->tab_ptr_Article[i].nombre_auteur; u++)
//             {
//                 exploration(monauteur->tab_ptr_Article[i].tab_ptr_auteur[u]);
//             }
//     }
// }


int main()
{
    INFO("exection de tests")

    // INFO("tests:generation graph")

    // FILE * XML               = fopen(origineXML      ,"r");
    // exitIfNull(XML  ,"erreur ouverture bd")
    // graphe_struct_Konqui graph= gen_Graph_from_XML(XML);
    // fclose(XML);

    // INFO("tests:Serialisation")

    // FILE * DBficheEcriture   = fopen(cache_fiche     ,"w");
    // FILE * DBauteurEcriture  = fopen(auteur_cache    ,"w");
    // FILE * DBArticleEcriture = fopen(Article_cache   ,"w");
    // serialise_Graph(graph,
    //     DBficheEcriture,
    //     DBauteurEcriture,
    //     DBArticleEcriture);

    // fclose(DBficheEcriture);
    // fclose(DBauteurEcriture);
    // fclose(DBArticleEcriture);

    INFO("tests:deserialisation")

    // FILE * DBficheLecture   = fopen(custom_fiche_cache     ,"r");
    // FILE * DBauteurLecture  = fopen(custom_auteur_cache    ,"r");
    // FILE * DBArticleLecture = fopen(custom_Article_cache   ,"r");

    FILE * DBficheLecture   = fopen(cache_fiche     ,"r");
    FILE * DBauteurLecture  = fopen(auteur_cache    ,"r");
    FILE * DBArticleLecture = fopen(Article_cache   ,"r");

    graphe_struct_Konqui graph = deserialise_Graph(DBficheLecture
                                    ,DBauteurLecture
                                    ,DBArticleLecture);

    exitIfNull(DBficheLecture  ,"erreur ouverture bd")
    exitIfNull(DBauteurLecture ,"erreur ouverture bd")
    exitIfNull(DBArticleLecture,"erreur ouverture bd")

    fclose(DBficheLecture);
    fclose(DBauteurLecture);
    fclose(DBArticleLecture);

    test_exploration_Article(&graph.tab_Article_struct);

    ll_list * retour = stringSearch(&graph,searchauteur,"a");
    if (retour->size == 0)
    {
        ERROR("recherche echouer");
    }
    printSearch(retour,silence);

    // scoarboard(&graph1,TOP_auteur,5);
    // scoarboard(&graph1,TOP_Article,5);
    // printList_Article(graph1.tab_Article_struct);

    // printList_auteur(graph.tab_auteur_struct);
    // printList_Article(graph.tab_Article_struct);

    

    // find_auteur("Konqui",&graph.tab_auteur_struct);

    // parcour_largeur(graph);
    // test_exploration_Article(graph1.tab_Article_struct);


    // test_exploration_Article(graph.tab_Article_struct);



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

