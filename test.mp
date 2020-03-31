PROGRAMME exemple;
var i, j;
DEBUT
    i:=8;
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
        si i-1 alors
        debut
        fin
        sinon
        debut
            j:=9;
            tantque j faire
            debut
                ecrire(i-1, j);
                ecrire();
                j := j-1;
            fin
            ecrire(i-1, j);
            ecrire();
        fin
        i:=i-1;
    fin
    ecrire();
FIN.
