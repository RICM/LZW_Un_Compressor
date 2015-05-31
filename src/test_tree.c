#include <stdio.h>
#include <stdlib.h>

#include "tree.h"

int main (int argc, char **argv){

	/*
		on veut créer l'arbre suivant :

		(79|259) - (83|261) - (84|260)
		   |
		(82|262) - (83|263)

		qui définit le code des séquences suivantes :
		79 = 259 ; 
		82 = 262 ;
		79 83 = 261 ;
		79 84 = 260 ;
		82 83 = 263 ;

	*/

	/*
		On commence par créer t :
		(79|259)
	*/
	pTree t = createTree(79, 259, NULL, NULL);

	/*
		On ajoute (84|260) à droite de cet arbre
		t vaut :
		(79|259) - (84|260)
	*/
	pTree insert = insertRight(84, 260, &t);

	printf("Affichage de l'arbre a inserer a droite : \n");
	print_tree(insert, 0);

	printf("\nAffichage de l'arbre t : \n");
	print_tree(t, 0);	

	/*
		On ajoute à droite du noeud pointé par t, (83|261) en conservant ce qu'il y a à droite
		t vaut :
		(79|259) - (83|261) - (84|260)
	*/
	insert = insertRight(83, 261, &t);
	printf("\nAffichage de l'arbre a inserer a droite : \n");
	print_tree(insert, 0);

	printf("\nAffichage de l'arbre t : \n");
	print_tree(t, 0);

	/*
		On insert à gauche du noeud pointé par t, (82|262) en conservant ce qu'il y a à gauche
		t vaut :
		(79|259) - (83|261) - (84|260)
		   |
		(82|262)
	*/
	insert = insertLeft(82, 262, &t);
	printf("\nAffichage de l'arbre a inserer a gauche : \n");
	print_tree(insert, 0);

	printf("\nAffichage de l'arbre t : \n");
	print_tree(t, 0);

	/*
		On insert à droite du noeud précédement inséré, (83|263)
		t vaut :
		(79|259) - (83|261) - (84|260)
		   |
		(82|262) - (83|263)
	*/
	insert = insertRight(83, 263, &insert);
	printf("\nAffichage de l'arbre a inserer a droite du precedent : \n");
	print_tree(insert, 0);

	printf("\nAffichage de l'arbre t : \n");
	print_tree(t, 0);

	freeTree(&t);

	printf("Desallocation memoire de t : %s\n", (t == NULL)? "reussie" : "echec");
	return 0;
}