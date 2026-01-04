/*
 * serveur.c
 * ----------
 * Implémentation de la fonction exécutée par les threads serveurs.
 *
 * Rôle du fichier :
 * -----------------
 * Les serveurs sont les "producteurs" du modèle producteur-consommateur.
 * Leur mission :
 *   - Réserver un numéro de commande unique.
 *   - Demander à l'utilisateur quel plat il souhaite.
 *   - Vérifier si un cuisinier est disponible immédiatement.
 *   - Ajouter la commande dans la file d'attente.
 *   - Écrire les logs HTML correspondants.
 *
 * Synchronisation utilisée :
 * --------------------------
 * - mutex_compteur : protège l'accès au compteur commandes_produites.
 * - mutex_saisie : empêche plusieurs serveurs de lire la saisie en même temps.
 * - mutex_affichage : évite les affichages simultanés.
 * - places_libres : sémaphore indiquant les places disponibles dans la file.
 * - commandes_disponibles : sémaphore indiquant les commandes prêtes.
 * - cuisiniers_disponibles : sémaphore indiquant les cuisiniers libres.
 *
 * Particularité :
 * ---------------
 * Le serveur utilise sem_trywait() pour détecter si tous les cuisiniers
 * sont occupés. Cela permet d'afficher un message d'attente sans bloquer.
 */

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <semaphore.h>
#include "serveur.h"
#include "file.h"
#include "commande.h"
#include "log.h"
#include "interaction.h"
#include "globals.h"

/*
 * serveur
 * -------
 * Fonction exécutée par chaque thread serveur.
 *
 * Paramètre :
 *   - arg : pointeur vers un entier contenant l'ID du serveur.
 *
 * Fonctionnement :
 *   1. Réserver un numéro de commande unique.
 *   2. Demander à l'utilisateur le plat souhaité.
 *   3. Vérifier si un cuisinier est libre (sem_trywait).
 *   4. Attendre une place dans la file.
 *   5. Ajouter la commande dans le buffer circulaire.
 *   6. Log + affichage.
 */
void* serveur(void* arg) {
    int id = *(int*)arg;

    while (1) {

        /* ---------------------------------------------------------
         * 1. Réserver un numéro de commande unique
         * --------------------------------------------------------- */
        pthread_mutex_lock(&mutex_compteur);
        if (commandes_produites >= NB_COMMANDES) {
            pthread_mutex_unlock(&mutex_compteur);
            break;  // Toutes les commandes ont été produites
        }
        int num = ++commandes_produites;
        pthread_mutex_unlock(&mutex_compteur);

        /* ---------------------------------------------------------
         * 2. Saisie utilisateur (protégée)
         * --------------------------------------------------------- */
        pthread_mutex_lock(&mutex_saisie);
        printf("\nEntrez le plat (pizza/grec/burger) pour la commande #%d : ", num);
        fflush(stdout);
        Commande c = saisir_commande(num);
        pthread_mutex_unlock(&mutex_saisie);

        /* ---------------------------------------------------------
         * 3. Vérifier si un cuisinier est libre (sans bloquer)
         * --------------------------------------------------------- */
        if (sem_trywait(&cuisiniers_disponibles) == -1) {
            // Aucun cuisinier libre → la commande va attendre dans la file

            pthread_mutex_lock(&mutex_affichage);
            printf("[Serveur %d] La commande #%d est mise en file d'attente (tous les cuisiniers occupés)\n",
                   id, num);
            fflush(stdout);
            pthread_mutex_unlock(&mutex_affichage);

            char msg_attente[200];
            snprintf(msg_attente, sizeof(msg_attente),
                     "Serveur %d : commande #%d mise en file d'attente (tous les cuisiniers occupés)",
                     id, num);
            write_log(msg_attente);
        } else {
            // Un cuisinier était libre → on remet immédiatement le jeton
            sem_post(&cuisiniers_disponibles);
        }

        /* ---------------------------------------------------------
         * 4. Attendre une place dans la file
         * --------------------------------------------------------- */
        sem_wait(&places_libres);

        /* ---------------------------------------------------------
         * 5. Ajouter la commande dans la file
         * --------------------------------------------------------- */
        ajouter_commande(c);
        sem_post(&commandes_disponibles);

        /* ---------------------------------------------------------
         * 6. Affichage + log
         * --------------------------------------------------------- */
        pthread_mutex_lock(&mutex_affichage);
        printf("[Serveur %d] Commande %d enregistrée (%s)\n", id, c.id, c.plat);
        fflush(stdout);
        pthread_mutex_unlock(&mutex_affichage);

        char msg[150];
        snprintf(msg, sizeof(msg),
                 "Serveur %d a pris la commande #%d (%s)", id, c.id, c.plat);
        write_log(msg);

        sleep(1);  // Petite pause pour lisibilité
    }

    return NULL;
}
