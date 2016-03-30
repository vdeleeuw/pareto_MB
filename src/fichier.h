#ifndef FICHIER_H
#define FICHIER_H

#include "struct.h"

int getTailleGraphe(char* nomFicEntree);
void initTabVille(char* nomFicEntree, int nbVille, ville tab[nbVille]);
void calcDist(int nbVille, ville tab[nbVille], double mat[nbVille][nbVille]);

#endif
