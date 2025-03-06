#include<stdio.h>
#include<malloc.h>

struct Masina {
	int id;
	char* model;
	float tonaj;
	char serie;
};

struct Masina initializare(int idNout, const char* modelNou, float tonajNou, char serieNou) {
	struct Masina m;
	m.id = 1;
	m.id = idNout;
	m.model = malloc(sizeof(char) * (strlen(modelNou) + 1));
	strcpy_s(m.model, strlen(modelNou) + 1 , modelNou);
	m.tonaj = tonajNou;
	m.serie = serieNou;
	return m;
}

void afisare(struct Masina m) {
	printf("Id: %d\nModel: %s\nTonaj: %.2f\nSerie: %c\n\n", m.id, m.model, m.tonaj, m.serie);
}

void afisareVector(struct Masina* vectorMasini, int nrMasini) {
	for (int i = 0; i < nrMasini; i++)
	{
		afisare(vectorMasini[i]);
	}
}

struct Masina* copiazaPrimeleNMasini(struct Masina* vectorMasini, int nrMasini, int nrMasiniCopiate) {
	//copiem intr-un vector nou pe care il vom returna primele nrElementeCopiate
	struct Masina *vectorNou = malloc(sizeof(struct Masina) * nrMasiniCopiate);
	for (int i = 0; i < nrMasiniCopiate; i++)
	{
		vectorNou[i] = vectorMasini[i];
		//facem deep copy
		vectorNou[i].model = malloc(sizeof(char) * (strlen(vectorMasini[i].model) + 1));
		strcpy_s(vectorNou[i].model, strlen(vectorMasini[i].model) + 1, vectorMasini[i].model);
	}
	return vectorNou;
}

void dezalocare(struct Masina** vectorMasini, int* nrMasini) {
	for (int i = 0; i < *nrMasini; i++)
	{
		free((*vectorMasini)[i].model);
	}
	free(*vectorMasini);
	*vectorMasini = NULL;
	*nrMasini = 0;
}

void copiazaMasiniTonajMic(struct Masina* vectorMasini, int nrMasini, float prag, struct Masina** vectorNou, int* dimensiune) {
	//parametrul prag poate fi modificat in functie de 
	//tipul atributului ales pentru a indeplini o conditie
	//este creat un nou vector cu elementele care indeplinesc acea conditie
	(*dimensiune) = 0;
	for (int i = 0;  i < nrMasini; i++)
	{
		if (vectorMasini[i].tonaj < prag) {
			(*dimensiune)++;
		}
	}
	(*vectorNou) = (struct Masina*)malloc(sizeof(struct Masina) * (*dimensiune));
	int k = 0;
	for (int i = 0; i < nrMasini; i++)
	{
		if (vectorMasini[i].tonaj < prag) {
			(*vectorNou)[k] = vectorMasini[i];
			//deep copy
			(*vectorNou)[k].model = malloc(sizeof(char) * (strlen(vectorMasini[i].model) + 1));
			strcpy_s((*vectorNou)[k].model, strlen(vectorMasini[i].model) + 1, vectorMasini[i].model);
			k++;
		}
	}
}

struct Masina getPrimulElementConditionat(struct Masina* vector, int nrElemente, const char* conditie) {
	//trebuie cautat elementul care indeplineste o conditie
	//dupa atributul de tip char*. Acesta este returnat.
	struct Masina s;
	s.id = 1;

	return s;
}
	
int main() {
	struct Masina m;
	m = initializare(1, "Opel", 5.3, 'S');
	printf("Prima masina: \n");
	afisare(m);

	struct Masina* vectorMasini;
	int nrMasini = 3;
	vectorMasini = malloc(sizeof(struct Masina) * nrMasini);
	vectorMasini[0] = initializare(2, "Renault", 3.5, 'X');
	vectorMasini[1] = initializare(3, "BMW", 8.5, 'Y');
	vectorMasini[2] = initializare(4, "Audi", 6.3, 'C');
	printf("\nMai multe masini: \n");
	afisareVector(vectorMasini, nrMasini);

	struct Masina* vectorMasiniCopiate;
	int nrMasiniCopiate = 2;
	vectorMasiniCopiate = copiazaPrimeleNMasini(vectorMasini, nrMasini, nrMasiniCopiate);
	printf("\nMasini copiate: \n");
	afisareVector(vectorMasiniCopiate, nrMasiniCopiate);

	struct Masina* vectorMasiniTonajMic = NULL;
	int nrMasiniTonajMic = 0;
	copiazaMasiniTonajMic(vectorMasiniCopiate, nrMasiniCopiate, 5, &vectorMasiniTonajMic, &nrMasiniTonajMic);
	printf("\nMasini cu tonaj mic: \n");
	afisareVector(vectorMasiniTonajMic, nrMasiniTonajMic);

	dezalocare(&vectorMasiniCopiate, &nrMasiniCopiate);
	dezalocare(&vectorMasiniTonajMic, &nrMasiniTonajMic);

	return 0;
}