#ifndef STRUCT_H
#define STRUCT_H

#define TAILLE_TAB_FICHIER 201 	//taille max des fichiers de tests disponibles + 1
#define TAILLE_TAB 1000		//taille pour les tableaux avec les solutions de pareto  
#define NB_POINT_PLS 200	//nombre de points pour l'approximation PLS
#define TAILLE_MAX 50		//taille pour les chaines de caractere
#define NB_SOL 500		//nombre d'essais ! ca ne changera pas les noms des fichiers ! 

/* structs */
struct s_ville{
	int num;
	int x;
	int y;
};typedef struct s_ville ville;

struct s_sol{
	int parcours[TAILLE_TAB_FICHIER];
	double coutA;
	double coutB;
};typedef struct s_sol sol;

#endif
