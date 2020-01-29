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

char* getTypeIdent(Identificateurs i){
    return i.type;
}

void setValeurType(char* valeur, Identificateurs i){
    if(strcmp(i.type, "cst") == 0)
    {
        i.valeurType.valuesCst = malloc(sizeof(char)*strlen(valeur));
        i.valeurType.valuesCst = strcpy(i.valeurType.valuesCst, valeur);
    }
    else if(strcmp(i.type, "tableau")==0){
        i.valeurType.dimensionTab = atoi(valeur);
    }
    else if(strcmp(i.type, "variable")==0)
    {
        i.valeurType.adresseVar = malloc(sizeof(char)*strlen(valeur));
        i.valeurType.adresseVar = strcpy(i.valeurType.adresseVar, valeur);
    }
    else if(strcmp(i.type, "param") == 0)
    {
        i.valeurType.modePassageParam = malloc(sizeof(char)*strlen(valeur));
        i.valeurType.modePassageParam = strcpy(i.valeurType.modePassageParam, valeur);
    }
    else{
        i.valeurType.nbParamFonctionProcedure = atoi(valeur);
    }
}

void setTypeValeurRetourFonction(char* typeValeurRetour, Identificateurs i){
    i.typeValeurRetourFonction = malloc(sizeof(char)*strlen(typeValeurRetour));
    i.typeValeurRetourFonction = strcpy(i.typeValeurRetourFonction, typeValeurRetour);
}

char* getValuesCst(Identificateurs i){
    return i.valeurType.valuesCst;
}

int getDimensionTab(Identificateurs i){
    return i.valeurType.dimensionTab;
}

char* getAdresseVar(Identificateurs i){
    return i.valeurType.adresseVar;
}

char* getModePassageParam(Identificateurs i){
    return i.valeurType.modePassageParam;
}

int getNbParamFonctionProcedure(Identificateurs i){
    return i.valeurType.nbParamFonctionProcedure;
}

char* getType(Identificateurs i){
    return i.type;
}