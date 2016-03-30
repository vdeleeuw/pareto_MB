#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "struct.h"
#include "fichier.h"
#include "parcours.h"
#include "online.h"
#include "offline.h"

/* fonctions */

/*
Algo PLS
continu <- vrai
init(A); //ensemble sol non dominé (random?)
tant que continu faire
	choisir x appartenant a A
	choisir x' appartenant a N(x) //genere un voisin de x
	on rajoute x' a A
	filtre A (online)
	si toute solution est marqué
		alors continue <- faux
fin tant que
retourner A
*/
void paretoLocalSearch(int nbVille, char* ficPls, double matA[nbVille][nbVille], double matB[nbVille][nbVille], sol parParcours[TAILLE_TAB]){
	//variables	
	int i,j,k,mod=0;
	int voisin[nbVille];
	//algo
	printf("Ecriture du fichier %s...\n",ficPls);
	for(i=0;i<TAILLE_TAB;i++){
		if(i==NB_POINT_PLS)
			break;
		if(parParcours[i].coutA != -1 && parParcours[i].coutB != -1){
			//test de tout les voisins
			for(j=1;j<nbVille;j++)
				for(k=j;k<nbVille;k++){
						//si le voisin a modifié parParcours
						genVoisin(nbVille,j,k,parParcours[i].parcours,voisin);
						if(online(nbVille, NULL, NULL, 0, matA, matB, parParcours, voisin) == 1)
							mod=1;
					}
			//alors on recommence
			if(mod == 1){
				i=0;
				mod = 0;
			}
		}
	}
	//affichage des points dans un fichier
	FILE* ficSortiePls = fopen(ficPls,"w"); 
	if(ficSortiePls == NULL){
		printf("Erreur lors de l'écriture des fichiers !\n");
		exit(EXIT_FAILURE);
	}else{
		fprintf(ficSortiePls,"#--------------------------------------------------------------# \n");
		fprintf(ficSortiePls,"# Le fichier se présente ainsi : \n");
		fprintf(ficSortiePls,"# Parcours : \n");
		fprintf(ficSortiePls,"# Detail du parcours \n");
		fprintf(ficSortiePls,"# CoutDuParcoursPourLe1erFichier CoutDuParcoursPourLe2emeFichier \n");
		fprintf(ficSortiePls,"#--------------------------------------------------------------# \n\n");
		int i,j;
		for(i=0;i<TAILLE_TAB;++i)
			if(parParcours[i].coutA != -1 && parParcours[i].coutB != -1){
				fprintf(ficSortiePls,"# Parcours : \n# ");
				for(j=1;j<nbVille;++j)
					fprintf(ficSortiePls,"%d ",parParcours[i].parcours[j]);
				fprintf(ficSortiePls,"\n%f %f\n\n",parParcours[i].coutA, parParcours[i].coutB);	
			}
		fclose(ficSortiePls);
	}
};

