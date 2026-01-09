#include "../Headers/fonctions.h"
#include "../Headers/outils.h"
#include <stdio.h>


long long complexite ;

// 1
void afficherNTrajet(int nb, Trajet lTrajet[nb])
{

    complexite = 0;

    printf("Voici la liste de tout les trajets : \n");

    complexite += 1 ;
    for (int i = 0; i < nb; i++)
    { // Parcours de tout les trajets.
        complexite += 2 ;

        complexite += 2 ;
        if (lTrajet[i].numbus != 0)
        {
            complexite += 7 ;
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
    complexite += 2 ;
}

// 2. à partir du numéro d’un bus, l’affichage de toutes les informations sur le trajet (villes de départ et
// d’arrivée, dates et horaires de départ et d’arrivée, liste des clients)
void afficheInfoTrajet(int nb, Trajet trajet[nb], int numbus)
{
    complexite = 0 ;

    complexite += 1 ;
    for (int i = 0; i < nb; i++)
    {
        complexite += 2 ;

        complexite += 2 ;
        if (trajet[i].numbus == numbus)
        {
            afficherTrajet(trajet[i]);
            return;
        }
    }
    complexite += 2 ;
    printf("aucun trajet n'a été trouver\n");
}

// 3. l’affichage de tous les trajets triés par ville de départ et par date de départ
void afficherTrajetTrie(int nb, Trajet lTrajet[nb])
{
    complexite = 0 ;

    complexite += 1 ;
    int T[nb];

    complexite += 1 ;
    for (int i = 0; i < nb; i++){
        complexite += 4 ;
        T[i] = i;
    }
    complexite += 2 ;

    tri_selection_indirect(nb, lTrajet, T);

    complexite += 1 ;
    for (int i = 0; i < nb; i++)
    {
        complexite += 2 ;

        complexite += 2 ;
        if (lTrajet[i].numbus != 0)
        {
            complexite += 14 ;
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
    complexite += 2 ;
}

// 4. à partir du numéro d’un bus, ajout et suppression de clients
/**
 * l'id n'a pas d'incidence, le nom est sensible a la casse
 */
void ajoutSupprClients(int nb, Trajet trajet[nb], int numbus, Passager new_or_not)
{
    complexite = 0 ;

    int a = 0;
    complexite += 2 ;

    for (int i = 0; i < nb; i++)
    {
        complexite += 2 ;

        complexite += 2 ;
        if (trajet[i].numbus == numbus)
        { // une fois le bon trajet trouver
            complexite += 1 ;
            for (int y = 0; y < trajet[i].nb_passager; y++)
            { // on parcours tout les passager
                complexite += 3 ;

                complexite += 3 ;
                if (str_cmp(trajet[i].listePassagers[y].nom, new_or_not.nom) == 0){
                    a = 1; // si le nom du passager est le meme
                    complexite += 1 ;
                }
                if (a)
                {
                    complexite += 9 ;
                    trajet[i].listePassagers[y] = trajet[i].listePassagers[y + 1]; // si un passager a été trouver alors on le remplace par le prochian passager
                    trajet[i].listePassagers[y].id -= 1;
                }
            }
            complexite += 2 ;
            if (a)
            {
                complexite += 2 ;
                trajet[i].nb_passager--;
                printf("passager retirer");
            }
            else
            {
                complexite += 8 ;
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
    complexite = 0 ;

    int trouve = 0; // si un client est trouvé pour un trajet donné.
    complexite += 2 ;
    for (int i = 0; i < nb && !trouve; i++)
    { // On cherche le bus ayant pour numéro bus nBus // debut for1
        complexite += 4 ;
        complexite += 2 ;
        if (lTrajet[i].numbus == nBus)
        { // On le trouve
            int j;
            complexite += 1 ;
            for (j = 0; j < 56 && lTrajet[i].listePassagers[j].nom[0] != 0 && !trouve; j++)
            { // On cherche le passager // debut for2
                complexite += 9 ;

                complexite += 3 ;
                if (lTrajet[i].listePassagers[j].id == client.id)
                {
                    complexite += 6 ;
                    // On le trouve
                    copie_str(lTrajet[i].listePassagers[j].nom, client.nom);     // On change son nom par le nouveau nom qui peut être identifique au premier
                    lTrajet[i].listePassagers[j].prixbillet = client.prixbillet; // On change le prix de son billet
                    trouve = 1;
                } // On a fait ce que l'on voulait faire, le peut se terminer.
            } // fin for2
            complexite += 8 ;

            complexite += 1 ;
            if (!trouve)
            {
                complexite += 1 ;
                if (j > 55)
                {
                    complexite += 1 ;
                    printf("Le bus %d est complet.\n", lTrajet[i].numbus);
                }
                else
                {
                    complexite += 3 ;
                    lTrajet[i].listePassagers[j] = client;
                }
                complexite += 1 ;
                trouve = 1;
            } // fin if

        } // fin if
    } // fin for1
    complexite += 3 ;
    complexite += 1 ;
    if (!trouve)
        printf("Le bus %d n'existe pas\n", nBus);
}

// 6. la sauvegarde des données dans un fichier (mise à jour du fichier ou création d’un nouveau fichier)
void sauvegardeDonnees(int nb, Trajet trajet[nb], char *name)
{
    complexite = 0;
    FILE *f = fopen(name, "w");

    complexite += 1;
    if (!f)
        return;

    complexite += 1;
    for (int i = 0; i < nb; i++)
    {
        complexite += 2;


        complexite += 8;
        fprintf(f, "%d,%s,%s,%02d/%02d/%02d,%s,%s,",
                trajet[i].numbus,
                trajet[i].villeDepart,
                trajet[i].villeArrivee,
                trajet[i].dateDepart.jour,
                trajet[i].dateDepart.mois,
                trajet[i].dateDepart.annee,
                trajet[i].horaireDepart,
                trajet[i].horaireArrivee);
        complexite += 1;
        for (int p = 0; p < trajet[i].nb_passager; p++)
        {
            complexite += 3;
            fprintf(f, "%d:%s:%.2f",
                    trajet[i].listePassagers[p].id,
                    trajet[i].listePassagers[p].nom,
                    trajet[i].listePassagers[p].prixbillet);
            complexite += 9;
            if (p < trajet[i].nb_passager - 1)
            {
                fprintf(f, ",");
            }
        }
        complexite += 2;
        fprintf(f, "\n");
    }
    complexite += 1;
    printf("sauvgarde effectuer \n");
    fclose(f);
}

// 7. un filtre sur les trajets partant d’une ville, partant à une date, arrivant le lendemain
int filtreTrajets1(int n, Trajet *lTrajet, Trajet *lTrajet_filtre, char ville[50], Date dateDepart)
{
    complexite = 0;

    int j = 0;
    complexite += 1;
    for (int i = 0; i < n; i++)
    {
        complexite += 2;

        complexite += 2;
        if (compare_date(lTrajet[i].dateDepart, dateDepart) == 2)
        {
            complexite += 3;
            if (str_cmp(lTrajet[i].horaireArrivee, lTrajet[i].horaireDepart) <= 0)
            {
                complexite += 2;
                if (str_cmp(lTrajet[i].villeDepart, ville) == 0)
                {
                    complexite += 4;
                    lTrajet_filtre[j] = lTrajet[i];
                    j++;
                }
            }
        }
    }
    complexite += 1;
    return j;
}

// 8. un filtre sur les trajets combinant ville de départ, ville d’arrivée et date de départ
int filtreTrajets2(int n, Trajet *lTrajet, Trajet *lTrajet_filtre, char villeDepart[50], char villeArrivee[50], Date dateDepart)
{
    complexite = 0;

    int j = 0;
    complexite += 2;
    for (int i = 0; i < n; i++)
    {
        complexite += 2;

        complexite += 8;
        if (str_cmp(lTrajet[i].horaireArrivee, villeArrivee) == 0
        && str_cmp(lTrajet[i].horaireArrivee, villeDepart) == 0
        && compare_date(lTrajet[i].dateDepart, dateDepart) == 2)
        {
            complexite += 4;
            lTrajet_filtre[j] = lTrajet[i];
            j++;
        }
    }
    complexite += 1;
    return j;
}

// 9. l’affichage des trajets triés par chiffre d’affaires (différence entre les prix des billets payés par les
// passagers et le coût du trajet supporté par l’entreprise), avec affichage de ce chiffre d’affaires
void affichageTrajetTriesCA(int nb, Trajet *lTrajet)
{
    complexite += 0;

    complexite += 2;
    int T[nb];
    double tCa[nb];

    complexite += 1;
    for (int i = 0; i < nb; i++)
    {
        complexite += 2;
        complexite += 5;
        T[i] = i;
        tCa[i] = calcule_ca(lTrajet[i]);
    }
    complexite += 1;

    tri_selection_indirect_ca(nb, T, tCa);
    complexite += 1;
    for (int i = 0; i < nb; i++)
    {
        complexite += 2;
        complexite += 3;
        if (lTrajet[T[i]].numbus != 0)
        {
            complexite += 12;
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
            complexite += 7;
            if (tCa[T[i]] == -99999.99)
            {
                printf("CA INCONNU");
            }
            else{
                complexite += 2;
                printf("%8.2lf", tCa[T[i]]);
            }
            printf("\n");
        }
    }
    complexite += 1;
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