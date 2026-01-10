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
    int td1 = d1.annee*365 + d1.mois*30 + d1.jour;
    int td2 = d2.annee*365 + d2.mois*30 + d2.jour;

    return (td2 - td1);
    // if (d1.annee == d2.annee && d1.mois == d2.mois && d1.jour == d2.jour)
    // {
    //     return 2;
    // }
    // if (d1.annee > d2.annee)
    //     return 0;
    // else if (d1.annee < d2.annee)
    //     return 1;
    // if (d1.mois > d2.mois)
    //     return 0;
    // else if (d1.mois < d2.mois)
    //     return 1;
    // if (d1.jour > d2.jour)
    //     return 0;
    // return 1;
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
                if (compare_date(lTrajet[T[j]].dateDepart, lTrajet[T[j_mini]].dateDepart) )
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

int compare_horaire(char *h1, char *h2)
{
    int hd1, md1, hd2, md2;
    sscanf(h1, "%2d:%2d", &hd1, &md1);
    sscanf(h2, "%2d:%2d", &hd2, &md2);
    int t1 = hd1 * 60 + md1;
    int t2 = hd2 * 60 + md2;
    return t1 - t2;
}

void tri_selection_horaire(int n, Trajet lTrajet[n], Trajet lTrajet_trier[n], Trajet trajetCible)
{
    int T[n];
    for (int i = 0; i < n; i++)
    {
        T[i] = i;
    }

    for (int i = 0; i < n - 1; i++)
    {
        int j_min = i;
        for (int j = i + 1; j < n; j++)
        {
            // Calculate date difference for T[j] and T[j_min] relative to trajetCible
            int diff_date_j = (lTrajet[T[j]].dateDepart.annee - trajetCible.dateDepart.annee) * 365 +
                              (lTrajet[T[j]].dateDepart.mois - trajetCible.dateDepart.mois) * 30 +
                              (lTrajet[T[j]].dateDepart.jour - trajetCible.dateDepart.jour);

            int diff_date_j_min = (lTrajet[T[j_min]].dateDepart.annee - trajetCible.dateDepart.annee) * 365 +
                                  (lTrajet[T[j_min]].dateDepart.mois - trajetCible.dateDepart.mois) * 30 +
                                  (lTrajet[T[j_min]].dateDepart.jour - trajetCible.dateDepart.jour);

            if (diff_date_j < diff_date_j_min)
            {
                j_min = j;
            }
            else if (diff_date_j == diff_date_j_min)
            { 
                int diff_horaire_j = compare_horaire(lTrajet[T[j]].horaireDepart, trajetCible.horaireDepart);
                int diff_horaire_j_min = compare_horaire(lTrajet[T[j_min]].horaireDepart, trajetCible.horaireDepart);

                if (diff_horaire_j < diff_horaire_j_min)
                {
                    j_min = j;
                }
            }
        }
        int temp_idx = T[i];
        T[i] = T[j_min];
        T[j_min] = temp_idx;
    }
    // Copy sorted trajets to lTrajet_trier
    for (int i = 0; i < n; i++)
    {
        lTrajet_trier[i] = lTrajet[T[i]];
    }
    for (int i = 0; i < n; i++) { afficherTrajet(lTrajet_trier[i]); }
}

int filtrerTrajetsIdentiques(int nb, Trajet *lTrajet, Trajet *lTrajet_filtre, Trajet trajetRef)
{
    int x = 0;
    for (int j = 0; j < nb; j++)
    {
        char lVilleArriver_tmp[50];
        char lVilleDepart_tmp[50];
        char villeArrivee_tmp[50];
        char villeDepart_tmp[50];

        copie_str(lVilleArriver_tmp, lTrajet[j].villeArrivee);
        copie_str(lVilleDepart_tmp, lTrajet[j].villeDepart);
        copie_str(villeArrivee_tmp, trajetRef.villeArrivee);
        copie_str(villeDepart_tmp, trajetRef.villeDepart);
        upper(lVilleArriver_tmp);
        upper(lVilleDepart_tmp);
        upper(villeArrivee_tmp);
        upper(villeDepart_tmp);
        if (str_cmp(lVilleArriver_tmp, villeArrivee_tmp) == 0 && str_cmp(lVilleDepart_tmp, villeDepart_tmp) == 0)
        {
            lTrajet_filtre[x] = lTrajet[j];
            x++;
        }
    }
    return x;
}

void reatribution(Trajet wait[], Trajet *ltrajet, int nb_pass, int nb)
{
    printf("-----------------------------------------\n");
    for (int i = 0; i < nb_pass; i++)
    {
        // Tri des passagers de ce trajet par prix de billet décroissant
        for (int j = 0; j < wait[i].nb_passager - 1; j++)
        {
            for (int k = j + 1; k < wait[i].nb_passager; k++)
            {
                if (wait[i].listePassagers[j].prixbillet < wait[i].listePassagers[k].prixbillet)
                {
                    Passager temp = wait[i].listePassagers[j];
                    wait[i].listePassagers[j] = wait[i].listePassagers[k];
                    wait[i].listePassagers[k] = temp;
                }
            }
        }

        // for (int p = 0; p < wait[i].nb_passager; p++)
        // {
        //     printf(" Passager %d: %s (ID: %d, Prix: %.2f) 2\n", p + 1, wait[i].listePassagers[p].nom, wait[i].listePassagers[p].id, wait[i].listePassagers[p].prixbillet);
        // }
        // printf("-----------------------------------------\n");

        Trajet lTrajet_filtre[nb];
        // int indices_trajets_identiques[nb];
        int nb_trajets_identiques = filtrerTrajetsIdentiques(nb, ltrajet, lTrajet_filtre, wait[i]);

        // Sort the filtered identical trips by proximity to the original trip's date and time
        Trajet sorted_identical_trajets[nb_trajets_identiques];
        tri_selection_horaire(nb_trajets_identiques, lTrajet_filtre, sorted_identical_trajets, wait[i]);

        for (int p = 0; p < wait[i].nb_passager; p++)
        {
            Passager current_passager = wait[i].listePassagers[p];
            int passager_attribue = 0;

            for (int t_idx = 0; t_idx < nb_trajets_identiques; t_idx++)
            { // Iterate through the sorted_identical_trajets
                Trajet *target_trajet = &sorted_identical_trajets[t_idx];
                if (target_trajet->nb_passager < 56)
                {
                    target_trajet->listePassagers[target_trajet->nb_passager] = current_passager;
                    target_trajet->nb_passager++;
                    passager_attribue = 1;
                    break; // Passager attribué, passer au suivant
                }
            }
            if (!passager_attribue)
            {
                printf("Le passager %s du bus %d n'a pas pu être réattribué.\n", current_passager.nom, wait[i].numbus);
            }
        }
        // (void)passager_attribue;

    }
}