/* programme principal */
int main(int argc, char* argv[]){
	//messages
	printf("----------------------------------------\n");
	printf("--- PROJET DE LEEUW VALERIAN M1 INFO ---\n");
	printf("-- Matière : Optimisation Combinatoire -\n");
	printf("----- Enseignant : BASSEUR MATHIEU -----\n");
	printf("----------------------------------------\n\n");
	if(argc != 3){
		printf("Nombre d'arguments invalide, il faut deux fichiers !\n");
		exit(EXIT_FAILURE);
	}else{
		if(getTailleGraphe(argv[1]) != getTailleGraphe(argv[2])){
			printf("Tailles incompatibles !");
		}else{
			printf("Lecture des fichiers et initialisation des données...\n");
			//init des donnees
			srand(19931610);		 			//random
			int nbVille=getTailleGraphe(argv[1])+1; 		// on ignore la case 0, car les villes commencent a 1
			ville tabVilleA[nbVille], tabVilleB[nbVille];
			initTabVille(argv[1], nbVille, tabVilleA);
			initTabVille(argv[2], nbVille, tabVilleB);
			double matDistVilleA[nbVille][nbVille], matDistVilleB[nbVille][nbVille];
			calcDist(nbVille, tabVilleA, matDistVilleA);
			calcDist(nbVille, tabVilleB, matDistVilleB);
			
			//nom du fichier de sortie offline parcours
			char nomOff[TAILLE_MAX] = "./result/offline500_";
			strcat(nomOff, strstr(argv[1],"kro"));
			nomOff[strlen(nomOff)-4]='\0';
			strcat(nomOff, strstr(argv[2], "kro"));			
			nomOff[strlen(nomOff)-4]='\0';
			char nomOffTxt[TAILLE_MAX];			//data
			char nomOffJpg[TAILLE_MAX];			//jpg
			strcpy(nomOffTxt, nomOff); strcat(nomOffTxt, ".txt");
			strcpy(nomOffJpg, nomOff); strcat(nomOffJpg, ".jpg");

			//nom du fichier de sortie offline pareto
			char nomOffPar[TAILLE_MAX]="./result/offlinePareto500_";
			strcat(nomOffPar, strstr(argv[1],"kro"));
			nomOffPar[strlen(nomOffPar)-4]='\0';
			strcat(nomOffPar, strstr(argv[2], "kro"));			
			nomOffPar[strlen(nomOffPar)-4]='\0';
			char nomOffParTxt[TAILLE_MAX];			//data
			char nomOffParJpg[TAILLE_MAX];			//jpg
			strcpy(nomOffParTxt, nomOffPar); strcat(nomOffParTxt, ".txt");
			strcpy(nomOffParJpg, nomOffPar); strcat(nomOffParJpg, ".jpg");

			//nom du fichier de sortie online parcours
			char nomOn[TAILLE_MAX] = "./result/online500_";
			strcat(nomOn, strstr(argv[1],"kro"));
			nomOn[strlen(nomOn)-4]='\0';
			strcat(nomOn, strstr(argv[2], "kro"));			
			nomOn[strlen(nomOn)-4]='\0';
			char nomOnTxt[TAILLE_MAX];			//data
			char nomOnJpg[TAILLE_MAX];			//jpg
			strcpy(nomOnTxt, nomOn); strcat(nomOnTxt, ".txt");
			strcpy(nomOnJpg, nomOn); strcat(nomOnJpg, ".jpg");

			//nom du fichier de sortie online pareto
			char nomOnPar[TAILLE_MAX]="./result/onlinePareto500_";
			strcat(nomOnPar, strstr(argv[1],"kro"));
			nomOnPar[strlen(nomOnPar)-4]='\0';
			strcat(nomOnPar, strstr(argv[2], "kro"));			
			nomOnPar[strlen(nomOnPar)-4]='\0';
			char nomOnParTxt[TAILLE_MAX];			//data
			char nomOnParJpg[TAILLE_MAX];			//jpg
			strcpy(nomOnParTxt, nomOnPar); strcat(nomOnParTxt, ".txt");
			strcpy(nomOnParJpg, nomOnPar); strcat(nomOnParJpg, ".jpg");

			//nom du fichier de sortie pls pareto
			char nomPls[TAILLE_MAX]="./result/plsPareto_";
			strcat(nomPls, strstr(argv[1],"kro"));
			nomPls[strlen(nomPls)-4]='\0';
			strcat(nomPls, strstr(argv[2], "kro"));			
			nomPls[strlen(nomPls)-4]='\0';
			char nomPlsTxt[TAILLE_MAX];			//data
			char nomPlsJpg[TAILLE_MAX];			//jpg
			strcpy(nomPlsTxt, nomPls); strcat(nomPlsTxt, ".txt");
			strcpy(nomPlsJpg, nomPls); strcat(nomPlsJpg, ".jpg");
		
			//effacage des anciens fichiers pour ce jeu de test
			printf("Suppression des anciens fichiers...\n\n");
			remove(nomOnTxt);	remove(nomOffTxt);	
			remove(nomOnParTxt);	remove(nomOffParTxt);
			remove(nomPlsTxt);	remove(nomPlsJpg);
			remove(nomOnJpg);	remove(nomOffJpg);
			remove(nomOnParJpg);	remove(nomOffParJpg);
			
	
			//resolution offline
			offline(nbVille, nomOffTxt, nomOffParTxt, matDistVilleA, matDistVilleB);			

			//resolution online
			int i;
			//initialisation
			int parcours[nbVille];
			sol parParcoursOn[TAILLE_TAB];
			for(i=0;i<TAILLE_TAB;i++){
				parParcoursOn[i].coutA = -1;
				parParcoursOn[i].coutB = -1; 			
			}
			//ajout online
			printf("Ecriture du fichier %s...\n",nomOnParTxt);
			for(i=0;i<NB_SOL;++i){
				genParcours(nbVille, parcours);
				online(nbVille, nomOnTxt, nomOnParTxt, 1, matDistVilleA, matDistVilleB, parParcoursOn, parcours);
			}	

			//resolution PLS
			//on utilise les solution de online pareto
			paretoLocalSearch(nbVille, nomPlsTxt, matDistVilleA, matDistVilleB, parParcoursOn);

			//generation des images avec gnuplot
			printf("\n");
			FILE * gnuplotPipe = popen ("gnuplot -persistent", "w");
			if(gnuplotPipe == NULL){
				printf("Il est necessaire d'avoir gnuplot d'installé pour générer les graphiques !\n");
			}else{
				//commandes gnuplots
				char tmpCommande[TAILLE_MAX];
				strcpy(tmpCommande, "set term jpeg");
				fprintf(gnuplotPipe, "%s \n", tmpCommande);

				//image offline 500
				strcpy(tmpCommande, "set output '");
				strcat(tmpCommande, nomOffJpg);
				strcat(tmpCommande, "'");
				fprintf(gnuplotPipe, "%s \n", tmpCommande);
				strcpy(tmpCommande, "plot '");
				strcat(tmpCommande, nomOffTxt);
				strcat(tmpCommande, "' using 1:2");
				fprintf(gnuplotPipe, "%s \n", tmpCommande);
				printf("Génération du graphique %s...\n",nomOffJpg);
				//image offline 500 pareto
				strcpy(tmpCommande, "set output '");
				strcat(tmpCommande, nomOffParJpg);
				strcat(tmpCommande, "'");
				fprintf(gnuplotPipe, "%s \n", tmpCommande);
				strcpy(tmpCommande, "plot '");
				strcat(tmpCommande, nomOffParTxt);
				strcat(tmpCommande, "' using 1:2");
				fprintf(gnuplotPipe, "%s \n", tmpCommande);
				printf("Génération du graphique %s...\n",nomOffParJpg);

				//image online 500
				strcpy(tmpCommande, "set output '");
				strcat(tmpCommande, nomOnJpg);
				strcat(tmpCommande, "'");
				fprintf(gnuplotPipe, "%s \n", tmpCommande);
				strcpy(tmpCommande, "plot '");
				strcat(tmpCommande, nomOnTxt);
				strcat(tmpCommande, "' using 1:2");
				fprintf(gnuplotPipe, "%s \n", tmpCommande);
				printf("Génération du graphique %s...\n",nomOnJpg);
				//image online 500 pareto
				strcpy(tmpCommande, "set output '");
				strcat(tmpCommande, nomOnParJpg);
				strcat(tmpCommande, "'");
				fprintf(gnuplotPipe, "%s \n", tmpCommande);
				strcpy(tmpCommande, "plot '");
				strcat(tmpCommande, nomOnParTxt);
				strcat(tmpCommande, "' using 1:2");
				fprintf(gnuplotPipe, "%s \n", tmpCommande);
				printf("Génération du graphique %s...\n",nomOnParJpg);

				//image pls pareto
				strcpy(tmpCommande, "set output '");
				strcat(tmpCommande, nomPlsJpg);
				strcat(tmpCommande, "'");
				fprintf(gnuplotPipe, "%s \n", tmpCommande);
				strcpy(tmpCommande, "plot '");
				strcat(tmpCommande, nomPlsTxt);
				strcat(tmpCommande, "' using 1:2");
				fprintf(gnuplotPipe, "%s \n", tmpCommande);
				printf("Génération du graphique %s...\n",nomPlsJpg);
			}
		}
	}
	printf("\nTerminé ! Regardez le dossier './result' pour voir les rendus du projet.\n");
	exit(EXIT_SUCCESS);
};
