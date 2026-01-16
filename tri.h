//
// Created by elias on 16/01/2026.
//

#ifndef PROJETCDATAFRAME_MAIN_TRI_H
#define PROJETCDATAFRAME_MAIN_TRI_H
#include "projet.h"

// Fonctions pour le tri des données :
void permuter(int *a, int *b);
void quicksort(COLUMN *col, int first, int last);
int partition(COLUMN *col, int gauche, int droite);
void tri_par_insertion(COLUMN *col);
int compare(COL_TYPE *a, COL_TYPE *b, ENUM_TYPE type);


#endif //PROJETCDATAFRAME_MAIN_TRI_H
