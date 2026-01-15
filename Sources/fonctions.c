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
    char villetmp[50];

    for (int i = 0; i < n; i++)
    {
        copie_str(villetmp, lTrajet[i].villeDepart);
        upper(villetmp); // Pour ignorer la casse
        upper(ville);
        if (compare_date(lTrajet[i].dateDepart, dateDepart) == 0) // On filtre les trajets sur leurs dates de départs
        {
            if (str_cmp(lTrajet[i].horaireArrivee, lTrajet[i].horaireDepart) <= 0) // On les refiltres sur les horaires, il doit partir un jour et
            {                                                                      // arriver le lendemain
                if (str_cmp(villetmp, ville) == 0) //Les villes sont les mêmes sans prendre en compte la casse
                {
                    lTrajet_filtre[j] = lTrajet[i]; //On sélectionne le Trajet, donc on le met dans lTrajet_filtre
                    j++;                            //La taille de lTrajet_filtre augmente
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
        char lVilleArriver_tmp[50];
        char lVilleDepart_tmp[50];
        char villeArrivee_tmp[50];
        char villeDepart_tmp[50];

        copie_str(lVilleArriver_tmp, lTrajet[i].villeArrivee);
        copie_str(lVilleDepart_tmp, lTrajet[i].villeDepart);
        copie_str(villeArrivee_tmp, villeArrivee);
        copie_str(villeDepart_tmp, villeDepart);
        upper(lVilleArriver_tmp);
        upper(lVilleDepart_tmp);
        upper(villeArrivee_tmp);
        upper(villeDepart_tmp);
        if (str_cmp(lVilleArriver_tmp, villeArrivee_tmp) == 0 && str_cmp(lVilleDepart_tmp, villeDepart_tmp) == 0 && compare_date(lTrajet[i].dateDepart, dateDepart) == 0)
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

// TODO: fonction a faire
//  10. la possibilité de supprimer tous les bus avec un chiffre d’affaires négatif, en répartissant les passagers
//  sur les trajets identiques, en priorisant les passagers ayant payé le plus sur les dates et horaires les plus
//  proches du trajet initial. Il faudra indiquer le gain généré par cette opération

int supprBusCANegatif(int nb, Trajet ltrajet[])
{
    int nb_removed = 0;
    int write_idx = 0;
    double gl_ca_1 = 0;
    double gl_ca_2 = 0;
    Trajet wait[nb];

    for (int i = 0; i < nb; i++)
    {
        double ca = calcule_ca(ltrajet[i]);
        gl_ca_1 += ca;
        if (ca < 0)
        {
            wait[nb_removed] = ltrajet[i];
            nb_removed++;
        }
        else
        {
            if (write_idx != i)
            {
                ltrajet[write_idx] = ltrajet[i];
            }
            write_idx++;
        }
    }

    printf("Trajets avec CA négatif supprimés : %d\n", nb_removed);
    for (int i = 0; i < nb_removed; i++) afficherTrajet(wait[i]);

    reatribution(wait, ltrajet, nb_removed, write_idx);

    for (int i = 0; i < nb; i++) gl_ca_2 += calcule_ca(ltrajet[i]);

    printf("cette modification à eux un bénéfice ou un couts de : %.2lf\n", gl_ca_2 - gl_ca_1);
    return write_idx;
}
