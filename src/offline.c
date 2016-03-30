#include <stdlib.h>
#include <stdio.h>

#include "offline.h"
#include "parcours.h"

//fonction qui sors les solutions de pareto parmis un ensemble de solutions
void offline(int nbVille, char* ficOff, char* ficOffPar, double matA[nbVille][nbVille], double matB[nbVille][nbVille]){
	int parcours[nbVille],i,j;
	int parParcours[NB_SOL];
	sol valParcours[NB_SOL];	//tableau d'evaluation des parcours
	FILE* ficSortieOff = fopen(ficOff, "w"); 
	FILE* ficSortieOffPar = fopen(ficOffPar, "w"); 

	if(ficSortieOff == NULL || ficSortieOffPar == NULL){
		printf("Erreur lors de la création des fichiers.\n");
		exit(EXIT_FAILURE);
	}else{
		//generation des parcours et ecriture dans le fichier
		printf("Ecriture du fichier %s...\n",ficOff);
		fprintf(ficSortieOff,"#--------------------------------------------------------------# \n");
		fprintf(ficSortieOff,"# Le fichier se présente ainsi : \n");
		fprintf(ficSortieOff,"# Parcours i : \n");
		fprintf(ficSortieOff,"# Detail du parcours \n");
		fprintf(ficSortieOff,"# CoutDuParcoursPourLe1erFichier CoutDuParcoursPourLe2emeFichier \n");
		fprintf(ficSortieOff,"#--------------------------------------------------------------# \n\n");
		for(i=0;i<NB_SOL;++i){
			//generation
			genParcours(nbVille, parcours);
			//cout du parcrours
			valParcours[i]=evalParcours(nbVille,parcours,matA,matB);
			//sauvegarde du parcours
			fprintf(ficSortieOff,"# Parcours %d : \n# ",i);
			for(j=1;j<nbVille;++j)	
				fprintf(ficSortieOff,"%d ",parcours[j]);
			fprintf(ficSortieOff,"\n%f %f\n\n",valParcours[i].coutA,valParcours[i].coutB);
			parParcours[i]=1; 
		}
		//fermeture du fichier
		fclose(ficSortieOff);
		//evaluation des meilleurs parcours
		for(i=0;i<NB_SOL;++i)
			for(j=0;j<NB_SOL;++j)
				if(i != j){
					if(domine(valParcours[i],valParcours[j]) == 1)
						parParcours[i] = 0;
					if(domine(valParcours[i],valParcours[j]) == -1)
						parParcours[j] = 0;
				}
		//sauvegarde des meilleurs parcours et ecriture fichier
		printf("Ecriture du fichier %s...\n",ficOffPar);
		fprintf(ficSortieOffPar,"#--------------------------------------------------------------# \n");
		fprintf(ficSortieOffPar,"# Le fichier se présente ainsi : \n");
		fprintf(ficSortieOffPar,"# Parcours i : \n");
		fprintf(ficSortieOffPar,"# Detail du parcours \n");
		fprintf(ficSortieOffPar,"# CoutDuParcoursPourLe1erFichier CoutDuParcoursPourLe2emeFichier \n");
		fprintf(ficSortieOffPar,"#--------------------------------------------------------------# \n\n");
		for(i=0;i<NB_SOL;++i)
			if(parParcours[i]==1){
				fprintf(ficSortieOffPar,"# Parcours %d : \n# ",i);
				for(j=1;j<nbVille;++j)	
					fprintf(ficSortieOffPar,"%d ",valParcours[i].parcours[j]);
				fprintf(ficSortieOffPar,"\n%f %f\n\n",valParcours[i].coutA, valParcours[i].coutB);
			}
		//fermeture du fichier
		fclose(ficSortieOffPar);
	}	
};

