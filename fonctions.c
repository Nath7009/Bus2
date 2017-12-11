#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonctions.h"

void lireFichier(ligne *line, char* nomFichier) // On renvoie le pointeur vers la ligne, on a besoin de connaitre le nom du fichier il faut que line soit deja alouée
{
    FILE *fichier;
    char c;
    int numArret=0,tmp,indHr=0;
    char nomArret[20];
    int index=0;
    ligne temp;
    temp.nbArrets=2;//Pas de \n pour le premier et le dernier arret, donc on a besoin de commencer à 2 au lieu de 0

    fichier=fopen(nomFichier,"r");

    while(feof(fichier)==0)  //On cherche le nombre d'arrets dans le fichier
    {
        c=getc(fichier);
        if(c=='\n')
        {
            temp.nbArrets++;
        }
    }

    rewind(fichier);

    temp.arrets=(arret*)malloc(sizeof(arret)*temp.nbArrets);

    while(feof(fichier)==0)
    {
        c=getc(fichier);
        index=0;
        indHr=0;
        while(c!=',' && feof(fichier)==0)  //On cherche le nom de l'arret
        {
            nomArret[index]=c;
            index++;
            c=getc(fichier);
        }
        nomArret[index]='\0';
        // temp.arrets[numArret].nom=(char*)malloc(sizeof(char)*index);
        strcpy(temp.arrets[numArret].nom,nomArret);
        //temp.arrets[numArret].nom=nomArret; //On affecte le nombre d'arrets a la ligne


        while((c<48 || c>57)  && feof(fichier)==0)  //Tant que ce qu'on lit n'est pas un nombre
        {
            c=getc(fichier);
        }

        fseek(fichier,-sizeof(char),SEEK_CUR);//On revient un caractère en arrière pour lire l'heure en entier
        temp.arrets[numArret].nbHr=1;
        temp.arrets[numArret].heures=(heure*)malloc(sizeof(heure));

        while(c!='\n' && feof(fichier)==0)
        {
            while((c=getc(fichier))!=',' && c!='|')  //Tant qu'on reste sur la meme heure
            {
                fseek(fichier,-sizeof(char),SEEK_CUR);
                fscanf(fichier,"%d",&tmp);
                temp.arrets[numArret].heures[indHr].hr=tmp;
                //fscanf(fichier,"%d",temp.arrets[numArret].heures[ temp.arrets[numArret].nbHr-1].hr);
                c=getc(fichier);
                fscanf(fichier,"%d",&tmp);
                temp.arrets[numArret].heures[indHr].mn=tmp;
                indHr++;
                // fscanf(fichier,"%d",temp.arrets[numArret].heures[ temp.arrets[numArret].nbHr-1].mn);
            }

            while((c<48 || c>57)  && feof(fichier)==0 && c!='\n')  //Tant que ce qu'on lit n'est pas un nombre
            {
                c=getc(fichier);
            }
            if(c!='\n' && feof(fichier)==0)
            {
                fseek(fichier,-sizeof(char),SEEK_CUR);//On revient un caractère en arrière pour lire l'heure en entier
                temp.arrets[numArret].nbHr++;
                temp.arrets[numArret].heures=(heure*)realloc(temp.arrets[numArret].heures,sizeof(heure)*(temp.arrets[numArret].nbHr+1));
            }
        }
        numArret++;
    }
    *line=temp;
    fclose(fichier);
}

int login(const char* MDP)
{
    int choix;
    char motDePasse[20];
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

    return choix;
}

void getHorArret(char* nomArret, char* nomLigne,arret* arr){ //nomArret=nom de l'arret comme on l'a dans le fichier des lignes (majuscule), nomLigne, le nom du fichier dans lequel on va chercher l'arret
    //On renvoie l'arret dans un pointeur que l'on met à null si on ne trouve pas l'arret
    ligne lign;
    int i=0;
    lireFichier(&lign,nomLigne);
    while(strcmp(nomArret,lign.arrets[i].nom)!=0 && i<lign.nbArrets){
        i++;
    }
    if(i<lign.nbArrets){
        *arr=lign.arrets[i];
    }
    else{
        printf("L'arret demande n'a pas ete trouve");
        arr=NULL;
    }
}
