#include "../Headers/fonctions.h"
#include "../Headers/outils.h"
#include <stdio.h>

// 1
void afficherNTrajet(int nb, Trajet lTrajet[nb])
{
    printf("Voici la liste de tout les trajets : \n");
    for (int i = 0; i < nb; i++)
    { // Parcours de tout les trajets.
        if (lTrajet[i].numbus != 0)
        {
            printf("Ville de départ : %17s | Ville d'arrivée : %17s | Date de départ : %02d/%02d/%4d | ", lTrajet[i].villeDepart, lTrajet[i].villeArrivee,
                   lTrajet[i].dateDepart.jour, lTrajet[i].dateDepart.mois, lTrajet[i].dateDepart.annee);
            printf("Horaire de départ : ");
            afficherhoraire(lTrajet[i].horaireDepart);
            printf(" | ");
            printf("Horaire d'arrivée : ");

            afficherhoraire(lTrajet[i].horaireArrivee);
            printf("\n");
        }
    }
}

// 2. à partir du numéro d’un bus, l’affichage de toutes les informations sur le trajet (villes de départ et
// d’arrivée, dates et horaires de départ et d’arrivée, liste des clients)
void afficheInfoTrajet(int nb, Trajet trajet[nb], int numbus)
{
    for (int i = 0; i < nb; i++)
    {
        if (trajet[i].numbus == numbus)
        {
            afficherTrajet(trajet[i]);
            return;
        }
    }
    printf("aucun trajet n'a été trouver\n");
}

// 3. l’affichage de tous les trajets triés par ville de départ et par date de départ
void afficherTrajetTrie(int nb, Trajet lTrajet[nb])
{
    int T[nb];
    for (int i = 0; i < nb; i++)
        T[i] = i;

    tri_selection_indirect(nb, lTrajet, T);
    for (int i = 0; i < nb; i++)
    {
        if (lTrajet[i].numbus != 0)
        {
            printf("NumBus : %d | Ville de départ : %17s | Ville d'arrivée : %17s | Date de départ : %02d/%02d/%4d | ", lTrajet[T[i]].numbus,
                   lTrajet[T[i]].villeDepart, lTrajet[T[i]].villeArrivee,
                   lTrajet[T[i]].dateDepart.jour, lTrajet[T[i]].dateDepart.mois, lTrajet[T[i]].dateDepart.annee);
            printf("Horaire de départ : ");
            afficherhoraire(lTrajet[i].horaireDepart);
            printf(" | ");
            printf("Horaire d'arrivée : ");
            afficherhoraire(lTrajet[i].horaireArrivee);
            printf("\n");
        }
    }
}

// 4. à partir du numéro d’un bus, ajout et suppression de clients
/**
 * l'id n'a pas d'incidence, le nom est sensible a la casse
 */
void ajoutSupprClients(int nb, Trajet trajet[nb], int numbus, Passager new_or_not)
{
    int a = 0;
    for (int i = 0; i < nb; i++)
    {
        if (trajet[i].numbus == numbus)
        { // une fois le bon trajet trouver
            for (int y = 0; y < trajet[i].nb_passager; y++)
            { // on parcours tout les passager
                if (str_cmp(trajet[i].listePassagers[y].nom, new_or_not.nom) == 0)
                    a = 1; // si le nom du passager est le meme
                if (a)
                {
                    trajet[i].listePassagers[y] = trajet[i].listePassagers[y + 1]; // si un passager a été trouver alors on le remplace par le prochian passager
                    trajet[i].listePassagers[y].id -= 1;
                }
            }
            if (a)
            {
                trajet[i].nb_passager--;
                printf("passager retirer");
            }
            else
            {
                trajet[i].nb_passager += 1;
                new_or_not.id = trajet[i].nb_passager; // on ajuste l'id comme étant le derner id
                trajet[i].listePassagers[trajet[i].nb_passager - 1] = new_or_not;
                printf("passager ajouter");
            }
            return;
        }
    }
    printf("pas de trajet trouver");
}

// 5
void modificationClients(int nb, Trajet *lTrajet, int nBus, Passager client)
{
    int trouve = 0; // si un client est trouvé pour un trajet donné.
    for (int i = 0; i < nb && !trouve; i++)
    { // On cherche le bus ayant pour numéro bus nBus // debut for1
        if (lTrajet[i].numbus == nBus)
        { // On le trouve
            int j;
            for (j = 0; j < 56 && lTrajet[i].listePassagers[j].nom[0] != 0 && !trouve; j++)
            { // On cherche le passager // debut for2
                if (lTrajet[i].listePassagers[j].id == client.id)
                {                                                                // On le trouve
                    copie_str(lTrajet[i].listePassagers[j].nom, client.nom);     // On change son nom par le nouveau nom qui peut être identifique au premier
                    lTrajet[i].listePassagers[j].prixbillet = client.prixbillet; // On change le prix de son billet
                    trouve = 1;
                } // On a fait ce que l'on voulait faire, le peut se terminer.
            } // fin for2
            if (!trouve)
            {
                if (j > 55)
                {
                    printf("Le bus %d est complet.\n", lTrajet[i].numbus);
                }
                else
                {
                    lTrajet[i].listePassagers[j] = client;
                }
                trouve = 1;
            } // fin if

        } // fin if
    } // fin for1
    if (!trouve)
        printf("Le bus %d n'existe pas\n", nBus);
}

