#include "relacion.h"

int main(int argc, char ** argv) {
    Relacion *r1, *r2, *r3, *r4;

    printf("EJEMPLO 1\n");

    r1 = relacionNueva("ejemplo1", 3);
    relacionImprime(stdout, r1);

    relacionCierreTransitivo(r1);
    relacionImprime(stdout, r1);

    printf("EJEMPLO 2\n");

    r2 = relacionNueva("ejemplo2", 4);

    relacionInserta(r2, 1, 3);
    relacionInserta(r2, 2, 2);
    relacionInserta(r2, 2, 3);
    relacionInserta(r2, 3, 2);

    relacionImprime(stdout, r2);

    relacionCierreTransitivo(r2);
    relacionImprime(stdout, r2);
    
    printf("EJEMPLO 3\n");

    r3 = relacionNueva("ejemplo3", 6);

    relacionInserta(r3, 0, 1);
    relacionInserta(r3, 3, 5);
    
    relacionImprime(stdout, r3);

    relacionCierreTransitivo(r3);
    relacionImprime(stdout, r3);
    
    printf("EJEMPLO 4\n");

    r4 = relacionNueva("ejemplo4", 7);

    relacionInserta(r4, 0, 1);
    relacionInserta(r4, 0, 3);
    relacionInserta(r4, 1, 2);
    relacionInserta(r4, 2, 5);
    relacionInserta(r4, 4, 6);
    
    relacionImprime(stdout, r4);

    relacionCierreTransitivo(r4);
    relacionImprime(stdout, r4);

    relacionElimina(r1);
    relacionElimina(r2);
    relacionElimina(r3);
    relacionElimina(r4);
    
    r1 = relacionNueva("grafo1",8);


	relacionInserta(r1,0,1);
	relacionInserta(r1,0,2);
	relacionInserta(r1,1,4);
	relacionInserta(r1,2,3);
	relacionInserta(r1,3,0);
	relacionInserta(r1,4,6);
	relacionInserta(r1,5,4);
	relacionInserta(r1,5,7);
	relacionInserta(r1,6,5);

	fprintf(stdout,"R1\n");
	relacionImprime(stdout,r1);

	r2 = relacionCopia(r1);

	fprintf(stdout,"R2 = copia(R1)\n");
	fprintf(stdout,"R2\n");
	relacionImprime(stdout,r2);

	fprintf(stdout,"R1*\n");
	relacionCierreTransitivo(r1);

	relacionImprime(stdout,r1);

	

	relacionElimina(r1);
	relacionElimina(r2);

       return 0;
}
