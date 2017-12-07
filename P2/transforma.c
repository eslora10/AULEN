#include "transforma.h"

AFND * AFNDTransforma(AFND * afnd){
    AFND * afd;
    int i,j,k,l,num_simbolos_AFND, num_estados_AFND, esFin = 0,tipo;
    char* nombreIni, *nombre;
    char nombreF[128];


    /************/
    int * listaEstados;
    int * listaEstadosSig;
    /************/

    num_simbolos_AFND=AFNDNumSimbolos(afnd);
    num_estados_AFND=AFNDNumEstados(afnd);

    listaEstados=(int*) calloc(num_estados_AFND,sizeof(int));
    listaEstadosSig=(int*) calloc(num_estados_AFND,sizeof(int));


    afd= AFNDNuevo("finito",num_simbolos_AFND,num_estados_AFND);

    /*conseguir los simbolos paar el nuevo automata*/
    for(i=0;i<num_simbolos_AFND;i++)
        AFNDInsertaSimbolo(afd, AFNDSimboloEn(afnd, i));

    /*conseguir el estado inicial*/
    i=AFNDIndiceEstadoInicial(afnd);
    nombreIni=AFNDNombreEstadoEn(afnd, i);
    listaEstados[i]=1;
    strcpy(nombreF,nombreIni);

    /*conseguimos los estados a los que transita el afnd desde su estado ini con LAMBDAS*/
    for(j=0;j<num_estados_AFND;j++)
        if(AFNDCierreLTransicionIJ(afnd, i, j)){
            /*asignamos transicion al estado en la pos j*/
            listaEstados[j]=1;

            nombre=AFNDNombreEstadoEn(afnd,j);
            tipo=AFNDTipoEstadoEn(afnd, j);
            esFin = (tipo== FINAL ||tipo== INICIAL_Y_FINAL);
            strcat(nombreF,nombre);
        }
    if (esFin)
        AFNDInsertaEstado(afd,nombreF,INICIAL_Y_FINAL);
    else
        AFNDInsertaEstado(afd,nombreF,INICIAL);


    /*iter Simbolo indice i*/
    for(i=0;i<num_simbolos_AFND;i++)
        /*iter estados (los que tengo dentro del nuevo estado)==listaEstados indice j*/
        for(j=0;j<num_estados_AFND;j++)
            if(listaEstados[j]==1){
                listaEstados[j]=0;
                strcpy(nombreF,"");
                /*iteramos en el resto de estados, veamos a donde podemos ir*/
                for(k=0;k<num_estados_AFND;k++)
                    if(AFNDTransicionIndicesEstadoiSimboloEstadof(afnd, j, i, k)){
                    /*CASO: podemos ir al estado k*/
                        nombre=AFNDNombreEstadoEn(afnd, k);
                        strcat(nombreF,nombre);
                        /********es necesario poner aqui esFin=0?????********/

                        /*TODO anyadir estado k a la lista listaEstadosSig  ESTHER KNOWS WHY*/

                        
                        /*iteramos los estados Siguientes para ver si podemos transitar CON LAMBDAS*/
                        for(l=0;l<num_estados_AFND;l++)
                            if(AFNDCierreLTransicionIJ(afnd, k,l)){
                                /*asignamos transicion al estado en la pos l*/
                                listaEstadosSig[l]=1;

                                nombre=AFNDNombreEstadoEn(afnd,l);
                                tipo=AFNDTipoEstadoEn(afnd, l);
                                esFin = (tipo== FINAL ||tipo== INICIAL_Y_FINAL);
                                strcat(nombreF,nombre);
                            }
                        if (esFin)
                            AFNDInsertaEstado(afd,nombreF,FINAL);
                        else
                            AFNDInsertaEstado(afd,nombreF,NORMAL);

                    /*TODO conseguimos la transicion en el nuevo automata*/
                    }
                }


    return afd;
}
