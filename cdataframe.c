#include "cdataframe.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

CDataframe* create_dataframe() {
    CDataframe *df = (CDataframe*)malloc(sizeof(CDataframe));
    if (df == NULL) return NULL;
    df->columns = (COLUMN**)malloc(REALLOC_SIZE * sizeof(COLUMN*));
    if (df->columns == NULL) {
        free(df);
        return NULL;
    }
    df->num_columns = 0;
    df->physical_size = REALLOC_SIZE;
    return df;
}

void add_column_to_dataframe(CDataframe *df, COLUMN *col) {
    if (df->num_columns >= df->physical_size) {
        df->physical_size += REALLOC_SIZE;
        COLUMN **new_columns = (COLUMN**) realloc(df->columns, df->physical_size * sizeof(COLUMN*));
        if (new_columns == NULL) return;
        df->columns = new_columns;
    }
    df->columns[df->num_columns++] = col;
}

void fill_dataframe_from_user_input(CDataframe *df) {
    if (df == NULL) return;
    int num_cols;
    printf("Entrez le nombre de colonnes a ajouter : ");
    scanf("%d", &num_cols);

    for (int i = 0; i < num_cols; i++) {
        char title[100];
        printf("Entrez le titre de la colonne %d : ", i + 1);
        scanf("%s", title);

        COLUMN *col = create_column(title);
        if (col == NULL) {
            printf("Erreur lors de la creation de la colonne\n");
            return;
        }

        int num_values;
        printf("Entrez le nombre de valeurs a ajouter a la colonne \"%s\" : ", title);
        scanf("%d", &num_values);

        for (int j = 0; j < num_values; j++) {
            int value;
            printf("Entrez la valeur %d pour la colonne \"%s\" : ", j + 1, title);
            scanf("%d", &value);

            if (!insert_value(col, value)) {
                printf("Erreur lors de l'insertion de la valeur dans la colonne \"%s\"\n", title);
                return;
            }
        }
        add_column_to_dataframe(df, col);
        printf("Colonne \"%s\" ajoutee au CDataframe avec succes\n", title);
    }
}

int fill_dataframe_hardcoded(CDataframe *df) {
    // Supprimer le CDataframe existant avant d'ajouter de nouvelles données
    delete_dataframe(&df);

    // Créer un nouveau CDataframe
    df = create_dataframe();
    if (df == NULL) {
        printf("Erreur lors de la création du CDataframe.\n");
        return 0;
    }

    // Ajouter les colonnes avec les données en dur
    COLUMN *col1 = create_column("Age");
    insert_value(col1, 25);
    insert_value(col1, 30);
    insert_value(col1, 22);
    add_column_to_dataframe(df, col1);

    COLUMN *col2 = create_column("Salaire");
    insert_value(col2, 50000);
    insert_value(col2, 60000);
    insert_value(col2, 55000);
    add_column_to_dataframe(df, col2);

    COLUMN *col3 = create_column("Experience");
    insert_value(col3, 5);
    insert_value(col3, 7);
    insert_value(col3, 6);
    add_column_to_dataframe(df, col3);

    return 1;
}


void delete_dataframe(CDataframe **df) {
    if (df && *df) {
        for (int i = 0; i < (*df)->num_columns; i++) {
            delete_column(&(*df)->columns[i]);
        }
        free((*df)->columns);
        free(*df);
        *df = NULL;
    }
}

void print_dataframe(CDataframe *df) {
    if (df == NULL || df->num_columns == 0) {
        printf("Le CDataframe est vide.\n");
        return;
    }

    // Affichage des titres de colonnes sur la première ligne
    printf("%-20s", ""); // Pour l'espace vide en haut à gauche
    for (int i = 0; i < df->num_columns; i++) {
        printf("%-20s", df->columns[i]->title);
    }
    printf("\n");

    // Affichage des données à partir de la deuxième ligne
    int max_rows = 0;
    for (int i = 0; i < df->num_columns; i++) {
        if (df->columns[i]->logical_size > max_rows) {
            max_rows = df->columns[i]->logical_size;
        }
    }

    for (int row = 0; row < max_rows; row++) {
        printf("%-20d", row + 1); // Numéro de ligne
        for (int col = 0; col < df->num_columns; col++) {
            if (row < df->columns[col]->logical_size) {
                printf("%-20d", df->columns[col]->data[row]);
            } else {
                printf("%-20s", ""); // Pour les cellules vides
            }
        }
        printf("\n");
    }
}


