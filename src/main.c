#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include "file.h"
#include "serveur.h"
#include "cuisinier.h"
#include "log.h"
#include "commande.h"
#include "interaction.h"
#include "globals.h"


int main() {
    // Initialisation des mutex et sémaphores
    pthread_mutex_init(&mutex_file, NULL);
    pthread_mutex_init(&mutex_compteur, NULL);
    pthread_mutex_init(&mutex_affichage, NULL);
    pthread_mutex_init(&mutex_saisie, NULL);

    sem_init(&places_libres, 0, CAPACITE);
    sem_init(&commandes_disponibles, 0, 0);

    // Création des threads
    pthread_t serveurs[2];
    pthread_t cuisiniers[2];
    int ids_serveurs[2] = {1, 2};
    int ids_cuisiniers[2] = {1, 2};

    for (int i = 0; i < 2; i++) {
        pthread_create(&serveurs[i], NULL, serveur, &ids_serveurs[i]);
    }
    for (int i = 0; i < 2; i++) {
        pthread_create(&cuisiniers[i], NULL, cuisinier, &ids_cuisiniers[i]);
    }

    for (int i = 0; i < 2; i++) {
        pthread_join(serveurs[i], NULL);
        pthread_join(cuisiniers[i], NULL);
    }

    // Nettoyage
    pthread_mutex_destroy(&mutex_file);
    pthread_mutex_destroy(&mutex_compteur);
    pthread_mutex_destroy(&mutex_affichage);
    pthread_mutex_destroy(&mutex_saisie);

    sem_destroy(&places_libres);
    sem_destroy(&commandes_disponibles);

    printf("\nSimulation terminée : %d commandes produites et %d consommées (max %d).\n",
           commandes_produites, commandes_consommees, NB_COMMANDES);

    write_log("Simulation terminée");
    return 0;
}
