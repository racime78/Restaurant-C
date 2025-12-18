/*
 * log.c
 * ------
 * Gère l'écriture des logs dans un fichier HTML.
 * - write_log() : ajoute un message formaté avec l'heure dans logs.html.
 * - Si le fichier est vide, écrit l'entête HTML et le style CSS.
 * 
 * Rôle : tracer toutes les actions du restaurant dans une page lisible par navigateur.
 */


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "log.h"

void write_log(const char *message) {
    FILE *f = fopen("logs.html", "a"); // ouverture en ajout
    if (!f) {
        perror("Erreur ouverture logs.html");
        return;
    }

    // Récupérer l'heure actuelle
    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    // Si le fichier est vide, écrire l'entête HTML
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
            "    .log { margin: 10px; padding: 10px; background: #fff; border-left: 4px solid #007BFF; }\n"
            "    .time { color: gray; font-size: 0.9em; }\n"
            "  </style>\n"
            "</head>\n"
            "<body>\n"
            "<h1>Logs du Restaurant</h1>\n"
        );
    }

    // Écrire un log formaté
    fprintf(f,
        "<div class=\"log\">\n"
        "  <div class=\"time\">[%02d:%02d:%02d]</div>\n"
        "  <div class=\"msg\">%s</div>\n"
        "</div>\n",
        t->tm_hour, t->tm_min, t->tm_sec, message
    );

    fclose(f);
}
