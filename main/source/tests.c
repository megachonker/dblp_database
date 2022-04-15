#include <stdio.h>
#include <stdlib.h>
#include "../header/unwrap.h"
#include "../header/fonctions_graphe.h"
#include "../header/Dijkstra.h"


#include <string.h>
// #include <pthread.h>
#include <assert.h>


#include "../header/macro.h"

#include "../header/search.h"

int main(void)
{

    graphe_struct_Konqui graphe_Konqui= faire_graphe_Konqui(cache_fiche, auteur_cache, Article_cache);

    graphe_struct_Katie graphe_Katie= faire_graphe_ptr_auteur(graphe_Konqui);

    char* nom_auteur= "Abdelouahed Hamdi";
}