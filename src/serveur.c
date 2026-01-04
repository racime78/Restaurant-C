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

void* serveur(void* arg) {
    int id = *(int*)arg;

    while (1) {

        // 🔑 Réserver le numéro de commande tout de suite
        pthread_mutex_lock(&mutex_compteur);
        if (commandes_produites >= NB_COMMANDES) {
            pthread_mutex_unlock(&mutex_compteur);
            break;
        }
        int num = ++commandes_produites;
        pthread_mutex_unlock(&mutex_compteur);

        // ✅ Saisie utilisateur
        pthread_mutex_lock(&mutex_saisie);
        printf("\nEntrez le plat (pizza/grec/burger) pour la commande #%d : ", num);
        fflush(stdout);
        Commande c = saisir_commande(num);
        pthread_mutex_unlock(&mutex_saisie);

        // ✅ Vérifier proprement si tous les cuisiniers sont occupés
        // On tente de prendre un cuisinier SANS bloquer
        if (sem_trywait(&cuisiniers_disponibles) == -1) {
            // Aucun cuisinier libre → la commande va réellement attendre

            // Affichage terminal
            pthread_mutex_lock(&mutex_affichage);
            printf("[Serveur %d] La commande #%d est mise en file d'attente (tous les cuisiniers occupés)\n",
                   id, num);
            fflush(stdout);
            pthread_mutex_unlock(&mutex_affichage);

            // Log HTML
            char msg_attente[200];
            snprintf(msg_attente, sizeof(msg_attente),
                     "Serveur %d : commande #%d mise en file d'attente (tous les cuisiniers occupés)",
                     id, num);
            write_log(msg_attente);
        } else {
            // Au moins un cuisinier était libre : on remet immédiatement le jeton
            sem_post(&cuisiniers_disponibles);
        }

        // ✅ Attendre une place dans la file
        sem_wait(&places_libres);

        // ✅ Ajouter la commande
        ajouter_commande(c);
        sem_post(&commandes_disponibles);

        // ✅ Affichage et log
        pthread_mutex_lock(&mutex_affichage);
        printf("[Serveur %d] Commande %d enregistrée (%s)\n", id, c.id, c.plat);
        fflush(stdout);
        pthread_mutex_unlock(&mutex_affichage);

        char msg[150];
        snprintf(msg, sizeof(msg),
                 "Serveur %d a pris la commande #%d (%s)", id, c.id, c.plat);
        write_log(msg);

        sleep(1);
    }

    return NULL;
}
