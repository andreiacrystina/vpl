#include <stdio.h>
#include <stdlib.h>
#include "bib_VPL_petro.h"

#define MAX 100

int main() {
	int escolha;

	reservatorio *lista_mensal = NULL;
	reservatorio *lista_anual = NULL;

	for (;;) {
		escolha = menu();

		switch (escolha) {
		case 1:
			lista_mensal = cadastra_dados_mensal(lista_mensal);
			break;
		case 2:
			imprime_lista_mensal(lista_mensal);
			break;
		case 3:
			imprime_lista_anual(lista_anual);
			break;
		case 4:
			exit(0);
			break;
		}
	}

	return 0;
}
