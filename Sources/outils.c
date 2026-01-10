#include "../Headers/fonctions.h"
#include <stdio.h>

void copie_str(char *c1, char *c2)
{
    int i = 0;
    for (i = 0; c2[i] != 0; i++)
    {
        c1[i] = c2[i];
    }
    c1[i] = 0;
}

int str_cmp(char *ch1, char *ch2)
{
    int i;
    for (i = 0; ch1[i] != 0 && ch2[i] != 0; i++)
    {
        if (ch1[i] > ch2[i])
            return 1;
        if (ch1[i] < ch2[i])
            return -1;
    }
    return ch1[i] - ch2[i];
}

void upper(char *ch)
{
    for (int i = 0; ch[i] != 0; i++)
    {
        if (ch[i] >= 'a' && ch[i] <= 'z')
        {
            ch[i] = ch[i] - ('a' - 'A');
        }
    }
}

int compare_date(Date d1, Date d2)
{
    if (d1.annee == d2.annee && d1.mois == d2.mois && d1.jour == d2.jour)
    {
        return 2;
    }
    if (d1.annee > d2.annee)
        return 0;
    else if (d1.annee < d2.annee)
        return 1;
    if (d1.mois > d2.mois)
        return 0;
    else if (d1.mois < d2.mois)
        return 1;
    if (d1.jour > d2.jour)
        return 0;
    return 1;
}

void tri_selection_indirect(int n, Trajet lTrajet[n], int T[n])
{
    int temp;
    for (int i = 0; i < n - 1; i++)
    {
        int j_mini = i;
        for (int j = i + 1; j < n; j++)
        {
            if (str_cmp(lTrajet[T[j]].villeDepart, lTrajet[T[j_mini]].villeDepart) == 0)
            {
                if (compare_date(lTrajet[T[j]].dateDepart, lTrajet[T[j_mini]].dateDepart))
                    j_mini = j;
            }
            if (str_cmp(lTrajet[T[j_mini]].villeDepart, lTrajet[T[j]].villeDepart) > 0)
            {
                j_mini = j;
            }
        }
        temp = T[i];
        T[i] = T[j_mini];
        T[j_mini] = temp;
    }
}

void afficherhoraire(char *horaire)
{
    if (horaire[0] == 0)
        printf("ABSENT");
    else
    {
        printf(" %c%c:%c%c", horaire[0], horaire[1], horaire[2], horaire[3]);
    }
}


void afficherTrajet(Trajet lTrajet)
{
    printf("Ville de départ : %17s | Ville d'arrivée : %17s | Date de départ : %02d/%02d/%4d | ", lTrajet.villeDepart, lTrajet.villeArrivee,
           lTrajet.dateDepart.jour, lTrajet.dateDepart.mois, lTrajet.dateDepart.annee);
    printf("Horaire de départ : ");
    afficherhoraire(lTrajet.horaireDepart);
    printf(" | ");
    printf("Horaire d'arrivée : ");

    afficherhoraire(lTrajet.horaireArrivee);
    printf("\n");
}

double calcule_ca(Trajet trajet)
{
    int hd, md, ha, ma;
    double somme_billet = 0.0;
    int cout_bus = 100;

    if (trajet.horaireDepart[0] == 0 || trajet.horaireArrivee[0] == 0)
    {
        return -99999.99;
    } // valeur arbitraire

    sscanf(trajet.horaireDepart, "%2d%2d", &hd, &md);
    sscanf(trajet.horaireArrivee, "%2d%2d", &ha, &ma);

    int tDepart = hd * 60 + md;
    int tArrivee = ha * 60 + ma;

    if (tArrivee < tDepart)
    {
        tArrivee += 24 * 60; // passage de minuit
    }
    cout_bus += ((tArrivee - tDepart + 59) / 60) * 50;

    int i = 0;
    while (i < trajet.nb_passager)
    {
        somme_billet += trajet.listePassagers[i].prixbillet;
        i++;
    }
    return somme_billet - cout_bus;
}

void tri_selection_indirect_ca(int n, int T[n], double tCa[n])
{
    int temp;
    for (int i = 0; i < n - 1; i++)
    {
        int j_mini = i;
        for (int j = i + 1; j < n; j++)
        {
            if (tCa[T[j]] < tCa[T[j_mini]])
            {
                j_mini = j;
            }
        }
        temp = T[i];
        T[i] = T[j_mini];
        T[j_mini] = temp;
    }
}
