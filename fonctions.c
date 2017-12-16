#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonctions.h"

void viderBuffer()
{
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}

void lireFichier(ligne *line, char* nomFichier) // On renvoie le pointeur vers la ligne, on a besoin de connaitre le nom du fichier il faut que line soit deja alouée
{
    FILE *fichier;
    char c;
    int numArret=0,tmp,indHr=0;
    char nomArret[20];
    int index=0,i;
    ligne temp;
    temp.nbArrets=1;//Pas de \n pour le  dernier arret, donc on a besoin de commencer à 2 au lieu de 0

    fichier=fopen(nomFichier,"r");
    if(fichier!=NULL)
    {
        while(feof(fichier)==0)  //On cherche le nombre d'arrets dans le fichier
        {
            c=getc(fichier);
            if(c=='\n')
            {
                temp.nbArrets++;
            }
        }

        rewind(fichier);

        temp.arrets=(arret*)malloc(sizeof(arret)*temp.nbArrets); //On alloue le bon nombre d'arrêts

        while(feof(fichier)==0 && c!='\n')  //On lit la première ligne pour avoir le nom et la direction de la ligne
        {
            c=getc(fichier);
            temp.nomLigne[index]=c; //On stocke le nom dans le tableau nomLigne
            index++;
        }
        temp.nomLigne[index-1]='\0'; //On termine le tableau par un \0



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
            for(i=0;i<temp.nbArrets;i++){
                temp.arrets[i].heures=(heure*)malloc(sizeof(heure));
            }

            while((c<48 || c>57)  && feof(fichier)==0)  //Tant que ce qu'on lit n'est pas un nombre
            {
                c=getc(fichier);
            }

            fseek(fichier,-sizeof(char),SEEK_CUR);//On revient un caractère en arrière pour lire l'heure en entier
            temp.arrets[numArret].nbHr=1;

            indHr=0;
            while(c!='\n' && feof(fichier)==0)
            {

                while((c=getc(fichier))!=',' && c!='|'  && feof(fichier)==0)  //Tant qu'on reste sur la meme heure
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

arret* getHorArret(char* nomArret, ligne lign)
{
    int i=0;
    arret* arr;
    while(strcmp(nomArret,lign.arrets[i].nom)!=0 && i<lign.nbArrets) //Tant qu'on ne trouve pas l'arrêt recherché et qu'on n'est pas à la fin du tableau
    {
        i++;
    }
    if(i<lign.nbArrets)
    {
        arr=&lign.arrets[i];
    }
    else
    {
        printf("L'arret demande n'a pas ete trouve\n");
        arr=0;
    }
    return arr;
}

void lireLignes(ligne* lignes)
{
    char nomLigne[13]; //12 caracteres permettent de stocker Ligne + numero de ligne + direction (a ou b) + .csv
    int numLigne=1,indLigne=0, fichierExiste=1, indNom=5;
    //numLigne pour stocker le numéro de la ligne, indLigne pour stocker l'indice du tableau lignes , fichierExiste pour tester si le fichier existe (1 s'il existe, 0 sinon)
    char direction='a';
    FILE *fichier;

    while(numLigne<100 && indLigne<=NB_LIGNES)  //Tant qu'on a pas atteint le maximum de numero de livres(99) et qu'on a pas atteint la fin du tableau
    {
        direction='a';
        while(direction<='z'  && indLigne<=NB_LIGNES && fichierExiste) //On percourt toutes les lettres tant qu'on a un fichier qui existe
        {
            strcpy(nomLigne,"Ligne");
            indNom=5;//On déplace l'indice sur le nom juste après Ligne
            if(numLigne<10)  //Si le numéro de la ligne est inférieur à 10
            {
                nomLigne[indNom]=numLigne+48;
                indNom++;
            }
            else
            {
                nomLigne[indNom]=(numLigne/10)+48;//On prend le numéro des dizaines
                indNom++;
                nomLigne[indNom]=(numLigne%10)+48;//On met le numéro des unités après
                indNom++;
            }
            nomLigne[indNom]=direction;
            indNom++;
            nomLigne[indNom]='\0';
            strcat(nomLigne,".csv");// On met .csv à la fin du nom du fichier
            fichier=fopen(nomLigne,"r");
            if(fichier!=NULL)
            {
                fclose(fichier);
                lireFichier(&lignes[indLigne],nomLigne);
                fichierExiste=1;
                lignes[indLigne].nbLigne=numLigne;
                indLigne++;

            }
            else
            {
                fichierExiste=0;
            }
            direction++;
        }
        fichierExiste=1;
        numLigne++;
    }
}

void affLigne(ligne line){
    int i,j;
    for(i=0;i<line.nbArrets;i++){
        printf("Nom de l'arret : %s\n",line.arrets[i].nom);
        for(j=0;j<line.arrets[i].nbHr;j++){
            printf("%d h %d\n",line.arrets[i].heures[j].hr,line.arrets[i].heures[j].mn);
        }
    }


}
