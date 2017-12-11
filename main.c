#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonctions.h"

const char MDP[]="admin";

int main()
{
    FILE *fichier;
    char motDePasse[20],nomArret[20],nomLigne[10];
    int log=0,i;
    char numLigne;
    int choixMenu;
    ligne *lign;
    arret arretTmp;
    lign=(ligne*)malloc(sizeof(ligne));
    lireFichier(lign,"Ligne1.csv");
    log=login(MDP); //1=utilisateur standard, 2=administrateur

    if(log==1)
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
                    printf("Entrer le nom de l'arret\n");
                    scanf("%s",nomArret);
                    //fgets(nomArret,sizeof(nomArret),stdin);
                    printf("Entrer le numero de la ligne\n");
                    scanf("%c",&numLigne);
                    strcpy(nomLigne,"Ligne");
                    strcat(nomLigne,"1.csv");
                    getHorArret(nomArret,nomLigne,&arretTmp);
                    if(&arretTmp==NULL){
                        printf("L'arret n'a pas pu etre trouve");
                    }
                    else{
                        for(i=0;i<arretTmp.nbHr;i++){
                            printf("%d heure %d\n",&arretTmp.heures[i].hr,&arretTmp.heures[i].mn);
                        }
                    }
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
    return 1;
}


