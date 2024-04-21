//
// Created by 33781 on 21/04/2024.
//

#ifndef CDATAFRAME_YE_CHRIST_PP_COLUMN_H
#define CDATAFRAME_YE_CHRIST_PP_COLUMN_H
#define REALLOC_SIZE 256
// Structure pour représenter une colonne de données
typedef struct {
    char *title; // Titre de la colonne
    int *data;   // Tableau dynamique pour stocker les données
    int logical_size; // Taille logique (nombre de valeurs insérées)
    int physical_size; // Taille physique (nombre de cases allouées)
} Column;

// Prototype de la fonction
Column *create_column(char *title);

// Prototype de la fonction pour insérer une valeur dans une colonne
int insert_value(Column *col, int value);

// Prototype de la fonction pour libérer l'espace alloué par une colonne
void delete_column(Column **col);

// Prototype de la fonction pour afficher le contenu d'une colonne
void print_col(Column *col);

// Prototype de la fonction pour retourner le nombre d'occurrences d'une valeur dans une colonne
int count_occurrences(Column *col, int x);

// Prototype de la fonction pour retourner la valeur à la position x dans une colonne
int get_value_at_position(Column *col, int x);

// Prototype de la fonction pour retourner le nombre de valeurs supérieures à x dans une colonne
int count_values_greater_than_x(Column *col, int x);

// Prototype de la fonction pour retourner le nombre de valeurs inférieures à x dans une colonne
int count_values_less_than_x(Column *col, int x);

// Prototype de la fonction pour retourner le nombre de valeurs égales à x dans une colonne
int count_values_equal_to_x(Column *col, int x);


#endif //CDATAFRAME_YE_CHRIST_PP_COLUMN_H
