#ifndef ONLINE_H
#define ONLINE_H

#include "struct.h"

int online(int nbVille, char* ficOn, char* ficOnPar, int fic, double matA[nbVille][nbVille], double matB[nbVille][nbVille], sol parParcours[TAILLE_TAB], int parcours[nbVille]);

#endif
