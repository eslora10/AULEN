#include "ap.h"
#include "list.h"
#include "estado.h"
#include "palabra.h"
#include "stack.h"
#include <string.h>
#include <stdio.h>

#define LAMBDA "lambda"

/*funciones de transicion*/
struct _transicionAP {
    List* ****acciones;
    int num_simbolos_pila;
    int num_estados;
    int num_simbolos_entrada;
};

typedef struct _transicionAP TransicionAP;

struct _AP {
    char *nombre;
    List *alfabeto; /*Set*/
    int len_alfabeto;
    List *alfabeto_pila; /*Set, se reserva un caracter para la lambda*/
    int len_alfabeto_pila;
    List *estados; /*Set*/
    int len_estados;
    Relacion *lambdas;
    Palabra *palabra;
    ConfiguracionApnd *q;
    TransicionAP * fn_tansicion;
    Estado *inicial;
};

void destroy_p_string(void* s) {
    free(s);
}

void *copy_p_string(const void* s1) {
    char *s2;

    s2 = (char*) malloc(sizeof (char)* strlen((char*) s1) + 1);

    strcpy(s2, (char*) s1);

    return s2;

}

int print_p_string(FILE *f, const void*s) {
    return fprintf(f, "%s ", (char*) s);
}

TransicionAP *transicionAPNueva(char * nombre, int num_simbolos_pila,
        int num_estados, int num_simbolos_entrada) {
    TransicionAP *t;
    int pila, estado_ini, estado_fin, entrada;

    if (!nombre) return NULL;

    t = (TransicionAP *) malloc(sizeof (TransicionAP));
    if (!t) return NULL;

    t->num_simbolos_pila = num_simbolos_pila;
    t->num_estados = num_estados;
    t->num_simbolos_entrada = num_simbolos_entrada + 1; /*Para la lambda*/

    t->acciones = (List* ****) malloc(num_simbolos_pila * sizeof (List ****));
    for (pila = 0; pila < num_simbolos_pila; pila++) {
        t->acciones[pila] = (List ****) malloc(num_estados * sizeof (List***));
        for (estado_ini = 0; estado_ini < num_estados; estado_ini++) {
            t->acciones[pila][estado_ini] = (List ***) malloc(num_estados * sizeof (List**));
            for (estado_fin = 0; estado_fin < num_estados; estado_fin++) {
                t->acciones[pila][estado_ini][estado_fin] = (List **) malloc((num_simbolos_entrada + 1) * sizeof (List*));
                for (entrada = 0; entrada < (num_simbolos_entrada + 1); entrada++)
                    t->acciones[pila][estado_ini][estado_fin][entrada] =
                        list_ini((destroy_element_function_type) palabraElimina,
                        (copy_element_function_type) palabraCopia,
                        (print_element_function_type) palabraImprime,
                        (cmp_element_function_type) palabraCompara);
            }
        }
    }
    return t;
}

void transicionAPLibera(TransicionAP *t) {
    int pila, estado_ini, estado_fin, entrada;
    if (!t) return;

    for (pila = 0; pila < t->num_simbolos_pila; pila++) {
        for (estado_ini = 0; estado_ini < t->num_estados; estado_ini++) {
            for (estado_fin = 0; estado_fin < t->num_estados; estado_fin++) {
                for (entrada = 0; entrada < t->num_simbolos_entrada; entrada++)
                    list_destroy(t->acciones[pila][estado_ini][estado_fin][entrada]);
                free(t->acciones[pila][estado_ini][estado_fin]);
            }
            free(t->acciones[pila][estado_ini]);
        }
        free(t->acciones[pila]);
    }
    free(t->acciones);
    free(t);
}

TransicionAP *transicionAPinserta(TransicionAP *t, int pila, int estado_ini,
        int estado_fin, int entrada, Palabra* palabra) {
    if (!t || !palabra) return NULL;
    if (pila >= t->num_simbolos_pila || estado_ini >= t->num_estados ||
            estado_fin >= t->num_estados || entrada >= t->num_simbolos_entrada)
        return NULL;
    list_insertFirst(t->acciones[pila][estado_ini][estado_fin][entrada], (void*) palabra);

    return t;

}

