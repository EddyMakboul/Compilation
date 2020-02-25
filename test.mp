PROGRAMME exemple;
CONST testConst=52, otherConst='test de constante 2', test='test d''erreur';
VAR nb, var2, var3;
DEBUT
    { Test de commentaire }
    ECRIRE('Entrez un nombre entier:');
    ECRIRE();
    LIRE(nb);
    ECRIRE('Vous avez ecrit : ', nb);
    ECRIRE();
    nb:=(testConst);
    ECRIRE(nb);
    ECRIRE();
    ECRIRE(5*5);
    ECRIRE();
    ECRIRE(otherConst, 'je teste la validite du compilateur', 5*5);
FIN
