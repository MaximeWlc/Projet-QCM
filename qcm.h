/*
 * Description : Fichier d'en-tete contenant les definitions de constantes,
 * les structures de donnees principales (Question et QCM)
 * des fonctions utilisees dans le logiciel "Questions pour un Tekien".
 */

/* Gardiens d'inclusion pour eviter les erreurs de redefinition si le fichier est inclus plusieurs fois */
#ifndef QCM_H
#define QCM_H

#define PASS_PROF "cytech2026"

/*
 * Structure representant une question individuelle du QCM.
 * Contient l'enonce, les 4 propositions de reponse et la ou les bonnes reponses attendues.
 */

typedef struct {
    char intitule[500];
    char propA[200];
    char propB[200];
    char propC[200];
    char propD[200];
    char bonnes_reponses[5]; 
} Question;

/*
 * Structure representant un QCM complet.
 * Regroupe les parametres de jeu (points negatifs, choix multiples, mode sequentiel)
 * et un tableau de 10 questions pretes a etre posees.
 */

typedef struct {
    char titre[100];
    int points_negatifs; 
    int choix_multiple;  
    int mode_sequentiel; 
    Question questions[10];
} QCM;

/* Prototypes des fonctions */

/* Vide le buffer d'entree clavier pour eviter les boucles infinies lors de saisies invalides */
void vider_buffer();
void sauvegarder_qcm(QCM q);
int charger_qcm(char *nom_qcm, QCM *q);
void melanger_questions(Question questions[], int taille);
void poser_question(Question q, QCM qcm_actuel, float *score, char *reponse_utilisateur);
void lancer_quizz(QCM mon_qcm);
void creer_qcm();
void mode_etudiant();
void mode_enseignant();

#endif
