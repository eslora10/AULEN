#include "AP.h"
#define SIMBOLO_INICIO_PILA 'Z'

struct _AP {
    char *nombre;
    List *alfabeto; /*Set*/
    int len_alfabeto;
    List *estados; /*Set*/
    int len_estados;
    List *fn_transicion; /*Vamos a tratarlo como una lista de transiciones
                          * siendo transicion un TAD nuevo*/
    Relacion *lambdas;
    Palabra *palabra;
    ConfiguracionApnd *q;
};

/*funciones de transicion*/
struct _transicionAP {
    List* ****acciones;
    int num_simbolos_pila;
    int num_estados;
    int num_simbolos_entrada;
};

TransicionAP transicionAPNueva(char * nombre, int num_simbolos_pila,
        int num_estados, int num_simbolos_entrada) {
    TransicionAP *t;
    int pila, estado_ini, estado_fin, entrada;

    if (!nombre) return NULL;

    t = (TransicionAP *) malloc(sizeof (TransicionAp));
    if (!t) return NULL;

    t->num_simbolos_pila = num_simbolos_pila;
    t->num_estados = num_estados;
    t->num_simbolos_entrada = num_simbolos_entrada;

    t->acciones = (List* ****) malloc(num_simbolos_pila * sizeof (List ****));
    for (pila = 0; pila < num_simbolos_pila; pila++) {
        t->acciones[pila] = (List ****) malloc(num_estados * sizeof (List***));
        for (estado_ini = 0; estado < num_estados; estados++) {
            t->acciones[pila][estado_ini] = (List ***) malloc(num_simbolos_entrada * sizeof (List**));
            for (estado_fin = 0; estado < num_estados; estados++) {
                t->acciones[pila][estado_ini][estado_fin] = (List **) malloc(num_simbolos_entrada * sizeof (List*));
                for (entrada = 0; estada < num_simbolos_entrada; entrada++)
                    t->acciones[pila][estado_ini][estado_fin][entrada] =
                        list_ini(destroy_element_function_type)palabraElimina,
                        (copy_element_function_type) palabraCopia,
                        (print_element_function_type) palabraImprime,
                        (cmp_element_function_type) palabraCompara
                        );
            }
        }
    }
    return t;
}

void *transicionAPNueva(TransicionAP *t) {
    int pila, estado_ini, estado_fin, entrada;
    if (!t) return;

    for (pila = 0; pila < t->num_simbolos_pila; pila++) {
        for (estado_ini = 0; estado < num_estados; estados++) {
            for (estado_fin = 0; estado < num_estados; estados++) {
                for (entrada = 0; estada < num_simbolos_entrada; entrada++)
                    list_destroy(t->acciones[pila][estado_ini][estado_fin][entrada]);
                free(t->acciones[pila][estado_ini][estado_fin]);
            }
            free(t->acciones[pila][estado_ini]);
        }
        free(t->acciones[pila])
    }
    free(t->acciones);
    free(t);
    return t;
}

TransicionAP *transicionAPinserta(TransicionAP *t, int pila, int estado_ini,
        int estado_fin, int entrada, Palabra* palabra) {
    if (!t || !palabra) return NULL;
    if (pila >= t->num_simbolos_pila || estado_ini >= t->num_estados ||
            estado_fin >= t->num_estados || entrada >= t->num_simbolos_entrada)
        return NULL;
    list_t->acciones[pila][estado_ini][estado_fin][palabra] = palabra;
    
    return t;

}

/*fin funciones transicion*/
AP * APNuevo(char * nombre,
        int num_estados,
        int num_simbolos_entrada,
        int num_simbolos_pila);

void APElimina(AP * p_ap);

void APImprime(FILE * fd, AP * p_ap);

AP * APInsertaSimboloAlfabetoEntrada(AP * p_ap, char * simbolo);

AP * APInsertaSimboloAlfabetoPila(AP * p_ap, char * simbolo);

AP * APInsertaEstado(AP * p_ap, char * nombre, int tipo);

AP * APInsertaLTransicion(AP * p_ap,
        char * nombre_estado_i,
        char * nombre_estado_f);

AP * APInsertaTransicion(AP * p_ap,
        char * nombre_simbolo_pila,
        char * nombre_estado_i,
        char * nombre_estado_f,
        char * nombre_simbolo_entrada,
        Palabra * accion);

AP * APInsertaLetra(AP * p_ap, char * letra);

AP * APCierraLTransicion(AP * p_ap);

AP * APInicializaEstado(AP * p_ap);

int APTransita(AP * p_ap);

int APProcesaEntrada(FILE *fd, AP * p_ap);
t->acciones[pila][estado] = (List ***) malloc(num_simbolos_entrada * sizeof (List**));
for (entrada = 0; estada < num_simbolos_entrada; entrada++)
    t -
}


}


}

