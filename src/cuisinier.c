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
        pthread_mutex_lock(&mutex_compteur);
        if (commandes_consommees >= NB_COMMANDES) {
            pthread_mutex_unlock(&mutex_compteur);
            break;
        }
        commandes_consommees++;
        pthread_mutex_unlock(&mutex_compteur);

        // Retirer une commande de la file
        Commande c = retirer_commande();
        c.etat = 1; // EN_PREPARATION

        // Décompte du temps de préparation (une seule ligne)
        for (int t = c.temps_preparation; t > 0; t--) {
            pthread_mutex_lock(&mutex_affichage);
            printf("\rCuisinier %d prépare commande #%d (%s) - Temps restant : %2d sec   ",
                   id, c.id, c.plat, t);
            fflush(stdout);
            pthread_mutex_unlock(&mutex_affichage);
            sleep(1);
        }

        c.etat = 2; // TERMINEE
        pthread_mutex_lock(&mutex_affichage);
        printf("\rCuisinier %d a terminé la commande #%d (%s)\n", id, c.id, c.plat);
        fflush(stdout);
        pthread_mutex_unlock(&mutex_affichage);

        // Log
        char msg[100];
        snprintf(msg, sizeof(msg), "Cuisinier %d a terminé la commande #%d (%s)", id, c.id, c.plat);
        write_log(msg);
    }

    return NULL;
}
