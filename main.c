#include "Analyseur.h"
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
    //TableIdentificateurs* tableIdent;
    //tableIdent = malloc(sizeof(TableIdentificateurs));
    //analyseur_lexical(argv[1], tableIdent);
    printf("------------\n");
    analyseur_syntaxique(argv[1]);
    printf("------------\n");
    /*for(int j=0; j<tableIdent->actualLength; j++)
    {
        printf("%s %s ", tableIdent->tableIdentificateurs[j].nomIdent, tableIdent->tableIdentificateurs[j].type);
        if(strcmp(tableIdent->tableIdentificateurs[j].type, "CONST")==0 && tableIdent->tableIdentificateurs[j].typc==1)
            printf("%s\n", tableIdent->tableIdentificateurs[j].valch);
        else
            printf("%d\n", tableIdent->tableIdentificateurs[j].valent);
    }*/
    return 0;
}
