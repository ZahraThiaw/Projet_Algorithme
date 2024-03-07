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
    int heure;
    int minute;
    int seconde;
} Date;
typedef struct {
    int matricule;
    Date date;
    int present;
} presence;
void dateAujourdhui(char* date);
int presenceDejaAjoutee(const char* nomFichier, int matricule, Date date_presence);
void ajoutpresent(const char* nomFichier, int matricule, int present);
int checkPassword(const char* nomFichier, const char* username, const char* motDePasse);
void marquerPresences();
int matriculeValide(int matricule, const char* nomFichier);
#endif