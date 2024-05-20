#ifndef CDATAFRAME_YE_CHRIST_PP_CDATAFRAME_H
#define CDATAFRAME_YE_CHRIST_PP_CDATAFRAME_H

#include "column.h"

// Structure pour représenter un CDataframe
typedef struct {
    COLUMN **columns; // Tableau dynamique de pointeurs vers des colonnes
    int num_columns;  // Nombre de colonnes dans le CDataframe
    int physical_size; // Taille physique du tableau de pointeurs
} CDataframe;

// Prototypes des fonctions pour un CDataframe
// Alimentation
CDataframe* create_dataframe();
void fill_dataframe_from_user_input(CDataframe *df);
int fill_dataframe_hardcoded(CDataframe *df);

//Affichage
void print_dataframe(CDataframe *df);
void print_partial_dataframe(CDataframe *df, int limite);
void print_partial_columns(CDataframe *df, int limite);
void delete_dataframe(CDataframe **df);

//Operation usuelles
void add_row(CDataframe *df, int * values);
void remove_row(CDataframe *df, int row_index);
void add_column_to_dataframe(CDataframe *df, COLUMN *col);
void remove_col(CDataframe *df,  int col_index);
void rename_col(COLUMN *col, char *new_title);
int value_exists(CDataframe *cdf, int value);
void set_value(CDataframe *cdf, int row, int col, int value);
void print_column_titles(CDataframe *cdf);

#endif //CDATAFRAME_YE_CHRIST_PP_CDATAFRAME_H
