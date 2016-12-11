#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>

typedef struct 
{
	char rua[50];
	int numero;
	char complemento[50];
	char bairro[50];
	int cep;
	char cidade[50];
	char estado[50];
	char pais[50];
} address;

typedef struct 
{
	int DDD;
	int numero;
} phone;

typedef struct 
{
	int dia;
	int mes;
	int ano;
} date;

typedef struct
{
	char nome[100];
	char email[100];
	address endereco;
	phone telefone;
	date aniversario;
} agendaTelefonica;

/**
 * Limpa buffer
 */
void limparBuffer()
{
	fflush(stdin);
	__fpurge(stdin);
}

/**
 * Voltar ao menu principal
 */
void voltarMenu()
{
	printf("\n\nPressione [ENTER] para voltar ao menu principal...");

	limparBuffer();
	getchar();
	system("clear");
}

/**
 * Zerar dados de contato
 */
agendaTelefonica* zerarContato(agendaTelefonica *agenda, int posicao)
{
	strcpy(agenda[posicao].nome, "");
	strcpy(agenda[posicao].email, "");
	strcpy(agenda[posicao].endereco.rua, "");
	agenda[posicao].endereco.numero = 0;
	strcpy(agenda[posicao].endereco.complemento, "");
	strcpy(agenda[posicao].endereco.bairro, "");
	agenda[posicao].endereco.cep = 0;
	strcpy(agenda[posicao].endereco.cidade, "");
	strcpy(agenda[posicao].endereco.estado, "");
	strcpy(agenda[posicao].endereco.pais, "");
	agenda[posicao].telefone.DDD = 0;
	agenda[posicao].telefone.numero = 0;
	agenda[posicao].aniversario.dia = 0;
	agenda[posicao].aniversario.mes = 0;
	agenda[posicao].aniversario.ano = 0;

	return agenda;
}

/**
 * Reordena agenda em ordem alfabetica
 */
agendaTelefonica* reordenaAgenda(agendaTelefonica *agenda, int n)
{
	agendaTelefonica *aux = (agendaTelefonica*) malloc(sizeof(agendaTelefonica));

	for (int i = 0; i < n; ++i)
	{
		for (int j = i+1; j < n; ++j)
		{
			if(strcoll(agenda[i].nome, agenda[j].nome) > 1){
				aux[0] = agenda[i];
				agenda[i] = agenda[j];
				agenda[j] = aux[0];
			}
		}
	}

	free(aux);

	return agenda;
}

/**
 * Mostrar contato
 */
void mostrarContato(agendaTelefonica *agenda, int i)
{
	printf("USUÁRIO[%d]\n", i+1);
	printf("Nome: %s\n", agenda[i].nome);
	printf("E-mail: %s\n", agenda[i].email);
	printf("Rua: %s\n", agenda[i].endereco.rua);
	printf("Número: %d\n", agenda[i].endereco.numero);
	printf("Complemento: %s\n", agenda[i].endereco.complemento);
	printf("Bairro: %s\n", agenda[i].endereco.bairro);
	printf("CEP: %d\n", agenda[i].endereco.cep);
	printf("Cidade: %s\n", agenda[i].endereco.cidade);
	printf("Estado: %s\n", agenda[i].endereco.estado);
	printf("Pais: %s\n", agenda[i].endereco.pais);
	printf("Telefone: (%d) %d\n", agenda[i].telefone.DDD, agenda[i].telefone.numero);
	printf("Aniversario: %d/%d/%d\n", agenda[i].aniversario.dia, agenda[i].aniversario.mes, agenda[i].aniversario.ano);
}

/**
 * Faz uma busca nas opcoes de inteiros em um vetor
 */
int buscaOpcaoVetorInteiros(int vetor[], int tamanho, int escolha)
{
	int encontrou = 0;

	for (int i = 0; i < tamanho; ++i)
	{
		if(vetor[i] == escolha)
			encontrou = 1;
	}

	return encontrou;
}

/**
 * Inserir contato
 */
agendaTelefonica* inserirContato(agendaTelefonica *agenda, int *n)
{
	printf("Insira o nome: ");
	limparBuffer();
	scanf("%[^\n]", agenda[*n].nome);

	printf("Insira o e-mail: ");
	limparBuffer();
	scanf("%[^\n]", agenda[*n].email);

	printf("Insira o nome da rua: ");
	limparBuffer();
	scanf("%[^\n]", agenda[*n].endereco.rua);

	printf("Insira o numero da residencia: ");
	scanf("%d", &agenda[*n].endereco.numero);

	printf("Insira o complemento: ");
	limparBuffer();
	scanf("%[^\n]", agenda[*n].endereco.complemento);

	printf("Insira o bairro: ");
	limparBuffer();
	scanf("%[^\n]", agenda[*n].endereco.bairro);

	printf("Insira o cep: ");
	scanf("%d", &agenda[*n].endereco.cep);

	printf("Insira a cidade: ");
	limparBuffer();
	scanf("%[^\n]", agenda[*n].endereco.cidade);

	printf("Insira o estado: ");
	limparBuffer();
	scanf("%[^\n]", agenda[*n].endereco.estado);

	printf("Insira o pais: ");
	limparBuffer();
	scanf("%[^\n]", agenda[*n].endereco.pais);

	printf("Insira o DDD: ");
	scanf("%d", &agenda[*n].telefone.DDD);

	printf("Insira o telefone: ");
	scanf("%d", &agenda[*n].telefone.numero);

	printf("Insira o dia em que nasceu: ");
	scanf("%d", &agenda[*n].aniversario.dia);

	printf("Insira o mes em que nasceu: ");
	scanf("%d", &agenda[*n].aniversario.mes);

	printf("Insira o ano em que nasceu: ");
	scanf("%d", &agenda[*n].aniversario.ano);

	printf("\nContato inserido com sucesso!");
	*n = *n + 1;

	return reordenaAgenda(agenda, *n);
}

