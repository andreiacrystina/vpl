typedef struct {
	char nome_empresa[100];
	char nome_campo[100];
	char data[100];
	float poco_produtor;
	float poco_injetor;
	float poco_explorador;
  float poco_abandonado;
  float venda_oleo;
  float venda_gas;
  float tempo_producao;
  float producao_oleo;
  float producao_gas;
	struct mensal *prox;
} mensal;

typedef struct {
	char nome_empresa[100];
	char nome_campo[100];
	char data[100];
	float poco_produtor;
	float poco_injetor;
	float poco_explorador;
  float poco_abandonado;
  float venda_oleo;
  float venda_gas;
  float tempo_producao;
  float producao_oleo;
  float producao_gas;
	struct anual *prox;
} anual;

int menu(void)
{
	// No windows usar system("cls");
	system("clear");
	int c = 0;
	do {
		printf("Este eh um programa que calcula o VPL de projetos petroliferos!\n\n -- MENU:\n");
		printf("\t 1. Cadastrar os Dados da Analise Mensal\n");
		printf("\t 2. Cadastrar os Dados da Analise Anual\n");
		printf("\t 3. Listar Analises Mensais\n");
		printf("\t 4. Listar Analises Anuais\n");
		printf("\t 5. Sair\n\n");
		printf("-- Digite sua escolha: ");
		scanf("%d", &c);
	} while (c <= 0 || c > 5);
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

mensal *cadastra_dados_mensal(mensal *p) {
	// Declaracao de ponteiros de controle.
	mensal *novo = NULL, *temp = p;

	// Aloca o espaço de memória necessário para salvar uma lista mensal.
  novo = (mensal *) malloc(sizeof (mensal));

	// Recebe os dados do usuário.
	printf("Cadastro de Dados para Analise Mensal do VPL\n");
  printf("\t Informe o nome da empresa: ");
	ler_string(novo->nome_empresa, 100);
  printf("\t Informe o nome do campo: ");
	ler_string(novo->nome_campo, 100);
	printf("\t Data (mes/ano): ");
	ler_string(novo->data, 100);
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

anual *cadastra_dados_anual(anual *p) {
	// Declaracao de ponteiros de controle.
	anual *novo = NULL, *temp = p;

	// Aloca o espaço de memória necessário para salvar uma lista anual.
  novo = (anual *) malloc(sizeof (anual));

	// Recebe os dados do usuário.
	printf("Cadastro de Dados para Analise Anual do VPL\n");
	printf("\t Informe o nome da empresa: ");
	ler_string(novo->nome_empresa, 100);
  printf("\t Informe o nome do campo: ");
	ler_string(novo->nome_campo, 100);
	printf("\t Data (mes/ano): ");
	ler_string(novo->data, 100);
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

	// Indica que o elemento que será adicionado na lista é o último elemento.
  novo->prox = NULL;

	// Verifica se a lista está vazia.
  if (p == NULL) {
		// Retorna os novos dados cadastrados como sendo o primeiro elemento da lista.
    return novo;
  } else {
		// Percorre toda a lista em busca do último elemento (anual->prox == NUL).
    while (temp->prox != NULL) {
      temp = temp->prox;
    }
    temp->prox = novo;
    return p;
  }
}

void imprime_lista_mensal(mensal *p) {
	system("clear");

  mensal *temp = p;
	while (temp != NULL) {
		printf("\t Lista Mensal\n");
		printf("\t Nome da Empresa: %s\n", temp->nome_empresa);
		printf("\t Nome do Campo..: %s\n", temp->nome_campo);
		printf("\t Data : %s\n", temp->data);
		printf("\t Quantidade de Poco Produtor: %f\n", temp->poco_produtor);
		printf("\t Quantidade de Poco Injetor: %f\n", temp->poco_injetor);
		printf("\t Quantidade de Poco Explorador: %f\n", temp->poco_explorador);
		printf("\t Quantidade de Poco Abandonado: %f\n", temp->poco_abandonado);
		printf("\t Preco de Venda do Oleo (em dolar): %f\n", temp->venda_oleo);
		printf("\t Preco de Venda do Gas (em dolar): %f\n", temp->venda_gas);
		printf("\t Tempo de Producao dos Pocos (em dias): %f\n", temp->tempo_producao);
		printf("\t Producao Total do Oleo (em bbl): %f\n", temp->producao_oleo);
		printf("\t Producao Total do Gas (em bbl): %f\n", temp->producao_gas);

		temp = temp->prox;
	}

	// No windows usar system("pause");
	system( "read -n 1 -s -p \"Pressione qualquer tecla para continuar...\"" );
}

void imprime_lista_anual(anual *p) {
	system("clear");

  anual *temp = p;
	while (temp != NULL) {
		printf("\t Lista Anual\n");
		printf("\t Nome da Empresa: %s\n", temp->nome_empresa);
		printf("\t Nome do Campo..: %s\n", temp->nome_campo);
		printf("\t Data : %s\n", temp->data);
		printf("\t Quantidade de Poco Produtor: %f\n", temp->poco_produtor);
		printf("\t Quantidade de Poco Injetor: %f\n", temp->poco_injetor);
		printf("\t Quantidade de Poco Explorador: %f\n", temp->poco_explorador);
		printf("\t Quantidade de Poco Abandonado: %f\n", temp->poco_abandonado);
		printf("\t Preco de Venda do Oleo (em dolar): %f\n", temp->venda_oleo);
		printf("\t Preco de Venda do Gas (em dolar): %f\n", temp->venda_gas);
		printf("\t Tempo de Producao dos Pocos (em dias): %f\n", temp->tempo_producao);
		printf("\t Producao Total do Oleo (em bbl): %f\n", temp->producao_oleo);
		printf("\t Producao Total do Gas (em bbl): %f\n", temp->producao_gas);

		temp = temp->prox;
	}

	// No windows usar system("pause");
	system( "read -n 1 -s -p \"Pressione qualquer tecla para continuar...\"" );
}
