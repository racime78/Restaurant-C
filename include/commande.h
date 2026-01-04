/*
 * -----------
 * Définition de la structure représentant une commande dans le système.
 *
 * Rôle du fichier :
 * -----------------
 * Ce fichier fournit :
 *   - Le type `Commande`, utilisé par tous les modules (serveurs, cuisiniers, file d’attente).
 *   - La constante `NB_COMMANDES`, qui fixe le nombre total de commandes
 *     que la simulation doit traiter avant de s’arrêter.
 *
 * Utilisation :
 * -------------
 * - Les serveurs créent des objets Commande et les ajoutent à la file.
 * - Les cuisiniers retirent ces objets et mettent à jour leur état.
 * - La file d’attente stocke des Commande dans un buffer circulaire.
 */

#ifndef COMMANDE_H
#define COMMANDE_H

// Structure représentant une commande dans le restaurant
typedef struct {
    int id;                  // Identifiant unique de la commande
    char plat[20];           // Nom du plat (pizza, grec, burger, etc.)
    int temps_preparation;   // Temps de préparation en secondes
    int etat;                // 0 = PRISE, 1 = EN_PREPARATION, 2 = TERMINEE
} Commande;

// Nombre total de commandes que la simulation doit traiter
#define NB_COMMANDES 10

#endif
