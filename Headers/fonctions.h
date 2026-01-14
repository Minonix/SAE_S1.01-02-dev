#ifndef FONCTIONS_H_INCLUDED
#define FONCTIONS_H_INCLUDED


typedef struct
{
    int id;
    char nom[50];
    double prixbillet;
} Passager;

typedef struct
{
    int jour;
    int mois;
    int annee;
} Date;

typedef struct
{
    int numbus;
    char villeDepart[50];
    char villeArrivee[50];
    Date dateDepart;
    char horaireDepart[5];
    char horaireArrivee[5];
    int nb_passager;
    Passager listePassagers[56];
} Trajet;


/**
* entre : nb (nombre d'éléments), lTrajet (tableau de Trajet)
* résultats : void
* Pré-condition : nb >= 0
* Post-condition : Affiche tous les trajets (villes, dates, horaires) sur la sortie standard
**/
void afficherNTrajet(int nb, Trajet lTrajet[nb]);

/**
* entre : nb (nombre d'éléments), trajet (tableau de Trajet), numbus (numéro du bus recherché)
* résultats : void
* Pré-condition : nb >= 0
* Post-condition : Affiche les détails complets du trajet correspondant au numéro de bus, ou un message d'erreur si non trouvé
**/
void afficheInfoTrajet(int nb, Trajet trajet[nb], int numbus);

/**
* entre : nb (nombre d'éléments), lTrajet (tableau de Trajet)
* résultats : void
* Pré-condition : nb >= 0
* Post-condition : Affiche les trajets triés par ville de départ puis par date de départ
**/
void afficherTrajetTrie(int nb, Trajet lTrajet[nb]);

/**
* entre : nb (nombre d'éléments), trajet (tableau de Trajet), numbus (numéro du bus), new_or_not (Passager à ajouter/supprimer)
* résultats : void
* Pré-condition : nb >= 0
* Post-condition : Ajoute le passager s'il n'existe pas (et s'il reste de la place), ou le supprime s'il existe (basé sur le nom) dans le bus spécifié
**/
void ajoutSupprClients(int nb, Trajet trajet[nb], int numbus, Passager new_or_not);

/**
* entre : nb (nombre d'éléments), lTrajet (pointeur vers tableau de Trajet), numbus (numéro du bus), client (Passager avec nouvelles infos)
* résultats : void
* Pré-condition : nb >= 0
* Post-condition : Modifie le nom et le prix du passager (identifié par ID) dans le bus spécifié, ou l'ajoute si non trouvé
**/
void modificationClients(int nb, Trajet *lTrajet, int numbus, Passager client);

/**
* entre : nb (nombre d'éléments), trajet (tableau de Trajet), name (nom du fichier de sauvegarde)
* résultats : void
* Pré-condition : name est un chemin valide accessible en écriture
* Post-condition : Écrit l'ensemble des données des trajets et passagers dans le fichier spécifié au format CSV
**/
void sauvegardeDonnees(int nb, Trajet trajet[nb], char *name);

/**
* entre : n (nombre d'éléments), lTrajet (tableau source), lTrajet_filtre (tableau destination), ville (filtre ville départ), dateDepart (filtre date)
* résultats : int (nombre de trajets trouvés)
* Pré-condition : lTrajet_filtre doit être alloué avec une taille suffisante (>= n)
* Post-condition : Remplit lTrajet_filtre avec les trajets partant de la ville donnée à la date donnée et arrivant le lendemain
**/
int filtreTrajets1(int n, Trajet *lTrajet, Trajet *lTrajet_filtre, char ville[50], Date dateDepart);

/**
* entre : n (nombre d'éléments), lTrajet (tableau source), lTrajet_filtre (tableau destination), villeDepart, villeArrivee, dateDepart
* résultats : int (nombre de trajets trouvés)
* Pré-condition : lTrajet_filtre doit être alloué avec une taille suffisante (>= n)
* Post-condition : Remplit lTrajet_filtre avec les trajets correspondant aux villes de départ/arrivée et à la date spécifiées
**/
int filtreTrajets2(int n, Trajet *lTrajet, Trajet *lTrajet_filtre, char villeDepart[50], char villeArrivee[50], Date dateDepart);


/**
* entre : nb (nombre d'éléments), lTrajet (tableau de Trajet)
* résultats : void
* Pré-condition : nb >= 0
* Post-condition : Affiche la liste des trajets triée par chiffre d'affaires croissant
**/
void affichageTrajetTriesCA(int nb, Trajet *lTrajet);


/**
* entre : nb (nombre d'éléments), ltrajet (tableau de Trajet)
* résultats : int (nouveau nombre de trajets)
* Pré-condition : nb >= 0
* Post-condition : Supprime les bus à CA négatif, réattribue leurs passagers sur d'autres bus compatibles, et retourne la nouvelle taille du tableau
**/
int supprBusCANegatif(int nb, Trajet ltrajet[nb]);

#endif // FONCTIONS_H_INCLUDED
