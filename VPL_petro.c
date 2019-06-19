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
	}else{
		printf("Sem informacao de controle (MAX)!\n ");
		system ( "read -n 1 -s -p \"Pressione qualquer tecla para continuar...\"" );
		exit(1);
	}
	fclose(file);

	// Leitura do arquivo de dados dos reservatórios.
	file = fopen("VPL.bin", "rb");
	if (!file){
		printf("Dados inexistentes!\n");
		system ( "read -n 1 -s -p \"Pressione qualquer tecla para continuar...\"" );
		exit(1);
	}else{
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
			// imprime_lista_anual(lista_anual);
			break;
		case 4:
			gravar(ini);
			gravar_controle();
			exit(0);
			break;
		}
	}

	return 0;
}
