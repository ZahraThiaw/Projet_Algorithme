#include <stdio.h>
#include <stdlib.h>
#include "fonction.h"
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <termios.h>



char* connexionUtiliser(char *password) {
    static char username[50];
    printf("Entrez votre nom d'utilisateur : ");
    scanf("%s", username);
    //char *motDePasse = getpass("Entrez votre mot de passe : ");
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
    return username;
}
int validerUtilisateur(const char* nomFichier, const char* fichierEtudiant, const char* username, const char* motDePasseSaisi) {
    FILE *fichier;
    Utilisateur utilisateur;
    fichier = fopen(nomFichier, "r");
    if (fichier) {
        while (fscanf(fichier, "%d %s %s %s %s", &utilisateur.type, utilisateur.nom, utilisateur.prenom, utilisateur.username,
                      utilisateur.motDePasse) == 5) {
            if (strcmp(utilisateur.username, username) == 0 && strcmp(utilisateur.motDePasse, motDePasseSaisi) == 0) {
                fclose(fichier);
                return utilisateur.type; // Utilisateur valide
            }
        }
        fclose(fichier);
    } else {
        printf("Impossible d'ouvrir le fichier\n");
    }

    Etudiant etudiant;
    fichier = fopen(fichierEtudiant, "r");
    if (fichier) {
        while (fscanf(fichier, "%d %d %s %s %s %s %s", &etudiant.type, &etudiant.matricule, etudiant.classe, etudiant.nom, etudiant.prenom, etudiant.username,
                      etudiant.motDePasse) == 7) {
            if (strcmp(etudiant.username, username) == 0 && strcmp(etudiant.motDePasse, motDePasseSaisi) == 0) {
                fclose(fichier);
                return etudiant.type; // Utilisateur valide
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
Etudiant recupererEtudiant(int matricule){
    FILE *fichier = fopen("etudiants.txt","r");
    if(fichier != NULL) {
        Etudiant etudiant;
        while(fscanf(fichier,"%d %d %s %s %s %s %s",&etudiant.type, &etudiant.matricule, etudiant.classe, etudiant.prenom, etudiant.nom, etudiant.username, etudiant.motDePasse) != EOF) {
           // printf("%d\n", etudiant.matricule);
            if(etudiant.matricule == matricule){
                // printf("%d %s %s ",etudiant.matricule,etudiant.prenom,etudiant.nom);
             return etudiant;
             break;
            }
           
        }
    }
}
int presenceDejaAjoutee(int matricule, Date date_presence) {
    FILE* fichier = fopen("presence.txt", "r");
    if (fichier != NULL) {
        Etudiant etudiant;
        Etudiant e=recupererEtudiant(matricule);
        presence p;
        while (fscanf(fichier, "%d %s %s %s %d %d %d %d %d %d %d\n",&p.etudiant.matricule,e.classe,e.nom,e.prenom,&p.date.jour,&p.date.mois,&p.date.annee,&p.date.heure,&p.date.minute,&p.date.seconde,&p.present) == 11) {
            if (p.etudiant.matricule == matricule && p.date.jour == date_presence.jour && p.date.mois == date_presence.mois && p.date.annee == date_presence.annee) {
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
        Etudiant etudiant;
        Etudiant e=recupererEtudiant(matricule);
        presence p;
        p.etudiant.matricule = matricule;
        p.present = present;
        char date[21];
        dateAujourdhui(date);
        p.date.jour = (date[0] - '0') * 10 + (date[1] - '0');
        p.date.mois = (date[3] - '0') * 10 + (date[4] - '0');
        p.date.annee = (date[6] - '0') * 1000 + (date[7] - '0') * 100 + (date[8] - '0') * 10 + (date[9] - '0');
        p.date.heure = (date[11] - '0') * 10 + (date[12] - '0');
        p.date.minute = (date[14] - '0') * 10 + (date[15] - '0');
        p.date.seconde = (date[17] - '0') * 10 + (date[18] - '0');

        if (!presenceDejaAjoutee(matricule, p.date)) {
            fprintf(fichier, "%d %s %s %s %d/%d/%d %d:%d:%d %d\n",p.etudiant.matricule,e.classe,e.nom,e.prenom,p.date.jour,p.date.mois,p.date.annee,p.date.heure,p.date.minute,p.date.seconde,p.present);
            printf("\xE2\x9C\x85 Matricule valide. Presence à : %d:%d:%d\n", p.date.heure, p.date.minute, p.date.seconde);
            enregistrerDate(p.date);
        } else {
            printf("Presence déjà ajoutée\n");
        }
        fclose(fichier);
    }
}
int checkPassword(const char* nomFichier, const char* username, const char* motDePasse) {
    //char input[20];
    char password[50];
    int i = 0;
    char ch;
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
    
    FILE *fichier;
    Utilisateur utilisateur;
    fichier = fopen(nomFichier, "r");
    if (fichier) {
        while (fscanf(fichier, "%d %s %s %s %s", &utilisateur.type, utilisateur.nom, utilisateur.prenom, utilisateur.username,
                      utilisateur.motDePasse) == 5) {
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
    while (fscanf(fichier, "%d %d %s %s %s %s %s", &etudiant.type, &etudiant.matricule, etudiant.classe, etudiant.nom, etudiant.prenom, etudiant.username,
                      etudiant.motDePasse) == 7) {
        if (etudiant.matricule == matricule) {
            fclose(fichier);
            return 1; // Le matricule est présent dans le fichier
        }
    }
    fclose(fichier);
    return 0; // Le matricule n'est pas présent dans le fichier
}
int getMatriculeFromUsername(const char* fichierEtudiant, const char* username) {
    FILE* fichier = fopen(fichierEtudiant, "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier des étudiants.\n");
        return -1; // Valeur de matricule invalide
    }

    Etudiant etudiant;
    while (fscanf(fichier, "%d %d %s %s %s %s %s", &etudiant.type, &etudiant.matricule, etudiant.classe, etudiant.nom, etudiant.prenom, etudiant.username,
                      etudiant.motDePasse) == 7) {
        if (strcmp(etudiant.username, username) == 0) {
            fclose(fichier);
            return etudiant.matricule; // Retourne le matricule de l'étudiant
        }
    }

    fclose(fichier);
    return -1; // Aucun matricule trouvé pour cet utilisateur
}
void  enregistrerDate( Date date) {
    FILE* fichier = fopen("date.txt", "a");
    if (fichier != NULL) {
        if (dateexiste(date)==0)
        {
            fprintf(fichier, "%d/%d/%d\n", date.jour, date.mois, date.annee);
            //Date ajoutée
            fclose(fichier);
        }
    }
}
int dateexiste(Date date) {
    FILE* fichier = fopen("date.txt", "r");
    if (fichier != NULL) {
        Date d;
        while(fscanf(fichier, "%d/%d/%d", &d.jour, &d.mois, &d.annee) != EOF) {
           // printf("%d/%d/%d\n", d.jour, d.mois, d.annee);
        if (d.jour == date.jour && d.mois == date.mois && d.annee == date.annee) {
             //La date existe deja
            return 1;
        } 
    }
    fclose(fichier);
    return 0;
}
}

void afficherParDate(Date d,char *nomFichier) {
    FILE* fichier2 = fopen("presence.txt", "r");
    FILE* fichier=fopen(nomFichier,"a");
    presence p;
    Etudiant e;
    if (fichier2 != NULL) {
                fprintf(fichier, "                              Les présents du %d/%d/%d\n", d.jour, d.mois, d.annee);
                fprintf(fichier, "+---------------+------------------+---------------+---------------+---------------+\n");
                fprintf(fichier, "| Matricule     | Classe           | Nom           | Prenom        | Heure         |\n");
                fprintf(fichier, "+---------------+------------------+---------------+---------------+---------------+\n");
         
    while(fscanf(fichier2, "%d %s %s %s %d/%d/%d %d:%d:%d %d\n",&p.etudiant.matricule,e.classe,e.nom,e.prenom,&p.date.jour,&p.date.mois,&p.date.annee,&p.date.heure,&p.date.minute,&p.date.seconde,&p.present) == 11) {
               if (d.jour == p.date.jour && d.mois == p.date.mois && d.annee == p.date.annee) {
                    fprintf(fichier,"|%-14d |%-17s |%-14s |%-14s |%d:%d:%d       |\n",p.etudiant.matricule,e.classe,e.nom,e.prenom,p.date.heure,p.date.minute,p.date.seconde);                   
                fprintf(fichier, "+---------------+------------------+---------------+---------------+---------------+\n");
                }
            }
} else {
    printf("Erreur lors de l'ouverture du fichier des présences.\n");
}
fclose(fichier);
fclose(fichier2);
}

void afficherTous(){
    FILE* fichier = fopen("date.txt", "r");
    presence p;
    Etudiant e;
    if (fichier != NULL) {
        Date d;
        while(fscanf(fichier, "%d/%d/%d", &d.jour, &d.mois, &d.annee) != EOF) {
            //printf("%d/%d/%d\n", d.jour, d.mois, d.annee);
            afficherParDate(d,"presencepardate.txt");   
        }
        fclose(fichier);
    }
    copyfile("presencepardate.txt", "presence_tous.txt");
}

void copyfile(char *nomFichier1, char *nomFichier2) {
    FILE* fichier1 = fopen(nomFichier1, "r");
    FILE* fichier2 = fopen(nomFichier2, "w");
    if (fichier1 != NULL && fichier2 != NULL) {
        char ch;
        while ((ch = fgetc(fichier1)) != EOF) {
            fputc(ch, fichier2);
        }
        fclose(fichier1);
        fclose(fichier2);
    }
     // Suppression du fichier source
    remove(nomFichier1);
    // Copie du fichier source dans le fichier de destination
    //rename(nomFichier2, nomFichier1);
   }
// Fonction pour vérifier si une année est bissextile
int estBissextile(int annee) {
    if ((annee % 4 == 0 && annee % 100 != 0) || (annee % 400 == 0))
        return 1; // Si bissextile
    else
        return 0; // Sinon
}
// Fonction pour vérifier si une date est valide
int estDateValide(int jour, int mois, int annee) {
    // Vérification des limites des mois et du jour
    if (mois < 1 || mois > 12 || jour < 1)
        return 0;
    // Vérification du nombre de jours pour février
    if (mois == 2) {
        if (estBissextile(annee)) {
            if (jour > 29)
                return 0;
        } else {
            if (jour > 28)
                return 0;
        }
    }
    // Vérification du nombre de jours pour les mois de 30 jours
    else if (mois == 4 || mois == 6 || mois == 9 || mois == 11) {
        if (jour > 30)
            return 0;
    }
    // Vérification du nombre de jours pour les mois de 31 jours
    else {
        if (jour > 31)
            return 0;
    }
    // Si la date est valide
    return 1;
}

#include <ctype.h>
Date verifieDate(){
    char date[10],ch;
    Date d;
    int i = 0;
    do
    {
        printf("Saisir une date (JJ/MM/AAAA) : ");
        scanf("%d/%d/%d", &d.jour, &d.mois, &d.annee);
        while(getchar() != '\n');
        if (!estDateValide(d.jour, d.mois, d.annee)) {
            printf("Date invalide. Recommencez.\n");
        }else {
            break;
        }
    } while (1);
    return d;
    
}

void afficherAuneDate(Date d){
    //char mot ="presence"+d.jour+"-"+d.mois+"-"+d.annee;
    char mot[50];
    sprintf(mot, "presence-%d-%d-%d.txt", d.jour, d.mois, d.annee);
    printf("%s\n",mot);
    FILE* fichier = fopen(mot, "w");
     if (fichier != NULL) {
        afficherParDate(d,mot);
        fclose(fichier);
     }
}


void envoieMsg(int matricule, char *message) {
    //printf("envoieMsg(%d, %s)\n", matricule, message);
    Message msg;
    msg.matricule = matricule;
    Etudiant e= recupererEtudiant(matricule);
    strcpy(msg.message, message);
    strcpy(msg.source,"admin");
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    msg.date.annee = tm->tm_year + 1900;
    msg.date.mois = tm->tm_mon + 1;
    msg.date.jour = tm->tm_mday;
    msg.date.heure = tm->tm_hour;
    msg.date.minute = tm->tm_min;
    msg.date.seconde = tm->tm_sec;
    msg.etat = 0;
    FILE *f = fopen("messages.txt", "a");
    fprintf(f, "%s  %d %s %s %d/%d/%d à %d:%d:%d etat: %d %s\n",msg.source,msg.matricule, e.prenom, e.nom,msg.date.jour, msg.date.mois, msg.date.annee, msg.date.heure, msg.date.minute, msg.date.seconde, msg.etat ,msg.message);
    fclose(f);
    //printf(Green"Message envoyé avec succès \xE2\x9C\x85\n");
}
void Messageaapprenant(){
    int matricule;
    char msg[100];
    do{
    printf("veuillez entrer le matricule de l'etudiant : \n");
    scanf("%d", &matricule);
    while(getchar() != '\n');
     if(!matriculeValide(matricule, "etudiants.txt")) printf("Matricule invalide \n");

    } while(!matriculeValide(matricule, "etudiants.txt")); 
    printf("veuillez entrer le message : \n");
    fgets(msg, 100, stdin); // Utilisation de fgets pour lire la chaîne complète
    msg[strcspn(msg, "\n")] = '\0'; // Suppression du saut de ligne
    envoieMsg(matricule, msg);
    printf("Message envoyé avec succès \xE2\x9C\x85\n");
}

void lesmatricules(int tab[100],int *nb){
    FILE *fichier;
    char ligne[100];
    int matricule;
    Etudiant e;
    int index = 0;

    fichier = fopen("etudiants.txt", "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.");
        exit(1);
    }

    while (fgets(ligne, sizeof(ligne), fichier)) {
        // Supposons que le format de ligne soit : matricule,ID_classe
        sscanf(ligne, "%d %d %s %s %s %s %s",&e.type, &e.matricule, e.classe, e.prenom, e.nom, e.username, e.motDePasse);
           // printf("%d %s %s %s %d %d %d\n", matricule,e.login, e.nom, e.prenom, e.classe, e.presence, e.absence);
            
            //printf("%d\n", e.matricule);
            tab[index] = e.matricule;
            index++;
        
    }
    fclose(fichier);

    *nb = index;
}
void messageaTous(){
    int tab[100],nb_etudiants;
    char msg[100];

    lesmatricules(tab, &nb_etudiants);
    printf("veuillez entrer le message : \n");
    fgets(msg, 100, stdin); // Utilisation de fgets pour lire la chaîne complète
    msg[strcspn(msg, "\n")] = '\0'; // Suppression du saut de ligne
    for(int i=0;i<nb_etudiants;i++){
        envoieMsg(tab[i], msg);
    }
    printf("Message envoyé avec succès \xE2\x9C\x85\n");
}


void listClasse(int tab[100],int *nb,char *classe){
    FILE *fichier = fopen("etudiants.txt", "r");
    int matricule;
    Etudiant e;
    int index = 0;
    while(fscanf(fichier, "%d %d %s %s %s %s %s",&e.type, &e.matricule, e.classe, e.prenom, e.nom, e.username, e.motDePasse) == 7) {
        if (strcmp(e.classe, classe) == 0) {
            tab[index] = e.matricule;
            printf("%d\n", tab[index]);
            index++;
        }
    }
    *nb = index;
    fclose(fichier);

}

void messageClasse(char* classe){
   int tab[100],nb_etudiants;
    char msg[100];

    listClasse(tab,&nb_etudiants, classe);
    printf("veuillez entrer le message : \n");
    fgets(msg, 100, stdin); // Utilisation de fgets pour lire la chaîne complète
    msg[strcspn(msg, "\n")] = '\0'; // Suppression du saut de ligne
   // while(getchar() != '\n');
    printf("%s\n", msg);
    for(int i=0;i<nb_etudiants;i++){
        //printf("%d\n", tab[i]);
        envoieMsg(tab[i], msg);
    }
    printf("Message envoyé avec succès \xE2\x9C\x85\n");

}

void lireMessage(int matricule) {
    FILE *f = fopen("messages.txt", "r");
    if (f == NULL) {
        printf("Erreur lors de l'ouverture du fichier.");
        exit(1);
    }
    char ligne[100];
    Message msg;
    Etudiant e;
    
    while (fgets(ligne, sizeof(ligne), f) != NULL) {
        if (sscanf(ligne, "%s %d %s %s %d/%d/%d à %d:%d:%d etat: %d %[^\n]", msg.source, &msg.matricule, e.nom, e.prenom, &msg.date.jour, &msg.date.mois, &msg.date.annee, &msg.date.heure, &msg.date.minute, &msg.date.seconde, &msg.etat, msg.message) != EOF) {
            if (msg.matricule == matricule) {
                printf("Message envoyé par:%s %s\n",msg.source, msg.message);
                printf("Date:%d/%d/%d à %d:%d:%d\n",msg.date.jour, msg.date.mois, msg.date.annee, msg.date.heure, msg.date.minute, msg.date.seconde);
               
            }
        }
    }

    fclose(f);
}

void modifierEtatMessage(int matricule){
    FILE *f_in = fopen("messages.txt", "r");
    FILE *f_out = fopen("messages_temp.txt", "w"); // Fichier temporaire pour écrire les mises à jour

    if (f_in == NULL || f_out == NULL) {
        printf("Erreur lors de l'ouverture des fichiers.");
        exit(1);
    }

    char ligne[200];
    Message msg;
    Etudiant e;
    
    while (fgets(ligne, sizeof(ligne), f_in) != NULL) {
        if (sscanf(ligne, "%s %d %s %s %d/%d/%d à %d:%d:%d etat: %d %[^\n]", msg.source, &msg.matricule, e.nom, e.prenom, &msg.date.jour, &msg.date.mois, &msg.date.annee, &msg.date.heure, &msg.date.minute, &msg.date.seconde, &msg.etat, msg.message) != EOF) {
            if (msg.matricule == matricule) {
                msg.etat = 1;
                fprintf(f_out, "%s %d %s %s %d/%d/%d à %d:%d:%d etat: %d %s\n", msg.source, msg.matricule, e.nom, e.prenom,  msg.date.jour, msg.date.mois, msg.date.annee, msg.date.heure, msg.date.minute, msg.date.seconde, msg.etat, msg.message);
            }else {
                fprintf(f_out, "%s %d %s %s %d/%d/%d à %d:%d:%d etat: %d %s\n", msg.source, msg.matricule, e.nom, e.prenom,  msg.date.jour, msg.date.mois, msg.date.annee, msg.date.heure, msg.date.minute, msg.date.seconde, msg.etat, msg.message);
        
            }

        }
    } 
        

    fclose(f_in);
    fclose(f_out);

    // Remplacer l'ancien fichier par le nouveau
    remove("messages.txt");
    rename("messages_temp.txt", "messages.txt");
}

void nbreMessages(int mat,int *nb){
    FILE *fichier;
    char ligne[100];
    int matricule;
    Etudiant e;
    int index = 0;
    Message msg;

    fichier = fopen("messages.txt", "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.");
        exit(1);
    }

    fseek(fichier, 0, SEEK_SET);
    while (fgets(ligne, sizeof(ligne), fichier)) {
        // Supposons que le format de ligne soit : matricule,ID_classe
        sscanf(ligne, "%s %d %s %s %d/%d/%d à %d:%d:%d etat: %d %s", msg.source, &msg.matricule, e.nom, e.prenom,  &msg.date.jour, &msg.date.mois, &msg.date.annee, &msg.date.heure, &msg.date.minute, &msg.date.seconde, &msg.etat,msg.message);
        
        if(msg.etat == 0 && msg.matricule == mat){
            index++;
        }
       
        
        
       
           // printf("%d %s %s %s %d %d %d\n", matricule,e.login, e.nom, e.prenom, e.classe, e.presence, e.absence);
            
        
    }

    fclose(fichier);

    *nb = index;
}