

#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "ecosys.h"


int main(void) { 
  int i;
  int energie=10;
  srand(time(NULL));

  Animal *a1 = creer_animal(0,10, energie);
  Animal *a2 = creer_animal(15,35, energie);
  Animal *a3 = creer_animal(2,42, energie);
  Animal *a4 = creer_animal(18,13, energie);
  
  a1->suivant=a2;
  a2->suivant=a3;
  a3->suivant=a4;

  ajouter_animal(2,3,10,&a1);


  Animal *a5 = creer_animal(2,5, energie);
  Animal *a6 = creer_animal(15,35, energie);
  Animal *a7 = creer_animal(9,22, energie);
  Animal *a8 = creer_animal(17,3, energie);
  
  a5->suivant=a6;
  a6->suivant=a7;
  a7->suivant=a8;

  enlever_animal(&a5,a5); enlever_animal(&a5,a7);
  
  
  printf("Test de la fonction ajouter_animal(2,3,10,&a1) en affichant a1 :\n");
  Animal *a1_test = a1;
  while (a1_test) {
  	 printf("%d, %d, %f\n", a1_test->x, a1_test->y, a1_test->energie);
  	 a1_test = a1_test->suivant;
  }
  
  
  printf("\nEn affichant a5, test des fonctions : enlever_animal(&a5,a5) et enlever_animal(&5,&7)\n");
  Animal *a5_test = a5;
  while (a5_test) {
    printf("%d, %d, %f\n", a5_test->x, a5_test->y, a5_test->energie);
    a5_test = a5_test->suivant;
  }
  
  
  printf("\n");
  afficher_ecosys(a1,a5);

  a1 = liberer_liste_animaux(a1);
  a5 = liberer_liste_animaux(a5);
  
  return 0;
}
