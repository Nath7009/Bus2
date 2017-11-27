#include <stdio.h>
#include <stdlib.h>

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

sddfsdfsfdfdsfdsfdf


int main()
{
    printf("%d",sizeof(ligne));
    return 0;
}
