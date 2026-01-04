/*
 * globals.h
 * ----------
 * Déclaration des variables globales utilisées dans tout le projet.
 *
 * Rôle du fichier :
 * -----------------
 * Ce module centralise :
 *   - Les mutex partagés entre les threads.
 *   - Les sémaphores nécessaires à la synchronisation.
 *   - Les compteurs globaux (commandes produites / consommées).
 *   - La constante NB_CUISINIERS, définissant le nombre de cuisiniers actifs.
 *
 * Pourquoi un fichier global ?
 * ----------------------------
 * Les serveurs, cuisiniers et la file d’attente doivent partager
 * des ressources communes :
 *   - La file d’attente (protégée par mutex_file)
 *   - Les compteurs (protégés par mutex_compteur)
 *   - L’affichage (protégé par mutex_affichage)
 *   - La saisie utilisateur (protégée par mutex_saisie)
 *   - Les sémaphores du modèle producteur-consommateur
 *
 * globals.h permet à tous les fichiers (.c) d’accéder à ces ressources
 * sans les redéclarer, tout en évitant les doublons grâce à "extern".
 */

#ifndef GLOBALS_H
#define GLOBALS_H

#include <pthread.h>
#include <semaphore.h>

/* ---------------------- */
/*   MUTEX GLOBAUX        */
/* ---------------------- */

// Protège l'accès à la file d'attente (buffer circulaire)
extern pthread_mutex_t mutex_file;

// Protège les compteurs commandes_produites / commandes_consommees
extern pthread_mutex_t mutex_compteur;

// Empêche les affichages simultanés (évite les lignes mélangées)
extern pthread_mutex_t mutex_affichage;

// Empêche plusieurs serveurs de demander une saisie en même temps
extern pthread_mutex_t mutex_saisie;


/* ---------------------- */
/*   SÉMAPHORES GLOBAUX   */
/* ---------------------- */

// Nombre de places libres dans la file (tampon producteur-consommateur)
extern sem_t places_libres;

// Nombre de commandes disponibles pour les cuisiniers
extern sem_t commandes_disponibles;

// Nombre de cuisiniers actuellement disponibles
extern sem_t cuisiniers_disponibles;


/* ---------------------- */
/*   COMPTEURS GLOBAUX    */
/* ---------------------- */

// Nombre total de commandes déjà produites par les serveurs
extern int commandes_produites;

// Nombre total de commandes déjà consommées par les cuisiniers
extern int commandes_consommees;


/* ---------------------- */
/*   PARAMÈTRES GLOBAUX   */
/* ---------------------- */

// Nombre de cuisiniers actifs dans la simulation
#define NB_CUISINIERS 2

#endif
