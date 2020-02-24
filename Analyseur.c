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
        case 4:
            printf("Identifiant deja existant.\n");
            break;
        case 5:
            printf("Erreur identifiant non declaree ligne :%d\n", NUM_LIGNE);
            break;
        case 6:
            printf("Erreur identifiant n'est pas une variable ligne :%d\n", NUM_LIGNE);
            break;
        case 7:
            printf("Erreur semantique ligne : %d\n", NUM_LIGNE);
            break;
        case 8:
            printf("Identifiant de type ch : %d\n", NUM_LIGNE);
            break;
    }
    return exit(EXIT_FAILURE);
}

void lire_car(){
    CARLU = (char)fgetc(file);
    if(CARLU == EOF) {
        erreur(0);
    }
    else if(CARLU == '\n')
        NUM_LIGNE+=1;
}

void sauter_separateurs(){
    int nb = 0;
    if(CARLU=='{')
    {
        nb+=1;
        while(nb!=0)
        {
            lire_car();
            if(CARLU=='{')
                nb+=1;
            else if(CARLU=='}')
                nb-=1;
        }
    }
    if(CARLU=='}')
        lire_car();
    while(CARLU==' ' || CARLU=='\t' || CARLU=='\n')
    {
        lire_car();
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

T_UNILEX reco_entier(){
    char* chaine = malloc(sizeof(chaine));
    char* max_int = malloc(sizeof(max_int)*15);
    sprintf(chaine, "%c", CARLU);
    sprintf(max_int, "%d", INT_MAX);
    lire_car();
    while(CARLU>='0' && CARLU<='9')
    {
        chaine = strcat(chaine, &CARLU);
        lire_car();
    }
    if(strlen(chaine) >= strlen(max_int))
        erreur(1);

    NOMBRE = atoi(chaine);
    return ent;
}

T_UNILEX reco_chaine(){
    char* chaine = malloc(sizeof(chaine)*LONG_MAX_CHAINE+1);
    int length = 0;
    int var_bool = 0;
    while(var_bool == 0)
    {
        if(length==LONG_MAX_CHAINE-2)
            erreur(2);
        chaine[length]=CARLU;
        lire_car();
        if(CARLU=='\'')
        {
            lire_car();
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

T_UNILEX reco_ident_ou_mot_reserve(){
    int length = 0;
    char* chaine = malloc(sizeof(char)*LONG_MAX_IDENT+1);
    while((CARLU>='0'&&CARLU<='9')||(CARLU>='A'&&CARLU<='z')||CARLU=='_')
    {
        if(length<LONG_MAX_IDENT) {
            chaine[length] = CARLU;
            lire_car();
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
        otherChaine = malloc(sizeof(char) * strlen(CHAINE));
        otherChaine = strcpy(otherChaine, CHAINE);
    } else{
        otherChaine = malloc(sizeof(char)*10);
        sprintf(otherChaine, "%s", "PROGRAMME");
    }
    CHAINE = strcpy(CHAINE, chaine);

    if(est_un_mot_reserve())
        return motcle;
    else {
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

T_UNILEX reco_symb(){
    CHAINE = strcpy(CHAINE, &CARLU);
    switch(CARLU){
        case ';':{
            lire_car();
            return ptvirg;
        }
        case '+':{
            lire_car();
            return plus;
        }
        case '/':{
            lire_car();
            return divi;
        }
        case '.':{
            lire_car();
            return point;
        }
        case '-':{
            lire_car();
            return moins;
        }
        case '(':{
            lire_car();
            return parouv;
        }
        case '=':{
            lire_car();
            return eg;
        }
        case '*':{
            lire_car();
            return mult;
        }
        case ')':{
            lire_car();
            return parfer;
        }
        case ',':{
            lire_car();
            return virg;
        }
        case '<':{
            lire_car();
            switch(CARLU){
                case '=':{
                    CHAINE = strcat(CHAINE, &CARLU);
                    lire_car();
                    return infe;
                }
                case '>':{
                    CHAINE=strcat(CHAINE, &CARLU);
                    lire_car();
                    return diff;
                }
                default:{
                    return inf;
                }
            }
        }
        case '>':{
            lire_car();
            if(CARLU=='='){
                CHAINE=strcat(CHAINE, &CARLU);
                lire_car();
                return supe;
            } else{
                return sup;
            }
        }
        case ':':{
            lire_car();
            if(CARLU=='='){
                CHAINE = strcat(CHAINE, &CARLU);
                lire_car();
                return aff;
            } else{
                return deuxpts;
            }
        }
        default:{

        }
    }
}

int prog(){
    printf("Fonction prog\n");
    if(strcmp(CHAINE, "PROGRAMME")!=0)
        return 0;
    unilex = analex();
    if(unilex != ident)
        return 0;
    Identificateurs i;
    i.nomIdent = malloc(sizeof(char*)*strlen(CHAINE));
    i.type = malloc(sizeof(char*)*strlen("PROGRAMME"));
    setNameIdent(CHAINE, i);
    setTypeIdent("PROGRAMME", i);
    addIdentificateurs(tableIdent, i);
    unilex = analex();
    if(unilex!=ptvirg)
        return 0;
    unilex=analex();
    if(strcmp(CHAINE, "CONST")==0) {
        if (decl_const() == 0)
            return 0;
    }
    if(strcmp(CHAINE, "VAR")==0)
        if(decl_var()==0)
            return 0;
    if(bloc()==0)
        return 0;
    return 1;
}

int decl_const(){
    printf("Fonction decl_const\n");
    if(strcmp(CHAINE, "CONST")==0){
        while(unilex!=ptvirg){
            unilex = analex();
            if(unilex!=ident)
                return 0;
            if(contains(tableIdent, CHAINE)!=-1)
                erreur(4);

            Identificateurs i;
            i.nomIdent = malloc(sizeof(char*)*strlen(CHAINE));
            i.type = malloc(sizeof(char*)*strlen("CONST"));
            setNameIdent(CHAINE, i);
            setTypeIdent("CONST", i);
            unilex = analex();
            if(unilex!=eg)
                return 0;
            unilex=analex();
            if(unilex!=ent && unilex!=ch)
                return 0;
            if(unilex==ent)
            {
                i.typc = 0;
                i.valent = NOMBRE;
            }
            else if(unilex==ch){
                i.typc = 1;
                i.valch = malloc(sizeof(char)*strlen(CHAINE)+1);
                i.valch = strcpy(i.valch, CHAINE);
                addConstChaine(CHAINE);
            }
            addIdentificateurs(tableIdent, i);
            unilex = analex();
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

int decl_var(){
    printf("Fonction decl_var\n");
    if(strcmp(CHAINE, "VAR")==0){
        while(unilex!=ptvirg){
            unilex=analex();
            if(unilex!=ident)
                return 0;
            if(contains(tableIdent, CHAINE)!=-1)
                erreur(4);
            Identificateurs i;
            i.nomIdent = malloc(sizeof(char*)*strlen(CHAINE));
            i.type = malloc(sizeof(char*)*strlen("VAR"));
            setNameIdent(CHAINE, i);
            setTypeIdent("VAR", i);
            i.typc = 0;
            i.valent = DERNIERE_ADRESSE_VAR_GLOB++;
            addIdentificateurs(tableIdent, i);
            unilex = analex();
            if(unilex!=ptvirg){
                if(unilex!=virg)
                    return 0;
            }
        }
    }
    unilex = analex(file);
    return 1;
}

int bloc(){
    printf("Fonction bloc\n");
    if(strcmp(CHAINE, "DEBUT")==0)
    {
        unilex=analex();
        while(strcmp(CHAINE, "FIN")!=0) {
            if (instruction() == 0)
                return 0;
        }
        return 1;
    }
    else{
        return 0;
    }
}

int instruction(){
    printf("Fonction instruction\n");
    if(strcmp(CHAINE, "LIRE")==0)
        return lecture()==1;
    else if(strcmp(CHAINE, "ECRIRE")==0)
        return ecriture()==1;
    else if(unilex==ident) {
        return affectation() == 1;
    }
    else
        return bloc()==1;
}

int affectation(){
    printf("Fonction affectation\n");
    varBool = 1;
    if(unilex != ident)
        return 0;
    if(contains(tableIdent, CHAINE)==-1)
        erreur(5);
    if(strcmp(tableIdent->tableIdentificateurs[contains(tableIdent, CHAINE)].type, "VAR")!=0)
        erreur(6);
    unilex = analex();
    if(unilex!=aff)
        return 0;
    unilex = analex();
    if(expr()==0)
        return 0;
    if(unilex!=ptvirg)
        return 0;
    unilex = analex();
    varBool = 0;
    strBool = 0;
    return 1;
}

int lecture(){
    printf("Fonction lecture\n");
    if(strcmp(CHAINE, "LIRE")!=0)
        return 0;
    unilex = analex();
    if(unilex!=parouv)
        return 0;
    unilex=analex();
    if(unilex==parfer)
        return 0;
    while(unilex!=parfer)
    {
        if(unilex!=ident)
            return 0;
        if(contains(tableIdent, CHAINE)==-1)
            erreur(5);
        if(strcmp(tableIdent->tableIdentificateurs[contains(tableIdent, CHAINE)].type, "VAR")!=0)
            erreur(6);
        unilex = analex();
        if(unilex!=parfer){
            if(unilex!=virg)
                return 0;
            unilex=analex();
            if(unilex==parfer)
                return 0;
        }
    }
    unilex = analex(file);
    if(unilex!=ptvirg)
        return 0;
    unilex = analex(file);
    return 1;

}

int ecriture(){
    printf("Fonction ecriture\n");
    if(strcmp(CHAINE, "ECRIRE")!=0)
        return 0;
    unilex = analex();
    if(unilex!=parouv)
        return 0;
    unilex = analex();
    while(unilex!=parfer)
    {
        if(ecr_exp()==0)
            return 0;
        if(unilex!=parfer)
        {
            if(unilex!=virg)
                return 0;
            unilex = analex();
            if(unilex==parfer)
                return 0;
        }
    }
    unilex=analex(file);
    if(unilex!=ptvirg)
        return 0;
    unilex=analex(file);
    varBool = 0;
    strBool = 0;
    return 1;
}

int ecr_exp(){
    printf("Fonction ecr_exp\n");
    if(unilex!=ch)
    {
        if(expr()!=0) {
            //unilex = analex();
            return 1;
        }
        else
            return 0;
    } else {
        unilex=analex();
        return 1;
    }
}

int expr(){
    printf("Fonction expr\n");
    if(terme() == 0)
        return 0;
    if(suite_terme()==0)
        return 0;
    return 1;
}

int suite_terme(){
    printf("Fonction suite_terme\n");
    if(unilex==ptvirg||unilex==parfer||unilex==virg) {
        return 1;
    }
    if(op_bin()==0)
        return 0;
    unilex=analex();
    if(expr()==0)
        return 0;
    return 1;
}

int terme(){
    printf("Fonction terme\n");
    if(unilex==ent||unilex==ident) {
        if(unilex==ident)
        {
            if(contains(tableIdent, CHAINE)==-1)
                erreur(5);
            if(strcmp(tableIdent->tableIdentificateurs[contains(tableIdent, CHAINE)].type, "CONST")==0) {
                if (tableIdent->tableIdentificateurs[contains(tableIdent, CHAINE)].typc == 1) {
                    if(varBool == 1 || strBool == 1)
                        erreur(8);
                    else
                        strBool = 1;
                }
            }
            varBool = 1;
        }
        unilex = analex();
        return 1;
    }
    if(unilex==parouv){
        unilex = analex();
        if(expr()==0)
            return 0;
        if(unilex!=parfer)
            return 0;
        unilex=analex();
        return 1;
    }
    else{
        if(unilex==moins)
        {
            unilex = analex();
            return terme();
        }
        else return 0;
    }
}

int op_bin(){
    printf("Fonction op_bin\n");
    return unilex==plus||unilex==moins||unilex==mult||unilex==divi;
}

T_UNILEX analex(){
    while(CARLU=='{'||CARLU==' ' || CARLU=='\t' || CARLU=='\n'){
        sauter_separateurs();
    }
    if(CARLU>='0' && CARLU<='9')
    {
        return reco_entier();
    }
    else if(CARLU=='\'')
    {
        return reco_chaine();
    }
    else if(CARLU>='A' && CARLU<='z')
    {
        return reco_ident_ou_mot_reserve();
    }
    else{
        return reco_symb();
    }
}

void initialiser(TableIdentificateurs* tableIdentificateurs){
    NUM_LIGNE = 1;
    NB_CONST_CHAINE = 0;
    DERNIERE_ADRESSE_VAR_GLOB = 0;
    VAL_DE_CONST_CHAINE = malloc(sizeof(char*));
    CHAINE = malloc(sizeof(char)*LONG_MAX_CHAINE);
    sprintf(CHAINE, "%s", ".....");
    sprintf(TABLE_MOTS_RESERVES[0], "%s", "CONST");
    sprintf(TABLE_MOTS_RESERVES[1], "%s", "DEBUT");
    sprintf(TABLE_MOTS_RESERVES[2], "%s", "ECRIRE");
    sprintf(TABLE_MOTS_RESERVES[3], "%s", "FIN");
    sprintf(TABLE_MOTS_RESERVES[4], "%s", "LIRE");
    sprintf(TABLE_MOTS_RESERVES[5], "%s", "PROGRAMME");
    sprintf(TABLE_MOTS_RESERVES[6], "%s", "VAR");
    file = fopen(SOURCE, "r");
    tableIdent = tableIdentificateurs;
    init(tableIdent);
}

void terminer(){
    fclose(file);
}

void analyseur_lexical(char* source, TableIdentificateurs* tableIdentificateurs){
    FILE* fichier = NULL;
    T_UNILEX affichage;
    SOURCE = malloc(sizeof(char)*40);
    SOURCE = strcpy(SOURCE, source);
    CHAINE = malloc(sizeof(CHAINE));
    initialiser(tableIdentificateurs);
    lire_car();
    while(strcmp(CHAINE, "FIN")!=0){
        affichage = analex(fichier);
        if(affichage==ent)
            printf("%d %s\n", NOMBRE, t_unilex_to_string(affichage));
        else
            printf("%s %s\n", CHAINE, t_unilex_to_string(affichage));
    }
    terminer();
}

void anasynt(){
    lire_car();
    analex();
    if(prog()!=0)
        printf("Le programme source est syntaxiquement correct\n");
    else{
        erreur(3);
    }
}

void analyseur_syntaxique(char* source, TableIdentificateurs* tableIdentificateurs){
    FILE* fichier = NULL;
    SOURCE = malloc(sizeof(char)*40);
    SOURCE = strcpy(SOURCE, source);
    CHAINE = malloc(sizeof(CHAINE));
    initialiser(tableIdentificateurs);
    sprintf(CHAINE, "%s", "");
    anasynt();
    printf("Nb de const chaine : %d\n", NB_CONST_CHAINE);
    for(int i=0; i<NB_CONST_CHAINE;i++)
    {
        printf("%s\n", VAL_DE_CONST_CHAINE[i]);
    }
    terminer();
}

void addConstChaine(char* chaine){
    VAL_DE_CONST_CHAINE = realloc(VAL_DE_CONST_CHAINE, sizeof(char*)*(NB_CONST_CHAINE+1));
    VAL_DE_CONST_CHAINE[NB_CONST_CHAINE] = malloc(sizeof(char)*strlen(chaine)+1);
    VAL_DE_CONST_CHAINE[NB_CONST_CHAINE] = strcpy(VAL_DE_CONST_CHAINE[NB_CONST_CHAINE], chaine);
    NB_CONST_CHAINE++;
}