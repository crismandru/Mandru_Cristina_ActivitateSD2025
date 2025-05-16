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
//void afisareMasina(Masina masina) {
//	printf("Id: %d\n", masina.id);
//	printf("Numar usi: %d\n", masina.nrUsi);
//	printf("Pret: %.2f\n", masina.pret);
//	printf("Model: %s\n", masina.model);
//	printf("Nume sofer: %s\n", masina.numeSofer);
//	printf("Serie: %c\n\n", masina.serie);
//}
//
//void afisareVectorMasini(Masina* masini, int nrMasini) {
//	for (int i = 0; i < nrMasini; i++)
//	{
//		afisareMasina(masini[i]);
//	}
//}
//
//void adaugaMasinaInVector(Masina** masini, int* nrMasini, Masina masinaNoua) {
//	Masina* vector = malloc(sizeof(Masina) * ((*nrMasini) + 1));
//	for (int i = 0; i < (*nrMasini); i++)
//	{
//		vector[i] = (*masini)[i];
//	}
//	//facem deepcopy deoarece masinaNoua isi schimba zona de memorie
//	vector[(*nrMasini)] = masinaNoua;
//	vector[(*nrMasini)].model = malloc(sizeof(char) * (strlen(masinaNoua.model) + 1));
//	strcpy_s(vector[(*nrMasini)].model, strlen(masinaNoua.model) + 1, masinaNoua.model);
//	vector[(*nrMasini)].numeSofer = malloc(sizeof(char) * (strlen(masinaNoua.numeSofer) + 1));
//	strcpy_s(vector[(*nrMasini)].numeSofer, strlen(masinaNoua.numeSofer) + 1, masinaNoua.numeSofer);
//	(*nrMasini)++;
//	free(*masini);
//	(*masini) = vector;
//}
//
//Masina citireMasinaFisier(FILE* file) {
//	Masina masina;
//	char buffer[100];
//	char separator[] = ",\n";
//
//	if (fgets(buffer, 100, file) == NULL) {
//		masina.id = -1; 
//		return masina;
//	}
//
//	char* token = strtok(buffer, separator);
//	masina.id = atoi(token);
//
//	token = strtok(NULL, separator);
//	masina.nrUsi = atoi(token);
//
//	token = strtok(NULL, separator);
//	masina.pret = atof(token); 
//
//	token = strtok(NULL, separator);
//	masina.model = malloc(strlen(token) + 1);
//	strcpy(masina.model, token);
//
//	token = strtok(NULL, separator);
//	masina.numeSofer = malloc(strlen(token) + 1);
//	strcpy(masina.numeSofer, token);
//
//	token = strtok(NULL, separator);
//	masina.serie = token[0];
//
//	return masina;
//}
//
//Masina* citireVectorMasiniFisier(const char* numeFisier, int* nrMasiniCitite) {
//	FILE* f = fopen(numeFisier, "r");
//	Masina* masini = NULL;
//	while (!feof(f)) {
//		Masina m = citireMasinaFisier(f);
//		adaugaMasinaInVector(&masini, nrMasiniCitite, m);
//		//ptc am facut deepcopy trb sa facem asta
//		free(m.model);
//		free(m.numeSofer);
//	}
//	fclose(f);
//	return masini;
//}
//
//void dezalocareVectorMasini(Masina** vector, int* nrMasini) {
//	for (int i = 0; i < *nrMasini; i++)
//	{
//		free((*vector)[i].model);
//		free((*vector)[i].numeSofer);
//	}
//	free(*vector);
//	*vector = NULL;
//	*nrMasini = 0;
//}
//
//int main() {
//	Masina* masini = NULL;
//	int nrMasini = 0;
//	masini = citireVectorMasiniFisier("masini.txt", &nrMasini);
//	afisareVectorMasini(masini, nrMasini);
//	dezalocareVectorMasini(&masini, &nrMasini);
//	return 0;
//}