#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Headers/fonctions.h"

void parsec(char *chemin, int nb, Trajet fichier[nb], int nb_c);
int count_file(char *chemin, int *nb_c) ;

int main(void) {
    char chemin[50] = "trajets_bus.csv";
    int nb_c = 0;
    printf("Veiliier renseinger le chemin vers le CSV : \n");
    // scanf("%s", &chemin); //! retirer le \n en haut
    int nb_l = count_file(chemin, &nb_c);
    Trajet *fichier = malloc(nb_l * sizeof(Trajet));
    parsec(chemin, nb_l, fichier, nb_c);

    free(fichier);
    return (1);
}

int count_file(char *chemin, int *nb_c) {
    FILE *fichier = fopen(chemin, "r");

    if (fichier == NULL) {
        printf("Impossible d'ouvrir le fichier.\n");
        return 1;
    }

    int compteur = 0;
    char c;
    char dernier_char = 0;

    while ((c = fgetc(fichier)) != EOF) {
        *nb_c += 1;
        
        if (c == '\n') {
            compteur++;
        }
        dernier_char = c; 
    }

    if (dernier_char != 0 && dernier_char != '\n') {
        compteur++;
    }

    fclose(fichier);

    printf("Le fichier contient %d lignes et %d carac.\n", compteur, *nb_c);

    return compteur;
}

void parsec(char *chemin, int nb, Trajet result[nb], int nb_c) {
    FILE *fichier = fopen(chemin, "r");
    char c;

    if (fichier == NULL) {
        printf("Impossible d'ouvrir le fichier.\n");
        return ;
    }
    
    char *buffer;
    buffer = malloc(sizeof(char) * nb_c);
    int i;
    for (i = 0; i<nb_c && ((c = fgetc(fichier)) != EOF); i++) {
        buffer[i] = c;
    }
    buffer[i] = '\0';
    fclose(fichier);

    

    free(buffer);
}