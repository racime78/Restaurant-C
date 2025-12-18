#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include "serveur.h"
#include "file.h"
#include "commande.h"
#include "log.h"
#include "interaction.h"
#include "globals.h"

void* serveur(void* arg) {
    int id = *(int*)arg;

    while (1) {
        // 🔑 Réserver le numéro de commande tout de suite
        pthread_mutex_lock(&mutex_compteur);
        if (commandes_produites >= NB_COMMANDES) {
            pthread_mutex_unlock(&mutex_compteur);
            break;
        }
        int num = ++commandes_produites; // incrément immédiat
        pthread_mutex_unlock(&mutex_compteur);

        // Saisie utilisateur
        pthread_mutex_lock(&mutex_saisie);
        printf("\nEntrez le plat (pizza/grec/burger) pour la commande #%d : ", num);
        fflush(stdout);
        Commande c = saisir_commande(num);
        pthread_mutex_unlock(&mutex_saisie);

        // Sémaphores pour limiter la file
        sem_wait(&places_libres);
        ajouter_commande(c);
        sem_post(&commandes_disponibles);

        // Affichage et log
        printf("[Serveur %d] Commande %d enregistrée (%s)\n", id, c.id, c.plat);
        fflush(stdout);

        char msg[100];
        snprintf(msg, sizeof(msg), "Serveur %d a pris la commande #%d (%s)", id, c.id, c.plat);
        write_log(msg);

        sleep(1);
    }
    return NULL;
}
