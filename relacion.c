#include "relacion.h"

struct _Relacion {
    char *nombre;
    int num_elementos;
    int **origen;
    int **cierre;
};

Relacion * relacionNueva(char * nombre, int num_elementos);

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

void relacionElimina(Relacion * p_r);

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

Relacion * relacionInserta(Relacion * p_r, int i, int j);

int relacionTamano(Relacion * p_r) {
    if (!p_r) return -1;
    return p_r->num_elementos;
}


Relacion * relacionCierreTransitivo(Relacion * p_r);

int relacionIJ(Relacion * p_r, int i, int j) {
    if (!p_r) return -1;

    return p_r->origen[i][j];
}

int relacionCierreIJ(Relacion * p_r, int i, int j);


