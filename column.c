#include "column.h"

COLUMN *create_column(const char *title) {
    COLUMN *col = (COLUMN*)malloc(sizeof(COLUMN));
    if (col == NULL) return NULL;
    col->title = strdup(title);
    col->data = NULL;
    col->logical_size = 0;
    col->physical_size = 0;
    return col;
}

int insert_value(COLUMN* col, int value) {
    if (col->logical_size == col->physical_size) {
        col->physical_size += REALLOC_SIZE;
        int *new_data = (int*) realloc(col->data, col->physical_size * sizeof(int));
        if (new_data == NULL) return 0;
        col->data = new_data;
    }
    col->data[col->logical_size++] = value;
    return 1;
}

void delete_column(COLUMN **col) {
    if (col && *col) {
        free((*col)->title);
        free((*col)->data);
        free(*col);
        *col = NULL;
    }
}


int count_values_greater_than_x(COLUMN *col, int x) {
    if (col == NULL) return 0;
    int count = 0;
    for (int i = 0; i < col->logical_size; i++) {
        if (col->data[i] > x) count++;
    }
    return count;
}

int count_values_less_than_x(COLUMN *col, int x) {
    if (col == NULL) return 0;
    int count = 0;
    for (int i = 0; i < col->logical_size; i++) {
        if (col->data[i] < x) count++;
    }
    return count;
}

int count_values_equal_to_x(COLUMN *col, int x) {
    if (col == NULL) return 0;
    int count = 0;
    for (int i = 0; i < col->logical_size; i++) {
        if (col->data[i] == x) count++;
    }
    return count;
}

