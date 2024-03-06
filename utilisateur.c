#include <stdio.h>
#include <stdlib.h>
#include "fonction.h"
#include <string.h>
#include <time.h>


int main() {
   // afficherListeUtilisateurs("utilisateurs.txt");
    int nombreUtilisateurs=2;
     // Supposons que vous ayez une liste prédéfinie d'utilisateurs avec leurs informations
    Utilisateur utilisateur[] = {
        {"Admin", "Admin", "admin", "admin123", 1},
        {"Fatimata", "Thiaw", "Zahra", "2024", 2},
    };
    char date[10];
                dateAujourdhui(date);
                printf("Date du jour : %s\n", date);
    char username[50];
    char motDePasse[50];
    int typeUtilisateur;
    do {
        typeUtilisateur = connexionUtiliser();
        if (typeUtilisateur == 1) {
            int choix = 0;
            do
            {
                puts("***************Menu Admin***************");
                puts("      1. GESTION DES ETUDIANTS");
                puts("      2. GENERATION DE FICHIERS");
                puts("      3. MARQUER LES PRESENCES");
                puts("      4. ENVOYER UN MESSAGE");
                puts("      5. QUITTER");
                puts("****************************************");
            } while (choix != 5);

        } else if (typeUtilisateur == 2) {
            int choix = 0;
            puts("***************Menu Apprenant***************");
            puts("      1. MARQUER MA PRÉSENCE");
            puts("      2. NOMBRE DE MINUTES D’ABSENCE");
            puts("      3. MES MESSAGES (0)");
            puts("      4. QUITTER");
            puts("****************************************");
        }
    } while (typeUtilisateur != 1 && typeUtilisateur != 2);
    return 0;
}