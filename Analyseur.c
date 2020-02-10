#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#include "Analyseur.h"
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
        case 3:
            printf("Erreur syntaxique.\n");
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
    if(strlen(chaine) >= strlen(max_int))
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
    chaine[length+1] = '\0';
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
        if(contains(tableIdent, i)==-1) {
            if(strcmp(getTypeIdent(i), ",")==0) {
                if (strcmp(getTypeIdent(tableIdent->tableIdentificateurs[tableIdent->actualLength - 1]), "VAR") == 0) {
                    setTypeIdent("VAR", i);
                }
                else if(strcmp(getTypeIdent(tableIdent->tableIdentificateurs[tableIdent->actualLength-1]), "CONST") == 0)
                {
                    setTypeIdent("CONST", i);
                }
            }
            addIdentificateurs(tableIdent, i);
        }
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

int prog(FILE* file){
    printf("Fonction prog\n");
    if(strcmp(CHAINE, "PROGRAMME")!=0)
        return 0;
    unilex = analex(file);
    if(unilex != ident)
        return 0;
    unilex = analex(file);
    if(unilex!=ptvirg)
        return 0;
    unilex=analex(file);
    if(strcmp(CHAINE, "CONST")==0) {
        if (decl_const(file) == 0)
            return 0;
    }
    if(strcmp(CHAINE, "VAR")==0)
        if(decl_var(file)==0)
            return 0;
    if(bloc(file)==0)
        return 0;
    return 1;
}

int decl_const(FILE* file){
    printf("Fonction decl_const\n");
    if(strcmp(CHAINE, "CONST")==0){
        while(unilex!=ptvirg){
            unilex = analex(file);
            if(unilex!=ident)
                return 0;
            unilex = analex(file);
            if(unilex!=eg)
                return 0;
            unilex=analex(file);
            if(unilex!=ent && unilex!=ch)
                return 0;
            unilex = analex(file);
            if(unilex!=ptvirg)
            {
                if(unilex!=virg)
                    return 0;
            }
        }
    }
    unilex = analex(file);
    return 1;
}

int decl_var(FILE* file){
    printf("Fonction decl_var\n");
    if(strcmp(CHAINE, "VAR")==0){
        while(unilex!=ptvirg){
            unilex=analex(file);
            if(unilex!=ident)
                return 0;
            unilex = analex(file);
            if(unilex!=ptvirg){
                if(unilex!=virg)
                    return 0;
            }
        }
    }
    unilex = analex(file);
    return 1;
}

int bloc(FILE* file){
    printf("Fonction bloc\n");
    if(strcmp(CHAINE, "DEBUT")==0)
    {
        unilex=analex(file);
        while(strcmp(CHAINE, "FIN")!=0) {
            if (instruction(file) == 0)
                return 0;
        }
        return 1;
    }
    else{
        return 0;
    }
}

int instruction(FILE* file){
    printf("Fonction instruction\n");
    if(strcmp(CHAINE, "LIRE")==0)
        return lecture(file)==1;
    else if(strcmp(CHAINE, "ECRIRE")==0)
        return ecriture(file)==1;
    else if(unilex==ident)
        return affectation(file)==1;
    else
        return bloc(file)==1;
}

int affectation(FILE * file){
    printf("Fonction affectation\n");
    if(unilex != ident)
        return 0;
    unilex = analex(file);
    if(unilex!=aff)
        return 0;
    if(expr(file)==0)
        return 0;
    if(unilex!=ptvirg)
        return 0;
    unilex = analex(file);
    return 1;
}

int lecture(FILE* file){
    printf("Fonction lecture\n");
    if(strcmp(CHAINE, "LIRE")!=0)
        return 0;
    unilex = analex(file);
    if(unilex!=parouv)
        return 0;
    unilex=analex(file);
    if(unilex==parfer)
        return 0;
    while(unilex!=parfer)
    {
        if(unilex!=ident)
            return 0;
        unilex = analex(file);
        if(unilex!=parfer){
            if(unilex!=virg)
                return 0;
            unilex=analex(file);
        }
    }
    unilex = analex(file);
    if(unilex!=ptvirg)
        return 0;
    unilex = analex(file);
    return 1;

}