/*fin funciones transicion*/
AP * APNuevo(char * nombre,
        int num_estados,
        int num_simbolos_entrada,
        int num_simbolos_pila);

void APElimina(AP * p_ap);

void APImprime(FILE * fd, AP* p_ap);

AP * APInsertaSimboloAlfabetoEntrada(AP * p_ap, char * simbolo);

AP * APInsertaSimboloAlfabetoPila(AP * p_ap, char * simbolo);

AP * APInsertaEstado(AP * p_ap, char * nombre, int tipo);

AP * APInsertaLTransicion(AP * p_ap,
        char * nombre_estado_i,
        char * nombre_estado_f);

AP * APInsertaTransicion(AP * p_ap,
        char * nombre_simbolo_pila,
        char * nombre_estado_i,
        char * nombre_estado_f,
        char * nombre_simbolo_entrada,
        Palabra * accion);

AP * APInsertaLetra(AP * p_ap, char * letra);

AP * APCierraLTransicion(AP * p_ap);

AP * APInicializaEstado(AP * p_ap);

int APTransita(AP * p_ap);

int APProcesaEntrada(FILE *fd, AP * p_ap);
t->acciones[pila][estado] = (List ***) malloc(num_simbolos_entrada * sizeof (List**));
for (entrada = 0; estada < num_simbolos_entrada; entrada++)
    t -
}


}


}

/*fin funciones transicion*/
AP * APNuevo(char * nombre,
        int num_estados,
        int num_simbolos_entrada,
        int num_simbolos_pila);

void APElimina(AP * p_ap);

void APImprime(FILE * fd, AP* p_ap);

AP * APInsertaSimboloAlfabetoEntrada(AP * p_ap, char * simbolo);

AP * APInsertaSimboloAlfabetoPila(AP * p_ap, char * simbolo);

AP * APInsertaEstado(AP * p_ap, char * nombre, int tipo);

AP * APInsertaLTransicion(AP * p_ap,
        char * nombre_estado_i,
        char * nombre_estado_f);

AP * APInsertaTransicion(AP * p_ap,
        char * nombre_simbolo_pila,
        char * nombre_estado_i,
        char * nombre_estado_f,
        char * nombre_simbolo_entrada,
        Palabra * accion);

AP * APInsertaLetra(AP * p_ap, char * letra);

AP * APCierraLTransicion(AP * p_ap);

AP * APInicializaEstado(AP * p_ap);

int APTransita(AP * p_ap);

int APProcesaEntrada(FILE *fd, AP * p_ap);
t->acciones[pila][estado] = (List ***) malloc(num_simbolos_entrada * sizeof (List**));
for (entrada = 0; estada < num_simbolos_entrada; entrada++)
    t -
}


}


}

/*fin funciones transicion*/
AP * APNuevo(char * nombre,
        int num_estados,
        int num_simbolos_entrada,
        int num_simbolos_pila);

void APElimina(AP * p_ap);

void APImprime(FILE * fd, AP* p_ap);

AP * APInsertaSimboloAlfabetoEntrada(AP * p_ap, char * simbolo);

AP * APInsertaSimboloAlfabetoPila(AP * p_ap, char * simbolo);

AP * APInsertaEstado(AP * p_ap, char * nombre, int tipo);

AP * APInsertaLTransicion(AP * p_ap,
        char * nombre_estado_i,
        char * nombre_estado_f);

AP * APInsertaTransicion(AP * p_ap,
        char * nombre_simbolo_pila,
        char * nombre_estado_i,
        char * nombre_estado_f,
        char * nombre_simbolo_entrada,
        Palabra * accion);

AP * APInsertaLetra(AP * p_ap, char * letra);

AP * APCierraLTransicion(AP * p_ap);

AP * APInicializaEstado(AP * p_ap);

int APTransita(AP * p_ap);

int APProcesaEntrada(FILE *fd, AP * p_ap);
t->acciones[pila][estado] = (List ***) malloc(num_simbolos_entrada * sizeof (List**));
for (entrada = 0; estada < num_simbolos_entrada; entrada++)
    t -
}


}


}

/*fin funciones transicion*/
AP * APNuevo(char * nombre,
        int num_estados,
        int num_simbolos_entrada,
        int num_simbolos_pila);

void APElimina(AP * p_ap);

void APImprime(FILE * fd, AP* p_ap);

AP * APInsertaSimboloAlfabetoEntrada(AP * p_ap, char * simbolo);

AP * APInsertaSimboloAlfabetoPila(AP * p_ap, char * simbolo);

AP * APInsertaEstado(AP * p_ap, char * nombre, int tipo);

