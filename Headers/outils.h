#ifndef OUTILS_H
#define OUTILS_H

#include "fonctions.h"

/**
* entre : c1 (destination), c2 (source)
* résultats : void
* Pré-condition : c1 doit être alloué et de taille suffisante pour contenir c2
* Post-condition : Copie la chaîne de caractères c2 dans c1
Milo ROUSSET
**/
void copie_str(char *c1, char *c2);


/**
* entre : ch1, ch2 (chaînes de caractères à comparer)
* résultats : int (résultat de la comparaison)
* Pré-condition : ch1 et ch2 sont des chaînes valides terminées par \0
* Post-condition : Retourne 0 si identiques, >0 si ch1 > ch2, <0 si ch1 < ch2 (ordre lexicographique)
Milo ROUSSET
**/
int str_cmp(char *ch1, char *ch2);

/**
* entre : trajet (structure Trajet)
* résultats : double (chiffre d'affaires)
* Pré-condition : Les horaires doivent être au format valide
* Post-condition : Calcule le bénéfice (somme des billets - coût du trajet)
Milo ROUSSET
**/
double calcule_ca(Trajet trajet);

/**
* entre : ch (chaîne de caractères)
* résultats : void
* Pré-condition : ch est une chaîne valide
* Post-condition : Convertit les lettres minuscules de la chaîne en majuscules
Milo ROUSSET
**/
void upper(char* ch);

/**
* entre : d1, d2 (structures Date)
* résultats : int (différence en jours)
* Pré-condition : aucune
* Post-condition : Retourne un entier positif si d1 < d2, négatif si d1 > d2, 0 si égales
Clement Martini
**/
int compare_date(Date d1, Date d2);

/**
* entre : horaire (chaîne de caractères HHMM)
* résultats : void
* Pré-condition : horaire contient 4 caractères ou est vide
* Post-condition : Affiche l'horaire au format HH:MM ou "ABSENT"
Milo ROUSSET
**/
void afficherhoraire(char *horaire);

/**
* entre : lTrajet (structure Trajet)
* résultats : void
* Pré-condition : aucune
* Post-condition : Affiche les informations principales du trajet sur une ligne
Clement Martini
**/
void afficherTrajet(Trajet lTrajet);

/**
* entre : n (taille du tableau), lTrajet (tableau de données), T (tableau d'indices)
* résultats : void
* Pré-condition : T doit être initialisé avec les indices de 0 à n-1
* Post-condition : Trie le tableau d'indices T selon la ville de départ et la date des trajets dans lTrajet
Milo ROUSSET
**/
void tri_selection_indirect(int n, Trajet lTrajet[], int T[]);

/**
* entre : n (taille du tableau), T (tableau d'indices), tCa (tableau des chiffres d'affaires)
* résultats : void
* Pré-condition : T doit être initialisé, tCa doit correspondre aux indices
* Post-condition : Trie le tableau d'indices T selon les valeurs croissantes de tCa
Milo ROUSSET
**/
void tri_selection_indirect_ca(int n, int T[], double tCa[]);

/**
* entre : nb (taille totale), n (taille sous-ensemble), ltrajet (tableau complet), s_trajet (indices sous-ensemble), trajetCible (référence)
* résultats : void
* Pré-condition : s_trajet contient n indices valides
* Post-condition : Trie les indices de s_trajet par proximité d'horaire et de date avec le trajetCible
Clement Martini
**/
void tri_selection_horaire(int nb, int n, Trajet ltrajet[nb], int s_trajet[n], Trajet trajetCible);

/**
* entre : wait (tableau des trajets supprimés), ltrajet (tableau des trajets valides), nb_pass (nb supprimés), nb (nb valides)
* résultats : void
* Pré-condition : wait contient les trajets dont les passagers doivent être réattribués
* Post-condition : Tente de replacer les passagers des trajets supprimés vers les trajets valides identiques
Clement Martini
**/
void reatribution(Trajet wait[], Trajet *ltrajet, int nb_pass, int nb);

#endif // OUTILS_H_INCLUDED
