#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Fotbalist Fotbalist;
struct Fotbalist {
	int id;
	char* nume;
	float salariu;
};

typedef struct Nod Nod;
struct Nod {
	Fotbalist info;
	Nod* st;
	Nod* dr;
	int gradEchilibru;
};

Fotbalist citesteFotbalistDinFisier(FILE* file) {
	Fotbalist f;
	char buffer[100];
	char sep[3] = ",\n";
	char* aux;
	fgets(buffer, 100, file);

	aux = strtok(buffer, sep);
	f.id = atoi(aux);
	aux = strtok(NULL, sep);
	f.nume = malloc(strlen(aux) + 1);
	strcpy_s(f.nume, strlen(aux) + 1, aux);
	aux = strtok(NULL, sep);
	f.salariu = atof(aux);
	return f;
}

void afisareFotbalist(Fotbalist fotbalist) {
	printf("\nID: %d", fotbalist.id);
	printf("\nNume: %s", fotbalist.nume);
	printf("\nSalariu: %.2f", fotbalist.salariu);
	printf("\n");
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

void adaugaFotbalistInArbore(Nod** arbore, Fotbalist fotbalistNou) {
	if ((*arbore) == NULL) {
		Nod* nou = (Nod*)malloc(sizeof(Nod));
		nou->info = fotbalistNou;
		nou->st = nou->dr = NULL;
		nou->gradEchilibru = 0;
		(*arbore) = nou;
	}
	else {
		if (fotbalistNou.id < (*arbore)->info.id) {
			adaugaFotbalistInArbore(&((*arbore)->st), fotbalistNou);
		}
		if (fotbalistNou.id > (*arbore)->info.id) {
			adaugaFotbalistInArbore(&((*arbore)->dr), fotbalistNou);
		}
	}

	int st = inaltime((*arbore)->st);
	int dr = inaltime((*arbore)->dr);
	(*arbore)->gradEchilibru = st - dr;
	if ((*arbore)->gradEchilibru > 1) {
		if (fotbalistNou.id < (*arbore)->st->info.id) {
			rotireDr(arbore);
		}
		else {
			rotireSt(&(*arbore)->st);
			rotireDr(arbore);
		}
	}
	else if ((*arbore)->gradEchilibru < -1) {
		if (fotbalistNou.id > (*arbore)->dr->info.id) {
			rotireSt(arbore);
		}
		else {
			rotireDr(&(*arbore)->dr);
			rotireSt(arbore);
		}
	}
}

Nod* citireFotbalistiDinFisier(const char* numeFisier) {
	Nod* arbore = NULL;
	FILE* file = fopen(numeFisier, "r");
	while (!feof(file)) {
		Fotbalist f = citesteFotbalistDinFisier(file);
		adaugaFotbalistInArbore(&arbore, f);
	}
	fclose(file);
	return arbore;
}

void afisarePostOrdine(Nod* arbore) {
	if (arbore) {
		afisarePostOrdine(arbore->st);
		afisarePostOrdine(arbore->dr);
		afisareFotbalist(arbore->info);
	}
}

Fotbalist getFotbalistDupaId(Nod* arbore, int id) {
	if (arbore) {
		if (id < arbore->info.id) {
			getFotbalistDupaId(arbore->st, id);
		}
		else if (id > arbore->info.id) {
			getFotbalistDupaId(arbore->dr, id);
		}
		else {
			return arbore->info;
		}
	}
}

int determinaNrFotbalisti(Nod* arbore) {
	if (arbore) {
		int fotbalistiSt = determinaNrFotbalisti(arbore->st);
		int fotbalistiDr = determinaNrFotbalisti(arbore->dr);
		return 1 + fotbalistiSt + fotbalistiDr;
	}
	return 0;
}

void dezalocare(Nod** arbore) {
	if (*arbore) {
		dezalocare(&(*arbore)->st);
		dezalocare(&(*arbore)->dr);
		free((*arbore)->info.nume);
		free(*arbore);
		*arbore = 0;
	}
}

int main() {
	Nod* arbore = citireFotbalistiDinFisier("fotbalisti.txt");
	afisarePostOrdine(arbore);

	printf("\nFotbalistul 3:");
	afisareFotbalist(getFotbalistDupaId(arbore, 3));

	printf("\nNumarul de fotbalisti: %d", determinaNrFotbalisti(arbore));

	dezalocare(&arbore);
	return 0;
}