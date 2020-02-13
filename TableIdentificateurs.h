#ifndef DEF_TABLEIDENTIFICATEURS_H
#define DEF_TABLEIDENTIFICATEURS_H
#include "Identificateurs.h"

typedef struct{
    Identificateurs* tableIdentificateurs;
    int length;
    int actualLength;
} TableIdentificateurs;

void init(TableIdentificateurs* tableIdent);
void reallouer(TableIdentificateurs* tableIdent);
void addIdentificateurs(TableIdentificateurs* tableIdent, Identificateurs ident);
int contains(TableIdentificateurs* tableIdent, char* ident);

#endif //COMPILATIONPROJECT_TABLEIDENTIFICATEURS_H
