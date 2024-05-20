#include "cdataframe.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Créer un dataframe (df)*/
CDataframe* create_dataframe() {
    CDataframe *df = (CDataframe*)malloc(sizeof(CDataframe));
    if (df == NULL)
        return NULL; //NULL en cas d'échec de l'allocation de mémoire.
    df->columns = (COLUMN**)malloc(REALLOC_SIZE * sizeof(COLUMN*));
    if (df->columns == NULL) {
        free(df);
        return NULL; //NULL en cas d'échec de l'allocation de mémoire.
    }
    df->num_columns = 0; // Initialise le nombre de colonnes et la taille physique du df
    df->physical_size = REALLOC_SIZE;
    return df; //retourne pointeur vers le nouveau df créé.
}

/* Ajoute une colonne au df*/
void add_column_to_dataframe(CDataframe *df, COLUMN *col) { //Pointeur vers le df et pointeur vers la colonne à ajouter.
    if (df->num_columns >= df->physical_size) {
        df->physical_size += REALLOC_SIZE;
        COLUMN **new_columns = (COLUMN**) realloc(df->columns, df->physical_size * sizeof(COLUMN*));
        if (new_columns == NULL)
            return;
        df->columns = new_columns; //maj du tab pointeur de col
    }
    df->columns[df->num_columns++] = col; //ajoute col et incrémente le df
}

/* Remplit le df par l'utilisateur*/
void fill_dataframe_from_user_input(CDataframe *df) { //pointeur vers le df à remplir
    if (df == NULL) //vérifie si df existe
        return;
    int num_cols;
    printf("Entrez le nombre de colonnes a ajouter : ");
    scanf("%d", &num_cols);//saisie nb col

    for (int i = 0; i < num_cols; i++) {
        char title[100];
        printf("Entrez le titre de la colonne %d : ", i + 1);
        scanf("%s", title); //saisie titre col

        COLUMN *col = create_column(title);
        if (col == NULL) {
            printf("Erreur lors de la creation de la colonne\n");
            return;
        }

        int num_values;
        printf("Entrez le nombre de valeurs a ajouter a la colonne \"%s\" : ", title);
        scanf("%d", &num_values); //saisie nb val

        for (int j = 0; j < num_values; j++) {
            int value;
            printf("Entrez la valeur %d pour la colonne \"%s\" : ", j + 1, title);
            scanf("%d", &value); //saisie valeur pour col

            if (!insert_value(col, value)) {
                printf("Erreur lors de l'insertion de la valeur dans la colonne \"%s\"\n", title);
                return;
            }
        }
        add_column_to_dataframe(df, col); //ajoute la col au df
        printf("Colonne \"%s\" ajoutee au CDataframe avec succes\n", title);
    }
}

