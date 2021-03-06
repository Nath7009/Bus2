#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonctions.h"

const char MDP[]="admin";
int NB_LIGNES=17;

int main()
{
    char *nomArret,nomLigne[10];
    int log=0,i,j,k,reussi=0,ecartMinutes, ecartMiniMinutes=10000;
    int numLigne,nbHoraires=0,nbArrets=0;
    int choixMenu,choixLigne;
    heure heureActu,ecart;
    heureActu.hr=0;
    heureActu.mn=0;
    ligne *lign;
    ligne *lignes;
    arret *arretTmp;
    lignes=(ligne*)malloc(sizeof(ligne)*NB_LIGNES);
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

                    if(i<NB_LIGNES-1)  //Si il y a plusieurs lignes avec le meme numero, on propose � l'utilisateur de choisir la bonne direction
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
                                    printf("%d),%s\n",j-i,lignes[j].nomLigne); //On donne le nombre � entrer et on le fait partir de 0 avec j-i, puis 1,2,... tant qu'on a une ligne avec le bon num�ro
                                    j++;
                                }
                                scanf("%d",&choixLigne);
                            }
                            while(choixLigne<0 && choixLigne>j-i-1); //S�curit�, j-i-1 car on inr�mente j � la fin de la boucle
                            lign=&lignes[choixLigne+i];//On r�cup�re l'adresse de la bonne ligne pour chercher un arret dedans
                        }
                    }
                    else if(i<NB_LIGNES)
                    {
                        lign=&lignes[i];
                    }
                    else
                    {
                        printf("La ligne que vous cherchez n'est pas disponible\n");
                        break;
                    }

                    arretTmp=getHorArret(nomArret,*lign); //On r�cup�re l'arret si il existe
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
                        while(heureActu.hr<0 || heureActu.mn<0 || heureActu.hr>24 || heureActu.mn>60);  //On v�rifie que l'heure est bien confornme

                        for(i=0; i<arretTmp->nbHr; i++) //Recherche de la meilleure heure
                        {
                            ecart.hr=heureActu.hr-arretTmp->heures[i].hr; //On calcule l'�cart entre l'heure voulue et les horaires
                            ecart.mn=heureActu.mn-arretTmp->heures[i].mn;
                            ecartMinutes=ecart.hr*60+ecart.mn;
                            if(ecartMinutes>=0)  //Si on a pas encore pass� la bonne heure
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

                    if(i<NB_LIGNES-1)  //Si il y a plusieurs lignes avec le meme numero, on propose � l'utilisateur de choisir la bonne direction
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
                                    printf("%d),%s\n",j-i,lignes[j].nomLigne); //On donne le nombre � entrer et on le fait partir de 0 avec j-i, puis 1,2,... tant qu'on a une ligne avec le bon num�ro
                                    j++;
                                }
                                scanf("%d",&choixLigne);
                            }
                            while(choixLigne<0 && choixLigne>j-i-1); //S�curit�, j-i-1 car on inr�mente j � la fin de la boucle
                            lign=&lignes[choixLigne+i];//On r�cup�re l'adresse de la bonne ligne pour chercher un arret dedans
                        }
                    }
                    else if(i<NB_LIGNES)
                    {
                        lign=&lignes[i];
                    }
                    else
                    {
                        printf("La ligne que vous cherchez n'est pas disponible\n");
                        break;
                    }

                    arretTmp=getHorArret(nomArret,*lign); //On r�cup�re l'arret si il existe
                    if(arretTmp==0)
                    {
                        printf("L'arret n'a pas pu etre trouve\n");
                    }
                    else
                    {
                        for(i=0; i<arretTmp->nbHr; i++) //On �crit toutes les heures dans la console
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

                    if(i<NB_LIGNES-1)  //Si il y a plusieurs lignes avec le meme numero, on propose � l'utilisateur de choisir la bonne direction
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
                                    printf("%d),%s\n",j-i,lignes[j].nomLigne); //On donne le nombre � entrer et on le fait partir de 0 avec j-i, puis 1,2,... tant qu'on a une ligne avec le bon num�ro
                                    j++;
                                }
                                scanf("%d",&choixLigne);
                                viderBuffer();
                            }
                            while(choixLigne<0 && choixLigne>j-i-1); //S�curit�, j-i-1 car on inr�mente j � la fin de la boucle
                            lign=&lignes[choixLigne+i];//On r�cup�re l'adresse de la bonne ligne pour chercher un arret dedans
                        }
                    }
                    else if(i<NB_LIGNES)
                    {
                        lign=&lignes[i];
                    }
                    else
                    {
                        printf("La ligne que vous cherchez n'est pas disponible\n");
                        break;
                    }

                    arretTmp=getHorArret(nomArret,*lign); //On r�cup�re l'arret si il existe
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
        printf("Vous pouvez acceder au programme en tant qu'administrateur\n");
        do
        {
            printf("Que voulez vous faire ?\n");
            printf("1-Donner l'horaire de passage du prochain bus pour un arret\n") ;
            printf("2-Donner l'horaire d'une ligne pour un arret\n");
            printf("3-Consulter les horaires d'un arret de bus\n");
            printf("4-Sauvegarder les horaires d'un arret d'une ligne dans un fichier\n");
            printf("5-Ajouter un arret\n");
            printf("6-Modifier le nom d'un arret\n");
            printf("7-Supprimer un arret\n");
            printf("8-Creer une ligne\n");
            printf("9-Modifier le nom d'une ligne\n");
            printf("10-Supprimer une ligne\n");
            printf("11-Afficher une ligne\n");
            printf("12-Quitter le programme\n");
            scanf("%d",&choixMenu);
            viderBuffer();
            if(choixMenu>=1 && choixMenu<12)
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

                    if(i<NB_LIGNES-1)  //Si il y a plusieurs lignes avec le meme numero, on propose � l'utilisateur de choisir la bonne direction
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
                                    printf("%d),%s\n",j-i,lignes[j].nomLigne); //On donne le nombre � entrer et on le fait partir de 0 avec j-i, puis 1,2,... tant qu'on a une ligne avec le bon num�ro
                                    j++;
                                }
                                scanf("%d",&choixLigne);
                            }
                            while(choixLigne<0 && choixLigne>j-i-1); //S�curit�, j-i-1 car on inr�mente j � la fin de la boucle
                            lign=&lignes[choixLigne+i];//On r�cup�re l'adresse de la bonne ligne pour chercher un arret dedans
                        }
                    }
                    else if(i<NB_LIGNES)
                    {
                        lign=&lignes[i];
                    }
                    else
                    {
                        printf("La ligne que vous cherchez n'est pas disponible\n");
                        break;
                    }

                    arretTmp=getHorArret(nomArret,*lign); //On r�cup�re l'arret si il existe
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
                        while(heureActu.hr<0 || heureActu.mn<0 || heureActu.hr>24 || heureActu.mn>60);  //On v�rifie que l'heure est bien confornme

                        for(i=0; i<arretTmp->nbHr; i++) //Recherche de la meilleure heure
                        {
                            ecart.hr=heureActu.hr-arretTmp->heures[i].hr; //On calcule l'�cart entre l'heure voulue et les horaires
                            ecart.mn=heureActu.mn-arretTmp->heures[i].mn;
                            ecartMinutes=ecart.hr*60+ecart.mn;
                            if(ecartMinutes>=0)  //Si on a pas encore pass� la bonne heure
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

                    if(i<NB_LIGNES-1)  //Si il y a plusieurs lignes avec le meme numero, on propose � l'utilisateur de choisir la bonne direction
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
                                    printf("%d),%s\n",j-i,lignes[j].nomLigne); //On donne le nombre � entrer et on le fait partir de 0 avec j-i, puis 1,2,... tant qu'on a une ligne avec le bon num�ro
                                    j++;
                                }
                                scanf("%d",&choixLigne);
                            }
                            while(choixLigne<0 && choixLigne>j-i-1); //S�curit�, j-i-1 car on inr�mente j � la fin de la boucle
                            lign=&lignes[choixLigne+i];//On r�cup�re l'adresse de la bonne ligne pour chercher un arret dedans
                        }
                    }
                    else if(i<NB_LIGNES)
                    {
                        lign=&lignes[i];
                    }
                    else
                    {
                        printf("La ligne que vous cherchez n'est pas disponible\n");
                        break;
                    }

                    arretTmp=getHorArret(nomArret,*lign); //On r�cup�re l'arret si il existe
                    if(arretTmp==0)
                    {
                        printf("L'arret n'a pas pu etre trouve\n");
                    }
                    else
                    {
                        for(i=0; i<arretTmp->nbHr; i++) //On �crit toutes les heures dans la console
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

                    if(i<NB_LIGNES-1)  //Si il y a plusieurs lignes avec le meme numero, on propose � l'utilisateur de choisir la bonne direction
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
                                    printf("%d),%s\n",j-i,lignes[j].nomLigne); //On donne le nombre � entrer et on le fait partir de 0 avec j-i, puis 1,2,... tant qu'on a une ligne avec le bon num�ro
                                    j++;
                                }
                                scanf("%d",&choixLigne);
                                viderBuffer();
                            }
                            while(choixLigne<0 && choixLigne>j-i-1); //S�curit�, j-i-1 car on inr�mente j � la fin de la boucle
                            lign=&lignes[choixLigne+i];//On r�cup�re l'adresse de la bonne ligne pour chercher un arret dedans
                        }
                    }
                    else if(i<NB_LIGNES)
                    {
                        lign=&lignes[i];
                    }
                    else
                    {
                        printf("La ligne que vous cherchez n'est pas disponible\n");
                        break;
                    }

                    arretTmp=getHorArret(nomArret,*lign); //On r�cup�re l'arret si il existe
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
                    //Ajouter un arret
                    printf("Entrer le numero de la ligne a laquelle vous voulez changer l'arret\n");
                    scanf("%d",&numLigne);
                    viderBuffer();
                    i=0;
                    while(i<NB_LIGNES && lignes[i].nbLigne!=numLigne) i++; //On cherche la ligne dans le tableau des lignes

                    if(i<NB_LIGNES-1)  //Si il y a plusieurs lignes avec le meme numero, on propose � l'utilisateur de choisir la bonne direction
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
                                    printf("%d),%s\n",j-i,lignes[j].nomLigne); //On donne le nombre � entrer et on le fait partir de 0 avec j-i, puis 1,2,... tant qu'on a une ligne avec le bon num�ro
                                    j++;
                                }
                                scanf("%d",&choixLigne);
                                viderBuffer();
                            }
                            while(choixLigne<0 && choixLigne>j-i-1); //S�curit�, j-i-1 car on inr�mente j � la fin de la boucle
                            lign=&lignes[choixLigne+i];//On r�cup�re l'adresse de la bonne ligne pour chercher un arret dedans
                        }
                    }
                    else if(i<NB_LIGNES)
                    {
                        lign=&lignes[i];
                    }
                    else
                    {
                        printf("La ligne que vous cherchez n'est pas disponible\n");
                        break;
                    }
                    printf("La ligne que vous cherchez a ete trouvee\n");
                    printf("Entrer le nom de l'arret que vous voulez ajouter\n");
                    gets(nomArret);
                    lign->arrets=(arret*)realloc(lign->arrets,sizeof(arret)*(lign->nbArrets+1));
                    strcpy(lign->arrets[lign->nbArrets].nom,nomArret); //On copie le nom de l'arret dans la bonne case memoire
                    lign->nbArrets++; //On incr�mente le nombre d'arrets dans la ligne
                    printf("Entrer le nombre d'horaires que vous souhaitez entrer\n");
                    scanf("%d",&nbHoraires);
                    viderBuffer();
                    lign->arrets[lign->nbArrets-1].heures=(heure*)malloc(sizeof(heure)*nbHoraires); //On a nbArrets = nombre d'arrets +1, donc on accede � nbArrets-1
                    lign->arrets[lign->nbArrets-1].heures[0].hr=0;
                    lign->arrets[lign->nbArrets-1].heures[0].mn=0;
                    ecartMinutes=10;//On l'initialise a une valeur superieure � 1 pour qu'� la premi�re it�ration il n'y ait pas de probl�me
                    for(i=0; i<nbHoraires; i++) //On parcourt tous les horaires pour le saisir
                    {
                        printf("Entrer l'horaire numero %d\n",i+1); //On met i+1 pour commencer a 1
                        do
                        {
                            printf("Entrer l'heure\n");
                            scanf("%d",&lign->arrets[lign->nbArrets-1].heures[i].hr);
                            printf("Entrer la minute\n");
                            scanf("%d",&lign->arrets[lign->nbArrets-1].heures[i].mn);
                            if(i>0)  //Si ce n'est pas la premi�re heure
                            {
                                ecartMinutes=lign->arrets[lign->nbArrets-1].heures[i].mn-lign->arrets[lign->nbArrets-1].heures[i-1].mn;//On calcule l'�cart des minutes
                                ecartMinutes+=(lign->arrets[lign->nbArrets-1].heures[i].hr-lign->arrets[lign->nbArrets-1].heures[i-1].hr)*60;//On ajoute � l'ecart des minutes l'ecart des heures
                            }

                            if(ecartMinutes<1)  //Si on �crit une horaire � une heure inf�rieure � l'heure d'avant
                            {
                                printf("L'heure que vous avez saisi n'est pas valide\n");
                            }
                        }
                        while(lign->arrets[lign->nbArrets-1].heures[i].mn < 0   //On teste si l'heure est valide
                                || lign->arrets[lign->nbArrets-1].heures[i].mn > 60
                                ||lign->arrets[lign->nbArrets-1].heures[i].hr < 0
                                ||lign->arrets[lign->nbArrets-1].heures[i].hr > 24  //Si l'heure n'est pas correcte ou si les heures sont trop proches
                                ||ecartMinutes<=1); //Il faut que les horaires soient �cart�s d'au moins 1 minute, donc tant qu'on a pas cet ecart, on recommence
                    }
                    viderBuffer();
                    break;
                case 6:
                    printf("Entrer le nom de l'arret\n");
                    gets(nomArret);
                    printf("Entrer le numero de la ligne\n");
                    scanf("%d",&numLigne);
                    viderBuffer();

                    i=0;
                    while(i<NB_LIGNES && lignes[i].nbLigne!=numLigne) i++; //On cherche la ligne dans le tableau des lignes

                    if(i<NB_LIGNES-1)  //Si il y a plusieurs lignes avec le meme numero, on propose � l'utilisateur de choisir la bonne direction
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
                                    printf("%d),%s\n",j-i,lignes[j].nomLigne); //On donne le nombre � entrer et on le fait partir de 0 avec j-i, puis 1,2,... tant qu'on a une ligne avec le bon num�ro
                                    j++;
                                }
                                scanf("%d",&choixLigne);
                                viderBuffer();
                            }
                            while(choixLigne<0 && choixLigne>j-i-1); //S�curit�, j-i-1 car on inr�mente j � la fin de la boucle
                            lign=&lignes[choixLigne+i];//On r�cup�re l'adresse de la bonne ligne pour chercher un arret dedans
                        }
                    }
                    else if(i<NB_LIGNES)
                    {
                        lign=&lignes[i];
                    }
                    else
                    {
                        printf("La ligne que vous cherchez n'est pas disponible\n");
                        break;
                    }

                    arretTmp=getHorArret(nomArret,*lign); //On r�cup�re l'arret si il existe
                    if(arretTmp==0)
                    {
                        printf("L'arret n'a pas pu etre trouve");
                    }
                    else
                    {
                        printf("Quel est le nom que vous voulez donner a cet arret\n");
                        gets(nomArret);
                        strcpy(arretTmp->nom,nomArret); //l'arret temporaire a la meme adresse que l'arret dans le tableau lignes, donc on copie � l'aide de cette adresse
                    }
                    break;
                case 7:
                    printf("Entrer le nom de l'arret\n");
                    gets(nomArret);
                    printf("Entrer le numero de la ligne\n");
                    scanf("%d",&numLigne);
                    viderBuffer();

                    i=0;

                    while(i<NB_LIGNES && lignes[i].nbLigne!=numLigne) i++; //On cherche la ligne dans le tableau des lignes

                    if(i<NB_LIGNES-1)  //Si il y a plusieurs lignes avec le meme numero, on propose � l'utilisateur de choisir la bonne direction
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
                                    printf("%d),%s\n",j-i,lignes[j].nomLigne); //On donne le nombre � entrer et on le fait partir de 0 avec j-i, puis 1,2,... tant qu'on a une ligne avec le bon num�ro
                                    j++;
                                }
                                scanf("%d",&choixLigne);
                                viderBuffer();
                            }
                            while(choixLigne<0 && choixLigne>j-i-1); //S�curit�, j-i-1 car on inr�mente j � la fin de la boucle
                            lign=&lignes[choixLigne+i];//On r�cup�re l'adresse de la bonne ligne pour chercher un arret dedans
                        }
                    }
                    else if(i<NB_LIGNES)
                    {
                        lign=&lignes[i];
                    }
                    else
                    {
                        printf("La ligne que vous cherchez n'est pas disponible\n");
                        break;
                    }

                    arretTmp=getHorArret(nomArret,*lign); //On r�cup�re l'arret si il existe
                    if(arretTmp==0)
                    {
                        printf("L'arret n'a pas pu etre trouve");
                    }
                    else
                    {
                        i=0;
                        while(strcmp(lign->arrets[i].nom,arretTmp->nom)!=0 && i<lign->nbArrets-1) i++; //On cherche l'indice de l'arret dan la ligne
                        if(i<lign->nbArrets-1)
                        {
                            for(j=i; j<lign->nbArrets-1; j++) //On percourt tous les arrets pour les supprimer
                            {
                                lign->arrets[j]=lign->arrets[j+1]; //On remplace chaque arret par le suivant
                            }
                            lign->nbArrets--; //On diminue le nombre d'arrets
                            lign->arrets=(arret*)realloc(lign->arrets,lign->nbArrets*sizeof(arret));//On realloue le tableau pour qu'il soit plus petit
                        }
                        else
                        {
                            printf("Une erreur est survenue, veuillez reesayer\n");
                        }
                    }
                    break;
                case 8:
                    printf("Entrer le nom de la ligne que vous voulez creer\n");
                    gets(nomLigne);
                    printf("Entrer le numero de la ligne\n");
                    scanf("%d",&numLigne);
                    viderBuffer();
                    if(numLigne>0 && numLigne<99)  //On teste si le numero de la ligne est positif et inf�rieur � 99 pour etre conforme
                    {
                        NB_LIGNES++;
                        lignes=(ligne*)realloc(lignes,sizeof(ligne)*NB_LIGNES);//On agrandit la taille du tableau
                        lignes[NB_LIGNES-1].nbLigne=numLigne;
                        strcpy(lignes[NB_LIGNES-1].nomLigne,nomLigne);
                        printf("Combien d'arrets voulez vous ajouter a la ligne?\n");
                        scanf("%d",&nbArrets);
                        viderBuffer();
                        if(nbArrets>0)
                        {
                            lignes[NB_LIGNES-1].nbArrets=nbArrets; //On affecte le nombre d'arrets � la ligne
                            lignes[NB_LIGNES-1].arrets=malloc(sizeof(arret)*nbArrets); //On alloue de la memoire pour les arrets
                            for(j=0; j<nbArrets; j++)
                            {
                                printf("Quel nom voulez vous donner a l'arret numero %d ?\n",j+1);
                                gets(nomArret);
                                strcpy(lignes[NB_LIGNES-1].arrets[j].nom,nomArret);
                                printf("Combien d'horaires voulez vous ajouter a cet arret ?\n");
                                scanf("%d",&nbHoraires);
                                viderBuffer();
                                if(nbHoraires>0)
                                {
                                    lignes[NB_LIGNES-1].arrets[j].heures=(heure*)malloc(sizeof(heure)*nbHoraires); //On alloue assez de m�moire pour les heures
                                    lignes[NB_LIGNES-1].arrets[j].nbHr=nbHoraires;
                                    for(i=0; i<lignes[NB_LIGNES-1].arrets[j].nbHr; i++)
                                    {
                                        printf("Entrer l'horaire numero %d\n",i+1); //On met i+1 pour commencer a 1
                                        do
                                        {
                                            printf("Entrer l'heure\n");
                                            scanf("%d",&lignes[NB_LIGNES-1].arrets[j].heures[i].hr);
                                            printf("Entrer la minute\n");
                                            scanf("%d",&lignes[NB_LIGNES-1].arrets[j].heures[i].mn);
                                            viderBuffer();
                                            if(i>0)  //Si ce n'est pas la premi�re heure
                                            {
                                                ecartMinutes=lignes[NB_LIGNES-1].arrets[j].heures[i].mn-lignes[NB_LIGNES-1].arrets[j].heures[i-1].mn;//On calcule l'�cart des minutes
                                                ecartMinutes+=(lignes[NB_LIGNES-1].arrets[j].heures[i].hr-lignes[NB_LIGNES-1].arrets[j].heures[i-1].hr)*60;//On ajoute � l'ecart des minutes l'ecart des heures
                                            }

                                            if(ecartMinutes<1)  //Si on �crit une horaire � une heure inf�rieure � l'heure d'avant
                                            {
                                                printf("L'heure que vous avez saisi n'est pas valide\n");
                                            }
                                        }
                                        while(lignes[NB_LIGNES-1].arrets[j].heures[i].mn < 0   //On teste si l'heure est valide
                                                || lignes[NB_LIGNES-1].arrets[j].heures[i].mn > 60
                                                ||lignes[NB_LIGNES-1].arrets[j].heures[i].hr < 0
                                                ||lignes[NB_LIGNES-1].arrets[j].heures[i].hr > 24  //Si l'heure n'est pas correcte ou si les heures sont trop proches
                                                ||ecartMinutes<=1); //Il faut que les horaires soient �cart�s d'au moins 1 minute, donc tant qu'on a pas cet ecart, on recommence
                                    }
                                }
                            }

                        }
                    }
                    break;
                case 9:
                    printf("Entrer le numero de la ligne\n");
                    scanf("%d",&numLigne);
                    viderBuffer();

                    i=0;
                    while(i<NB_LIGNES && lignes[i].nbLigne!=numLigne) i++; //On cherche la ligne dans le tableau des lignes

                    if(i<NB_LIGNES-1)
                    {
                        if(lignes[i+1].nbLigne==numLigne)  //Si il y a plusieurs lignes avec le meme numero, on propose � l'utilisateur de choisir la bonne direction
                        {
                            printf("Il y a plusieurs directions correspondant a la ligne que vous cherchez\n");
                            do
                            {
                                printf("Veuillez entrer le numero de la ligne que vous cherchez\n");
                                j=i;
                                while(lignes[j].nbLigne==numLigne && j<NB_LIGNES)  //On parcourt les lignes
                                {
                                    printf("%d),%s\n",j-i,lignes[j].nomLigne); //On donne le nombre � entrer et on le fait partir de 0 avec j-i, puis 1,2,... tant qu'on a une ligne avec le bon num�ro
                                    j++;
                                }
                                scanf("%d",&choixLigne);
                                viderBuffer();
                            }
                            while(choixLigne<0 && choixLigne>j-i-1); //S�curit�, j-i-1 car on incr�mente j � la fin de la boucle
                            lign=&lignes[choixLigne+i];//On r�cup�re l'adresse de la bonne ligne pour chercher un arret dedans
                        }
                    }
                    else if(i<NB_LIGNES)
                    {
                        lign=&lignes[i];
                    }
                    else
                    {
                        printf("La ligne que vous cherchez n'est pas disponible\n");
                        break;
                    }
                    printf("Donnez le nouveau nom de la ligne\n");
                    gets(nomLigne);
                    strcpy(lign->nomLigne,nomLigne);
                    break;
                case 10:

                    printf("Entrer le numero de la ligne\n");
                    scanf("%d",&numLigne);
                    viderBuffer();

                    i=0;

                    while(i<NB_LIGNES && lignes[i].nbLigne!=numLigne) i++; //On cherche la ligne dans le tableau des lignes

                    if(i<NB_LIGNES-1)  //Si on a touv� la ligne
                    {
                        if(lignes[i+1].nbLigne==numLigne) //Si il y a plusieurs lignes avec le meme numero, on propose � l'utilisateur de choisir la bonne direction
                        {
                            printf("Il y a plusieurs directions correspondant a la ligne que vous cherchez\n");
                            do
                            {
                                printf("Veuillez entrer le numero de la ligne que vous cherchez\n");
                                j=i;
                                while(lignes[j].nbLigne==numLigne && j<NB_LIGNES)  //On parcourt les lignes
                                {
                                    printf("%d),%s\n",j-i,lignes[j].nomLigne); //On donne le nombre � entrer et on le fait partir de 0 avec j-i, puis 1,2,... tant qu'on a une ligne avec le bon num�ro
                                    j++;
                                }
                                scanf("%d",&choixLigne);
                                viderBuffer();
                            }
                            while(choixLigne<0 && choixLigne>j-i-1); //S�curit�, j-i-1 car on inr�mente j � la fin de la boucle
                            lign=&lignes[choixLigne+i];//On r�cup�re l'adresse de la bonne ligne pour la supprimer
                        }
                    }
                    else if(i<NB_LIGNES) //Si il y a une seule ligne avec ce nom
                    {
                        lign=&lignes[i];
                    }
                    else
                    {
                        printf("La ligne que vous cherchez n'est pas disponible\n");
                        break;
                    }

                    i=0;
                    while(strcmp(lign->nomLigne,lignes[i].nomLigne)!=0 && i<NB_LIGNES) i++; //On cherche l'indice de la ligne dans lignes
                    if(i<NB_LIGNES)
                    {
                        for(j=i; j<NB_LIGNES; j++) //On parcourt toutes les lignes pour les supprimer
                        {
                            lignes[j]=lignes[j+1]; //On remplace chaque ligne par la suivante
                        }
                        NB_LIGNES--; //On diminue le nombre d'arrets
                        lignes=(ligne*)realloc(lignes,NB_LIGNES*sizeof(ligne));//On realloue le tableau pour qu'il soit plus petit
                    }
                    else
                    {
                        printf("Une erreur est survenue\n");
                    }

                    break;
                case 11:
                    printf("Entrer le numero de la ligne\n");
                    scanf("%d",&numLigne);
                    viderBuffer();

                    i=0;
                    while(i<NB_LIGNES && lignes[i].nbLigne!=numLigne) i++; //On cherche la ligne dans le tableau des lignes

                    if(i<NB_LIGNES-1)
                    {
                        if(lignes[i+1].nbLigne==numLigne)  //Si il y a plusieurs lignes avec le meme numero, on propose � l'utilisateur de choisir la bonne direction
                        {
                            printf("Il y a plusieurs directions correspondant a la ligne que vous cherchez\n");
                            do
                            {
                                printf("Veuillez entrer le numero de la ligne que vous cherchez\n");
                                j=i;
                                while(lignes[j].nbLigne==numLigne && j<NB_LIGNES)  //On parcourt les lignes
                                {
                                    printf("%d),%s\n",j-i,lignes[j].nomLigne); //On donne le nombre � entrer et on le fait partir de 0 avec j-i, puis 1,2,... tant qu'on a une ligne avec le bon num�ro
                                    j++;
                                }
                                scanf("%d",&choixLigne);
                                viderBuffer();
                            }
                            while(choixLigne<0 && choixLigne>j-i-1); //S�curit�, j-i-1 car on incr�mente j � la fin de la boucle
                            lign=&lignes[choixLigne+i];//On r�cup�re l'adresse de la bonne ligne pour chercher un arret dedans
                        }
                    }
                    else if(i<NB_LIGNES)
                    {
                        lign=&lignes[i];
                    }
                    else
                    {
                        printf("La ligne que vous cherchez n'est pas disponible\n");
                        break;
                    }
                    affLigne(*lign);
                    break;
                }
            }
        }
        while(choixMenu!=12);
    }
    free(lignes);
    return 1;
}


