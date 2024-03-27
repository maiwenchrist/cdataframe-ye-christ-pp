#ifndef CDATAFRAME_YE_CHRIST_PP_FUNCTION_H
#define CDATAFRAME_YE_CHRIST_PP_FUNCTION_H

#define REALOC_SIZE 256

typedef struct{
    char * title;
    int * vals;
    int size_phy;
    int size_log;
}COLUMN;

COLUMN *create_column(char* title);


#endif //CDATAFRAME_YE_CHRIST_PP_FUNCTION_H
