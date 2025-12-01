#ifndef FONCTIONS_H_INCLUDED
#define FONCTIONS_H_INCLUDED
#define NB 8

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char nom[50];
    double prixbillet;
} Passager;

typedef struct {
    int nombus;
    char villeDepart[50];
    char villeArrivee[50];
    char dateDepart[11];
    char horaireDepart[5];
    char horaireArrivee[5];
    Passager listePassagers[55];
} Trajet ;



#endif // FONCTIONS_H_INCLUDED
