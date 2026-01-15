#ifndef PARSEC_H_INCLUDED
#define PARSEC_H_INCLUDED

#include "fonctions.h"

/** 
* entre : chemin (chaîne de caractères représentant le chemin du fichier)
* résultats : int (nombre de lignes)
* Pré-condition : Le fichier doit exister et être accessible en lecture
* Post-condition : Retourne le nombre de lignes du fichier (nombre de trajets), ou 0 si vide/erreur
Clement Martini
**/
int count_lines(char *chemin);

/** 
* entre : chemin (fichier source), nb (nombre d'éléments), fichier (tableau de destination)
* résultats : void
* Pré-condition : nb doit correspondre au nombre de lignes du fichier, fichier doit être alloué
* Post-condition : Parse le fichier CSV et remplit le tableau de structures Trajet avec les données
Clement Martini
**/
void parsec(char *chemin, int nb, Trajet fichier[nb]);

/** 
* entre : src (chaîne source), dest (buffer destination), separateur (caractère délimiteur)
* résultats : char* (pointeur vers la position suivante dans src)
* Pré-condition : src et dest doivent être des pointeurs valides, dest assez grand
* Post-condition : Extrait une sous-chaîne de src jusqu'au séparateur, la copie dans dest, et retourne la position après le séparateur
Clement Martini
**/
char *extraire_token(char *src, char *dest, char separateur);

/** 
* entre : date (chaîne au format JJ/MM/AAAA), trajet (pointeur vers structure Trajet)
* résultats : void
* Pré-condition : date doit respecter le format attendu
* Post-condition : Convertit la chaîne date et initialise les champs jour, mois, année de la structure trajet
Clement Martini
**/
void parsec_date(char *date, Trajet *trajet);

#endif // PARSEC_H_INCLUDED