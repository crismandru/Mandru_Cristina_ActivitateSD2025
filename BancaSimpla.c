//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//typedef struct Banca Banca;
//struct Banca {
//	char* numeBanca;
//	int nrSectii;
//	int nrAngajati;
//};
//
//typedef struct Nod Nod;
//struct Nod {
//	Banca info;
//	Nod* next;
//};
//
//void afisareBanca(Banca b) {
//	printf("Banca: %s\n", b.numeBanca);
//	printf("Nr selectii: %d\n", b.nrSectii);
//	printf("Nr angajati: %d\n\n", b.nrAngajati);
//}
//
//void afisareBanci(Nod* cap) {
//	while (cap) {
//		afisareBanca(cap->info);
//		cap = cap->next;
//	}
//}
//
//Banca citireBancaDinFisier(FILE* file) {
//	Banca b;
//	char buffer[100];
//	char sep[3] = ",\n";
//	fgets(buffer, 100, file);
//	char* aux;
//
//	aux = strtok(buffer, sep);
//	b.numeBanca = malloc(strlen(aux) + 1);
//	strcpy_s(b.numeBanca, strlen(aux) + 1, aux);
//
//	b.nrSectii = atoi(strtok(NULL, sep));
//	b.nrAngajati = atoi(strtok(NULL, sep));
//
//	return b;
//}
//
//void inserareBancaInLista(Nod** cap, Banca bancaNoua) {
//	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
//	nodNou->info = bancaNoua;
//	nodNou->next = NULL;
//	if ((*cap) == NULL) {
//		*cap = nodNou;
//	}
//	else {
//		Nod* temp = *cap;
//		while (temp->next) {
//			temp = temp->next;
//		}
//		temp->next = nodNou;
//	}
//}
//
//Nod* citireBanciDinFisier(const char* numeFisier) {
//	Nod* lista = NULL;
//	FILE* f = fopen(numeFisier, "r");
//	while (!feof(f)) {
//		inserareBancaInLista((&lista), citireBancaDinFisier(f));
//	}
//	fclose(f);
//	return lista;
//}
//
//int main() {
//	Nod* lista = citireBanciDinFisier("banci.txt");
//	afisareBanci(lista);
//	return 0;
//}