#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "qcm.h"

/* Vide le buffer se saisie standard pour eviter les boucles infinies suite à de mauvaises entrées */
void vider_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

/* Sauvegarde les donnees d'une structure QCM dans un fichier texte portant le nom du titre */
void sauvegarder_qcm(QCM q) {
    char nom_f[110];
    int i;
    sprintf(nom_f, "%s.txt", q.titre);
    FILE *f = fopen(nom_f, "w");
    if (f == NULL) {
        printf("Erreur lors de la creation du fichier.\n");
        return;
    }

    fprintf(f, "%s\n%d\n%d\n%d\n", q.titre, q.points_negatifs, q.choix_multiple, q.mode_sequentiel);
    for (i = 0; i < 10; i++) {
        fprintf(f, "%s\n%s\n%s\n%s\n%s\n%s\n", 
                q.questions[i].intitule, q.questions[i].propA, q.questions[i].propB, 
                q.questions[i].propC, q.questions[i].propD, q.questions[i].bonnes_reponses);
    }
    fclose(f);
}
/* Charge un QCM depuis un fichier texte dans la structure. Retourne 1 en cas de succes, 0 si le fichier est introuvable */
int charger_qcm(char *nom_qcm, QCM *q) {
    char nom_f[110];
    int i;
    sprintf(nom_f, "%s.txt", nom_qcm);
    FILE *f = fopen(nom_f, "r");
    if (f == NULL) return 0;

    fscanf(f, " %[^\n]\n%d\n%d\n%d\n", q->titre, &q->points_negatifs, &q->choix_multiple, &q->mode_sequentiel);
    for (i = 0; i < 10; i++) {
        fscanf(f, " %[^\n]\n", q->questions[i].intitule);
        fscanf(f, " %[^\n]\n", q->questions[i].propA);
        fscanf(f, " %[^\n]\n", q->questions[i].propB);
        fscanf(f, " %[^\n]\n", q->questions[i].propC);
        fscanf(f, " %[^\n]\n", q->questions[i].propD);
        fscanf(f, " %s\n", q->questions[i].bonnes_reponses);
    }
    fclose(f);
    return 1;
}
/* Melange l'ordre des questions dans le tableau pour rendre l'ordre aleatoire a chaque execution */
void melanger_questions(Question questions[], int taille) {
    int i, j;
    Question temp;
    for (i = taille - 1; i > 0; i--) {
        j = rand() % (i + 1);
        temp = questions[i];
        questions[i] = questions[j];
        questions[j] = temp;
    }
}
/* Affiche l'enonce et les propositions, recupere le choix du joueur et met a jour le score selon les regles du QCM */
void poser_question(Question q, QCM qcm_actuel, float *score, char *reponse_utilisateur) {
    char choix[10];
    int saisie_ok = 0;

    printf("\n%s\n", q.intitule);
    printf("a) %s\n", q.propA);
    printf("b) %s\n", q.propB);
    printf("c) %s\n", q.propC);
    printf("d) %s\n", q.propD);

    if (qcm_actuel.mode_sequentiel == 0) {
        printf("0) Passer la question\n");
    }

    while (!saisie_ok) {
        printf("Votre choix : ");
        if (scanf(" %9s", choix) != 1) {
            vider_buffer();
            continue;
        }

        if (strcmp(choix, "0") == 0) {
            if (qcm_actuel.mode_sequentiel == 1) {
                printf("Erreur : Le mode sequentiel t'oblige a repondre.\n");
            } else {
                saisie_ok = 1;
            }
        } else {
            saisie_ok = 1;
        }
    }

    strcpy(reponse_utilisateur, choix);

    if (strcmp(choix, q.bonnes_reponses) == 0) {
        *score += 2.0;
    } else if (strcmp(choix, "0") != 0 && qcm_actuel.points_negatifs == 1) {
        *score -= 1.0;
    }
}
/* Gere le deroulement d'un test complet : pose les 10 questions, calcule la note sur 20 et affiche le corrige */
void lancer_quizz(QCM mon_qcm) {
    float score = 0.0;
    char reponses_joueur[10][10];
    int i;

    melanger_questions(mon_qcm.questions, 10);
    printf("\n--- DEBUT DU QCM : %s ---\n", mon_qcm.titre);

    for (i = 0; i < 10; i++) {
        printf("\nQuestion %d/10 :", i + 1);
        poser_question(mon_qcm.questions[i], mon_qcm, &score, reponses_joueur[i]);
    }

    if (score < 0.0) score = 0.0;
    
    printf("\n--- RESULTATS ---\n");
    printf("Votre score final est : %.2f / 20.00\n\n", score);

    printf("--- CORRIGE ---\n");
    for (i = 0; i < 10; i++) {
        printf("Q%d : ", i + 1);
        if (strcmp(reponses_joueur[i], mon_qcm.questions[i].bonnes_reponses) == 0) {
            printf("Correct (%s)\n", mon_qcm.questions[i].bonnes_reponses);
        } else if (strcmp(reponses_joueur[i], "0") == 0) {
            printf("Passee (Bonne reponse : %s)\n", mon_qcm.questions[i].bonnes_reponses);
        } else {
            printf("Faux (Reponse donnee : %s, attendue : %s)\n", reponses_joueur[i], mon_qcm.questions[i].bonnes_reponses);
        }
    }
}
/* Interface de saisie permettant a l'enseignant de creer un nouveau QCM, definir ses regles et ses 10 questions */
void creer_qcm() {
    QCM n;
    int i;
    printf("\nNom du QCM (sans espace) : ");
    scanf("%s", n.titre);

    printf("Points negatifs (1=Oui, 0=Non) : "); scanf("%d", &n.points_negatifs);
    printf("Choix multiples (1=Oui, 0=Non) : "); scanf("%d", &n.choix_multiple);
    printf("Mode sequentiel (1=Oui, 0=Non) : "); scanf("%d", &n.mode_sequentiel);

    for (i = 0; i < 10; i++) {
        printf("\nQ%d Enonce : ", i+1);
        scanf(" %[^\n]", n.questions[i].intitule);
        printf("Prop a : "); scanf(" %[^\n]", n.questions[i].propA);
        printf("Prop b : "); scanf(" %[^\n]", n.questions[i].propB);
        printf("Prop c : "); scanf(" %[^\n]", n.questions[i].propC);
        printf("Prop d : "); scanf(" %[^\n]", n.questions[i].propD);
        printf("Bonne(s) reponse(s) (ex: a ou ab) : "); scanf("%s", n.questions[i].bonnes_reponses);
    }
    
    sauvegarder_qcm(n);
    printf("QCM %s enregistre avec succes.\n", n.titre);
    /* Ajout du nouveau QCM dans le fichier index */
    FILE *f_liste = fopen("liste_qcm.txt", "a");
    if (f_liste != NULL) {
        fprintf(f_liste, "%s\n", n.titre);
        fclose(f_liste);
    }
}
/* Menu de l'etudiant : lit le fichier d'index pour afficher les QCM disponibles et permet d'en charger un */
void mode_etudiant() {
    char nom[100];
    char nom_lu[100];
    QCM q;
    FILE *f_liste;

    printf("\n--- ESPACE ETUDIANT ---\n");
    printf("QCM disponibles sur le serveur :\n");

    /* Lecture du fichier index pour afficher la liste */
    f_liste = fopen("liste_qcm.txt", "r");
    if (f_liste != NULL) {
        while (fscanf(f_liste, "%s", nom_lu) == 1) {
            printf("- %s\n", nom_lu);
        }
        fclose(f_liste);
    } else {
        printf("- (Aucun QCM trouve ou fichier index manquant)\n");
    }
    printf("------------------------------\n");

    printf("Nom du QCM a charger (sans l'extension .txt) : ");
    scanf("%s", nom);

    if (charger_qcm(nom, &q)) {
        lancer_quizz(q);
    } else {
        printf("Erreur : Le fichier %s.txt est introuvable.\n", nom);
    }
}
/* Menu securise de l'enseignant : verifie le mot de passe avant d'autoriser la creation de nouveaux QCM */
void mode_enseignant() {
    char pass[50];
    int choix;

    printf("\nMot de passe : ");
    scanf("%s", pass);
    if (strcmp(pass, PASS_PROF) != 0) {
        printf("Acces refuse.\n");
        return;
    }

    do {
        printf("\n--- MENU ENSEIGNANT ---\n");
        printf("1. Creer un nouveau QCM\n");
        printf("2. Retour\nChoix : ");
        if (scanf("%d", &choix) != 1) {
            vider_buffer();
            continue;
        }

        if (choix == 1) creer_qcm();
    } while (choix != 2);
}
