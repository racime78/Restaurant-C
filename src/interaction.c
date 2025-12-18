/*
 * interaction.c
 * --------------
 * Gère l'interaction avec l'utilisateur pour la saisie des commandes.
 * - Associe automatiquement un temps de préparation selon le plat choisi.
 *   - pizza  -> 10 secondes
 *   - grec   -> 5 secondes
 *   - burger -> 5 secondes
 *   - autre  -> 3 secondes par défaut
 * - Initialise l'état de la commande à "PRISE".
 * 
 * Rôle : fournir une interface utilisateur simple pour créer des commandes.
 */

#include <stdio.h>
#include <string.h>
#include "interaction.h"

Commande saisir_commande(int id) {
    Commande c;
    c.id = id;

    // ⚠️ On ne fait plus de printf ici, le serveur affiche déjà le prompt
    scanf("%19s", c.plat);

    if (strcmp(c.plat, "pizza") == 0) {
        c.temps_preparation = 10;
    } else if (strcmp(c.plat, "grec") == 0) {
        c.temps_preparation = 5;
    } else if (strcmp(c.plat, "burger") == 0) {
        c.temps_preparation = 5;
    } else {
        c.temps_preparation = 3; // valeur par défaut
    }

    c.etat = 0; // PRISE
    return c;
}
