#include "../Headers/fonctions.h"
#include "../Headers/outils.h"
#include "../Headers/parsec.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int count_lines(char *chemin)
{
    FILE *f = fopen(chemin, "r");
    if (!f)
        return 0;

    int lignes = 0;
    char buffer[2048];
    while (fgets(buffer, sizeof(buffer), f))
    {
        lignes++;
    }
    fclose(f);
    return lignes;
}

char *extraire_token(char *src, char *dest, char separateur)
{
    int len = 0;
    while (src[len] != '\0' && src[len] != separateur)
    {
        len++;
    }

    strncpy(dest, src, len);
    dest[len] = '\0';

    if (src[len] != '\0')
        return src + len + 1;
    return src + len;
}

void parsec(char *chemin, int nb, Trajet fichier[nb])
{
    FILE *f = fopen(chemin, "r");
    if (!f)
        return;

    char ligne[2048];
    char temp[100];
    int i = 0;

    while (i < nb && fgets(ligne, sizeof(ligne), f))
    {
        ligne[strcspn(ligne, "\n")] = 0;

        char *curseur = ligne;

        curseur = extraire_token(curseur, temp, ',');
        fichier[i].numbus = atoi(temp);

        curseur = extraire_token(curseur, fichier[i].villeDepart, ',');
        curseur = extraire_token(curseur, fichier[i].villeArrivee, ',');
        curseur = extraire_token(curseur, temp, ',');
        parsec_date(temp, &fichier[i]);
        curseur = extraire_token(curseur, fichier[i].horaireDepart, ',');
        curseur = extraire_token(curseur, fichier[i].horaireArrivee, ',');

        int p = 0;
        char buffer_passager[100];

        while (*curseur != '\0' && p < 56)
        {
            curseur = extraire_token(curseur, buffer_passager, ',');

            if (buffer_passager[0] != '\0')
            {
                char *p_curseur = buffer_passager;

                p_curseur = extraire_token(p_curseur, temp, ':');
                fichier[i].listePassagers[p].id = atoi(temp);

                p_curseur = extraire_token(p_curseur, fichier[i].listePassagers[p].nom, ':');

                p_curseur = extraire_token(p_curseur, temp, ':');
                fichier[i].listePassagers[p].prixbillet = atof(temp);

                p++;
            }
        }
        fichier[i].nb_passager = p;
        i++;
    }
    fclose(f);
}

void parsec_date(char *date, Trajet *le_trajet)
{
    le_trajet->dateDepart.jour = atoi(date);
    date += 3;
    le_trajet->dateDepart.mois = atoi(date);
    date += 3;
    le_trajet->dateDepart.annee = atoi(date);
}
