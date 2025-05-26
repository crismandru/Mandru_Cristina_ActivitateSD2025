#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Masina Masina;
struct Masina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};

typedef struct Nod Nod;
struct Nod {
	Masina info;
	Nod* st;
	Nod* dr;
	int gradEchilibru;
};

Masina citireMasinaDinFisier(FILE* file) {
	Masina m;
	char buffer[100];
	char sep[3] = ",\n";
	char* aux;
	fgets(buffer, 100, file);
	
	aux = strtok(buffer, sep);
	m.id = atoi(aux);
	m.nrUsi = atoi(strtok(NULL, sep));
	m.pret = atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	m.model = malloc(strlen(aux) + 1);
	strcpy_s(m.model, strlen(aux) + 1, aux);
	aux = strtok(NULL, sep);
	m.numeSofer = malloc(strlen(aux) + 1);
	strcpy_s(m.numeSofer, strlen(aux) + 1, aux);
	m.serie = *strtok(NULL, sep);

	return m;
}

void afisareMasina(Masina masina) {
	printf("Id: %d\n", masina.id);
	printf("Nr. usi : %d\n", masina.nrUsi);
	printf("Pret: %.2f\n", masina.pret);
	printf("Model: %s\n", masina.model);
	printf("Nume sofer: %s\n", masina.numeSofer);
	printf("Serie: %c\n\n", masina.serie);
}

int inaltime(Nod* arbore) {
	if (arbore) {
		int inaltimeSt = inaltime(arbore->st);
		int inaltimeDr = inaltime(arbore->dr);
		return 1 + (inaltimeSt > inaltimeDr ? inaltimeSt : inaltimeDr);
	}
}

void rotireSt(Nod** radacina) {
	Nod* aux = (*radacina)->dr;
	(*radacina)->dr = aux->st;
	aux->st = (*radacina);
	(*radacina) = aux;
}

void rotireDr(Nod** radacina) {
	Nod* aux = (*radacina)->st;
	(*radacina)->st = aux->dr;
	aux->dr = (*radacina);
	(*radacina) = aux;
}

void adaugaMasinaInAVL(Nod** arbore, Masina masinaNoua) {
	if (!(*arbore)) {
		Nod* nou = (Nod*)malloc(sizeof(Nod));
		nou->info = masinaNoua;
		nou->st = nou->dr = NULL;
		nou->gradEchilibru = 0;
		*arbore = nou;
	}
	else {
		if (masinaNoua.id < (*arbore)->info.id) {
			adaugaMasinaInAVL(&((*arbore)->st), masinaNoua);
		}
		else if (masinaNoua.id > (*arbore)->info.id) {
			adaugaMasinaInAVL(&((*arbore)->dr), masinaNoua);
		}
	}

	// recalculăm echilibrul
	int st = inaltime((*arbore)->st);
	int dr = inaltime((*arbore)->dr);
	(*arbore)->gradEchilibru = st - dr;

	if ((*arbore)->gradEchilibru > 1) {
		if (masinaNoua.id < (*arbore)->st->info.id) {
			rotireDr(arbore);
		}
		else {
			rotireSt(&(*arbore)->st);
			rotireDr(arbore);
		}
	}
	else if ((*arbore)->gradEchilibru < -1) {
		if (masinaNoua.id > (*arbore)->dr->info.id) {
			rotireSt(arbore);
		}
		else {
			rotireDr(&(*arbore)->dr);
			rotireSt(arbore);
		}
	}
}

Nod* citireArboreDinFisier(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	Nod* arbore = NULL;
	while (!feof(f)) {
		Masina m = citireMasinaDinFisier(f);
		adaugaMasinaInAVL(&arbore, m);
	}
	fclose(f);
	return arbore;
}

void afisareInOrdine(Nod* arbore) {
	if (arbore) {
		afisareInOrdine(arbore->st);
		afisareMasina(arbore->info);
		afisareInOrdine(arbore->dr);
	}
}

void afisarePreOrdine(Nod* arbore) {
	if (arbore) {
		afisareMasina(arbore->info);
		afisarePreOrdine(arbore->st);
		afisarePreOrdine(arbore->dr);
	}
} 

void afisarePostOrdine(Nod* arbore) {
	if (arbore) {
		afisarePostOrdine(arbore->st);
		afisarePostOrdine(arbore->dr);
		afisareMasina(arbore->info);
	}
}

Masina getMasinaDupaId(Nod* arbore, int id) {
	if (arbore) {
		if (arbore->info.id < id) {
			return getMasinaDupaId(arbore->dr, id);
		}
		else if (arbore->info.id > id) {
			return getMasinaDupaId(arbore->st, id);
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

float calculeazaPretTotal(Nod* arbore) {
	if (arbore) {
		float pretSt = calculeazaPretTotal(arbore->st);
		float pretDr = calculeazaPretTotal(arbore->dr);
		return arbore->info.pret + pretSt + pretDr;
	}
	return 0;
}

float calculeazaPretulMasinilorUnuiSofer(Nod* arbore, const char* numeSofer) {
	float pretTotal = 0;
	if (arbore) {
		if (strcmp(arbore->info.numeSofer, numeSofer) == 0) {
			pretTotal += arbore->info.pret;
		}
		pretTotal += calculeazaPretulMasinilorUnuiSofer(arbore->st, numeSofer);
		pretTotal += calculeazaPretulMasinilorUnuiSofer(arbore->dr, numeSofer);
	}
	return pretTotal;
}

void dezalocareArboreDeMasini(Nod** arbore) {
	if (*arbore) {
		dezalocareArboreDeMasini(&(*arbore)->st);
		dezalocareArboreDeMasini(&(*arbore)->dr);
		free((*arbore)->info.model);
		free((*arbore)->info.numeSofer);
		free(*arbore);
		*arbore = NULL;
	}
}

int main() {
	Nod* arbore = citireArboreDinFisier("masini.txt");
	afisarePostOrdine(arbore);

	printf("Masina 3: \n");
	afisareMasina(getMasinaDupaId(arbore, 3));

	printf("Numar noduri: %d", determinaNrNoduri(arbore));

	printf("\nPret total: %.2f", calculeazaPretTotal(arbore));

	printf("\nIonescu are masini in valoare de %.2f", calculeazaPretulMasinilorUnuiSofer(arbore, "Ionescu"));

	dezalocareArboreDeMasini(&arbore);
	return 0;
}