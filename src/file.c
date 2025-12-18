/*
 * file.c
 * -------
 * Implémente la file d'attente des commandes (buffer circulaire).
 * - ajouter_commande() : ajoute une commande dans la file si une place est libre.
 * - retirer_commande() : retire une commande de la file si disponible.
 * 
 * Synchronisation :
 * - Utilise un mutex pour protéger l'accès concurrent au buffer.
 * - Utilise deux sémaphores :
 *   - places_libres : nombre de places disponibles dans la file.
 *   - commandes_disponibles : nombre de commandes prêtes à être consommées.
 * 
 * Rôle : gérer la file d'attente entre serveurs (producteurs) et cuisiniers (consommateurs).
 */


#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include "file.h"

// Définition des variables globales déclarées en extern dans file.h
Commande file[CAPACITE];
int in = 0;
int out = 0;

// Mutex et sémaphores (ils seront initialisés dans main.c)
extern pthread_mutex_t mutex_file;
extern sem_t places_libres;
extern sem_t commandes_disponibles;

// Fonction pour ajouter une commande dans le buffer
void ajouter_commande(Commande c) {
    // Attendre qu'il y ait une place libre
    sem_wait(&places_libres);

    // Verrouiller l'accès au buffer
    pthread_mutex_lock(&mutex_file);

    // Insérer la commande
    file[in] = c;
    in = (in + 1) % CAPACITE;

    printf("[Serveur] Commande %d ajoutée (%s)\n", c.id, c.plat);

    // Déverrouiller
    pthread_mutex_unlock(&mutex_file);

    // Signaler qu'une commande est disponible
    sem_post(&commandes_disponibles);
}

// Fonction pour retirer une commande du buffer
Commande retirer_commande() {
    Commande c;

    // Attendre qu'une commande soit disponible
    sem_wait(&commandes_disponibles);

    // Verrouiller l'accès au buffer
    pthread_mutex_lock(&mutex_file);

    // Retirer la commande
    c = file[out];
    out = (out + 1) % CAPACITE;

    printf("[Cuisinier] Commande %d retirée (%s)\n", c.id, c.plat);

    // Déverrouiller
    pthread_mutex_unlock(&mutex_file);

    // Signaler qu'une place est libre
    sem_post(&places_libres);

    return c;
}
