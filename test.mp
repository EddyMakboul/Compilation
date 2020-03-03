PROGRAMME exemple;
CONST testConst=52, otherConst='test de constante 2', test='test d''erreur';
VAR nb, var2, var3;
DEBUT
    { Test de commentaire }
    ECRIRE('Entrez un nombre entier: ');
    LIRE(nb);
    ECRIRE('Vous avez ecrit : ', nb);
    ECRIRE();
    nb:=(testConst);
    ECRIRE('Ecriture d''une variable: ', nb);
    ECRIRE();
    ECRIRE('Ecriture d''une expr : ', 5*5);
    ECRIRE();
    ECRIRE('Ecriture d''une constante string : ', otherConst);
FIN
