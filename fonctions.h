#ifndef FONCTIONS_H_INCLUDED
#define FONCTIONS_H_INCLUDED
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
    void lireFichier(ligne *line, char* nomFichier);
    int login(const char* MDP);
    void getHorArret(char* nomArret, char* nomLigne,arret* arr);
    #endif // FONCTIONS_H_INCLUDED
