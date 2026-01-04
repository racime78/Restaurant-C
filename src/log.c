/*
 * log.c
 * ------
 * Gestion de l'écriture des logs dans un fichier HTML.
 *
 * Rôle du fichier :
 * -----------------
 * Ce module fournit la fonction write_log(), utilisée par les serveurs,
 * les cuisiniers et le main pour enregistrer toutes les actions du
 * restaurant dans un fichier HTML lisible dans un navigateur.
 *
 * Fonctionnement :
 * ----------------
 * - Le fichier logs.html est ouvert en mode append ("a").
 * - Si le fichier est vide, l'entête HTML + CSS est automatiquement écrit.
 * - Chaque appel ajoute un bloc <div> contenant :
 *       * l'heure courante (HH:MM:SS)
 *       * le message fourni
 * - Le fichier n'est jamais fermé définitivement ici : seule la balise
 *   </body></html> est ajoutée dans main.c à la fin de la simulation.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "log.h"

/*
 * write_log
 * ---------
 * Écrit un message formaté dans logs.html.
 *
 * Paramètre :
 *   - message : texte à enregistrer dans le fichier HTML.
 *
 * Étapes :
 *   1. Ouvrir logs.html en mode ajout.
 *   2. Si le fichier est vide → écrire l'entête HTML + CSS.
 *   3. Récupérer l'heure actuelle.
 *   4. Écrire un bloc <div> contenant l'heure et le message.
 *   5. Fermer le fichier.
 */
void write_log(const char *message) {
    FILE *f = fopen("logs.html", "a");  // Ouverture en ajout
    if (!f) {
        perror("Erreur ouverture logs.html");
        return;
    }

    /* ---------------------------------------------------------
     * 1. Récupérer l'heure actuelle
     * --------------------------------------------------------- */
    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    /* ---------------------------------------------------------
     * 2. Si le fichier est vide, écrire l'entête HTML
     * --------------------------------------------------------- */
    fseek(f, 0, SEEK_END);
    if (ftell(f) == 0) {
        fprintf(f,
            "<!DOCTYPE html>\n"
            "<html lang=\"fr\">\n"
            "<head>\n"
            "  <meta charset=\"UTF-8\">\n"
            "  <title>Logs du Restaurant</title>\n"
            "  <style>\n"
            "    body { font-family: Arial, sans-serif; background: #f4f4f4; }\n"
            "    .log { margin: 10px; padding: 10px; background: #fff; "
                      "border-left: 4px solid #007BFF; }\n"
            "    .time { color: gray; font-size: 0.9em; }\n"
            "  </style>\n"
            "</head>\n"
            "<body>\n"
            "<h1>Logs du Restaurant</h1>\n"
        );
    }

    /* ---------------------------------------------------------
     * 3. Écrire un log formaté
     * --------------------------------------------------------- */
    fprintf(f,
        "<div class=\"log\">\n"
        "  <div class=\"time\">[%02d:%02d:%02d]</div>\n"
        "  <div class=\"msg\">%s</div>\n"
        "</div>\n",
        t->tm_hour, t->tm_min, t->tm_sec, message
    );

    fclose(f);
}
