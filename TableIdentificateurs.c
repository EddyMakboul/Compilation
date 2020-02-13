#include "TableIdentificateurs.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void init(TableIdentificateurs* tableIdent){
    tableIdent->length=0;
    tableIdent->actualLength=0;
}

void reallouer(TableIdentificateurs* tableIdent){
    if(tableIdent->length==0) {
        tableIdent->length = 1;
        tableIdent->tableIdentificateurs = malloc(sizeof(Identificateurs)*tableIdent->length);
    }
    else
        tableIdent->length*=2;
    tableIdent->tableIdentificateurs = realloc(tableIdent->tableIdentificateurs, sizeof(Identificateurs)*tableIdent->length);
}

void addIdentificateurs(TableIdentificateurs* tableIdent, Identificateurs i){
    if(tableIdent->actualLength==tableIdent->length)
        reallouer(tableIdent);
    tableIdent->tableIdentificateurs[tableIdent->actualLength] = i;
    tableIdent->actualLength++;
}

int contains(TableIdentificateurs* tableIdent, char* i){
    for(int index=0; index<tableIdent->actualLength; index++)
    {
        if(strcmp(tableIdent->tableIdentificateurs[index].nomIdent,i)==0)
            return index;
    }

    return -1;
}