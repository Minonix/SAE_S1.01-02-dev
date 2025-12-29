#include "../Headers/fonctions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int count_lines(char *chemin);
void parsec(char *chemin, int nb, Trajet fichier[nb]);
char *extraire_token(char *src, char *dest, char separateur);
void parsec_date(char *date, Trajet *trajet);

// --- MAIN ---
int main(void)
{
    char chemin[50] = "test.csv";
    int nb_l = count_lines(chemin);

    if (nb_l <= 0)
    {
        printf("Fichier vide ou introuvable.\n");
        return 1;
    }

    Trajet fichier[nb_l];
    parsec(chemin, nb_l, fichier);
    // afficheInfoTrajet(nb_l, fichier, 7113);
    Passager test = {30, "Martini", 12.50};
    ajoutSupprClients(nb_l, fichier, 7112, test);
    printf("\n");
    // affichernTrajet(nb_l, fichier);
    
    // // afficheInfoTrajet(nb_l)
    // // --- AFFICHAGE TEST ---
    printf("\n--- RESULTAT (%d trajets) ---\n", nb_l);
    for (int i = 0; i < nb_l; i++)
    {
        printf("------------------------------------------------\n");
        printf("[TRAJET %d] Bus: %d | %s (%02d/%02d/%d) -> %s\n",
               i + 1, fichier[i].numbus, fichier[i].villeDepart, fichier[i].dateDepart.jour, fichier[i].dateDepart.mois, fichier[i].dateDepart.annee, fichier[i].villeArrivee);

        for (int p = 0; p < fichier[i].nb_passager; p++)
        {
            // On affiche même si les données sont partielles (vide)
            printf("    Passager %d: ID=%d, Nom='%s', Prix=%.2f\n",
                   p + 1,
                   fichier[i].listePassagers[p].id,
                   fichier[i].listePassagers[p].nom,
                   fichier[i].listePassagers[p].prixbillet);
        }
    }
    printf("------------------------------------------------\n");

    return 0;
}

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

/** Fonction outil pour simplifier le parsing.
 * Lit 'src' jusqu'au 'separateur', copie dans 'dest', et retourne la suite.
 * Gère automatiquement les champs vides.
 */
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

//! Ancien programme :
/*
void parsec(char *chemin, int nb, Trajet fichier[nb], int nb_c);
int count_file(char *chemin, int *nb_c);

void parsec_ligne(char *ligne, const char delimiter, char list_item[62][50]);



int main(void)

{
    char chemin[50] = "trajets_10.csv";

    char chemin[50] = "trajets_10.csv";

    int nb_c = 0;

    printf("Veullier renseinger le chemin vers le CSV : \n");

    // scanf("%s", &chemin); //! retirer le \n en haut

    int nb_l = count_file(chemin, &nb_c);

    Trajet fichier[nb_l];

    // Trajet *fichier = (Trajet *)calloc(nb_l, sizeof(Trajet));

    // if (fichier == NULL)

    //     return 1;



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

        for (int p = 0; p < fichier->nb_passager; p++)

        {

            // // Condition simple pour ne pas afficher des passagers vides (ajuste selon ta struct)

            // if (fichier[i].listePassagers[p].id != 0)

            // {

            printf("    - ID: %d | Nom: %s | Prix: %.2f\n",

                   fichier[i].listePassagers[p].id,

                   fichier[i].listePassagers[p].nom,

                   fichier[i].listePassagers[p].prixbillet);

            // }

        }

    }

    printf("------------------------------------------------\n");

    // ==========================================

    // FIN ZONE DE TEST

    // ==========================================



    // free(fichier);

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



    char buffer[nb_c + 1];

    // buffer = malloc(sizeof(char) * (nb_c + 1));

    // if (buffer == NULL)

    // {

    //     printf("buffer, n'a pus trouver de l'espace");

    //     return;

    // }



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

        char list_item[62][50] = {0};

        parsec_ligne(token, ',', list_item);



        result[x].numbus = atoi(list_item[0]);

        strcpy(result[x].villeDepart, list_item[1]);

        strcpy(result[x].villeArrivee, list_item[2]);

        strcpy(result[x].dateDepart, list_item[3]);

        strcpy(result[x].horaireDepart, list_item[4]);

        strcpy(result[x].horaireArrivee, list_item[5]);

        int b = 0, nb_passager = 0;

        for (int a = 6; list_item[a] != NULL; a++, b++)

        {

            char list_pass[62][50] = {0};

            parsec_ligne(list_item[a], ':', list_pass);

            result[x].listePassagers[b].id = atoi(list_pass[0]);

            strcpy(result[x].listePassagers[b].nom, list_pass[1]);

            result[x].listePassagers[b].prixbillet = atof(list_pass[2]);

            nb_passager++;

            // for (int y = 0; list_pass[y] != NULL; y++)

            // {

            //     free(list_pass[y]);

            // }

            // free(list_pass);

        }

        result[x].nb_passager = nb_passager;

        // for (int y = 0; list_item[y] != NULL; y++)

        //     free(list_item[y]);

        // free(list_item);

        x++;

        token = strtok(NULL, "\n"); // Appels suivants avec NULL

    }



    // free(buffer);

}



void parsec_ligne(char *ligne, const char delimiter, char list_item[62][50])

{

    char *debut = ligne;

    char *fin;

    int x = 0;

    // char *list_item[50];

    // char **list_item = calloc(62, sizeof(char *));

    // if (!list_item)

    //     return NULL;

    while ((fin = strchr(debut, delimiter)) != NULL)

    {

        int longueur = fin - debut;

        char item[longueur + 1];

        // char *item = malloc(longueur + 1);

        // if (item == NULL)

        //     return (NULL);

        strncpy(item, debut, longueur);

        item[longueur] = '\0';

        strcpy(list_item[x], item);

        x++;

        debut = fin + 1;

    }

    int longueur;

    for (longueur = 0; debut[longueur] != 0; longueur++)

        ;

    // char *item = malloc(longueur + 1);

    // if (item == NULL)

    //     return (NULL);



    char item[longueur + 1];

    strncpy(item, debut, longueur);

    item[longueur] = '\0';

    strcpy(list_item[x], item);

    // return list_item;

}

*/