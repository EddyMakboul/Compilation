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
            printf("Erreur syntaxique ligne :%d.\n", NUM_LIGNE);
            break;
        case 4:
            printf("Identifiant deja existant ligne :%d.\n", NUM_LIGNE);
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
        case 9:
            printf("Erreur d'execution : division par zero.\n");
            break;
        case 10:
            printf("Erreur arguments ne peuvent affectés, ligne: %d.\n", NUM_LIGNE);
            break;
        default:
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

char* t_unilex_to_string(T_UNILEX uni){
    switch(uni){
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
        otherChaine = malloc(sizeof(char) * (strlen(CHAINE)+1));
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
    //printf("Fonction prog\n");
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

    testFct = 1;
    if(strcmp(CHAINE, "FONCTION")==0)
        if(decl_fct()==0)
            return 0;
    testFct = 0;
    CO=0;
    if(bloc()==0)
        return 0;
    addPCode("STOP");
    return 1;
}

int decl_const(){
    //printf("Fonction decl_const\n");
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
    unilex = analex();
    return 1;
}

int decl_var(){
    //printf("Fonction decl_var\n");
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
    unilex = analex();
    return 1;
}

int decl_fct(){
    if(strcmp(CHAINE, "FONCTION")!=0)
        return 0;
    unilex=analex();
    if(unilex!=ident)
        return 0;
    nameFonction = realloc(nameFonction, sizeof(nameFonction)*strlen(CHAINE));
    Identificateurs identifi;
    identifi.nomIdent = malloc(sizeof(identifi.nomIdent)*strlen(CHAINE));
    sprintf(identifi.nomIdent, "%s", CHAINE);
    sprintf(nameFonction, "%s", CHAINE);
    identifi.type = malloc(sizeof(identifi.type)*strlen("fct"));
    sprintf(identifi.type, "%s", "fct");
    identifi.nbArg=0;
    identifi.start = CO;
    unilex = analex();
    if(unilex!=parouv)
        return 0;
    unilex = analex();
    while(unilex!=parfer)
    {
        if(unilex!=ident)
            return 0;
        if(identifi.nbArg==0)
            identifi.nameArgs = malloc(sizeof(identifi.nameArgs));
        else
            identifi.nameArgs = realloc(identifi.nameArgs, sizeof(identifi.nameArgs)*(identifi.nbArg+1));
        identifi.nameArgs[identifi.nbArg] = malloc(sizeof(identifi.nameArgs[identifi.nbArg])*strlen(CHAINE));
        identifi.nameArgs[identifi.nbArg] = strcpy(identifi.nameArgs[identifi.nbArg], CHAINE);
        identifi.nbArg+=1;
        unilex = analex();
        if(unilex==virg)
        {
            unilex = analex();
            if(unilex==parfer)
                return 0;
        } else
            if(unilex!=parfer)
                return 0;
    }
    identifi.args = malloc(sizeof(identifi.args)*identifi.nbArg);
    unilex = analex();
    if(unilex != deuxpts)
        return 0;
    unilex = analex();
    if(strcmp(CHAINE, "ENTIER")!=0)
        return 0;
    unilex = analex();
    addIdentificateurs(tableIdent, identifi);
    if(bloc()==0)
        return 0;
    nameFonction = realloc(nameFonction, sizeof(nameFonction)*strlen(identifi.nomIdent));
    sprintf(nameFonction, "%s", identifi.nomIdent);
    tableIdent->tableIdentificateurs[contains(tableIdent, nameFonction)].end = CO-1;
    if(strcmp(CHAINE, "FONCTION")==0)
        return decl_fct();
    return 1;
}

int bloc(){
    //printf("Fonction bloc\n");
    if(strcmp(CHAINE, "DEBUT")==0)
    {
        unilex=analex();
        while(strcmp(CHAINE, "FIN")!=0) {
            if (instruction() == 0)
                return 0;
        }
        unilex = analex();
        return 1;
    }
    else{
        return 0;
    }
}

int instruction(){
    //printf("Fonction instruction\n");
    if(strcmp(CHAINE, "SI")==0)
        return inst_cond();
    else return inst_non_cond();
}

int inst_non_cond(){
    if(strcmp(CHAINE, "LIRE")==0)
        return lecture()==1;
    if(strcmp(CHAINE, "ECRIRE")==0)
        return ecriture()==1;
    if(strcmp(CHAINE, "DEBUT") == 0)
        return bloc()==1;
    if(unilex==ident) {
        if(strcmp(tableIdent->tableIdentificateurs[contains(tableIdent, CHAINE)].type, "fct")==0) {
            int verifPlus = verifFct();
            if(verifPtVirg==0) {
                if (unilex != ptvirg)
                    return 0;
                unilex = analex();
            }
            verifPtVirg=0;
            return verifPlus;
        }
        else
            return affectation() == 1;
    }
    if(strcmp(CHAINE, "TANTQUE")==0)
        return inst_repe()==1;
    return 0;
}

int verifFct(){
    Identificateurs identifi = tableIdent->tableIdentificateurs[contains(tableIdent, CHAINE)];
    int value = 0;
    if(strcmp(identifi.nomIdent, nameFonction)==0)
        value = 1;
    nameFonction = malloc(sizeof(nameFonction)*strlen(CHAINE));
    sprintf(nameFonction, "%s", CHAINE);
    if(strcmp(identifi.type, "fct")!=0)
        return 0;
    unilex = analex();
    if(unilex!=parouv) {
        if(unilex==aff && testFct==0)
        {
            return 0;
        } else if(unilex == aff){
            if(value==1)
            {
                tableIdent->tableIdentificateurs[contains(tableIdent, nameFonction)].hasReturn =1;
                unilex = analex();
                if(expr()==0)
                    return 0;
                if(unilex!=ptvirg)
                    return 0;
                if(testFct==1)
                {
                    addPCodeFonction("FINFONCTION");
                } else
                    addPCode("FINFONCTION");
                unilex = analex();
                verifPtVirg = 1;
                return 1;
            }
        }
        return 0;
    }
    unilex = analex();
    if(identifi.nbArg!=0)
    {
        for(int i=0;i<identifi.nbArg;i++)
        {
            if(unilex!=ent && unilex!=ident)
                return 0;
            if(unilex==ident){
                if(tableIdent->tableIdentificateurs[contains(tableIdent, CHAINE)].typc!=0)
                    return 0;
                tableIdent->tableIdentificateurs[contains(tableIdent, nameFonction)].args[i] =
                        tableIdent->tableIdentificateurs[contains(tableIdent, CHAINE)].valent;
            } else
                tableIdent->tableIdentificateurs[contains(tableIdent, nameFonction)].args[i] = NOMBRE;
            unilex = analex();
            if(i<identifi.nbArg-1) {
                if (unilex != virg)
                    return 0;
                unilex = analex();
            }else{
                if(unilex!=parfer)
                    return 0;
            }
        }
    } else
    {
        if(unilex!=parfer)
            return 0;
    }
    unilex = analex();
    addFonction(identifi.nomIdent);
    return 1;

}

int inst_repe(){
    if(strcmp(CHAINE, "TANTQUE")!=0)
        return 0;
    unilex = analex();
    addTabMemMove(CO);
    if(expr()==0)
        return 0;
    if(testFct==1) {
        addPCodeFonction("ALSN");
        addPCodeFonction("");
    }
    else {
        addPCode("ALSN");
        addPCode("");
    }
    addTabMemMove(CO-1);
    if(strcmp(CHAINE, "FAIRE")!=0)
        return 0;
    unilex = analex();
    if(instruction()!=1)
        return 0;
    int num = removeTabMemMove();
    int num2 = removeTabMemMove();
    if(testFct==1)
    {
        P_CODE_FONCTION[num] = malloc(sizeof(CO));
        sprintf(P_CODE_FONCTION[num], "%d", CO+2);
        addPCodeFonction("ALLE");
        addPCodeIntFonction(num2);
    }
    else {
        P_CODE[num] = malloc(sizeof(int));
        sprintf(P_CODE[num], "%d", CO + 2);
        addPCode("ALLE");
        addPCodeInt(num2);
    }
    return 1;
}

int inst_cond(){
    if(strcmp(CHAINE, "SI")!=0)
        return 0;
    unilex = analex();
    if(expr()==0)
        return 0;
    if(testFct==1){
        addPCodeFonction("ALSN");
        addPCodeFonction("");
    }
    else{
        addPCode("ALSN");
        addPCode("");
    }
    addTabMemMove(CO-1);
    if(strcmp(CHAINE, "ALORS")!=0)
        return 0;
    unilex = analex();
    if(instruction()==0)
        return 0;
    int num = removeTabMemMove();
    if(testFct==1)
    {
        P_CODE_FONCTION[num] = malloc(sizeof(CO));
        sprintf(P_CODE_FONCTION[num], "%d", CO+2);
    }else{
        P_CODE[num] = malloc(sizeof(CO));
        sprintf(P_CODE[num], "%d", CO+2);
    }
    if(strcmp(CHAINE, "SINON")==0) {
        if(testFct==1){
            addPCodeFonction("ALLE");
            addPCodeFonction("");
        }
        else {
            addPCode("ALLE");
            addPCode("");
        }
        addTabMemMove(CO-1);
        unilex = analex();
        if(instruction()==0)
            return 0;
        num = removeTabMemMove();
        if(testFct==1){
            P_CODE_FONCTION[num] = malloc(sizeof(CO));
            sprintf(P_CODE_FONCTION[num], "%d", CO);
        }else {
            P_CODE[num] = malloc(sizeof(CO));
            sprintf(P_CODE[num], "%d", CO);
        }
    }

    return 1;
}


int affectation(){
    //printf("Fonction affectation\n");
    varBool = 1;
    if(unilex != ident)
        return 0;
    if(contains(tableIdent, CHAINE)==-1)
        erreur(5);
    if(strcmp(tableIdent->tableIdentificateurs[contains(tableIdent, CHAINE)].type, "VAR")!=0 && testFct==0)
        erreur(6);
    else if((strcmp(tableIdent->tableIdentificateurs[contains(tableIdent, CHAINE)].type, "VAR")!=0 ||
    strcmp(tableIdent->tableIdentificateurs[contains(tableIdent, CHAINE)].type, "fct")!=0) && testFct==1){
        erreur(6);
    }
    if(testFct==1)
    {
        if(strcmp(tableIdent->tableIdentificateurs[contains(tableIdent, CHAINE)].type, "fct")!=0)
        {
            addPCodeFonction("EMPI");
            addPCodeIntFonction(tableIdent->tableIdentificateurs[contains(tableIdent, CHAINE)].valent);
        }
        else{
            addPCodeFonction("RETURN");
            tableIdent->tableIdentificateurs[contains(tableIdent, CHAINE)].hasReturn = 1;
        }
    }
    else {
        addPCode("EMPI");
        addPCodeInt(tableIdent->tableIdentificateurs[contains(tableIdent, CHAINE)].valent);
    }
    unilex = analex();
    if(unilex!=aff)
        return 0;
    unilex = analex();
    if(expr()==0)
        return 0;
    if(unilex!=ptvirg)
        return 0;
    if(testFct == 1)
        addPCodeFonction("AFFE");
    else
        addPCode("AFFE");
    unilex = analex();
    varBool = 0;
    strBool = 0;
    return 1;
}

int lecture(){
    //printf("Fonction lecture\n");
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
            erreur(10);
        if(testFct==1){
            if(containsArgs(CHAINE, tableIdent->tableIdentificateurs[contains(tableIdent, nameFonction)])==0)
                erreur(6);
            addPCodeFonction("EMPI");
            addPCodeIntFonction(tableIdent->tableIdentificateurs[contains(tableIdent, CHAINE)].valent);
            addPCodeFonction("LIRE");
        }else {
            addPCode("EMPI");
            addPCodeInt(tableIdent->tableIdentificateurs[contains(tableIdent, CHAINE)].valent);
            addPCode("LIRE");
        }
        unilex = analex();
        if(unilex!=parfer){
            if(unilex!=virg)
                return 0;
            unilex=analex();
            if(unilex==parfer)
                return 0;
        }
    }
    unilex = analex();
    if(unilex!=ptvirg)
        return 0;
    unilex = analex();
    return 1;

}

