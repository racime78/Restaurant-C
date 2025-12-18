/*
 * log.h
 * ------
 * Déclare la fonction write_log().
 * - write_log() : écrit un message formaté dans un fichier HTML (logs.html).
 * 
 * Rôle : fournir le prototype de la fonction de logging aux autres fichiers.
 */


#ifndef LOG_H
#define LOG_H

// Fonction pour écrire un log dans un fichier HTML
void write_log(const char *message);

#endif
