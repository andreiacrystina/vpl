//Andréia Jardim, Caroline Garcia, Felipe Machado, Marcelo Lopes, Yan Alegre

typedef struct {
	char nome_empresa[100];
	char nome_campo[100];
	int mes;
	int ano;
	float poco_produtor;
	float poco_injetor;
	float poco_explorador;
  float poco_abandonado;
  float venda_oleo;
  float venda_gas;
  float tempo_producao;
  float producao_oleo;
  float producao_gas;
	float VPL;
} reservatorio;

typedef struct reg {
	reservatorio conteudo;
	struct reg *prox;
} registro;

registro *busca(int mes, int ano, registro * ini);

int menu(void)
{
	// No windows usar system("cls");
	system("clear");
	int c = 0;
	do {
		printf("Este eh um programa que calcula o VPL de projetos petroliferos!\n\n -- MENU:\n\n");
		printf("\t 1. Cadastrar os Dados da Analise Mensal\n");
		printf("\t 2. Listar Analises Mensais\n");
		printf("\t 3. Listar Analises Anuais\n");
		printf("\t 4. Remover Dado da Lista Mensal\n");
		printf("\t 5. Salvar e Sair\n\n");
		printf("-- Digite sua escolha: ");
		scanf("%d", &c);
	} while (c <= 0 || c > 5);
	getchar();
	return c;
}

registro *cria(void)
{
	registro *start;

	start = (registro *) malloc(sizeof(registro));
	start->prox = NULL;
	return start;
}

void insere(reservatorio x, registro *p)
{
	registro *nova;

	nova = (registro *) malloc(sizeof(registro));
	nova->conteudo = x;
	nova->prox = p->prox;
	p->prox = nova;
}

void remova(reservatorio lista_mensal, registro * ini)
{
	registro *p, *q;
	p = ini;
	q = ini->prox;
	while ((q != NULL) && (q->conteudo.mes != lista_mensal.mes) && (q->conteudo.ano != lista_mensal.ano)) {
		p = q;
		q = q->prox;
	}
	if (q != NULL) {
		p->prox = q->prox;
		free(q);
	}
}

registro *busca(int mes, int ano, registro * ini)
{
	registro *p;
	p = ini->prox;
	while ((p != NULL) && (p->conteudo.mes != mes) && (p->conteudo.ano != ano)) {
		p = p->prox;
	}

	// Apenas retorna o registro p se o mesmo não for nulo e o mes e ano forem iguais ao informado.
	if ((p != NULL) && (p->conteudo.mes == mes) && (p->conteudo.ano == ano))
	{
		return p;
	} else {
		return NULL;
	}
}

void gravar(registro * ini){
	system("clear");

	FILE *file;
	file = fopen("VPL.bin", "wb");
	if (!file){
		printf("Nao conseguiu criar o arquivo");
		system ( "read -n 1 -s -p \"Pressione qualquer tecla para continuar...\"" );
		return;
	}

	registro *p;
	for (p = ini->prox; p != NULL; p = p->prox){
		fwrite(&p->conteudo, sizeof(reservatorio), 1, file);
	}

	printf("Os dados foram salvos!!\n");
	fclose(file);
	printf("\n");
}

void gravar_controle(void) {
	FILE *file;
	file = fopen("controle.bin", "wb");
	if (!file){
		printf("Nao conseguiu criar arquivo de controle");
		system ( "read -n 1 -s -p \"Pressione qualquer tecla para continuar...\"" );
		return;
	}
	fwrite(&MAX, sizeof(int), 1, file);
	fclose(file);
}

void ler_string(char palavra[100], int tamanho) {
	int i = 0;
	char c;

	c = getchar();
	while ((c != '\n') && (i < tamanho)) {
		palavra[i++] = c;
		c = getchar();
	}
	palavra[i] = '\0';
	palavra[i] = '\0';

	if (c != '\n') {
		c = getchar();
		while ((c != '\n') && (c != EOF)) {
			c = getchar();
		}
	}
}