// 6. la sauvegarde des données dans un fichier (mise à jour du fichier ou création d’un nouveau fichier)
void sauvegardeDonnees(int nb, Trajet trajet[nb], char *name)
{
    FILE *f = fopen(name, "w");
    if (!f)
        return;
    for (int i = 0; i < nb; i++)
    {
        fprintf(f, "%d,%s,%s,%02d/%02d/%02d,%s,%s,",
                trajet[i].numbus,
                trajet[i].villeDepart,
                trajet[i].villeArrivee,
                trajet[i].dateDepart.jour,
                trajet[i].dateDepart.mois,
                trajet[i].dateDepart.annee,
                trajet[i].horaireDepart,
                trajet[i].horaireArrivee);
        for (int p = 0; p < trajet[i].nb_passager; p++)
        {
            fprintf(f, "%d:%s:%.2f",
                    trajet[i].listePassagers[p].id,
                    trajet[i].listePassagers[p].nom,
                    trajet[i].listePassagers[p].prixbillet);
            if (p < trajet[i].nb_passager - 1)
            {
                fprintf(f, ",");
            }
        }
        fprintf(f, "\n");
    }
    printf("sauvgarde effectuer \n");
    fclose(f);
}

// 7. un filtre sur les trajets partant d’une ville, partant à une date, arrivant le lendemain
int filtreTrajets1(int n, Trajet *lTrajet, Trajet *lTrajet_filtre, char ville[50], Date dateDepart)
{
    int j = 0;
    for (int i = 0; i < n; i++)
    {
        if (compare_date(lTrajet[i].dateDepart, dateDepart) == 2)
        {
            if (str_cmp(lTrajet[i].horaireArrivee, lTrajet[i].horaireDepart) <= 0)
            {
                if (str_cmp(lTrajet[i].villeDepart, ville) == 0)
                {
                    lTrajet_filtre[j] = lTrajet[i];
                    j++;
                }
            }
        }
    }
    return j;
}

// 8. un filtre sur les trajets combinant ville de départ, ville d’arrivée et date de départ
int filtreTrajets2(int n, Trajet *lTrajet, Trajet *lTrajet_filtre, char villeDepart[50], char villeArrivee[50], Date dateDepart)
{
    int j = 0;
    for (int i = 0; i < n; i++)
    {
        if (str_cmp(lTrajet[i].horaireArrivee, villeArrivee) == 0
        && str_cmp(lTrajet[i].horaireArrivee, villeDepart) == 0
        && compare_date(lTrajet[i].dateDepart, dateDepart) == 2)
        {
            lTrajet_filtre[j] = lTrajet[i];
            j++;
        }
    }
    return j;
}

// 9. l’affichage des trajets triés par chiffre d’affaires (différence entre les prix des billets payés par les
// passagers et le coût du trajet supporté par l’entreprise), avec affichage de ce chiffre d’affaires
void affichageTrajetTriesCA(int nb, Trajet *lTrajet)
{
    int T[nb];
    double tCa[nb];
    for (int i = 0; i < nb; i++)
    {
        T[i] = i;
        tCa[i] = calcule_ca(lTrajet[i]);
    }

    tri_selection_indirect_ca(nb, T, tCa);
    for (int i = 0; i < nb; i++)
    {
        if (lTrajet[T[i]].numbus != 0)
        {
            printf("NumBus : %d | Ville de départ : %17s | Ville d'arrivée : %17s | Date de départ : %02d/%02d/%4d | ", lTrajet[T[i]].numbus,
                   lTrajet[T[i]].villeDepart, lTrajet[T[i]].villeArrivee,
                   lTrajet[T[i]].dateDepart.jour, lTrajet[T[i]].dateDepart.mois, lTrajet[T[i]].dateDepart.annee);
            printf("Horaire de départ : ");
            afficherhoraire(lTrajet[T[i]].horaireDepart);
            printf(" | ");
            printf("Horaire d'arrivée : ");
            afficherhoraire(lTrajet[T[i]].horaireArrivee);
            printf(" | ");
            printf("Chiffre d'affaire : ");
            if (tCa[T[i]] == -99999.99)
            {
                printf("CA INCONNU");
            }
            else
                printf("%8.2lf", tCa[T[i]]);
            printf("\n");
        }
    }
}


//TODO: fonction a faire
// 10. la possibilité de supprimer tous les bus avec un chiffre d’affaires négatif, en répartissant les passagers
// sur les trajets identiques, en priorisant les passagers ayant payé le plus sur les dates et horaires les plus
// proches du trajet initial. Il faudra indiquer le gain généré par cette opération

// void supprBusCANegatif(int nb, Trajet ltrajet[nb], int numbus) {
//     int dec = 0, nb_pass = 0;
//     double ca;
//     Trajet wait[nb];
//     for (int i = 0; i + dec < nb; i++) {

//         while ((ca = calcule_ca(ltrajet[i])) < 0) {
//             wait[dec] = ltrajet[i];
//             nb_pass++;
//             dec++;
//         ltrajet[i] = ltrajet[i+dec];
//     }
//     }
//     nb -= dec;
//     reatribution(wait, ltrajet, nb, nb_pass);
// }