#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Campionat Campionat;
struct Campionat {
	int id;
	char* tara;
    char* nume;
    int nrEchipe;
    int nrJucatori;
};

typedef struct Nod Nod;
struct Nod {
    Campionat info;
    Nod* st;
    Nod* dr;
    int gradEchilibru;
};

Campionat citireCampionatDinFisier(FILE* file) {
    Campionat c;
    char buffer[100];
    char sep[3] = ",\n";
    char* aux;
    fgets(buffer, 100, file);

    aux = strtok(buffer, sep);
    c.id = atoi(aux);
    aux = strtok(NULL, sep);
    c.tara = malloc(strlen(aux) + 1);
    strcpy_s(c.tara, strlen(aux) + 1, aux);
    aux = strtok(NULL, sep);
    c.nume = malloc(strlen(aux) + 1);
    strcpy_s(c.nume, strlen(aux) + 1, aux);
    c.nrEchipe = atoi(strtok(NULL, sep));
    c.nrJucatori = atoi(strtok(NULL, sep));

    return c;
}

void afisareCampionat(Campionat campionat) {
    printf("Id: %d\n", campionat.id);
    printf("Tara: %s\n", campionat.tara);
    printf("Nume: %s\n", campionat.nume);
    printf("Nr. echipe: %d\n", campionat.nrEchipe);
    printf("Nr. jucatori: %d\n\n", campionat.nrJucatori);
}

int inaltime(Nod* arbore) {
    if (arbore) {
        int inaltimeSt = inaltime(arbore->st);
        int inaltimeDr = inaltime(arbore->dr);
        return 1 + (inaltimeSt > inaltimeDr ? inaltimeSt : inaltimeDr);
    }
}

void rotireSt(Nod** arbore) {
    Nod* aux = (*arbore)->dr;
    (*arbore)->dr = aux->st;
    aux->st = *arbore;
    *arbore = aux;
}

void rotireDr(Nod** arbore) {
    Nod* aux = (*arbore)->st;
    (*arbore)->st = aux->dr;
    aux->dr = *arbore;
    *arbore = aux;
}

void adaugaCampionatInAVL(Nod** arbore, Campionat campionatNou) {
    if (*arbore == NULL) {
        Nod* nou = (Nod*)malloc(sizeof(Nod));
        nou->info = campionatNou;
        nou->st = nou->dr = NULL;
        nou->gradEchilibru = 0;
        *arbore = nou;
    }
    else {
        if (campionatNou.id < (*arbore)->info.id) {
            adaugaCampionatInAVL(&((*arbore)->st), campionatNou);
        }
        else if (campionatNou.id > (*arbore)->info.id) {
            adaugaCampionatInAVL(&((*arbore)->dr), campionatNou);
        }
    }

    int st = inaltime((*arbore)->st);
    int dr = inaltime((*arbore)->dr);
    (*arbore)->gradEchilibru = st - dr;
    
    if ((*arbore)->gradEchilibru > 1) {
        if (campionatNou.id < (*arbore)->st->info.id) {
            rotireDr(arbore);
        }
        else {
            rotireSt(&(*arbore)->st);
            rotireDr(arbore);
        }
    }
    else if ((*arbore)->gradEchilibru < -1) {
        if (campionatNou.id > (*arbore)->dr->info.id) {
            rotireSt(arbore);
        }
        else {
            rotireDr(&(*arbore)->dr);
            rotireSt(arbore);
        }
    }
}

Nod* citireArboreDinFisier(const char* numeFisier) {
    Nod* arbore = NULL;
    FILE* file = fopen(numeFisier, "r");
    while (!feof(file)) {
        Campionat c = citireCampionatDinFisier(file);
        adaugaCampionatInAVL(&arbore, c);
    }
    fclose(file);
    return arbore;
}

void afisareInOrdine(Nod* arbore) {
    if (arbore) {
        afisareInOrdine(arbore->st);
        afisareCampionat(arbore->info);
        afisareInOrdine(arbore->dr);
    }
}

void afisarePreOrdine(Nod* arbore) {
    if (arbore) {
        afisareCampionat(arbore->info);
        afisarePreOrdine(arbore->st);
        afisarePreOrdine(arbore->dr);
    }
}

Campionat getCampionatDupaId(Nod* arbore, int id) {
    if (arbore) {
        if (id < arbore->info.id) {
            return getCampionatDupaId(arbore->st, id);
        }
        else if (id > arbore->info.id) {
            return getCampionatDupaId(arbore->dr, id);
        }
        else {
            return arbore->info;
        }
    }
}

int determinaNrNoduri(Nod* arbore) {
    if (arbore) {
        int noduriSt = determinaNrNoduri(arbore->st);
        int noduriDr = determinaNrNoduri(arbore->dr);
        return 1 + noduriSt + noduriDr;
    }
    return 0;
}

int calculeazaJucatoriTotali(Nod* arbore) {
    if (arbore) {
        int jucatoriSt = calculeazaJucatoriTotali(arbore->st);
        int jucatoriDr = calculeazaJucatoriTotali(arbore->dr);
        return arbore->info.nrJucatori + jucatoriSt + jucatoriDr;
    }
    return 0;
}

int calculeazaNrEchipeTara(Nod* arbore, const char* taraCautata) {
    int nrEchipeTara = 0;
    if (arbore) {
        if (strcmp(arbore->info.tara, taraCautata) == NULL) {
            nrEchipeTara += arbore->info.nrEchipe;
        }
        nrEchipeTara += calculeazaNrEchipeTara(arbore->st, taraCautata);
        nrEchipeTara += calculeazaNrEchipeTara(arbore->dr, taraCautata);
    }
    return nrEchipeTara;
}

void dezalocare(Nod** arbore) {
    if (*arbore) {
        dezalocare(&(*arbore)->st);
        dezalocare(&(*arbore)->dr);
        free((*arbore)->info.nume);
        free((*arbore)->info.tara);
        free(*arbore);
        *arbore = NULL;
    }
}

int main() {
    Nod* arbore = citireArboreDinFisier("campionate.txt");
    afisarePreOrdine(arbore);

    printf("Campionatul cu ID-ul 5\n");
    afisareCampionat(getCampionatDupaId(arbore, 5));

    printf("Numarul de campionate: %d", determinaNrNoduri(arbore));
    
    printf("\nNumarul total de jucatori este: %d", calculeazaJucatoriTotali(arbore));

    printf("\nNumarul de echipe in Romania: %d", calculeazaNrEchipeTara(arbore, "Romania"));
    printf("\n");

    dezalocare(&arbore);
    return 0;
}