//
<<<<<<< HEAD
// Created by yeemm on 27/03/2024.
//

#include "function.h"
=======
// Created by maiwe on 27/03/2024.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"

COLUMN *create_column(char* title){
    COLUMN * col = (COLUMN*)malloc(sizeof(COLUMN));
    if(col = NULL){
        return NULL;
    }

    col->title = (char *)malloc(strlen(title) +1);
    strcpy(col-> title,title);
}
>>>>>>> 88e6451 (Commencement de la première fonction COLUMN*create_column(char* title))
