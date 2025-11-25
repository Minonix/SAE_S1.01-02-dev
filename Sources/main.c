#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "../Headers/fonctions.h"

void parsec(char *chemin, int nb, Trajet fichier[nb]);
int count_file(char *chemin) ;

int main(void) {
    char chemin[50] = "trajets_bus.csv";
    printf("Veiliier renseinger le chemin vers le CSV : ");
    // scanf("%s", &chemin);
    int nb = count_file(chemin);
    Trajet fichier[nb];
    parsec(chemin, nb, fichier);
    
}

int count_file(char *chemin) {
    FILE *fichier = fopen(chemin, "r");

    if (fichier == NULL) {
        printf("Impossible d'ouvrir le fichier.\n");
        return 1;
    }

    int compteur = 0;
    char c;
    char dernier_char = 0;

    while ((c = fgetc(fichier)) != EOF) {
        
        if (c == '\n') {
            compteur++;
        }
        dernier_char = c; 
    }

    if (dernier_char != 0 && dernier_char != '\n') {
        compteur++;
    }

    fclose(fichier);

    printf("Le fichier contient %d lignes.\n", compteur);

    return compteur;
}

void parsec(char *chemin, int nb, Trajet result[nb]) {
    FILE *fichier = fopen(chemin, "r");
    char c;

    if (fichier == NULL) {
        printf("Impossible d'ouvrir le fichier.\n");
        return 1;
    }

    for (int l = 0; !feof(fichier) && l < nb; l++ ) {
        while ((c = fgetc(fichier)) != EOF && c != '\n' )
        {
            
        }
        
    }
}