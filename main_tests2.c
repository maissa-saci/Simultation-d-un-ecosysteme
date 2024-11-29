

#include <assert.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ecosys.h"


int main(){

        //------TME2 - QST 7---------------------//
        
        // Création des listes de proies et de prédateurs (20 par liste)
        srand(time(NULL)); 
        Animal *liste_proie = creer_animal(rand() % SIZE_X, rand() % SIZE_Y, 10);
	Animal *liste_predateur = creer_animal(rand() % SIZE_X, rand() % SIZE_Y, 10);
	
	for(int i = 0; i < 19; i++){
		ajouter_animal(rand() % SIZE_X, rand() % SIZE_Y, 10, &liste_proie);
		ajouter_animal(rand() % SIZE_X, rand() % SIZE_Y, 10, &liste_predateur);
	}

	printf("le nombre de proies est :%d \n",compte_animal_rec(liste_proie));
        printf("le nombre de predateurs est :%d \n",compte_animal_rec(liste_predateur));
        
        

//------TME2 - QST 7---------------------//
//--------Tester la fonction "enlever_animal------------------"//

    printf("\n le nombre de predateurs avant d'ajouter un predateur : %d \n",compte_animal_rec(liste_predateur));;
    Animal *pre = creer_animal(2,30,10);
    liste_predateur=ajouter_en_tete_animal(liste_predateur,pre);
    printf("le nombre de predateurs  apres avoir rajouter un predateur est  :%d \n",compte_animal_rec(liste_predateur));
    enlever_animal(&liste_predateur,pre);
    printf("le nombre de predateurs  apres l'utilisation de  la fonction 'enlever_animal' est :%d \n",compte_animal_rec(liste_predateur));
    printf("\n");

   

    /*---------TME 03-----------------*/

    //-------qst 01 ------//

    // tester les deux fonctions :ecrire_ecosys() et lire_ecosys() 
	

	Animal *liste_proie_test_lire = NULL;
	Animal *liste_predateur_test_lire = NULL;
	ecrire_ecosys("liste_ecosys.txt", liste_proie, liste_predateur);
	lire_ecosys("liste_ecosys.txt", &liste_proie_test_lire, &liste_predateur_test_lire);


	afficher_ecosys(liste_proie_test_lire, liste_predateur_test_lire); printf("\n");


	Animal *tempProie = liste_proie_test_lire;
	printf("Proies :\n");
    while (tempProie) {
  		printf("%d, %d, %f\n", tempProie->x, tempProie->y, tempProie->energie);
  		tempProie = tempProie->suivant;
    }
  
	Animal *tempPredateur = liste_predateur_test_lire;
  	printf("\nPrédateurs :\n");
  	while (tempPredateur) {
  		printf("%d, %d, %f\n", tempPredateur->x, tempPredateur->y, tempPredateur->energie);
  		tempPredateur = tempPredateur->suivant;
    }
    
   

	liste_proie = liberer_liste_animaux(liste_proie);
	liste_predateur = liberer_liste_animaux(liste_predateur);
	liste_proie_test_lire = liberer_liste_animaux(liste_proie_test_lire);
	liste_predateur_test_lire = liberer_liste_animaux(liste_predateur_test_lire);

	
	return 0;
}
