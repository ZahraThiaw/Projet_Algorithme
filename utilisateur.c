#include <stdio.h>
#include <stdlib.h>
#include "fonction.h"
#include <string.h>
#include <time.h>
#include <termios.h>
#include <unistd.h>


int main() {
    //  int tab[100],nb_etudiants;
    //  char classe[20] = "Dev_Web";
    //  listClasse(tab,&nb_etudiants,classe);
    // Date date;
//     // int dateValide = 0;
// do {
//         printf("Entrez une date (jour mois annee) : ");
//         scanf("%d/%d/%d", &date.jour, &date.mois, &date.annee);
        
//         if (estDateValide(date.jour, date.mois, date.annee)) {
//             dateValide = 1;
//             if (dateexiste(date)==1)
//             {
//              afficherAuneDate(date);  
//             }
//         } else {
//             printf("La date n'est pas valide. Veuillez réessayer.\n");
//             break;
//         }
// } while (!dateValide);

    char motDePasse[50];
    int typeUtilisateur;
    int matricule;
    do {
        char* username = connexionUtiliser(motDePasse);
        typeUtilisateur = validerUtilisateur("utilisateurs.txt", "etudiants.txt", username, motDePasse);
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
                    int option;
                    puts("***************GENERATION DE FICHIERS***************");
                    puts("           1-Générer la liste des présences par date : ");
                    puts("           2-Afficher la liste des présences à une Date : ");
                    puts("****************************************************");
                    puts("Veuillez choisir une option : ");
                    scanf("%d", &option);

                    if (option==1){
                        afficherTous();
                    }else if (option==2){
                        afficherAuneDate(verifieDate());
                    }else{
                        puts("Veuillez choisir une option valide");
                    }
                }else if (choix==3)
                {
                    puts("***************MARQUER LES PRESENCES***************");
                    marquerPresences();
                }
                else if (choix==4)
                {
                    int option;

                    puts("***************ENVOYER UN MESSAGE***************");
                    printf("         1-Envoyer un message à tous les apprenants\n");
                    printf("         2-Envoyer un message à une classe\n");
                    printf("         3-Envoyer un message à un apprenant\n");
                    printf("         4-Retour\n");
                    puts("*************************************************");

                    printf("Veuillez choisir une option : ");
                    scanf("%d", &option);
                    if (option==1)
                    {
                        printf("Envoyer un message à tous les apprenants\n");
                        messageaTous();
                    }else if (option==2)
                    {
                        int choixclasse;
                        printf("Envoyer un message à une classe\n");
                        puts("           1-Dev_Web");
                        puts("           2-Dev_Data");
                        puts("           3-Ref_Dig");
                        puts("Veuillez choisir une classe : ");
                        scanf("%d", &choixclasse);

                        if (choixclasse==1){
                            messageClasse("Dev_Web");
                        }else if (choixclasse==2){
                            messageClasse("Dev_Data");
                        }else if (choixclasse==3){
                            messageClasse("Ref_Dig");
                        }else{
                            printf("Veuillez choisir une classe valide\n");
                        }
                    }else if (option==3)
                    {
                        printf("Envoyer un message à un apprenant\n");
                        Messageaapprenant();
                    }else if (option==4)
                    {
                        printf("Retour\n");
                    }else {
                        printf("Veuillez choisir une option valide\n");
                    }

                }else if (choix==5) {
                    break;
                }
            } while (choix != 5);

        } else if (typeUtilisateur == 2) {
            matricule = getMatriculeFromUsername("etudiants.txt", username);
            int choix = 0;
            do
            {
                int a=0;
                nbreMessages(matricule,&a);
                puts("***************Menu Apprenant***************");
                puts("      1. MARQUER MA PRÉSENCE");
                puts("      2. NOMBRE DE MINUTES D’ABSENCE");
                printf("    3. MES MESSAGES (%d)\n",a);
                puts("      4. DECONNEXION");
                puts("****************************************");
                puts("Veuillez choisir une option : ");
                scanf("%d", &choix);

                if (choix == 1)
                {
                    puts("***************MARQUER MA PRÉSENCE***************");
                    matricule = getMatriculeFromUsername("etudiants.txt", username);
                    if (matricule != -1) {
                         ajoutpresent("presence.txt", matricule, 1);
                    } else {
                        printf("Matricule non valide. Veuillez réessayer.\n");
                    }
                } else if (choix == 2)
                {
                    puts("***************NOMBRE DE MINUTES D’ABSENCE***************");
                } else if (choix == 3){
                    puts("***************MES MESSAGES***************");
                    lireMessage(matricule);
                    printf("***************FIN DE MES MESSAGES***************\n");
                    printf("appuyer sur une touche pour continuer...\n");
                    getchar();
                    modifierEtatMessage(matricule);
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

