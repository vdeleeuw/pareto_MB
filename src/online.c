#include <stdio.h>
#include <stdlib.h>

#include "online.h"
#include "parcours.h"

//fonction qui valide les solutions au fur et a mesure online(A, S)
//parParcours[TAILLE_TAB] doit bien être initalisé lors du premier appel !! (toutes les sol à -1 -1)
//return 1 si modif, 0 sinon
//fic = 0 pas de fichier généré, autre chose oui
int online(int nbVille, char* ficOn, char* ficOnPar, int fic, double matA[nbVille][nbVille], double matB[nbVille][nbVille], sol parParcours[TAILLE_TAB], int parcours[nbVille]){
	//ecrire le parcours dans le fichier ficOn sans l'effacer	
	FILE* ficSortieOn = fopen(ficOn,"r");
	if(fic != 0){
		if(ficSortieOn == NULL){
			//creation du fichier si inexistant
			ficSortieOn = fopen(ficOn,"w");
			if(ficSortieOn == NULL){
				printf("Erreur lors de la création des fichiers !");		
				exit(EXIT_FAILURE);
			}else{
				fprintf(ficSortieOn,"#--------------------------------------------------------------# \n");
				fprintf(ficSortieOn,"# Le fichier se présente ainsi : \n");
				fprintf(ficSortieOn,"# Parcours : \n");
				fprintf(ficSortieOn,"# Detail du parcours \n");
				fprintf(ficSortieOn,"# CoutDuParcoursPourLe1erFichier CoutDuParcoursPourLe2emeFichier \n");
				fprintf(ficSortieOn,"#--------------------------------------------------------------# \n\n");
				printf("Ecriture du fichier %s...\n",ficOn);
		
			}
		}
	}
	//eval le nouveau parcours
	int i,j,nbChange=0;	
	sol tmpSol=evalParcours(nbVille,parcours,matA,matB);
	//ajout au fichier existant
	if(fic != 0){
		fclose(ficSortieOn);
	 		ficSortieOn = fopen(ficOn,"a");
		if(ficSortieOn != NULL){
			fprintf(ficSortieOn,"# Parcours :\n# ");
			for(i=1;i<nbVille;++i)	
				fprintf(ficSortieOn,"%d ",parcours[i]);
			fprintf(ficSortieOn,"\n%f %f\n\n",tmpSol.coutA,tmpSol.coutB);
		}else{
			printf("Erreur lors de l'ajout dans les fichiers !\n");
			exit(EXIT_FAILURE);
		}
	}
	//domine le nouveau parcours
	for(i=0;i<TAILLE_TAB;++i)
			if(parParcours[i].coutA != -1 && parParcours[i].coutB != -1){
				//si mieu déjà présent
				if(domine(tmpSol,parParcours[i]) == 1)
					return 0;
				//si remplace un parcours existant
				if(domine(tmpSol,parParcours[i]) == -1){
					if(nbChange == 0){
						parParcours[i].coutA = tmpSol.coutA;
						parParcours[i].coutB = tmpSol.coutB;
						for(j=1;j<nbVille;++j)
							parParcours[i].parcours[j] = tmpSol.parcours[j];					
						nbChange++;					
					}else{		
						parParcours[i].coutA = -1;
						parParcours[i].coutB = -1;
					}
				}			
			}
	//si comparable à aucun parcour on l'ajoute
	if(nbChange == 0)
		for(i=0;i<TAILLE_TAB;++i)
			if(parParcours[i].coutA == -1 && parParcours[i].coutB == -1){
				parParcours[i].coutA = tmpSol.coutA;
				parParcours[i].coutB = tmpSol.coutB;
				for(j=1;j<nbVille;++j)
					parParcours[i].parcours[j] = tmpSol.parcours[j];	
				break;
			}
	//reecrire tout le fichier ficOnPar
	FILE* ficSortieOnPar = fopen(ficOnPar,"w"); 
	if(fic != 0){
		fclose(ficSortieOn);
		if(ficSortieOnPar == NULL){
			printf("Erreur lors de l'écriture des fichiers !\n");
			exit(EXIT_FAILURE);
		}else{
			fprintf(ficSortieOnPar,"#--------------------------------------------------------------# \n");
			fprintf(ficSortieOnPar,"# Le fichier se présente ainsi : \n");
			fprintf(ficSortieOnPar,"# Parcours : \n");
			fprintf(ficSortieOnPar,"# Detail du parcours \n");
			fprintf(ficSortieOnPar,"# CoutDuParcoursPourLe1erFichier CoutDuParcoursPourLe2emeFichier \n");
			fprintf(ficSortieOnPar,"#--------------------------------------------------------------# \n\n");
			int i,j;
			for(i=0;i<TAILLE_TAB;++i)
				if(parParcours[i].coutA != -1 && parParcours[i].coutB != -1){
					fprintf(ficSortieOnPar,"# Parcours : \n# ");
					for(j=1;j<nbVille;++j)
						fprintf(ficSortieOnPar,"%d ",parParcours[i].parcours[j]);
					fprintf(ficSortieOnPar,"\n%f %f\n\n",parParcours[i].coutA, parParcours[i].coutB);	
				}
			fclose(ficSortieOnPar);
		}
	}
	return 1;
};