List *transicionAPbusca(TransicionAP *t, int pila, int estado_ini,
        int estado_fin, int entrada) {
    if (pila > t->num_simbolos_pila || estado_ini > t->num_estados ||
            estado_fin > t->num_estados || entrada > t->num_simbolos_entrada)
        return NULL;
    return t->acciones[pila][estado_ini][estado_fin][entrada];
}

/*fin funciones transicion*/
AP * APNuevo(char * nombre,
        int num_estados,
        int num_simbolos_entrada,
        int num_simbolos_pila) {
    AP *ap;

    ap = (AP*) malloc(sizeof (AP));
    if (!ap) return NULL;

    ap->nombre = (char*) malloc((strlen(nombre) + 1) * sizeof (char));
    if (!ap->nombre) return NULL;
    strcpy(ap->nombre, nombre);

    ap->alfabeto = list_ini((destroy_element_function_type) destroy_p_string, copy_p_string,
            print_p_string, (cmp_element_function_type) strcmp);

    ap->estados = list_ini((destroy_element_function_type) estadoElimina,
            (copy_element_function_type) estado_copy, (print_element_function_type) estadoImprime,
            (cmp_element_function_type) estadoCompara);

    ap->alfabeto_pila = list_ini((destroy_element_function_type) destroy_p_string, copy_p_string,
            print_p_string, (cmp_element_function_type) strcmp);

    ap->lambdas = relacionNueva("Lambda pura", num_estados);
    ap->palabra = palabraNueva();
    ap->q = configuracionApndIni();
    ap->fn_tansicion = transicionAPNueva(nombre, num_simbolos_pila,
            num_estados, num_simbolos_entrada);

    ap->len_alfabeto_pila = num_simbolos_pila;
    ap->len_alfabeto = num_simbolos_entrada;
    ap->len_estados = num_estados;

    /*ap->pila = stack_ini((destroy_element_function_type) free, copy_p_string,
            print_p_string, (cmp_element_function_type) strcmp);*/

    return ap;
}

void APElimina(AP * p_ap) {
    if (p_ap->nombre)
        free(p_ap-> nombre);
    if (p_ap->alfabeto)
        list_destroy(p_ap->alfabeto);
    if (p_ap->alfabeto_pila)
        list_destroy(p_ap->alfabeto_pila);
    if (p_ap->estados)
        list_destroy(p_ap->estados);
    if (p_ap->fn_tansicion)
        transicionAPLibera(p_ap->fn_tansicion);
    if (p_ap->inicial)
        estadoElimina(p_ap->inicial);
    if (p_ap->lambdas)
        relacionElimina(p_ap->lambdas);
    if (p_ap->palabra)
        palabraElimina(p_ap->palabra);
    if (p_ap->q)
        configuracionApndDestroy(p_ap->q);

    free(p_ap);

}

void APImprime(FILE * fd, AP* p_ap) {
    int i, j, k, l;
    char* simbolo;

    fprintf(fd, "********************************** AUTÓMATA A PILA *****************************************\n");
    fprintf(fd, "AP={ %s\n", p_ap->nombre);
    fprintf(fd, "\n\tSigma={");
    list_print(fd, p_ap->alfabeto);
    fprintf(fd, "}\n");
    fprintf(fd, "\n\n\tGamma={");
    list_print(fd, p_ap->alfabeto_pila);
    fprintf(fd, "}\n");
    fprintf(fd, "\n\n\tQ={");
    list_print(fd, p_ap->estados);
    fprintf(fd, "}\n");
    fprintf(fd, "\n\n\tConfiguracion actual:\n");
    configuracionApndPrint(fd, p_ap->q);
    fprintf(fd, "\n\n\tCadena inicial:\n");
    palabraImprime(fd, p_ap->palabra);
    fprintf(fd, "\n\n\tTransiciones Lambda Puras:\n");
    relacionImprime(fd, p_ap->lambdas);
    fprintf(fd, "\n\n\tTransiciones que modifican entrada o pila: [ <cima pila> "
            "<estado inicial> <estado final> <simbolo entrada> ==> ] <accion en la pila>\n");
    for (i = 0; i < (p_ap->fn_tansicion)->num_simbolos_pila; i++)
        for (j = 0; j < (p_ap->fn_tansicion)->num_estados; j++)
            for (k = 0; k < (p_ap->fn_tansicion)->num_estados; k++)
                for (l = 0; l < (p_ap->fn_tansicion)->num_simbolos_entrada; l++) {
                    if (list_isEmpty((p_ap->fn_tansicion)->acciones[i][j][k][l]) == FALSE) {
                        fprintf(fd, "[");
                        fprintf(fd, "%s,", (char*) list_get_pos(p_ap->alfabeto_pila, i));
                        estadoImprime(fd, list_get_pos(p_ap->estados, j));
                        fprintf(fd, ",");
                        estadoImprime(fd, list_get_pos(p_ap->estados, k));
                        fprintf(fd, ",");
                        simbolo = (char*) list_get_pos(p_ap->alfabeto, l);
                        if (simbolo)
                            fprintf(fd, "%s]==>", simbolo);
                        else
                            fprintf(fd, "%s]==>", LAMBDA);
                        list_print(fd, (p_ap->fn_tansicion)->acciones[i][j][k][l]);
                        fprintf(fd, "\n");
                    }
                }

    fprintf(fd, "}\n");


}

