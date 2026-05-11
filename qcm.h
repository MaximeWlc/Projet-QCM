#ifndef QCM_H
#define QCM_H

#define PASS_PROF "cytech2026"

typedef struct {
    char intitule[500];
    char propA[200];
    char propB[200];
    char propC[200];
    char propD[200];
    char bonnes_reponses[5]; 
} Question;

typedef struct {
    char titre[100];
    int points_negatifs; 
    int choix_multiple;  
    int mode_sequentiel; 
    Question questions[10];
} QCM;

/* Prototypes des fonctions */
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
