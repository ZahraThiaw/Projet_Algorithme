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
                puts("      5. DECONNEXION");
                puts("****************************************");
                puts("Veuillez choisir une option : ");
                scanf("%d", &choix);

                if (choix==1)
                {
                    puts("***************GESTION DES ETUDIANTS***************");
                }else if (choix==2)
                {
                    puts("***************GENERATION DE FICHIERS***************");
                }else if (choix==3)
                {
                    puts("***************MARQUER LES PRESENCES***************");
                    

                    int choixclasse;
                    do
                    {
                        puts("***************CLASSES***************");
                        puts("Classe 1 (Dev Web)");
                        puts("Classe 2 (Ref Dig)");
                        puts("Choisissez une classe : ");
                        scanf("%d", &choixclasse);

                        if (choixclasse==1)
                        {
                            // Saisie du matricule de l'apprenant
                            int matriculeSaisi;
                            printf("Entrez le matricule de l'apprenant : ");
                            scanf("%d", &matriculeSaisi);

                            ajoutpresent("classes.txt", matriculeSaisi, 1); // appel de la fonction ajoutpresent(const char* nomFichier, int matricule, int present) 
                        }else if (choixclasse==2)
                        {
                            // Saisie du matricule de l'apprenant
                            int matriculeSaisi;
                            printf("Entrez le matricule de l'apprenant : ");
                            scanf("%d", &matriculeSaisi);

                            ajoutpresent("classes.txt", matriculeSaisi, 1); // appel de la fonction ajoutpresent(const char* nomFichier, int matricule, int present) 
                        }
                        
                    } while (choixclasse != 1 && choixclasse != 2);
                }
                else if (choix==4)
                {
                    puts("***************ENVOYER UN MESSAGE***************");
                }else if (choix==5) {
                    break;
                }
            } while (choix != 5);

        } else if (typeUtilisateur == 2) {
            int choix = 0;
            puts("***************Menu Apprenant***************");
            puts("      1. MARQUER MA PRÉSENCE");
            puts("      2. NOMBRE DE MINUTES D’ABSENCE");
            puts("      3. MES MESSAGES (0)");
            puts("      4. DECONNEXION");
            puts("****************************************");
            puts("Veuillez choisir une option : ");
            scanf("%d", &choix);
            do
            {
                if (choix == 1)
            {
                puts("***************MARQUER MA PRÉSENCE***************");
                int matriculeSaisi;
                printf("Entrez le matricule de l'apprenant : ");
                scanf("%d", &matriculeSaisi);
                ajoutpresent("classes.txt", matriculeSaisi, 1); 
            } else if (choix == 2)
            {
                puts("***************NOMBRE DE MINUTES D’ABSENCE***************");
            } else if (choix == 3){
                puts("***************MES MESSAGES***************");
            } else if (choix == 4){
                break;
            }
            } while (choix != 4);
            
            
           
        } else {
            printf("Identifiants incorrects. Veuillez réessayer.\n");
        }
    } while (typeUtilisateur != 1 && typeUtilisateur != 2);
    return 0;
}

