#include "parcours.h"

//genere un parcours de ville dans tab sans doublons 
void genParcours(int nbVille, int tab[nbVille]){
	//variables	
	int i,j,tmp,found;
	//init tab
	for(i=1; i<nbVille; ++i)
		tab[i]=0;	
	//remplissage aleatoire sans doublons	
	for(i=1; i<nbVille; ++i){
		found = 1;
		tmp=rand()%nbVille;
		for(j=1; j<nbVille; ++j)
			if(tmp == tab[j])
				found = 0;
		if(found == 0)
			--i;
		else
			tab[i] = tmp;
	}
};

//evalue le parcours tab et retourne une sol en conséquence
//tab est le parcours des villes tab[i] à tab[i+1] à tab[i+2]...
//mat est la matrice des distances entre les villes
sol evalParcours(int nbVille, int tab[nbVille], double matA[nbVille][nbVille], double matB[nbVille][nbVille]){
	int i;
	//init
	sol res;
	res.coutA=0;
	res.coutB=0;
	for(i=1;i<nbVille-1;++i){
		res.parcours[i] = tab[i];
		res.coutA+= matA[tab[i]][tab[i+1]]; 
		res.coutB+= matB[tab[i]][tab[i+1]]; 
	}
	res.parcours[i] = tab[i];
	//on retourne au depart
	res.coutA+=matA[tab[i]][tab[1]];
	res.coutB+=matB[tab[i]][tab[1]];
	return res;
};

//fonction qui determine si la solution est dominée ou non
//1 si S1 >= S2
//-1 si S2 <= S1
//0 sinon
int domine(sol s1, sol s2){
	if(s1.coutA >= s2.coutA && s1.coutB >= s2.coutB) 
		return 1;
	if(s1.coutA <= s2.coutA && s1.coutB <= s2.coutB) 
		return -1;
	return 0;
};

/*
voisinage
inverser 2 ville
ex : 1 2 3 4 5 6 7 8 9
donne: 1 2 6 5 4 3 7 8 9
N voisin = n(n-1) / 2 
*/
void genVoisin(int nbVille, int a, int b, int parcours[nbVille], int res[nbVille]){
	int i;
	if(a>b){
		i=a;	
		a=b;
		b=i;
	}	
	for(i=0;i<a;++i)
		res[i]=parcours[i];
	for(;b>=a;--b){
		res[i]=parcours[b];
		++i;
	}
	for(;i<nbVille;++i)
		res[i]=parcours[i];
};


