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

    /** Permet de lire un fichier et de l'écrire dans une variable de type ligne
     *
     * \param line ligne* On retourne la ligne dans ce pointeur
     * \param nomFichier char* Nom du fichier dans lequel on va lire (ex: Ligne1.csv)
     * \return void On retourne déjà ce qu'on veut dans line*,  donc pas besoin de retourner quoi que ce soit
     *
     */
    void lireFichier(ligne *line, char* nomFichier);

    /** \brief Cette fonction permet de se connecter
     *
     * \param MDP const char* On prend en entrée le mot de passe administrateur
     * \return int On retourne 1 si l'utilisateur est connecté en tant que simple utilisateur et 2 si l'utilisateur est connecté en tant qu'administrateur
     *
     */
    int login(const char* MDP);

    /** \brief Cette fonction permet de récuperer les horaires de passage d'une ligne sur un arrêt
     *
     * \param nomArret char* Le nom de l'arrêt que l'on recherche
     * \param nomLigne char* Le nom du fichier qui contient la ligne
     * \param arr arret* On renvoie l'arret que l'on recherche si on l'a trouvé dans cette adresse
     * \return void  On retourne déjà ce qu'on veut dans arr*,  donc pas besoin de retourner quoi que ce soit
     *
     */
    void getHorArret(char* nomArret, char* nomLigne,arret* arr);
    #endif // FONCTIONS_H_INCLUDED
