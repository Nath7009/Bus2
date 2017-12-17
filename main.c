#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonctions.h"

const char MDP[]="admin";

int main()
{
    FILE *fichier;
    char motDePasse[20],*nomArret,nomLigne[10];
    int log=0,i,j,k,reussi=0,ecartMinutes, ecartMiniMinutes=10000;
    int numLigne;
    int choixMenu,choixLigne;
    heure heureActu,ecart, ecartMin;
    heureActu.hr=0;
    heureActu.mn=0;
    ligne *lign;
    ligne lignes[NB_LIGNES];
    arret *arretTmp;
    nomArret=(char*)malloc(sizeof(char)*20);
    lign=(ligne*)malloc(sizeof(ligne));
    lireLignes(lignes);
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
            viderBuffer();
            if(choixMenu>=1 && choixMenu<5)
            {
                switch(choixMenu)
                {
                case 1 :
                    printf("Entrer le nom de l'arret\n");
                    gets(nomArret);
                    printf("Entrer le numero de la ligne\n");
                    scanf("%d",&numLigne);
                    viderBuffer();

                    i=0;
                    while(i<NB_LIGNES && lignes[i].nbLigne!=numLigne) i++; //On cherche la ligne dans le tableau des lignes

                    if(i<NB_LIGNES-1)  //Si il y a plusieurs lignes avec le meme numero, on propose à l'utilisateur de choisir la bonne direction
                    {
                        if(lignes[i+1].nbLigne==numLigne)
                        {
                            printf("Il y a plusieurs directions correspondant a la ligne que vous cherchez\n");
                            do
                            {
                                printf("Veuillez entrer le numero de la ligne que vous cherchez\n");
                                j=i;
                                while(lignes[j].nbLigne==numLigne && j<NB_LIGNES)  //On parcourt les lignes
                                {
                                    printf("%d),%s\n",j-i,lignes[j].nomLigne); //On donne le nombre à entrer et on le fait partir de 0 avec j-i, puis 1,2,... tant qu'on a une ligne avec le bon numéro
                                    j++;
                                }
                                scanf("%d",&choixLigne);
                            }
                            while(choixLigne<0 && choixLigne>j-i-1); //Sécurité, j-i-1 car on inrémente j à la fin de la boucle
                            lign=&lignes[choixLigne+i];//On récupère l'adresse de la bonne ligne pour chercher un arret dedans
                        }
                    }
                    else if(i<NB_LIGNES)
                    {
                        lign=&lignes[i];
                    }
                    else
                    {
                        printf("La ligne que vous cherchez n'est pas disponible\n");
                    }

                    arretTmp=getHorArret(nomArret,*lign); //On récupère l'arret si il existe
                    if(arretTmp==0)
                    {
                        printf("L'arret n'a pas pu etre trouve\n");
                    }
                    else
                    {
                        printf("Arret trouve\n");
                        do
                        {
                            printf("Entrer l'heure a laquelle vous voulez l'horaire le plus proche\n");
                            scanf("%d",&heureActu.hr);
                            printf("Entrer la minute a laquelle vous voulez l'horaire le plus proche\n");
                            scanf("%d",&heureActu.mn);
                        }
                        while(heureActu.hr<0 || heureActu.mn<0 || heureActu.hr>24 || heureActu.mn>60);  //On vérifie que l'heure est bien confornme

                        ecartMin.hr=24;
                        ecartMin.mn=60;

                        for(i=0; i<arretTmp->nbHr; i++) //Recherche de la meilleure heure
                        {
                            ecart.hr=heureActu.hr-arretTmp->heures[i].hr; //On calcule l'écart entre l'heure voulue et les horaires
                            ecart.mn=heureActu.mn-arretTmp->heures[i].mn;
                            ecartMinutes=ecart.hr*60+ecart.mn;
                            if(ecartMinutes>=0)  //Si on a pas encore passé la bonne heure
                            {
                                if(ecartMinutes<ecartMiniMinutes)
                                {
                                    ecartMiniMinutes=ecartMinutes;
                                }
                            }
                        }
                        ecart.hr=heureActu.hr-ecartMiniMinutes/60;
                        ecart.mn=heureActu.mn-ecartMiniMinutes%60;
                        if(ecart.mn<0)
                        {
                            ecart.hr--;
                            ecart.mn+=60;
                        }
                        printf("Un bus passe a l'arret que vous avez selectionne a %d heures %d\n\n",ecart.hr,ecart.mn);

                    }
                    break;
                case 2 :
                    printf("Entrer le nom de l'arret\n");
                    gets(nomArret);
                    printf("Entrer le numero de la ligne\n");
                    scanf("%d",&numLigne);
                    viderBuffer();

                    i=0;
                    while(i<NB_LIGNES && lignes[i].nbLigne!=numLigne) i++; //On cherche la ligne dans le tableau des lignes

                    if(i<NB_LIGNES-1)  //Si il y a plusieurs lignes avec le meme numero, on propose à l'utilisateur de choisir la bonne direction
                    {
                        if(lignes[i+1].nbLigne==numLigne)
                        {
                            printf("Il y a plusieurs directions correspondant a la ligne que vous cherchez\n");
                            do
                            {
                                printf("Veuillez entrer le numero de la ligne que vous cherchez\n");
                                j=i;
                                while(lignes[j].nbLigne==numLigne && j<NB_LIGNES)  //On parcourt les lignes
                                {
                                    printf("%d),%s\n",j-i,lignes[j].nomLigne); //On donne le nombre à entrer et on le fait partir de 0 avec j-i, puis 1,2,... tant qu'on a une ligne avec le bon numéro
                                    j++;
                                }
                                scanf("%d",&choixLigne);
                            }
                            while(choixLigne<0 && choixLigne>j-i-1); //Sécurité, j-i-1 car on inrémente j à la fin de la boucle
                            lign=&lignes[choixLigne+i];//On récupère l'adresse de la bonne ligne pour chercher un arret dedans
                        }
                    }
                    else if(i<NB_LIGNES)
                    {
                        lign=&lignes[i];
                    }
                    else
                    {
                        printf("La ligne que vous cherchez n'est pas disponible\n");
                    }

                    arretTmp=getHorArret(nomArret,*lign); //On récupère l'arret si il existe
                    if(arretTmp==0)
                    {
                        printf("L'arret n'a pas pu etre trouve\n");
                    }
                    else
                    {
                        for(i=0; i<arretTmp->nbHr; i++) //On écrit toutes les heures dans la console
                        {
                            printf("%d heure %d\n",arretTmp->heures[i].hr,arretTmp->heures[i].mn);
                        }
                    }
                    break;
                case 3 :
                    printf("Quel arret voulez vous rechercher ?\n");
                    gets(nomArret);
                    //viderBuffer();
                    reussi=0;
                    for(i=0; i<NB_LIGNES; i++)
                    {
                        for(j=0; j<lignes[i].nbArrets-1; j++)
                        {
                            if(strcmp(nomArret,lignes[i].arrets[j].nom)==0)
                            {
                                reussi=1;
                                printf("%s\n",lignes[i].nomLigne);
                                for(k=0; k<lignes[i].arrets[j].nbHr; k++)
                                {
                                    printf("%d h %d\n",lignes[i].arrets[j].heures[k].hr,lignes[i].arrets[j].heures[k].mn);
                                }
                            }
                        }
                    }
                    if(reussi==0)
                    {
                        printf("L'arret demande n'a pas pu etre trouve\n");
                    }
                    break;
                case 4 :
                    printf("Entrer le nom de l'arret\n");
                    gets(nomArret);
                    printf("Entrer le numero de la ligne\n");
                    scanf("%d",&numLigne);
                    viderBuffer();

                    i=0;
                    while(i<NB_LIGNES && lignes[i].nbLigne!=numLigne) i++; //On cherche la ligne dans le tableau des lignes

                    if(i<NB_LIGNES-1)  //Si il y a plusieurs lignes avec le meme numero, on propose à l'utilisateur de choisir la bonne direction
                    {
                        if(lignes[i+1].nbLigne==numLigne)
                        {
                            printf("Il y a plusieurs directions correspondant a la ligne que vous cherchez\n");
                            do
                            {
                                printf("Veuillez entrer le numero de la ligne que vous cherchez\n");
                                j=i;
                                while(lignes[j].nbLigne==numLigne && j<NB_LIGNES)  //On parcourt les lignes
                                {
                                    printf("%d),%s\n",j-i,lignes[j].nomLigne); //On donne le nombre à entrer et on le fait partir de 0 avec j-i, puis 1,2,... tant qu'on a une ligne avec le bon numéro
                                    j++;
                                }
                                scanf("%d",&choixLigne);
                                viderBuffer();
                            }
                            while(choixLigne<0 && choixLigne>j-i-1); //Sécurité, j-i-1 car on inrémente j à la fin de la boucle
                            lign=&lignes[choixLigne+i];//On récupère l'adresse de la bonne ligne pour chercher un arret dedans
                        }
                    }
                    else if(i<NB_LIGNES)
                    {
                        lign=&lignes[i];
                    }
                    else
                    {
                        printf("La ligne que vous cherchez n'est pas disponible\n");
                    }

                    arretTmp=getHorArret(nomArret,*lign); //On récupère l'arret si il existe
                    if(arretTmp==0)
                    {
                        printf("L'arret n'a pas pu etre trouve");
                    }
                    else
                    {
                        printf("Quel est le nom du fichier dans lequel vous voulez ecrire les horaires ?\n");
                        gets(nomLigne);
                        //viderBuffer();
                        ecrireArrFichier(*arretTmp,nomLigne);
                    }
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
            printf("5-Ajouter un arrêt\n");
            printf("6-Modifier le nom d'un arrêt\n");
            printf("7-Supprimer un arrêt\n");
            printf("8-Creer une ligne");
            printf("9-Modifier une ligne\n");
            printf("10-Supprimer une ligne\n");
            printf("11-Afficher une ligne\n");
            scanf("%d",&choixMenu);
            viderBuffer();
            if(choixMenu>=1 && choixMenu<5)
            {
                switch(choixMenu)
                {
                case 1 :
                    printf("Entrer le nom de l'arret\n");
                    gets(nomArret);
                    printf("Entrer le numero de la ligne\n");
                    scanf("%d",&numLigne);
                    viderBuffer();

                    i=0;
                    while(i<NB_LIGNES && lignes[i].nbLigne!=numLigne) i++; //On cherche la ligne dans le tableau des lignes

                    if(i<NB_LIGNES-1)  //Si il y a plusieurs lignes avec le meme numero, on propose à l'utilisateur de choisir la bonne direction
                    {
                        if(lignes[i+1].nbLigne==numLigne)
                        {
                            printf("Il y a plusieurs directions correspondant a la ligne que vous cherchez\n");
                            do
                            {
                                printf("Veuillez entrer le numero de la ligne que vous cherchez\n");
                                j=i;
                                while(lignes[j].nbLigne==numLigne && j<NB_LIGNES)  //On parcourt les lignes
                                {
                                    printf("%d),%s\n",j-i,lignes[j].nomLigne); //On donne le nombre à entrer et on le fait partir de 0 avec j-i, puis 1,2,... tant qu'on a une ligne avec le bon numéro
                                    j++;
                                }
                                scanf("%d",&choixLigne);
                            }
                            while(choixLigne<0 && choixLigne>j-i-1); //Sécurité, j-i-1 car on inrémente j à la fin de la boucle
                            lign=&lignes[choixLigne+i];//On récupère l'adresse de la bonne ligne pour chercher un arret dedans
                        }
                    }
                    else if(i<NB_LIGNES)
                    {
                        lign=&lignes[i];
                    }
                    else
                    {
                        printf("La ligne que vous cherchez n'est pas disponible\n");
                    }

                    arretTmp=getHorArret(nomArret,*lign); //On récupère l'arret si il existe
                    if(arretTmp==0)
                    {
                        printf("L'arret n'a pas pu etre trouve\n");
                    }
                    else
                    {
                        printf("Arret trouve\n");
                        do
                        {
                            printf("Entrer l'heure a laquelle vous voulez l'horaire le plus proche\n");
                            scanf("%d",&heureActu.hr);
                            printf("Entrer la minute a laquelle vous voulez l'horaire le plus proche\n");
                            scanf("%d",&heureActu.mn);
                        }
                        while(heureActu.hr<0 || heureActu.mn<0 || heureActu.hr>24 || heureActu.mn>60);  //On vérifie que l'heure est bien confornme

                        ecartMin.hr=24;
                        ecartMin.mn=60;

                        for(i=0; i<arretTmp->nbHr; i++) //Recherche de la meilleure heure
                        {
                            ecart.hr=heureActu.hr-arretTmp->heures[i].hr; //On calcule l'écart entre l'heure voulue et les horaires
                            ecart.mn=heureActu.mn-arretTmp->heures[i].mn;
                            ecartMinutes=ecart.hr*60+ecart.mn;
                            if(ecartMinutes>=0)  //Si on a pas encore passé la bonne heure
                            {
                                if(ecartMinutes<ecartMiniMinutes)
                                {
                                    ecartMiniMinutes=ecartMinutes;
                                }
                            }
                        }
                        ecart.hr=heureActu.hr-ecartMiniMinutes/60;
                        ecart.mn=heureActu.mn-ecartMiniMinutes%60;
                        if(ecart.mn<0)
                        {
                            ecart.hr--;
                            ecart.mn+=60;
                        }
                        printf("Un bus passe a l'arret que vous avez selectionne a %d heures %d\n\n",ecart.hr,ecart.mn);

                    }
                    break;
                case 2 :
                    printf("Entrer le nom de l'arret\n");
                    gets(nomArret);
                    printf("Entrer le numero de la ligne\n");
                    scanf("%d",&numLigne);
                    viderBuffer();

                    i=0;
                    while(i<NB_LIGNES && lignes[i].nbLigne!=numLigne) i++; //On cherche la ligne dans le tableau des lignes

                    if(i<NB_LIGNES-1)  //Si il y a plusieurs lignes avec le meme numero, on propose à l'utilisateur de choisir la bonne direction
                    {
                        if(lignes[i+1].nbLigne==numLigne)
                        {
                            printf("Il y a plusieurs directions correspondant a la ligne que vous cherchez\n");
                            do
                            {
                                printf("Veuillez entrer le numero de la ligne que vous cherchez\n");
                                j=i;
                                while(lignes[j].nbLigne==numLigne && j<NB_LIGNES)  //On parcourt les lignes
                                {
                                    printf("%d),%s\n",j-i,lignes[j].nomLigne); //On donne le nombre à entrer et on le fait partir de 0 avec j-i, puis 1,2,... tant qu'on a une ligne avec le bon numéro
                                    j++;
                                }
                                scanf("%d",&choixLigne);
                            }
                            while(choixLigne<0 && choixLigne>j-i-1); //Sécurité, j-i-1 car on inrémente j à la fin de la boucle
                            lign=&lignes[choixLigne+i];//On récupère l'adresse de la bonne ligne pour chercher un arret dedans
                        }
                    }
                    else if(i<NB_LIGNES)
                    {
                        lign=&lignes[i];
                    }
                    else
                    {
                        printf("La ligne que vous cherchez n'est pas disponible\n");
                    }

                    arretTmp=getHorArret(nomArret,*lign); //On récupère l'arret si il existe
                    if(arretTmp==0)
                    {
                        printf("L'arret n'a pas pu etre trouve\n");
                    }
                    else
                    {
                        for(i=0; i<arretTmp->nbHr; i++) //On écrit toutes les heures dans la console
                        {
                            printf("%d heure %d\n",arretTmp->heures[i].hr,arretTmp->heures[i].mn);
                        }
                    }
                    break;
                case 3 :
                    printf("Quel arret voulez vous rechercher ?\n");
                    gets(nomArret);
                    //viderBuffer();
                    reussi=0;
                    for(i=0; i<NB_LIGNES; i++)
                    {
                        for(j=0; j<lignes[i].nbArrets-1; j++)
                        {
                            if(strcmp(nomArret,lignes[i].arrets[j].nom)==0)
                            {
                                reussi=1;
                                printf("%s\n",lignes[i].nomLigne);
                                for(k=0; k<lignes[i].arrets[j].nbHr; k++)
                                {
                                    printf("%d h %d\n",lignes[i].arrets[j].heures[k].hr,lignes[i].arrets[j].heures[k].mn);
                                }
                            }
                        }
                    }
                    if(reussi==0)
                    {
                        printf("L'arret demande n'a pas pu etre trouve\n");
                    }
                    break;
                case 4 :
                    printf("Entrer le nom de l'arret\n");
                    gets(nomArret);
                    printf("Entrer le numero de la ligne\n");
                    scanf("%d",&numLigne);
                    viderBuffer();

                    i=0;
                    while(i<NB_LIGNES && lignes[i].nbLigne!=numLigne) i++; //On cherche la ligne dans le tableau des lignes

                    if(i<NB_LIGNES-1)  //Si il y a plusieurs lignes avec le meme numero, on propose à l'utilisateur de choisir la bonne direction
                    {
                        if(lignes[i+1].nbLigne==numLigne)
                        {
                            printf("Il y a plusieurs directions correspondant a la ligne que vous cherchez\n");
                            do
                            {
                                printf("Veuillez entrer le numero de la ligne que vous cherchez\n");
                                j=i;
                                while(lignes[j].nbLigne==numLigne && j<NB_LIGNES)  //On parcourt les lignes
                                {
                                    printf("%d),%s\n",j-i,lignes[j].nomLigne); //On donne le nombre à entrer et on le fait partir de 0 avec j-i, puis 1,2,... tant qu'on a une ligne avec le bon numéro
                                    j++;
                                }
                                scanf("%d",&choixLigne);
                                viderBuffer();
                            }
                            while(choixLigne<0 && choixLigne>j-i-1); //Sécurité, j-i-1 car on inrémente j à la fin de la boucle
                            lign=&lignes[choixLigne+i];//On récupère l'adresse de la bonne ligne pour chercher un arret dedans
                        }
                    }
                    else if(i<NB_LIGNES)
                    {
                        lign=&lignes[i];
                    }
                    else
                    {
                        printf("La ligne que vous cherchez n'est pas disponible\n");
                    }

                    arretTmp=getHorArret(nomArret,*lign); //On récupère l'arret si il existe
                    if(arretTmp==0)
                    {
                        printf("L'arret n'a pas pu etre trouve");
                    }



                    else
                    {
                        printf("Quel est le nom du fichier dans lequel vous voulez ecrire les horaires ?\n");
                        gets(nomLigne);
                        ecrireArrFichier(*arretTmp,nomLigne);
                    }
                    break;
                case 5:
                    break;
                case 6:
                    break;
                case 7:
                    break;
                case 8:
                    break;
                case 9:
                    break;
                case 10:
                    break;
                case 11:
                    break;
                }
            }
        }
        while(choixMenu!=5);
    }
    return 1;
}