AP * APInsertaSimboloAlfabetoEntrada(AP * p_ap, char * simbolo) {
    /*no control de errores, asumimos el usuario sabe lo que hace*/

    if (list_belongs(p_ap->alfabeto, (void *) simbolo))
        return p_ap;

    list_insertFirst(p_ap->alfabeto, (void *) simbolo);

    return p_ap;

}

AP * APInsertaSimboloAlfabetoPila(AP * p_ap, char * simbolo) {
    /*no control de errores, asumimos el usuario sabe lo que hace*/

    if (list_belongs(p_ap->alfabeto_pila, (void *) simbolo))
        return p_ap;

    list_insertFirst(p_ap->alfabeto_pila, simbolo);

    return p_ap;

}

AP * APInsertaEstado(AP * p_ap, char * nombre, int tipo) {
    Estado *e = NULL;


    e = estadoNuevo(nombre, tipo);
    if (!e)
        return NULL;

    if (tipo == INICIAL)
        p_ap->inicial = estado_copy(e);

    if (list_belongs(p_ap->estados, (void *) e)) {
        estadoElimina(e);
        return p_ap;
    }
    list_insertFirst(p_ap->estados, e);
    estadoElimina(e);

    return p_ap;
}

AP * APInsertaLTransicion(AP * p_ap, char * nombre_estado_i, char * nombre_estado_f) {

    int i = -1, j = -1;
    Estado *estadoi, *estadof;

    estadoi = estadoNuevo(nombre_estado_i, 0);
    estadof = estadoNuevo(nombre_estado_f, 0);

    i = list_get(p_ap->estados, estadoi);
    j = list_get(p_ap->estados, estadof);

    if (i < 0 || j < 0) return p_ap;

    relacionInserta(p_ap->lambdas, i, j);

    estadoElimina(estadoi);
    estadoElimina(estadof);

    return p_ap;
}

AP * APInsertaTransicion(AP * p_ap,
        char * nombre_simbolo_pila,
        char * nombre_estado_i,
        char * nombre_estado_f,
        char * nombre_simbolo_entrada,
        Palabra * accion) {
    int pila, estado_i, estado_f, entrada, f = 0;
    Estado *e;

    if (!nombre_simbolo_entrada) {
        nombre_simbolo_entrada = LAMBDA;
        entrada = (p_ap->fn_tansicion)->num_simbolos_entrada - 1;
    } else {
        entrada = list_get(p_ap->alfabeto, (void*) nombre_simbolo_entrada);
    }
    if (!accion) {
        f = 1;
        accion = palabraNueva();
    }

    pila = list_get(p_ap->alfabeto_pila, (void*) nombre_simbolo_pila);

    e = estadoNuevo(nombre_estado_i, 0);
    estado_i = list_get(p_ap->estados, e);
    estadoElimina(e);
    e = estadoNuevo(nombre_estado_f, 0);
    estado_f = list_get(p_ap->estados, e);
    estadoElimina(e);

    transicionAPinserta(p_ap->fn_tansicion, pila, estado_i, estado_f, entrada, accion);

    if (f) palabraElimina(accion);



    return p_ap;
}

