#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Album Album;
struct Album {
	int id;
	char* numeAlbum;
	char* numeArtist;
	float durataTotala;
	unsigned int nrMelodii;
	unsigned char rating;
};

typedef struct Nod Nod;
struct Nod {
	Album info;
	Nod* st;
	Nod* dr;
	int gradEchilibru;
};

Album citesteAlbumDinFisier(FILE* file) {
	Album a;
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;

	aux = strtok(buffer, sep);
	a.id = atoi(aux);
	aux = strtok(NULL, sep);
	a.numeAlbum = malloc(strlen(aux) + 1);
	strcpy_s(a.numeAlbum, strlen(aux) + 1, aux);
	aux = strtok(NULL, sep);
	a.numeArtist = malloc(strlen(aux) + 1);
	strcpy_s(a.numeArtist, strlen(aux) + 1, aux);
	aux = strtok(NULL, sep);
	a.durataTotala = atof(aux);
	aux = strtok(NULL, sep);
	a.nrMelodii = (unsigned int)atoi(aux);
	aux = strtok(NULL, sep);
	a.rating = *aux;

	return a;
}

void afiseazaAlbum(Album album) {
	printf("\nId: %d", album.id);
	printf("\nNume album: %s", album.numeAlbum);
	printf("\nNume artist: %s", album.numeArtist);
	printf("\nDurata totala: %.2f", album.durataTotala);
	printf("\nNumar melodii: %u", album.nrMelodii);
	printf("\nRating: %c", album.rating);
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

void adaugaAlbumInAVL(Nod** arbore, Album albumNou) {
	if ((*arbore) == NULL) {
		Nod* nou = (Nod*)malloc(sizeof(Nod));
		nou->info = albumNou;
		nou->st = nou->dr = NULL;
		nou->gradEchilibru = 0;
		(*arbore) = nou;
	}
	else {
		if (albumNou.id < (*arbore)->info.id) {
			adaugaAlbumInAVL(&((*arbore)->st), albumNou);
		}
		else if (albumNou.id > (*arbore)->info.id) {
			adaugaAlbumInAVL(&((*arbore)->dr), albumNou);
		}
	}

	int st = inaltime((*arbore)->st);
	int dr = inaltime((*arbore)->dr);
	(*arbore)->gradEchilibru = st - dr;

	if ((*arbore)->gradEchilibru > 1) {
		if (albumNou.id < (*arbore)->st->info.id) {
			rotireDr(arbore);
		}
		else {
			rotireSt(&(*arbore)->st);
			rotireDr(arbore);
		}
	}
	else if ((*arbore)->gradEchilibru < -1) {
		if (albumNou.id > (*arbore)->dr->info.id) {
			rotireSt(arbore);
		}
		else {
			rotireDr(&(*arbore)->dr);
			rotireSt(arbore);
		}
	}
}

Album getAlbumDupaId(Nod* arbore, int id) {
	if (arbore) {
		if (id < arbore->info.id) {
			return getAlbumDupaId(arbore->st, id);
		}
		else if (id > arbore->info.id) {
			return getAlbumDupaId(arbore->dr, id);
		}
		else {
			return arbore->info;
		}
	}
}

int determinaNrAlbume(Nod* arbore) {
	if (arbore) {
		int albumeSt = determinaNrAlbume(arbore->st);
		int albumeDr = determinaNrAlbume(arbore->dr);
		return 1 + albumeDr + albumeSt;
	}
	return 0;
}

Nod* citireArboreDinFisier(const char* numeFisier) {
	Nod* arbore = NULL;
	FILE* file = fopen(numeFisier, "r");
	while (!feof(file)) {
		Album a = citesteAlbumDinFisier(file);
		adaugaAlbumInAVL(&arbore, a);
	}
	fclose(file);
	return arbore;
}

void afisareInOrdine(Nod* arbore) {
	if (arbore) {
		afisareInOrdine(arbore->st);
		afiseazaAlbum(arbore->info);
		afisareInOrdine(arbore->dr);
	}
}

void dezalocare(Nod** arbore) {
	if (*arbore) {
		dezalocare(&(*arbore)->st);
		dezalocare(&(*arbore)->dr);
		free((*arbore)->info.numeAlbum);
		free((*arbore)->info.numeArtist);
		free(*arbore);
		(*arbore) = NULL;
	}
}

int main() {
	Nod* arbore = citireArboreDinFisier("albume.txt");
	afisareInOrdine(arbore);

	printf("\nAlbumul 5: ");
	afiseazaAlbum(getAlbumDupaId(arbore, 5));

	printf("\nNumarul total de albume: %d", determinaNrAlbume(arbore));

	dezalocare(&arbore);

	return 0;
}