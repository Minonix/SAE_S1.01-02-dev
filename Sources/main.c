#include "../Headers/fonctions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void parsec(char *chemin, int nb, Trajet fichier[nb], int nb_c);
int count_file(char *chemin, int *nb_c);
void parsec_ligne(char *ligne, int nb, Trajet result[nb]);

int main(void)
{
    char chemin[50] = "test.csv";
    int nb_c = 0;
    printf("Veiliier renseinger le chemin vers le CSV : \n");
    // scanf("%s", &chemin); //! retirer le \n en haut
    int nb_l = count_file(chemin, &nb_c);
    Trajet *fichier = malloc(nb_l * sizeof(Trajet));
    if (fichier == NULL)
        return 1;

    parsec(chemin, nb_l, fichier, nb_c);

    free(fichier);
    return (1);
}

int count_file(char *chemin, int *nb_c)
{
    FILE *fichier = fopen(chemin, "r");

    if (fichier == NULL)
    {
        printf("Impossible d'ouvrir le fichier.\n");
        return 1;
    }

    int compteur = 0;
    char c;
    char dernier_char = 0;

    while ((c = fgetc(fichier)) != EOF)
    {
        *nb_c += 1;

        if (c == '\n')
        {
            compteur++;
        }
        dernier_char = c;
    }

    if (dernier_char != 0 && dernier_char != '\n')
    {
        compteur++;
    }

    fclose(fichier);

    printf("Le fichier contient %d lignes et %d carac.\n", compteur, *nb_c);

    return compteur;
}

void parsec(char *chemin, int nb, Trajet result[nb], int nb_c)
{
    FILE *fichier = fopen(chemin, "r");
    char c;

    if (fichier == NULL)
    {
        printf("Impossible d'ouvrir le fichier.\n");
        return;
    }

    char *buffer;
    buffer = malloc(sizeof(char) * nb_c);
    if (buffer == NULL)
    {
        printf("buffer, na pus trouver de l'espace");
        return;
    }

    int i;
    for (i = 0; i < nb_c && ((c = fgetc(fichier)) != EOF); i++)
    {
        buffer[i] = c;
    }
    buffer[i] = '\0';
    fclose(fichier);

    char *token = strtok(buffer, "\n"); // Premier appel avec la variable

    while (token != NULL)
    {
        parsec_ligne(token);
        token = strtok(NULL, "\n"); // Appels suivants avec NULL
    }

    // printf("Dernier morceau : %s\n", debut);

    free(buffer);
}

void parsec_ligne(char *ligne, int nb, Trajet result[nb])
{
    char *debut = ligne;
    char *fin;
    int i, x = 0;
    char **list_item = malloc(sizeof(char *) * 62);
    while ((fin = strchr(debut, ',')) != NULL)
    {
        int longueur = fin - debut;
        char *item = malloc(longueur + 1);
        strncpy(item, debut, longueur);
        item[longueur] = '\0';
        printf("item = %s\n", item);
        list_item[x] = item;
        x++;
        debut = fin + 1;
    }
    int longueur;
    for (longueur = 0; debut[longueur] != 0; longueur++);
    char *item = malloc(longueur + 1);
    strncpy(item, debut, longueur);
    item[longueur] = '\0';
    printf("item = %s\n", item);
    list_item[x] = item;








    for (int y = 0; list_item[y] != NULL; y++)
        free(list_item[y]);
}