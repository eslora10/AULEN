#include "transforma.h"

AFND * AFNDTransforma(AFND * afnd){
    AFND * afd;
    int i,j,num_simbolos_AFND, num_estados_AFND, esFin = 0,tipo;
    char* nombreIni, *nombre;
    char nombreF[128];

    num_simbolos_AFND=AFNDNumSimbolos(afnd);
    num_estados_AFND=AFNDNumEstados(afnd);

    afd= AFNDNuevo("finito",num_simbolos_AFND,num_estados_AFND);

    /*conseguir los simbolos paar el nuevo automata*/
    for(i=0;i<num_simbolos_AFND;i++)
        AFNDInsertaSimbolo(afd, AFNDSimboloEn(afnd, i));

    /*conseguir el estado inicial*/
    i=AFNDIndiceEstadoInicial(afnd);
    nombreIni=AFNDNombreEstadoEn(afnd, i);
    strcpy(nombreF,nombreIni);

    /*conseguimos los estados a los que transita el afnd desde su estado ini con LAMBDAS*/
    for(j=0;j<num_estados_AFND;j++)
        if(AFNDCierreLTransicionIJ(afnd, i, j)){
            nombre=AFNDNombreEstadoEn(afnd,j);
            tipo=AFNDTipoEstadoEn(afnd, j);
            esFin = (tipo== FINAL ||tipo== INICIAL_Y_FINAL);
            strcat(nombreF,nombre);
        }
    if (esFin) {
        AFNDInsertaEstado(afd,nombreF,INICIAL_Y_FINAL);
    }else{
        AFNDInsertaEstado(afd,nombreF,INICIAL);
    }


    return afd;
}