int ecriture(){
    //printf("Fonction ecriture\n");
    if(strcmp(CHAINE, "ECRIRE")!=0)
        return 0;
    unilex = analex();
    if(unilex!=parouv)
        return 0;
    unilex = analex();
    if(unilex==parfer) {
        if(testFct==1)
            addPCodeFonction("ECRL");
        else
            addPCode("ECRL");
    }
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
    unilex=analex();
    if(unilex!=ptvirg)
        return 0;
    unilex=analex();
    varBool = 0;
    strBool = 0;
    return 1;
}

int ecr_exp(){
    //printf("Fonction ecr_exp\n");
    if(unilex!=ch)
    {
        if(expr()!=0) {
            if(SOM_PILOP!=0)
            {
                if(testFct==1)
                    addPCodeFonction(PILOP[SOM_PILOP-1]);
                else
                    addPCode(PILOP[SOM_PILOP-1]);
                free(PILOP[SOM_PILOP-1]);
                PILOP = realloc(PILOP, sizeof(char *) * (SOM_PILOP-1));
                SOM_PILOP--;
            }
            if(verifExpr == 1) {
                if(testFct==1)
                    addPCodeFonction("ECRE");
                else
                    addPCode("ECRE");
            }
            verifExpr = 0;
            return 1;
        }
        else
            return 0;
    } else {
        if(testFct==1)
        {
            addPCodeFonction("ECRC");
            addPCodeFonction(CHAINE);
            addPCodeFonction("FINC");
        }
        else {
            addPCode("ECRC");
            addPCode(CHAINE);
            addPCode("FINC");
        }
        unilex=analex();
        return 1;
    }
}

