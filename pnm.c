#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pnm.h"

int load_pnm(PNM **image, char *filename) {
    
    if (strstr(filename, ".ppm") == NULL && strstr(filename, ".pgm") == NULL && strstr(filename, ".pbm") == NULL) {
        return -2; 
    }

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return -3;
    }

    *image = (PNM *)malloc(sizeof(PNM));
    if (*image == NULL) {
        fclose(file);
        return -1; 
    }

    if (fscanf(file, "%s", (*image)->magic_number) != 1) {
        fclose(file);
        free(*image);
        return -3; 
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        if (line[0] != '#' && line[0] != '\n' && line[0] != '\r') { 
            break; 
        }
    }

    if (sscanf(line, "%d %d", &(*image)->width, &(*image)->height) != 2) {
        fclose(file);
        free(*image);
        return -3;
    }

    if (strcmp((*image)->magic_number, "P1") == 0) {
        (*image)->max_value = 1;
    } else {
        if (fscanf(file, "%d", &(*image)->max_value) != 1) {
            fclose(file);
            free(*image);
            return -3; 
        }
    }


    (*image)->pixels = (int **)malloc((*image)->height * sizeof(int *));
    if ((*image)->pixels == NULL) {
        fclose(file);
        free(*image);
        return -1; 
    }
    for (int i = 0; i < (*image)->height; i++) {
        (*image)->pixels[i] = (int *)malloc((*image)->width * sizeof(int));
        if ((*image)->pixels[i] == NULL) {
            fclose(file);
            free_pnm(*image);
            return -1;
        }
    }

    for (int i = 0; i < (*image)->height; i++) {
        for (int j = 0; j < (*image)->width; j++) {
            if (fscanf(file, "%d", &(*image)->pixels[i][j]) != 1) {
                printf("Failed to read pixel data.\n");
                fclose(file);
                free_pnm(*image);
                return -3; 
            }
        }
    }

    fclose(file);
    return 0; 
}

int write_pnm(PNM *image, char *filename) {
    if (strstr(filename, ".ppm") == NULL && strstr(filename, ".pgm") == NULL && strstr(filename, ".pbm") == NULL) {
        return -1; 
    }

    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        return -2; 
    }

    fprintf(file, "%s\n", image->magic_number);
    fprintf(file, "%d %d\n", image->width, image->height);
    fprintf(file, "%d\n", image->max_value);

    for (int i = 0; i < image->height; i++) {
        for (int j = 0; j < image->width; j++) {
            fprintf(file, "%d ", image->pixels[i][j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
    return 0; 
}

void free_pnm(PNM *image) {
    if (image == NULL) return; 

    if (image->pixels != NULL) {
        for (int i = 0; i < image->height; i++) {
            free(image->pixels[i]);
        }
        free(image->pixels);
    }

    free(image);
}
