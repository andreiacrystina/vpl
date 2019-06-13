#include <stdio.h>
#include <stdlib.h>
#include "bib_VPL_petro.h"

#define MAX 100

int main() {
	int escolha;

	mensal *lista_mensal = NULL;
	anual *lista_anual = NULL;

	for (;;) {
		escolha = menu();

		switch (escolha) {
		case 1:
			lista_mensal = cadastra_dados_mensal(lista_mensal);
			break;
		case 2:
			lista_anual = cadastra_dados_anual(lista_anual);
			break;
		case 3:
			imprime_lista_mensal(lista_mensal);
			break;
		case 4:
			printf("Imprime...");
			break;
		case 5:
			exit(0);
			break;
		}
	}
	return 0;
}
