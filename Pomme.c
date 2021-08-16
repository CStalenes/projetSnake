#include <stdlib.h>
#include <stdio.h>

Pomme pomme_gen_alea(int n, int m){

	Pomme pomme;
	pomme.position.ligne   = rand() % n+1;
	pomme.position.colonne = rand() % m+1;
	return pomme;

}