AP * APInicializaCadena(AP *p_ap) {
    if (p_ap->palabra)
        palabraElimina(p_ap->palabra);
    p_ap->palabra = palabraNueva();
    return p_ap;
}

AP * APInsertaLetra(AP * p_ap, char * letra) {
    palabraInsertaLetra(p_ap->palabra, letra);

    return p_ap;
}

AP * APCierraLTransicion(AP * p_ap) {
    relacionCierreTransitivo(p_ap->lambdas);

    return p_ap;
}

AP * APInicializaEstado(AP * p_ap) {
    ConfiguracionAp *cap = NULL;
    Stack *pila;
    Estado* fin;
    int i, j;

    pila = stack_ini((destroy_element_function_type) destroy_p_string, copy_p_string,
            print_p_string, (cmp_element_function_type) strcmp);
    stack_push(pila, (void*) SIMBOLO_INICIO_PILA);

    cap = configuracionApNueva(p_ap->inicial, pila, p_ap->palabra);
    p_ap->q = configuracionApndInsert(p_ap->q, cap);
    configuracionApElimina(cap);
    /*Obtener el indice del estado inicial*/
    i = list_get(p_ap->estados, (void*) p_ap->inicial);

    /*transitar desde q0 con lambdas*/
    for (j = 0; j < p_ap->len_estados; j++)
        if (relacionCierreIJ(p_ap->lambdas, i, j)) {
            fin = list_get_pos(p_ap->estados, j);
            cap = configuracionApNueva(fin, pila, p_ap->palabra);
            p_ap->q = configuracionApndInsert(p_ap->q, cap);
            configuracionApElimina(cap);
        }

    stack_destroy(pila);
    return p_ap;
}

int sub_transita(AP* p_ap, int lambda, int estado_fin_pos, Estado *estado_fin,
        Palabra *cadena, char **entrada_act, Stack *pila, List *palabras, ConfiguracionApnd *q_nueva) {
    int i, j, k, l, retval = 0;
    ConfiguracionAp *destino;
    Stack *pila_nueva;
    Palabra *insert_pila, *cadena_nueva;
    char **palabra_pila;
    Estado *fin;

    for (j = list_size(palabras) - 1; j >= 0; j--) {
        /*Sacar palabra de la lista*/
        insert_pila = (Palabra *) list_extractFirst(palabras);
        /*Meter palabra en la pila*/
        palabra_pila = palabraGetPalabra(insert_pila);
        pila_nueva = stack_copy(pila);
        for (k = palabraTamano(insert_pila) - 1; k >= 0; k--) {
            stack_push(pila_nueva, palabra_pila[k]);
        }
        /*Volver a insertar la palabra en la lista para futuras transiciones*/
        list_insertLast(palabras, (void*) insert_pila);
        palabraElimina(insert_pila);
        /*Creamos una nueva configuradcion ap*/
        cadena_nueva = palabraNueva();
        for (l = lambda; l < palabraTamano(cadena); l++)
            palabraInsertaLetra(cadena_nueva, entrada_act[l]);
        if (estadoTipo(estado_fin) == FINAL && !palabraTamano(cadena_nueva))
            /*La palabra se acepta por estado final*/
            retval = 1;
        else if (!palabraTamano(cadena_nueva) && stack_isEmpty(pila_nueva) == TRUE)
            /*La palabra se acepta por vaciado de pila*/
            retval = 1;
        destino = configuracionApNueva(estado_fin, pila_nueva, cadena_nueva);
        /*Metemos la configuracion ap en la apnd*/
        configuracionApndInsert(q_nueva, destino);
        configuracionApElimina(destino);
        /*miramos las lambdas de este estado una vez actualizada la entrada y la palabra*/
        for( i = 0; i < p_ap->len_estados; i++)
            if (relacionCierreIJ(p_ap->lambdas, estado_fin_pos, i)) {
                fin = list_get_pos(p_ap->estados, i);
                destino = configuracionApNueva(fin, pila_nueva, cadena_nueva);
                configuracionApndInsert(q_nueva, destino);
                configuracionApElimina(destino);
            }
        stack_destroy(pila_nueva);
        palabraElimina(cadena_nueva);
    }
    return retval;
}

