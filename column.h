#ifndef CDATAFRAME_YE_CHRIST_PP_COLUMN_H
#define CDATAFRAME_YE_CHRIST_PP_COLUMN_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define REALLOC_SIZE 256

typedef struct {
    char *title;
    int *data;
    int logical_size;
    int physical_size;
} COLUMN;

COLUMN *create_column(const char *title);
int insert_value(COLUMN *col, int value);
void delete_column(COLUMN **col);
int count_values_greater_than_x(COLUMN *col, int x);
int count_values_less_than_x(COLUMN *col, int x);
int count_values_equal_to_x(COLUMN *col, int x);

#endif // CDATAFRAME_YE_CHRIST_PP_COLUMN_H
