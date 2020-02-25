#ifndef DEF_ANALYSEURLEXICAL_H
#define DEF_ANALYSEURLEXICAL_H
#include <stdio.h>
#include "TableIdentificateurs.h"
#define LONG_MAX_IDENT 20
#define LONG_MAX_CHAINE 50
#define NB_MOTS_RESERVES 7

// Variables globales
char * SOURCE;
char CARLU;
int NOMBRE;
char* CHAINE;
int NUM_LIGNE;
char TABLE_MOTS_RESERVES[NB_MOTS_RESERVES][10];
TableIdentificateurs* tableIdent;
FILE* file;
int NB_CONST_CHAINE;
char** VAL_DE_CONST_CHAINE;
int DERNIERE_ADRESSE_VAR_GLOB;
int varBool;
int strBool;

char** MEMVAR;
char** P_CODE;
int CO;
int* PILEX;
int SOM_PILEX;
char** PILOP;
int SOM_PILOP;

typedef enum T_UNILEX {
    motcle,
    ident,
    ent,
    ch,
    virg,
    ptvirg,
    point,
    deuxpts,
    parouv,
    parfer,
    inf,
    sup,
    eg,
    plus,
    moins,
    mult,
    divi,
    infe,
    supe,
    diff,
    aff
} T_UNILEX;

T_UNILEX unilex;

/* ---------------- Analyseur Lexical ------------ */
void erreur(int numErreur);
void lire_car();
void sauter_separateurs();
char* t_unilex_to_string(T_UNILEX unilex);
T_UNILEX reco_entier();
T_UNILEX reco_chaine();
T_UNILEX reco_ident_ou_mot_reserve();
int est_un_mot_reserve();
T_UNILEX reco_symb();
T_UNILEX analex();
void initialiser(TableIdentificateurs* tableIdent);
void terminer();
void analyseur_lexical(char* source, TableIdentificateurs* tableIdent);

/* ---------------- Analyseur syntaxique ---------- */
int prog();
int decl_const();
int decl_var();
int bloc();
int instruction();
int affectation();
int lecture();
int ecriture();
int ecr_exp();
int expr();
int suite_terme();
int terme();
int op_bin();
void anasynt();
void analyseur_syntaxique(char* source, TableIdentificateurs* tableIdentificateurs);

/* ----------------- Analyseur sémantique --------- */
void addConstChaine(char* chaine);

/* ----------------- Génération de code ----------- */
void addPCode(char* chaine);
void addPCodeInt(int nb);
void addPilop(char* chaine);

#endif