float receita_bruta(reservatorio pr) {
  float preco_oleo, preco_gas, custo_producao_oleo, custo_producao_gas, resultado;
  //fator de conversão do oleo e gas
  float fbo = 1.95;

  preco_oleo = pr.venda_oleo * fbo;
  preco_gas = pr.venda_gas;

  //calculo do valor de venda do barril de petroleoem milhoes de dolares
  custo_producao_oleo = (7.08 * pr.producao_oleo);
  custo_producao_gas = (0.0072 * pr.producao_gas);

  resultado = (((preco_oleo * custo_producao_oleo) + (preco_gas * custo_producao_gas))/1000000);

	return (resultado);
}

float participacao_especial(reservatorio pr) {
	float temp, temp1, resultado;

	temp = pr.producao_oleo;
	temp1 = receita_bruta(pr);
	/* a participacao especial eh aplicada na producao de oleo do reservatorio, logo quanto maior a producao do reservatorio, maior eh a participacao especial. Producao abaixo de 900 mil metros cubicos de oleo equivalente possui isencao  */

	if (temp <= (900 * 1000000)) {
		resultado = 0;
	} else if (temp > (900 * 1000000) && temp <= (1350 * 1000000)) {
		resultado = temp1 * 0.1;
	} else if (temp > (1350 * 1000000) && temp <= (1800 * 1000000)) {
		resultado = temp1 * 0.2;
	} else if (temp > (1800 * 1000000) && temp <= (2550 * 1000000)) {
		resultado = temp1 * 0.3;
	} else if (temp > (2550 * 1000000) && temp <= (2700 * 1000000)) {
		resultado = temp1 * 0.35;
	} else {
		resultado = temp1 * 0.4;
	}

	return (resultado);
}

float pis_cofins(reservatorio pr) {
  float pis_cofins, temp;

	temp = receita_bruta(pr);

	pis_cofins = temp * 0.0925;

	return (pis_cofins);
}

float royalties(reservatorio pr) {
	float royalties, temp;

	temp = receita_bruta(pr);

	royalties = temp * 0.0848;

	return (royalties);
}

float receita_liquida(reservatorio pr) {
	float exploracao, perfuracao, completacao, abandono, temp1;

	//Investimentos contabilizados como despesas.
	exploracao = (44 * pr.poco_explorador);
	perfuracao = (14 * pr.poco_produtor) + (14 * pr.poco_injetor);
	completacao = (13 * pr.poco_produtor) + (13 * pr.poco_injetor);
	abandono = (2.43 * pr.poco_produtor) + (2.43 * pr.poco_injetor);

	temp1 = receita_bruta(pr);

	return (temp1 - exploracao - perfuracao - completacao - abandono);
}

float lucro_tributario(reservatorio pr) {
	//parcela de impostos que são pagos para a uniao.
	float temp1, temp2, temp3, temp4;

	temp1 = receita_liquida(pr);
	temp2 = royalties(pr);
	temp3 = pis_cofins(pr);
	temp4 = participacao_especial(pr);

	return (temp1 - temp2 - temp3 - temp4);
}

float IR_CSLL(reservatorio pr) {
	float temp;
	float resultado;

	temp = lucro_tributario(pr);

	if(temp <= 0) {
		resultado = 0;
	} else {
		resultado = temp * 0.34;
	}
	return resultado;
}

float FLC(reservatorio pr) {
	float temp1, temp2;

	temp1 = lucro_tributario(pr);
	temp2 = IR_CSLL(pr);

	return (temp1 - temp2);
}

float VPL(reservatorio pr) {
	float temp, temp1, temp2, p, taxa_desconto = 0.14;

	temp = FLC(pr);
	temp1 = 1 - taxa_desconto;
	temp2 = pr.tempo_producao;
	p = pow(temp1, temp2);

	return (temp / p);
}