int expr(){
    //printf("Fonction expr\n");
    if(terme() == 0)
        return 0;
    if(suite_terme()==0) {
        return 0;
    }
    if((unilex==ptvirg||unilex==virg||strcmp(CHAINE, "ALORS")==0||strcmp(CHAINE, "FAIRE")==0) && SOM_PILOP!=0) {
        for(int i=SOM_PILOP-1; i>=0; i--) {
            if(testFct==1)
                addPCodeFonction(PILOP[i]);
            else
                addPCode(PILOP[i]);
            free(PILOP[i]);
            PILOP = realloc(PILOP, sizeof(char *) * (i));
            SOM_PILOP--;
        }
    }
    return 1;
}

int suite_terme(){
    //printf("Fonction suite_terme\n");
    if(unilex==ptvirg||unilex==parfer||unilex==virg || strcmp(CHAINE, "FAIRE")==0 || strcmp(CHAINE, "ALORS")==0) {
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
    //printf("Fonction terme\n");
    if(unilex==ent||unilex==ident) {
        if(unilex==ent)
        {
            if(testFct==1){
                addPCodeFonction("EMPI");
                addPCodeIntFonction(NOMBRE);
            }
            else {
                addPCode("EMPI");
                addPCodeInt(NOMBRE);
            }
            verifExpr = 1;
        }
        if(unilex==ident)
        {
            if(contains(tableIdent, CHAINE)==-1&&testFct!=1) {
                erreur(5);
            }
            if(testFct==1 && contains(tableIdent, CHAINE)==-1 && containsArgs(CHAINE, tableIdent->tableIdentificateurs[contains(tableIdent, nameFonction)])==-1) {
                erreur(5);
            }
            if(testFct==1 && contains(tableIdent, CHAINE)==-1)
            {
                if(containsArgs(CHAINE, tableIdent->tableIdentificateurs[contains(tableIdent, nameFonction)])==-1)
                    erreur(5);
                addPCodeFonction("EMPI");
                char* strVal = malloc(sizeof(strVal)*(strlen(nameFonction)+2));
                sprintf(strVal, "@ %s %d", nameFonction, containsArgs(CHAINE, tableIdent->tableIdentificateurs[contains(tableIdent, nameFonction)]));
                addPCodeFonction(strVal);
                verifExpr=1;
            }
            else {
                if (strcmp(tableIdent->tableIdentificateurs[contains(tableIdent, CHAINE)].type, "CONST") == 0) {
                    if (tableIdent->tableIdentificateurs[contains(tableIdent, CHAINE)].typc == 1) {
                        if (varBool == 1 || strBool == 1)
                            erreur(8);
                        else
                            strBool = 1;
                    }
                }
                if (strcmp(tableIdent->tableIdentificateurs[contains(tableIdent, CHAINE)].type, "CONST") == 0) {
                    if (tableIdent->tableIdentificateurs[contains(tableIdent, CHAINE)].typc == 1) {
                        if (testFct == 1) {
                            addPCodeFonction("ECRC");
                            addPCodeFonction(tableIdent->tableIdentificateurs[contains(tableIdent, CHAINE)].valch);
                            addPCodeFonction("FINC");
                        } else {
                            addPCode("ECRC");
                            addPCode(tableIdent->tableIdentificateurs[contains(tableIdent, CHAINE)].valch);
                            addPCode("FINC");
                        }
                        verifExpr = 0;
                    } else {
                        if (testFct == 1) {
                            addPCodeFonction("EMPI");
                            addPCodeIntFonction(tableIdent->tableIdentificateurs[contains(tableIdent, CHAINE)].valent);
                        } else {
                            addPCode("EMPI");
                            addPCodeInt(tableIdent->tableIdentificateurs[contains(tableIdent, CHAINE)].valent);
                        }
                        verifExpr = 1;
                    }
                } else if (strcmp(tableIdent->tableIdentificateurs[contains(tableIdent, CHAINE)].type, "fct") == 0) {
                    if (verifFct() == 0)
                        return 0;
                    if (testFct == 1) {
                        addPCodeFonction("RETURN");
                    } else {
                        addPCode("RETURN");
                    }
                    return 1;
                } else {
                    if (testFct == 1) {
                        addPCodeFonction("EMPI");
                        addPCodeIntFonction(tableIdent->tableIdentificateurs[contains(tableIdent, CHAINE)].valent);
                        addPCodeFonction("CONT");
                    } else {
                        addPCode("EMPI");
                        addPCodeInt(tableIdent->tableIdentificateurs[contains(tableIdent, CHAINE)].valent);
                        addPCode("CONT");
                    }
                    verifExpr = 1;
                }
            }
            varBool = 1;
        }
        unilex = analex();
        return 1;
    }
    if(unilex==parouv){
        nbPar++;
        tabPar = realloc(tabPar, sizeof(int) * nbPar);
        tabPar[nbPar-1]=0;
        unilex = analex();
        if(expr()==0)
            return 0;
        if(unilex!=parfer)
            return 0;
        unilex=analex();
        for(int i=0; i<tabPar[nbPar-1]; i++)
        {
            if(testFct==1)
                addPCodeFonction(PILOP[SOM_PILOP-1]);
            else
                addPCode(PILOP[SOM_PILOP-1]);
            free(PILOP[SOM_PILOP-1]);
            PILOP = realloc(PILOP, sizeof(char*)*(SOM_PILOP-1));
            SOM_PILOP--;
        }
        nbPar--;
        tabPar = realloc(tabPar, sizeof(int)*nbPar);
        return 1;
    }
    else{
        if(unilex==moins)
        {
            unilex = analex();
            int value = terme();
            if(testFct==1)
                addPCodeFonction("MOIN");
            else
                addPCode("MOIN");
            return value;
        }
        else return 0;
    }
}

int op_bin(){
    //printf("Fonction op_bin\n");
    if(unilex==plus) {
        addPilop("ADDI");
    }
    else if(unilex==moins) {
        addPilop("SOUS");
    }
    else if(unilex==mult) {
        addPilop("MULT");
    }
    else {
        addPilop("DIVI");
    }
    if(nbPar>=1)
        tabPar[nbPar-1]+=1;
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
    nbPar=0;
    testFct = 0;
    NB_CONST_CHAINE = 0;
    DERNIERE_ADRESSE_VAR_GLOB = 0;
    SOM_PILEX=-1;
    tailleMaxPilex = 0;
    CO = 0;
    tailleMaxMemMove = 0;
    VAL_DE_CONST_CHAINE = malloc(sizeof(char*));
    CHAINE = malloc(sizeof(char)*LONG_MAX_CHAINE);
    sprintf(CHAINE, "%s", ".....");
    sprintf(TABLE_MOTS_RESERVES[0], "%s", "ALORS");
    sprintf(TABLE_MOTS_RESERVES[1], "%s", "CONST");
    sprintf(TABLE_MOTS_RESERVES[2], "%s", "DEBUT");
    sprintf(TABLE_MOTS_RESERVES[3], "%s", "ECRIRE");
    sprintf(TABLE_MOTS_RESERVES[4], "%s", "ENTIER");
    sprintf(TABLE_MOTS_RESERVES[5], "%s", "FAIRE");
    sprintf(TABLE_MOTS_RESERVES[6], "%s", "FIN");
    sprintf(TABLE_MOTS_RESERVES[7], "%s", "FONCTION");
    sprintf(TABLE_MOTS_RESERVES[8], "%s", "LIRE");
    sprintf(TABLE_MOTS_RESERVES[9], "%s", "PROGRAMME");
    sprintf(TABLE_MOTS_RESERVES[10], "%s", "SI");
    sprintf(TABLE_MOTS_RESERVES[11], "%s", "SINON");
    sprintf(TABLE_MOTS_RESERVES[12], "%s", "TANTQUE");
    sprintf(TABLE_MOTS_RESERVES[13], "%s", "VAR");
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
    SOURCE = malloc(sizeof(char)*strlen(source));
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
    if(prog()!=0) {
        printf("Le programme source est syntaxiquement correct\n");
    }
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
    /*printf("Nb de const chaine : %d\n", NB_CONST_CHAINE);
    for(int i=0; i<NB_CONST_CHAINE;i++)
    {
        printf("%s\n", VAL_DE_CONST_CHAINE[i]);
    }*/
    terminer();
    creer_fichier_code();
    interpreter();
}

void addConstChaine(char* chaine){
    VAL_DE_CONST_CHAINE = realloc(VAL_DE_CONST_CHAINE, sizeof(char*)*(NB_CONST_CHAINE+1));
    VAL_DE_CONST_CHAINE[NB_CONST_CHAINE] = malloc(sizeof(char)*strlen(chaine)+1);
    VAL_DE_CONST_CHAINE[NB_CONST_CHAINE] = strcpy(VAL_DE_CONST_CHAINE[NB_CONST_CHAINE], chaine);
    NB_CONST_CHAINE++;
}

void addPCode(char* chaine){
    P_CODE = realloc(P_CODE, sizeof(char*)*(CO+1));
    P_CODE[CO] = malloc(sizeof(char)*(strlen(chaine)+1));
    P_CODE[CO] = strcpy(P_CODE[CO], chaine);
    CO++;
}

void addPCodeFonction(char* chaine){
    P_CODE_FONCTION = realloc(P_CODE_FONCTION, sizeof(char*)*(CO+1));
    P_CODE_FONCTION[CO] = malloc(sizeof(char)*strlen(chaine)+1);
    P_CODE_FONCTION[CO] = strcpy(P_CODE_FONCTION[CO], chaine);
    CO++;
}

void addPilop(char* chaine){
    PILOP = realloc(PILOP, sizeof(char*)*(SOM_PILOP+1));
    PILOP[SOM_PILOP] = malloc(sizeof(char)*(strlen(chaine)+1));
    sprintf(PILOP[SOM_PILOP], "%s", chaine);
    SOM_PILOP++;
}

void addTabMemMove(int numMove){
    tabMemMove = realloc(tabMemMove, sizeof(int*)*(tailleMaxMemMove+1));
    tabMemMove[tailleMaxMemMove] = numMove;
    tailleMaxMemMove++;
}

int removeTabMemMove(){
    int numMove = tabMemMove[tailleMaxMemMove-1];
    tabMemMove = realloc(tabMemMove, sizeof(int*)*(tailleMaxMemMove-1));
    tailleMaxMemMove--;
    return numMove;
}

void addPCodeInt(int nb){
    char* string = malloc(sizeof(nb));
    sprintf(string, "%d", nb);
    P_CODE = realloc(P_CODE, sizeof(char*)*(CO+1));
    P_CODE[CO] = malloc(sizeof(char)*(strlen(string)+1));
    P_CODE[CO] = strcpy(P_CODE[CO], string);
    CO++;
    free(string);
}

void addPCodeIntFonction(int nb){
    char* string = malloc(sizeof(nb));
    sprintf(string, "%d", nb);
    P_CODE_FONCTION = realloc(P_CODE_FONCTION, sizeof(P_CODE_FONCTION)*(CO+1));
    P_CODE_FONCTION[CO] = malloc(sizeof(P_CODE_FONCTION[CO])*(strlen(string)+1));
    P_CODE_FONCTION[CO] = strcpy(P_CODE_FONCTION[CO], string);
    CO++;
    free(string);
}

void creer_fichier_code(){
    FILE* fileMachine = NULL;
    char* name = malloc(sizeof(char)*(strlen(SOURCE)+2));
    sprintf(name, "%.*s%s", (int)strlen(SOURCE)-3, SOURCE, ".COD");
    fileMachine = fopen(name, "w");
    int testBool = 0;
    for(int i=0; i<CO; i++)
    {
        if(strcmp(P_CODE[i], "EMPI")==0 || strcmp(P_CODE[i], "ALSN")==0||strcmp(P_CODE[i], "ALLE")==0)
            fprintf(fileMachine, "%s ", P_CODE[i]);
        else if(strcmp(P_CODE[i], "ECRC")==0)
        {
            fprintf(fileMachine, "%s ", P_CODE[i]);
            testBool = 1;
        }else if(strcmp(P_CODE[i], "FINC") == 0)
        {
            testBool = 0;
            fprintf(fileMachine, "%s\n", P_CODE[i]);
        }else if(testBool == 1)
            fprintf(fileMachine, "%s ", P_CODE[i]);
        else
            fprintf(fileMachine, "%s\n", P_CODE[i]);
    }
}

void interpreter(){
    MEMVAR = malloc(sizeof(MEMVAR)*DERNIERE_ADRESSE_VAR_GLOB+1);
    CO=0;
    while(strcmp(P_CODE[CO], "STOP")!=0)
    {
        if(strcmp(P_CODE[CO], "ADDI")==0){
            PILEX[SOM_PILEX-1] = PILEX[SOM_PILEX-1]+PILEX[SOM_PILEX];
            SOM_PILEX--;
            CO++;
        }
        else if(strcmp(P_CODE[CO], "SOUS")==0){
            PILEX[SOM_PILEX-1] = PILEX[SOM_PILEX-1]-PILEX[SOM_PILEX];
            SOM_PILEX--;
            CO++;
        }
        else if(strcmp(P_CODE[CO], "MULT")==0) {
            PILEX[SOM_PILEX-1] = PILEX[SOM_PILEX-1]*PILEX[SOM_PILEX];
            SOM_PILEX--;
            CO++;
        }
        else if(strcmp(P_CODE[CO], "DIVI")==0){
            if(PILEX[SOM_PILEX]==0)
                erreur(9);
            PILEX[SOM_PILEX-1] = PILEX[SOM_PILEX-1]/PILEX[SOM_PILEX];
            SOM_PILEX--;
            CO++;
        }
        else if(strcmp(P_CODE[CO], "MOIN")==0){
            PILEX[SOM_PILEX] = -PILEX[SOM_PILEX];
            CO++;
        }
        else if(strcmp(P_CODE[CO], "AFFE")==0){
            MEMVAR[PILEX[SOM_PILEX-1]] = PILEX[SOM_PILEX];
            SOM_PILEX-=2;
            CO++;
        }
        else if(strcmp(P_CODE[CO], "LIRE")==0){
            scanf("%d", MEMVAR+PILEX[SOM_PILEX]);
            SOM_PILEX--;
            CO++;
        }
        else if(strcmp(P_CODE[CO], "ECRL") == 0){
            printf("\n");
            CO++;
        }
        else if(strcmp(P_CODE[CO], "ECRE")==0){
            printf("%d", PILEX[SOM_PILEX]);
            SOM_PILEX--;
            CO++;
        }
        else if(strcmp(P_CODE[CO], "ECRC")==0){
            for(int i=0; i<strlen(P_CODE[CO+1]);i++)
                if(P_CODE[CO+1][i]!='\'')
                    printf("%c", P_CODE[CO+1][i]);
            CO+=3;
        }
        else if(strcmp(P_CODE[CO], "EMPI")==0){
            SOM_PILEX++;
            if(SOM_PILEX>=tailleMaxPilex) {
                PILEX = realloc(PILEX, sizeof(int) * ++tailleMaxPilex);
            }
            PILEX[SOM_PILEX] = (int)strtol(P_CODE[CO+1], NULL, 10);
            CO+=2;
        }
        else if(strcmp(P_CODE[CO], "CONT")==0){
            PILEX[SOM_PILEX] = MEMVAR[PILEX[SOM_PILEX]];
            CO++;
        }
        else if(strcmp(P_CODE[CO], "ALLE")==0){
            CO=(int)atoi(P_CODE[CO+1]);
        }
        else if(strcmp(P_CODE[CO], "ALSN")==0){
            if(PILEX[SOM_PILEX]==0)
                CO = (int)atoi(P_CODE[CO+1]);
            else
                CO+=2;
            SOM_PILEX--;
        }else if(strcmp(P_CODE[CO], "FINFONCTION")==0){
            if(strcmp(P_CODE[CO+1], "RETURN")!=0){
                PILEX = realloc(PILEX, sizeof(int)*--tailleMaxPilex);
                CO+=1;
            } else
                CO+=2;
        }
        else if(strcmp(P_CODE[CO], "RETURN")==0){
            if(strcmp(P_CODE[CO+2],"EMPIF")==0)
            {
                SOM_PILEX++;
                if(SOM_PILEX>=tailleMaxPilex){
                    PILEX = realloc(PILEX, sizeof(int)*++tailleMaxPilex);
                }
                PILEX[SOM_PILEX] = (int)strtol(P_CODE[CO+1], NULL, 10);
                CO+=3;
            }
            CO+=2;
        }else if(strcmp(P_CODE[CO], "ADDFCT")==0){
            nameFonction = strcpy(nameFonction, P_CODE[CO+1]);
            CO+=2;
        }
    }
    printf("\n");
}

void addFonction(char* string){
    Identificateurs identifi = tableIdent->tableIdentificateurs[contains(tableIdent, string)];
    for(int i=identifi.start;i<=identifi.end;i++) {
        if(P_CODE_FONCTION[i][0]=='@') {
            char* str = malloc(sizeof(str)*strlen(P_CODE_FONCTION[i])-1);
            char* strToken = strtok(P_CODE_FONCTION[i], " ");
            if(strcmp(strToken, "@")==0)
                strToken = strtok(NULL, " ");
            if(contains(tableIdent, strToken)==0)
                erreur(11);
            sprintf(nameFonction, "%s", strToken);
            strToken = strtok(NULL, " ");
            sprintf(str, "%d", tableIdent->tableIdentificateurs[contains(tableIdent, nameFonction)].args[
                    strtol(strToken, NULL, 10)]);
            if(testFct==1)
                addPCodeFonction(str);
            else
                addPCode(str);
        }else {
            if(testFct==1)
                addPCodeFonction(P_CODE_FONCTION[i]);
            else
                addPCode(P_CODE_FONCTION[i]);
        }
    }
}