#variables de compilation
CC=gcc
CFLAGS= 
LDFLAGS=-Wall -lm -g
EXEC=projet


#compilation
all: ./bin/$(EXEC)

./obj/fichier.o: ./src/fichier.c
	$(CC) -o $@ -c $< $(CFLAGS)

./obj/offline.o: ./src/offline.c
	$(CC) -o $@ -c $< $(CFLAGS)

./obj/online.o: ./src/online.c
	$(CC) -o $@ -c $< $(CFLAGS)

./obj/parcours.o: ./src/parcours.c
	$(CC) -o $@ -c $< $(CFLAGS)

./obj/main.o: ./src/main.c ./src/struct.h ./src/online.h ./src/offline.h ./src/parcours.h ./src/fichier.h
	$(CC) -o $@ -c $< $(CFLAGS)

./bin/$(EXEC): ./obj/main.o ./obj/online.o ./obj/offline.o ./obj/parcours.o ./obj/fichier.o
	$(CC) -o $@ $^ $(LDFLAGS)


#nettoyeur
clean:
	rm -rf ./obj/*

mrproper: clean
	rm -rf ./bin/*
	rm -rf ./result/*

#help
help:	
	@echo - TP optimisation combinatoire DE LEEUW Valérian -
	@echo 
	@echo Commandes utiles :
	@echo make : Compile le programme $(EXEC) dans le dossier \"bin\".
	@echo
	@echo Commandes de nettoyage : 
	@echo make clean : Supprime les fichiers objets.
	@echo make mrproper : Execute \"clean\", supprime l\'éxecutable et tout les fichiers résultats.
	@echo


