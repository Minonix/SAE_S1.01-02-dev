#include "../Headers/fonctions.h"
#include <stdio.h>

extern long long complexite;

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

void upper(char *ch)
{
    complexite += 1 ;
    for (int i = 0; ch[i] != 0; i++)
    {
        complexite += 3 ;

        complexite += 5 ;
        if (ch[i] >= 'a' && ch[i] <= 'z') //si c'est une lettre minuscule
        {
            complexite += 5 ;
            ch[i] = ch[i] - ('a' - 'A');
        }
    }
    complexite += 2 ;
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

void afficherhoraire(char *horaire)
{

    complexite +=2;

    if (horaire[0] == 0)
        printf("ABSENT"); //Si l'horaire n'est pas présent
    else
    {
        complexite +=4;
        printf(" %c%c:%c%c", horaire[0], horaire[1], horaire[2], horaire[3]); //On affiche l'horaire sous forme hh:mm
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

    complexite += 2 ;

    complexite += 5 ;

    if (trajet.horaireDepart[0] == 0 || trajet.horaireArrivee[0] == 0)
    {
        return -99999.99;
    } // valeur arbitraire

    sscanf(trajet.horaireDepart, "%2d%2d", &hd, &md);//hd pour heure départ, md pour minute départ
    sscanf(trajet.horaireArrivee, "%2d%2d", &ha, &ma);//ha pour heure arrivé, ma pour minute arrivé

    complexite += 6 ;
    int tDepart = hd * 60 + md; //tDepart en minutes donc heure*60
    int tArrivee = ha * 60 + ma;//tArrivee en minutes donc heure*60

    complexite += 1 ;
    if (tArrivee < tDepart) // Passage de minuit
    {
        complexite += 2 ;
        tArrivee += 24 * 60; // On ajoute 24 heures en minutes
    }
    complexite += 5 ;
    cout_bus += ((tArrivee - tDepart + 59) / 60) * 50; // On ajoute 59 pour arrondir au supérieur

    complexite += 1 ;
    int i = 0;
    while (i < trajet.nb_passager)//calcule de la somme du coût des billets
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

int compare_horaire(char *h1, char *h2)
{
    complexite +=7;
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

    complexite +=1;
    for (int i = 0; i < n - 1; i++)
    {
        complexite +=3;

        int j_mini = i;
        complexite +=1;

        complexite +=2;
        for (int j = i + 1; j < n; j++)
        {
            complexite +=2;

            complexite +=11;
            if (compare_horaire(ltrajet[s_trajet[j]].horaireDepart, trajetCible.horaireDepart) < compare_horaire(ltrajet[s_trajet[j_mini]].horaireDepart, trajetCible.horaireDepart)
            && compare_date(ltrajet[s_trajet[j]].dateDepart, trajetCible.dateDepart) < compare_date(ltrajet[s_trajet[j_mini]].dateDepart, trajetCible.dateDepart))
            {
                complexite +=1;
                j_mini = j;
            }
        }
        complexite +=1;

        complexite +=6;
        temp = s_trajet[i];
        s_trajet[i] = s_trajet[j_mini];
        s_trajet[j_mini] = temp;
    }
    complexite +=2;
}

int filtrerTrajetsIdentiques(int nb, Trajet *lTrajet, int *indices_trajets_identiques, Trajet trajetRef)
{
    complexite +=1;
    int x = 0;

    complexite +=1;
    for (int j = 0; j < nb; j++)
    {
        complexite +=1;


        char lVilleArriver_tmp[50];
        char lVilleDepart_tmp[50];
        char villeArrivee_tmp[50];
        char villeDepart_tmp[50];

        complexite +=2;

        copie_str(lVilleArriver_tmp, lTrajet[j].villeArrivee);
        copie_str(lVilleDepart_tmp, lTrajet[j].villeDepart);
        copie_str(villeArrivee_tmp, trajetRef.villeArrivee);
        copie_str(villeDepart_tmp, trajetRef.villeDepart);
        upper(lVilleArriver_tmp);
        upper(lVilleDepart_tmp);
        upper(villeArrivee_tmp);
        upper(villeDepart_tmp);
        complexite +=3;
        if (str_cmp(lVilleArriver_tmp, villeArrivee_tmp) == 0 && str_cmp(lVilleDepart_tmp, villeDepart_tmp) == 0)
        {
            complexite +=3;
            indices_trajets_identiques[x] = j;
            x++;
        }
    }
    complexite +=1;
    return x;
}

void reatribution(Trajet wait[], Trajet *ltrajet, int nb_pass, int nb)
{
    complexite +=1;
    int no_attribute = 0;
    complexite +=1;
    for (int i = 0; i < nb_pass; i++)
    {
        complexite +=2;
        // Tri des passagers de ce trajet par prix de billet décroissant

        complexite +=1;
        for (int j = 0; j < wait[i].nb_passager - 1; j++)
        {
            complexite +=4;

            complexite +=2;
            for (int k = j + 1; k < wait[i].nb_passager; k++)
            {
                complexite +=3;

                complexite +=5;
                if (wait[i].listePassagers[j].prixbillet < wait[i].listePassagers[k].prixbillet)
                {
                    complexite +=11;
                    Passager temp = wait[i].listePassagers[j];
                    wait[i].listePassagers[j] = wait[i].listePassagers[k];
                    wait[i].listePassagers[k] = temp;
                }
            }
            complexite +=2;
        }
        complexite +=3;

        complexite +=4;
        int indices_trajets_identiques[nb];
        int nb_trajets_identiques = filtrerTrajetsIdentiques(nb, ltrajet, indices_trajets_identiques, wait[i]);

        tri_selection_horaire(nb, nb_trajets_identiques, ltrajet, indices_trajets_identiques, wait[i]);

        complexite +=1;
        for (int p = 0; p < wait[i].nb_passager; p++)
        {
            complexite +=3;

            complexite +=4;
            Passager current_passager = wait[i].listePassagers[p];
            int passager_attribue = 0;

            complexite +=1;
            for (int j = 0; j < nb_trajets_identiques && !passager_attribue; j++)
            {
                complexite +=4;

                complexite +=2;
                int idx = indices_trajets_identiques[j];
                complexite +=2;
                if (ltrajet[idx].nb_passager < 55)
                {
                    complexite +=12;
                    int k = ltrajet[idx].nb_passager;
                    ltrajet[idx].listePassagers[k] = current_passager;
                    ltrajet[idx].listePassagers[k].id = k + 1;
                    ltrajet[idx].nb_passager++;
                    passager_attribue = 1;
                }
            }
            complexite +=3;

            complexite +=1;
            if (!passager_attribue){
                complexite+=1;
                no_attribute++;
            }
        }
        complexite +=2;
    }
    complexite +=1;
    printf("%d passagers n'ont pas pus etre réatribuer et on été perdus\n", no_attribute);
}

