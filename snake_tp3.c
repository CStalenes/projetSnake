#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <MLV/MLV_all.h>
#define N 64
#define M 32
#define CARRE 20
#define TAILLE_X CARRE * M
#define TAILLE_Y CARRE * N
#define BORD 50
#define TAILLE_SERP 2
#define NB_POMMES 3

typedef struct {
	int ligne;
	int colonne;
} Case;

typedef enum {
	NORD,
	SUD,
	EST,
	OUEST
} Direction;

typedef struct serpent {
	Case corps[N * M];
	int taille;
	Direction dir;
} Serpent;

typedef struct pomme {
	Case position;
} Pomme;

typedef struct monde {
	Serpent serpent;
	Pomme pomme[3];
	int nb_mange;
} Monde;

Pomme pomme_gen_alea(int n, int m) {
	Pomme p;

	p.position.ligne = rand() % n + 1;
	p.position.colonne = rand() % m + 1;
	return p;
}

void ajouter_pomme_monde(Monde *mon) {
	Pomme p;
	int x;
	int y;
	int i;
	int j;

	p = pomme_gen_alea(N, M);
	x = p.position.ligne;
	y = p.position.colonne;

	/* verifie que la pomme n'apparaisse pas sur le serpent */ /* (*mon).serpent = mon->serpent */
	for (i = 0; i < mon->serpent.taille; i++) {
		if (y == mon->serpent.corps[i].ligne && x == mon->serpent.corps[i].colonne) {
			ajouter_pomme_monde(mon);
			return ;
		}
	}

	/* verifie que la pomme n'apparaisse pas sur une pomme deja existante */
	for (j = 0; j < 3; j++) {
		if (x == mon->pomme[j].position.ligne && y == mon->pomme[j].position.colonne) {
			ajouter_pomme_monde(mon);
			return ;
		}
	}

	for (i = 0; mon->pomme[i].position.ligne != 0 && mon->pomme[i].position.colonne != 0; i++) {
	}
	mon->pomme[i].position.ligne = x;/* afin de ne pas avoir tous les serpent en coordonné (0,0) */
	mon->pomme[i].position.colonne = y;
}

Serpent init_serpent() {
	Serpent ser;
	int i;

	ser.corps[0].ligne = M / 2;
	ser.corps[0].colonne = N / 2;
	for (i = 0; i < TAILLE_SERP - 1; i++) {
		ser.corps[i + 1].ligne = M / 2 - (i + 1);/* afin d afficher le reste du corps du serpent */
		ser.corps[i + 1].colonne = N / 2;
	}
	ser.taille = TAILLE_SERP;
	ser.dir = EST;
	return ser;
}

/* fct ajoute */
Monde monde_gen() {
	Monde mon;
	int i;

	for (i = 0; i < 3; i++) {
		mon.pomme[i].position.ligne = 0;
		mon.pomme[i].position.colonne = 0;
	}
	mon.nb_mange = 0;
	return mon;
}

Monde init_monde(int nb_pommes) {
	int i = 0;
	Monde mon;

	mon = monde_gen();
	mon.serpent = init_serpent();
	while (i < nb_pommes) {
		ajouter_pomme_monde(&mon);
		i++;
	}
	return mon;
}

