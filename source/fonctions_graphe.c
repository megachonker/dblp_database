#include <stdio.h>
#include <stdlib.h>
#include "../header/unwrap.h"
#include "../header/fonctions_graphe.h"


graphe_struct_Konqui faire_graphe_Konqui(char * DBfiche, char * DBauteur, char * DBArticle)
{
    INFO("tests:deserialisation")

    FILE * DBficheLecture   = fopen(DBfiche     ,"r");
    FILE * DBauteurLecture  = fopen(DBauteur    ,"r");
    FILE * DBArticleLecture = fopen(DBArticle   ,"r");
    
    graphe_struct_Konqui graphe_Konqui = deserialise_Graph(DBficheLecture
                                    ,DBauteurLecture
                                    ,DBArticleLecture);

    exitIfNull(DBficheLecture  ,"erreur ouverture bd")
    exitIfNull(DBauteurLecture ,"erreur ouverture bd")
    exitIfNull(DBArticleLecture,"erreur ouverture bd")

    fclose(DBficheLecture);
    fclose(DBauteurLecture);
    fclose(DBArticleLecture);

    return graphe_Konqui;
}



//faire le graphe (tableau) des pointeurs vers les auteurs, ce que je vais appeler ensuite graphe_Katie
graphe_struct_Katie faire_graphe_ptr_auteur( graphe_struct_Konqui graphe_Konqui)
{

    int size_graphe= graphe_Konqui.tab_auteur_struct.nombre_auteur;
    graphe_struct_Katie graphe_struct;
    graphe_struct.graphe= malloc(sizeof(auteur_struct*)*size_graphe);
    exitIfNull(graphe_struct.graphe,"faire_graphe_ptr_auteur:Echec du mallc ")
    graphe_struct.size_graphe= size_graphe;

    for(int i=0; i<size_graphe; i++)
    {
        auteur_struct* ai_ptr= &(graphe_Konqui.tab_auteur_struct.tab_auteur[i]);
        ai_ptr->size_pcc_auteur= -1;
        graphe_struct.graphe[i]= ai_ptr;           
    }
    graphe_struct.nb_auteurMax = graphe_Konqui.tab_auteur_struct.nombre_auteur;
    return graphe_struct;
}


void voir_si_un_auteur_est_dans_le_graphe_et_donner_un_Article_ou_il_apparait(graphe_struct_Katie graphe_struct, char* nom_auteur)
{
    comparaison_auteur trouver_ou_pas= auteur_pas_trouver;
    auteur_struct* ptr_auteur= NULL;
    
    for(int i=0; i<graphe_struct.size_graphe; i++)
    {
        if(strcmp(nom_auteur, graphe_struct.graphe[i]->nom_auteur)==0)
        {
            trouver_ou_pas= auteur_trouver;
            ptr_auteur= graphe_struct.graphe[i];
            
        }
    }
    if(trouver_ou_pas== auteur_pas_trouver)
    {
        printf("%s n'apparait dans aucun Article\n", nom_auteur);   
    }
    else 
    {
        printf("%s apparait dans le graphe, il est par exemple l'auteur de l'Article: %s\n", nom_auteur, ptr_auteur->tab_ptr_Article[0]->nom_Article);        
    }
}

void donner_tous_les_Articles_de_auteur(graphe_struct_Katie graphe_struct, char* nom_auteur)
{
    comparaison_auteur trouver_ou_pas= auteur_pas_trouver;
    auteur_struct* ptr_auteur= NULL;
    
    for(int i=0; i<graphe_struct.size_graphe; i++)
    {
        if(strcmp(nom_auteur, graphe_struct.graphe[i]->nom_auteur)==0)
        {
            trouver_ou_pas= auteur_trouver;
            ptr_auteur= graphe_struct.graphe[i];
            
        }
    }
    if(trouver_ou_pas== auteur_pas_trouver)
    {
        printf("%s n'apparait dans aucun Article\n", nom_auteur);   
    }
    else
    {
        printf("%s apparait dans le graphe, il est l'auteur des l'Articles: \n", nom_auteur);
        for(int k=0; k< ptr_auteur->size; k++)
        {
            printf("%s\n", ptr_auteur->tab_ptr_Article[k]->nom_Article);
        }
    }
}

void donner_tous_ceux_qui_ont_travalle_avec_auteur(graphe_struct_Katie graphe_struct, char* nom_auteur)
{
    comparaison_auteur trouver_ou_pas= auteur_pas_trouver;
    auteur_struct* ptr_auteur= NULL;
    
    for(int i=0; i<graphe_struct.size_graphe; i++)
    {
        if(strcmp(nom_auteur, graphe_struct.graphe[i]->nom_auteur)==0)
        {
            trouver_ou_pas= auteur_trouver;
            ptr_auteur= graphe_struct.graphe[i];
            
        }
    }
    if(trouver_ou_pas== auteur_pas_trouver)
    {
        printf("%s n'apparait dans aucun Article\n", nom_auteur);   
    }
    else
    {
        printf("%s a déjà écrit un Article avec:\n", nom_auteur);
    
        for(int l=0; l< ptr_auteur->size; l++)
        {

            Article_struct* ptr_Al= ptr_auteur->tab_ptr_Article[l];

            for(int k=0; k< ptr_Al->nombre_auteur; k++)
            {
                auteur_struct* ptr_collegue= ptr_Al->tab_ptr_auteur[k];
                printf("%s\n", ptr_collegue->nom_auteur);

            }
        }
    }
}

