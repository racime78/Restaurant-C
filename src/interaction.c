/*
 * interaction.c
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
 *     - Lit le nom du plat saisi par l'utilisateur.
 *     - Associe automatiquement un temps de préparation :
 *         * pizza  -> 10 secondes
 *         * grec   -> 5 secondes
 *         * burger -> 5 secondes
 *         * autre  -> 3 secondes (valeur par défaut)
 *     - Initialise l'état de la commande à PRISE (0).
 *
 * Utilisation :
 * -------------
 * - Appelé exclusivement par les threads serveurs.
 * - Protégé par mutex_saisie pour éviter les saisies simultanées.
 */

#include <stdio.h>
#include <string.h>
#include "interaction.h"

/*
 * saisir_commande
 * ----------------
 * Crée une structure Commande à partir de la saisie utilisateur.
 *
 * Paramètre :
 *   - id : identifiant unique attribué par le serveur.
 *
 * Retour :
 *   - Une structure Commande initialisée (id, plat, temps, état).
 *
 * Remarque :
 *   - Aucun printf ici : le serveur affiche déjà le prompt.
 */
Commande saisir_commande(int id) {
    Commande c;
    c.id = id;

    // Lire le nom du plat (max 19 caractères)
    scanf("%19s", c.plat);

    // Associer un temps de préparation selon le plat
    if (strcmp(c.plat, "pizza") == 0) {
        c.temps_preparation = 10;
    } 
    else if (strcmp(c.plat, "grec") == 0) {
        c.temps_preparation = 5;
    } 
    else if (strcmp(c.plat, "burger") == 0) {
        c.temps_preparation = 5;
    } 
    else {
        c.temps_preparation = 3;  // Valeur par défaut
    }

    // État initial : commande prise par le serveur
    c.etat = 0;  // PRISE

    return c;
}
