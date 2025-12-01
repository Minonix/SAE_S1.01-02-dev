#include "../Headers/fonctions.h"
#include <stdio.h>




void copie_str(char* c1, char* c2){
    int i=0;
    for (i=0; c2[i]!=0; i++){
        c1[i] = c2[i];
    }
    c1[i] = 0;
}


//1
void afficherTrajet(int nb, Trajet lTrajet[nb]){
    printf("Voici la liste de tout les trajets : \n");
    for (int i=0; i<nb; i++) {  //Parcours de tout les trajets.
            printf("Ville de départ : %s ; Ville d'arrivée : %s ; Date de départ : %s ; Horaire de Départ : %s ; Horaire d'arrivée : %s", // affichage des trajets
            lTrajet[i].villeDepart, lTrajet[i].villeArrivee, lTrajet[i].dateDepart, lTrajet[i].horaireDepart, lTrajet[i].horaireArrivee);
    }
}

// 2. à partir du numéro d’un bus, l’affichage de toutes les informations sur le trajet (villes de départ et
// d’arrivée, dates et horaires de départ et d’arrivée, liste des clients)

// 3. l’affichage de tous les trajets triés par ville de départ et par date de départ

// 4. à partir du numéro d’un bus, ajout et suppression de clients


// 5
void modificationClients(int nb, Trajet* lTrajet, int nBus, Passager client ){
    int trouve = 0; // si un client est trouvé pour un trajet donné.
    for (int i=0; i<nb && !trouve; i++){ // On cherche le bus ayant pour numéro bus nBus
        if (lTrajet[i].numbus == nBus){ //On le trouve
            int j;
            for (j=0; j<55 && lTrajet[i].listePassagers[j].nom[0]!=0 && !trouve; j++){ // On cherche le passager
                if (lTrajet[i].listePassagers[j].id == client.id){ // On le trouve
                    copie_str(lTrajet[i].listePassagers[j].nom, client.nom); // On change son nom par le nouveau nom qui peut être identifique au premier
                    lTrajet[i].listePassagers[j].prixbillet = client.prixbillet; // On change le prix de son billet
                    trouve = 1;} // On a fait ce que l'on voulait faire, le programme vas donc s'arreter.
            } // fin for
            if (!trouve){
                if (j>54){
                    printf("Le bus %d est complet.", lTrajet[i].numbus);}
                else{
                    lTrajet[i].listePassagers[j] = client ;}
                trouve = 1;
            } // fin if

        } //fin if
    } // fin for
    if (!trouve)printf("Le bus %d n'existe pas", nBus);
}


// 6. la sauvegarde des données dans un fichier (mise à jour du fichier ou création d’un nouveau fichier)

// 7. un filtre sur les trajets partant d’une ville, partant à une date, arrivant le lendemain

// 8. un filtre sur les trajets combinant ville de départ, ville d’arrivée et date de départ

// 9. l’affichage des trajets triés par chiffre d’affaires (différence entre les prix des billets payés par les
// passagers et le coût du trajet supporté par l’entreprise), avec affichage de ce chiffre d’affaires

// 10. la possibilité de supprimer tous les bus avec un chiffre d’affaires négatif, en répartissant les passagers
// sur les trajets identiques, en priorisant les passagers ayant payé le plus sur les dates et horaires les plus
// proches du trajet initial. Il faudra indiquer le gain généré par cette opération
