/*
 * globals.c
 * ----------
 * Définit toutes les variables globales utilisées dans le projet.
 * - Compteurs de commandes produites et consommées
 * - Mutex pour synchroniser l'accès aux ressources partagées
 * - Sémaphores pour gérer la file
 */

#include <pthread.h>
#include <semaphore.h>
#include "commande.h"
#include "globals.h"

// Compteurs
int commandes_produites = 0;
int commandes_consommees = 0;

// Mutex
pthread_mutex_t mutex_file;
pthread_mutex_t mutex_compteur;
pthread_mutex_t mutex_affichage;
pthread_mutex_t mutex_saisie;

// Sémaphores
sem_t places_libres;
sem_t commandes_disponibles;
