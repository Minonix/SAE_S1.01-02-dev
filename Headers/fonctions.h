#ifndef FONCTIONS_H_INCLUDED
#define FONCTIONS_H_INCLUDED

typedef struct {
    int id;
    char nom[50];
    double prixbillet;
} Passager;

typedef struct {
    int numbus;
    char villeDepart[50];
    char villeArrivee[50];
    char dateDepart[11];
    char horaireDepart[5];
    char horaireArrivee[5];
    Passager listePassagers[55];
} Trajet ;

// 1.l’affichage de tous les trajets prévus (villes de départ et d’arrivée, dates et horaires de départ et d’arrivée)
void afficherTrajet(Trajet trajet);

// 2. à partir du numéro d’un bus, l’affichage de toutes les informations sur le trajet (villes de départ et
// d’arrivée, dates et horaires de départ et d’arrivée, liste des clients)
void afficheInfoTrajet(Trajet trajet, int numbus);

// 3. l’affichage de tous les trajets triés par ville de départ et par date de départ
void afficheTrajetTriés(Trajet trajet);

// 4. à partir du numéro d’un bus, ajout et suppression de clients
void ajoutSupprClients(Trajet trajet, int numbus);

// 5. à partir du numéro d’un bus et de numéro (id) d’un client, modification ou ajout du nom du client ou du prix de son billet
void modificationClients(Trajet trajet, int numbus, int idClient);

// 6. la sauvegarde des données dans un fichier (mise à jour du fichier ou création d’un nouveau fichier)
void sauvegardeDonnees(Trajet trajet);

// 7. un filtre sur les trajets partant d’une ville, partant à une date, arrivant le lendemain
void filtreTrajets1(Trajet trajet, char ville[50], char dateDepart[11]);

// 8. un filtre sur les trajets combinant ville de départ, ville d’arrivée et date de départ
void filtreTrajets2(Trajet trajet, char ville[50], char dateDepart[11], char horaireDepart[5]);

// 9. l’affichage des trajets triés par chiffre d’affaires (différence entre les prix des billets payés par les
// passagers et le coût du trajet supporté par l’entreprise), avec affichage de ce chiffre d’affaires
void affichageTrajetTriésCA(Trajet trajet);

// 10. la possibilité de supprimer tous les bus avec un chiffre d’affaires négatif, en répartissant les passagers sur les trajets identiques,
// en priorisant les passagers ayant payé le plus sur les dates et horaires les plus proches du trajet initial. Il faudra indiquer le gain généré par cette opération
void supprBusCANegatif(Trajet trajet, int numbus);

#endif // FONCTIONS_H_INCLUDED
