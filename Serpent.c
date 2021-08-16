
Serpent init_serpent(){
	Serpent ser;
	int i;

	ser.corp[0].ligne   = N/2;/* car la tete c est la première coord du serpent */
	ser.corp[0].colonne = M/2;

	for(i=0; i< TAILLE_SER - 1; i++){ /* taille-1 car on veut juste dessiner le corp sans inclure la tete  avec */
		ser.corp[i + 1].ligne   = N/2 - (i+1);/* si on ne met pas i+1 on ne pourra pas avancer et on soustrait par -(i+1) pour avoir tt le corp du serpent */
		ser.corp[i + 1].colonne = M/2; 
	}

	ser.taille = TAILLE_SER; /* on affecte par la bonne taille trouvé */
	ser.dir    = Est;
	return ser;
}