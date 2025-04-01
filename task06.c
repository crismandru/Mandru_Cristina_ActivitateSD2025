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

//creare structura pentru un nod dintr-o lista dublu inlantuita
struct Nod {
	Masina info;
	struct Nod* next;
	struct Nod* prev;
};
typedef struct Nod Nod;

//creare structura pentru Lista Dubla 
struct listaDubla {
	Nod* head;
	Nod* tail;
	int nrNoduri; //nu-i obligatoriu dar e mișto să știi na
};
typedef struct listaDubla listaDubla;

Masina citireMasinaDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Masina m1;
	aux = strtok(buffer, sep);
	m1.id = atoi(aux);
	m1.nrUsi = atoi(strtok(NULL, sep));
	m1.pret = atof(strtok(NULL, sep));
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

void afisareListaMasiniDeLaFinal(listaDubla listaDubla) {
	Nod* temp = listaDubla.tail;
	while (temp) {
		afisareMasina(temp->info);
		temp = temp->prev;
	}
}

void afisareListaMasiniDeLaInceput(listaDubla listaDubla) {
	Nod* temp = listaDubla.head;
	while (temp) {
		afisareMasina(temp->info);
		temp = temp->next;
	}
}

void adaugaMasinaInListaLaFinal(listaDubla* listaDubla, Masina masinaNoua) {
	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
	nodNou->info = masinaNoua;
	nodNou->next = NULL;
	nodNou->prev = listaDubla->tail;

	if (listaDubla->head == NULL) {
		listaDubla->head = nodNou;
	}
	else {
		listaDubla->tail->next = nodNou;
	}

	listaDubla->nrNoduri++;
	listaDubla->tail = nodNou;
}

void adaugaLaInceputInLista(listaDubla* listaDubla, Masina masinaNoua) {
	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
	nodNou->info = masinaNoua;
	nodNou->prev = NULL;
	nodNou->next = listaDubla->head;

	if (listaDubla->head == NULL) {
		listaDubla->tail = nodNou;
	}
	else {
		listaDubla->head->prev = nodNou;
	}

	listaDubla->head = nodNou;
	listaDubla->nrNoduri++;
}

listaDubla citireLDMasiniDinFisier(const char* numeFisier) {
	listaDubla lista;
	lista.head = NULL;
	lista.tail = NULL;
	lista.nrNoduri = 0;
	FILE* f = fopen(numeFisier, "r");

	while (!feof(f)) {
		adaugaMasinaInListaLaFinal(&lista, citireMasinaDinFisier(f));
	}
	fclose(f);
	return lista;
}

void dezalocareLDMasini(listaDubla* listaDubla) {
	if (listaDubla->head) {
		Nod* temp = listaDubla->head;
		while (temp->next != NULL) {
			free(temp->info.numeSofer);
			free(temp->info.model);
			temp = temp->next;
			free(temp->prev);
		}
		free(temp->info.numeSofer);
		free(temp->info.model);
		free(temp);
		listaDubla->head = NULL;
		listaDubla->tail = NULL;
		listaDubla->nrNoduri = 0;
	}
}

float calculeazaPretMediu(listaDubla listaDubla) {
	Nod* aux = listaDubla.head;
	float suma = 0;
	while (aux) {
		suma += aux->info.pret;
		aux = aux->next;
	}
	return listaDubla.nrNoduri ? suma / listaDubla.nrNoduri : 0;
}

void stergeMasinaLaPozitie(listaDubla* lista, int pozitie) {
	if (pozitie < 0 || pozitie >= lista->nrNoduri) {
		printf("Pozitia %d este invalida.\n", pozitie);
		return;
	}

	Nod* temp = lista->head;
	for (int i = 0; i < pozitie; i++) {
		temp = temp->next;
	}

	if (temp->prev) {
		temp->prev->next = temp->next;
	}
	else {
		lista->head = temp->next;
	}

	if (temp->next) {
		temp->next->prev = temp->prev;
	}
	else {
		lista->tail = temp->prev;
	}

	free(temp->info.model);
	free(temp->info.numeSofer);
	free(temp);

	lista->nrNoduri--;
}

void adaugaMasinaSortatDupaPret(listaDubla* lista, Masina masinaNoua) {
	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
	nodNou->info = masinaNoua;
	nodNou->next = NULL;
	nodNou->prev = NULL;

	if (lista->head == NULL) {
		lista->head = lista->tail = nodNou;
	}
	else if (masinaNoua.pret < lista->head->info.pret) {
		nodNou->next = lista->head;
		lista->head->prev = nodNou;
		lista->head = nodNou;
	}
	else {
		Nod* temp = lista->head;
		while (temp->next != NULL && temp->next->info.pret < masinaNoua.pret) {
			temp = temp->next;
		}
		nodNou->next = temp->next;
		nodNou->prev = temp;
		temp->next = nodNou;

		if (nodNou->next) {
			nodNou->next->prev = nodNou;
		}
		else {
			lista->tail = nodNou;
		}
	}
	lista->nrNoduri++;
}

void interschimbaMasiniPePozitii(listaDubla* lista, int poz1, int poz2) {
	if (poz1 < 0 || poz2 < 0 || poz1 >= lista->nrNoduri || poz2 >= lista->nrNoduri) {
		printf("Pozitii invalide\n");
		return;
	}

	if (poz1 == poz2) {
		printf("Pozitiile sunt identice, nu este necesara interschimbarea\n");
		return;
	}

	Nod* nod1 = lista->head;
	Nod* nod2 = lista->head;

	for (int i = 0; i < poz1; i++) {
		nod1 = nod1->next;
	}

	for (int i = 0; i < poz2; i++) {
		nod2 = nod2->next;
	}

	Masina temp = nod1->info;
	nod1->info = nod2->info;
	nod2->info = temp;
}

char* getNumeSoferMasinaScumpa(listaDubla lista) {
	//cauta masina cea mai scumpa si 
	Nod* temp = lista.head;
	Nod* maxim = lista.head;
	while (temp) {
		if (temp->info.pret > maxim->info.pret) {
			maxim = temp;
		}
		temp = temp->next;

	}

	char* numeCopiat = (char*)malloc(sizeof(maxim->info.numeSofer) + 1);
	strcpy_s(numeCopiat, strlen(maxim->info.numeSofer) + 1, maxim->info.numeSofer);
	return numeCopiat;
}

int main() {
	listaDubla lista;
	lista = citireLDMasiniDinFisier("masini.txt");
	printf("\nMasinile de la cap la coada\n\n");
	afisareListaMasiniDeLaFinal(lista);
	printf("\nMasinile de la coada la cap\n\n");
	afisareListaMasiniDeLaInceput(lista);
	float pretMediu = 0;
	pretMediu = calculeazaPretMediu(lista);
	printf("Pretul mediu este: %.2f", pretMediu);
	printf("\n");
	char* numeReturnat = getNumeSoferMasinaScumpa(lista);
	printf("\nNume returnat: %s", numeReturnat);
	printf("\n");

	//șterge mașina de pe poziția 2 (a treia mașină)
	stergeMasinaLaPozitie(&lista, 2);
	afisareListaMasiniDeLaInceput(lista);

	Masina m = { 11, 4, 25000.5, "BMW", "Cris", 'X' };
	adaugaMasinaSortatDupaPret(&lista, m);
	afisareListaMasiniDeLaInceput(lista);

	interschimbaMasiniPePozitii(&lista, 4, 7); 
	afisareListaMasiniDeLaInceput(lista);

	dezalocareLDMasini(&lista);
	return 0;
}