int APTransita(AP * p_ap) {
    ConfiguracionAp *cap;
    Estado *estado_ini, *estado_fin;
    Palabra *cadena;
    List *palabras;
    ConfiguracionApnd *q_nueva;
    char **entrada_act, *top;
    Stack *pila;
    int i, pila_pos, estado_ini_pos, estado_fin_pos, entrada, lambda, retval = 0;

    q_nueva = configuracionApndIni();

    do {
        cap = configuracionApndExtract(p_ap->q);
        if (!cap)
            break;

        pila = getPila(cap);
        if (stack_isEmpty(pila)) {
            configuracionApElimina(cap);
            continue;
        }
        cadena = getCadena(cap);
        estado_ini = getEstado(cap);
        top = stack_pop(pila);
        pila_pos = list_get(p_ap->alfabeto_pila, (void*) top);
        free(top);
        estado_ini_pos = list_get(p_ap->estados, (void*) estado_ini);
        entrada_act = palabraGetPalabra(cadena);
        if (!palabraTamano(cadena)) {
            /*Toda la entrada se ha procesado, no se transita desde estado*/
            entrada = -1;
        } else {
            entrada = list_get(p_ap->alfabeto, (void*) entrada_act[0]);
        }
        lambda = (p_ap->fn_tansicion)->num_simbolos_entrada - 1;

        /*Recorrer todos los estados, llamar a la funcion de transicion y ver si nos 
         movemos a ese estado*/
        for (i = 0; i < p_ap->len_estados; i++) {
            estado_fin = (Estado*) list_extractFirst(p_ap->estados);            
            list_insertLast(p_ap->estados, estado_fin);
            estado_fin_pos = i;
            /*Transiciones que consumen entrada*/
            if (entrada != -1) {
                palabras = transicionAPbusca(p_ap->fn_tansicion, pila_pos, estado_ini_pos,
                        estado_fin_pos, entrada);
                if (list_isEmpty(palabras) == FALSE) {
                    retval = sub_transita(p_ap, 1, estado_fin_pos, estado_fin, cadena,
                            entrada_act, pila, palabras, q_nueva);
                }
            }

            palabras = transicionAPbusca(p_ap->fn_tansicion, pila_pos, estado_ini_pos,
                    estado_fin_pos, lambda);
            if (list_isEmpty(palabras) == TRUE) {
                estadoElimina(estado_fin);
                continue;
            }
            retval = sub_transita(p_ap, 0, estado_fin_pos, estado_fin, cadena,
                    entrada_act, pila, palabras, q_nueva);
            estadoElimina(estado_fin);

        }
        configuracionApElimina(cap);
    } while (configuracionApndIsEmpty(p_ap->q) == FALSE);

    configuracionApndDestroy(p_ap->q);
    p_ap->q = q_nueva;


    return retval;
}

int APProcesaEntrada(FILE *fd, AP * p_ap) {
    int i = 0, aceptada = 0;

    fprintf(fd, "\n\n********************************** PROCESO DE CADENA ***************************************\n");
    fprintf(fd, "SE VA A PROCESAR LA ENTRADA:");
    palabraImprime(fd, p_ap->palabra);
    fprintf(fd, "\nA PARTIR DE ESTA CONFIGURACIÓN INICIAL:\n");
    /*APInicializaEstado(p_ap);*/
    configuracionApndPrint(fd, p_ap->q);
    do {
        fprintf(fd, "\tITERACION %d TRAS ITERAR LA CONFIGURACIÓN ES ===>\n", i);
        if (APTransita(p_ap))
            aceptada = 1;
        configuracionApndPrint(fd, p_ap->q);
        i++;
    } while (!configuracionApndIsEmpty(p_ap->q));

    if (aceptada) {
        fprintf(fd, "¡¡¡ RECONOCIDA !!!!\n");
    } else {
        fprintf(fd, "¡¡¡ RECHAZADA !!!!\n");
    }
    return aceptada;
}