#ifndef OUTILS_H
#define OUTILS_H

#include "fonctions.h"

/*
Parametres : c1, c2 deux pointeurs vers une chaine de caractere.
Pre-condition : c1 doit être de la même taille ou plus grande que c2
Post_condition : Copie la chaine c2 dans la chaine c1
*/
void copie_str(char *c1, char *c2);


/*
Parametres : char *ch1, pointeur vers la première chaîne de caractères ;
             char *ch2, pointeur vers la deuxième chaîne de caractères.
Sortie : int, retourne 0 si les chaînes sont identiques, 1 si ch1 est supérieure à ch2,
         ou -1 si ch1 est inférieure à ch2.
Pré-condition : ch1 et ch2 doivent être des chaînes de caractères valides (terminées par '\0').
Post-condition : compare les deux chaînes selon l'ordre ASCII caractère par caractère.
*/
int str_cmp(char *ch1, char *ch2);

/*
Parametres : Trajet trajet, une structure de type Trajet.
Sortie : double, retourne le bénéfice net du trajet (total des billets vendus moins le coût d'exploitation du bus) ou -99999.99 si les horaires sont invalides.
Pré-condition : aucune.
Post-condition : extrait les horaires de départ et d'arrivée pour calculer la durée du trajet (en gérant le passage de minuit).
                 Calcule le coût du bus (100€ de base + 50€ par heure entamée). Additionne le prix des billets des
                 passagers dont l'id est compris entre 0 et 55, puis retourne la somme finale (billets - coût).
*/
double calcule_ca(Trajet trajet);

/*
Parametres : char *ch, un pointeur vers la chaîne de caractères à transformer.
Sortie : aucune .
Pré-condition : ch doit être une chaîne de caractères valide se terminant par le caractère nul '\0'.
Post-condition : parcourt la chaîne et remplace chaque lettre minuscule par sa
                 majuscule. Les caractères qui ne sont pas des minuscules ou qui ne sont pas des lettres restent inchangés.
*/
void upper(char* ch);

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

/*
Parametres : Trajet lTrajet, une structure de type Trajet contenant les données d'un voyage (villes, date, horaires).
Pré-condition : aucune.
Post-condition : affiche les informations d'un trajet sur une seule ligne.
                 Vérifie la présence des horaires : si une chaîne est vide affiche "ABSENT", sinon affiche l'horaire stocké.
*/
void afficherTrajet(Trajet lTrajet);

/* 3
Parametres: int n, lTrajet un tableau de n éléments contennant des struct Trajet
Parametres entrée/sortie : int T[n]
Pré-condition : n > 0
Post-condition, trie selection indirect du tableau ltrajet avec T comme tableau d'indice de lTrajet
*/
void tri_selection_indirect(int n, Trajet lTrajet[], int T[]);

/*
Parametres : int n, le nombre d'éléments à trier ;
             int T[n], un tableau d'entiers (index) ;
             double tCa[n], le tableau de référence contenant les chiffres d'affaires tCa[i] correspond au chiffre d'affaire du Trajet T[i].
Pré-condition : n > 0 ; le tableau T doit initialement contenir les indices valides du tableau tCa de 0 à n-1.
Post-condition : effectue un tri par sélection sur le tableau d'index T en se basant sur les valeurs du tableau tCa.
                 À la fin, T est réorganisé de telle sorte que tCa[T[i]] est classé par ordre croissant,
                 permettant un accès trié aux données sans modifier le tableau tCa original.
*/
void tri_selection_indirect_ca(int n, int T[], double tCa[]);

//TODO: liste des fonction a faire pour le 10

void tri_selection_horaire(int nb, int n, Trajet ltrajet[nb], int s_trajet[n], Trajet trajetCible);


void reatribution(Trajet wait[], Trajet *ltrajet, int nb_pass, int nb);

#endif // OUTILS_H_INCLUDED
