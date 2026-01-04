/*
 * globals.c
 * ----------
 * Définition des variables globales utilisées dans tout le projet.
 *
 * Rôle du fichier :
 * -----------------
 * Ce module contient les définitions (et non les déclarations) de toutes
 * les variables globales partagées entre les différents modules :
 *
 *   - Compteurs de commandes produites et consommées.
 *   - Mutex pour protéger les ressources critiques.
 *   - Sémaphores pour gérer la synchronisation du modèle
 *     producteur-consommateur (serveurs ↔ cuisiniers).
 *
 * Pourquoi un fichier globals.c ?
 * -------------------------------
 * Les variables globales doivent être définies **une seule fois** dans
 * tout le programme. Elles sont déclarées en `extern` dans globals.h,
 * puis définies ici pour éviter les doublons et les erreurs de linkage.
 */

#include <pthread.h>
#include <semaphore.h>
#include "commande.h"
#include "globals.h"

/* ---------------------------------------------------------
 * Compteurs globaux
 * ---------------------------------------------------------
 * commandes_produites :
 *     Nombre total de commandes créées par les serveurs.
 *
 * commandes_consommees :
 *     Nombre total de commandes traitées par les cuisiniers.
 */
int commandes_produites = 0;
int commandes_consommees = 0;

/* ---------------------------------------------------------
 * Mutex globaux
 * ---------------------------------------------------------
 * mutex_file :
 *     Protège l'accès concurrent au buffer circulaire.
 *
 * mutex_compteur :
 *     Protège les compteurs commandes_produites / commandes_consommees.
 *
 * mutex_affichage :
 *     Empêche les affichages simultanés (évite les lignes mélangées).
 *
 * mutex_saisie :
 *     Empêche plusieurs serveurs de demander une saisie utilisateur
 *     en même temps.
 */
pthread_mutex_t mutex_file;
pthread_mutex_t mutex_compteur;
pthread_mutex_t mutex_affichage;
pthread_mutex_t mutex_saisie;

/* ---------------------------------------------------------
 * Sémaphores globaux
 * ---------------------------------------------------------
 * places_libres :
 *     Nombre de places disponibles dans la file d'attente.
 *
 * commandes_disponibles :
 *     Nombre de commandes prêtes à être retirées par les cuisiniers.
 *
 * cuisiniers_disponibles :
 *     Nombre de cuisiniers actuellement libres.
 */
sem_t places_libres;
sem_t commandes_disponibles;
sem_t cuisiniers_disponibles;
