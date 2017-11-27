#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char MDP[]="admin";

typedef struct
{
    int minute;
    int heure;
} heure;

typedef struct
{
    char nom[20];
    int nbHr;
    heure *heures;
} arret;

typedef struct
{
    int nbLigne;
    char nomLigne[20];
    int nbArrets;
    arret *arrets;
} ligne;



int main()
{
    FILE *fichier;
    char motDePasse[20]="0";
    int choix,choixMenu;
    do
    {
        do
        {
            printf("Etes vous un simple utlisateur ou un administateur ? 1 pour utilisateur et 2 pour administrateur\n");
            scanf("%d",&choix);
        }
        while(choix !=1 && choix !=2);
        if(choix ==2)
        {
            printf("Entrer le  mot de passe \n");
            scanf("%s",motDePasse);
        }
    }
    while(strcmp(MDP,motDePasse)!=0 && choix==2);
    if(choix==1)
    {
        printf("Vous pouvez acceder au programme en tant que simple utilisateur\n");
        do
        {
            printf("Que voulez vous faire ?\n");
            printf("1-Donner l'horaire de passage du prochain bus pour un arret\n") ;
            printf("2-Donner l'horaire d'une ligne pour un arret\n");
            printf("3-Consulter les horaires d'un arret de bus\n");
            printf("4-Sauvegarder les horaires d'un arret d'une ligne dans un fichier\n");
            printf("5-Quitter le programme\n");
            scanf("%d",&choixMenu);
            if(choixMenu>=1 && choixMenu<5)
            {
                switch(choixMenu)
                {
                case 1 :

                    break;
                case 2 :

                    break;
                case 3 :

                    break;
                case 4 :

                    break;


                }
            }
        }
        while(choixMenu!=5);

    }
    else
    {
        printf("Vous pouvez acceder au programme en tant qu'admin\n");

    }
    return 0;
}

