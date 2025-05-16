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
//struct Campionat citire() {
//	struct Campionat c;
//
//	printf("Introduceti ID-ul campionatului: ");
//	scanf("%d", &c.id);
//	getchar();
//
//	c.tara = malloc(sizeof(char) * 100);
//	c.nume = malloc(sizeof(char) * 100);
//
//	printf("Introduceti tara campionatului: ");
//	fgets(c.tara, sizeof(c.tara), stdin);
//	c.tara[strcspn(c.tara, "\n")] = 0;
//
//	printf("Introduceti numele campionatului: ");
//	fgets(c.nume, sizeof(c.nume), stdin);
//	c.nume[strcspn(c.nume, "\n")] = 0;
//
//	printf("Introduceti numarul de echipe: ");
//	scanf("%d", &c.nrEchipe);
//
//	printf("Introduceti numarul de jucatori: ");
//	scanf("%d", &c.nrJucatori);
//
//	return c;
//}
//
//void afisare(struct Campionat c) {
//	printf("Id: %d\nTara: %s\nNume: %s\nNumarul de echipe: %d\nNumarul de jucator: %d\n\n",
//		c.id, c.tara, c.nume, c.nrEchipe, c.nrJucatori);
//}
//
//void afisareVector(struct Campionat* vectorCampionate, int nrCampionate) {
//	for (int i = 0; i < nrCampionate; i++)
//	{
//		afisare(vectorCampionate[i]);
//	}
//}
//
//void calculeazaMedieJucatoriEchipa(struct Campionat c) {
//	if (c.nrEchipe == 0) {
//		printf("Numarul de echipe nu poate fi 0.\n");
//	}
//	else {
//		float medie = (float)c.nrJucatori / c.nrEchipe;
//		printf("Media jucatorilor pe echipa in campionatul %s este: %.2f\n", c.nume, medie);
//	}
//}
//
//void modificaNumeCampionat(struct Campionat* c, const char* numeNou) {
//	free(c->nume);
//	c->nume = malloc(sizeof(char) * (strlen(numeNou) + 1));
//	strcpy_s(c->nume, strlen(numeNou) + 1, numeNou);
//}
//
////filtrează campionatele care au peste (prag) echipe 
//struct Campionat* filtrareCampionate(struct Campionat* vectorCampionate, int nrCampionate, int* nrCampionateNou, int prag) {
//	struct Campionat* vectorNou = malloc(sizeof(struct Campionat) * nrCampionate);
//	*nrCampionateNou = 0;
//	for (int i = 0; i < nrCampionate; i++)
//	{
//		if (vectorCampionate[i].nrEchipe > prag) {
//			vectorNou[*nrCampionateNou] = initializare(vectorCampionate[i].id, vectorCampionate[i].tara,
//											vectorCampionate[i].nume, vectorCampionate[i].nrEchipe,
//											vectorCampionate[i].nrJucatori);
//			(*nrCampionateNou)++;
//		}
//	}
//	return vectorNou;
//}
//
//void eliberareMemorie(struct Campionat* c) {
//	free(c->tara);
//	free(c->nume);
//}
//
//void dezalocareVector(struct Campionat** vectorCampionate, int* nrCampionate) {
//	for (int i = 0; i < *nrCampionate; i++)
//	{
//		free((*vectorCampionate)[i].tara);
//	}
//	free(*vectorCampionate);
//	*vectorCampionate = NULL;
//	*nrCampionate = 0;
//}
//
//int main() {
//	int nrCampionate = 5;
//	struct Campionat* vectorCampionate = malloc(sizeof(struct Campionat) * nrCampionate);
//	vectorCampionate[0] = initializare(1, "Romania", "Liga 1", 16, 468);
//	vectorCampionate[1] = initializare(2, "Romania", "Liga 2", 22, 573);
//	vectorCampionate[2] = initializare(3, "Germania", "Bundesliga", 18, 508);
//	vectorCampionate[3] = initializare(4, "Anglia", "Premier League", 20, 550);
//	vectorCampionate[4] = initializare(5, "Spania", "La Liga", 20, 530);
//
//	printf("Vector initial:\n\n");
//	afisareVector(vectorCampionate, nrCampionate);
//
//	int nrCampionateNou;
//	struct Campionat* campionateFiltrate = filtrareCampionate(vectorCampionate, nrCampionate, &nrCampionateNou, 18);
//
//	printf("Campionatele cu mai mult de 18 echipe:\n\n");
//	afisareVector(campionateFiltrate, nrCampionateNou);
//
//	dezalocareVector(&vectorCampionate, &nrCampionate);
//	dezalocareVector(&campionateFiltrate, &nrCampionateNou);
//
//	return 0;
//}