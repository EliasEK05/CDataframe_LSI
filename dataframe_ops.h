//
// Created by elias on 16/01/2026.
//

#ifndef PROJETCDATAFRAME_MAIN_DATAFRAME_OPS_H
#define PROJETCDATAFRAME_MAIN_DATAFRAME_OPS_H

#include "projet.h"

// Fonctions pour les opérations sur le dataframe :
void affichage_cdt(COLUMN** liste, int nb_col);
void affichage_cdt_ligne(COLUMN** liste, int nb_col, int debut, int fin);
void affichage_cdt_col(COLUMN** liste, int nb_col, int debut, int fin);
void add_line(COLUMN** liste, int taille);
void suppr_ligne(COLUMN** liste, int taille);
int rechercher_val(COLUMN** liste, int taille);
void remplacer_valeur(COLUMN** liste, int taille);
void affichage_par_index(COLUMN** liste, int taille);

#endif //PROJETCDATAFRAME_MAIN_DATAFRAME_OPS_H
