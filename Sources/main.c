#include "../Headers/fonctions.h"
#include "../Headers/outils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int count_lines(char *chemin);
void parsec(char *chemin, int nb, Trajet fichier[nb]);
char *extraire_token(char *src, char *dest, char separateur);
void parsec_date(char *date, Trajet *trajet);

// --- MAIN ---
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("ERROR : nombre d'arguments incohérant.\n");
        return (1);
    }
    char chemin[50];
    copie_str(chemin, argv[1]);
    int nb_l = count_lines(chemin);

    if (nb_l <= 0)
    {
        printf("Fichier vide ou introuvable.\n");
        return 1;
    }

    Trajet fichier[nb_l];

    // DEBUT MAIN
    parsec(chemin, nb_l, fichier);
    int choix = 1;
    while (choix)
    {
        system("clear");
        printf("\n1 - Affichage des trajets\n");
        printf("2 - Affichage des informations sur un trajet particulier\n");
        printf("3 - Affichage des trajets triés par ville de départ et par date de départ\n");
        printf("4 - Ajout et suppression de clients à partir du numéro d’un bus\n");
        printf("5 - Modification ou ajout du nom du client ou du prix de son billet à partir du numéro d’un bus et de numéro (id) d’un client\n");
        printf("6 - Sauvegarder les données dans un fichier\n");
        printf("7 - Filtrage des trajets partant d’une ville, partant à une date, arrivant le lendemain\n");
        printf("8 - Filtrage des trajets combinant ville de départ, ville d’arrivée et date de départ\n");
        printf("9 - Affichage des trajets triés par chiffre d’affaires\n");
        printf("10 - Supprimer tous les bus avec un chiffre d’affaires négatif\n");
        printf("0 - Quitter\n");

        printf("Entrer votre choix : ");
        scanf("%d", &choix);

        if (choix == 1)
        {
            afficherNTrajet(nb_l, fichier);
        }
        else if (choix == 2)
        {
            int numbus_recherche;
            printf("Entrez le numéro du bus à afficher : ");
            scanf("%d", &numbus_recherche);
            afficheInfoTrajet(nb_l, fichier, numbus_recherche);
        }
        else if (choix == 3)
        {
            afficherTrajetTrie(nb_l, fichier);
        }
        else if (choix == 4)
        {
            int numbus_mod;
            Passager p_new_or_not;
            printf("Entrez le numéro du bus : ");
            scanf("%d", &numbus_mod);
            printf("Entrez le nom du passager (pour ajouter ou supprimer) : ");
            scanf("%s", p_new_or_not.nom);
            // L'ID et le prix du billet ne sont pas pertinents pour l'ajout/suppression par nom
            p_new_or_not.id = 0;
            p_new_or_not.prixbillet = 0.0;
            ajoutSupprClients(nb_l, fichier, numbus_mod, p_new_or_not);
        }
        else if (choix == 5)
        {
            int numbus_mod;
            Passager client_mod;
            printf("Entrez le numéro du bus : ");
            scanf("%d", &numbus_mod);
            printf("Entrez l'ID du client à modifier/ajouter : ");
            scanf("%d", &client_mod.id);
            printf("Entrez le nouveau nom du client : ");
            scanf("%s", client_mod.nom);
            printf("Entrez le nouveau prix du billet du client : ");
            scanf("%lf", &client_mod.prixbillet);
            modificationClients(nb_l, fichier, numbus_mod, client_mod);
        }
        else if (choix == 6)
        {
            char nom_fichier_sauvegarde[50];
            printf("Entrez le nom du fichier de sauvegarde (ex: sauvegarde.csv) : ");
            scanf("%s", nom_fichier_sauvegarde);
            sauvegardeDonnees(nb_l, fichier, nom_fichier_sauvegarde);
        }
        else if (choix == 7)
        {
            char ville_filtre[50];
            Date date_filtre;
            Trajet trajets_filtres[nb_l];
            int nb_filtres;

            printf("Entrez la ville de départ pour le filtre : ");
            scanf("%s", ville_filtre);
            printf("Entrez le jour de départ (JJ) : ");
            scanf("%d", &date_filtre.jour);
            printf("Entrez le mois de départ (MM) : ");
            scanf("%d", &date_filtre.mois);
            printf("Entrez l'année de départ (AAAA) : ");
            scanf("%d", &date_filtre.annee);

            nb_filtres = filtreTrajets1(nb_l, fichier, trajets_filtres, ville_filtre, date_filtre);
            printf("Trajets filtrés (partant de %s, le %02d/%02d/%04d, arrivant le lendemain) :\n", ville_filtre, date_filtre.jour, date_filtre.mois, date_filtre.annee);
            for (int i = 0; i < nb_filtres; i++)
            {
                afficherTrajet(trajets_filtres[i]);
            }
        }
        else if (choix == 8)
        {
            char ville_depart_filtre[50];
            char ville_arrivee_filtre[50];
            Date date_filtre;
            Trajet trajets_filtres[nb_l];
            int nb_filtres;

            printf("Entrez la ville de départ pour le filtre : ");
            scanf("%s", ville_depart_filtre);
            printf("Entrez la ville d'arrivée pour le filtre : ");
            scanf("%s", ville_arrivee_filtre);
            printf("Entrez le jour de départ (JJ) : ");
            scanf("%d", &date_filtre.jour);
            printf("Entrez le mois de départ (MM) : ");
            scanf("%d", &date_filtre.mois);
            printf("Entrez l'année de départ (AAAA) : ");
            scanf("%d", &date_filtre.annee);

            nb_filtres = filtreTrajets2(nb_l, fichier, trajets_filtres, ville_depart_filtre, ville_arrivee_filtre, date_filtre);
            printf("Trajets filtrés (départ %s, arrivée %s, le %02d/%02d/%04d) :\n", ville_depart_filtre, ville_arrivee_filtre, date_filtre.jour, date_filtre.mois, date_filtre.annee);
            for (int i = 0; i < nb_filtres; i++)
            {
                afficherTrajet(trajets_filtres[i]);
            }
        }
        else if (choix == 9)
        {
            affichageTrajetTriesCA(nb_l, fichier);
        }
        else if (choix == 10)
        {
            supprBusCANegatif(nb_l, fichier); // Cette fonction nécessite une implémentation plus complexe
        }
        else if (choix == 777) {
            //zone de test
            printf("--- Test de tri_selection_horaire ---\n");

            // Création de trajets de test
            Trajet testTrajets[5];
            int nbTestTrajets = 5;

            // Trajet de référence
            Trajet refTrajet;
            copie_str(refTrajet.villeDepart, "Paris");
            copie_str(refTrajet.villeArrivee, "Lyon");
            refTrajet.dateDepart.jour = 10;
            refTrajet.dateDepart.mois = 5;
            refTrajet.dateDepart.annee = 2024;
            copie_str(refTrajet.horaireDepart, "12:00");

            // Trajet 0: Identique à la référence, même date, même heure
            copie_str(testTrajets[0].villeDepart, "Paris");
            copie_str(testTrajets[0].villeArrivee, "Lyon");
            testTrajets[0].dateDepart.jour = 10;
            testTrajets[0].dateDepart.mois = 5;
            testTrajets[0].dateDepart.annee = 2024;
            copie_str(testTrajets[0].horaireDepart, "12:00");

            // Trajet 1: Identique à la référence, même date, heure plus tard
            copie_str(testTrajets[1].villeDepart, "Paris");
            copie_str(testTrajets[1].villeArrivee, "Lyon");
            testTrajets[1].dateDepart.jour = 10;
            testTrajets[1].dateDepart.mois = 5;
            testTrajets[1].dateDepart.annee = 2024;
            copie_str(testTrajets[1].horaireDepart, "14:30");

            // Trajet 2: Identique à la référence, date plus tard, heure plus tôt
            copie_str(testTrajets[2].villeDepart, "Paris");
            copie_str(testTrajets[2].villeArrivee, "Lyon");
            testTrajets[2].dateDepart.jour = 11;
            testTrajets[2].dateDepart.mois = 5;
            testTrajets[2].dateDepart.annee = 2024;
            copie_str(testTrajets[2].horaireDepart, "1000");

            // Trajet 3: Identique à la référence, date plus tôt, heure plus tard
            copie_str(testTrajets[3].villeDepart, "Paris");
            copie_str(testTrajets[3].villeArrivee, "Lyon");
            testTrajets[3].dateDepart.jour = 9;
            testTrajets[3].dateDepart.mois = 5;
            testTrajets[3].dateDepart.annee = 2024;
            copie_str(testTrajets[3].horaireDepart, "1300");

            // Trajet 4: Identique à la référence, même date, heure plus tôt
            copie_str(testTrajets[4].villeDepart, "Paris");
            copie_str(testTrajets[4].villeArrivee, "Lyon");
            testTrajets[4].dateDepart.jour = 10;
            testTrajets[4].dateDepart.mois = 5;
            testTrajets[4].dateDepart.annee = 2024;
            copie_str(testTrajets[4].horaireDepart, "1100");

            int indices_identiques[5] = {0, 1, 2, 3, 4}; // Tous les trajets sont "identiques" pour ce test
            tri_selection_horaire(nbTestTrajets, nbTestTrajets, testTrajets, indices_identiques, refTrajet);

            printf("Ordre des trajets après tri (indices) :\n");
            for (int i = 0; i < nbTestTrajets; i++) {
                printf("Indice %d: ", indices_identiques[i]);
                afficherTrajet(testTrajets[indices_identiques[i]]);
            }
        }
        else if (choix != 0){
            printf("Argument non attendus.");
        }

        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        if (choix != 0)
        {
            printf("\nAppuyez sur Entrée pour revenir au menu...");
            while ((c = getchar()) != '\n' && c != EOF);
        }
    }

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
