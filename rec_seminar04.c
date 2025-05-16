//#define _CRT_SECURE_NO_WARNINGS
//#include <stdlib.h>
//#include <stdio.h>
//#include <string.h>
//#include <malloc.h>
//
//typedef struct StructuraMasina Masina;
//struct StructuraMasina {
//	int id;
//	int nrUsi;
//	float pret;
//	char* model;
//	char* numeSofer;
//	unsigned char serie;
//};
//
//typedef struct Nod Nod;
//struct Nod {
//	Masina info;
//	Nod* next;
//};
//
//Masina citireMasinaDinFisier(FILE* file) {
//	Masina m;
//	char buffer[100];
//	char sep[3] = ",\n";
//	char* aux;
//	fgets(buffer, 100, file);
//
//	aux = strtok(buffer, sep);
//	m.id = atoi(aux);
//	m.nrUsi = atoi(strtok(NULL, sep));
//	m.pret = atof(strtok(NULL, sep));
//
//	aux = strtok(NULL, sep);
//	m.model = malloc(strlen(aux) + 1);
//	strcpy_s(m.model, strlen(aux) + 1, aux);
//
//	aux = strtok(NULL, sep);
//	m.numeSofer = malloc(strlen(aux) + 1);
//	strcpy_s(m.numeSofer, strlen(aux) + 1, aux);
//
//	m.serie = *strtok(NULL, sep);
//
//	return m;
//}
//
//void afisareMasina(Masina masina) {
//	printf("Id: %d\n", masina.id);
//	printf("Nr. usi : %d\n", masina.nrUsi);
//	printf("Pret: %.2f\n", masina.pret);
//	printf("Model: %s\n", masina.model);
//	printf("Nume sofer: %s\n", masina.numeSofer);
//	printf("Serie: %c\n\n", masina.serie);
//}
//
//void afisareListaMasini(Nod* cap) {
//	while (cap) {
//		afisareMasina(cap->info);
//		cap = cap->next;
//	}
//}
//
//void adaugaMasinaInListaLaFinal(Nod** cap, Masina masinaNoua) {
//	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
//	nodNou->info = masinaNoua;
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
//void adaugaMasinaInListaLaInceput(Nod** cap, Masina masinaNoua) {
//	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
//	nodNou->info = masinaNoua;
//	nodNou->next = *cap;
//	(*cap) = nodNou;
//}
//
//Nod* citireMasiniDinFisier(const char* numeFisier) {
//	Nod* lista = NULL;
//	FILE* f = fopen(numeFisier, "r");
//	while (!feof(f)) {
//		adaugaMasinaInListaLaFinal((&lista), citireMasinaDinFisier(f));
//	}
//	fclose(f);
//	return lista;
//}
//
//float calculeazaPretMediu(Nod* cap) {
//	float suma = 0;
//	int nrMasini = 0;
//	while (cap) {
//		suma += cap->info.pret;
//		nrMasini++;
//		cap = cap->next;
//	}
//	return suma / nrMasini;
//}
//
//
//float calculeazaPretulMasinilorUnuiSofer(Nod* cap, const char* numeSoferCautat) {
//	float suma = 0;
//	while (cap) {
//		if (strcmp(cap->info.numeSofer, numeSoferCautat) == 0) {
//			suma += cap->info.pret;
//		}
//		cap = cap->next;
//	}
//	return suma;
//}
//
//void stergeMasiniDinSeria(Nod** cap, char serieCautata) {
//	while ((*cap) && (*cap)->info.serie == serieCautata) {
//		Nod* temp = *cap;
//		*cap = (*cap)->next;
//		free(temp->info.model);
//		free(temp->info.numeSofer);
//		free(temp);
//	}
//	Nod* p = *cap;
//	while (p && p->next) {
//		if (p->next->info.serie == serieCautata) {
//			Nod* temp = p->next;
//			p->next = temp->next;
//			free(temp->info.model);
//			free(temp->info.numeSofer);
//			free(temp);
//		}
//		else {
//			p = p->next;
//		}
//	}
//}
//
//void dezalocareMemorie(Nod** cap) {
//	while (*cap) {
//		Nod* temp = *cap;
//		*cap = (*cap)->next;
//		free(temp->info.model);
//		free(temp->info.numeSofer);
//		free(temp);
//	}
//}
//
//int main() {
//	Nod* lista = citireMasiniDinFisier("masini.txt");
//	afisareListaMasini(lista);
//
//	float pretMediu = calculeazaPretMediu(lista);
//	printf("\nPretul mediu al unei masini este %.2f lei.\n", pretMediu);
//
//	float pretulMasinilorLuiGheorghe = calculeazaPretulMasinilorUnuiSofer(lista, "Gheorghe");
//	printf("\nPretul masinilor lui Gheorghe: %.2f\n", pretulMasinilorLuiGheorghe);
//
//	printf("\n\nLista de masini fara Seria A\n\n");
//	stergeMasiniDinSeria((&lista), 'A');
//	afisareListaMasini(lista);
//
//	dezalocareMemorie(&lista);
//
//	return 0;
//}