AP * APInsertaLTransicion(AP * p_ap,
        char * nombre_estado_i,
        char * nombre_estado_f);

AP * APInsertaTransicion(AP * p_ap,
        char * nombre_simbolo_pila,
        char * nombre_estado_i,
        char * nombre_estado_f,
        char * nombre_simbolo_entrada,
        Palabra * accion);

AP * APInsertaLetra(AP * p_ap, char * letra);

AP * APCierraLTransicion(AP * p_ap);

AP * APInicializaEstado(AP * p_ap);

int APTransita(AP * p_ap);

int APProcesaEntrada(FILE *fd, AP * p_ap);
t->acciones[pila][estado] = (List ***) malloc(num_simbolos_entrada * sizeof (List**));
for (entrada = 0; estada < num_simbolos_entrada; entrada++)
    t -
}


}


}

/*fin funciones transicion*/
AP * APNuevo(char * nombre,
        int num_estados,
        int num_simbolos_entrada,
        int num_simbolos_pila);

void APElimina(AP * p_ap);

void APImprime(FILE * fd, AP* p_ap);

AP * APInsertaSimboloAlfabetoEntrada(AP * p_ap, char * simbolo);

AP * APInsertaSimboloAlfabetoPila(AP * p_ap, char * simbolo);

AP * APInsertaEstado(AP * p_ap, char * nombre, int tipo);

AP * APInsertaLTransicion(AP * p_ap,
        char * nombre_estado_i,
        char * nombre_estado_f);

AP * APInsertaTransicion(AP * p_ap,
        char * nombre_simbolo_pila,
        char * nombre_estado_i,
        char * nombre_estado_f,
        char * nombre_simbolo_entrada,
        Palabra * accion);

AP * APInsertaLetra(AP * p_ap, char * letra);

AP * APCierraLTransicion(AP * p_ap);

AP * APInicializaEstado(AP * p_ap);

int APTransita(AP * p_ap);

int APProcesaEntrada(FILE *fd, AP * p_ap);
t->acciones[pila][estado] = (List ***) malloc(num_simbolos_entrada * sizeof (List**));
for (entrada = 0; estada < num_simbolos_entrada; entrada++)
    t -
}


}


}

/*fin funciones transicion*/
AP * APNuevo(char * nombre,
        int num_estados,
        int num_simbolos_entrada,
        int num_simbolos_pila);

void APElimina(AP * p_ap);

void APImprime(FILE * fd, AP* p_ap);

AP * APInsertaSimboloAlfabetoEntrada(AP * p_ap, char * simbolo);

AP * APInsertaSimboloAlfabetoPila(AP * p_ap, char * simbolo);

AP * APInsertaEstado(AP * p_ap, char * nombre, int tipo);

AP * APInsertaLTransicion(AP * p_ap,
        char * nombre_estado_i,
        char * nombre_estado_f);

AP * APInsertaTransicion(AP * p_ap,
        char * nombre_simbolo_pila,
        char * nombre_estado_i,
        char * nombre_estado_f,
        char * nombre_simbolo_entrada,
        Palabra * accion);

AP * APInsertaLetra(AP * p_ap, char * letra);

AP * APCierraLTransicion(AP * p_ap);

AP * APInicializaEstado(AP * p_ap);

int APTransita(AP * p_ap);

int APProcesaEntrada(FILE *fd, AP * p_ap);
t->acciones[pila][estado] = (List ***) malloc(num_simbolos_entrada * sizeof (List**));
for (entrada = 0; estada < num_simbolos_entrada; entrada++)
    t -
}


}


}

/*fin funciones transicion*/
AP * APNuevo(char * nombre,
        int num_estados,
        int num_simbolos_entrada,
        int num_simbolos_pila);

void APElimina(AP * p_ap);

void APImprime(FILE * fd, AP* p_ap);

AP * APInsertaSimboloAlfabetoEntrada(AP * p_ap, char * simbolo);

AP * APInsertaSimboloAlfabetoPila(AP * p_ap, char * simbolo);

AP * APInsertaEstado(AP * p_ap, char * nombre, int tipo);

AP * APInsertaLTransicion(AP * p_ap,
        char * nombre_estado_i,
        char * nombre_estado_f);

AP * APInsertaTransicion(AP * p_ap,
        char * nombre_simbolo_pila,
        char * nombre_estado_i,
        char * nombre_estado_f,
        char * nombre_simbolo_entrada,
        Palabra * accion);

AP * APInsertaLetra(AP * p_ap, char * letra);

AP * APCierraLTransicion(AP * p_ap);

AP * APInicializaEstado(AP * p_ap);

int APTransita(AP * p_ap);

int APProcesaEntrada(FILE *fd, AP * p_ap);