void print_partial_dataframe(CDataframe *df, int limite) {
    if (df == NULL) {
        printf("Le CDataframe est vide.\n");
        return;
    }

    printf("Contenu du CDataframe a une limite de lignes: %d\n", limite);

    // Afficher les titres des colonnes
    for (int i = 0; i < df->num_columns; i++) {
        printf("%-20s", df->columns[i]->title);
    }
    printf("\n");

    // Afficher les valeurs des colonnes jusqu'à la limite spécifiée
    for (int j = 0; j < limite; j++) {
        for (int i = 0; i < df->num_columns; i++) {
            printf("[%d] %-17d", j, df->columns[i]->data[j]);
        }
        printf("\n");
    }
}


void print_partial_columns(CDataframe *df, int limite) {
    if (df == NULL) {
        printf("Le CDataframe est vide.\n");
        return;
    }

    printf("Contenu du CDataframe a une limite de colonnes: %d\n", limite);

    // Afficher les titres des colonnes
    for (int i = 0; i < limite && i < df->num_columns; i++) {
        printf("%-20s", df->columns[i]->title);
    }
    printf("\n");

    // Afficher les valeurs des colonnes jusqu'à la limite spécifiée
    for (int j = 0; j < df->columns[0]->logical_size; j++) {
        for (int i = 0; i < limite && i < df->num_columns; i++) {
            printf("[%d] %-17d", j, df->columns[i]->data[j]);
        }
        printf("\n");
    }
}



void add_row(CDataframe *df, int *values) {
    if (df == NULL || values == NULL) return;
    for (int i = 0; i < df->num_columns; i++) {
        insert_value(df->columns[i], values[i]);
    }
}

void remove_row(CDataframe *df, int row_index){
    // Vérifier si le CDataframe existe et si l'index est valide
    if (df == NULL || row_index < 1 || row_index > df->columns[0]->logical_size) {
        printf("Index de ligne invalide.\n");
        return;
    }

    // Parcourir chaque colonne
    for(int i = 0; i < df->num_columns; i++){
        // Vérifier si l'index de ligne est valide pour cette colonne
        if(row_index <= df->columns[i]->logical_size){
            // Décaler les valeurs pour supprimer la ligne
            for(int j = row_index - 1; j < df->columns[i]->logical_size - 1; j++){
                df->columns[i]->data[j] = df->columns[i]->data[j+1];
            }
            // Mettre à jour la taille logique de la colonne
            df->columns[i]->logical_size--;
        }
    }
}


void remove_column(CDataframe *df, int col_index) {
    if (df == NULL || col_index < 0 || col_index >= df->num_columns) return;
    delete_column(&df->columns[col_index]);
    for (int i = col_index; i < df->num_columns - 1; i++) {
        df->columns[i] = df->columns[i + 1];
    }
    df->num_columns--;
}

void rename_column(CDataframe *df, int col_index, const char *new_title) {
    if (df == NULL || col_index < 0 || col_index >= df->num_columns || new_title == NULL) return;
    COLUMN *col = df->columns[col_index];
    free(col->title);
    col->title = strdup(new_title);
}

int value_exists(CDataframe *df, int value) {
    if (df == NULL) return 0;
    for (int i = 0; i < df->num_columns; i++) {
        COLUMN *col = df->columns[i];
        for (int j = 0; j < col->logical_size; j++) {
            if (col->data[j] == value) return 1;
        }
    }
    return 0;
}

void set_value(CDataframe *df, int row, int col, int value) {
    if (df == NULL || row < 0 || col < 0 || col >= df->num_columns || row >= df->columns[col]->logical_size) return;
    df->columns[col]->data[row] = value;
}

void print_column_titles(CDataframe *df) {
    if (df == NULL) return;
    for (int i = 0; i < df->num_columns; i++) {
        printf("Colonne %d: %s\n", i + 1, df->columns[i]->title);
    }
}

int num_rows(CDataframe *df) {
    if (df == NULL || df->num_columns == 0)
        return 0;
    return df->columns[0]->logical_size;
}


int num_cols(CDataframe *df) {
    if (df == NULL)
        return 0;
    return df->num_columns;
}

int count_cells_equal_to_x(CDataframe *df, int x) {
    if (df == NULL) return 0;
    int count = 0;
    for (int i = 0; i < df->num_columns; i++) {
        count += count_values_equal_to_x(df->columns[i], x);
    }
    return count;
}

int count_cells_greater_than_x(CDataframe *df, int x) {
    if (df == NULL) return 0;
    int count = 0;
    for (int i = 0; i < df->num_columns; i++) {
        count += count_values_greater_than_x(df->columns[i], x);
    }
    return count;
}

int count_cells_less_than_x(CDataframe *df, int x) {
    if (df == NULL) return 0;
    int count = 0;
    for (int i = 0; i < df->num_columns; i++) {
        count += count_values_less_than_x(df->columns[i], x);
    }
    return count;
}
