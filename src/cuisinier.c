#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include "cuisinier.h"
#include "file.h"
#include "commande.h"
#include "log.h"
#include "globals.h"

void* cuisinier(void* arg) {
    int id = *(int*)arg;

    while (1) {
        // Vérifier si toutes les commandes sont déjà traitées
        pthread_mutex_lock(&mutex_compteur);
        if (commandes_consommees >= NB_COMMANDES) {
            pthread_mutex_unlock(&mutex_compteur);
            break;
        }
        pthread_mutex_unlock(&mutex_compteur);

        // 🔑 Sémaphores pour synchroniser
        sem_wait(&commandes_disponibles);
        Commande c = retirer_commande();
        sem_post(&places_libres);

        // Réserver et incrémenter le compteur consommées
        pthread_mutex_lock(&mutex_compteur);
        commandes_consommees++;
        pthread_mutex_unlock(&mutex_compteur);

        // Log du retrait
        char msg_retrait[100];
        snprintf(msg_retrait, sizeof(msg_retrait),
                 "Cuisinier %d a retiré la commande #%d (%s)", id, c.id, c.plat);
        write_log(msg_retrait);

        c.etat = 1; // EN_PREPARATION

        // Décompte du temps de préparation
        for (int t = c.temps_preparation; t > 0; t--) {
    pthread_mutex_lock(&mutex_affichage);
    printf("Cuisinier %d prépare commande #%d (%s) - Temps restant : %2d sec\n",
           id, c.id, c.plat, t);
    fflush(stdout);
    pthread_mutex_unlock(&mutex_affichage);
    sleep(1);
}


        c.etat = 2; // TERMINEE
        printf("\rCuisinier %d a terminé la commande #%d (%s)\n", id, c.id, c.plat);
        fflush(stdout);

        // Log de fin
        char msg_fin[100];
        snprintf(msg_fin, sizeof(msg_fin),
                 "Cuisinier %d a terminé la commande #%d (%s)", id, c.id, c.plat);
        write_log(msg_fin);
    }

    return NULL;
}