reservatorio *cadastra_dados_mensal(registro *ini) {
	system("clear");

	// Declaracao de variaveis de controle.
	reservatorio temp;
	float calculo_vpl = 0;

	// Recebe os dados do usuário.
	printf("Cadastro de Dados para Analise Mensal do VPL\n\n");
  printf("\t Informe o nome da empresa: ");
	ler_string(temp.nome_empresa, 100);
  printf("\t Informe o nome do campo: ");
	ler_string(temp.nome_campo, 100);
	printf("\t Mes (01 a 12): ");
	scanf("%d", &temp.mes);
	printf("\t Ano : ");
	scanf("%d", &temp.ano);
	printf("\t Quantidade de Poco Produtor: ");
	scanf("%f", &temp.poco_produtor);
	printf("\t Quantidade de Poco Injetor: ");
	scanf("%f", &temp.poco_injetor);
	printf("\t Quantidade de Poco Explorador: ");
	scanf("%f", &temp.poco_explorador);
	printf("\t Quantidade de Poco Abandonado: ");
	scanf("%f", &temp.poco_abandonado);
	printf("\t Preco de Venda do Oleo (em dolar): ");
	scanf("%f", &temp.venda_oleo);
	printf("\t Preco de Venda do Gas (em dolar): ");
	scanf("%f", &temp.venda_gas);
	printf("\t Tempo de Producao dos Pocos (em dias): ");
	scanf("%f", &temp.tempo_producao);
	printf("\t Producao Total do Oleo (em bbl): ");
	scanf("%f", &temp.producao_oleo);
	printf("\t Producao Total do Gas (em bbl): ");
	scanf("%f", &temp.producao_gas);

	// Realiza o calculo do valor presente liquido do projeto.
	calculo_vpl = VPL(temp);
	temp.VPL = calculo_vpl;
	printf("\t VPL: %.2f\n", temp.VPL);

	insere(temp, ini);
	MAX++;
	system ( "read -n 1 -s -p \"Pressione qualquer tecla para continuar...\"" );
}

void imprime_lista_mensal(registro *ini){
	system("clear");
	if (ini->prox != NULL) {
		registro *p;

		for (p = ini->prox; p != NULL; p = p->prox){
			printf("\t Lista Mensal\n\n");
			printf("\t Nome da Empresa: %s\n", p->conteudo.nome_empresa);
			printf("\t Nome do Campo..: %s\n", p->conteudo.nome_campo);
			printf("\t Mes : %d\n", p->conteudo.mes);
			printf("\t Ano : %d\n", p->conteudo.ano);
			printf("\t Quantidade de Poco Produtor: %.2f\n", p->conteudo.poco_produtor);
			printf("\t Quantidade de Poco Injetor: %.2f\n", p->conteudo.poco_injetor);
			printf("\t Quantidade de Poco Explorador: %.2f\n", p->conteudo.poco_explorador);
			printf("\t Quantidade de Poco Abandonado: %.2f\n", p->conteudo.poco_abandonado);
			printf("\t Preco de Venda do Oleo (em dolar): %.2f\n", p->conteudo.venda_oleo);
			printf("\t Preco de Venda do Gas (em dolar): %.2f\n", p->conteudo.venda_gas);
			printf("\t Tempo de Producao dos Pocos (até 31 dias): %.2f\n", p->conteudo.tempo_producao);
			printf("\t Producao Total do Oleo (em bbl): %.2f\n", p->conteudo.producao_oleo);
			printf("\t Producao Total do Gas (em bbl): %.2f\n", p->conteudo.producao_gas);
			printf("\t VPL: %.2f\n", p->conteudo.VPL);
			printf("\n-------------------------------------------------------------------------\n\n");
		}
	} else {
		printf("Não existem registros de lista mensal cadastrados.\n");
	}

	// No windows usar system("pause");
	system( "read -n 1 -s -p \"Pressione qualquer tecla para continuar...\"" );
}

