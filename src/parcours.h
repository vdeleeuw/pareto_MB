#ifndef PARCOURS_H
#define PARCOURS_H

#include "struct.h"

void genVoisin(int nbVille, int a, int b, int parcours[nbVille], int res[nbVille]);
void genParcours(int nbVille, int tab[nbVille]);
sol evalParcours(int nbVille, int tab[nbVille], double matA[nbVille][nbVille], double matB[nbVille][nbVille]);
int domine(sol s1, sol s2);

#endif
