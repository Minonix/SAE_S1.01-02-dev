#include "../Headers/fonctions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void parsec(char *chemin, int nb, Trajet fichier[nb], int nb_c);
int count_file(char *chemin, int *nb_c);
char **parsec_ligne(char *ligne, const char delimiter);

int main(void)
{
    char chemin[50] = "test.csv";
    int nb_c = 0;
    printf("Veullier renseinger le chemin vers le CSV : \n");
    // scanf("%s", &chemin); //! retirer le \n en haut
    int nb_l = count_file(chemin, &nb_c);
    Trajet *fichier = calloc(nb_l, sizeof(Trajet));
    if (fichier == NULL)
        return 1;

    parsec(chemin, nb_l, fichier, nb_c);

    // ==========================================
    // DEBUT ZONE DE TEST
    // ==========================================

    printf("\n\n--- RÉSULTAT DU PARSING (%d trajets trouvés) ---\n", nb_l);

    for (int i = 0; i < nb_l; i++)
    {
        printf("------------------------------------------------\n");
        printf("[TRAJET %d]\n", i + 1);
        printf("  Bus ID   : %d\n", fichier[i].numbus);
        printf("  Depart   : %s (Ville: %s)\n", fichier[i].horaireDepart, fichier[i].villeDepart);
        printf("  Arrivee  : %s (Ville: %s)\n", fichier[i].horaireArrivee, fichier[i].villeArrivee);
        printf("  Date     : %s\n", fichier[i].dateDepart);

        printf("  Passagers :\n");
        // On suppose ici que la liste de passagers est remplie.
        // Note : Il serait bien d'avoir un champ 'nb_passagers' dans ta struct Trajet
        // Ici, j'affiche les 5 premiers pour tester, ou jusqu'à ce que l'ID soit 0
        for (int p = 0; p < 55; p++)
        {
            // Condition simple pour ne pas afficher des passagers vides (ajuste selon ta struct)
            if (fichier[i].listePassagers[p].id != 0)
            {
                printf("    - ID: %d | Nom: %s | Prix: %.2f\n",
                       fichier[i].listePassagers[p].id,
                       fichier[i].listePassagers[p].nom,
                       fichier[i].listePassagers[p].prixbillet);
            }
        }
    }
    printf("------------------------------------------------\n");
    // ==========================================
    // FIN ZONE DE TEST
    // ==========================================

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
    buffer = malloc(sizeof(char) * (nb_c + 1));
    if (buffer == NULL)
    {
        printf("buffer, n'a pus trouver de l'espace");
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
    int x = 0;
    while (token != NULL)
    {
        char **list_item = parsec_ligne(token, ',');

        result[x].numbus = atoi(list_item[0]);
        strcpy(result[x].villeDepart, list_item[1]);
        strcpy(result[x].villeArrivee, list_item[2]);
        strcpy(result[x].dateDepart, list_item[3]);
        strcpy(result[x].horaireDepart, list_item[4]);
        strcpy(result[x].horaireArrivee, list_item[5]);
        int b = 0;
        for (int a = 6; list_item[a] != NULL; a++, b++)
        {
            char **list_pass = parsec_ligne(list_item[a], ':    ');
            result[x].listePassagers[b].id = atoi(list_pass[0]);
            strcpy(result[x].listePassagers[b].nom, list_pass[1]);
            result[x].listePassagers[b].prixbillet = atof(list_pass[2]);
            for (int y = 0; list_pass[y] != NULL; y++)
                free(list_pass[y]);
            free(list_pass);
        }
        for (int y = 0; list_item[y] != NULL; y++)
            free(list_item[y]);
        free(list_item);
        x++;
        token = strtok(NULL, "\n"); // Appels suivants avec NULL
    }

    // printf("Dernier morceau : %s\n", debut);

    free(buffer);
}

char **parsec_ligne(char *ligne, const char delimiter)
{
    char *debut = ligne;
    char *fin;
    int x = 0;
    char **list_item = calloc(62, sizeof(char *));
    if (!list_item)
        return NULL;
    while ((fin = strchr(debut, delimiter)) != NULL)
    {
        int longueur = fin - debut;
        char *item = malloc(longueur + 1);
        if (item == NULL) return (NULL);
        strncpy(item, debut, longueur);
        item[longueur] = '\0';
        list_item[x] = item;
        x++;
        debut = fin + 1;
    }
    int longueur;
    for (longueur = 0; debut[longueur] != 0; longueur++)
        ;
    char *item = malloc(longueur + 1);
    if (item == NULL) return (NULL) ;
    strncpy(item, debut, longueur);
    item[longueur] = '\0';
    list_item[x] = item;
    return list_item;
}