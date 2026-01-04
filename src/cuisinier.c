/*
 * cuisinier.c
 * ------------
 * Implémentation de la fonction exécutée par les threads cuisiniers.
 *
 * Rôle du fichier :
 * -----------------
 * Ce module contient la logique des cuisiniers dans le modèle
 * producteur-consommateur. Chaque cuisinier :
 *   - attend qu'une commande soit disponible,
 *   - la retire de la file d'attente,
 *   - réserve un "slot cuisinier" pour indiquer qu'il travaille,
 *   - simule la préparation du plat,
 *   - met à jour les compteurs globaux,
 *   - écrit des logs HTML,
 *   - libère son slot une fois la commande terminée.
 *
 * Synchronisation utilisée :
 * --------------------------
 * - commandes_disponibles : nombre de commandes prêtes à être retirées.
 * - places_libres : nombre de places libres dans la file.
 * - cuisiniers_disponibles : nombre de cuisiniers actuellement libres.
 * - mutex_compteur : protège les compteurs globaux.
 * - mutex_affichage : empêche les affichages simultanés.
 *
 * Ce fichier est un élément central du modèle consommateur.
 */

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include "cuisinier.h"
#include "file.h"
#include "commande.h"
#include "log.h"
#include "globals.h"

/*
 * cuisinier
 * ---------
 * Fonction exécutée par chaque thread cuisinier.
 *
 * Paramètre :
 *   - arg : pointeur vers un entier contenant l'ID du cuisinier.
 *
 * Fonctionnement :
 *   1. Vérifie si toutes les commandes ont été traitées.
 *   2. Attend qu'une commande soit disponible (sem_wait).
 *   3. Retire la commande de la file.
 *   4. Réserve un "slot cuisinier" (indique qu'il est occupé).
 *   5. Met à jour les compteurs.
 *   6. Simule la préparation du plat.
 *   7. Libère le slot cuisinier.
 */
void* cuisinier(void* arg) {
    int id = *(int*)arg;

    while (1) {

        /* ---------------------------------------------------------
         * 1. Vérifier si toutes les commandes ont été traitées
         * --------------------------------------------------------- */
        pthread_mutex_lock(&mutex_compteur);
        if (commandes_consommees >= NB_COMMANDES) {
            pthread_mutex_unlock(&mutex_compteur);
            break;  // Fin du thread cuisinier
        }
        pthread_mutex_unlock(&mutex_compteur);

        /* ---------------------------------------------------------
         * 2. Attendre qu'une commande soit disponible
         *    (sémaphore consommateur)
         * --------------------------------------------------------- */
        sem_wait(&commandes_disponibles);

        /* ---------------------------------------------------------
         * 3. Retirer la commande de la file
         * --------------------------------------------------------- */
        Commande c = retirer_commande();
        sem_post(&places_libres);  // Une place se libère dans la file

        /* ---------------------------------------------------------
         * 4. Réserver un cuisinier (il devient occupé)
         * --------------------------------------------------------- */
        sem_wait(&cuisiniers_disponibles);

        /* ---------------------------------------------------------
         * 5. Incrémenter le compteur de commandes traitées
         * --------------------------------------------------------- */
        pthread_mutex_lock(&mutex_compteur);
        commandes_consommees++;
        pthread_mutex_unlock(&mutex_compteur);

        /* ---------------------------------------------------------
         * 6. Log : retrait de la commande
         * --------------------------------------------------------- */
        char msg_retrait[100];
        snprintf(msg_retrait, sizeof(msg_retrait),
                 "Cuisinier %d a retiré la commande #%d (%s)",
                 id, c.id, c.plat);
        write_log(msg_retrait);

        c.etat = 1;  // EN_PREPARATION

        /* ---------------------------------------------------------
         * 7. Simulation de la préparation du plat
         * --------------------------------------------------------- */
        for (int t = c.temps_preparation; t > 0; t--) {
            pthread_mutex_lock(&mutex_affichage);
            printf("Cuisinier %d prépare commande #%d (%s) - Temps restant : %2d sec\n",
                   id, c.id, c.plat, t);
            fflush(stdout);
            pthread_mutex_unlock(&mutex_affichage);
            sleep(1);
        }

        /* ---------------------------------------------------------
         * 8. Fin de préparation
         * --------------------------------------------------------- */
        c.etat = 2;  // TERMINEE

        pthread_mutex_lock(&mutex_affichage);
        printf("Cuisinier %d a terminé la commande #%d (%s)\n",
               id, c.id, c.plat);
        fflush(stdout);
        pthread_mutex_unlock(&mutex_affichage);

        // Log fin
        char msg_fin[100];
        snprintf(msg_fin, sizeof(msg_fin),
                 "Cuisinier %d a terminé la commande #%d (%s)",
                 id, c.id, c.plat);
        write_log(msg_fin);

        /* ---------------------------------------------------------
         * 9. Libérer un cuisinier (il redevient disponible)
         * --------------------------------------------------------- */
        sem_post(&cuisiniers_disponibles);
    }

    return NULL;
}
