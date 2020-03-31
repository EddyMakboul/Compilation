#include "Identificateurs.h"
#include <string.h>

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

int containsArgs(char* nameArgs, Identificateurs identifi){
    for(int i=0; i<identifi.nbArg; i++){
        if(strcmp(nameArgs, identifi.nameArgs[i])==0)
            return i;
    }
    return -1;
}