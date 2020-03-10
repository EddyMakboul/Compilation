PROGRAMME exemple;
var i, j;
DEBUT
    i:=9;
    tantque i faire
    debut
        j:=9;
        tantque j faire
        debut
            ecrire(i, j);
            ecrire();
            j := j-1;
        fin
        ecrire(i, j);
        ecrire();
        i:=i-1;
    fin
    ecrire(i, j);
    ecrire();
FIN.
