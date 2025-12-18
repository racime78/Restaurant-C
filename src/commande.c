/*
 * commande.c
 * ----------
 * Contient les fonctions liées à la gestion d'une commande.
 * - Ici, uniquement la fonction afficherCommande() qui affiche l'ID et le plat d'une commande.
 * - Utilisé pour tracer ou déboguer les commandes créées par les serveurs.
 */


#include "commande.h"
#include <stdio.h>

void afficherCommande(Commande c) {
    printf("Commande #%d : %s\n", c.id, c.plat);
}
