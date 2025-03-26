﻿#define _CRT_SECURE_NO_WARNINGS
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
		listaDubla->head == nodNou;
		listaDubla->nrNoduri++;
	}
	else {
		listaDubla->tail->next = nodNou;
		listaDubla->nrNoduri++;
	}

	listaDubla->tail = nodNou;
}

void adaugaMasinaInListaDeLaInceput(listaDubla* listaDubla, Masina masinaNoua) {
	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
	nodNou->info = masinaNoua;
	nodNou->next = listaDubla->head;
	nodNou->prev = NULL;

	if (listaDubla->tail == NULL) {
		listaDubla->tail == nodNou;
		listaDubla->nrNoduri++;
	}
	else {
		listaDubla->head->prev = nodNou;
		listaDubla->nrNoduri++;
	}

	listaDubla->head = nodNou;
}

void adaugaLaInceputInLista(listaDubla* listaDubla, Masina masinaNoua) {
	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
	nodNou->info = masinaNoua;
	nodNou->prev = NULL;
	nodNou->next = listaDubla->head;

	if (listaDubla->tail == NULL) {
		listaDubla->tail == nodNou;
		listaDubla->nrNoduri++;
	}
	else {
		listaDubla->head->prev = nodNou;
		listaDubla->nrNoduri++;
	}

	listaDubla->head = nodNou;
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
	return listaDubla.nrNoduri?suma/listaDubla.nrNoduri:0;
}

void stergeMasinaDupaID(/*lista masini*/ int id) {
	//sterge masina cu id-ul primit.
	//tratati situatia ca masina se afla si pe prima pozitie, si pe ultima pozitie
}

char* getNumeSoferMasinaScumpa(listaDubla lista) {
	Nod* temp = lista.head;
	Nod* maxim = lista.head;
	while (temp) {
		if (temp->info.pret > maxim->info.pret) {
			maxim = temp;
		}
		temp = temp->next;
	}
	char* nume = (char*)malloc(sizeof(strlen(temp->info.numeSofer) + 1 ));
	strcpy_s(maxim->info.numeSofer, strlen(temp->info.numeSofer) + 1, temp->info.numeSofer);
	return nume;
}

int main() {
	listaDubla lista;
	lista = citireLDMasiniDinFisier("masini.txt");
	printf("Lista de masini de la coada la cap\n");
	afisareListaMasiniDeLaFinal(lista);

	printf("Lista de masini de la cap la coada \n");
	afisareListaMasiniDeLaInceput(lista);

	float pretMediu = 0;
	pretMediu = calculeazaPretMediu(lista);
	printf("Pretul mediu este %d\n");


	dezalocareLDMasini(&lista);

	return 0;
}