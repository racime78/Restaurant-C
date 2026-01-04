/*
 * file.c
 * -------
 * Implémentation de la file d'attente des commandes (buffer circulaire).
 *
 * Rôle du fichier :
 * -----------------
 * Ce module gère le tampon partagé entre :
 *   - les serveurs (producteurs), qui ajoutent des commandes,
 *   - les cuisiniers (consommateurs), qui retirent des commandes.
 *
 * Il utilise un buffer circulaire pour stocker les commandes, ainsi que
 * des mécanismes de synchronisation (mutex + sémaphores) pour garantir
 * un accès sûr et ordonné dans un environnement multithread.
 *
 * Synchronisation :
 * -----------------
 * - mutex_file :
 *       protège l'accès concurrent au buffer (in/out/file[]).
 *
 * - places_libres (sémaphore) :
 *       indique combien de places sont disponibles dans la file.
 *       empêche les serveurs de dépasser la capacité.
 *
 * - commandes_disponibles (sémaphore) :
 *       indique combien de commandes sont prêtes à être consommées.
 *       empêche les cuisiniers de retirer une commande inexistante.
 *
 * Ce fichier est un élément central du modèle producteur-consommateur.
 */

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include "file.h"

/* --------------------------------------------------------------------
 * Définition des variables globales déclarées en extern dans file.h
 * -------------------------------------------------------------------- */
Commande file[CAPACITE];   // Buffer circulaire
int in = 0;                // Index d'insertion
int out = 0;               // Index de retrait

// Mutex et sémaphores (initialisés dans main.c)
extern pthread_mutex_t mutex_file;
extern sem_t places_libres;
extern sem_t commandes_disponibles;

/*
 * ajouter_commande
 * ----------------
 * Ajoute une commande dans le buffer circulaire.
 *
 * Étapes :
 *   1. Attendre une place libre (sémaphore places_libres).
 *   2. Verrouiller le buffer.
 *   3. Insérer la commande à l'index 'in'.
 *   4. Avancer l'index circulaire.
 *   5. Déverrouiller le buffer.
 *   6. Signaler qu'une commande est disponible.
 */
void ajouter_commande(Commande c) {
    // 1. Attendre qu'il y ait une place libre
    sem_wait(&places_libres);

    // 2. Verrouiller l'accès au buffer
    pthread_mutex_lock(&mutex_file);

    // 3. Insérer la commande
    file[in] = c;

    // 4. Avancer l'index circulaire
    in = (in + 1) % CAPACITE;

    printf("[Serveur] Commande %d ajoutée (%s)\n", c.id, c.plat);

    // 5. Déverrouiller le buffer
    pthread_mutex_unlock(&mutex_file);

    // 6. Signaler qu'une commande est disponible
    sem_post(&commandes_disponibles);
}

/*
 * retirer_commande
 * ----------------
 * Retire une commande du buffer circulaire.
 *
 * Étapes :
 *   1. Attendre qu'une commande soit disponible.
 *   2. Verrouiller le buffer.
 *   3. Retirer la commande à l'index 'out'.
 *   4. Avancer l'index circulaire.
 *   5. Déverrouiller le buffer.
 *   6. Signaler qu'une place est libre.
 */
Commande retirer_commande() {
    Commande c;

    // 1. Attendre qu'une commande soit disponible
    sem_wait(&commandes_disponibles);

    // 2. Verrouiller l'accès au buffer
    pthread_mutex_lock(&mutex_file);

    // 3. Retirer la commande
    c = file[out];

    // 4. Avancer l'index circulaire
    out = (out + 1) % CAPACITE;

    printf("[Cuisinier] Commande %d retirée (%s)\n", c.id, c.plat);

    // 5. Déverrouiller le buffer
    pthread_mutex_unlock(&mutex_file);

    // 6. Signaler qu'une place est libre
    sem_post(&places_libres);

    return c;
}
