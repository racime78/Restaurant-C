/*
 * commande.c
 * ----------
 * Implémentation des fonctions liées à la gestion d'une commande.
 *
 * Rôle du fichier :
 * -----------------
 * Ce module contient des fonctions utilitaires permettant de manipuler
 * ou d'afficher des structures Commande. Il sert principalement pour
 * le débogage, le traçage ou l'affichage simple des commandes créées
 * par les serveurs.
 *
 * Fonction principale :
 * ---------------------
 *   void afficherCommande(Commande c)
 *     - Affiche l'identifiant et le nom du plat d'une commande.
 *     - Utile pour vérifier que les commandes sont correctement créées
 *       avant d'être ajoutées dans la file d'attente.
 */

#include "commande.h"
#include <stdio.h>

/*
 * afficherCommande
 * ----------------
 * Affiche une commande sous la forme :
 *     Commande #ID : PLAT
 *
 * Paramètre :
 *   - c : la commande à afficher
 */
void afficherCommande(Commande c) {
    printf("Commande #%d : %s\n", c.id, c.plat);
}
