#include "projet.h"

// Crée un CDataframe complet avec saisie utilisateur des colonnes et des valeurs
COLUMN** cdt(int nb_col) {
    COLUMN **liste_col = malloc(nb_col * sizeof(COLUMN*));
    int type;
    char titre[100];


    for (int i = 0; i < nb_col; i++) {
        printf("Type de la colonne, ecrivez 1 pour int, 2 pour char, 3 pour float, 4 pour double, 5 pour str :");
        scanf("%d", &type);printf("\n");
        printf("Saisir un titre : ");

        scanf("%s", titre);printf("\n");

        liste_col[i] = create_column(type, titre);
    }

    int nb_val;
    printf("Saisir le nombre de valeur souhaite dans les colonnes :");
    scanf("%d", &nb_val);printf("\n");

    for(int i = 0; i<nb_col; i++){
        for (int j = 0; j<nb_val; j++){
            printf("\nSaisir la valeur %d de la colonne %d :", j, i);
            char input[100];
            scanf("%s", input);
            if (strcmp(input, "NULL") == 0) {
                insert_value(liste_col[i], NULL);}
            else {
                switch (liste_col[i]->column_type) {
                    case INT: {
                        int val = atoi(input);
                        insert_value(liste_col[i], &val);
                        break;
                    }
                    case CHAR: {
                        char val = input[0];
                        insert_value(liste_col[i], &val);
                        break;
                    }
                    case FLOAT: {
                        float val = atof(input);
                        insert_value(liste_col[i], &val);
                        break;
                    }
                    case DOUBLE: {
                        double val = atof(input);
                        insert_value(liste_col[i], &val);
                        break;
                    }
                    case STRING: {
                        insert_value(liste_col[i], input);
                        break;
                    }


                }
            }


        }
    }

    return liste_col;
}

// Crée un CDataframe vide sans saisir de valeurs
COLUMN** cdt_vide(int nb_col){
    COLUMN **liste_col = malloc(nb_col * sizeof(COLUMN*));
    int type;
    char titre[100];


    for (int i = 0; i < nb_col; i++) {
        printf("Type de la colonne, ecrivez 1 pour int, 2 pour char, 3 pour float, 4 pour double, 5 pour str :");
        scanf("%d", &type);printf("\n");
        printf("Saisir un titre : ");

        scanf("%s", titre);printf("\n");

        liste_col[i] = create_column(type, titre);
    }
    return liste_col;
}

// Supprime toutes les colonnes d'un CDataframe
void delete_cdt(COLUMN** liste, int nb_col){
    for (int i=0; i<nb_col; i++)
        delete_column(&liste[i]);
}
