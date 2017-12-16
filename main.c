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
    int numLigne;
    int choixMenu,choixLigne;
    ligne *lign;
    ligne lignes[NB_LIGNES];
    arret *arretTmp;
    nomArret=(char*)malloc(sizeof(char)*20);
    lign=(ligne*)malloc(sizeof(ligne));
    lireLignes(lignes);
    lireFichier(lign,"Ligne1.csv");
    log=login(MDP); //1=utilisateur standard, 2=administrateur
    for(i=0;i<NB_LIGNES;i++){affLigne(lignes[i]);}
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
            viderBuffer();
            if(choixMenu>=1 && choixMenu<5)
            {
                switch(choixMenu)
                {
                case 1 :
                    printf("Quel a");
                    break;
                case 2 :
                    printf("Entrer le nom de l'arret\n");
                    gets(nomArret);
                    printf("Entrer le numero de la ligne\n");
                    scanf("%d",&numLigne);
                    viderBuffer();

                    i=0;
                    while(i<NB_LIGNES && lignes[i].nbLigne!=numLigne) i++; //On cherche la ligne dans le tableau des lignes

                    if(i<NB_LIGNES-1){ //Si il y a plusieurs lignes avec le meme numero, on propose à l'utilisateur de choisir la bonne direction
                        if(lignes[i+1].nbLigne==numLigne){
                            printf("Il y a plusieurs directions correspondant a la ligne que vous cherchez\n");
                            do{
                                printf("Veuillez entrer le numero de la ligne que vous cherchez\n");
                                j=i;
                                while(lignes[j].nbLigne==numLigne && j<NB_LIGNES){ //On parcourt les lignes
                                    printf("%d),%s\n",j-i,lignes[j].nomLigne); //On donne le nombre à entrer et on le fait partir de 0 avec j-i, puis 1,2,... tant qu'on a une ligne avec le bon numéro
                                    j++;
                                }
                                scanf("%d",&choixLigne);
                            }while(choixLigne<0 && choixLigne>j-i-1);//Sécurité, j-i-1 car on inrémente j à la fin de la boucle
                            lign=&lignes[choixLigne+i];//On récupère l'adresse de la bonne ligne pour chercher un arret dedans
                        }
                    }
                    else if(i<NB_LIGNES){
                        lign=&lignes[i];
                    }
                    else{
                        printf("La ligne que vous cherchez n'est pas disponible\n");
                    }

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


