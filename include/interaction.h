/*
 * interaction.h
 * --------------
 * Déclare la fonction de saisie utilisateur pour créer une commande.
 * - saisir_commande() : demande à l'utilisateur de saisir un plat et retourne une commande complète.
 * 
 * Rôle : centraliser l'interaction utilisateur pour la création des commandes.
 */

#ifndef INTERACTION_H
#define INTERACTION_H

#include "commande.h"

// Demande à l'utilisateur de saisir une commande
Commande saisir_commande(int id);

#endif
