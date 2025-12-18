/*
 * cuisinier.h
 * ------------
 * Déclare la fonction cuisinier(void* arg).
 * - Cette fonction est exécutée par les threads cuisiniers.
 * - Elle est définie dans cuisinier.c.
 * 
 * Rôle : fournir le prototype de la fonction cuisinier aux autres fichiers.
 */

#ifndef CUISINIER_H
#define CUISINIER_H

void* cuisinier(void* arg);

#endif
