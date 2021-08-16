#include <stdlib.h>
#include <stdio.h>


void ajouter_pomme_monde(Monde *mon){

	Pomme pomme;

	int i;
	int j;
	int x;
	int y;

	pomme = pomme_gen_alea(n,m);
	x = pomme.position.ligne;
	y = pomme.position.colonne;

	/* IL faut pas que la pomme apparaisse sur le serpent */
	/*si les coordonne(x,y) de la pomme sont pareil que celle ou il y a le serpent (sur la grille corp[i])   alors on la rajoute ailleur en faisant appel à la fonction ajoute_pom(mon)*/

	for(i = 0; i< mon->ser.taille; i++){
		if(x == mon->ser.corp[i].ligne && y == mon->ser.corp[j].colonne){
			ajouter_pomme_monde(mon);
			return ;
		}
	}

	/* Il faut pas que la pomme soit ajouter dans une case ayant déja une pomme */

	for( i = 0; i < 3; i++){
		if(x == mon->pomme[i].position.ligne && y == mon->pomme[j].position.colonne){
			ajouter_pomme_monde(mon);
			return;
		}
	}

	/* comme on commence a i = 0 alors on doit pas avoir le serpent en coord (0,0) */

	for(i = 0; mon->ser.corp[i].ligne != 0 && mon->ser.corp[i].colonne != 0; i++){
		return ;

	}

	mon->pomme[i].position.ligne   = x;
	mon->pomme[j].position.colonne = y; 

	/* Il faut pas que la pomme soit afficher à l'exterieur du cadre */


}



Monde init_monde(int nb_pomme){
	int i;
	Monde mon;

	//mon      = monde_gen();
	mon.ser  = init_serpent(); 

	while(i< nb_pomme){
		ajouter_pomme_monde(&mon);
		i++;
	}
	return mon;
}

int deplacer_serpent(Monde *mon){
	int i;
	int j = mon->serpent.taille;/* on met ça car qd le serpent se deplace c'est tt le long du corps qui bouge aussi dc on affect j a taille_ser */
	int tete_serp_x;
	int tete_serp_y;

	/* on stocke les coordonnees de la tete */
	tete_serp_x = mon->serpent.corps[0].ligne;
	tete_serp_y = mon->serpent.corps[0].colonne;

	while (j > 0) {
		mon->serpent.corps[j].ligne = mon->serpent.corps[j + 1].ligne;
		mon->serpent.corps[j].colonne = mon->serpent.corps[j + 1].colonne;
		j--;
	}

	if (mon->serpent.dir == NORD) {
		/* on compare les coordonnees de chaque pomme avec les coordonnees de la tete du serpent */
		for (i = 0; i < 3; i++){
			if (mon->pomme[i].position.ligne == tete_serp_x - 1 && mon->pomme[i].position.colonne == tete_serp_y) {
				return 0;
			}
		}
		mon->serpent.corps[0].colonne -= 1;
	}

	else if (mon->serpent.dir == SUD) {
		for (i = 0; i < 3; i++){
			if (mon->pomme[i].position.ligne == tete_serp_x + 1 && mon->pomme[i].position.colonne == tete_serp_y) {
				return 0;
			}
		}
		mon->serpent.corps[0].colonne += 1;
	}

	else if (mon->serpent.dir == EST) {
		for (i = 0; i < 3; i++){
			if (mon->pomme[i].position.ligne == tete_serp_x && mon->pomme[i].position.colonne == tete_serp_y + 1) {
				return 0;
			}
		}
		mon->serpent.corps[0].ligne += 1;
	}

	else if (mon->serpent.dir == OUEST) {
		for (i = 0; i < 3; i++){
			if (mon->pomme[i].position.ligne == tete_serp_x && mon->pomme[i].position.colonne == tete_serp_y - 1) {
				return 0;
			}
		}
		mon->serpent.corps[0].ligne -= 1;
	}

	return 1;

}