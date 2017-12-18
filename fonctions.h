#ifndef FONCTIONS_H_INCLUDED
#define FONCTIONS_H_INCLUDED

extern int NB_LIGNES;

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
        char nomLigne[40];
        int nbArrets;
        arret *arrets;
    } ligne;

    /** \brief Fonction qui vide le buffer d'entrée pour éviter d'avoir de problèmes dans les fgets
     *
     * \return void
     *
     */
    void viderBuffer();

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
     * \param lign ligne La ligne dans laquelle on cherche l'arrêt
     * \param arr arret* On renvoie l'arret que l'on recherche si on l'a trouvé dans cette adresse
     * \return void  On retourne déjà ce qu'on veut dans arr*,  donc pas besoin de retourner quoi que ce soit
     *
     */
    arret* getHorArret(char* nomArret, ligne lign);

    /** \brief  Permet de lire tous les fichiers de ligne présents dans le dossier et de les écrire dans un tableau
     *
     * \param lignes ligne* Le tableau dans lequel on stocke les lignes, doit être déjà alloué
     *
     */
    void lireLignes(ligne* lignes);

    /** \brief
 *
 * \param line ligne Ligne à afficher
 * \return void Retourne ce qu'il y a à afficher dans la console
 *
 */
    void affLigne(ligne line);

    /** \brief
     *
     * \param arr arret Arret à écrire dans le fichier
     * \param nomFichier char* Nom du fichier dans lequel écrire
     * \return void
     *
     */
    void ecrireArrFichier(arret arr, char *nomFichier);
    #endif // FONCTIONS_H_INCLUDED
