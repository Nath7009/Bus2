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
    int choix;
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
        printf("Vous pouvez acceder au programme en tant que simple utilisateur");
    }
    else
    {
        printf("Vous pouvez acceder au programme en tant qu'admin");

    }
    return 0;
}

