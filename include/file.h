/*
 * file.h
 * -------
 * Déclare la file d'attente des commandes (buffer circulaire).
 * - CAPACITE : taille maximale de la file.
 * - file[] : tableau partagé contenant les commandes.
 * - in/out : indices pour gérer l'insertion et le retrait dans le buffer.
 * - ajouter_commande() : ajoute une commande dans la file.
 * - retirer_commande() : retire une commande de la file.
 * 
 * Rôle : fournir les structures et fonctions nécessaires à la gestion
 *        de la file d'attente entre serveurs et cuisiniers.
 */

#ifndef FILE_H
#define FILE_H

#include "commande.h"   // pour utiliser la struct Commande

// Taille maximale de la file (buffer circulaire)
#define CAPACITE 10

// Buffer partagé
extern Commande file[CAPACITE];

// Indices pour gérer le buffer circulaire
extern int in;
extern int out;

// Prototypes des fonctions
void ajouter_commande(Commande c);
Commande retirer_commande();

#endif
