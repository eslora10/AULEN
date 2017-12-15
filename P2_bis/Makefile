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

# $ make
# $ make all
all: p2
# $ make p1

########################################################################
# P2
########################################################################
afnd.o: afnd.c afnd.h
	$(CC) $(CFLAGS) -c $< -o $@
transforma.o: transforma.c afnd.h transforma.h
	$(CC) $(CFLAGS) -c $< -o $@
main.o: main.c afnd.h transforma.h
p2: main.o transforma.o afnd.o
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
	@rm -f *~ *.o core p2
	
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
