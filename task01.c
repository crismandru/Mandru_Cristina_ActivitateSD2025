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

struct Campionat initializare(int idNou, const char* taraNoua, const char* numeNou, int nrEchipeNou, int nrJucatoriNou) {
	struct Campionat c;
	c.id = idNou;
	c.tara = malloc(sizeof(char) * (strlen(taraNoua) + 1));
	strcpy_s(c.tara, strlen(taraNoua) + 1, taraNoua);
	c.nume = malloc(sizeof(char) * (strlen(numeNou) + 1));
	strcpy_s(c.nume, strlen(numeNou) + 1, numeNou);
	c.nrEchipe = nrEchipeNou;
	c.nrJucatori = nrJucatoriNou;
	return c;
}

struct Campionat citire() {
	struct Campionat c;

	printf("Introduceti ID-ul campionatului: ");
	scanf("%d", &c.id);
	getchar();

	c.tara = malloc(sizeof(char) * 100);
	c.nume = malloc(sizeof(char) * 100);

	printf("Introduceti tara campionatului: ");
	fgets(c.tara, sizeof(c.tara), stdin);
	c.tara[strcspn(c.tara, "\n")] = 0;

	printf("Introduceti numele campionatului: ");
	fgets(c.nume, sizeof(c.nume), stdin);
	c.nume[strcspn(c.nume, "\n")] = 0;

	printf("Introduceti numarul de echipe: ");
	scanf("%d", &c.nrEchipe);

	printf("Introduceti numarul de jucatori: ");
	scanf("%d", &c.nrJucatori);

	return c;
}

void afisare(struct Campionat c) {
	printf("Id: %d\nTara: %s\nNume: %s\nNumarul de echipe: %d\nNumarul de jucator: %d\n\n",
		c.id, c.tara, c.nume, c.nrEchipe, c.nrJucatori);
}

void calculeazaMedieJucatoriEchipa(struct Campionat c) {
	if (c.nrEchipe == 0) {
		printf("Numarul de echipe nu poate fi 0.\n");
	}
	else {
		float medie = (float)c.nrJucatori / c.nrEchipe;
		printf("Media jucatorilor pe echipa in campionatul %s este: %.2f\n", c.nume, medie);
	}
}

void modificaNumeCampionat(struct Campionat* c, const char* numeNou) {
	free(c->nume);
	c->nume = malloc(sizeof(char) * (strlen(numeNou) + 1));
	strcpy_s(c->nume, strlen(numeNou) + 1, numeNou);
}

int main() {
	struct Campionat c1, c2, c3;
	c1 = initializare(1, "Romania", "Liga 1", 16, 468);
	c2 = initializare(2, "Romania", "Liga 2", 22, 573);
	c3 = initializare(3, "Germania", "Bundesliga", 18, 508);
	afisare(c1);
	afisare(c2);
	afisare(c3);

	modificaNumeCampionat(&c1, "Liga 1 Superliga");
	printf("\nCampionat cu nume schimbat:\n");
	afisare(c1);

	struct Campionat c4 = citire();
	afisare(c4);

	calculeazaMedieJucatoriEchipa(c1);
	calculeazaMedieJucatoriEchipa(c2);
	calculeazaMedieJucatoriEchipa(c3);
	calculeazaMedieJucatoriEchipa(c4);

	return 0;
}