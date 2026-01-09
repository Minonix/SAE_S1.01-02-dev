#ifndef FONCTIONS_H_INCLUDED
#define FONCTIONS_H_INCLUDED


typedef struct
{
    int id;
    char nom[50];
    double prixbillet;
} Passager;

typedef struct
{
    int jour;
    int mois;
    int annee;
} Date;

typedef struct
{
    int numbus;
    char villeDepart[50];
    char villeArrivee[50];
    Date dateDepart;
    char horaireDepart[5];
    char horaireArrivee[5];
    int nb_passager;
    Passager listePassagers[56];
} Trajet;



/* 1
Parametres : int nb , lTrajet un tableau de nb éléments contennant des struct Trajet
Pré-condition : aucune
Post-condition : L’affichage de tous les trajets prévus (villes de départ et d’arrivée, dates et horaires de départ et d’arrivée)
*/
void afficherNTrajet(int nb, Trajet lTrajet[nb]);

// 2. à partir du numéro d’un bus, l’affichage de toutes les informations sur le trajet (villes de départ et
// d’arrivée, dates et horaires de départ et d’arrivée, liste des clients)
void afficheInfoTrajet(int nb, Trajet trajet[nb], int numbus);

/* 3
Parametres: int nb, lTrajet un tableau de nb éléments contennant des struct Trajet
Pré-condition : Aucune
Post-condition : L’affichage de tous les trajets triés par ville de départ et par date de départ
*/
void afficherTrajetTrie(int nb, Trajet lTrajet[nb]);



// 4. à partir du numéro d’un bus, ajout et suppression de clients
void ajoutSupprClients(int nb, Trajet trajet[nb], int numbus, Passager new_or_not);

/* 5
Parametres : int nb ; lTrajet, un pointeur vers un tableau contennant nb élément de type Trajet ; int nBus le numéro d'un bus (de type Trajet);
             Passager Client, un client possédant un id, un nom et un prix.
Pré-condition : aucune
Post-condition : à partir d'un numéro d’un bus et du numéro (id) d’un client, modifie ou ajoute le nom du client ou/et
                 du prix de son billet
*/
void modificationClients(int nb, Trajet *lTrajet, int numbus, Passager client);

// 6. la sauvegarde des données dans un fichier (mise à jour du fichier ou création d’un nouveau fichier)
void sauvegardeDonnees(int nb, Trajet trajet[nb], char *name);

/* 7
Parametres : int n;
             Trajet *lTrajet, un pointeur vers le tableau contenant les n trajets à analyser ;
             Trajet *lTrajet_filtre, un pointeur vers le tableau de destination pour les résultats ;
             char ville[50], la ville de départ recherchée ;
             Date dateDepart, la date de départ recherchée.
Sortie : int j, le nombre de trajets ayant validé les critères et ayant été copiés dans lTrajet_filtre.
Pré-condition : n >= 0 ; lTrajet_filtre doit être de la même taille que lTrajet.
Post-condition : remplit lTrajet_filtre avec les trajets de lTrajet qui partent de la ville donnée à la date
                 indiquée, et qui arrive le lendemain.
*/
int filtreTrajets1(int n, Trajet *lTrajet, Trajet *lTrajet_filtre, char ville[50], Date dateDepart);

// 8. un filtre sur les trajets combinant ville de départ, ville d’arrivée et date de départ
int filtreTrajets2(int n, Trajet *lTrajet, Trajet *lTrajet_filtre, char villeDepart[50], char villeArrivee[50], Date dateDepart);

// 9. l’affichage des trajets triés par chiffre d’affaires (différence entre les prix des billets payés par les
// passagers et le coût du trajet supporté par l’entreprise), avec affichage de ce chiffre d’affaires
/* 9
Parametres : int nb, le nombre de trajets dans le tableau ;
             Trajet *lTrajet, un pointeur vers le tableau contenant les données des trajets.
Pré-condition : nb >= 0 ; les fonctions calcule_ca, tri_selection_indirect_ca et afficherhoraire doivent être définies.
Post-condition :Affichage des trajets triés par chiffre d’affaires (différence entre les prix des billets payés par les
                passagers et le coût du trajet supporté par l’entreprise), avec affichage de ce chiffre d’affaires.
*/
void affichageTrajetTriesCA(int nb, Trajet *lTrajet);


// 10. la possibilité de supprimer tous les bus avec un chiffre d’affaires négatif, en répartissant les passagers sur les trajets identiques,
// en priorisant les passagers ayant payé le plus sur les dates et horaires les plus proches du trajet initial. Il faudra indiquer le gain généré par cette opération
void supprBusCANegatif(Trajet trajet, int numbus);

#endif // FONCTIONS_H_INCLUDED
