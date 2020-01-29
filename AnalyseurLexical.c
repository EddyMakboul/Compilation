#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#include "AnalyseurLexical.h"
#include "Identificateurs.h"

void erreur(int numErreur){
    switch(numErreur){
        case 0:
            printf("fin de fichier atteinte.\n");
            break;
        case 1:
            printf("Ce nombre depasse la limite.\n");
            break;
        case 2:
            printf("Cette chaine depasse le nombre de caractere autorises\n");
            break;
    }
    return exit(EXIT_FAILURE);
}

void lire_car(FILE * fichier){
    CARLU = (char)fgetc(fichier);
    if(CARLU == EOF) {
        erreur(0);
    }
    else if(CARLU == '\n')
        NUM_LIGNE+=1;
}

void sauter_separateurs(FILE * fichier){
    int nb = 0;
    if(CARLU=='{')
    {
        nb+=1;
        while(nb!=0)
        {
            lire_car(fichier);
            if(CARLU=='{')
                nb+=1;
            else if(CARLU=='}')
                nb-=1;
        }
    }
    while(CARLU==' ' || CARLU=='\t' || CARLU=='\n')
    {
        lire_car(fichier);
    }
}

char* t_unilex_to_string(T_UNILEX unilex){
    switch(unilex){
        case 0:{
            return "motcle";
        }
        case 1:{
            return "ident";
        }
        case 2:{
            return "ent";
        }
        case 3:{
            return "ch";
        }
        case 4:{
            return "virg";
        }
        case 5:{
            return "ptvirg";
        }
        case 6:{
            return "point";
        }
        case 7:{
            return "deuxpts";
        }
        case 8:{
            return "parouv";
        }
        case 9:{
            return "parfer";
        }
        case 10:{
            return "inf";
        }
        case 11:{
            return "sup";
        }
        case 12:{
            return "eg";
        }
        case 13:{
            return "plus";
        }
        case 14:{
            return "moins";
        }
        case 15:{
            return "mult";
        }
        case 16:{
            return "divi";
        }
        case 17:{
            return "infe";
        }
        case 18:{
            return "supe";
        }
        case 19:{
            return "diff";
        }
        case 20:{
            return "aff";
        }
        default:{

        }
    }
}

T_UNILEX reco_entier(FILE* fichier){
    char* chaine = malloc(sizeof(chaine));
    char* max_int = malloc(sizeof(max_int));
    sprintf(max_int, "%d", INT_MAX);
    chaine = strcat(chaine, &CARLU);
    while(CARLU>='0' && CARLU<='9')
    {
        chaine = strcat(chaine, &CARLU);
        lire_car(fichier);
    }

    if(strcmp(max_int, chaine)<0)
        erreur(1);

    NOMBRE = atoi(chaine);
    return ent;
}

T_UNILEX reco_chaine(FILE* fichier){
    char* chaine = malloc(sizeof(chaine)*LONG_MAX_CHAINE+1);
    int length = 0;
    int var_bool = 0;
    while(var_bool == 0)
    {
        if(length==LONG_MAX_CHAINE-2)
            erreur(2);
        chaine[length]=CARLU;
        lire_car(fichier);
        if(CARLU=='\'')
        {
            lire_car(fichier);
            if(CARLU!='\'') {
                var_bool = 1;
            }
        }
        length++;
    }
    chaine[length] = '\'';
    chaine[length] = '\0';
    CHAINE = strcpy(CHAINE, chaine);
    return ch;
}

T_UNILEX reco_ident_ou_mot_reserve(FILE* fichier){
    int length = 0;
    char* chaine = malloc(sizeof(char)*LONG_MAX_IDENT+1);
    while((CARLU>='0'&&CARLU<='9')||(CARLU>='A'&&CARLU<='z')||CARLU=='_')
    {
        if(length<LONG_MAX_IDENT) {
            chaine[length] = CARLU;
            lire_car(fichier);
        }
        length++;
    }
    chaine[length] = '\0';
    for(int i=0; i<length; i++)
    {
        chaine[i] = (char)toupper(chaine[i]);
    }
    char* otherChaine;
    if(strlen(CHAINE)!=0) {
        otherChaine = malloc(sizeof(char *) * strlen(CHAINE));
        otherChaine = strcpy(otherChaine, CHAINE);
    } else{
        otherChaine = malloc(sizeof(char)*10);
        sprintf(otherChaine, "%s", "PROGRAMME");
    }
    CHAINE = strcpy(CHAINE, chaine);

    if(est_un_mot_reserve())
        return motcle;
    else {
        Identificateurs i;
        i.nomIdent = malloc(sizeof(char*)*strlen(CHAINE));
        i.type = malloc(sizeof(char*)*strlen(otherChaine));
        setNameIdent(CHAINE, i);
        setTypeIdent(otherChaine, i);
        if(contains(tableIdent, i)==-1)
            addIdentificateurs(tableIdent, i);
        return ident;
    }
}

