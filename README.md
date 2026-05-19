Le projet QCM a été développé en langage C. Il permet la création, la gestion des fichiers de sauvegarde, ainsi que l'exécution de QCM.

Fichiers du projet

- main.c : Point d'entrée contenant la boucle principale et le menu.
- qcm.c : Implémentation des fonctionnalités (lecture/écriture fichiers, algorithme du QCM).
- qcm.h : Structures de données et prototypes des fonctions.
- Makefile : Fichier de configuration automatisant la compilation du projet.
- Fichiers.txt : Fichiers de sauvegarde générés par le programme contenant les questions et les listes de QCM (ex: Algorithmique.txt, liste_qcm.txt).

Le projet inclut un `Makefile` afin de compiler tout d'un coup. Il faudra rajouter le ./



[[[[Il y a marqué ::; Un readme : fichier texte indiquant les commandes 
et les options pour compiler et faire fonctionner le 
projet correctement.]]]]



# Projet : Questions pour un Tekien (Logiciel de QCM)

Ce projet est une application de QCM interactive développée en C. Elle permet aux étudiants de passer des tests thématiques et aux enseignants de créer de nouveaux questionnaires sécurisés par mot de passe.

---

## 1. Options de Compilation (Makefile)

Le projet utilise un `Makefile` pour automatiser la génération de l'exécutable. Les options de compilation incluses garantissent la sécurité et la conformité du code :

* **`gcc`** : Le compilateur standard utilisé.
* **`-Wall`** : Active la quasi-totalité des avertissements du compilateur pour détecter les erreurs de logique ou de syntaxe.
* **`-Wextra`** : Active des avertissements complémentaires pour renforcer la rigueur du code.

---

## 2. Commandes de Compilation

Pour compiler et gérer les fichiers du projet, exécutez les commandes suivantes dans votre terminal :

### Compiler le projet
Génère l'exécutable `ProjetInfo` à partir des fichiers sources (`main.c`, `qcm.c`) et de l'en-tête (`qcm.h`).
```bash
make

Fonctionnalités de l'application

    Mode Étudiant :

Lit automatiquement le fichier d'index liste_qcm.txt pour afficher les questionnaires disponibles sur le serveur.
Permet de charger un QCM (ex: Programmation_C ou Algorithmique) sans taper l'extension .txt.

        Gère le score en direct sur 20 points, prend en compte les points négatifs si l'option est active, et affiche un corrigé complet à la fin du test.

    Mode Enseignant :

        Sécurisé par le mot de passe global défini dans l'en-tête : cytech2026.

        Permet de configurer interactivement les règles d'un nouveau quiz (activation des points négatifs, du choix multiple ou du mode séquentiel).

        Guide l'enseignant pour écrire un bloc strict de 10 questions.

        Enregistre automatiquement le questionnaire au format texte brut et met à jour le fichier d'index liste_qcm.txt.

