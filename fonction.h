#ifndef FONCTION_H
#define FONCTION_H

// Structure pour représenter un utilisateur
typedef struct Utilisateur {
    int type;
    char nom[50];
    char prenom[50];
    char username[50];
    char motDePasse[50];
}Utilisateur;
char* connexionUtiliser(char *password);
int validerUtilisateur(const char* nomFichier, const char* fichierEtudiant, const char* username, const char* motDePasse);
// Structure représentant un étudiant
typedef struct {
    int type;
    int matricule;
    char classe [15];
    char prenom[50];
    char nom[50];
    char username[50];
    char motDePasse[50];
    int present;
} Etudiant;
// Structure représentant une classe
typedef struct {
    char nom[50];
    Etudiant etudiants[30]; // Liste des étudiants
    int nombreEtudiants;
}Classe;
typedef struct {
    int jour;
    int mois;
    int annee;
    int heure;
    int minute;
    int seconde;
} Date;
typedef struct {
    Etudiant etudiant;
    Date date;
    int present;
} presence;
void dateAujourdhui(char* date);
Etudiant recupererEtudiant(int matricule);
int presenceDejaAjoutee(int matricule, Date date_presence);
void ajoutpresent(const char* nomFichier, int matricule, int present);
int checkPassword(const char* nomFichier, const char* username, const char* motDePasse);
void marquerPresences();
int matriculeValide(int matricule, const char* nomFichier);
int getMatriculeFromUsername(const char* fichierEtudiant, const char* username);
void enregistrerDate(Date date);
int dateexiste(Date date);
void afficherTous();
void afficherParDate(Date d,char *nomFichier);
int estBissextile(int annee);
int estDateValide(int jour, int mois, int annee);
Date verifieDate();
void afficherAuneDate(Date d);
void copyfile(char *nomFichier1, char *nomFichier2);
typedef struct {
    char source[20];
    int matricule;
    char nom[20];
    char prenom[20];
    char message[100];
    Date date;
    int etat;
} Message;
void envoieMsg(int matricule, char *message);
void Messageaapprenant();
void messageaTous();
void lesmatricules(int tab[100],int *nb);
void messageClasse(char *classe);
void listClasse(int tab[100],int *nb,char *classe);
void lireMessage(int matricule);
void nbreMessages(int mat,int *nb);
void modifierEtatMessage(int matricule);
#endif