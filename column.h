#ifndef CDATAFRAME_YE_CHRIST_PP_COLUMN_H
#define CDATAFRAME_YE_CHRIST_PP_COLUMN_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define REALLOC_SIZE 256

// Structure pour représenter une colonne de données
typedef struct {
    char *title;        // Titre de la colonne
    int *data;          // Tableau dynamique pour stocker les données
    int logical_size;   // Taille logique (nombre de valeurs insérées)
    int physical_size;  // Taille physique (nombre de cases allouées)
} COLUMN;

COLUMN *create_column(char *title);
int insert_value(COLUMN *col, int value);
void delete_column(COLUMN **col);
void print_col(COLUMN *col);

// Autres fonctions
int count_occurrences(COLUMN *col, int x);
int get_value_at_position(COLUMN *col, int position);
int count_values_greater_than_x(COLUMN *col, int x);
int count_values_less_than_x(COLUMN *col, int x);
int count_values_equal_to_x(COLUMN *col, int x);

#endif // CDATAFRAME_YE_CHRIST_PP_COLUMN_H
