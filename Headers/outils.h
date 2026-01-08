#ifndef OUTILS_H
#define OUTILS_H

#include "fonctions.h"

/*
Parametres : c1, c2 deux pointeurs vers une chaine de caractere.
Pre-condition : c1 doit être de la même taille ou plus grande que c2
Post_condition : Copie la chaine c2 dans la chaine c1
*/
void copie_str(char *c1, char *c2);


int str_cmp(char *ch1, char *ch2);

double calcule_ca(Trajet trajet);

/**
 * entrées d1, d2: Date
 * sortie : int
 * post-cond: return 1 si d1 < d2. Si d1> d2, return  0. Si d1=d2 return 2.
 */
int compare_date(Date d1, Date d2);

/*
entrées : char* horaire
pré-condition : un horaire est un tableau de forme hhmm, contennant 4 caracteres + le caractere \n de fin, horaire peut être vide.
post-condition : affiche l'horaire sous la forme hh:mm
*/
void afficherhoraire(char *horaire);

void afficherTrajet(Trajet lTrajet);

/* 3
Parametres: int n, lTrajet un tableau de n éléments contennant des struct Trajet
Parametres entrée/sortie : int T[n]
Pré-condition : n > 0
Post-condition, trie selection indirect du tableau ltrajet avec T comme tableau d'indice de lTrajet
*/
void tri_selection_indirect(int n, Trajet lTrajet[], int T[]);


void tri_selection_indirect_ca(int n, int T[], double tCa[]);

//TODO: liste des fonction a faire pour le 10
int retrait(Trajet trajet, Trajet wait[], int nb_pass);

// reatribution(Trajet wait[], Trajet *ltrajet, int nb_pass, int nb);

#endif // OUTILS_H_INCLUDED
