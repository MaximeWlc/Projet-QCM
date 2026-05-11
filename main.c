#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "qcm.h"

int main() {
    int choix;
    srand(time(NULL));

    do {
        printf("\n=== LOGICIEL QCM CY TECH ===\n");
        printf("1. Mode Etudiant\n");
        printf("2. Mode Enseignant\n");
        printf("3. Quitter\n");
        printf("Votre choix : ");
        
        if (scanf("%d", &choix) != 1) {
            vider_buffer();
            continue;
        }

        switch(choix) {
            case 1: mode_etudiant(); break;
            case 2: mode_enseignant(); break;
            case 3: break;
        }
    } while (choix != 3);

    return 0;
}
