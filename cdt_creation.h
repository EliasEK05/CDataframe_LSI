//
// Created by elias on 16/01/2026.
//

#ifndef PROJETCDATAFRAME_MAIN_CDT_CREATION_H
#define PROJETCDATAFRAME_MAIN_CDT_CREATION_H
#include "projet.h"


// Fonctions concernant la création du CDataframe :
COLUMN** cdt(int nb_col);
COLUMN** cdt_vide(int nb_col);
void delete_cdt(COLUMN** liste, int nb_col);


#endif //PROJETCDATAFRAME_MAIN_CDT_CREATION_H
