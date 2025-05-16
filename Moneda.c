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
//void inserareInLista(Nod** cap, Moneda m) {
//	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
//	nodNou->info = m;
//	nodNou->next = *cap;
//	*cap = nodNou;
//}
//
//void afisareMoneda(Moneda m) {
//	printf("Tara: %s\n", m.tara);
//	printf("Valoare nominala: %d\n", m.valoareNominala);
//	printf("Greutate: %.2f\n", m.greutate);
//	printf("An emitere: %d\n\n", m.anEmitere);
//}
//
//void afisareMonezi(Nod* cap) {
//	while (cap) {
//		afisareMoneda(cap->info);
//		cap = cap->next;
//	}
//}
//
//Moneda aflaMonedaGreutateMaxima(Nod* cap) {
//	Nod* temp = cap;
//	Moneda monedaGreutateMaxima = temp->info;
//	while (temp) {
//		if (temp->info.greutate > monedaGreutateMaxima.greutate) {
//			monedaGreutateMaxima = temp->info;
//		}
//		temp = temp->next;
//	}
//	return monedaGreutateMaxima;
//}
//
//void stergeMonedaDupaGreutate(Nod** cap, float greutateCautata) {
//	while ((*cap) != NULL && (*cap)->info.greutate == greutateCautata) {
//		Nod* temp = *cap;
//		*cap = (*cap)->next;
//		free(temp->info.tara);
//		free(temp);
//	}
//	Nod* p = *cap;
//	while (p != NULL && p->next != NULL) {
//		if (p->next->info.greutate == greutateCautata) {
//			Nod* temp = p->next;
//			p->next = temp->next;
//			free(temp->info.tara);
//			free(temp);
//		}
//		else {
//			p = p->next;
//		}
//	}
//}
//
//void dezalocareMemorie(Nod** cap) {
//	Nod* temp;
//	while (*cap) {
//		temp = *cap;
//		*cap = (*cap)->next;
//		free(temp->info.tara);
//		free(temp);
//	}
//	printf("\n\nMemoria a fost dezalocata\n\n");
//}
//
//int main() {
//	Nod* lista = NULL;
//
//	Moneda m1 = initializareMoneda("Romania", 5, 10.50, 2007);
//	Moneda m2 = initializareMoneda("Franta", 7, 21.30, 2011);
//	Moneda m3 = initializareMoneda("Finlanda", 3, 6.8, 2000);
//	Moneda m4 = initializareMoneda("Norvegia", 31, 31.4, 1975);
//	Moneda m5 = initializareMoneda("Anglia", 9, 14.50, 2002);
//
//	inserareInLista((&lista), m1);
//	inserareInLista((&lista), m2);
//	inserareInLista((&lista), m3);
//	inserareInLista((&lista), m4);
//	inserareInLista((&lista), m5);
//
//	printf("Lista de monezi\n\n");
//	afisareMonezi(lista);
//
//	printf("\n\nMoneda cu greutate maxima\n\n");
//	Moneda monedaGreutateMaxima = aflaMonedaGreutateMaxima(lista);
//	afisareMoneda(monedaGreutateMaxima);
//
//	printf("\n\nSUPREMATIA LEULUI\n\n");
//	stergeMonedaDupaGreutate((&lista), 21.30);
//	stergeMonedaDupaGreutate((&lista), 6.8);
//	stergeMonedaDupaGreutate((&lista), 31.4);
//	stergeMonedaDupaGreutate((&lista), 14.50);
//	afisareMonezi(lista);
//
//	dezalocareMemorie(&lista);
//
//	return 0;
//}