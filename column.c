//
// Created by 33781 on 21/04/2024.
//

#include "column.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define REALLOC_SIZE 256

Column *create_column(char *title) {
    // Allocation de mémoire pour la colonne
    Column *col = (Column *)malloc(sizeof(Column));
    if (col == NULL) {
        return NULL; // En cas d'échec de l'allocation de mémoire
    }

    // Initialisation des attributs de la colonne
    col->title = strdup(title); // Duplication de la chaîne de titre
    col->data = NULL; // Initialisation du tableau de données à NULL
    col->logical_size = 0; // Taille logique initialisée à 0
    col->physical_size = 0; // Taille physique initialisée à 0

    return col;
}

// Fonction pour insérer une valeur dans une colonne
int insert_value(Column *col, int value) {
    if (col == NULL) {
        return 0; // Vérifier si la colonne existe
    }

    // Vérifier si la taille physique est épuisée ou nulle
    if (col->physical_size == 0 || col->logical_size >= col->physical_size) {
        // Réallouer de l'espace pour le tableau de données
        int new_size = col->physical_size + REALLOC_SIZE;
        int *new_data = (int *)realloc(col->data, new_size * sizeof(int));
        if (new_data == NULL) {
            return 0; // En cas d'échec de ré-allocation de mémoire
        }
        col->data = new_data;
        col->physical_size = new_size;
    }

    // Insérer la valeur dans le tableau de données
    col->data[col->logical_size] = value;
    col->logical_size++;

    return 1; // La valeur a été ajoutée avec succès
}

// Fonction pour libérer l'espace alloué par une colonne
void delete_column(Column **col) {
    if (*col == NULL) {
        return; // Vérifier si la colonne existe
    }

    // Libérer le titre de la colonne
    free((*col)->title);
    (*col)->title = NULL;

    // Libérer le tableau de données de la colonne
    free((*col)->data);
    (*col)->data = NULL;

    // Libérer la structure de la colonne elle-même
    free(*col);
    *col = NULL;
}

// Fonction pour afficher le contenu d'une colonne
void print_col(Column *col) {
    if (col == NULL) {
        printf("La colonne est vide.\n");
        return; // Vérifier si la colonne existe
    }

    printf("Contenu de la colonne \"%s\":\n", col->title);
    for (int i = 0; i < col->logical_size; i++) {
        printf("[%d] %d\n", i, col->data[i]);
    }
}

// Fonction pour retourner le nombre d'occurrences d'une valeur dans une colonne
int count_occurrences(Column *col, int x) {
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
int get_value_at_position(Column *col, int x) {
    if (col == NULL || x < 0 || x >= col->logical_size) {
        // Vérifier si la colonne existe et si la position est valide
        return -1; // Retourner une valeur indiquant une erreur ou une valeur non trouvée
    }

    return col->data[x];
}

// Fonction pour retourner le nombre de valeurs supérieures à x dans une colonne
int count_values_greater_than_x(Column *col, int x) {
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

int count_values_less_than_x(Column *col, int x) {
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
int count_values_equal_to_x(Column *col, int x) {
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