int deplacer_serpent(Monde *mon) {
	int i;
	int j = mon->serpent.taille;/
	int tete_serp_x;
	int tete_serp_y;

	/* on stocke les coordonnees de la tete */
	tete_serp_x = mon->serpent.corps[0].ligne;
	tete_serp_y = mon->serpent.corps[0].colonne;

	while (j > 0) {
		mon->serpent.corps[j].ligne = mon->serpent.corps[j - 1].ligne;
		mon->serpent.corps[j].colonne = mon->serpent.corps[j - 1].colonne;
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

int manger_pomme(Monde *mon) {
	int i;
	int tete_x;
	int tete_y;

	tete_x = mon->serpent.corps[0].colonne;
	tete_y = mon->serpent.corps[0].ligne;
	for (i = 0; i < 3; i++) {
		if (tete_x == mon->pomme[i].position.ligne && tete_y == mon->pomme[i].position.colonne) {
			mon->nb_mange ++;
			mon->pomme[i].position.ligne = 0;
			mon->pomme[i].position.colonne = 0;
			return 1;
		}
	}
	return 0;
}

int mort_serpent(Monde *mon) {
	int i;
	int tete_x;
	int tete_y;

	tete_x = mon->serpent.corps[0].ligne;
	tete_y = mon->serpent.corps[0].colonne;
	if (tete_x < 1 || tete_x > M || tete_y < 1 || tete_y > N) {
		return 1;
	}
	for (i = 1; i < mon->serpent.taille; i++) {
		if (tete_x == mon->serpent.corps[i].ligne && tete_y == mon->serpent.corps[i].colonne) {
			return 1;
		}
	}
	return 0;
}

void afficher_quadrillage(Monde *mon) {
	int i;
	int carre;

	carre = 0;
	for (i = 0; i < M + 1; i++) {
		MLV_draw_line(carre + BORD / 2, 0  + BORD / 2, carre + BORD / 2, TAILLE_Y + BORD / 2, MLV_COLOR_WHITE);
		carre += CARRE;
	}

	carre = 0;
	for (i = 0; i < N + 1; i++) {
		MLV_draw_line(0 + BORD / 2, carre + BORD / 2, TAILLE_X + BORD / 2, carre + BORD / 2, MLV_COLOR_WHITE);
		carre += CARRE;
	}
}

void afficher_pomme(Pomme *pom) {
	int x;
	int y;

	x = pom->position.colonne;
	y = pom->position.ligne;
	MLV_draw_filled_circle(x * CARRE - (CARRE / 2)  + BORD / 2, y * CARRE - (CARRE / 2) + BORD / 2, CARRE / 3, MLV_COLOR_RED);
}

void afficher_serpent(Serpent *ser) {
	int i;
	int tete_x;
	int tete_y;

	tete_x = ser->corps[0].ligne;
	tete_y = ser->corps[0].colonne;
	MLV_draw_filled_circle(tete_x * CARRE - (CARRE / 2) + BORD / 2, tete_y * CARRE - (CARRE / 2) + BORD / 2, CARRE / 3, MLV_COLOR_YELLOW);
	for (i = 1; i < ser->taille; i++) {
		MLV_draw_filled_rectangle(ser->corps[i].ligne * CARRE - (3 * CARRE / 4) + BORD / 2, ser->corps[i].colonne * CARRE - (3 * CARRE / 4) + BORD / 2, CARRE / 2, CARRE / 2, MLV_COLOR_GREEN);
	}
}

void afficher_monde(Monde *mon) {
	int i;

	afficher_quadrillage(mon);
	afficher_serpent(&mon->serpent);
	for (i = 0; i < 3; i++) {
		afficher_pomme(&mon->pomme[i]);
		MLV_actualise_window();
	}
}

int main(int argc, char* argv[]){
	char *score = "Partie terminee";
	
	Monde mon;
	MLV_Keyboard_button dir;
	MLV_Button_state etat;
	MLV_Event event;

	srand(time(NULL));
	MLV_create_window("Snake", "", TAILLE_X + BORD, TAILLE_Y + BORD);
	mon = init_monde(NB_POMMES);
	afficher_monde(&mon);
	MLV_wait_keyboard(&dir, NULL, NULL);
	if (dir == MLV_KEYBOARD_SPACE) {
		while (mort_serpent(&mon) != 1) {
			event = MLV_get_event(&dir, NULL, NULL, NULL, NULL, NULL, NULL, NULL, &etat);
			if (event == MLV_KEY) {
				if (etat == MLV_PRESSED) {
					;
				}
			}
			if (manger_pomme(&mon) == 1) {
				ajouter_pomme_monde(&mon);
			}

			if (dir == MLV_KEYBOARD_UP) {
				if (mon.serpent.dir != SUD) {
					mon.serpent.dir = NORD;
				}
			}

			if (dir == MLV_KEYBOARD_DOWN) {
				if (mon.serpent.dir != NORD) {
					mon.serpent.dir = SUD;
				}
			}

			if (dir == MLV_KEYBOARD_LEFT) {
				if (mon.serpent.dir != EST) {
					mon.serpent.dir = OUEST;
				}
			}

			if (dir == MLV_KEYBOARD_RIGHT) {
				if (mon.serpent.dir != OUEST) {
					mon.serpent.dir = EST;
				}
			}
			deplacer_serpent(&mon);
			MLV_clear_window(MLV_COLOR_BLACK);
			afficher_monde(&mon);
			MLV_wait_milliseconds(125);
		}
		MLV_clear_window(MLV_COLOR_BLACK);
		MLV_draw_text((TAILLE_X + BORD) / 2 - 45, (TAILLE_Y + BORD)/ 2, score, MLV_COLOR_WHITE);
		MLV_actualise_window();
		MLV_wait_seconds(2);
	}

	MLV_actualise_window();
	MLV_free_window();
	
	return 0;
}