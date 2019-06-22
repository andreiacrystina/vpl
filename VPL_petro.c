#include <stdio.h>
#include <stdlib.h>
int MAX = 0;

#include "bib_VPL_petro.h"


int main() {
	int escolha;

	registro *ini;
	ini = cria();

	// Leitura do arquivo de controle.
	FILE *file;
	if((file = fopen("controle.bin", "rb")) != NULL){
		fread(&MAX, sizeof(int), 1, file);
	}
	fclose(file);

	// Leitura do arquivo de dados dos reservatórios.
	file = fopen("VPL.bin", "rb");
	if (file){
		int i;
		reservatorio lista_mensal;
		for(i=0; i<MAX; i++){
			fread(&lista_mensal, sizeof(reservatorio), 1, file);
			insere(lista_mensal, ini);
		}
	}
	fclose(file);

	for (;;) {
		escolha = menu();

		switch (escolha) {
		case 1:
			cadastra_dados_mensal(ini);
			break;
		case 2:
			imprime_lista_mensal(ini);
			break;
		case 3:
			imprime_lista_anual(ini);
			break;
		case 4:
			remover_dados(ini);
			break;
		case 5:
			gravar_controle();
			gravar(ini);
			exit(0);
			break;
		}
	}

	return 0;
}
