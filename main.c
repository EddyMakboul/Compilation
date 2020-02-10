#include "Analyseur.h"
#include <stdlib.h>

int main(int argc, char* argv[]) {
    TableIdentificateurs* tableIdent;
    tableIdent = malloc(sizeof(TableIdentificateurs));
    //analyseur_lexical(argv[1], tableIdent);
    printf("------------\n");
    analyseur_syntaxique(argv[1], tableIdent);
    printf("------------\n");
    for(int j=0; j<tableIdent->actualLength; j++)
    {
        printf("%s %s\n", tableIdent->tableIdentificateurs[j].nomIdent, tableIdent->tableIdentificateurs[j].type);
    }
    return 0;
}
