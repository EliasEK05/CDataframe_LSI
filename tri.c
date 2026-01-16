#include "tri.h"

// Permute deux valeurs entières
void permuter(int *a, int *b) {
    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

// Algorithme de tri rapide (quicksort) pour les index d'une colonne
void quicksort(COLUMN *col, int gauche, int droite) {
    if (gauche < droite){
        int pi = partition(col, gauche, droite);
        quicksort(col, gauche, pi-1);
        quicksort(col, pi + 1, droite);
    }
}

// Fonction de partition pour l'algorithme quicksort
int partition(COLUMN *col, int gauche, int droite) {
    int i = gauche - 1;

    switch (col->column_type) {
        case INT: {
            COL_TYPE *pivot = col->data[col->index[droite]];
            for (int j = gauche; j < droite; j++) {
                if (col->data[col->index[j]] != NULL &&
                    (pivot == NULL || col->data[col->index[j]]->int_value <= pivot->int_value)) {
                    i++;
                    permuter(&(col->index[i]), &(col->index[j]));
                }
            }
            permuter(&(col->index[i + 1]), &(col->index[droite]));
            return i + 1;
        }
        case CHAR: {
            COL_TYPE *pivot = col->data[col->index[droite]];
            for (int j = gauche; j < droite; j++) {
                if (col->data[col->index[j]] != NULL &&
                    (pivot == NULL || col->data[col->index[j]]->char_value <= pivot->char_value)) {
                    i++;
                    permuter(&(col->index[i]), &(col->index[j]));
                }
            }
            permuter(&(col->index[i + 1]), &(col->index[droite]));
            return i + 1;
        }
        case FLOAT: {
            COL_TYPE *pivot = col->data[col->index[droite]];
            for (int j = gauche; j < droite; j++) {
                if (col->data[col->index[j]] != NULL &&
                    (pivot == NULL || col->data[col->index[j]]->float_value <= pivot->float_value)) {
                    i++;
                    permuter(&(col->index[i]), &(col->index[j]));
                }
            }
            permuter(&(col->index[i + 1]), &(col->index[droite]));
            return i + 1;
        }
        case DOUBLE: {
            COL_TYPE *pivot = col->data[col->index[droite]];
            for (int j = gauche; j < droite; j++) {
                if (col->data[col->index[j]] != NULL &&
                    (pivot == NULL || col->data[col->index[j]]->double_value <= pivot->double_value)) {
                    i++;
                    permuter(&(col->index[i]), &(col->index[j]));
                }
            }
            permuter(&(col->index[i + 1]), &(col->index[droite]));
            return i + 1;
        }
        case STRING: {
            COL_TYPE *pivot = col->data[col->index[droite]];
            for (int j = gauche; j < droite; j++) {
                if (col->data[col->index[j]] != NULL &&
                    (pivot == NULL || strcmp(col->data[col->index[j]]->string_value, pivot->string_value) <= 0)) {
                    i++;
                    permuter(&(col->index[i]), &(col->index[j]));
                }
            }
            permuter(&(col->index[i + 1]), &(col->index[droite]));
            return i + 1;
        }
        default:
            return -1;
    }
}

// Algorithme de tri par insertion pour les index
void tri_par_insertion(COLUMN *col) {
    printf("\ntri par insertion effectue\n");
    for (int i = 1; i < col->taille_log; i++) {
        int j = i;
        while (j > 0 && col->data[col->index[j - 1]] != NULL &&
               (col->data[col->index[j]] == NULL ||
                compare(col->data[col->index[j - 1]], col->data[col->index[j]], col->column_type) > 0)) {
            permuter(&(col->index[j]), &(col->index[j - 1]));
            j--;
        }
    }
}

// Compare deux valeurs selon leur type de données
int compare(COL_TYPE *a, COL_TYPE *b, ENUM_TYPE type) {
    switch (type) {
        case INT:
            return (a->int_value > b->int_value) - (a->int_value < b->int_value);
        case CHAR:
            return (a->char_value > b->char_value) - (a->char_value < b->char_value);
        case FLOAT:
            return (a->float_value > b->float_value) - (a->float_value < b->float_value);
        case DOUBLE:
            return (a->double_value > b->double_value) - (a->double_value < b->double_value);
        case STRING:
            return strcmp(a->string_value, b->string_value);
        default:
            return 0;
    }
}
