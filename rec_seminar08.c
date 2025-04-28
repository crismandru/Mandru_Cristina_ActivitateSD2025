#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;

struct Nod {
	Masina info;
	struct Nod* st;
	struct Nod* dr;
};
typedef struct Nod Nod;

Masina citireMasinaDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Masina m1;
	aux = strtok(buffer, sep);
	m1.id = atoi(aux);
	m1.nrUsi = atoi(strtok(NULL, sep));
	m1.pret= atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	m1.model = malloc(strlen(aux) + 1);
	strcpy_s(m1.model, strlen(aux) + 1, aux);

	aux = strtok(NULL, sep);
	m1.numeSofer = malloc(strlen(aux) + 1);
	strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);

	m1.serie = *strtok(NULL, sep);
	return m1;
}

void afisareMasina(Masina masina) {
	printf("Id: %d\n", masina.id);
	printf("Nr. usi : %d\n", masina.nrUsi);
	printf("Pret: %.2f\n", masina.pret);
	printf("Model: %s\n", masina.model);
	printf("Nume sofer: %s\n", masina.numeSofer);
	printf("Serie: %c\n\n", masina.serie);
}


void adaugaMasinaInArbore(Nod** arbore, Masina masinaNoua) {
	if (!(*arbore)) {
		Nod* nou = (Nod*)malloc(sizeof(Nod));
		nou->info = masinaNoua;
		nou->st = NULL;
		nou->dr = NULL;
		(*arbore) = nou;
	}
	else {
		if((*arbore)->info.id > masinaNoua.id) {
			adaugaMasinaInArbore(&((*arbore)->st), masinaNoua);
		}
		else if(((*arbore)->info.id < masinaNoua.id)) {
			adaugaMasinaInArbore(&((*arbore)->dr), masinaNoua);
		}
		//else {
		//	printf("Masina cu id-ul %d exista deja in arbore!\n", masinaNoua.id);
		//}
	}
}

void* citireArboreDeMasiniDinFisier(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	if (!f) {
		printf("Eroare la deschiderea fisierului %s\n", numeFisier);
		return NULL;
	}
	Nod* arbore = NULL;
	while (!feof(f)) {
		Masina m = citireMasinaDinFisier(f);
		adaugaMasinaInArbore(&arbore, m);
	}
	fclose(f);
	return arbore;
}

void afisareMasiniDinArbore(/*arbore de masini*/) {
	//afiseaza toate elemente de tip masina din arborele creat
	//prin apelarea functiei afisareMasina()
	//parcurgerea arborelui poate fi realizata in TREI moduri
	//folositi toate cele TREI moduri de parcurgere mai jooos
}

// SRD - inordine - elemente ordonate crescător
void afisareInOdine(Nod* arbore) {
	if (arbore) {
		afisareInOdine(arbore->st);
		afisareMasina(arbore->info);
		afisareInOdine(arbore->dr);
	}
}

// RSD
void afisarePreOrdine(Nod* arbore) {
	if (arbore) {
		afisareMasina(arbore->info);
		afisarePreOrdine(arbore->st);
		afisarePreOrdine(arbore->dr);
	}
}

// SDR
void afisarePostOrdine(Nod* arbore) {
	if (arbore) {
		afisarePostOrdine(arbore->st);
		afisarePostOrdine(arbore->dr);
		afisareMasina(arbore->info);
	}
}

void dezalocareArboreDeMasini(Nod** arbore) {
	if (*arbore) {
		dezalocareArboreDeMasini(&((*arbore)->st));
		dezalocareArboreDeMasini(&((*arbore)->dr));
		free((*arbore)->info.model);
		free((*arbore)->info.numeSofer);
		free(*arbore);
		*arbore = NULL;
	}
}

Masina getMasinaByID(Nod* arbore, int id) {
	if (arbore) {
		if (arbore->info.id < id) {
			return getMasinaByID(arbore->dr, id);
		}
		else if (arbore->info.id > id) {
			return getMasinaByID(arbore->st, id);
		}
		else {
			return arbore->info;
		}
	}
}

int determinaNumarNoduri(Nod* arbore) {
	if (arbore) {
		return 1 + determinaNumarNoduri(arbore->st) + determinaNumarNoduri(arbore->dr);
	}
	else {
		return 0;
	}
	return 0;
}

int calculeazaInaltimeArbore(Nod* arbore) {
	if (arbore) {
		int inaltimeSt = calculeazaInaltimeArbore(arbore->st);
		int inaltimeDr = calculeazaInaltimeArbore(arbore->dr);
		return 1 + (inaltimeSt > inaltimeDr ? inaltimeSt : inaltimeDr);
	}
	else {
		return 0;
	}
	return 0;
}

float calculeazaPretTotal(Nod* arbore) {
	if (arbore == NULL) {
		return 0;
	}
	float totalStanga = calculeazaPretTotal(arbore->st);
	float totalDreapta = calculeazaPretTotal(arbore->dr);
	return arbore->info.pret + totalStanga + totalDreapta;
}

float calculeazaPretulMasinilorUnuiSofer(Nod* arbore, const char* numeSofer) {
	//calculeaza pretul tuturor masinilor unui sofer.
	if (arbore) {
		float pret = 0;
		if (strcmp(arbore->info.numeSofer, numeSofer) == 0) {
			pret += arbore->info.pret;
		}
		return pret + calculeazaPretulMasinilorUnuiSofer(arbore->st, numeSofer) + calculeazaPretulMasinilorUnuiSofer(arbore->dr, numeSofer);
	}
	else {
		return 0;
	}
}

int main() {
	Nod* radacina = NULL;
	radacina = citireArboreDeMasiniDinFisier("masini_arbore.txt");
	printf("Afisarea masinilor InOrdine\n\n");
	afisareInOdine(radacina);

	int id = 8;
	Masina m = getMasinaByID(radacina, id);
	printf("\nAfisarea masinii cu ID-ul 8\n\n");
	afisareMasina(m);

	int nrNoduri = determinaNumarNoduri(radacina);
	printf("\nNumarul de noduri din arbore este: %d\n", nrNoduri);

	int inaltimeArbore = calculeazaInaltimeArbore(radacina);
	printf("\nInaltimea arborelui este: %d\n", inaltimeArbore);

	float pretTotal = calculeazaPretTotal(radacina);
	printf("\nPretul total al masinilor din arbore este: %.2f\n", pretTotal);

	float pretulTotalAlMasinilor = calculeazaPretulMasinilorUnuiSofer(radacina, "Gheorghe");
	printf("\nPretul total al masinilor lui Gheorghe este: %.2f\n", pretulTotalAlMasinilor);

	dezalocareArboreDeMasini(&radacina);

	return 0;
}