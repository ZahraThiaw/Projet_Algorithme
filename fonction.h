#ifndef FONCTION_H
#define FONCTION_H

// Structure pour représenter un utilisateur
typedef struct Utilisateur {
    char nom[50];
    char prenom[50];
    char username[50];
    char motDePasse[50];
    int type;
}Utilisateur;
int connexionUtiliser();
int validerUtilisateur(const char* nomFichier, const char* username, const char* motDePasse);
#endif