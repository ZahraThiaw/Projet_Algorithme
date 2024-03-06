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
// Structure représentant un étudiant
typedef struct {
    int matricule;
    char nom[50];
    int present;
} Etudiant;
// Structure représentant une classe
typedef struct {
    char nom[50];
    Etudiant etudiants[30]; // Liste des étudiants
    int nombreEtudiants;
} Classe;
typedef struct {
    int jour;
    int mois;
    int annee;
} Date;
typedef struct {
    int matricule;
    Date date;
    int present;
} presence;
void dateAujourdhui(char* date);
void ajoutpresent(const char* nomFichier, int matricule, int present);
#endif