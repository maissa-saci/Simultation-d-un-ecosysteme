

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "ecosys.h"

float p_ch_dir=0.5;
float p_reproduce_proie=0.3;
float p_reproduce_predateur=0.3;
int temps_repousse_herbe=-15;

/* PARTIE 1*/
/* Fourni: Part 1, exercice 3, question 2 */
Animal *creer_animal(int x, int y, float energie) {
  Animal *na = (Animal *)malloc(sizeof(Animal));
  assert(na);
  na->x = x;
  na->y = y;
  na->energie = energie;
  na->dir[0] = rand() % 3 - 1;
  na->dir[1] = rand() % 3 - 1;
  na->suivant = NULL;
  return na;
}


/* Fourni: Part 1, exercice 3, question 3 */
Animal *ajouter_en_tete_animal(Animal *liste, Animal *animal) {
  assert(animal);
  assert(!animal->suivant);
  animal->suivant = liste;
  return animal;
}

/* A faire. TME2, question 2 */
void ajouter_animal(int x, int y, float energie, Animal **liste_animal) {
        // on verifie les deux conditions sur les coordonnées
	assert(x >= 0 && x < SIZE_X);
	assert(y >= 0 && y < SIZE_Y);
	//creation d'un nouvel animal et l'ajouter en tete de liste
	*liste_animal = ajouter_en_tete_animal(*liste_animal, creer_animal(x,y,energie));
}

/* A Faire. Part 1, exercice 5, question 5 */
void enlever_animal(Animal **liste, Animal *animal) {
	Animal *listeP = *liste;
	Animal *temp = NULL;
	
	if (listeP == animal){
		*liste = (*liste)->suivant;
    free(listeP);
	}
	
	else {
		while(listeP){
			if(listeP->suivant == animal){
				temp = listeP->suivant;
				listeP->suivant = listeP->suivant->suivant;
				free(temp);
			}
			
			else listeP = listeP->suivant;
		}
	}
}

/* A Faire. TME2 question 4 */
Animal* liberer_liste_animaux(Animal *liste) {
	Animal *temp1 = liste;
	Animal *temp2 = NULL;
	// Parcourir la liste et libérer chaque élément
	while(temp1){
		temp2 = temp1;
		temp1 = temp1->suivant;// Parcourir la liste et libérer chaque élément
		free(temp2);// Parcourir la liste et libérer chaque élément
	}
	
	return NULL;
}

/* Fourni: part 1, exercice 3, question 4 */
unsigned int compte_animal_rec(Animal *la) {
  if (!la) return 0;
  return 1 + compte_animal_rec(la->suivant);
}

/* Fourni: part 1, exercice 3, question 4 */
unsigned int compte_animal_it(Animal *la) {
  unsigned int cpt=0;
  while (la) {
    cpt++;
    la=la->suivant;
  }
  return cpt;
}



/* Part 1. Exercice 4, question 1, ATTENTION, ce code est susceptible de contenir des erreurs... corrigé.*/
//TME2 -qst 1- 

/*apres s'avoir appuyer sur l'outil debogage gdb/ddd on a trouve qu'il y a une erreur dans cette fonction 
  dans le tableau 2D ecosys  les lignes et les colonnes etaient inverses*/

  /*ceci est la version corrigée */ 
void afficher_ecosys(Animal *liste_proie, Animal *liste_predateur) {
  unsigned int i, j;
  char ecosys[SIZE_X][SIZE_Y];
  Animal *pa=NULL;

  for (i = 0; i < SIZE_X; ++i) {
    for (j = 0; j < SIZE_Y; ++j) {
      ecosys[i][j]=' ';
    }
  }


  // On ajoute les proies
  pa = liste_proie;
  while (pa) {
    ecosys[pa->x][pa->y] = '*';
    pa=pa->suivant;
  }

  // On ajoute les predateurs
  pa = liste_predateur;
  while (pa) {
      if ((ecosys[pa->x][pa->y] == '@') || (ecosys[pa->x][pa->y] == '*')) { 
        ecosys[pa->x][pa->y] = '@';
      } else {
        ecosys[pa->x][pa->y] = 'O';
      }
    pa = pa->suivant;
  }

  // On affiche le tableau
  printf("+");
  for (j = 0; j < SIZE_Y; ++j) {
    printf("-");
  }  
  printf("+\n");
  for (i = 0; i < SIZE_X; ++i) {
    printf("|");
    for (j = 0; j < SIZE_Y; ++j) {
      putchar(ecosys[i][j]);
    }
    printf("|\n");
  }
  printf("+");
  for (j = 0; j < SIZE_Y; ++j) {
    printf("-");
  }
  printf("+\n");
  int nbproie=compte_animal_it(liste_proie);
  int nbpred=compte_animal_it(liste_predateur);
  
  printf("Nb proies : %5d\tNb predateurs : %5d\n", nbproie, nbpred);
  
  //Pour les boucles, il fallait mettre i < SIZE_X et j < SIZE_Y, pas l'inverse.
}


