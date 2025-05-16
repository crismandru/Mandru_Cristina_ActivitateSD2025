//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//struct StructuraMasina {
//	int id;
//	int nrUsi;
//	float pret;
//	char* model;
//	char* numeSofer;
//	unsigned char serie;
//};
//typedef struct StructuraMasina Masina;
//
//struct Nod {
//	Masina info;
//	struct Nod* next;
//};
//typedef struct Nod Nod;
//
//Masina citireMasinaDinFisier(FILE* file) {
//	char buffer[100];
//	char sep[3] = ",\n";
//	fgets(buffer, 100, file);
//	char* aux;
//	Masina m1;
//	aux = strtok(buffer, sep);
//	m1.id = atoi(aux);
//	m1.nrUsi = atoi(strtok(NULL, sep));
//	m1.pret = atof(strtok(NULL, sep));
//	aux = strtok(NULL, sep);
//	m1.model = malloc(strlen(aux) + 1);
//	strcpy_s(m1.model, strlen(aux) + 1, aux);
//
//	aux = strtok(NULL, sep);
//	m1.numeSofer = malloc(strlen(aux) + 1);
//	strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);
//
//	m1.serie = *strtok(NULL, sep);
//	return m1;
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
//void afisareListaMasini(Nod* lista) {
//	while (lista) {
//		afisareMasina(lista->info);
//		lista = lista->next;
//	}
//}
//
//void adaugaMasinaInLista(Nod** lista, Masina masinaNoua) {
//	Nod* nou = (Nod*)malloc(sizeof(Nod));
//	nou->info = masinaNoua;
//	nou->next = NULL;
//	if ((*lista) == NULL) {
//		(*lista) = nou;
//	}
//	else {
//		Nod* temp = (*lista);
//		while (temp->next) {
//			temp = temp->next;
//		}
//		temp->next = nou;
//	}
//}
//
//void adaugaLaInceputInLista(Nod** cap, Masina masinaNoua) {
//	Nod* nou = (Nod*)malloc(sizeof(Nod));
//	nou->info = masinaNoua;
//	nou->next = *cap;
//	*cap = nou;
//}
//
//Nod* citireListaMasiniDinFisier(const char* numeFisier) {
//	FILE* f = fopen(numeFisier, "r");
//	Nod* lista = NULL;
//	while (!feof(f))
//	{
//		adaugaLaInceputInLista(&lista, citireMasinaDinFisier(f));
//	}
//	fclose(f);
//	return lista;
//}
//
//void dezalocareListaMasini(Nod** lista) {
//	while (*lista) {
//		Nod* p = (*lista);
//		(*lista) = (*lista)->next;
//		free(p->info.model);
//		free(p->info.numeSofer);
//		free(p);
//	}
//}
//
//float calculeazaPretMediu(Nod* lista) {
//	float s = 0;
//	int k = 0;
//	while (lista) {
//		s += lista->info.pret;
//		k++;
//		lista = lista->next;
//	}
//	return (k > 0) ? s / k : 0;
//}
//
//void stergeMasiniDinSeria(Nod** lista, char serieCautata) {
//	while ((*lista) != NULL && (*lista)->info.serie == serieCautata) {
//		Nod* temp = (*lista);
//		(*lista) = (*lista)->next;
//		free(temp->info.numeSofer);
//		free(temp->info.model);
//		free(temp);
//	}
//	Nod* p = (*lista);
//	while (p != NULL) {
//		while (p->next && p->next->info.serie != serieCautata) {
//			p = p->next;
//		}
//		if (p->next) {
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
//float calculeazaPretulMasinilorUnuiSofer(Nod* lista, const char* numeSofer) {
//	float suma = 0;
//	while (lista) {
//		if (strcmp(lista->info.numeSofer, numeSofer) == 0) {
//			suma += lista->info.pret;
//		}
//		lista = lista->next;
//	}
//	return suma;
//}
//
//void stergeNodLaPozitie(Nod** lista, int index) {
//	if (*lista == NULL || index < 0) {
//		return -1;
//	}
//
//	Nod* temp = *lista;
//
//	//șterge primul nod
//	if (index == 0) {
//		*lista = temp->next;
//		free(temp->info.model);
//		free(temp->info.numeSofer);
//		free(temp);
//		return;
//	}
//
//	//găsește nodul anterior celui șters
//	Nod* prev = NULL;
//	for (int i = 0; temp != NULL && i < index; i++) {
//		prev = temp;
//		temp = temp->next;
//	}
//
//	//dacă indexul este mai mare decât numărul de noduri
//	if (temp == NULL) {
//		return -1;
//	}
//
//	//scoatem nodul din listă
//	prev->next = temp->next;
//
//	//eliberăm memoria
//	free(temp->info.model);
//	free(temp->info.numeSofer);
//	free(temp);
//}
//
//void insereazaMasinaSortat(Nod** lista, Masina masinaNoua) {
//	Nod* nou = (Nod*)malloc(sizeof(Nod));
//	nou->info = masinaNoua;
//	nou->next = NULL;
//
//	//dacă lista este goală sau noul element trebuie inserat la început
//	if (*lista == NULL || (*lista)->info.pret > masinaNoua.pret) {
//		nou->next = *lista;
//		*lista = nou;
//		return;
//	}
//
//	//găsim poziția corectă pentru inserare
//	Nod* temp = *lista;
//	while (temp->next != NULL && temp->next->info.pret < masinaNoua.pret) {
//		temp = temp->next;
//	}
//
//	//inserare după nodul găsit
//	nou->next = temp->next;
//	temp->next = nou;
//}
//
//int main() {
//	Nod* masini = citireListaMasiniDinFisier("masini.txt");
//	afisareListaMasini(masini);
//
//	printf("--------------------PRET MEDIU-------------------\n");
//	printf("%.2f", calculeazaPretMediu(masini));
//
//	printf("\n\n----------------SUMA MASINI SOFER----------------\n");
//	printf("%.2f", calculeazaPretulMasinilorUnuiSofer(masini, "Elena Ionescu"));
//
//	printf("\n-----------------------------------------------\n");
//	stergeMasiniDinSeria(&masini, 'A');
//	afisareListaMasini(masini);
//
//	printf("\n-----------------------------------------------\n");
//	stergeMasiniDinSeria(&masini, 'B');
//	afisareListaMasini(masini);
//
//	printf("\n\n-------LISTA FARA A TREIA MASINA DIN LISTA-------\n");
//	stergeNodLaPozitie(&masini, 2);
//	afisareListaMasini(masini);
//
//
//	printf("\n\n-------MASINI INSERATE CRESCATOR DUPA PRET-------\n");
//	Masina m1 = { 1, 4, 15000.0, "Dacia", "Ion Popescu", 'A' };
//	Masina m2 = { 2, 2, 12000.0, "Fiat", "Maria Ionescu", 'B' };
//	Masina m3 = { 3, 6, 18000.0, "BMW", "George Vasile", 'C' };
//
//	Nod* lista = NULL;
//
//	insereazaMasinaSortat(&lista, m1);
//	insereazaMasinaSortat(&lista, m2);
//	insereazaMasinaSortat(&lista, m3);
//
//	afisareListaMasini(lista);
//
//	dezalocareListaMasini(&masini);
//
//	return 0;
//}