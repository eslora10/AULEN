

AFND * AFNDTransforma(AFND * afnd){
    AFND * afd;
    int i,num_simbolos;
    char* nombreIni;
    num_simbolos=AFNDNumSimbolos(afnd);

    afd= AFNDNuevo("finito",num_simbolos,AFNDNumEstados(afnd));

    /*conseguir los simbolos paar el nuevo automata*/
    for(i=0;i<num_simbolos;i++)
        AFNDInsertaSimbolo(afd, AFNDSimboloEn(afnd, i));

    /*conseguir el estado inicial*/
    i=AFNDIndiceEstadoInicial(afnd);
    nombreIni=AFNDNombreEstadoEn(afnd, i);




}
