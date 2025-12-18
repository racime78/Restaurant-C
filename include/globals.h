#ifndef GLOBALS_H
#define GLOBALS_H

#include <pthread.h>
#include <semaphore.h>

// Mutex globaux
extern pthread_mutex_t mutex_file;
extern pthread_mutex_t mutex_compteur;
extern pthread_mutex_t mutex_affichage;
extern pthread_mutex_t mutex_saisie;

// Sémaphores globaux
extern sem_t places_libres;
extern sem_t commandes_disponibles;

// Compteurs globaux
extern int commandes_produites;
extern int commandes_consommees;



#endif
