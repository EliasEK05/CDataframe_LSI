#include "projet.h"

// Affiche le CDataframe complet sous forme de tableau
void affichage_cdt(COLUMN** liste, int nb_col) {
    if (nb_col == 0) {
        printf("Le CDataframe est vide.\n");
        return;
    }

    char str[100];
    printf("Affichage du CDataframe :\n\n");

    for (int i = 0; i < liste[0]->taille_log; i++) { // ligne
        printf("[%d]\t", i);
        for (int j = 0; j < nb_col; j++) {
            COLUMN *col = liste[j];
            if (col->data[i] == NULL) {
                printf("NULL\t");
            } else {
                convert_value(col, i, str, sizeof(str));
                printf("%s\t", str);
            }
        }
        printf("\n");
    }
}

// Affiche des lignes spécifiques du CDataframe
void affichage_cdt_ligne(COLUMN** liste, int nb_col, int debut, int fin){
    char str[100];
    printf("Affichage du CDataframe :\n\n");
    for(int i=debut; i<=fin; i++){   //ligne
        printf("[%d]\t", i);
        for (int j=0; j<nb_col; j++){
            COLUMN *col = liste[j];
            if (col->data[i] == NULL){
                printf("NULL");
            }
            else{
                convert_value(col, i, str, sizeof(str));
                printf("%s   ", str);}
            int taille_val = strlen(str);
            for (int k = taille_val; k<10; k++)
                printf(" ");

        }
        printf("\n");
    }
}

// Affiche des colonnes spécifiques du CDataframe
void affichage_cdt_col(COLUMN** liste, int nb_col, int debut, int fin){
    char str[100];
    printf("Affichage du CDataframe :\n\n");
    for(int i=0; i<liste[i]->taille_log; i++){   //ligne
        printf("[%d]\t", i);
        for (int j=debut; j<=fin; j++){
            COLUMN *col = liste[j];
            if (col->data[i] == NULL){
                printf("NULL");
            }
            else{
                convert_value(col, i, str, sizeof(str));
                printf("%s   ", str);}
            int taille_val = strlen(str);
            for (int k = taille_val; k<10; k++)
                printf(" ");

        }
        printf("\n");
    }
}

// Affiche le CDataframe selon l'ordre des index d'une colonne triée
void affichage_par_index(COLUMN** liste, int taille){
    int colonne;
    do {
        printf("\nSaisir la colonne triee a partir de laquelle vous aller afficher le CDataframe :");
        scanf("%d", &colonne);
    } while (colonne<0||colonne>taille-1);
    char str[100];
    printf("Affichage du CDataframe :\n\n");

    for(int i=0; i<liste[0]->taille_log; i++){   //ligne
        printf("[%d]\t", i);
        for (int j=0; j<taille; j++){
            COLUMN *col = liste[j];
            if (col->data[liste[colonne]->index[i]] == NULL){
                printf("NULL");
            }
            else{
                convert_value(col, liste[colonne]->index[i], str, sizeof(str));
                printf("%s   ", str);}
            int taille_val = strlen(str);
            for (int k = taille_val; k<10; k++)
                printf(" ");

        }
        printf("\n");
    }
}

// Ajoute une nouvelle ligne de valeurs dans toutes les colonnes
void add_line(COLUMN** liste, int taille){
    for (int i=0; i<taille; i++){
        switch (liste[i]->column_type) {
            case INT: {
                int val;
                printf("\nSaisissez l'entier souhaitez vous ajouter (int) : ");
                scanf("%d", &val);
                insert_value(liste[i], &val);
                break;
            }
            case CHAR: {
                char val;
                printf("\nSaisissez le charactere souhaitez vous ajouter (char) : ");
                scanf(" %c", &val);
                insert_value(liste[i], &val);
                break;
            }
            case FLOAT: {
                float val;
                printf("\nSaisissez le flotant souhaitez vous ajouter (float) : ");
                scanf("%f", &val);
                insert_value(liste[i], &val);
                break;
            }
            case DOUBLE: {
                double val;
                printf("\nSaisissez le double souhaitez vous ajouter (double) : ");
                scanf("%lf", &val);
                insert_value(liste[i], &val);
                break;
            }
            case STRING: {
                char val[100];
                printf("\nSaisissez le mot souhaitez vous ajouter (str) : ");
                scanf("%s", val);
                insert_value(liste[i], val);
                break;
            }

        }

    }
}

// Supprime une ligne spécifique et décale les données restantes
void suppr_ligne(COLUMN** liste, int taille) {
    printf("Saisissez la ligne que vous souhaitez supprimer : ");
    int ligne;
    scanf("%d", &ligne);
    if (ligne < 0 || ligne >= liste[0]->taille_log) {
        printf("Saisissez une ligne valide\n");
        return;
    }

    for (int i = 0; i < taille; i++) {
        COLUMN* col = liste[i];
        if (col->column_type == STRING) {
            free(col->data[ligne]->string_value);
        }
        free(col->data[ligne]);

        for (int j = ligne; j < col->taille_log - 1; j++) {
            col->data[j] = col->data[j + 1];
        }
        col->data[col->taille_log - 1] = NULL;
        col->taille_log--;
    }
}

