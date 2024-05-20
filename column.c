#include "column.h"

/* Créer une nouvelle colonne avec le titre spécifié,
 * prend en paramètres une str qui représente le titre de la colonne*/
COLUMN *create_column(char *title) {
    COLUMN *col = (COLUMN*)malloc(sizeof(COLUMN));
    if (col == NULL) return NULL;
    col->title = strdup(title); // Copie le titre spécifié dans la nouvelle colonne
    col->data = NULL;
    col->logical_size = 0;
    col->physical_size = 0;
    return col; //retourne un pointeur vers la nouvelle colonne créée.
}

/* Insère une valeur dans une colonne,
 * retourne 1 si réussi sinon 0*/
int insert_value(COLUMN* col, int value) {
    if (col->logical_size == col->physical_size) {
        col->physical_size += REALLOC_SIZE;
        int *new_data = (int*) realloc(col->data, col->physical_size * sizeof(int));
        if (new_data == NULL)
            return 0;
        col->data = new_data; //pointeur vers données
    }
    col->data[col->logical_size++] = value; //insertion de la valeur et maj de la TL
    return 1;
}

/* Supprime une colonne */
void delete_column(COLUMN **col) { //Pointeur vers un pointeur de colonne
    if (col && *col) {
        free((*col)->title); //libère la mémoire alloué pour le titre,donnée et structure de la colonne.
        free((*col)->data);
        free(*col);
        *col = NULL; //affecte null au poinnteur pour éviter les problèmes
    }
}

/* Compte le nombre de valeurs > à x dans une col*/
int count_values_greater_than_x(COLUMN *col, int x) {
    if (col == NULL)
        return 0; //si la col existe, on initialise le compteur, on parcourt les valeurs et incrémente cpt si val est > à x
    int count = 0;
    for (int i = 0; i < col->logical_size; i++) {
        if (col->data[i] > x)
            count++;
    }
    return count; //retourne le nombre de val > à x dans la colonne
}

/* Compte le nombre de valeurs < à x dans une col*/
int count_values_less_than_x(COLUMN *col, int x) {
    if (col == NULL)
        return 0; //si la col existe, on initialise le compteur, on parcourt les valeurs et incrémente cpt si val est < à x
    int count = 0;
    for (int i = 0; i < col->logical_size; i++) {
        if (col->data[i] < x)
            count++;
    }
    return count; //retourne le nombre de val < à x dans la colonne
}

/* Compte le nombre de valeurs = à x dans une col*/
int count_values_equal_to_x(COLUMN *col, int x) {
    if (col == NULL)
        return 0; //si la col existe, on initialise le compteur, on parcourt les valeurs et incrémente cpt si val est = à x
    int count = 0;
    for (int i = 0; i < col->logical_size; i++) {
        if (col->data[i] == x)
            count++;
    }
    return count; //retourne le nombre de val = à x dans la colonne
}

