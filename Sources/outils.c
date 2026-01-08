#include "../Headers/fonctions.h"
#include <stdio.h>

long long complexite ;

void copie_str(char *c1, char *c2)
{

    int i = 0;

    complexite += 1 ;

    for (i = 0; c2[i] != 0; i++)
    {
        complexite += 6 ;
        c1[i] = c2[i];
    }
    complexite += 2 ;

    c1[i] = 0;

    complexite += 1 ;
}

int str_cmp(char *ch1, char *ch2)
{

    int i;
    complexite += 1 ;
    for (i = 0; ch1[i] != 0 && ch2[i] != 0; i++)
    {
        complexite += 6 ;

        complexite += 3 ;
        if (ch1[i] > ch2[i])
            return 1;

        complexite += 3 ;
        if (ch1[i] < ch2[i])
            return -1;
    }
    complexite += 5 ;

    complexite += 3 ;
    return ch1[i] - ch2[i];
}

int compare_date(Date d1, Date d2)
{

    complexite += 5 ;
    if (d1.annee == d2.annee && d1.mois == d2.mois && d1.jour == d2.jour)
    {
        return 2;
    }
    complexite += 2 ;
    if (d1.annee > d2.annee)
        return 0;
    else if (d1.annee < d2.annee)
        return 1;
    complexite += 2 ;
    if (d1.mois > d2.mois)
        return 0;
    else if (d1.mois < d2.mois)
        return 1;
    complexite += 1 ;
    if (d1.jour > d2.jour)
        return 0;
    return 1;
}

void tri_selection_indirect(int n, Trajet lTrajet[n], int T[n])
{

    int temp;

    complexite += 1 ;

    for (int i = 0; i < n - 1; i++)
    {
        complexite += 3 ;

        int j_mini = i;

        complexite += 1 ;

        complexite += 2 ;

        for (int j = i + 1; j < n; j++)
        {
            complexite += 2 ;

            complexite += 1 ;
            if (str_cmp(lTrajet[T[j]].villeDepart, lTrajet[T[j_mini]].villeDepart) == 0)
            {
                if (compare_date(lTrajet[T[j]].dateDepart, lTrajet[T[j_mini]].dateDepart)){
                    j_mini = j;
                    complexite += 1 ;
                }
            }
            complexite += 1 ;
            if (str_cmp(lTrajet[T[j_mini]].villeDepart, lTrajet[T[j]].villeDepart) > 0)
            {
                j_mini = j;
                complexite += 1 ;
            }
        }
        complexite += 7 ;

        temp = T[i];
        T[i] = T[j_mini];
        T[j_mini] = temp;
    }
}

void afficherTrajet(Trajet lTrajet)
{

    printf("Voici la liste de tout les trajets : \n");
    printf("Ville de départ : %17s | Ville d'arrivée : %17s | Date de départ : %02d/%02d/%4d | ", lTrajet.villeDepart, lTrajet.villeArrivee,
           lTrajet.dateDepart.jour, lTrajet.dateDepart.mois, lTrajet.dateDepart.annee);

    complexite += 4 ;

    if (lTrajet.horaireDepart[0] != 0)
        printf("Horaire de Départ : %6s | ", lTrajet.horaireDepart);
    else
        printf("Horaire de Départ : ABSENT | ");
    if (lTrajet.horaireArrivee[0] != 0)
        printf("Horaire d'arrivée : %6s\n", lTrajet.horaireArrivee);
    else
        printf("Horaire d'arrivée : ABSENT\n");
}

double calcule_ca(Trajet trajet)
{

    int hd, md, ha, ma;
    double somme_billet = 0.0;
    int cout_bus = 100;

    complexite += 2 ;

    complexite += 5 ;

    if (trajet.horaireDepart[0] == 0 || trajet.horaireArrivee[0] == 0)
    {
        return -99999.99;
    } // valeur arbitraire

    sscanf(trajet.horaireDepart, "%2d%2d", &hd, &md);
    sscanf(trajet.horaireArrivee, "%2d%2d", &ha, &ma);

    complexite += 6 ;

    int tDepart = hd * 60 + md;
    int tArrivee = ha * 60 + ma;

    complexite += 1 ;

    if (tArrivee < tDepart)
    {
        tArrivee += 24 * 60; // passage de minuit
        complexite += 2 ;
    }

    cout_bus += ((tArrivee - tDepart + 59) / 60) * 50;
    complexite += 5 ;

    int i = 0;
    complexite += 1 ;


    while (trajet.listePassagers[i].id <= 55 && trajet.listePassagers[i].id >= 0)
    {
        complexite += 5 ;
        somme_billet += trajet.listePassagers[i].prixbillet;
        i++;
        complexite += 3 ;
    }
    complexite += 5 ;
    complexite += 1 ;
    return somme_billet - cout_bus;
}

void tri_selection_indirect_ca(int n, int T[n], double tCa[n])
{

    int temp;

    complexite += 1 ;
    for (int i = 0; i < n - 1; i++)
    {
        complexite += 3 ;

        int j_mini = i;
        complexite += 1 ;

        complexite += 2 ;
        for (int j = i + 1; j < n; j++)
        {
            complexite += 2 ;

            complexite += 5 ;
            if (tCa[T[j]] < tCa[T[j_mini]])
            {
                complexite += 1 ;
                j_mini = j;
            }
        }

        complexite += 6 ;
        temp = T[i];
        T[i] = T[j_mini];
        T[j_mini] = temp;
    }
}

void afficherhoraire(char *horaire)
{
    complexite += 2 ;
    if (horaire[0] == 0)
        printf("ABSENT");
    else
    {
        printf(" %c%c:%c%c", horaire[0], horaire[1], horaire[2], horaire[3]);
        complexite += 4 ;
    }
}
