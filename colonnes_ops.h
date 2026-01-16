//
// Created by elias on 16/01/2026.
//

#ifndef PROJETCDATAFRAME_MAIN_COLONNES_OPS_H
#define PROJETCDATAFRAME_MAIN_COLONNES_OPS_H

#include "projet.h"


// Fonctions pour la gestion des colonnes :
COLUMN *create_column(ENUM_TYPE type, char *title);
int insert_value(COLUMN *col, void *value);
void print_col(COLUMN* col);
void delete_column(COLUMN **col);
void add_col(COLUMN*** liste, int *taille);
void suppr_col(COLUMN*** liste, int *taille);
void renommer_col(COLUMN** liste, int taille);
void convert_value(COLUMN *col, int i, char *str, int size);


#endif //PROJETCDATAFRAME_MAIN_COLONNES_OPS_H
