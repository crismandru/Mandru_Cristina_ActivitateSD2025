//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//typedef struct Moneda Moneda;
//struct Moneda {
//	char* tara;
//	int valoareNominala;
//	float greutate;
//	int anEmitere;
//};
//
//typedef struct Nod Nod;
//struct Nod {
//	Moneda info;
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
//Moneda initializareMoneda(const char* tara, int valoareNominala, float greutate, int anEmitere) {
//	Moneda m;
//	m.tara = malloc(sizeof(char) * (strlen(tara) + 1));
//	strcpy_s(m.tara, strlen(tara) + 1, tara);
//	m.valoareNominala = valoareNominala;
//	m.greutate = greutate;
//	m.anEmitere = anEmitere;
//	return m;
//}
//
//void afisareMoneda(Moneda m) {
//	printf("Tara: %s\n", m.tara);
//	printf("Valoare nominala: %d\n", m.valoareNominala);
//	printf("Greutate: %.2f\n", m.greutate);
//	printf("An emitere: %d\n\n", m.anEmitere);
//}
//
//void afisareMonezi(ListaDubla listaDubla) {
//	Nod* temp = listaDubla.head;
//	while (temp) {
//		afisareMoneda(temp->info);
//		temp = temp->next;
//	}
//}
//
//void adaugaMonedaInListaLaFinal(ListaDubla* listaDubla, Moneda monedaNoua) {
//	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
//	nodNou->info = monedaNoua;
//	nodNou->prev = listaDubla->tail;
//	nodNou->next = NULL;
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
//int main() {
//	ListaDubla lista;
//	lista.head = NULL;
//	lista.tail = NULL;
//	lista.nrNoduri = 0;
//	
//	Moneda m1 = initializareMoneda("Romania", 5, 10.50, 2007);
//	Moneda m2 = initializareMoneda("Franta", 7, 21.30, 2011);
//	Moneda m3 = initializareMoneda("Finlanda", 3, 6.8, 2000);
//	Moneda m4 = initializareMoneda("Norvegia", 31, 31.4, 1975);
//	Moneda m5 = initializareMoneda("Anglia", 9, 14.50, 2002);
//
//	adaugaMonedaInListaLaFinal((&lista), m1);
//	adaugaMonedaInListaLaFinal((&lista), m2);
//	adaugaMonedaInListaLaFinal((&lista), m3);
//	adaugaMonedaInListaLaFinal((&lista), m4);
//	adaugaMonedaInListaLaFinal((&lista), m5);
//
//	afisareMonezi(lista);
//
//	return 0;
//}