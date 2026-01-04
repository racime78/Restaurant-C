/*
 * main.c
 * -------
 * Point d'entrée de la simulation du restaurant.
 *
 * Rôle du fichier :
 * -----------------
 * Ce module initialise toutes les ressources nécessaires :
 *   - Mutex
 *   - Sémaphores
 *   - Threads serveurs et cuisiniers
 *   - Fichier de logs HTML
 *
 * Il orchestre ensuite l'exécution des threads et assure le nettoyage
 * final des ressources. C’est le cœur de la simulation.
 *
 * Fonctionnement général :
 * ------------------------
 * 1. Préparer le fichier logs.html (écrire l’en-tête si vide).
 * 2. Initialiser les mutex et sémaphores.
 * 3. Créer les threads serveurs et cuisiniers.
 * 4. Attendre la fin de tous les threads.
 * 5. Détruire les ressources.
 * 6. Afficher un résumé final.
 */

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

    /* ---------------------------------------------------------
     * 1. Préparation du fichier logs.html
     * --------------------------------------------------------- */
    FILE *f = fopen("logs.html", "a+");  // Ouverture sans effacer l’historique
    if (f) {
        fseek(f, 0, SEEK_END);

        // Si le fichier est vide → écrire l’en-tête HTML
        if (ftell(f) == 0) {
            fprintf(f,
                "<!DOCTYPE html>\n"
                "<html lang=\"fr\">\n"
                "<head>\n"
                "  <meta charset=\"UTF-8\">\n"
                "  <title>Logs du Restaurant</title>\n"
                "  <style>\n"
                "    body { font-family: Arial, sans-serif; background: #f4f4f4; }\n"
                "    .log { margin: 10px; padding: 10px; background: #fff; "
                          "border-left: 4px solid #007BFF; }\n"
                "    .time { color: gray; font-size: 0.9em; }\n"
                "  </style>\n"
                "</head>\n"
                "<body>\n"
                "<h1>Logs du Restaurant</h1>\n"
            );
        }
        fclose(f);
    }

    /* ---------------------------------------------------------
     * 2. Initialisation des mutex et sémaphores
     * --------------------------------------------------------- */
    pthread_mutex_init(&mutex_file, NULL);
    pthread_mutex_init(&mutex_compteur, NULL);
    pthread_mutex_init(&mutex_affichage, NULL);
    pthread_mutex_init(&mutex_saisie, NULL);

    sem_init(&places_libres, 0, CAPACITE);         // File vide → CAPACITE places libres
    sem_init(&commandes_disponibles, 0, 0);        // Aucune commande au début
    sem_init(&cuisiniers_disponibles, 0, NB_CUISINIERS);

    /* ---------------------------------------------------------
     * 3. Création des threads serveurs et cuisiniers
     * --------------------------------------------------------- */
    pthread_t serveurs[2];
    pthread_t cuisiniers[NB_CUISINIERS];

    int ids_serveurs[2] = {1, 2};
    int ids_cuisiniers[NB_CUISINIERS];

    // Threads serveurs
    for (int i = 0; i < 2; i++) {
        pthread_create(&serveurs[i], NULL, serveur, &ids_serveurs[i]);
    }

    // Threads cuisiniers
    for (int i = 0; i < NB_CUISINIERS; i++) {
        ids_cuisiniers[i] = i + 1;
        pthread_create(&cuisiniers[i], NULL, cuisinier, &ids_cuisiniers[i]);
    }

    /* ---------------------------------------------------------
     * 4. Attente de la fin des threads
     * --------------------------------------------------------- */
    for (int i = 0; i < 2; i++) {
        pthread_join(serveurs[i], NULL);
    }
    for (int i = 0; i < NB_CUISINIERS; i++) {
        pthread_join(cuisiniers[i], NULL);
    }

    /* ---------------------------------------------------------
     * 5. Nettoyage des ressources
     * --------------------------------------------------------- */
    pthread_mutex_destroy(&mutex_file);
    pthread_mutex_destroy(&mutex_compteur);
    pthread_mutex_destroy(&mutex_affichage);
    pthread_mutex_destroy(&mutex_saisie);

    sem_destroy(&places_libres);
    sem_destroy(&commandes_disponibles);
    sem_destroy(&cuisiniers_disponibles);

    /* ---------------------------------------------------------
     * 6. Résumé final
     * --------------------------------------------------------- */
    printf("\nSimulation terminée : %d commandes produites et %d consommées (max %d).\n",
           commandes_produites, commandes_consommees, NB_COMMANDES);

    write_log("Simulation terminée");

    // On ne ferme pas le HTML ici pour garder un fichier continu
    /*
    f = fopen("logs.html", "a");
    if (f) {
        fprintf(f, "</body>\n</html>\n");
        fclose(f);
    }
    */

    return 0;
}
