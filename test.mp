PROGRAMME exemple;
CONST testConst=52, otherConst='test de constante 2', test='test d''erreur';
VAR nb, var2, var3;
DEBUT
    { Test de commentaire }
    ECRIRE('Entrez un nombre entier:');
    LIRE(nb, var2);
    nb:=(testConst);
    ECRIRE('test d''ecriture', 5*5, otherConst);
    LIRE(nb);
FIN
