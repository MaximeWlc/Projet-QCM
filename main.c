/*
 * Fichier : main.c
 * Auteurs : Maxime, Loic
 * Description : Point d'entree du programme "Questions pour un Tekien".
 * Gere la boucle du menu principal et la navigation entre les differents modes.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "qcm.h"

int main() {
    int choix;

    /* * Initialisation du generateur de hasard en utilisant l'heure du systeme.
     * Sans cette ligne, la fonction rand() utiliserait la meme graine par defaut 
     * a chaque execution, ce qui genererait un melange des questions 
     * strictement identique a chaque lancement du logiciel.
     */
    srand(time(NULL));
    srand(time(NULL));

    do {
        /* Affichage de l'interface principale */
        printf("\n=== LOGICIEL QCM CY TECH ===\n");
        printf("1. Mode Etudiant\n");
        printf("2. Mode Enseignant\n");
        printf("3. Quitter\n");
        printf("Votre choix : ");

        /* * Saisie securisee : 
         * Si scanf ne reussit pas a lire un entier (ex: l'utilisateur tape une lettre), 
         * on nettoie le buffer clavier pour eviter une boucle infinie.
         */
        
        if (scanf("%d", &choix) != 1) {
            vider_buffer();
            continue;
        }

        /* Redirection vers les fonctions du fichier qcm.c selon le choix */

        switch(choix) {
            case 1: mode_etudiant(); break;
            case 2: mode_enseignant(); break;
            case 3: break;
        }
    } while (choix != 3);

    return 0;
}
