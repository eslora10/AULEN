#include "transforma.h"

struct Estado {
    char nombre[128];
    int tipo;
};

struct Transicion {
    char ini[128];
    char fin[128];
    char simbolo[16];
};

AFND * AFNDTransforma(AFND * afnd) {
    AFND * afd = NULL;
    int num_estados = 0, num_trans = 0;
    struct Estado * new_estados = NULL;
    struct Transicion *new_trans = NULL;
    struct Estado e;
    struct Transicion tr;
    int i, j, k, l, num_simbolos_AFND, num_estados_AFND, esFin = 0, tipo, seguir = 1;
    char* nombreIni = NULL, *nombre = NULL;
    char nombreF[128];


    /************/
    int * listaEstados;
    int * listaEstadosSig;
    int * estudiados;
    /************/

    num_simbolos_AFND = AFNDNumSimbolos(afnd);
    num_estados_AFND = AFNDNumEstados(afnd);

    listaEstados = (int*) calloc(num_estados_AFND, sizeof (int));
    listaEstadosSig = (int*) calloc(num_estados_AFND, sizeof (int));
    estudiados = (int*) calloc(num_estados_AFND, sizeof (int));

    /*afd= AFNDNuevo("finito",num_simbolos_AFND,num_estados_AFND);*/

    /*conseguir los simbolos paar el nuevo automata*/
    /*for(i=0;i<num_simbolos_AFND;i++)
        AFNDInsertaSimbolo(afd, AFNDSimboloEn(afnd, i));*/

    /*conseguir el estado inicial*/
    i = AFNDIndiceEstadoInicial(afnd);
    estudiados[i] = 1;
    nombreIni = AFNDNombreEstadoEn(afnd, i);
    listaEstados[i] = 1;
    strcpy(nombreF, nombreIni);

    /*conseguimos los estados a los que transita el afnd desde su estado ini con LAMBDAS*/
    for (j = 1; j < num_estados_AFND; j++)
        if (AFNDCierreLTransicionIJ(afnd, i, j)) {
            /*asignamos transicion al estado en la pos j*/
            listaEstados[j] = 1;
            estudiados[j] = 1;
            nombre = AFNDNombreEstadoEn(afnd, j);
            tipo = AFNDTipoEstadoEn(afnd, j);
            if (tipo == FINAL || tipo == INICIAL_Y_FINAL)
                esFin = 1;
            strcat(nombreF, nombre);
        }
    strcpy(e.nombre, nombreF);
    if (esFin) {
        e.tipo = INICIAL_Y_FINAL;
        esFin = 0;
    } else {
        e.tipo = INICIAL;
    }
    num_estados++;
    new_estados = (struct Estado*) realloc(new_estados, num_estados);
    strcpy(new_estados[num_estados - 1].nombre, e.nombre);
    new_estados[num_estados - 1].tipo = e.tipo;

    strcpy(tr.ini, nombreF);

    while (seguir) {
        seguir = 0;
        /*iteramos en la lista de simbolo de entrada (indice i)*/
        for (i = 0; i < num_simbolos_AFND; i++) {
            /*iteramos en la lista de estados, j es el estado actual*/
            for (j = 0; j < num_estados_AFND; j++) {
                if (listaEstados[j] == 1) {
                    /*TODO Mirar si marcar como estudiado es aqui*/
                    /*estudiados[j] = 1;*/ /*Marcamos el estado j como estudiado*/
                    strcpy(nombreF, "");
                    /*iteramos en el resto de estados, veamos a donde podemos ir*/
                    for (k = 0; k < num_estados_AFND; k++) {
                        if (AFNDTransicionIndicesEstadoiSimboloEstadof(afnd, j, i, k)) {
                            /*CASO: podemos ir al estado k*/
                            nombre = AFNDNombreEstadoEn(afnd, k);
                            strcat(nombreF, nombre);

                            /*Anyadir estado k a la lista listaEstadosSig  ESTHER KNOWS WHY*/
                            listaEstadosSig[k] = 1;
                            estudiados[k] = 1;
                            tipo = AFNDTipoEstadoEn(afnd, k);
                            if (tipo == FINAL || tipo == INICIAL_Y_FINAL)
                                esFin = 1;

                            /*iteramos los estados Siguientes para ver si podemos transitar CON LAMBDAS*/
                            for (l = 0; l < num_estados_AFND; l++) {
                                if (AFNDCierreLTransicionIJ(afnd, k, l) && k != l) {
                                    /*asignamos transicion al estado en la pos l*/
                                    listaEstadosSig[l] = 1;
                                    estudiados[l] = 1;
                                    nombre = AFNDNombreEstadoEn(afnd, l);
                                    tipo = AFNDTipoEstadoEn(afnd, l);
                                    if (tipo == FINAL || tipo == INICIAL_Y_FINAL)
                                        esFin = 1;
                                    strcat(nombreF, nombre);
                                }
                            }

                        }
                    }
                    printf("%s\n", nombreF);
                    if (strcmp("", nombreF) != 0) {
                        /*Creamos el nuevo estado*/
                        strcpy(e.nombre, nombreF);
                        if (esFin) {
                            e.tipo = FINAL;
                            esFin = 0;

                        } else
                            e.tipo = NORMAL;

                        num_estados++;
                        new_estados = (struct Estado*) realloc(new_estados, num_estados);
                        strcpy(new_estados[num_estados - 1].nombre, e.nombre);
                        new_estados[num_estados - 1].tipo = e.tipo;

                        /*Creamos una transicion*/
                        strcpy(tr.fin, nombreF);
                        strcpy(tr.simbolo, AFNDSimboloEn(afnd, i));
                        num_trans++;
                        new_trans = realloc(new_trans, num_trans);
                        strcpy(new_trans[num_trans - 1].ini, tr.ini);
                        strcpy(new_trans[num_trans - 1].fin, tr.fin);
                        strcpy(new_trans[num_trans - 1].simbolo, tr.simbolo);

                        /*Inicializamos el estado inicial de la proxima transicion
                         al estado en el que estamos ahora*/
                        strcpy(tr.ini, nombreF);
                    }
                }
            }
        }


        /*Cambiamos la lista de estados actual por la de estados siguientes
         ponemos los estados siguientes a 0*/
        for (l = 0; l < num_estados_AFND; l++) {
            listaEstados[l] = listaEstadosSig[l];
            listaEstadosSig[l] = 0;
        }
        for (l = 0; l < num_estados_AFND; l++) {
            if (!estudiados[l]) {
                seguir = 1;
                break;
            }
        }


    }
    /*Creamos el automata final*/
    afd = AFNDNuevo("finito", num_estados, num_simbolos_AFND);

    for (i = 0; i < num_simbolos_AFND; i++)
        AFNDInsertaSimbolo(afd, AFNDSimboloEn(afnd, i));

    for (i = 0; i < num_estados; i++)
        AFNDInsertaEstado(afd, new_estados[i].nombre, new_estados[i].tipo);
    for (i = 0; i < num_trans; i++) {
        AFNDInsertaTransicion(afd, new_trans[i].ini, new_trans[i].simbolo,
                new_trans[i].fin);
    }


    return afd;
}