void clear_screen() {
  printf("\x1b[2J\x1b[1;1H");  /* code ANSI X3.4 pour effacer l'ecran */
}

/* PARTIE 2*/

/* Part 2. Exercice 4, question 1 */

void bouger_animaux(Animal *la) {
  Animal *a = la;
  
	while(a){
		if (rand()/(float)RAND_MAX < p_ch_dir){ // Si un nombre aléatoire entre 0 et 1 est inférieur à la probabilité de changement de direction 'p_ch_dir'
			a->dir[0] = rand()%3 - 1; //Met à jour la direction x de l'animal (entre -1, 0, ou 1) en utilisant un reste de division modulo 3
			a->dir[1] = rand()%3 - 1; 
		}
		//ajout de -->'SIZE_X'/'SIZE_Y '<-- garantit que la valeur soit positive avant de faire le modulo (utile si la direction est négative)
    //par exemple si x=-1 et dir[0]=-1 alors ca donne -1/SIZE_X =-1 (en C, le reste d'une division peut être négatif)
		a->x = (a->x + a->dir[0] + SIZE_X) % SIZE_X; 
		a->y = (a->y + a->dir[1] + SIZE_Y) % SIZE_Y; /*Si un animal est situé en (4, 4) avec une direction (1, -1), il se déplacera vers 
                                                  (5, 3). Si SIZE_X est 5, en atteignant (5, 3), il réapparaît au bord opposé (0, 3)*/
		a = a->suivant;
	}
}

/* Part 2. Exercice 4, question 3 */

//Pour chaque animal, on génère un nombre aléatoire entre 0 et 1. Si ce nombre est inférieur à p_reproduce, l’animal se reproduit.
void reproduce(Animal **la, float p_reproduce) {
  Animal *a = la ? *la : NULL;

  while(a){
    if(rand()/(float)RAND_MAX < p_reproduce){
      ajouter_animal(a->x, a->y, a->energie/2.0, la);// Ajoute un nouvel animal au même emplacement avec la moitié de l'énergie du parent
      a->energie = a->energie/2.0; // Réduit l'énergie du parent de moitié
    }

    a = a->suivant;
  }
}


/* Part 2. Exercice 6, question 1 */
void rafraichir_proies(Animal **liste_proie, int monde[SIZE_X][SIZE_Y]) {
  bouger_animaux(*liste_proie);
   // Initialise un pointeur temporaire pour parcourir la liste des proies
  Animal *temp = liste_proie ? *liste_proie : NULL;

  while(temp){
    // Diminue l'énergie de la proie de 1 unité à chaque itération
    temp->energie--;
    // Vérifie si la proie a une énergie inférieure à 0 (proie morte).
    if (temp->energie < 0){
      enlever_animal(liste_proie, temp);// Supprime la proie de la liste si elle n'a plus d'énergie.
    }
//exo 7 qst 3 ::(s'applique que sur les proies)
    else if (monde[temp->x][temp->y] > 0){ // Si la proie se trouve dans une case contenant de l'herbe (énergie > 0).
      temp->energie += monde[temp->x][temp->y]; // La proie consomme l'herbe de la case, augmentant ainsi son énergie
      monde[temp->x][temp->y] = temps_repousse_herbe;  // Réinitialise le compteur de repousse de l'herbe pour cette case
    }

    temp = temp->suivant;
  }

  reproduce(liste_proie, p_reproduce_proie);
}

/* Part 2. Exercice 7, question 1 */
//une fois on trouve une proie sur une case donnee on la retourne !!
Animal *animal_en_XY(Animal *l, int x, int y) {
  Animal *temp = l;
  while(temp){
    if ((temp->x == x) && (temp->y == y))
      return temp;
    
    temp = temp->suivant;
  }

  return NULL;
} 

