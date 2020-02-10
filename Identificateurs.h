#ifndef DEF_IDENTIFICATEURS_H
#define DEF_IDENTIFICATEURS_H

union values{
    char* valuesCst;
    int dimensionTab;
    char* adresseVar;
    char* modePassageParam;
    int nbParamFonctionProcedure;
};

typedef struct Identificateurs {
    char* type;
    char* nomIdent;
    char* typeValeurRetourFonction;
    union values valeurType;
}Identificateurs;

Identificateurs* identificateurs;

void setNameIdent(char* valeur, Identificateurs identificateurs);
char* getNameIdent(Identificateurs identificateurs);
void setTypeIdent(char* type, Identificateurs identificateurs);
char* getTypeIdent(Identificateurs identificateurs);
void setValeurType(char* valeur, Identificateurs identificateurs);
void setTypeValeurRetourFonction(char* typeValeurRetour, Identificateurs identificateurs);
char* getValuesCst(Identificateurs identificateurs);
int getDimensionTab(Identificateurs identificateurs);
char* getAdresseVar(Identificateurs identificateurs);
char* getModePassageParam(Identificateurs identificateurs);
int getNbParamFonctionProcedure(Identificateurs identificateurs);
char* getType(Identificateurs identificateurs);


#endif //COMPILATIONPROJECT_IDENTIFICATEURS_H
