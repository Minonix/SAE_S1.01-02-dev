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
    int td1 = d1.annee * 365 + d1.mois * 30 + d1.jour;
    int td2 = d2.annee * 365 + d2.mois * 30 + d2.jour;

    return (td2 - td1);
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

int compare_horaire(char *h1, char *h2)
{
    int hd1, md1, hd2, md2;
    sscanf(h1, "%2d:%2d", &hd1, &md1);
    sscanf(h2, "%2d:%2d", &hd2, &md2);
    int t1 = hd1 * 60 + md1;
    int t2 = hd2 * 60 + md2;
    return t1 - t2;
}

void tri_selection_horaire(int nb, int n, Trajet ltrajet[nb], int s_trajet[n], Trajet trajetCible)
{
    int temp;
    for (int i = 0; i < n - 1; i++)
    {
        int j_mini = i;
        for (int j = i + 1; j < n; j++)
        {
            if (compare_horaire(ltrajet[s_trajet[j]].horaireDepart, trajetCible.horaireDepart) < compare_horaire(ltrajet[s_trajet[j_mini]].horaireDepart, trajetCible.horaireDepart) 
            && compare_date(ltrajet[s_trajet[j]].dateDepart, trajetCible.dateDepart) < compare_date(ltrajet[s_trajet[j_mini]].dateDepart, trajetCible.dateDepart))
            {
                j_mini = j;
            }
        }
        temp = s_trajet[i];
        s_trajet[i] = s_trajet[j_mini];
        s_trajet[j_mini] = temp;
    }
}

int filtrerTrajetsIdentiques(int nb, Trajet *lTrajet, int *indices_trajets_identiques, Trajet trajetRef)
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
            indices_trajets_identiques[x] = j;
            x++;
        }
    }
    return x;
}

void reatribution(Trajet wait[], Trajet *ltrajet, int nb_pass, int nb)
{
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

        int indices_trajets_identiques[nb];
        int nb_trajets_identiques = filtrerTrajetsIdentiques(nb, ltrajet, indices_trajets_identiques, wait[i]);

        tri_selection_horaire(nb, nb_trajets_identiques, ltrajet, indices_trajets_identiques, wait[i]);

        for (int p = 0; p < wait[i].nb_passager; p++)
        {
            Passager current_passager = wait[i].listePassagers[p];
            int passager_attribue = 0;
            
            for (int j = 0; j < nb_trajets_identiques && !passager_attribue; j++)
            {
                int idx = indices_trajets_identiques[j];
                if (ltrajet[idx].nb_passager < 55)
                {
                    int k = ltrajet[idx].nb_passager;
                    ltrajet[idx].listePassagers[k] = current_passager;
                    ltrajet[idx].listePassagers[k].id = k + 1;
                    ltrajet[idx].nb_passager++;
                    passager_attribue = 1;
                }
            }
            if (passager_attribue)
            {
                printf("Le passager %s du bus %d a pu être réattribué.\n", current_passager.nom, wait[i].numbus);
            }
        }
    }
}