/* Part 2. Exercice 7, question 2 */
/*c'est pareil que rafraichir_proie juste ici si se trouve proie dans la meme 
case du predateur alors elle serait mangee et pour le predateur
 pre->energie=pre->energie+pro->energie*/

void rafraichir_predateurs(Animal **liste_predateur, Animal **liste_proie) {
  bouger_animaux(*liste_predateur);
  Animal *temp = liste_predateur ? *liste_predateur : NULL;

  while(temp){
    temp->energie--;

    if (temp->energie < 0){
      enlever_animal(liste_predateur, temp);
    }
    else {
      // Cherche une proie dans la même case (x, y) que le prédateur actuel
      Animal *proieVictime = animal_en_XY(*liste_proie, temp->x, temp->y);

      // Si une proie est trouvée sur la même case.
      if (proieVictime != NULL){
        // Le prédateur mange la proie, gagnant l'énergie de la proie
        temp->energie += proieVictime->energie;
        enlever_animal(liste_proie, proieVictime);
      }
    }

    temp = temp->suivant;
  }

  reproduce(liste_predateur, p_reproduce_predateur);
}

/* Part 2. Exercice 5, question 2 */
void rafraichir_monde(int monde[SIZE_X][SIZE_Y]){ 
  for(int i = 0; i < SIZE_X; i++)
    for(int j = 0; j < SIZE_Y; j++)
      monde[i][j]++; /*chaque iteration de la simulation ,la quantite d'herbe de chaque case est incremente */
}





void ecrire_ecosys(const char *nom_fichier, Animal *liste_proie, Animal *liste_predateur){
        // Ouvre le fichier en mode écriture
	FILE *f = fopen(nom_fichier, "w");
	if (f == NULL){
		printf("Erreur lors de l'ouverture.");//si l'ouverture echoue
		exit(1);
	}

	fprintf(f, "<proies>\n");//en tete
	Animal *tmp = liste_proie;
	while(tmp){
	// ecriture des informations pour chaque proies 
		fprintf(f, "x=%d y=%d dir=[%d,%d] e=%f\n", tmp->x, tmp ->y, tmp->dir[0], tmp->dir[1], tmp->energie);
		tmp = tmp->suivant;
	}
	fprintf(f,"</proies>\n");//fin de la section proies

	fprintf(f,"<predateurs>\n");
	tmp = liste_predateur;
	while(tmp){
		fprintf(f, "x=%d y=%d dir=[%d,%d] e=%f\n", tmp->x, tmp ->y, tmp->dir[0], tmp->dir[1], tmp->energie);
		tmp = tmp->suivant;
	}
	fprintf(f, "</predateurs>\n");
	
	fclose(f);
}

void lire_ecosys(const char *nom_fichier, Animal **liste_proie, Animal **liste_predateur){
	FILE *f = fopen(nom_fichier, "r");
	if (f == NULL){
		printf("Erreur lors de l'ouverture.");
		exit(1);
	}

	char buffer[256]; //max 256 caractères par ligne, on vise plus haut.
	fgets(buffer, 256, f);
	assert(strncmp(buffer, "<proies>", 8) == 0);

	int x_lu, y_lu, dir0, dir1; float e_lu;
	fgets(buffer, 256, f);
	while(strncmp(buffer, "</proies>", 9) != 0){
		sscanf(buffer, "x=%d y=%d dir=[%d,%d] e=%f\n", &x_lu, &y_lu, &dir0, &dir1, &e_lu);
		Animal *a = creer_animal(x_lu, y_lu, e_lu);
		a->dir[0] = dir0; 
		a->dir[1] = dir1;
		a->suivant = *liste_proie;
		*liste_proie = a;
		fgets(buffer, 256, f);
	}

	fgets(buffer, 256, f);
	assert(strncmp(buffer, "<predateurs>", 12) == 0);

	fgets(buffer, 256, f);
	while(strncmp(buffer, "</predateurs>", 13) != 0){
		sscanf(buffer, "x=%d y=%d dir=[%d,%d] e=%f\n", &x_lu, &y_lu, &dir0, &dir1, &e_lu);
		Animal *a = creer_animal(x_lu, y_lu, e_lu);
		a->dir[0] = dir0; 
		a->dir[1] = dir1;
		a->suivant = *liste_predateur;
		*liste_predateur = a;
		fgets(buffer, 256, f);
	}

	fclose(f);
}
