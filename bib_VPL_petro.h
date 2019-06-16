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
	struct reservatorio *prox;
} reservatorio;


int menu(void)
{
	// No windows usar system("cls");
	system("clear");
	int c = 0;
	do {
		printf("Este eh um programa que calcula o VPL de projetos petroliferos!\n\n -- MENU:\n");
		printf("\t 1. Cadastrar os Dados da Analise Mensal\n");
		printf("\t 2. Listar Analises Mensais\n");
		printf("\t 3. Listar Analises Anuais\n");
		printf("\t 4. Sair\n\n");
		printf("-- Digite sua escolha: ");
		scanf("%d", &c);
	} while (c <= 0 || c > 4);
	getchar();
	return c;
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

float receita_bruta(reservatorio *pr) {
  float preco_oleo, preco_gas, custo_producao_oleo, custo_producao_gas, resultado;
  //fator de qualidade do oleo e gas
  float fbo = 1.95;
  float fbg = 0.0468;

  preco_oleo = pr->venda_oleo * fbo;
  preco_gas = pr->venda_gas * fbg;

  //calculo dos custos operacionais em milhoes de dolares
  custo_producao_oleo = ((7.08 * pr->producao_oleo) / 1000000);
  custo_producao_gas = ((0.0072 * pr->producao_oleo) / 1000000);

  resultado = (((preco_oleo * custo_producao_oleo) + (preco_gas * custo_producao_gas)) / 1000000);

	return (resultado);
}

float participacao_especial(reservatorio *pr) {
	float temp, temp1, resultado;

	temp = pr->producao_oleo;
	temp1 = receita_bruta(pr);
	/* a participacao especial eh aplicada na producao de oleo do reservatorio, logo quanto maior a producao do reservatorio, maior eh a participacao especial */

	if (temp <= 900) {
		resultado = 0;
	} else if (temp > 900 && temp <= 1350) {
		resultado = temp1 * 0.1;
	} else if (temp > 1350 && temp <= 1800) {
		resultado = temp1 * 0.2;
	} else if (temp > 1800 && temp <= 2550) {
		resultado = temp1 * 0.3;
	} else if (temp > 2550 && temp <= 2700) {
		resultado = temp1 * 0.35;
	} else {
		resultado = temp1 * 0.4;
	}

	return (resultado);
}

float pis_cofins(reservatorio *pr) {
  float pis_cofins, temp;

	temp = receita_bruta(pr);

	pis_cofins = temp * 0.0925;

	return (pis_cofins);
}

float royalties(reservatorio *pr) {
	float royalties, temp;

	temp = receita_bruta(pr);

	royalties = temp * 0.0848;

	return (royalties);
}

float receita_liquida(reservatorio *pr) {
	float aluguel, exploracao, perfuracao, completacao, abandono, temp1;

	exploracao = (44 * pr->poco_explorador) + 97;
	perfuracao = (14 * pr->poco_produtor) + (14 * pr->poco_injetor);
	completacao = (13 * pr->poco_produtor) + (13 * pr->poco_injetor);
	abandono = (2.43 * pr->poco_produtor) + (2.43 * pr->poco_injetor);

	temp1 = receita_bruta(pr);

	return (temp1 - exploracao - perfuracao - completacao - abandono);
}

float lucro_tributario(reservatorio *pr) {
	float temp1, temp2, temp3, temp4;

	temp1 = receita_liquida(pr);
	temp2 = royalties(pr);
	temp3 = pis_cofins(pr);
	temp4 = participacao_especial(pr);

	return (temp1 - temp2 - temp3 - temp4);
}

float IR_CSLL(reservatorio *pr) {
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

float FLC(reservatorio *pr) {
	float temp1, temp2;

	temp1 = lucro_tributario(pr);
	temp2 = IR_CSLL(pr);

	return (temp1 - temp2);
}

float VPL(reservatorio *pr) {
	float temp, temp1, temp2, p, taxa_desconto = 0.14;

	temp = FLC(pr);
	temp1 = 1 - taxa_desconto;
	temp2 = pr->tempo_producao;
	p = pow(temp1, temp2);

	return (temp / p);
}

reservatorio *cadastra_dados_mensal(reservatorio *p) {
	// Declaracao de ponteiros de controle.
	reservatorio *novo = NULL, *temp = p;
	float calculo_vpl = 0;

	// Aloca o espaço de memória necessário para salvar uma lista mensal de reservatorios.
  novo = (reservatorio *) malloc(sizeof (reservatorio));

	// Recebe os dados do usuário.
	printf("Cadastro de Dados para Analise Mensal do VPL\n");
  printf("\t Informe o nome da empresa: ");
	ler_string(novo->nome_empresa, 100);
  printf("\t Informe o nome do campo: ");
	ler_string(novo->nome_campo, 100);
	printf("\t Mes (01 a 12): ");
	scanf("%d", &novo->mes);
	printf("\t Ano : ");
	scanf("%d", &novo->ano);
	printf("\t Quantidade de Poco Produtor: ");
	scanf("%f", &novo->poco_produtor);
	printf("\t Quantidade de Poco Injetor: ");
	scanf("%f", &novo->poco_injetor);
	printf("\t Quantidade de Poco Explorador: ");
	scanf("%f", &novo->poco_explorador);
	printf("\t Quantidade de Poco Abandonado: ");
	scanf("%f", &novo->poco_abandonado);
	printf("\t Preco de Venda do Oleo (em dolar): ");
	scanf("%f", &novo->venda_oleo);
	printf("\t Preco de Venda do Gas (em dolar): ");
	scanf("%f", &novo->venda_gas);
	printf("\t Tempo de Producao dos Pocos (em dias): ");
	scanf("%f", &novo->tempo_producao);
	printf("\t Producao Total do Oleo (em bbl): ");
	scanf("%f", &novo->producao_oleo);
	printf("\t Producao Total do Gas (em bbl): ");
	scanf("%f", &novo->producao_gas);

	// Realiza o calculo do valor presente liquido do projeto.
	calculo_vpl = VPL(novo);
	novo->VPL = calculo_vpl;

	// Indica que o elemento que será adicionado na lista é o último elemento.
  novo->prox = NULL;

	// Verifica se a lista está vazia.
  if (p == NULL) {
		// Retorna os novos dados cadastrados como sendo o primeiro elemento da lista.
    return novo;
  } else {
		// Percorre toda a lista em busca do último elemento (mensal->prox == NUL).
    while (temp->prox != NULL) {
      temp = temp->prox;
    }
    temp->prox = novo;
    return p;
  }
}

void imprime_lista_mensal(reservatorio *p) {
	system("clear");

  reservatorio *temp = p;
	while (temp != NULL) {
		printf("\t Lista Mensal\n");
		printf("\t Nome da Empresa: %s\n", temp->nome_empresa);
		printf("\t Nome do Campo..: %s\n", temp->nome_campo);
		printf("\t Mes : %d\n", temp->mes);
		printf("\t Ano : %d\n", temp->ano);
		printf("\t Quantidade de Poco Produtor: %.2f\n", temp->poco_produtor);
		printf("\t Quantidade de Poco Injetor: %.2f\n", temp->poco_injetor);
		printf("\t Quantidade de Poco Explorador: %.2f\n", temp->poco_explorador);
		printf("\t Quantidade de Poco Abandonado: %.2f\n", temp->poco_abandonado);
		printf("\t Preco de Venda do Oleo (em dolar): %.2f\n", temp->venda_oleo);
		printf("\t Preco de Venda do Gas (em dolar): %.2f\n", temp->venda_gas);
		printf("\t Tempo de Producao dos Pocos (até 31 dias): %.2f\n", temp->tempo_producao);
		printf("\t Producao Total do Oleo (em bbl): %.2f\n", temp->producao_oleo);
		printf("\t Producao Total do Gas (em bbl): %.2f\n", temp->producao_gas);
		printf("\t VPL: %.2f\n", temp->VPL);
		printf("------------------------------------------------\n");
		temp = temp->prox;
	}

	// No windows usar system("pause");
	system( "read -n 1 -s -p \"Pressione qualquer tecla para continuar...\"" );
}

void imprime_lista_anual(reservatorio *p) {
	system("clear");

  reservatorio *temp = p;
	while (temp != NULL) {
		printf("\t Lista Anual\n");
		printf("\t Nome da Empresa: %s\n", temp->nome_empresa);
		printf("\t Nome do Campo..: %s\n", temp->nome_campo);
		printf("\t Mes : %d\n", temp->mes);
		printf("\t Ano : %d\n", temp->ano);
		printf("\t Quantidade de Poco Produtor: %.2f\n", temp->poco_produtor);
		printf("\t Quantidade de Poco Injetor: %.2f\n", temp->poco_injetor);
		printf("\t Quantidade de Poco Explorador: %.2f\n", temp->poco_explorador);
		printf("\t Quantidade de Poco Abandonado: %.2f\n", temp->poco_abandonado);
		printf("\t Preco de Venda do Oleo (em dolar): %.2f\n", temp->venda_oleo);
		printf("\t Preco de Venda do Gas (em dolar): %.2f\n", temp->venda_gas);
		printf("\t Tempo de Producao dos Pocos (em dias): %.2f\n", temp->tempo_producao);
		printf("\t Producao Total do Oleo (em bbl): %.2f\n", temp->producao_oleo);
		printf("\t Producao Total do Gas (em bbl): %.2f\n", temp->producao_gas);
		printf("\t VPL: %.2f\n", temp->VPL);

		temp = temp->prox;
	}

	// No windows usar system("pause");
	system( "read -n 1 -s -p \"Pressione qualquer tecla para continuar...\"" );
}