/* Remplit le df avec des données en dur*/
int fill_dataframe_hardcoded(CDataframe *df) { //pointeur vers le df à remplir
    delete_dataframe(&df); // Supprimer le df existant avant d'ajouter de nouvelles données
    df = create_dataframe(); // Créer un nouveau df
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

/* Supprime un df */
void delete_dataframe(CDataframe **df) { //pointeur vers un pointeur de df
    if (df && *df) { //vérifie si le df et le pointeur de df existe
        for (int i = 0; i < (*df)->num_columns; i++) {
            delete_column(&(*df)->columns[i]);
        }
        free((*df)->columns);
        free(*df);
        *df = NULL; //affecter null pour éviter les problèmes
    }
}

/* Affiche le contenu du df*/
void print_dataframe(CDataframe *df) { //pointeur vers un df
    if (df == NULL || df->num_columns == 0) {
        printf("Le CDataframe est vide.\n");
        return;
    }

    // Affichage des titres de colonnes sur la première ligne
    printf("%-20s", ""); // - texte alligné à gauche, 20 largeur du champ
    for (int i = 0; i < df->num_columns; i++) {
        printf("%-20s", df->columns[i]->title);
    }
    printf("\n");

    // Trouve le nombre maximal de lignes parmi toutes les colonnes
    int max_rows = 0;
    for (int i = 0; i < df->num_columns; i++) {
        if (df->columns[i]->logical_size > max_rows) {
            max_rows = df->columns[i]->logical_size;
        }
    }

    // Affichage des données à partir de la deuxième ligne
    for (int row = 0; row < max_rows; row++) {
        printf("%-20d", row + 1); // Numéro de ligne
        for (int col = 0; col < df->num_columns; col++) {
            if (row < df->columns[col]->logical_size) {
                printf("%-20d", df->columns[col]->data[row]); //valeur de col
            } else {
                printf("%-20s", ""); // Pour les cellules vides
            }
        }
        printf("\n");
    }
}

/* Affiche une partie du df jusqu'à limite de lignes spécifiés */
void print_partial_dataframe(CDataframe *df, int limite) { //pointeur vers le df
    if (df == NULL) {
        printf("Le CDataframe est vide.\n");
        return;
    }

    // Afficher les titres des colonnes
    for (int i = 0; i < df->num_columns; i++) {
        printf("%-20s", df->columns[i]->title);
    }
    printf("\n");

    // Afficher les valeurs des colonnes jusqu'à la limite spécifiée
    for (int j = 0; j < limite; j++) {
        for (int i = 0; i < df->num_columns; i++) {
            printf("[%d] %-17d", j, df->columns[i]->data[j]); // Affiche l'indice de ligne et les valeurs des colonnes
        }
        printf("\n");
    }
}

/* Affiche une partie du df jusqu'à limite de colonnes spécifiés */
void print_partial_columns(CDataframe *df, int limite) { //pointeur vers le df
    if (df == NULL) {
        printf("Le CDataframe est vide.\n");
        return;
    }
    // Afficher les titres des colonnes
    for (int i = 0; i < limite && i < df->num_columns; i++) {
        printf("%-20s", df->columns[i]->title);
    }
    printf("\n");

    // Afficher les valeurs des colonnes jusqu'à la limite spécifiée
    for (int j = 0; j < df->columns[0]->logical_size; j++) {
        for (int i = 0; i < limite && i < df->num_columns; i++) {
            printf("[%d] %-17d", j, df->columns[i]->data[j]); // Affiche l'indice de ligne et les valeurs des colonnes
        }
        printf("\n");
    }
}

/* Ajoute une nouvelle ligne au df avec les valeurs spécifiées.*/
void add_row(CDataframe *df, int *values) { //pointeur vers le df, tab des valeurs à ajouter à la nouvelle ligne
    if (df == NULL || values == NULL) //vérifie si les valeurs sont valides
        return;
    for (int i = 0; i < df->num_columns; i++) { //parcourt dans chaque colonne
        insert_value(df->columns[i], values[i]); //insère la valeur dans la colonne qui correspond
    }
}

/* Supprime une ligne du df à l'index choisi*/
void remove_row(CDataframe *df, int row_index){ //pointeur vers df, index de la ligne à supprimer
    if (df == NULL || row_index < 1 || row_index > df->columns[0]->logical_size) { // Vérifier si le df existe et si l'index est valide
        printf("Index de ligne invalide.\n");
        return;
    }
    for(int i = 0; i < df->num_columns; i++){ // Parcourir chaque colonne
        if(row_index <= df->columns[i]->logical_size){ // Vérifier si l'index de ligne est valide pour cette colonne
            for(int j = row_index - 1; j < df->columns[i]->logical_size - 1; j++){ // Décaler les valeurs pour supprimer la ligne
                df->columns[i]->data[j] = df->columns[i]->data[j+1];
            }
            df->columns[i]->logical_size--; // Mettre à jour la taille logique de la colonne
        }
    }
}

/* Supprime une colonne du df à l'index choisi */
void remove_column(CDataframe *df, int col_index) { //pointeur vers df, index de la colonne à supprimer
    if (df == NULL || col_index < 0 || col_index >= df->num_columns) // Vérifier si le df existe et si l'index est valide
        return;
    delete_column(&df->columns[col_index]); // Supprime la colonne à l'index choisi
    for (int i = col_index; i < df->num_columns - 1; i++) { //Décaler les valeurs pour remplir l'espace de la colonne supprimée
        df->columns[i] = df->columns[i + 1];
    }
    df->num_columns--; // Met à jour le nombre de colonnes dans le df
}

/* Renomme la colonne à l'index choisi*/
void rename_column(CDataframe *df, int col_index, char *new_title) { //pointeur vers le df, idex de la colonne à renommer, nouveau titre
    if (df == NULL || col_index < 0 || col_index >= df->num_columns || new_title == NULL)
        return;
    COLUMN *col = df->columns[col_index]; //accès à la colonne à renommer
    free(col->title); //libère l'ancien titre
    col->title = strdup(new_title); // Copie le nouveau titre de colonne pour qu'elle reste valable même à la fin de l'exécution
}

/* Vérifie si une valeur existe dans le df*/
int value_exists(CDataframe *df, int value) { //pointeur vers df, val à rechercher
    if (df == NULL) //vérifie si le df existe
        return 0;
    for (int i = 0; i < df->num_columns; i++) { //parcourt chaque col
        COLUMN *col = df->columns[i];
        for (int j = 0; j < col->logical_size; j++) { //parcourt chaque val
            if (col->data[j] == value) //vérifie si la valeur existe
                return 1;
        }
    }
    return 0;
}

/* Définit une valeur à une position spécifique dans le df. */
void set_value(CDataframe *df, int row, int col, int value) { //pointeur vers df, index ligne, col, val à définir
    if (df == NULL || row < 0 || col < 0 || col >= df->num_columns || row >= df->columns[col]->logical_size) //vérifie si df existe dans ligne, col, et s'ils sont valides
        return;
    df->columns[col]->data[row] = value; // Définit la valeur à la position spécifiée dans le df
}

/*Affiche les titres des colonnes du df*/
void print_column_titles(CDataframe *df) { //pointeur vers le df
    if (df == NULL)
        return;
    for (int i = 0; i < df->num_columns; i++) {
        printf("Colonne %d: %s\n", i + 1, df->columns[i]->title); //parcourt chaque colonne et affiche le titre
    }
}

/* Renvoie le nb de lignes du df */
int num_rows(CDataframe *df) { //pointeur vers le df
    if (df == NULL || df->num_columns == 0) //vérifie si df existe et qu'il y a au moins 1 col
        return 0;
    int max_rows = 0;

    for (int i = 0; i < df->num_columns; i++) { // Parcourt chaque colonne du dataframe
        if (df->columns[i]->logical_size > max_rows) { // Met à jour le nombre maximal de lignes
            max_rows = df->columns[i]->logical_size;
        }
    }
    return max_rows;
}

/* Renvoie le nb de col du df */
int num_cols(CDataframe *df) { //pointeur vers df
    if (df == NULL)
        return 0;
    return df->num_columns;
}

/* Compte le nb de cellules dans le df ayant une valeur égale à x. */
int count_cells_equal_to_x(CDataframe *df, int x) { //pointeur vers df, valeur à comparer
    if (df == NULL)
        return 0;
    int count = 0;
    for (int i = 0; i < df->num_columns; i++) {
        count += count_values_equal_to_x(df->columns[i], x);
    }
    return count;
}

/* Compte le nb de cellules dans le df ayant une valeur supérieur à x. */
int count_cells_greater_than_x(CDataframe *df, int x) { //pointeur vers df, valeur à comparer
    if (df == NULL)
        return 0;
    int count = 0;
    for (int i = 0; i < df->num_columns; i++) {
        count += count_values_greater_than_x(df->columns[i], x);
    }
    return count;
}

/* Compte le nb de cellules dans le df ayant une valeur inférieur à x. */
int count_cells_less_than_x(CDataframe *df, int x) { //pointeur vers df, valeur à comparer
    if (df == NULL)
        return 0;
    int count = 0;
    for (int i = 0; i < df->num_columns; i++) {
        count += count_values_less_than_x(df->columns[i], x);
    }
    return count;
}
