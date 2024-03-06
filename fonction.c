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
