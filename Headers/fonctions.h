#ifndef FONCTIONS_H_INCLUDED
#define FONCTIONS_H_INCLUDED


typedef struct {
    int id;
    char nom[50];
    double prixbillet;
} Passager;

typedef struct {
    int jour;
    int mois;
    int annee;
}Date;

typedef struct {
    int numbus;
    char villeDepart[50];
    char villeArrivee[50];
    Date dateDepart;
    char horaireDepart[5];
    char horaireArrivee[5];
    int nb_passager;
    Passager listePassagers[56];
} Trajet ;


/*
Parametres : c1, c2 deux pointeurs vers une chaine de caractere.
Pre-condition : c1 doit être de la même taille ou plus grande que c2
Post_condition : Copie la chaine c2 dans la chaine c1
*/
void copie_str(char* c1, char* c2);

int str_cmp(char* ch1, char* ch2);

/**
* entrées d1, d2: Date
* sortie avant: int
* post-cond: avant vaut 1 si d1 ≤ d2. Sinon, avant vaut 0.
*/
int est_avant(Date d1, Date d2);

void tri_selection_indirect(int n, Trajet lTrajet[n], int T[n]);

void afficherTrajet(Trajet lTrajet);

/* 1
Parametres : nb un int, lTrajet un tableau de nb éléments contennant des struct Trajet
Pré-condition : aucune
Post-condition : L’affichage de tous les trajets prévus (villes de départ et d’arrivée, dates et horaires de départ et d’arrivée)
*/
void afficherNTrajet(int nb, Trajet lTrajet[nb]);

// 2. à partir du numéro d’un bus, l’affichage de toutes les informations sur le trajet (villes de départ et
// d’arrivée, dates et horaires de départ et d’arrivée, liste des clients)
void afficheInfoTrajet(int nb, Trajet trajet[nb], int numbus);

// 3. l’affichage de tous les trajets triés par ville de départ et par date de départ
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
void modificationClients(int nb, Trajet* lTrajet, int numbus, Passager client);

// 6. la sauvegarde des données dans un fichier (mise à jour du fichier ou création d’un nouveau fichier)
void sauvegardeDonnees(int nb, Trajet trajet[nb], char *name);

// 7. un filtre sur les trajets partant d’une ville, partant à une date, arrivant le lendemain
void filtreTrajets1(Trajet trajet, char ville[50], char dateDepart[11]);

// 8. un filtre sur les trajets combinant ville de départ, ville d’arrivée et date de départ
void filtreTrajets2(Trajet trajet, char ville[50], char dateDepart[11], char horaireDepart[5]);

// 9. l’affichage des trajets triés par chiffre d’affaires (différence entre les prix des billets payés par les
// passagers et le coût du trajet supporté par l’entreprise), avec affichage de ce chiffre d’affaires
void affichageTrajetTriesCA(Trajet trajet);

// 10. la possibilité de supprimer tous les bus avec un chiffre d’affaires négatif, en répartissant les passagers sur les trajets identiques,
// en priorisant les passagers ayant payé le plus sur les dates et horaires les plus proches du trajet initial. Il faudra indiquer le gain généré par cette opération
void supprBusCANegatif(Trajet trajet, int numbus);

#endif // FONCTIONS_H_INCLUDED
