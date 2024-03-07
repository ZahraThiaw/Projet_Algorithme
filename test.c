#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "fonction.h"

void SaisieMotDePasse( char login[], char* password) {
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
        

        
        if (ch == 10 && sizeof(password)!=0) {  // 10 is the ASCII code for Enter
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
    if (password[strlen(password) - 1] == '\n') {
    password[strlen(password) - 1] = '\0';
}
    //printf("\nMot de passe saisi : %s\n", password);
    
    tcsetattr(STDIN_FILENO, TCSANOW, &old_term);  // restaure les paramètres du terminal d'origine
    printf("\n"); 
    
}
int main () {

    char login[50];
    char password[50];
    printf("Entrez votre nom d'utilisateur : ");
    scanf("%s", login);
    printf("Entrez votre mot de passe : ");
    SaisieMotDePasse(login, &password);
}