#ifndef DEF_IDENTIFICATEURS_H
#define DEF_IDENTIFICATEURS_H


typedef struct Identificateurs {
    char* type;
    char* nomIdent;
    int typc;
    int valent;
    char* valch;
    int nbArg;
    char** nameArgs;
    int* args;
    int start;
    int end;
    int hasReturn;
    int valueReturn;
}Identificateurs;

Identificateurs* identificateurs;

void setNameIdent(char* valeur, Identificateurs identificateurs);
char* getNameIdent(Identificateurs identificateurs);
void setTypeIdent(char* type, Identificateurs identificateurs);
int containsArgs(char* nameArgs, Identificateurs identificateurs);


#endif //COMPILATIONPROJECT_IDENTIFICATEURS_H
