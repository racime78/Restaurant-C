/*
 * serveur.h
 * ----------
 * Déclaration de la fonction exécutée par les threads serveurs.
 *
 * Rôle du fichier :
 * -----------------
 * Ce module expose la fonction serveur(), utilisée pour créer les threads
 * responsables de la prise de commandes. Il permet aux autres fichiers
 * (notamment main.c) d'accéder à cette fonction sans inclure directement
 * serveur.c.
 *
 * Fonction principale :
 * ---------------------
 *   void* serveur(void* arg)
 *     - Fonction exécutée par chaque thread serveur.
 *     - Rôle :
 *         * demander à l'utilisateur de saisir un plat,
 *         * créer une structure Commande,
 *         * l'ajouter dans la file d'attente,
 *         * gérer la synchronisation via mutex et sémaphores.
 *     - Le paramètre `arg` contient l'identifiant du serveur (int*).
 *
 * Utilisation :
 * -------------
 * - Appelé dans main.c via pthread_create().
 * - Nécessite l'inclusion de serveur.h pour connaître son prototype.
 */

#ifndef SERVEUR_H
#define SERVEUR_H

// Fonction exécutée par les threads serveurs
void* serveur(void* arg);

#endif
