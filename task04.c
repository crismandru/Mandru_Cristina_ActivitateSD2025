#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Campionat {
    int id;
    char* tara;
    char* nume;
    int nrEchipe;
    int nrJucatori;
};
typedef struct Campionat Campionat;

Campionat citireCampionatFisier(FILE* file) {
    Campionat c;
    char buffer[100];
    char separator[] = ",\n";

    if (fgets(buffer, 100, file) == NULL) {
        c.id = -1;
        return c;
    }

    char* token = strtok(buffer, separator);
    c.id = atoi(token);

    token = strtok(NULL, separator);
    c.tara = malloc(strlen(token) + 1);
    strcpy(c.tara, token);

    token = strtok(NULL, separator);
    c.nume = malloc(strlen(token) + 1);
    strcpy(c.nume, token);

    token = strtok(NULL, separator);
    c.nrEchipe = atoi(token);

    token = strtok(NULL, separator);
    c.nrJucatori = atoi(token);

    return c;
}

Campionat* citireVectorDinFisier(const char* numeFisier, int* nrCampionate) {
    FILE* f = fopen(numeFisier, "r");
    if (!f) {
        printf("Eroare la deschiderea fisierului!\n");
        return NULL;
    }

    Campionat* vectorCampionate = NULL;
    *nrCampionate = 0;
    while (!feof(f)) {
        Campionat c = citireCampionatFisier(f);
        if (c.id == -1) break;

        vectorCampionate = realloc(vectorCampionate, (*nrCampionate + 1) * sizeof(Campionat));
        vectorCampionate[*nrCampionate] = c;
        (*nrCampionate)++;
    }
    fclose(f);
    return vectorCampionate;
}

Campionat** creeazaMatrice(Campionat* vectorCampionate, int nrCampionate, int* nrLinii) {
    *nrLinii = 0;
    int capacitate = 10;
    Campionat** matrice = malloc(capacitate * sizeof(Campionat*));
    int* dimLinii = calloc(capacitate, sizeof(int));

    for (int i = 0; i < nrCampionate; i++) {
        int found = 0;
        for (int j = 0; j < *nrLinii; j++) {
            if (matrice[j][0].nrEchipe == vectorCampionate[i].nrEchipe) {
                matrice[j] = realloc(matrice[j], (dimLinii[j] + 1) * sizeof(Campionat));
                matrice[j][dimLinii[j]++] = vectorCampionate[i];
                found = 1;
                break;
            }
        }
        if (!found) {
            if (*nrLinii >= capacitate) {
                capacitate *= 2;
                matrice = realloc(matrice, capacitate * sizeof(Campionat*));
                dimLinii = realloc(dimLinii, capacitate * sizeof(int));
            }
            matrice[*nrLinii] = malloc(sizeof(Campionat));
            matrice[*nrLinii][0] = vectorCampionate[i];
            dimLinii[*nrLinii] = 1;
            (*nrLinii)++;
        }
    }
    free(dimLinii);
    return matrice;
}

void sorteazaMatricea(Campionat** matrice, int* dimLinii, int nrLinii) {
    for (int i = 0; i < nrLinii - 1; i++) {
        for (int j = i + 1; j < nrLinii; j++) {
            if (dimLinii[i] < dimLinii[j]) {
                Campionat* temp = matrice[i];
                matrice[i] = matrice[j];
                matrice[j] = temp;
                int tempDim = dimLinii[i];
                dimLinii[i] = dimLinii[j];
                dimLinii[j] = tempDim;
            }
        }
    }
}

void afisareMatrice(Campionat** matrice, int* dimLinii, int nrLinii) {
    for (int i = 0; i < nrLinii; i++) {
        printf("Cluster %d (Nr Echipe: %d):\n", i + 1, matrice[i][0].nrEchipe);
        for (int j = 0; j < dimLinii[i]; j++) {
            printf("  - %s (%s)\n", matrice[i][j].nume, matrice[i][j].tara);
        }
    }
}

int main() {
    int nrCampionate = 0;
    Campionat* vectorCampionate = citireVectorDinFisier("campionate.txt", &nrCampionate);
    if (!vectorCampionate) return -1;

    int nrLinii = 0;
    Campionat** matrice = creeazaMatrice(vectorCampionate, nrCampionate, &nrLinii);

    int* dimLinii = calloc(nrLinii, sizeof(int));
    for (int i = 0; i < nrLinii; i++) dimLinii[i] = 1;

    sorteazaMatricea(matrice, dimLinii, nrLinii);
    afisareMatrice(matrice, dimLinii, nrLinii);

    free(dimLinii);
    for (int i = 0; i < nrLinii; i++) free(matrice[i]);
    free(matrice);
    for (int i = 0; i < nrCampionate; i++) {
        free(vectorCampionate[i].tara);
        free(vectorCampionate[i].nume);
    }
    free(vectorCampionate);
    return 0;
}