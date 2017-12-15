#include "transforma.h"

struct Estado {
    char *nombre;
    int *lista_actual;
    int tipo;
};

struct Transicion {
    char *ini;
    char *fin;
    char *simbolo;
};

int in(char *nombre, struct Estado * estados, int len) {
    int i;
    for (i = 0; i < len; i++)
        if (!strcmp(nombre, estados[i].nombre))
            return 1;
    return 0;

}

AFND * AFNDTransforma(AFND * afnd) {
    AFND *afd = NULL;
    struct Estado *new_estados = NULL;
    struct Transicion *new_trans = NULL;
    int num_estados = 1, num_simbolos, num_trans = 0, num_estados_nd, final = 0, tipo;
    int i, j, k, l, estado, *lista_estados;
    char *nombre, nombreF[128];

    strcpy(nombreF, "");

    num_estados_nd = AFNDNumEstados(afnd);
    num_simbolos = AFNDNumSimbolos(afnd);

    new_estados = (struct Estado *) malloc(sizeof (struct Estado));
    new_estados[0].lista_actual = (int*) calloc(num_estados_nd, sizeof (int));
    lista_estados = (int*) calloc(num_estados_nd, sizeof (int));


    /*Conseguimos el indice del estado inicial y su nombre*/
    i = AFNDIndiceEstadoInicial(afnd);
    nombre = AFNDNombreEstadoEn(afnd, i);
    new_estados[0].lista_actual[i] = 1;

    /*Annadimos el nombre del estado inicial al nombre del nuevo estado*/
    strcat(nombreF, nombre);

    /*Vemos las transiciones lambda desde el inicial a otros estados y las anandimos*/
    for (j = 0; j < num_estados_nd; j++) {
        if (AFNDCierreLTransicionIJ(afnd, i, j) && i != j) {
            new_estados[0].lista_actual[j] = 1;
            /*Annadimos el estado j al nombre del nuevo estado*/
            nombre = AFNDNombreEstadoEn(afnd, j);
            strcat(nombreF, nombre);
            tipo = AFNDTipoEstadoEn(afnd, j);
            if (tipo == INICIAL_Y_FINAL || tipo == FINAL)
                final = 1;
        }
    }
    /*Creamos un nuevo estado*/
    new_estados[0].nombre = (char *) malloc((strlen(nombreF) + 1) * sizeof (char));
    strcpy(new_estados[0].nombre, nombreF);
    if (final || AFNDTipoEstadoEn(afnd, i) == INICIAL_Y_FINAL) {
        new_estados[0].tipo = INICIAL_Y_FINAL;
    } else {
        new_estados[0].tipo = INICIAL;
    }


    strcpy(nombreF, "");
    /*Iteramos en el conjunto de estados que forma el nuevo estado inicial y 
     * vemos sus transiciones*/
    for (estado = 0; estado < num_estados; estado++)
        for (j = 0; j < num_simbolos; j++) {
            for (k = 0; k < num_estados_nd; k++)
                lista_estados[k] = 0;
            for (i = 0; i < num_estados_nd; i++) {
                if (new_estados[estado].lista_actual[i] == 1) {
                    /*Iteramos en los simbolos*/
                    /*Iteramos en los estados finales*/
                    for (k = 0; k < num_estados_nd; k++) {
                        /*Vemos si existe una transicion i, j, k*/
                        if (AFNDTransicionIndicesEstadoiSimboloEstadof(afnd, i, j, k)) {
                            /*Metemos el nombre del estado en la nueva cadena*/

                            lista_estados[k] = 1;
                            nombre = AFNDNombreEstadoEn(afnd, k);
                            if (!strstr(nombreF, nombre))
                                strcat(nombreF, nombre);

                            /*Miramos si el tipo es final*/
                            tipo = AFNDTipoEstadoEn(afnd, k);
                            if (tipo == INICIAL_Y_FINAL || tipo == FINAL)
                                final = 1;

                            /*Miramos las transiciones lambda desde k*/
                            for (l = 0; l < num_estados_nd; l++) {
                                if (AFNDCierreLTransicionIJ(afnd, k, l) && k != l) {
                                    nombre = AFNDNombreEstadoEn(afnd, l);
                                    if (!strstr(nombreF, nombre))
                                        strcat(nombreF, nombre);
                                    lista_estados[l] = 1;

                                    /*Miramos si el tipo es final*/
                                    tipo = AFNDTipoEstadoEn(afnd, l);
                                    if (tipo == INICIAL_Y_FINAL || tipo == FINAL)
                                        final = 1;

                                }
                            }
                        }


                    }


                }
            }
            /*Creamos el nuevo estado y la nueva transicion*/
            if (strcmp("", nombreF)) {
                if (!in(nombreF, new_estados, num_estados)) {
                    num_estados++;
                    new_estados = (struct Estado*) realloc(new_estados, num_estados * sizeof (struct Estado));
                    new_estados[num_estados - 1].lista_actual = (int*) calloc(num_estados_nd, sizeof (int));
                    for (l = 0; l < num_estados_nd; l++) {
                        new_estados[num_estados - 1].lista_actual[l] = lista_estados[l];
                        lista_estados[l] = 0;
                    }

                    new_estados[num_estados - 1].nombre = (char *) malloc(sizeof (char)*(strlen(nombreF) + 1));
                    strcpy(new_estados[num_estados - 1].nombre, nombreF);
                    if (final)
                        new_estados[num_estados - 1].tipo = FINAL;
                    else
                        new_estados[num_estados - 1].tipo = NORMAL;
                }


                num_trans++;
                new_trans = (struct Transicion *) realloc(new_trans, num_trans * sizeof (struct Transicion));
                new_trans[num_trans - 1].ini = (char*) malloc(sizeof (char)*(strlen(new_estados[estado].nombre) + 1));
                strcpy(new_trans[num_trans - 1].ini, new_estados[estado].nombre);
                new_trans[num_trans - 1].fin = (char*) malloc(sizeof (char)*(strlen(nombreF) + 1));
                strcpy(new_trans[num_trans - 1].fin, nombreF);
                nombre = AFNDSimboloEn(afnd, j);
                new_trans[num_trans - 1].simbolo = (char*) malloc(sizeof (char)*(strlen(nombre) + 1));
                strcpy(new_trans[num_trans - 1].simbolo, nombre);
                strcpy(nombreF, "");
            }
        }

    /*Creamos el automata finito*/
    afd = AFNDNuevo("finito", num_estados, num_simbolos);

    /*Metemos los simbolos*/
    for (i = 0; i < num_simbolos; i++) {
        AFNDInsertaSimbolo(afd, AFNDSimboloEn(afnd, i));
    }

    /*Metemos los estados*/
    for (i = 0; i < num_estados; i++) {
        AFNDInsertaEstado(afd, new_estados[i].nombre, new_estados[i].tipo);
    }

    /*Metemos las transiciones*/
    for (i = 0; i < num_trans; i++) {
        AFNDInsertaTransicion(afd, new_trans[i].ini, new_trans[i].simbolo, new_trans[i].fin);
    }

    /*Liberamos las listas de estados y transiciones*/
    for (i = 0; i < num_estados; i++) {
        free(new_estados[i].nombre);
        free(new_estados[i].lista_actual);
    }
    free(new_estados);

    for (i = 0; i < num_trans; i++) {
        free(new_trans[i].ini);
        free(new_trans[i].fin);
        free(new_trans[i].simbolo);
    }
    free(new_trans);

    free(lista_estados);

    return afd;
}
