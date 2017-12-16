#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonctions.h"

const char MDP[]="admin";

int main()
{
    FILE *fichier;
    char motDePasse[20],*nomArret,nomLigne[10];
    int log=0,i,j;
    char numLigne;
    int choixMenu;
    ligne *lign;
    arret *arretTmp;
    nomArret=(char*)malloc(sizeof(char)*20);
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
                    viderBuffer();
                    printf("Entrer le nom de l'arret\n");
                    //scanf("%s",nomArret);
                    gets(nomArret);
                    printf("Entrer le numero de la ligne\n");
                    scanf("%c",&numLigne);
                    viderBuffer();
                    strcpy(nomLigne,"Ligne");
                    i=0;

                    while(nomLigne[i]!='\0') i++; //On cherche la dernière lettre du nom de la ligne

                    nomLigne[i]=numLigne; //On ajoute à la fin le numéro de ligne
                    i++;
                    nomLigne[i]='\0'; //On finit la chaine par un \0
                    strcat(nomLigne,".csv");
                    lireFichier(lign,nomLigne); //On lit le fichier et on l'écrit dans lign
                    arretTmp=getHorArret(nomArret,*lign); //On récupère l'arret si il existe
                    if(arretTmp==0){
                        printf("L'arret n'a pas pu etre trouve");
                    }
                    else{
                        for(i=0;i<arretTmp->nbHr;i++){ //On écrit toutes les heures dans la console
                            printf("%d heure %d\n",arretTmp->heures[i].hr,arretTmp->heures[i].mn);
                        }
                    }
                    break;
                case 3 :
                    viderBuffer();
                    printf("Quel arret voulez vous rechercher ?\n");
                    gets(nomArret);
                    for(j=0;j<NB_LIGNES;j++){
                       strcpy(nomLigne,"Ligne");
                        i=0;
                        while(nomLigne[i]!='\0') i++; //On cherche la dernière lettre du nom de la ligne
                        nomLigne[i]=(char)j; //On ajoute à la fin le numéro de ligne
                        i++;
                        nomLigne[i]='\0'; //On finit la chaine par un \0
                        strcat(nomLigne,".csv");
                        lireFichier(lign,nomLigne); //On lit le fichier et on l'écrit dans lign
                        arretTmp=getHorArret(nomArret,*lign); //On récupère l'arret si il existe

                        if(arretTmp==0){
                            printf("L'arret n'a pas pu etre trouve");
                        }
                        else{
                            for(i=0;i<arretTmp->nbHr;i++){ //On écrit toutes les heures dans la console
                                printf("%d heure %d\n",arretTmp->heures[i].hr,arretTmp->heures[i].mn);
                            }
                        }
                    }
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


