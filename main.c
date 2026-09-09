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

	return 0;
}

void calibrar_sensor(struct Sensor* sensor) {
	sensor->medida = sensor->ganho * sensor->medida + sensor->offset;
}

void mostrar_sensor(const struct Sensor sensor, int numero_sensor) {
	printf("Sensor %d\n", numero_sensor);
	printf("\tCanal: %d\n", sensor.canal);
	printf("\tGanho: %.2lf\n", sensor.ganho);
	printf("\tOffset: %.2lf\n", sensor.offset);
	printf("\tMedida: %.2lf\n", sensor.medida);
}

double calcular_media(const struct Sensor* sensores, int qtd_sensores) {
	double temp = 0;
	for (int i = 0; i < qtd_sensores; i++) {
		temp += sensores[i].medida;
	}

	return temp / qtd_sensores;
}

int indice_maior(const struct Sensor* sensores, int qtd_sensores) {
	int temp = 0;
	for (int i = 0; i < qtd_sensores; i++) {
		if (sensores[temp].medida < sensores[i].medida) temp = i;
	}

	return temp;
}
