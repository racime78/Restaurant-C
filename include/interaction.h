/*
 * interaction.h
 * --------------
 * Gestion de l'interaction utilisateur pour la création des commandes.
 *
 * Rôle du fichier :
 * -----------------
 * Ce module fournit la fonction permettant aux serveurs de demander
 * à l'utilisateur quel plat il souhaite commander. Il centralise toute
 * la logique de saisie afin d'éviter de dupliquer du code dans serveur.c.
 *
 * Fonction principale :
 * ---------------------
 *   Commande saisir_commande(int id)
 *     - Affiche une demande de saisie à l'utilisateur.
 *     - Lit le plat choisi (pizza, grec, burger, etc.).
 *     - Construit et retourne une structure Commande complète :
 *         * id unique
 *         * nom du plat
 *         * temps de préparation associé
 *         * état initial = PRISE (0)
 *
 * Utilisation :
 * -------------
 * - Appelé exclusivement par les threads serveurs.
 * - Protégé par mutex_saisie pour éviter les saisies simultanées.
 */

#ifndef INTERACTION_H
#define INTERACTION_H

#include "commande.h"

// Demande à l'utilisateur de saisir une commande et retourne une structure Commande
Commande saisir_commande(int id);

#endif
