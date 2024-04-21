//
// Created by 33781 on 21/04/2024.
//

#ifndef CDATAFRAME_YE_CHRIST_PP_CDATAFRAME_H
#define CDATAFRAME_YE_CHRIST_PP_CDATAFRAME_H

#include "column.h"

// Structure pour représenter un CDataframe
typedef struct {
    Column **columns; // Tableau dynamique de pointeurs vers des colonnes
    int num_columns;  // Nombre de colonnes dans le CDataframe
    int physical_size; // Taille physique du tableau de pointeurs
} CDataframe;

// Prototypes des fonctions pour un CDataframe
CDataframe* create_dataframe();
void fill_dataframe_from_user_input(CDataframe *df);
void fill_dataframe_hardcoded(CDataframe *df);
void add_column_to_dataframe(CDataframe *df, Column *col);
void print_dataframe(CDataframe *df);
void print_partial_dataframe(CDataframe *df, int limite);
void print_partial_columns(CDataframe *df, int limite);
void delete_dataframe(CDataframe **df);


#endif //CDATAFRAME_YE_CHRIST_PP_CDATAFRAME_H