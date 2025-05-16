//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//struct Campionat {
//	int id;
//	char* tara;
//	char* nume;
//	int nrEchipe;
//	int nrJucatori;
//};
//typedef struct Campionat Campionat;
//
//struct Campionat initializare(int idNou, const char* taraNoua, const char* numeNou, int nrEchipeNou, int nrJucatoriNou) {
//	struct Campionat c;
//	c.id = idNou;
//	c.tara = malloc(sizeof(char) * (strlen(taraNoua) + 1));
//	strcpy_s(c.tara, strlen(taraNoua) + 1, taraNoua);
//	c.nume = malloc(sizeof(char) * (strlen(numeNou) + 1));
//	strcpy_s(c.nume, strlen(numeNou) + 1, numeNou);
//	c.nrEchipe = nrEchipeNou;
//	c.nrJucatori = nrJucatoriNou;
//	return c;
//}
//
//void afisareCampionat(Campionat c) {
//	printf("Id: %d\nTara: %s\nNume: %s\nNumarul de echipe: %d\nNumarul de jucator: %d\n\n",
//		c.id, c.tara, c.nume, c.nrEchipe, c.nrJucatori);
//}
//
//void afisareCampionate(Campionat* vectorCampionate, int nrCampionate) {
//	for (int i = 0; i < nrCampionate; i++)
//	{
//		afisareCampionat(vectorCampionate[i]);
//	}
//}
//
//void adaugaCampionatInVector(Campionat** vectorCampionate, int* nrCampionate, Campionat campionatNou) {
//	Campionat* vectorCampionateNou = malloc(sizeof(Campionat) * ((*nrCampionate) + 1));
//	for (int i = 0; i < (*nrCampionate); i++)
//	{
//		vectorCampionateNou[i] = (*vectorCampionate)[i];
//	}
//	vectorCampionateNou[(*nrCampionate)] = campionatNou;
//	vectorCampionateNou[(*nrCampionate)].tara = malloc(sizeof(char) * (strlen(campionatNou.tara) + 1));
//	strcpy_s(vectorCampionateNou[(*nrCampionate)].tara, strlen(campionatNou.tara) + 1, campionatNou.tara);
//	vectorCampionateNou[(*nrCampionate)].nume = malloc(sizeof(char) * (strlen(campionatNou.nume) + 1));
//	strcpy_s(vectorCampionateNou[(*nrCampionate)].nume, strlen(campionatNou.nume) + 1, campionatNou.nume);
//	(*nrCampionate)++;
//	free(*vectorCampionate);
//	(*vectorCampionate) = vectorCampionateNou;
//}
//
//Campionat citireCampionatFisier(FILE* file) {
//	Campionat c;
//	char buffer[100];
//	char separator[] = ",\n";
//
//	if (fgets(buffer, 100, file) == NULL) {
//		c.id = -1;
//		return c;
//	}
//
//	char* token = strtok(buffer, separator);
//	c.id = atoi(token);
//
//	token = strtok(NULL, separator);
//	c.tara = malloc(strlen(token) + 1);
//	strcpy(c.tara, token);
//
//	token = strtok(NULL, separator);
//	c.nume = malloc(strlen(token) + 1);
//	strcpy(c.nume, token);
//
//	token = strtok(NULL, separator);
//	c.nrEchipe = atoi(token);
//
//	token = strtok(NULL, separator);
//	c.nrJucatori = atoi(token);
//
//	return c;
//}
//
//Campionat* citireVectorCampionateFisier(const char* numeFisier, int* nrCampionate) {
//	FILE* f = fopen(numeFisier, "r");
//	Campionat* vectorCampionate = NULL;
//	while (!feof(f)) {
//		Campionat c = citireCampionatFisier(f);
//		adaugaCampionatInVector(&vectorCampionate, nrCampionate, c);
//		free(c.tara);
//		free(c.nume);
//	}
//	fclose(f);
//	return vectorCampionate;
//}
//
//void salveazaCampionatInFisier(FILE* file, Campionat c) {
//	fprintf(file, "%d,%s,%s,%d,%d\n", c.id, c.tara, c.nume, c.nrEchipe, c.nrJucatori);
//}
//
//void salveazaCampionateInFisier(const char* numeFisier, Campionat* vectorCampionate, int nrCampionate) {
//	FILE* f = fopen(numeFisier, "w");
//	if (f == NULL) {
//		printf("Nu s-a putut deschide fisierul pentru salvare.\n");
//		return;
//	}
//	for (int i = 0; i < nrCampionate; i++) {
//		salveazaCampionatInFisier(f, vectorCampionate[i]);
//	}
//	fclose(f); 
//}
//
//void dezalocareVectorCampionate(Campionat** vectorCampionate, int* nrCampionate) {
//	for (int i = 0; i < *nrCampionate; i++)
//	{
//		free((*vectorCampionate)[i].tara);
//		free((*vectorCampionate)[i].nume);
//	}
//	free(*vectorCampionate);
//	(*vectorCampionate) = NULL;
//	(*nrCampionate) = 0;
//}
//
//int main() {
//	Campionat* vectorCampionate = NULL;
//	int nrCampionate = 0;
//
//	vectorCampionate = citireVectorCampionateFisier("campionate.txt", &nrCampionate);
//	afisareCampionate(vectorCampionate, nrCampionate);
//
//	struct Campionat c;
//	c = initializare(11, "Belgia", "Jupiler Pro League", 16, 450);
//
//	FILE* f = fopen("campionat_adaugat.txt", "w");
//	salveazaCampionatInFisier(f, c);
//	fclose(f);
//
//	int nrCampionateDeAdaugat = 3;
//	struct Campionat* vectorCampionateAdaugate = malloc(sizeof(struct Campionat) * nrCampionateDeAdaugat);
//	vectorCampionateAdaugate[0] = initializare(1, "Romania", "Liga 1", 16, 468);
//	vectorCampionateAdaugate[1] = initializare(2, "Romania", "Liga 2", 22, 573);
//	vectorCampionateAdaugate[2] = initializare(3, "Germania", "Bundesliga", 18, 508);
//	salveazaCampionateInFisier("campionate_adaugate.txt", vectorCampionateAdaugate, nrCampionateDeAdaugat);
//
//	dezalocareVectorCampionate(&vectorCampionate, &nrCampionate);
//
//	return 0;
//}