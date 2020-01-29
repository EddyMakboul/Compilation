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

void erreur(int numErreur);
void lire_car(FILE * fichier);
void sauter_separateurs(FILE * fichier);
char* t_unilex_to_string(T_UNILEX unilex);
T_UNILEX reco_entier(FILE* fichier);
T_UNILEX reco_chaine(FILE* fichier);
T_UNILEX reco_ident_ou_mot_reserve(FILE* fichier);
int est_un_mot_reserve();
T_UNILEX reco_symb(FILE* fichier);
void analex(FILE* fichier);
void initialiser(FILE** fichier);
void terminer(FILE** fichier);
void analyseur_lexical(char* source);

#endif