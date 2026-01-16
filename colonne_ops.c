#include "projet.h"

// Crée une nouvelle colonne avec le type et le titre spécifiés
COLUMN *create_column(ENUM_TYPE type, char* title){

    COLUMN* ptr = (COLUMN*) malloc(sizeof (COLUMN));
    ptr->titre = malloc(strlen(title) + 1);
    strcpy(ptr->titre, title);
    ptr->taille_phy = 0;
    ptr->taille_log = 0;
    ptr->column_type = type;
    ptr->data = NULL;
    ptr->index = NULL;
    ptr->valid_index = 0;
    return ptr;
}

// Insère une valeur dans une colonne (avec réallocation automatique si nécessaire)
int insert_value(COLUMN* col, void *value) {
    // Vérification et réallocation de la mémoire si nécessaire
    if (col->taille_log >= col->taille_phy) {
        col->taille_phy += REALOC_SIZE;
        col->data = (COL_TYPE**)realloc(col->data, col->taille_phy * sizeof(COL_TYPE*));
        col->index = (unsigned long long int*)realloc(col->index, col->taille_phy * sizeof(unsigned long long int));
        for (int i = col->taille_log; i < col->taille_phy; i++) {
            col->data[i] = NULL;
            col->index[i] = i;
        }
    }

    if (value == NULL) {
        col->data[col->taille_log] = NULL;
    } else {
        col->data[col->taille_log] = (COL_TYPE*)malloc(sizeof(COL_TYPE));
        switch (col->column_type) {
            case INT:
                col->data[col->taille_log]->int_value = *((int*)value);
                break;
            case CHAR:
                col->data[col->taille_log]->char_value = *((char*)value);
                break;
            case FLOAT:
                col->data[col->taille_log]->float_value = *((float*)value);
                break;
            case DOUBLE:
                col->data[col->taille_log]->double_value = *((double*)value);
                break;
            case STRING:
                col->data[col->taille_log]->string_value = (char*)malloc(strlen((char*)value) + 1);
                strcpy(col->data[col->taille_log]->string_value, (char*)value);
                break;
            default:
                free(col->data[col->taille_log]);
                return 0;
        }
    }
    col->index[col->taille_log] = col->taille_log;
    col->taille_log++;
    return 1;
}

// Supprime une colonne et libère toute la mémoire associée
void delete_column(COLUMN **col) {
    if (*col) {
        for (int i = 0; i < (*col)->taille_log; i++) {
            if ((*col)->column_type == STRING && (*col)->data[i]) {
                free((*col)->data[i]->string_value);
            }
            free((*col)->data[i]);
        }
        free((*col)->data);
        free((*col)->index);
        free((*col)->titre);
        free(*col);
        *col = NULL;
    }
}

// Convertit une valeur de la colonne en chaîne de caractères pour l'affichage
void convert_value(COLUMN *col, int i, char *str, int size){
        if (col->data[i] == NULL) {
            strncpy(str, "NULL", size);
            str[size - 1] = '\0';
        } else {
            switch (col->column_type) {
                case INT:
                    snprintf(str, size, "%d", col->data[i]->int_value);
                    break;
                case CHAR:
                    snprintf(str, size, "%c", col->data[i]->char_value);
                    break;
                case FLOAT:
                    snprintf(str, size, "%.2f", col->data[i]->float_value);
                    break;
                case DOUBLE:
                    snprintf(str, size, "%.2f", col->data[i]->double_value);
                    break;
                case STRING:
                    strncpy(str, col->data[i]->string_value, size);
                    str[size - 1] = '\0';
                    break;
                default:
                    str[0] = '\0';
                    break;
            }
        }
    }

// Affiche le contenu complet d'une colonne
void print_col(COLUMN* col){
    printf("Affichage de la colonne '%s':\n", col->titre);
    char str[100];
    for (int i = 0; i<col->taille_log; i++){
        if (col->data[i] == NULL){
            printf("[%d] NULL\n", i);
        }
        else{
        convert_value(col, i, str, sizeof(str));
        printf("[%d] %s \n",i, str);}
    }

}

// Ajoute une nouvelle colonne au CDataframe
void add_col(COLUMN*** liste, int *taille){
    (*taille)++;
    *liste = realloc(*liste, (*taille)*sizeof (COLUMN*));
    ENUM_TYPE type;
    printf("Saisir le type de la colonne entre int(1), char(2), float(3), double(4), str(5): ");
    scanf("%d", &type);
    printf("\nSaisir le titre de la colonne :");
    char titre[100];
    scanf("%s", titre);
    (*liste)[*taille - 1] = create_column(type, titre);
    for (int i=0; i< (*liste)[0]->taille_log; i++){
        switch ((*liste)[*taille-1]->column_type) {
            case INT: {
                int val;
                printf("\nSaisissez l'entier que souhaitez vous ajouter a la ligne %d (int) : ",i);
                scanf(" %d", &val);
                insert_value((*liste)[*taille-1], &val);
                break;
            }
            case CHAR: {
                char val;
                printf("\nSaisissez le charactere que souhaitez vous ajouter a la ligne %d (char) : ", i);
                scanf(" %c", &val);
                insert_value((*liste)[*taille-1], &val);
                break;
            }
            case FLOAT: {
                float val;
                printf("\nSaisissez le flotant que souhaitez vous ajouter a la ligne %d (float) : ",i);
                scanf(" %f", &val);
                insert_value((*liste)[*taille-1], &val);
                break;
            }
            case DOUBLE: {
                double val;
                printf("\nSaisissez le double souhaitez que vous ajouter a la ligne %d (double) : ",i);
                scanf(" %lf", &val);
                insert_value((*liste)[*taille-1], &val);
                break;
            }
            case STRING: {
                char val[100];
                printf("\nSaisissez le mot que souhaitez vous ajouter a la ligne %d (str) : ", i);
                scanf(" %s", val);
                insert_value((*liste)[*taille], val);
                break;
            }

        }

    }
}

// Supprime une colonne spécifique du CDataframe
void suppr_col(COLUMN*** liste, int *taille) {
    printf("Saisissez la colonne que vous souhaitez supprimer : ");
    int colonne;
    scanf("%d", &colonne);
    if (colonne < 0 || colonne >= *taille) {
        printf("Saisissez une colonne valide\n");
        return;
    }
    delete_column(&(*liste)[colonne]);

    for (int i = colonne; i < *taille - 1; i++) {
        (*liste)[i] = (*liste)[i + 1];
    }
    (*taille)--;
    if (*taille > 0) {
        *liste = realloc(*liste, (*taille) * sizeof(COLUMN*));
    } else {
        free(*liste);
        *liste = NULL;
    }
}

// Renomme le titre d'une colonne spécifique
void renommer_col(COLUMN** liste, int taille){
    int col;
    printf("Saisisez la colonne que vous voulez renommer : ");
    scanf("%d", &col);
    if (col < 0 || col >= taille) {
        printf("Saisissez une colonne valide\n");
        return;
    }
    printf("\nVous voulez modifiez la colonne ayant comme titre %s", liste[col]->titre);
    printf("\nSaisissez le nouveau titre de la colonne : ");
    char titre[20];
    scanf("%19s", titre);

    char *nouveau_titre = calloc(strlen(titre) + 1, sizeof(char));
    strcpy(nouveau_titre, titre);
    free(liste[col]->titre);
    liste[col]->titre = nouveau_titre;

}
