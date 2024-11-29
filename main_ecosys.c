

#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <strings.h>

#include "ecosys.h" 

#define NB_PROIES 20
#define NB_PREDATEURS 20
#define T_WAIT 40000
#define MAX_ITERATIONS 200
// ------- on a fait test(void) { } pour tester les 2 fct : bouger_animaux() et reproduce() ) et main(void){  pour la simulation }
//TME3 -exo4
// Remarque de l'exo: creer un seul animal

void test(void){
  // Test pour le bouger_animaux();

  Animal *a1 = creer_animal(15, 10, 10.0);
  assert(a1->x >= 0 && a1->x < SIZE_X); assert(a1->y >= 0 && a1->y < SIZE_Y);

  printf("Test de la fonction bouger_animaux() :\n");
  printf("Animal avant bouger : %d, %d, %.2f, [%d,%d]\n", a1->x, a1->y, a1->energie, a1->dir[0], a1->dir[1]);
  while((a1->x == 15) && (a1->y == 10))
    bouger_animaux(a1);
  printf("Animal après bouger : %d, %d, %.2f, [%d,%d]\n", a1->x, a1->y, a1->energie, a1->dir[0], a1->dir[1]);

  printf("\n");


  // Test pour le reproduce();

  for(int i = 0; i < 2; i++)
    reproduce(&a1, p_reproduce_proie);

  printf("Test de la fonction reproduce() 2 fois de suite : \n");
  Animal *temp = a1;
  while(temp){
    printf("%d, %d, %.2f, [%d,%d]\n", a1->x, a1->y, a1->energie, a1->dir[0], a1->dir[1]);
    temp = temp->suivant;
  }

  printf("\n");
  a1 = liberer_liste_animaux(a1);
  
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------*/

int main(void) {
  srand(time(NULL));
  float energie_proie = 10.0;
  float energie_predateur = 100.0;

  //Tout ce qui concerne les tests du TME 3.
  //test();


  // Création du tableau du monde, pour l'herbe
	int monde[SIZE_X][SIZE_Y] ;
   for (int i = 0; i < SIZE_X; i++){
    for (int j = 0; j < SIZE_Y; j++){
      monde[i][j] = 0;
    }
   }
   

  // Création de 20 animaux pour liste_proie et liste_predateur.

  Animal *liste_proie = NULL;
  Animal *liste_predateur = NULL;
	
	for(int i = 0; i < NB_PROIES; i++){ //NB_PROIES=20
		ajouter_animal(rand() % SIZE_X, rand() % SIZE_Y, energie_proie, &liste_proie);
    ajouter_animal(rand() % SIZE_X, rand() % SIZE_Y, energie_predateur, &liste_predateur);
	}


  // Ecrire du nombre de proies/predateurs par génération, afin de l'utiliser avec gnuplot.

  FILE *f = fopen("Evol_Pop.txt", "w");
    if (f == NULL){
      printf("Erreur lors de l'ouverture.");
      exit(1);
    }
  
  // fprintf(f, "gen proies predateurs\n");


  //Lancement de la simulation.

  int cpt = 0;
  while((liste_proie || liste_predateur) && cpt<MAX_ITERATIONS){
    fprintf(f, "%d %d %d\n", cpt, compte_animal_it(liste_proie), compte_animal_it(liste_predateur));
    afficher_ecosys(liste_proie, liste_predateur);
    clear_screen(); 
    afficher_ecosys(liste_proie, liste_predateur);
    rafraichir_proies(&liste_proie, monde);
    rafraichir_predateurs(&liste_predateur, &liste_proie);
    rafraichir_monde(monde);
    usleep(T_WAIT);
    cpt++;
  }

  fclose(f);
  liste_proie = liberer_liste_animaux(liste_proie);
  liste_predateur = liberer_liste_animaux(liste_predateur);
  return 0;
  }

  //printf("La simulation est terminée !\n"); 
  //on peut pas ecrire des phrases dans le fichier sinon gnuplot peut pas dessiner le graphe
  /*------------------------------------------------------------------------------------*/
  /*--------------------------------la partie approfondissement-------------------------------------------------*/
  
  
  // Graphe d'evolution à fournir plus tard

/*
Tout d'abord on execute notre main.ecosys.c :
-> make
->./ecosys
->le fichier "Evol_Pop.txt" sera creer avec une simulation 
->pour pouvoir dessiner notre graphe on doit installer gnuplot
->sudo apt gnuplot ((avec une version affiche sur le terminal en ecrivant gnuplot ca affiche les version qui existent
->
Afin d'utiliser gnuplot correctement, il faut taper ces commandes ci-dessous :
  1-gnuplot
  2-set terminal pngcairo size 640,480
  3-set output 'graph.png'
  4-plot "Evol_Pop.txt" using 1:2 with lines title "proies"
  5-replot "Evol_Pop.txt" using 1:3 with lines title "predateurs"
  
  --> mais c'est mieux d'utiliser directement :
 plot "Evol_Pop.txt" using 1:2 with lines title "Proies", \
     "Evol_Pop.txt" using 1:3 with lines title "Prédateurs"
     
  6-set output  # Ferme le fichier PNG

  plot "Evol_Pop.txt" using 1:2 with lines title "proies"
  replot "Evol_Pop.txt" using 1:3 with lines title "predateurs"
  exit
----------------------------------------------------------------------------------------------------------------------
Les paramètres que l'on peut modifier sont :
  Le nombre de proies/prédateurs au début.
  Leur énergie de base pour faire plus de génération.
  Ou les probabilités dans le fichier ecosys.c
*/
