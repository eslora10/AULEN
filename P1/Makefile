################################################################################################
# Makefile based on
# 	http://arantxa.ii.uam.es/~mcorella/teaching/mtp20506/Makefile
#	and
# 	https://stackoverflow.com/questions/1484817/how-do-i-make-a-simple-makefile-for-gcc-on-linux
# Author: Borja Gil Perez, borja.gil@uam.es
################################################################################################
LIBS = -lm -pthread
CC = gcc
CFLAGS = -g -Wall -ansi -pedantic
OBJ=relacion.o ap.o estado.o palabra.o configuracion_ap.o stack.o configuracion_apnd.o list.o dynamic_node.o
EJ= AP_enunciado AP_lambda AP_estrella

# $ make
# $ make all
all: AP_enunciado AP_lambda AP_estrella
########################################################################
# P1
#########################################################################
stack.o: stack.c stack.h basic_types.h
	$(CC) $(CFLAGS) -c $< -o $@
estado.o: estado.c estado.h
	$(CC) $(CFLAGS) -c $< -o $@
palabra.o: palabra.c palabra.h
	$(CC) $(CFLAGS) -c $< -o $@
configuracion_ap.o: configuracion_ap.c configuracion_ap.h estado.h stack.h palabra.h
	$(CC) $(CFLAGS) -c $< -o $@
dynamic_node.o: dynamic_node.c dynamic_node.h
	$(CC) $(CFLAGS) -c $< -o $@
list.o: list.c list.h dynamic_node.h
	$(CC) $(CFLAGS) -c $< -o $@
configuracion_apnd.o: configuracion_apnd.c configuracion_ap.h list.h
	$(CC) $(CFLAGS) -c $< -o $@
relacion.o: relacion.c relacion.h
	$(CC) $(CFLAGS) -c $< -o $@
ap.o: ap.c ap.h
	$(CC) $(CFLAGS) -c $< -o $@
pr_enunciado.o: pr_enunciado.c ap.h palabra.h
	$(CC) $(CFLAGS) -c $< -o $@
pr_enunciado_lambda.o: pr_enunciado_lambda.c ap.h palabra.h
	$(CC) $(CFLAGS) -c $< -o $@
pr_enunciado_lambda_0_estrella.o: pr_enunciado_lambda_0_estrella.c ap.h palabra.h
	$(CC) $(CFLAGS) -c $< -o $@
# $ make p1s3
AP_enunciado: pr_enunciado.o $(OBJ)
	$(CC) $^ -Wall $(LIBS) -o $@
AP_lambda: pr_enunciado_lambda.o $(OBJ)
	$(CC) $^ -Wall $(LIBS) -o $@
AP_estrella: pr_enunciado_lambda_0_estrella.o $(OBJ)
	$(CC) $^ -Wall $(LIBS) -o $@


########################################################################
# Information and Clean
########################################################################
# $ make info
info:
	@echo
	@echo "<Asignatura>, <Grado>"
	@echo "<Codigo de la entrega>"
	@echo
	@echo "Autores:"
	@echo "	<Autor, Correo electronico>"
	@echo "	<Autor, Correo electronico>"
	@echo
	@echo "Ejecutables:"
	@echo "	all"
	@echo "		p1"
	@echo "			$(P1)"
	@echo "		p2"
	@echo "			$(P2)"
	@echo
# $ make clean
clean:
	@echo "Borrando objetos, ejecutables, etc."
	@rm -fr Doxyfile latex html
	@rm -f *~ *.o core $(EJ)

########################################################################
# Using utilities
########################################################################
# $ make astyle-c
astyle-c:
	@echo "Applying Artistic Style to C programming files."
	@astyle *.h *.c
# $ make doxygen
doxygen:
	@rm -fr Doxyfile latex html
	@doxygen -g
	@doxygen Doxyfile
########################################################################
# Installation
########################################################################
# $ make dev-essential
dev-essential:
	@echo "Installing essential developer tools."
	sudo apt-get install astyle build-essential geany nemiver nmon terminator valgrind
	sudo apt-get install doxygen graphviz
# $ make lubuntu1404-custom
lubuntu1404-custom:
	@echo "Customizing Lubuntu 14.04"
	sudo apt-get purge abiword gnumeric
	sudo add-apt-repository ppa:indicator-brightness/ppa
	sudo add-apt-repository ppa:webupd8team/java
	sudo apt-get update
	sudo apt-get install language-selector-gnome libreoffice libreoffice-l10n-es lubuntu-restricted-extras thunderbird thunderbird-locale-es-es vlc
	sudo apt-get install indicator-brightness
	sudo apt-get install oracle-java8-installer && sudo apt-get install oracle-java8-set-default
	sudo apt-get autoremove && sudo apt-get autoclean
