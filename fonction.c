#include <stdio.h>
#include <stdlib.h>
#include "fonction.h"
#include <string.h>
#include <unistd.h>
#include <time.h>


int connexionUtiliser() {
    char username[50];
    printf("Entrez votre nom d'utilisateur : ");
    scanf("%s", username);

    char *motDePasse = getpass("Entrez votre mot de passe : ");
    return validerUtilisateur("utilisateurs.txt", username, motDePasse);
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

    strftime(buffer, 80, "%d/%m/%Y", infoTemps);
    sprintf(date, "%s", buffer);
}
void ajoutpresent(const char* nomFichier, int matricule, int present) {
    FILE* fichier = fopen(nomFichier, "a");
    if (fichier != NULL) {
        presence p, p1;
        p.matricule = matricule;
        p.present = present;
        char date[11];
        dateAujourdhui(date);
        p.date.jour = (date[0] - '0') * 10 + (date[1] - '0');
        p.date.mois = (date[3] - '0') * 10 + (date[4] - '0');
        p.date.annee = (date[6] - '0') * 1000 + (date[7] - '0') * 100 + (date[8] - '0') * 10 + (date[9] - '0');

        int presenceDejaAjoutee = 0;
        // Vérifier si la_presence est déjà ajoutée dans le fichier
        while (fscanf(fichier, "%d %d %d %d %d", &p1.matricule, &p1.date.jour, &p1.date.mois, &p1.date.annee, &p1.present) == 4) {
        if (p1.matricule == p.matricule && p1.date.jour == p.date.jour && p1.date.mois == p.date.mois && p1.date.annee == p.date.annee) {
            printf("Presence déjà ajoutée\n");
            presenceDejaAjoutee = 1;
            break;
        }
        }
        if (!presenceDejaAjoutee) {
        fprintf(fichier, "%d %d %d %d\n", p.matricule, p.date.jour, p.date.mois, p.date.annee);
        printf("Presence ajoutée avec succès\n");
        }
        fclose(fichier);
    }
}