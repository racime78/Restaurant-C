/*
 * commande.h
 * -----------
 * Définit la structure de base d'une commande.
 * - struct Commande : contient l'identifiant (id), le nom du plat, le temps de préparation et l'état.
 * - NB_COMMANDES : constante globale définissant le nombre maximum de commandes que la simulation peut traiter.
 * - États possibles d'une commande :
 *   - 0 = PRISE
 *   - 1 = EN_PREPARATION
 *   - 2 = TERMINEE
 * 
 * Rôle : fournir le type Commande et la limite de commandes aux autres modules.
 */

#ifndef COMMANDE_H
#define COMMANDE_H

typedef struct {
    int id;                  // Identifiant unique de la commande
    char plat[20];           // Nom du plat (pizza, grec, burger, etc.)
    int temps_preparation;   // Temps de préparation en secondes
    int etat;                // État de la commande : 0 = PRISE, 1 = EN_PREPARATION, 2 = TERMINEE
} Commande;

// Constante globale : nombre maximum de commandes
#define NB_COMMANDES 10

#endif
