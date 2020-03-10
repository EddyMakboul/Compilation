PROGRAMME prgm;
var resultat;
debut
    resultat:=10;
    si resultat-0 alors
    debut
        tantque resultat faire
        debut
            ecrire(resultat, ' ');
            resultat:= resultat-1;
        fin
        ecrire();
    fin
    sinon
        ecrire('le resultat est nul');
fin.
