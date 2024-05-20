#ifndef CDATAFRAME_YE_CHRIST_PP_CDATAFRAME_H
#define CDATAFRAME_YE_CHRIST_PP_CDATAFRAME_H
#include "column.h"

typedef struct {
    COLUMN **columns;
    int num_columns;
    int physical_size;
} CDataframe;

CDataframe* create_dataframe();
void fill_dataframe_from_user_input(CDataframe *df);
int fill_dataframe_hardcoded(CDataframe *df);
void add_column_to_dataframe(CDataframe *df, COLUMN *col);
void print_dataframe(CDataframe *df);
void print_partial_dataframe(CDataframe *df, int limite);
void print_partial_columns(CDataframe *df, int limite);
void delete_dataframe(CDataframe **df);
void add_row(CDataframe *df, int *values);
void remove_row(CDataframe *df, int row_index);
void remove_column(CDataframe *df, int col_index);
void rename_column(CDataframe *df, int col_index, char *new_title);
int value_exists(CDataframe *df, int value);
void set_value(CDataframe *df, int row, int col, int value);
void print_column_titles(CDataframe *df);
int num_rows(CDataframe *df);
int num_cols(CDataframe *df);
int count_cells_equal_to_x(CDataframe *df, int x);
int count_cells_greater_than_x(CDataframe *df, int x);
int count_cells_less_than_x(CDataframe *df, int x);

#endif //CDATAFRAME_YE_CHRIST_PP_CDATAFRAME_H
