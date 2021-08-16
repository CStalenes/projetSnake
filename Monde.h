#ifndef __MONDE__
#define __MONDE__

typedef struct monde{

	Serpent serpent;
	Pomme pomme[3];
	int nb_pomme_mange;

}Monde;

void ajouter_pomme_monde(Monde *mon);

Monde init_monde(int nb_pomme);


#endif