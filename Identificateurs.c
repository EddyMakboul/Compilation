#include "Identificateurs.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void setNameIdent(char* valeur, Identificateurs i){
    //i.nomIdent = malloc(sizeof(char)*strlen(valeur)+1);
    i.nomIdent = strcpy(i.nomIdent, valeur);
}

char* getNameIdent(Identificateurs i){
    return i.nomIdent;
}

void setTypeIdent(char* type, Identificateurs i){
    //i.type = malloc(sizeof(char)*strlen(type)+1);
    i.type = strcpy(i.type, type);
}