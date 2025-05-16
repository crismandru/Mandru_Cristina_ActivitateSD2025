//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
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
//	Nod* prev;
//};
//
//typedef struct ListaDubla ListaDubla;
//struct ListaDubla {
//	Nod* head;
//	Nod* tail;
//	int nrNoduri;
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
//void afisareMasiniDeLaFinal(ListaDubla listaDubla) {
//	Nod* temp = listaDubla.tail;
//	while (temp) {
//		afisareMasina(temp->info);
//		temp = temp->prev;
//	}
//}
//
//void afisareMasiniDeLaInceput(ListaDubla listaDubla) {
//	Nod* temp = listaDubla.head;
//	while (temp) {
//		afisareMasina(temp->info);
//		temp = temp->next;
//	}
//}
//
//void adaugaMasinaInListaLaFinal(ListaDubla* listaDubla, Masina masinaNoua) {
//	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
//	nodNou->info = masinaNoua;
//	nodNou->next = NULL;
//	nodNou->prev = listaDubla->tail;
//	
//	if (listaDubla->head == NULL) {
//		listaDubla->head = nodNou;
//	}
//	else {
//		listaDubla->tail->next = nodNou;
//	}
//	listaDubla->tail = nodNou;
//	listaDubla->nrNoduri++;
//}
//
//void adaugaMasinaInListaLaInceput(ListaDubla* listaDubla, Masina masinaNoua) {
//	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
//	nodNou->info = masinaNoua;
//	nodNou->next = listaDubla->head;
//	nodNou->prev = NULL;
//
//	if (listaDubla->head == NULL) {
//		listaDubla->head = nodNou;
//	}
//	else {
//		listaDubla->head->prev = nodNou;
//	}
//	listaDubla->head = nodNou;
//	listaDubla->nrNoduri++;
//}
//
//ListaDubla citireMasiniDinFisier(const char* numeFisier) {
//	ListaDubla lista;
//	lista.head = NULL;
//	lista.tail = NULL;
//	lista.nrNoduri = 0;
//
//	FILE* f = fopen(numeFisier, "r");
//	while (!feof(f)) {
//		adaugaMasinaInListaLaFinal((&lista), citireMasinaDinFisier(f));
//	}
//
//	fclose(f);
//	return lista;
//}
//
//float calculeazaPretMediu(ListaDubla listaDubla) {
//	float suma = 0;
//	while (listaDubla.head) {
//		suma += listaDubla.head->info.pret;
//		listaDubla.head = listaDubla.head->next;
//	}
//	return suma / listaDubla.nrNoduri;
//}
//
//char* getSoferCeaMaiScumpaMasina(ListaDubla lista) {
//	Nod* temp = lista.head;
//	Nod* max = lista.head;
//
//	while (temp) {
//		if (temp->info.pret > max->info.pret) {
//			max = temp;
//		}
//		temp = temp->next;
//	}
//
//	char* numeSoferBogat = (char*)malloc(sizeof(strlen(max->info.numeSofer) + 1));
//	strcpy_s(numeSoferBogat, strlen(max->info.numeSofer) + 1, max->info.numeSofer);
//	return numeSoferBogat;
//}
//
//void stergeMasinaDupaID(ListaDubla* lista, int idCautat) {
//	Nod* temp = lista->head;
//	while (temp) {
//		if (temp->info.id == idCautat) {
//			if (temp == lista->head) {
//				lista->head = temp->next;
//				if (lista->head) {
//					lista->head->prev = NULL;
//				}
//			}
//			else if (temp == lista->tail) {
//				lista->tail = temp->prev;
//				if (lista->tail) {
//					lista->tail->next = NULL;
//				}
//			}
//			else {
//				temp->prev->next = temp->next;
//				temp->next->prev = temp->prev;
//			}
//			free(temp->info.model);
//			free(temp->info.numeSofer);
//			free(temp);
//			lista->nrNoduri--;
//			return;
//		}
//		temp = temp->next;
//	}
//}
//
//void dezalocareMemorie(ListaDubla* listaDubla) {
//	while (listaDubla->head) {
//		Nod* temp = listaDubla->head;
//		while (temp) {
//			Nod* p = temp->next;
//			free(temp->info.model);
//			free(temp->info.numeSofer);
//			free(temp);
//			temp = p;
//		}
//		listaDubla->head = NULL;
//		listaDubla->tail = NULL;
//		listaDubla->nrNoduri = 0;
//	}
//}
//
//int main() {
//	ListaDubla lista = citireMasiniDinFisier("masini.txt");
//	afisareMasiniDeLaInceput(lista);
//
//	float pretMediu = calculeazaPretMediu(lista);
//	printf("\nPretul mediu pe masina este %.2f.\n", pretMediu);
//
//	char* numeSoferBogat = getSoferCeaMaiScumpaMasina(lista);
//	printf("\nSoferul cu cea mai scumpa masina este %s.\n", numeSoferBogat);
//
//	printf("\n\nLista de masini fara a 5a\n\n");
//	stergeMasinaDupaID(&lista, 5);
//	afisareMasiniDeLaInceput(lista);
//
//	dezalocareMemorie(&lista);
//
//	return 0;
//}