int ecriture(FILE * file){
    printf("Fonction ecriture\n");
    if(strcmp(CHAINE, "ECRIRE")!=0)
        return 0;
    unilex = analex(file);
    if(unilex!=parouv)
        return 0;
    unilex = analex(file);
    while(unilex!=parfer)
    {
        if(ecr_exp(file)==0)
            return 0;
        if(unilex!=parfer)
        {
            if(unilex!=virg)
                return 0;
            unilex = analex(file);
        }
    }
    unilex=analex(file);
    if(unilex!=ptvirg)
        return 0;
    unilex=analex(file);
    return 1;
}

int ecr_exp(FILE* file){
    printf("Fonction ecr_exp\n");
    if(unilex!=ch)
    {
        if(expr(file)!=0) {
            unilex = analex(file);
            return 1;
        }
        else
            return 0;
    } else {
        unilex=analex(file);
        return 1;
    }
}

int expr(FILE* file){
    printf("Fonction expr\n");
    unilex = analex(file);
    if(terme(file) == 0)
        return 0;
    unilex = analex(file);
    if(suite_terme(file)==0)
        return 0;
    return 1;
}

int suite_terme(FILE* file){
    printf("Fonction suite_terme\n");
    if(unilex==ptvirg||unilex==parfer) {
        return 1;
    }
    if(op_bin(file)==0)
        return 0;
    if(expr(file)==0)
        return 0;
    return 1;
}

int terme(FILE* file){
    printf("Fonction terme\n");
    if(unilex==ent||unilex==ident) {
        return 1;
    }
    if(unilex==parouv){
        if(expr(file)==0)
            return 0;
        if(unilex!=parfer)
            return 0;
        return 1;
    }
    else{
        if(unilex==moins)
        {
            return terme(file);
        }
        else return 0;
    }
}

int op_bin(FILE* file){
    printf("Fonction op_bin\n");
    return unilex==plus||unilex==moins||unilex==mult||unilex==divi;
}

T_UNILEX analex(FILE* fichier){
    if(CARLU=='{'||CARLU==' ' || CARLU=='\t' || CARLU=='\n'){
        sauter_separateurs(fichier);
    }
    if(CARLU>='0' && CARLU<='9')
    {
        return reco_entier(fichier);
    }
    else if(CARLU=='\'')
    {
        return reco_chaine(fichier);
    }
    else if(CARLU>='A' && CARLU<='z')
    {
        return reco_ident_ou_mot_reserve(fichier);
    }
    else{
        return reco_symb(fichier);
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
    T_UNILEX affichage;
    SOURCE = malloc(sizeof(char)*40);
    SOURCE = strcpy(SOURCE, source);
    CHAINE = malloc(sizeof(CHAINE));
    initialiser(&fichier);
    lire_car(fichier);
    while(strcmp(CHAINE, "FIN")!=0){
        affichage = analex(fichier);
        if(affichage==ent)
            printf("%d %s\n", NOMBRE, t_unilex_to_string(affichage));
        else
            printf("%s %s\n", CHAINE, t_unilex_to_string(affichage));
    }
    printf("%s\n", "------------");
    for(int j=0; j<tableIdent->actualLength; j++)
    {
        printf("%s %s\n", tableIdent->tableIdentificateurs[j].nomIdent, tableIdent->tableIdentificateurs[j].type);
    }
    terminer(&fichier);
}

void anasynt(FILE* file){
    lire_car(file);
    analex(file);
    if(prog(file)!=0)
        printf("Le programme source est syntaxiquement correct\n");
    else{
        erreur(3);
    }
}

void analyseur_syntaxique(char* source){
    FILE* fichier = NULL;
    SOURCE = malloc(sizeof(char)*40);
    SOURCE = strcpy(SOURCE, source);
    CHAINE = malloc(sizeof(CHAINE));
    initialiser(&fichier);
    sprintf(CHAINE, "%s", "");
    anasynt(fichier);
    terminer(&fichier);
}