void print_noms_des_voisins(graphe_struct_Katie graphe_t, char* nom_auteur)
{

    comparaison_auteur trouver_ou_pas= auteur_pas_trouver;
    auteur_struct* auteur_ptr= NULL;

    for(int i=0; i<graphe_t.size_graphe; i++)
    {
        graphe_t.graphe[i]->indice_dans_le_graphe= i;

        if(strcmp(nom_auteur, graphe_t.graphe[i]->nom_auteur)==0)
        {
            trouver_ou_pas= auteur_trouver;
            auteur_ptr= graphe_t.graphe[i];
        }
    }

    if(trouver_ou_pas== auteur_pas_trouver)
        printf("%s %s %s\n", "l'auteur", nom_auteur, "ne figure dans aucun Article");


    printf("voisins de %s\n", auteur_ptr->nom_auteur);

    for(int l=0; l< auteur_ptr->size; l++)
    {
        Article_struct* Al_ptr= auteur_ptr->tab_ptr_Article[l];

        for(int k=0; k< Al_ptr->nombre_auteur; k++)
        {
            auteur_struct* voisin_ptr= Al_ptr->tab_ptr_auteur[k];
            printf("%s\n", voisin_ptr->nom_auteur);
        }

    }

}





#define PROFONDEUREXP 6
void exploreauteur(const auteur_struct * monauteur,int profondeur);

void explorearticle(const Article_struct * monarticle, int profondeur){
    // INFO("Exploration Article")
    if (profondeur > PROFONDEUREXP)
    {
        return;
    }
    
    // BLUE()
    // tabulation(profondeur);
    // printf("%s\n",monarticle->nom_Article);
    // profondeur++;
    for (int i = 0; i < monarticle->nombre_auteur; i++)
    {
        // GREEN()
        // tabulation(profondeur);
        // printf("%s\n",monarticle->tab_ptr_auteur[i]->nom_auteur);
        //  CLRCOLOR()

        exploreauteur(monarticle->tab_ptr_auteur[i],profondeur);
    }
    
}

void exploreauteur(const auteur_struct * monauteur,int profondeur){
    // INFO("Exploration auteur")
    if (profondeur > PROFONDEUREXP)
    {
        return;
    }
    GREEN()
    repchar('\t',profondeur);
    GREY();printf("%s\n",monauteur->nom_auteur);
    CLRCOLOR()
    profondeur++;
    for (int i = 0; i < monauteur->nbArticlecontenue; i++)
    {
        // BLUE()
        // tabulation(profondeur);
        // printf("%s\n",monauteur->tab_ptr_Article[i]->nom_Article);
        // CLRCOLOR()
        explorearticle(monauteur->tab_ptr_Article[i],profondeur);
    }
    
}

void test_exploration_Article(const tab_Article_struct * mesarticle){
    // for (int i = 0; i < mesarticle->nombre_Article; i++)
    // {
    //     explorearticle(&mesarticle->tab_Article[i],0);
    // }
    
    for (int i = 0; i < mesarticle->nombre_Article ; i++)
    {
        BLUE()
        printf("%s ==> %d\n",mesarticle->tab_Article[i].nom_Article, mesarticle->tab_Article[i].nombre_auteur);
        for (int u = 0; u < mesarticle->tab_Article[i].nombre_auteur; u++)
        {
            GREEN()
            printf("\t%s ==> %d\n",mesarticle->tab_Article[i].tab_ptr_auteur[u]->nom_auteur,mesarticle->tab_Article[i].tab_ptr_auteur[u]->nbArticlecontenue);
            for (int pp = 0; pp < mesarticle->tab_Article[i].tab_ptr_auteur[u]->nbArticlecontenue; pp++)
            {
                BLUE()
                printf("\t\t%s ==> %d\n",mesarticle->tab_Article[i].tab_ptr_auteur[u]->tab_ptr_Article[pp]->nom_Article,mesarticle->tab_Article[i].tab_ptr_auteur[u]->tab_ptr_Article[pp]->nombre_auteur); 
                for (int UI = 0; UI < mesarticle->tab_Article[i].tab_ptr_auteur[u]->tab_ptr_Article[pp]->nombre_auteur; UI++)
                {
                    GREEN()
                    printf("\t\t\t%s\n",mesarticle->tab_Article[i].tab_ptr_auteur[u]->tab_ptr_Article[pp]->tab_ptr_auteur[UI]->nom_auteur);
                    // exploreauteur(mesarticle->tab_Article[i].tab_ptr_auteur[u]->tab_ptr_Article[pp]->tab_ptr_auteur[UI],3);
                }
            }           
        }
    }
}
