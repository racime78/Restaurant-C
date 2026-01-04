/*
 * log.h
 * ------
 * Gestion du système de logs HTML.
 *
 * Rôle du fichier :
 * -----------------
 * Ce module fournit la fonction write_log(), utilisée par tous les
 * composants du programme (serveurs, cuisiniers, main) pour écrire
 * des messages formatés dans le fichier logs.html.
 *
 * Le but est de centraliser la logique de logging afin :
 *   - d'éviter la duplication de code,
 *   - de garantir un format cohérent pour tous les messages,
 *   - de maintenir un historique lisible et structuré.
 *
 * Fonction principale :
 * ---------------------
 *   void write_log(const char *message)
 *     - Ouvre le fichier logs.html en mode append.
 *     - Ajoute un bloc HTML contenant :
 *         * l'heure courante,
 *         * le message fourni,
 *         * une mise en forme CSS simple.
 *     - Ne ferme pas le fichier HTML global (géré dans main.c).
 *
 * Utilisation :
 * -------------
 * - Appelé par serveur.c pour enregistrer les commandes.
 * - Appelé par cuisinier.c pour enregistrer les étapes de préparation.
 * - Appelé par main.c pour noter la fin de la simulation.
 */

#ifndef LOG_H
#define LOG_H

// Écrit un message formaté dans le fichier HTML de logs
void write_log(const char *message);

#endif
