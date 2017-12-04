#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char MDP[]="admin";

 typedef struct
{
    int mn;
    int hr;
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

int login(char* MDP)
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

void lireFichier(ligne *line, char* nomFichier) // On renvoie le pointeur vers la ligne, on a besoin de connaitre le nom du fichier il faut que line soit deja alouée
{
    FILE *fichier;
    char c;
    line->nbArrets=0;
    int numArret=0;
    char nomArret[20];
    int index=0;

    fichier=fopen(nomFichier,"r");

    while(feof(fichier)!=0)  //On cherche le nombre d'arrets dans le fichier
    {
        c=getc(fichier);
        if(c=='\n')
        {
            line->nbArrets++;
        }
    }
    rewind(fichier);

    line->arrets=(arret*)malloc(sizeof(arret)*line->nbArrets);

    while(feof(fichier)!=0)
    {
        c=getc(fichier);
        while(c!=',' && feof(fichier)!=0)  //On cherche le nom de l'arret
        {
            nomArret[index]=c;
            index++;
            c=getc(fichier);
        }
        nomArret[index]='\0';
        line->arrets[numArret].nom; //On affecte le nombre d'arrets a la ligne


        while((c<48 || c>57)  && feof(fichier)!=0)  //Tant que ce qu'on lit n'est pas un nombre
        {
            c=getc(fichier);
        }

        fseek(fichier,-sizeof(char),SEEK_CUR);//On revient un caractère en arrière pour lire l'heure en entier
        line->arrets[numArret].nbHr=1;
        line->arrets[numArret]->heures=(heure*)malloc(sizeof(heure));

        while(c!='\n' && feof(fichier)!=0)
        {
            while(c=getc(fichier)!=',' && c!='|')  //Tant qu'on reste sur la meme heure
            {
                fscanf(fichier,"%d",&(line->arrets[numArret]->heures[ line->arrets[numArret].nbHr-1].hr));
                c=getc(fichier);
                fscanf(fichier,"%d",&(line->arrets[numArret]->heures[ line->arrets[numArret].nbHr-1].mn));
            }

            while((c<48 || c>57)  && feof(fichier)!=0 && c!='\n')  //Tant que ce qu'on lit n'est pas un nombre
            {
                c=getc(fichier);
            }
            if(c!='\n' || c!=feof(fichier))
            {
                fseek(fichier,-sizeof(char),SEEK_CUR);//On revient un caractère en arrière pour lire l'heure en entier
                line->arrets[numArret].nbHr++;
                line->arrets[numArret]->heures=(heure*)realloc(sizeof(heure)*line->arrets[numArret].nbHr);
            }
        }
        numArret++;
    }

    fclose(fichier);
}


int main()
{
    FILE *fichier;
    char motDePasse[20];
    int log=0;
    int choixMenu;
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
}
return 0;
}

