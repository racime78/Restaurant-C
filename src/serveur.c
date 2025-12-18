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
        pthread_mutex_lock(&mutex_compteur);
        if (commandes_produites >= NB_COMMANDES) {
            pthread_mutex_unlock(&mutex_compteur);
            break;
        }
        int num = commandes_produites + 1;
        pthread_mutex_unlock(&mutex_compteur);

        // Saisie utilisateur protégée
        pthread_mutex_lock(&mutex_saisie);
        pthread_mutex_lock(&mutex_affichage);

        printf("\nEntrez le plat (pizza/grec/burger) pour la commande #%d : ", num);
        fflush(stdout);

        pthread_mutex_unlock(&mutex_affichage);

        Commande c = saisir_commande(num);
        pthread_mutex_unlock(&mutex_saisie);

        ajouter_commande(c);

        pthread_mutex_lock(&mutex_compteur);
        commandes_produites++;
        pthread_mutex_unlock(&mutex_compteur);

        pthread_mutex_lock(&mutex_affichage);
        printf("[Serveur] Commande %d enregistrée (%s)\n", c.id, c.plat);
        fflush(stdout);
        pthread_mutex_unlock(&mutex_affichage);

        char msg[100];
        snprintf(msg, sizeof(msg), "Serveur %d a pris la commande #%d (%s)", id, c.id, c.plat);
        write_log(msg);

        sleep(1);
    }

    return NULL;
}
