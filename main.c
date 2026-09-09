#include "stdio.h"

#define MAX_SENSORES 10

struct Sensor {
	int canal;
	double ganho;
	double offset;
	double medida;
};

void calibrar_sensor(struct Sensor* sensor);
void mostrar_sensor(const struct Sensor sensor, int numero_sensor);
double calcular_media(const struct Sensor* sensores, int qtd_sensores);
int indice_maior(const struct Sensor* sensores, int qtd_sensores);
void media_canal(const struct Sensor* sensores, double* medias, int qtd_sensores);

int main() {
	struct Sensor sensores[MAX_SENSORES];
	int qtd_sensores;

	do {
		printf("Informe a quantidade de sensores (0 < x < 11): ");
		scanf_s("%d", &qtd_sensores);
	} while (qtd_sensores < 1 || qtd_sensores > 10);
	printf("\n");

	for (int i = 0; i < qtd_sensores; i++) {
		printf("Sensor %d\n", i + 1);

		do {
			printf("\tCanal (0 ou 1): ");
			scanf_s("%d", &sensores[i].canal);
		} while (sensores[i].canal != 0 && sensores[i].canal != 1);
		do {
			printf("\tGanho (entre 10 V e 10.4 V): ");
			scanf_s("%lf", &sensores[i].ganho);
		} while (sensores[i].ganho < 10 || sensores[i].ganho > 10.4);
		do {
			printf("\tOffset (entre -1 e 1): ");
			scanf_s("%lf", &sensores[i].offset);
		} while (sensores[i].offset < -1 || sensores[i].offset > 1);
		printf("\tMedida: ");
		scanf_s("%lf", &sensores[i].medida);
	}
	printf("\n");

	double media_errada = calcular_media(sensores, qtd_sensores);

	printf("Media errada: %.2lf", media_errada);

	for (int i = 0; i < qtd_sensores; i++) {
		calibrar_sensor(&sensores[i]);
	}

	printf("\n");

	double media_corrigida = calcular_media(sensores, qtd_sensores);

	printf("Media corrigida: %.2lf\n\n", media_corrigida);

	int index_maior_media = indice_maior(sensores, qtd_sensores);

	printf("Sensor com maior media apos correcao: \n");
	mostrar_sensor(sensores[index_maior_media], index_maior_media + 1);
	printf("\n");

	printf("Todos os sensores apos calibracao: \n");
	for (int i = 0; i < qtd_sensores; i++) {
		mostrar_sensor(sensores[i], i + 1);
	}
	printf("\n");

	double medias[2] = { 0, 0 };
	media_canal(sensores, qtd_sensores, medias);

	printf("Media canal 0: %.2lf\n", medias[0]);
	printf("Media canal 1: %.2lf\n", medias[1]);

	return 0;
}

/**
* @brief Calibra a medida de um sensor.
* 
* A função utiliza a fórmula: medida corrigida = ganho * medida + offset para calibrar a medida do sensor
* 
* @param Sensor* sensor Sensor que terá a medida calibrada.
*/
void calibrar_sensor(struct Sensor* sensor) {
	sensor->medida = sensor->ganho * sensor->medida + sensor->offset;
}

/**
* @brief Mostra um sensor no console.
* 
* A função recebe um sensor e o número dele e exibe no console em uma formatação padrão.
* 
* @param Sensor sensor Sensor que será mostrado
* @param in numero_sensor Número do sensor que será mostrado na tela
*/
void mostrar_sensor(const struct Sensor sensor, int numero_sensor) {
	printf("Sensor %d\n", numero_sensor);
	printf("\tCanal: %d\n", sensor.canal);
	printf("\tGanho: %.2lf\n", sensor.ganho);
	printf("\tOffset: %.2lf\n", sensor.offset);
	printf("\tMedida: %.2lf\n", sensor.medida);
}

/**
* @brief Calcula a média das medidas dos sensores.
* 
* A função percorre o vetor de sensores e acumula na variável temp o valor da soma de todos as medidas.
* Após, utiliza a quantidade de sensores (qtd_sensores) para calcular a média aritimética da medida dos sensores.
* 
* @param Sensor* sensores Vetor de sensores.
* @param int qtd_sensores Quantidade de sensores no vetor.
* 
* @return double Média aritimética das medidas dos sensores do vetor.
*/
double calcular_media(const struct Sensor* sensores, int qtd_sensores) {
	double temp = 0;
	for (int i = 0; i < qtd_sensores; i++) {
		temp += sensores[i].medida;
	}

	return temp / qtd_sensores;
}

/**
* @brief Retorna o índice do sensor com maior medida.
*
* A função percorre o vetor de sensores e verifica qual possui maior medida. Ao final, retorna o índice deste elemento.
*
* @param Sensores* sensores Vetor de sensores.
* @param int qtd_sensores Quantidade de sensores no vetor.
* 
* @return int Indice do elemento que possui maior medida.
*/
int indice_maior(const struct Sensor* sensores, int qtd_sensores) {
	int temp = 0;
	for (int i = 0; i < qtd_sensores; i++) {
		if (sensores[temp].medida < sensores[i].medida) temp = i;
	}

	return temp;
}

void media_canal(const struct Sensor* sensores, double* medias, int qtd_sensores) {
	int qtd_0 = 0, qtd_1 = 0;
	double soma_0 = 0, soma_1 = 0;
	for (int i = 0; i < qtd_sensores; i++) {
		if (sensores[i].canal == 0) {
			soma_0 += sensores[i].medida;
			qtd_0++;
		} 
		if (sensores[i].canal == 1) {
			soma_1 += sensores[i].medida;
			qtd_1++;
		}
	}

	medias[0] = soma_0 / qtd_0;
	medias[1] = soma_1 / qtd_1;
}
