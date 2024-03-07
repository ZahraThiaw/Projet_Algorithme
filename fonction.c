#include <stdio.h>
#include <stdlib.h>
#include "fonction.h"
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <termios.h>



int connexionUtiliser() {
    char username[50];
    printf("Entrez votre nom d'utilisateur : ");
    scanf("%s", username);
    //char *motDePasse = getpass("Entrez votre mot de passe : ");
    char password[50];
    int i = 0;
    char ch;
    getchar();
    printf("Entrez votre mot de passe : ");
    struct termios old_term, new_term;
    tcgetattr(STDIN_FILENO, &old_term);  // sauvegarde des paramètres actuels du terminal
    new_term = old_term;
    new_term.c_lflag &= ~(ECHO | ECHOE | ECHOK | ECHONL | ICANON);  // désactive l'écho des caractères saisis et le mode canonique
    tcsetattr(STDIN_FILENO, TCSANOW, &new_term);  // applique les nouveaux paramètres du terminal
    while (1) {
        ch = getchar();
        if (ch == 10 && strlen(password) != 0) {  // 10 is the ASCII code for Enter
            break;
        } else if (ch == 127) {  // 127 is the ASCII code for Backspace
            if (i > 0) {
                i--;
                printf("\b \b");  // efface le caractère de la console
            }
        } else if (ch != 10) {
            password[i] = ch;
            i++;
            printf("*");  // affiche un astérisque à la place du caractère réel
        }
    }
    password[i] = '\0';  // Ajoute un caractère nul à la fin du mot de passe
    tcsetattr(STDIN_FILENO, TCSANOW, &old_term);  // restaure les paramètres du terminal d'origine
    printf("\n");
    return validerUtilisateur("utilisateurs.txt", username, password);
}
int validerUtilisateur(const char* nomFichier, const char* username, const char* motDePasse) {
    FILE *fichier;
    Utilisateur utilisateur;
    fichier = fopen(nomFichier, "r");

    if (fichier) {
        while (fscanf(fichier, "%s %s %s %s %d", utilisateur.nom, utilisateur.prenom, utilisateur.username,
                      utilisateur.motDePasse, &utilisateur.type) == 5) {
            if (strcmp(utilisateur.username, username) == 0 && strcmp(utilisateur.motDePasse, motDePasse) == 0) {
                fclose(fichier);
                return utilisateur.type; // Utilisateur valide
            }
        }
        fclose(fichier);
    } else {
        printf("Impossible d'ouvrir le fichier\n");
    }
    return 0; // Utilisateur non trouvé ou mot de passe incorrect
}
void dateAujourdhui(char* date) {
    time_t maintenant;
    struct tm* infoTemps;
    char buffer[80];
    time(&maintenant);
    infoTemps = localtime(&maintenant);
    strftime(buffer, 80, "%d/%m/%Y %H:%M:%S", infoTemps); // Ajoutez %H:%M:%S pour l'heure
    sprintf(date, "%s", buffer);
}
int presenceDejaAjoutee(const char* nomFichier, int matricule, Date date_presence) {
    FILE* fichier = fopen(nomFichier, "r");
    if (fichier != NULL) {
        presence p;
        while (fscanf(fichier, "%d %d %d %d", &p.matricule, &p.date.jour, &p.date.mois, &p.date.annee) == 4) {
            if (p.matricule == matricule && p.date.jour == date_presence.jour && p.date.mois == date_presence.mois && p.date.annee == date_presence.annee) {
                fclose(fichier);
                return 1; // La présence a déjà été ajoutée
            }
        }
        fclose(fichier);
    }
    return 0; // La présence n'a pas encore été ajoutée
}
void ajoutpresent(const char* nomFichier, int matricule, int present) {
    FILE* fichier = fopen(nomFichier, "a");
    if (fichier != NULL) {
        presence p;
        p.matricule = matricule;
        p.present = present;
        char date[21];
        dateAujourdhui(date);
        p.date.jour = (date[0] - '0') * 10 + (date[1] - '0');
        p.date.mois = (date[3] - '0') * 10 + (date[4] - '0');
        p.date.annee = (date[6] - '0') * 1000 + (date[7] - '0') * 100 + (date[8] - '0') * 10 + (date[9] - '0');
        p.date.heure = (date[11] - '0') * 10 + (date[12] - '0');
        p.date.minute = (date[14] - '0') * 10 + (date[15] - '0');
        p.date.seconde = (date[17] - '0') * 10 + (date[18] - '0');

        if (!presenceDejaAjoutee(nomFichier, matricule, p.date)) {
            fprintf(fichier, "%d %d %d %d %d %d %d %d\n", p.matricule, p.date.jour, p.date.mois, p.date.annee, p.date.heure, p.date.minute, p.date.seconde, p.present);
            printf("Matricule valide. Presence à : %d:%d:%d\n", p.date.heure, p.date.minute, p.date.seconde);
        } else {
            printf("Presence déjà ajoutée\n");
        }
        fclose(fichier);
    }
}
int checkPassword(const char* nomFichier, const char* username, const char* motDePasse) {
    char input[20];
    printf("Entrez votre mot de passe : ");
    scanf("%s", input);
    
    FILE *fichier;
    Utilisateur utilisateur;
    fichier = fopen(nomFichier, "r");

    if (fichier) {
        while (fscanf(fichier, "%s %s %s %s %d", utilisateur.nom, utilisateur.prenom, utilisateur.username,
                      utilisateur.motDePasse, &utilisateur.type) == 5) {
            if (strcmp(utilisateur.username, username) == 0 && strcmp(utilisateur.motDePasse, motDePasse) == 0) {
                fclose(fichier);
                return utilisateur.type; // Utilisateur valide
            }
        }
        fclose(fichier);
    } else {
        printf("Impossible d'ouvrir le fichier\n");
    }
    return 0;
}

void marquerPresences() {
    char username[50];
    char motDePasse[50];
    int matriculeSaisi;
    while (1) {
        printf("Entrez le matricule de l'apprenant (ou 'Q' pour quitter) : ");
        char input[20];
        scanf("%s", input);
        if (strcmp(input, "Q") == 0 || strcmp(input, "q") == 0) {
            printf("Vous avez choisi de quitter. Entrez votre mot de passe pour revenir au menu précédent : ");
            if (!checkPassword("utilisateurs.txt", "admin", "admin123")) {
                printf("Mot de passe invalide. Reconnectez-vous.\n");
                marquerPresences();
            }
            break;
        } else {
            matriculeSaisi = atoi(input);
            if (matriculeValide(matriculeSaisi, "etudiants.txt")) {
                ajoutpresent("presence.txt", matriculeSaisi, 1); // appel de la fonction ajoutpresent(const char* nomFichier, int matricule, int present)
            } else {
                printf("Matricule non valide. Veuillez réessayer.\n");
            }
        }
        printf("Appuyez sur entrée pour continuer...\n");
        fflush(stdin);
        getchar(); 
        getchar(); // Attendre que l'utilisateur appuie sur n'importe quelle touche
    }
}
// Fonction pour vérifier si un matricule est présent dans un fichier
int matriculeValide(int matricule, const char* nomFichier) {
    FILE* fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return 0;
    }
    Etudiant etudiant;
    while (fscanf(fichier, "%d %s", &etudiant.matricule, etudiant.nom) == 2) {
        if (etudiant.matricule == matricule) {
            fclose(fichier);
            return 1; // Le matricule est présent dans le fichier
        }
    }
    fclose(fichier);
    return 0; // Le matricule n'est pas présent dans le fichier
}