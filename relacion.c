#include "relacion.h"

struct _Relacion {
    char *nombre;
    int num_elementos;
    int **origen;
    int **pow;
    int **cierre;
};

Relacion * relacionNueva(char * nombre, int num_elementos) {
    Relacion *r = NULL;
    int i = 0;

    r = (Relacion*) malloc(sizeof (Relacion));

    r->nombre = nombre;
    r->num_elementos = num_elementos;

    /*init elem*/
    r->origen = (int**) malloc(num_elementos * sizeof (int*));
    for (i = 0; i < num_elementos; i++)
        r->origen[i] = (int*) calloc(num_elementos, sizeof (int));

    /*init cierre*/
    r->cierre = (int**) malloc(num_elementos * sizeof (int*));
    for (i = 0; i < num_elementos; i++)
        r->cierre[i] = (int*) calloc(num_elementos, sizeof (int));

    /*initi potencia*/
    r->pow = (int**) malloc(num_elementos * sizeof (int*));
    for (i = 0; i < num_elementos; i++)
        r->pow[i] = (int*) calloc(num_elementos, sizeof (int));

    return r;


}

void relacionImprime(FILE * fd, Relacion * p_r) {
    int i, j;

    if (!fd || !p_r) return;

    fprintf(fd, "%s={\n\t", p_r->nombre);

    for (i = 0; i < p_r->num_elementos; i++)
        fprintf(fd, "\t[%d]", i);
    fprintf(fd, "\nCIERRE\n");

    for (i = 0; i < p_r->num_elementos; i++) {
        fprintf(fd, "\t[%d]", i);
        for (j = 0; j < p_r->num_elementos; j++)
            fprintf(fd, "/t%d", p_r->cierre[i][j]);
        fprintf(fd, "\n");
    }

    fprintf(fd, "\nRELACION INICIAL i\n");
    for (i = 0; i < p_r->num_elementos; i++) {
        fprintf(fd, "\t[%d]", i);
        for (j = 0; j < p_r->num_elementos; j++)
            fprintf(fd, "/t%d", p_r->origen[i][j]);
        fprintf(fd, "\n");
    }
    fprintf(fd, "}\n");
}

void relacionElimina(Relacion * p_r) {

    int i = 0;

    if (!p_r) return;

    for (i = p_r->num_elementos; i > 0; i--) {
        free(p_r->origen[i]);
        free(p_r->cierre[i]);
    }

    free(p_r->origen);
    free(p_r->cierre);

    if (p_r->nombre)
        free(p_r->nombre);

}

Relacion * relacionCopia(Relacion * p_r1) {
    Relacion *p_r = NULL;
    int i, j;

    if (!p_r1) return NULL;

    p_r = relacionNueva(p_r->nombre, p_r->num_elementos);

    if (!p_r) return NULL;

    for (i = 0; i < p_r->num_elementos; i++)
        for (j = 0; j < p_r->num_elementos; j++) {
            p_r->origen[i][j] = p_r1->origen[i][j];
            p_r->cierre[i][j] = p_r1->cierre[i][j];
        }

    return p_r;
}

Relacion * relacionInserta(Relacion * p_r, int i, int j) {
    p_r->origen[i][j] = 1;
    p_r->cierre[i][j] = 1;
    p_r->pow[i][j] = 1;
    return p_r;
}

int relacionTamano(Relacion * p_r) {
    if (!p_r) return -1;
    return p_r->num_elementos;
}

Relacion * relacionCierreTransitivo(Relacion * p_r) {
    int i, j, k, f;

    for (i = 0; i < p_r->num_elementos; i++)
        for (j = 0; j < p_r->num_elementos; j++)
            for (k = i; k < j; k++)
                if (p_r->pow[i][k] == p_r->origen[k][j] && p_r->origen[k][j] == 1) {
                    p_r->cierre[i][j] = 1;
                    p_r->pow[i][j] = 1;
                    f = 1;
                }
    /*faltaria comprobar el flag-> cuando es 0 paramos el bucle*/
    return p_r;
}

/*
Modifica la relación para conservar el ella su cierre transitivo. Devuelve la relación como retorno.
 */
int relacionIJ(Relacion * p_r, int i, int j) {
    if (!p_r) return -1;

    return p_r->origen[i][j];
}

int relacionCierreIJ(Relacion * p_r, int i, int j) {
    /*indices positivos, principio RTFM*/
    return p_r->cierre[i][j];
}