// Recherche une valeur dans tout le CDataframe selon son type
int rechercher_val(COLUMN** liste, int taille){
    int trouve = 0;
    ENUM_TYPE type;
    do{
    printf("Saisissez le type de la valeur que vous recherchez dans le CDataframe, 1 pour int...: ");
    scanf("%d", &type);} while (type<1 || type>5);
    switch (type) {
        case INT:{
            printf("\nSaissir la valeur recherche :");
            int val;
            scanf("%d", &val);
            for(int i =0; i<taille; i++ ){
                if (liste[i]->column_type == INT) {
                    for (int j = 0; j < liste[0]->taille_log; j++) {
                        if (val == liste[i]->data[j]->int_value){
                            printf("\nValeur trouvee dans la colonne '%s' a la ligne %d !\n", liste[i]->titre, j);
                        return 1;}
                    }
                }
            }
            break;}
        case CHAR:{
            printf("\nSaissir la valeur recherche :");
            char val;
            scanf(" %c", &val);
            for(int i =0; i<taille; i++ ){
                if (liste[i]->column_type == CHAR) {
                    for (int j = 0; j < liste[0]->taille_log; j++) {
                        if (val == liste[i]->data[j]->char_value){
                            printf("\nValeur trouvee dans la colonne '%s' a la ligne %d !\n", liste[i]->titre, j);
                            return 1;}
                    }
                }
            }
            break;}
        case FLOAT:{
            printf("\nSaissir la valeur recherche :");
            float val;
            scanf("%f", &val);
            for(int i =0; i<taille; i++ ){
                if (liste[i]->column_type == FLOAT) {
                    for (int j = 0; j < liste[0]->taille_log; j++) {
                        if ( liste[i]->data[j]->float_value == val){
                            printf("\nValeur trouvee dans la colonne '%s' a la ligne %d !\n", liste[i]->titre, j);
                            return 1;}
                    }
                }
            }
            break;}
        case DOUBLE:{
            printf("\nSaissir la valeur recherche :");
            double val;
            scanf("%lf", &val);
            for(int i =0; i<taille; i++ ){
                if (liste[i]->column_type == DOUBLE) {
                    for (int j = 0; j < liste[0]->taille_log; j++) {
                        if (val == liste[i]->data[j]->double_value){
                            printf("\nValeur trouvee dans la colonne '%s' a la ligne %d !\n", liste[i]->titre, j);
                            return 1;}
                    }
                }
            }
            break;}
        case STRING:{
            printf("\nSaisir la valeur recherchee :");
            char val[100];
            scanf("%s", val);
            for(int i =0; i<taille; i++ ){
                if (liste[i]->column_type == STRING) {
                    for (int j = 0; j < liste[0]->taille_log; j++) {
                        if (strcmp(val, liste[i]->data[j]->string_value) == 0){
                            printf("\nValeur trouvee dans la colonne '%s' a la ligne %d !\n", liste[i]->titre, j);
                            return 1;}
                    }
                }
            }
            break;}
    }
    printf("\nLa valeur n a pas ete trouve dans le CDataframe");
    return 0;
}

// Remplace une valeur spécifique dans le CDataframe
void remplacer_valeur(COLUMN** liste, int taille){
    int ligne,col;
    printf("\nSaisir la ligne et la colonne sur lesquel se trouve la valeur que vous voulez remplacer [ligne,col]: ");
    scanf("%d,%d", &ligne,&col);

    if (col < 0 || col >= taille || ligne < 0 || ligne >= liste[col]->taille_log) {
        printf("Indices invalides.\n");
        return;
    }

    ENUM_TYPE type = liste[col]->column_type;


    switch (type) {
        case INT:{
            printf("\nSaissir la valeur que vous souhaiter insserer :");
            int val;
            scanf("%d", &val);
            liste[col]->data[ligne]->int_value = val;
            break;}
        case CHAR:{
            printf("\nSaissir la valeur que vous souhaiter insserer :");
            char val;
            scanf(" %c", &val);
            liste[col]->data[ligne]->char_value = val;
            break;}
        case FLOAT:{
            printf("\nSaissir la valeur que vous souhaiter insserer :");
            float val;
            scanf("%f", &val);
            liste[col]->data[ligne]->float_value = val;
            break;}
        case DOUBLE:{
            printf("\nSaissir la valeur que vous souhaiter insserer :");
            double val;
            scanf("%lf", &val);
            liste[col]->data[ligne]->double_value = val;
            break;}
        case STRING:{
            printf("\nSaissir la valeur que vous souhaiter insserer :");
            char val[100];
            scanf("%s", val);
            free(liste[col]->data[ligne]->string_value);
            liste[col]->data[ligne]->string_value = malloc(strlen(val) + 1);
            strcpy(liste[col]->data[ligne]->string_value, val);
            break;}
    }

}