void remover_dados(registro *ini)
{
	system("clear");
	int mes, ano;
	printf("Digite o mes que deseja remover: ");
	scanf("%d", &mes);
	printf("Digite o ano que deseja remover: ");
	scanf("%d", &ano);

	// se a posição  é valida, e aquele registro existe
	registro *temp;
	temp = busca(mes, ano, ini);

	if (temp != NULL){
		remova(temp->conteudo, ini);
		MAX--;
		printf("Registro do Mes: %d e Ano: %d foi removido com sucesso.\n", temp->conteudo.mes, temp->conteudo.ano);
		system ( "read -n 1 -s -p \"Pressione qualquer tecla para continuar...\"" );
	}else{
		printf("Registro nao encontrado, verifique os dados da busca!\n");
		system ( "read -n 1 -s -p \"Pressione qualquer tecla para continuar...\"" );
	}
}


void imprime_lista_anual(registro *ini){
	system("clear");

	int ano_controle = 0;

	reservatorio resultado;

	// Verifica se a lista está vazia.
	if (ini->prox != NULL) {
		registro *p;
		p = ini->prox;

		while ((p != NULL)) {
			if (ano_controle != p->conteudo.ano) {
				// Imprime o cabeçalho da lista
				printf("\n");
				printf("\t Lista Ano: %d \n", p->conteudo.ano);
				printf("\t-----------------------------------------\n");
				printf("\t Nome da Empresa: %s\n", p->conteudo.nome_empresa);
				printf("\t Nome do Campo..: %s\n", p->conteudo.nome_campo);
				printf("\t-----------------------------------------\n");

				// Zera os valores para o início do cálculo.
				resultado.poco_produtor = 0;
				resultado.poco_injetor = 0;
				resultado.poco_explorador = 0;
				resultado.poco_abandonado = 0;
				resultado.venda_oleo = 0;
				resultado.venda_gas = 0;
				resultado.tempo_producao = 0;
				resultado.producao_oleo = 0;
				resultado.producao_gas = 0;
				resultado.VPL = 0;

				ano_controle = p->conteudo.ano;
			}

			for (NULL; (p != NULL && ano_controle == p->conteudo.ano); p = p->prox) {
				resultado.poco_produtor += p->conteudo.poco_produtor;
				resultado.poco_injetor += p->conteudo.poco_injetor;
				resultado.poco_explorador += p->conteudo.poco_explorador;
				resultado.poco_abandonado += p->conteudo.poco_abandonado;
				resultado.tempo_producao += p->conteudo.tempo_producao;
				resultado.producao_oleo += p->conteudo.producao_oleo;
				resultado.producao_gas += p->conteudo.producao_gas;
				resultado.VPL += p->conteudo.VPL;
			}

			printf("\t Quantidade de Poco Produtor: %.2f\n", resultado.poco_produtor);
			printf("\t Quantidade de Poco Injetor: %.2f\n", resultado.poco_injetor);
			printf("\t Quantida de de Poco Explorador: %.2f\n", resultado.poco_explorador);
			printf("\t Quantidade de Poco Abandonado: %.2f\n", resultado.poco_abandonado);
			printf("\t Tempo de Producao dos Pocos (em dias): %.2f\n", resultado.tempo_producao);
			printf("\t Producao Total do Oleo (em bbl): %.2f\n", resultado.producao_oleo);
			printf("\t Producao Total do Gas (em bbl): %.2f\n", resultado.producao_gas);
			printf("\t VPL (em dolar): %.2f\n", resultado.VPL);
			printf("\n-------------------------------------------------------------------------\n");
		}
	} else {
		printf("Não existem registros cadastrados para realizar a análise anual.\n");
	}

	// No windows usar system("pause");
	system( "read -n 1 -s -p \"Pressione qualquer tecla para continuar...\"" );
}
