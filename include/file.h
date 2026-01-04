/*
 * file.h
 * -------
 * Gestion de la file d'attente des commandes (buffer circulaire).
 *
 * Rôle du fichier :
 * -----------------
 * Ce module définit la structure du buffer partagé utilisé pour stocker
 * les commandes entre les serveurs (producteurs) et les cuisiniers
 * (consommateurs). Il fournit :
 *
 *   - La constante CAPACITE : taille maximale du buffer.
 *   - Le tableau partagé `file[]` : stockage des commandes.
 *   - Les indices `in` et `out` : positions d'insertion et de retrait.
 *   - Les fonctions `ajouter_commande()` et `retirer_commande()` :
 *       opérations atomiques sur le buffer circulaire.
 *
 * Fonctionnement du buffer circulaire :
 * -------------------------------------
 * - `in`  pointe vers la prochaine position libre pour insérer une commande.
 * - `out` pointe vers la prochaine commande à retirer.
 * - Les deux indices avancent modulo CAPACITE.
 * - Le sémaphore `places_libres` empêche de dépasser la capacité.
 * - Le sémaphore `commandes_disponibles` empêche de retirer une commande vide.
 *
 * Ce fichier est utilisé par :
 *   - serveur.c  → pour ajouter des commandes.
 *   - cuisinier.c → pour retirer des commandes.
 */

#ifndef FILE_H
#define FILE_H

#include "commande.h"   // Pour utiliser la struct Commande

// Taille maximale de la file (buffer circulaire)
#define CAPACITE 10

// Buffer partagé contenant les commandes
extern Commande file[CAPACITE];

// Indices du buffer circulaire
extern int in;   // Prochaine position d'insertion
extern int out;  // Prochaine position de retrait

// Ajoute une commande dans la file (appelé par les serveurs)
void ajouter_commande(Commande c);

// Retire une commande de la file (appelé par les cuisiniers)
Commande retirer_commande();

#endif
