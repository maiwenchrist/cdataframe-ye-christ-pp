#include "column.h"

COLUMN *create_column(char *title) {
    COLUMN * col = (COLUMN*)malloc(sizeof(COLUMN));
    col-> title = title;
    col->data = NULL;
    col->logical_size = 0;
    col-> physical_size = 0;
    return col;
}

int insert_value(COLUMN* col, int value){
    if (col->logical_size == col->physical_size) {
        col->physical_size += REALLOC_SIZE;
        int *new_data = (int*) realloc(col->data, col->physical_size * sizeof(int));
        if (new_data == NULL) {
            return 0; // Réallocation échouée
        }
        col->data = new_data;
    }
    col->data[col->logical_size++] = value;
    return 1;
}

void delete_column(COLUMN **col) {
    if(col && *col){
        free((*col)->title);
        free((*col)->data);
        free((*col));
        *col =NULL;
    }
}
void print_col(COLUMN* col){
    printf("affichage de la colonne  %s\n",col->title);
    for(int i = 0; i<col->logical_size; i++){
        printf("[%d]  %d\n",i,col->data[i]);
    }
    printf("\n");
}

int count_occurrences(COLUMN *col, int x) {
    if (col == NULL) {
        return 0; // Vérifier si la colonne existe
    }

    int count = 0;
    for (int i = 0; i < col->logical_size; i++) {
        if (col->data[i] == x) {
            count++;
        }
    }

    return count;
}

// Fonction pour retourner la valeur à la position x dans une colonne
int get_value_at_position(COLUMN *col, int x) {
    if (col == NULL || x < 0 || x >= col->logical_size) {
        // Vérifier si la colonne existe et si la position est valide
        return -1; // Retourner une valeur indiquant une erreur ou une valeur non trouvée
    }

    return col->data[x];
}

// Fonction pour retourner le nombre de valeurs supérieures à x dans une colonne
int count_values_greater_than_x(COLUMN *col, int x) {
    if (col == NULL) {
        return 0; // Vérifier si la colonne existe
    }

    int count = 0;
    for (int i = 0; i < col->logical_size; i++) {
        if (col->data[i] > x) {
            count++;
        }
    }

    return count;
}

int count_values_less_than_x(COLUMN *col, int x) {
    if (col == NULL) {
        return 0; // Vérifier si la colonne existe
    }

    int count = 0;
    for (int i = 0; i < col->logical_size; i++) {
        if (col->data[i] < x) {
            count++;
        }
    }

    return count;
}

// Fonction pour retourner le nombre de valeurs égales à x dans une colonne
int count_values_equal_to_x(COLUMN *col, int x) {
    if (col == NULL) {
        return 0; // Vérifier si la colonne existe
    }

    int count = 0;
    for (int i = 0; i < col->logical_size; i++) {
        if (col->data[i] == x) {
            count++;
        }
    }
    return count;
}