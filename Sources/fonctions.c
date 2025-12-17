#include "../Headers/fonctions.h"
#include <stdio.h>




void copie_str(char* c1, char* c2){
    int i=0;
    for (i=0; c2[i]!=0; i++){
        c1[i] = c2[i];
    }
    c1[i] = 0;
}

int str_cmp(char* ch1, char* ch2){
    int i;
    for (i=0; ch1[i]!=0 && ch2[i]!=0; i++){
        if (ch1[i]>ch2[i]) return 1;
        if (ch1[i]<ch2[i]) return -1;
    }
    return ch1[i] - ch2[i];
}

int est_avant(Date d1, Date d2){
    if (d1.annee > d2.annee) return 0;
    else if (d1.annee < d2.annee) return 1;
    if (d1.mois > d2.mois) return 0;
    else if (d1.mois < d2.mois) return 1;
    if (d1.jour > d2.jour) return 0;
    return 1;
}

void tri_selection_indirect(int n, Trajet lTrajet[n], int T[n]){
    int temp ;
        for (int i = 0 ; i < n-1 ; i++) {
            int j_mini = i ;
            for (int j = i+1 ; j < n ; j++){
                if ( str_cmp(lTrajet[T[j]].villeDepart, lTrajet[T[j_mini]].villeDepart) == 0 ){
                    if (est_avant(lTrajet[T[j]].dateDepart,lTrajet[T[j_mini]].dateDepart) )
                        j_mini = j;
                }
                if  (  str_cmp(lTrajet[T[j_mini]].villeDepart,lTrajet[T[j]].villeDepart) > 0 ){
                    j_mini = j ;
                }
            }
            temp = T[i] ;
            T[i] = T[j_mini] ;
            T[j_mini] = temp ;
    }
}



//1
void afficherTrajet(int nb, Trajet lTrajet[nb]){
    printf("Voici la liste de tout les trajets : \n");
    for (int i=0; i<nb; i++) {  //Parcours de tout les trajets.
            printf("Ville de départ : %17s | Ville d'arrivée : %17s | Date de départ : %02d/%02d/%4d | ",lTrajet[i].villeDepart, lTrajet[i].villeArrivee,
                lTrajet[i].dateDepart.jour, lTrajet[i].dateDepart.mois, lTrajet[i].dateDepart.annee);
            if (lTrajet[i].horaireDepart[0] != 0) printf("Horaire de Départ : %6s | ",lTrajet[i].horaireDepart);
            else printf("Horaire de Départ : ABSENT | ");
            if (lTrajet[i].horaireArrivee[0] != 0) printf("Horaire d'arrivée : %6s\n",lTrajet[i].horaireArrivee);
            else  printf("Horaire d'arrivée : ABSENT\n");


    }
}

// 2. à partir du numéro d’un bus, l’affichage de toutes les informations sur le trajet (villes de départ et
// d’arrivée, dates et horaires de départ et d’arrivée, liste des clients)

// 3. l’affichage de tous les trajets triés par ville de départ et par date de départ
void afficherTrajetTrie(int nb, Trajet lTrajet[nb]){
    int T[nb];
    for (int i=0; i<nb; i++)T[i]=i;

    tri_selection_indirect(nb, lTrajet, T);
    for (int i=0; i<nb; i++){
        printf("Ville de départ : %17s | Ville d'arrivée : %17s | Date de départ : %02d/%02d/%4d \n",lTrajet[T[i]].villeDepart, lTrajet[T[i]].villeArrivee,
            lTrajet[T[i]].dateDepart.jour, lTrajet[T[i]].dateDepart.mois, lTrajet[T[i]].dateDepart.annee);
    }

}

// 4. à partir du numéro d’un bus, ajout et suppression de clients


// 5
void modificationClients(int nb, Trajet* lTrajet, int nBus, Passager client ){
    int trouve = 0; // si un client est trouvé pour un trajet donné.
    for (int i=0; i<nb && !trouve ; i++){ // On cherche le bus ayant pour numéro bus nBus // debut for1
        if (lTrajet[i].numbus == nBus){ //On le trouve
            int j;
            for (j=0; j<56 && lTrajet[i].listePassagers[j].nom[0]!=0 && !trouve ; j++){ // On cherche le passager // debut for2
                if (lTrajet[i].listePassagers[j].id == client.id){ // On le trouve
                    copie_str(lTrajet[i].listePassagers[j].nom, client.nom); // On change son nom par le nouveau nom qui peut être identifique au premier
                    lTrajet[i].listePassagers[j].prixbillet = client.prixbillet; // On change le prix de son billet
                    trouve = 1;} // On a fait ce que l'on voulait faire, le peut se terminer.
            } // fin for2
            if (!trouve){
                if (j>55){
                    printf("Le bus %d est complet.\n", lTrajet[i].numbus);}
                else{
                    lTrajet[i].listePassagers[j] = client ;}
                trouve = 1;
            } // fin if

        } //fin if
    } // fin for1
    if (!trouve)printf("Le bus %d n'existe pas\n", nBus);
}


// 6. la sauvegarde des données dans un fichier (mise à jour du fichier ou création d’un nouveau fichier)

// 7. un filtre sur les trajets partant d’une ville, partant à une date, arrivant le lendemain

// 8. un filtre sur les trajets combinant ville de départ, ville d’arrivée et date de départ

// 9. l’affichage des trajets triés par chiffre d’affaires (différence entre les prix des billets payés par les
// passagers et le coût du trajet supporté par l’entreprise), avec affichage de ce chiffre d’affaires

// 10. la possibilité de supprimer tous les bus avec un chiffre d’affaires négatif, en répartissant les passagers
// sur les trajets identiques, en priorisant les passagers ayant payé le plus sur les dates et horaires les plus
// proches du trajet initial. Il faudra indiquer le gain généré par cette opération
