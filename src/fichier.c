#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "fichier.h"

//retourne le nombre de ville via lecture fichier
int getTailleGraphe(char* nomFicEntree){
	FILE* ficEntree = fopen(nomFicEntree, "r"); 
	if(ficEntree == NULL){
		printf("Echec lors de l'ouverture du fichier (%s).\n", nomFicEntree);
		exit(EXIT_FAILURE);
	}else{
		int i, res = 0;
		char mot[TAILLE_MAX] = "";
		char ligne[TAILLE_MAX] = "";
		for(i=0; i<4; ++i)
			fgets(ligne, TAILLE_MAX, ficEntree);
		fscanf(ficEntree,"%s %d",mot, &res);
		fclose(ficEntree);
		return res;
	}
	return 0;
};

//initialise le tableau de ville
void initTabVille(char* nomFicEntree, int nbVille, ville tab[nbVille]){
	FILE* ficEntree = fopen(nomFicEntree, "r"); 
	if(ficEntree == NULL){
		printf("Echec lors de l'ouverture du fichier (%s).\n", nomFicEntree);
		exit(EXIT_FAILURE);
	}else{
		ville tmp;
		char ligne[TAILLE_MAX] = "";
		int i;
		for(i=0; i<6; ++i)
			fgets(ligne, TAILLE_MAX, ficEntree);
		for(i=0; i<nbVille; ++i){
			fgets(ligne, TAILLE_MAX, ficEntree);
			fscanf(ficEntree, "%d %d %d", &tmp.num, &tmp.x, &tmp.y);
			tab[tmp.num] = tmp;
		}
		fclose(ficEntree);
	}
};

//rempli la matrice de distance de ville a ville avec le tableau de ville
void calcDist(int nbVille, ville tab[nbVille], double mat[nbVille][nbVille]){
	int i,j;	
	for(i=1; i<nbVille; ++i){
		for(j=1; j<nbVille; ++j){
			int xCarre = (tab[i].x-tab[j].x) * (tab[i].x-tab[j].x);
			int yCarre = (tab[i].y-tab[j].y) * (tab[i].y-tab[j].y);
			mat[i][j]=sqrt(xCarre + yCarre); 
		}
	}
};
