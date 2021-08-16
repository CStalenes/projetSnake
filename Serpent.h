#ifndef __SERPENT__
#define __SERPENT__

#define N 32
#define M 32
#define taille_serpent 2



typedef enum{
	
	Nord;
	Sud;
	Ouest;
	Est;

}Direction;

typedef struct serpent{

	Case corps[N * M];/* pour que le serpent puisse etre creer sur la grille et pour qu'il puisse se deplecer aussi alors on utilse un tableau de position */
	Direction d;
	int taille;

}Serpent;


Serpent init_serpent();


#endif