/*
 * serveur.h
 * ----------
 * Déclare la fonction serveur(void* arg).
 * - Cette fonction est exécutée par les threads serveurs.
 * - Elle est définie dans serveur.c.
 * 
 * Rôle : fournir le prototype de la fonction serveur aux autres fichiers.
 */


#ifndef SERVEUR_H
#define SERVEUR_H

void* serveur(void* arg);

#endif
