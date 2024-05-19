//
// Created by 33781 on 21/04/2024.
//

#include "cdataframe.h"
#include <stdlib.h>
#include <stdio.h>

// Fonction pour créer un CDataframe vide
CDataframe* create_dataframe() {
    CDataframe *df = (CDataframe*)malloc(sizeof(CDataframe));
    if (df == NULL) {
        return NULL; // Échec d'allocation de mémoire
    }

    // Initialisation des membres du CDataframe
    df->columns = NULL;
    df->num_columns = 0;
    df->physical_size = 0;

    return df;
}
// Ajout d'une colonne au CDataframe
void add_column(CDataframe *df, COLUMN *column) {
    df->num_columns++;
    df->columns = (COLUMN**) realloc(df->columns, df->num_columns * sizeof(COLUMN*));
    df->columns[df->num_columns - 1] = column;
}

// Fonction pour remplir un CDataframe à partir des saisies utilisateur
void fill_dataframe_from_user_input(CDataframe *df) {
    if (df == NULL) {
        return; // Vérifier si le CDataframe existe
    }

    // Demander à l'utilisateur le nombre de colonnes à ajouter
    int num_cols;
    printf("Entrez le nombre de colonnes a ajouter : ");
    scanf("%d", &num_cols);

    // Pour chaque colonne
    for (int i = 0; i < num_cols; i++) {
        char title[100]; // Titre de la colonne
        printf("Entrez le titre de la colonne %d : ", i + 1);
        scanf("%s", title);

        // Créer une nouvelle colonne avec le titre fourni par l'utilisateur
        COLUMN *col = create_column(title);
        if (col == NULL) {
            printf("Erreur lors de la creation de la colonne\n");
            return;
        }

        // Demander à l'utilisateur le nombre de valeurs à ajouter à la colonne
        int num_values;
        printf("Entrez le nombre de valeurs a ajouter a la colonne \"%s\" : ", title);
        scanf("%d", &num_values);

        // Pour chaque valeur
        for (int j = 0; j < num_values; j++) {
            int value;
            printf("Entrez la valeur %d pour la colonne \"%s\" : ", j + 1, title);
            scanf("%d", &value);

            // Insérer la valeur dans la colonne
            if (!insert_value(col, value)) {
                printf("Erreur lors de l'insertion de la valeur dans la colonne \"%s\"\n", title);
                return;
            }
        }

        // Ajouter la colonne remplie au CDataframe
        add_column_to_dataframe(df, col);
        printf("Colonne \"%s\" ajoutee au CDataframe avec succes\n", title);
    }
}

// Fonction pour remplir en dur un CDataframe
int fill_dataframe_hardcoded(CDataframe *df) {
    COLUMN *col1 = create_column("Age");
    insert_value(col1, 25);
    insert_value(col1, 30);
    insert_value(col1, 22);
    add_column(df, col1);

    COLUMN *col2 = create_column("Score");
    insert_value(col2, 88);
    insert_value(col2, 92);
    insert_value(col2, 76);
    add_column(df, col2);
    return 0;
}

// Fonction pour afficher tout le contenu d'un CDataframe
void print_dataframe(CDataframe *df) {
    if (df == NULL) {
        printf("Le CDataframe est vide.\n");
        return;
    }

    printf("Contenu du CDataframe :\n");

    // Parcourir chaque colonne
    for (int i = 0; i < df->num_columns; i++) {
        printf("Colonne %d - %s:\n", i + 1, df->columns[i]->title);
        printf("[Index]\tValeur\n");
        // Afficher les valeurs de la colonne
        for (int j = 0; j < df->columns[i]->logical_size; j++) {
            printf("[%d]\t%d\n", j, df->columns[i]->data[j]);
        }
        printf("\n");
    }
}

// Fonction pour afficher une partie des lignes du CDataframe selon une limite fournie par l'utilisateur
void print_partial_dataframe(CDataframe *df, int limite) {
    if (df == NULL) {
        printf("Le CDataframe est vide.\n");
        return;
    }

    printf("Contenu du CDataframe jusqu'a la limite de lignes : %d\n", limite);

    // Parcourir chaque colonne
    for (int i = 0; i < df->num_columns; i++) {
        printf("Colonne %d - %s:\n", i + 1, df->columns[i]->title);
        printf("[Index]\tValeur\n");
        // Afficher les valeurs de la colonne jusqu'à la limite spécifiée
        for (int j = 0; j < limite && j < df->columns[i]->logical_size; j++) {
            printf("[%d]\t%d\n", j, df->columns[i]->data[j]);
        }
        printf("\n");
    }
}

// Fonction pour afficher une partie des colonnes du CDataframe selon une limite fournie par l'utilisateur
void print_partial_columns(CDataframe *df, int limite) {
    if (df == NULL) {
        printf("Le CDataframe est vide.\n");
        return;
    }

    printf("Contenu du CDataframe jusqu'a la limite de colonnes : %d\n", limite);

    // Parcourir chaque colonne jusqu'à la limite spécifiée
    for (int i = 0; i < df->num_columns && i < limite; i++) {
        printf("Colonne %d - %s:\n", i + 1, df->columns[i]->title);
        printf("[Index]\tValeur\n");
        // Afficher les valeurs de la colonne
        for (int j = 0; j < df->columns[i]->logical_size; j++) {
            printf("[%d]\t%d\n", j, df->columns[i]->data[j]);
        }
        printf("\n");
    }
}

void add_column_to_dataframe(CDataframe *df, COLUMN *col) {
    if (df == NULL || col == NULL) {
        return; // Vérifier si le CDataframe ou la colonne existent
    }

    // Réallouer de l'espace si nécessaire
    if (df->num_columns >= df->physical_size) {
        int new_size = df->physical_size + REALLOC_SIZE;
        COLUMN **new_columns = realloc(df->columns, new_size * sizeof(COLUMN *));
        if (new_columns == NULL) {
            return; // En cas d'échec de ré-allocation de mémoire
        }
        df->columns = new_columns;
        df->physical_size = new_size;
    }

    // Ajouter la colonne au CDataframe
    df->columns[df->num_columns] = col;
    df->num_columns++;
}

void delete_dataframe(CDataframe **df) {
    if (*df == NULL) {
        return; // Vérifier si le CDataframe existe
    }

    // Libérer chaque colonne du CDataframe
    for (int i = 0; i < (*df)->num_columns; i++) {
        delete_column(&((*df)->columns[i]));
    }

    // Libérer le tableau de pointeurs vers les colonnes
    free((*df)->columns);

    // Libérer la structure du CDataframe elle-même
    free(*df);
    *df = NULL;
}