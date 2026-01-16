#ifndef PROJETCDATAFRAME_PROJET_H
#define PROJETCDATAFRAME_PROJET_H
#define REALOC_SIZE 256

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "tri.h"
#include "cdt_creation.h"
#include "colonnes_ops.h"
#include "dataframe_ops.h"

enum enum_type
{
    NULLVAL = 0 ,INT , CHAR, FLOAT, DOUBLE, STRING,  UINT,  STRUCTURE
}; typedef enum enum_type ENUM_TYPE;

union column_type{
    unsigned int uint_value;
    signed int int_value;
    char char_value;
    float float_value;
    double double_value;
    char* string_value;
    void* struct_value;
}; typedef union column_type COL_TYPE ;

typedef struct {
    char* titre;
    unsigned taille_phy;
    unsigned int taille_log;
    ENUM_TYPE column_type;
    COL_TYPE **data;
    unsigned long long int *index;
    // État de l'index : 0=pas d'index, -1=invalide, 1=valide
    int valid_index;
    // Direction de tri : 0=ASC, 1=DESC
    int sort_dir;
}COLUMN;


#endif //PROJETCDATAFRAME_PROJET_H