/**
 * Remover contato
 */
agendaTelefonica* removerContato(agendaTelefonica *agenda, int *n)
{
	char nome[100];

	printf("Deseja remover qual contato? (insira o nome)\n");
	limparBuffer();
	scanf("%[^\n]", nome);

	for (int i = 0; i < *n; ++i)
	{
		if(strcmp(agenda[i].nome, nome) == 0){
			agenda = zerarContato(agenda, i);

			for (int j = i; j < *n - 1; ++j)
				agenda[j] = agenda[j+1];

			agenda = zerarContato(agenda, *n-1);

			printf("\nContato removido com sucesso!");
			*n = *n - 1;

			return agenda;
		}
	}

	printf("\nNenhum contato encontrado com este nome.");

	return agenda;
}

/**
 * Buscar contato por nome
 */
void buscarPorNome(agendaTelefonica *agenda, int n)
{
	char nome[100];

	printf("Deseja buscar por qual nome? ");
	limparBuffer();
	scanf("%[^\n]", nome);

	for (int i = 0; i < n; ++i)
	{
		if(strcmp(agenda[i].nome, nome) == 0){
			printf("\nContato encontrado... \n\n");
			mostrarContato(agenda, i);
			return;
		}
	}

	printf("\nNenhum contato encontrado com este nome.");
}

/**
 * Buscar contato por mes de aniversario
 */
void buscarPorMesAniversario(agendaTelefonica *agenda, int n)
{
	int i, mes, totalEncontrados = 0, encontrados[] = {}, escolhaOpcoes[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

	printf("Digite 1 para: Janeiro\n");
	printf("Digite 2 para: Fevereiro\n");
	printf("Digite 3 para: Marco\n");
	printf("Digite 4 para: Abril\n");
	printf("Digite 5 para: Maio\n");
	printf("Digite 6 para: Junho\n");
	printf("Digite 7 para: Julho\n");
	printf("Digite 8 para: Agosto\n");
	printf("Digite 9 para: Setembro\n");
	printf("Digite 10 para: Outubro\n");
	printf("Digite 11 para: Novembro\n");
	printf("Digite 12 para: Dezembro\n\n");
	printf("Qual mes você deseja? ");

	scanf("%d", &mes);

	if(buscaOpcaoVetorInteiros(escolhaOpcoes, sizeof(escolhaOpcoes) / sizeof(int), mes) == 0){
		system("clear");
		printf("Opção inválida!\n");
		buscarPorMesAniversario(agenda, n);
		return;
	}

	for (i = 0; i < n; ++i)
	{
		if(agenda[i].aniversario.mes == mes){
			encontrados[totalEncontrados] = i;
			totalEncontrados++;
		}
	}

	if(totalEncontrados)
	{
		system("clear");

		if(totalEncontrados == 1)
			printf("Foi encontrado 1 contato para sua busca...\n\n");
		else
			printf("Foram encontrados %d contatos para sua busca...\n\n", totalEncontrados);

		for (i = 0; i < totalEncontrados; ++i){
			mostrarContato(agenda, encontrados[i]);
			printf("\n");
		}

		return;
	}

	printf("\nNenhum contato encontrado para este mes.");
}

/**
 * Listar todos os contatos
 */
void listarContatos(agendaTelefonica *agenda, int n)
{
	if(n == 0)
		return;
	else if(n == 1)
		printf("Existe 1 contato na sua agenda...\n\n");
	else
		printf("Existem %d contatos na sua agenda...\n\n", n);

	for (int i = 0; i < n; ++i)
	{
		mostrarContato(agenda, i);
		printf("\n");	
	}
}

int main(void)
{
	int escolha, n = 0, totalRegistros = 100, escolhaOpcoes[] = {0, 1, 2, 3, 4, 5};

	agendaTelefonica *agenda;
	agenda = (agendaTelefonica*) malloc(totalRegistros * sizeof(agendaTelefonica));

	do
	{
		printf("##### AGENDA TELEFONICA #####\n");
		printf("Digite 1 para: Incluir um novo contato\n");
		printf("Digite 2 para: Remover um contato\n");
		printf("Digite 3 para: Buscar um contato pelo nome\n");
		printf("Digite 4 para: Buscar um contato pelo mes de aniversario\n");
		printf("Digite 5 para: Listar todos os contatos\n");
		printf("Digite 0 para: Sair\n\n");
		printf("Qual opção você deseja? ");

		scanf("%d", &escolha);

		if(buscaOpcaoVetorInteiros(escolhaOpcoes, sizeof(escolhaOpcoes) / sizeof(int), escolha) == 0){
			printf("\nOpção inválida!");
			voltarMenu();
		}

		switch(escolha)
		{
			/**
			 * Incluir um novo contato
			 */
			case 1:
				system("clear");
				agenda = inserirContato(agenda, &n);
				voltarMenu();
			break;

			/**
			 * Remover contato
			 */
			case 2:
				system("clear");
				agenda = removerContato(agenda, &n);
				voltarMenu();
			break;

			/**
			 * Buscar contato pelo nome
			 */
			case 3:
				system("clear");
				buscarPorNome(agenda, n);
				voltarMenu();
			break;

			/**
			 * Buscar contato pelo mes de aniversario
			 */
			case 4:
				system("clear");
				buscarPorMesAniversario(agenda, n);
				voltarMenu();
			break;

			/**
			 * Listar todos os contato
			 */
			case 5:
				system("clear");
				listarContatos(agenda, n);
				voltarMenu();
			break;
		}
	} while(escolha);
}