int est_un_mot_reserve(){
    int i=0;
    while(strcmp(CHAINE, TABLE_MOTS_RESERVES[i])!=0 && i<NB_MOTS_RESERVES) {
        i++;
    }

    if(i==NB_MOTS_RESERVES)
        return 0;
    else return 1;
}

T_UNILEX reco_symb(FILE* fichier){
    CHAINE = strcpy(CHAINE, &CARLU);
    switch(CARLU){
        case ';':{
            lire_car(fichier);
            return ptvirg;
        }
        case '+':{
            lire_car(fichier);
            return plus;
        }
        case '/':{
            lire_car(fichier);
            return divi;
        }
        case '.':{
            lire_car(fichier);
            return point;
        }
        case '-':{
            lire_car(fichier);
            return moins;
        }
        case '(':{
            lire_car(fichier);
            return parouv;
        }
        case '=':{
            lire_car(fichier);
            return eg;
        }
        case '*':{
            lire_car(fichier);
            return mult;
        }
        case ')':{
            lire_car(fichier);
            return parfer;
        }
        case ',':{
            lire_car(fichier);
            return virg;
        }
        case '<':{
            lire_car(fichier);
            switch(CARLU){
                case '=':{
                    CHAINE = strcat(CHAINE, &CARLU);
                    lire_car(fichier);
                    return infe;
                }
                case '>':{
                    CHAINE=strcat(CHAINE, &CARLU);
                    lire_car(fichier);
                    return diff;
                }
                default:{
                    return inf;
                }
            }
        }
        case '>':{
            lire_car(fichier);
            if(CARLU=='='){
                CHAINE=strcat(CHAINE, &CARLU);
                lire_car(fichier);
                return supe;
            } else{
                return sup;
            }
        }
        case ':':{
            lire_car(fichier);
            if(CARLU=='='){
                char car = '=';
                CHAINE = strcat(CHAINE, &CARLU);
                lire_car(fichier);
                return aff;
            } else{
                return deuxpts;
            }
        }
        default:{

        }
    }
}

void analex(FILE* fichier){
    T_UNILEX var;
    if(CARLU=='{'||CARLU==' ' || CARLU=='\t' || CARLU=='\n'){
        sauter_separateurs(fichier);
    }
    else if(CARLU>='0' && CARLU<='9')
    {
        var = reco_entier(fichier);
        printf("%d %s\n", NOMBRE, t_unilex_to_string(var));
    }
    else if(CARLU=='\'')
    {
        var = reco_chaine(fichier);
        printf("%s %s\n", CHAINE, t_unilex_to_string(var));
    }
    else if(CARLU>='A' && CARLU<='z')
    {
        var = reco_ident_ou_mot_reserve(fichier);
        printf("%s %s\n", CHAINE, t_unilex_to_string(var));
    }
    else{
        var = reco_symb(fichier);
        printf("%s %s\n", CHAINE, t_unilex_to_string(var));
    }
}

void initialiser(FILE** fichier){
    NUM_LIGNE = 0;
    CHAINE = malloc(sizeof(char)*LONG_MAX_CHAINE);
    sprintf(TABLE_MOTS_RESERVES[0], "%s", "CONST");
    sprintf(TABLE_MOTS_RESERVES[1], "%s", "DEBUT");
    sprintf(TABLE_MOTS_RESERVES[2], "%s", "ECRIRE");
    sprintf(TABLE_MOTS_RESERVES[3], "%s", "FIN");
    sprintf(TABLE_MOTS_RESERVES[4], "%s", "LIRE");
    sprintf(TABLE_MOTS_RESERVES[5], "%s", "PROGRAMME");
    sprintf(TABLE_MOTS_RESERVES[6], "%s", "VAR");
    *fichier = fopen(SOURCE, "r");
    tableIdent = malloc(sizeof(TableIdentificateurs));
    init(tableIdent);
}

void terminer(FILE** fichier){
    fclose(*fichier);
}

void analyseur_lexical(char* source){
    FILE* fichier = NULL;
    SOURCE = malloc(sizeof(char)*40);
    SOURCE = strcpy(SOURCE, source);
    CHAINE = malloc(sizeof(CHAINE));
    initialiser(&fichier);
    lire_car(fichier);
    sprintf(CHAINE, "%s", "");
    while(strcmp(CHAINE, "FIN")!=0){
        analex(fichier);
    }
    printf("%s\n", "------------");
    for(int j=0; j<tableIdent->length; j++)
    {
        printf("%s %s\n", tableIdent->tableIdentificateurs[j].nomIdent, tableIdent->tableIdentificateurs[j].type);
    }
    terminer(&fichier);
}