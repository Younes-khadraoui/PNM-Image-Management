#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pnm.h"

int main(int argc, char *argv[]) {
    if (argc != 7) {
        printf("Usage: %s -f <format> -i <image_input> -o <image_output>\n", argv[0]);
        return 1;
    }

    char *format = NULL;
    char *input_filename = NULL;
    char *output_filename = NULL;

    for (int i = 1; i < argc; i += 2) {
        if (strcmp(argv[i], "-f") == 0) {
            format = argv[i + 1];
        } else if (strcmp(argv[i], "-i") == 0) {
            input_filename = argv[i + 1];
        } else if (strcmp(argv[i], "-o") == 0) {
            output_filename = argv[i + 1];
        } else {
            printf("Option non reconnue: %s\n", argv[i]);
            return 1;
        }
    }

    if (format == NULL || input_filename == NULL || output_filename == NULL) {
        printf("Usage: %s -f <format> -i <image_input> -o <image_output>\n", argv[0]);
        return 1;
    }

    PNM *image = NULL;
    if ((strcmp(format, "PPM") == 0 && (strstr(input_filename, ".ppm") == NULL || strstr(output_filename, ".ppm") == NULL)) ||
        (strcmp(format, "PGM") == 0 && (strstr(input_filename, ".pgm") == NULL || strstr(output_filename, ".pgm") == NULL)) ||
        (strcmp(format, "PBM") == 0 && (strstr(input_filename, ".pbm") == NULL || strstr(output_filename, ".pbm") == NULL))) {
        printf("Le format spécifié ne correspond pas aux extensions des fichiers d'entrée ou de sortie.\n");
        return 1;
    }

    int result = load_pnm(&image, input_filename);
    if (result != 0) {
        if (result == -2)
            printf("Le nom du fichier en input est mal formé.\n");
        else if (result == -3)
            printf("Le contenu du fichier en input est malformé.\n");
        else
            printf("Erreur lors du chargement de l'image.\n");
        return 1;
    }

    result = write_pnm(image, output_filename);
    if (result != 0) {
        if (result == -1)
            printf("Le nom du fichier output passé en argument n'est pas valide.\n");
        else if (result == -2)
            printf("L'image n'a pas pu être sauvée dans un fichier.\n");
        return 1;
    }

    free_pnm(image);

    printf("L'image a été sauvegardée avec succès dans %s\n", output_filename);

    return 0;
}
