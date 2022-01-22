#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>

#include "functions.h" // Importar a defeni��o das fun��es

#define quantidadeMaximaEcoponto 500 // Define que a quantidade maxima dos ecopontos � 500

// Vari�veis globais
int maxRegistos = 0, totalRegistosIntroduzidos = 0, idProximoCliente = 1;
Ecoponto* ecopontos;

/* Implementa��o das fun��es */

// Fun��o para ler n�meros inteiro
// Recebe um ponteiro para um inteiro
// Dentro dela verificamos se o valor introduzido � v�lido, ou sej� se � um n�mero inteiro
// Se n�o for voltamos a perguntar at� o utilizador introduzir um n�mero inteiro valido
// No fim ele devolve o valor introduzido para o ponteiro
void lerInteiro(int *n){
	int temp, res;

	// Verifica se o valor introduzido � um inteiro, se n�o for fazer loop at� introduzir um inteiro
	res = scanf("%d", &temp);
	while(res != 1) {
        printf("Tens de escrever um n�mero inteiro.\n");
		printf("Tenta de novo: ");
		fflush(stdin);
        res = scanf("%d", &temp);
    }

	fflush(stdin);

	// Mandar o valor da vari�vel temp para o ponteiro *n
	*n = temp;
}

// Fun��o para ler n�meros float
// Recebe um ponteiro para um float
// Dentro dela verificamos se o valor introduzido � v�lido, ou sej� se � um n�mero float
// Se n�o for voltamos a perguntar at� o utilizador introduzir um n�mero float valido
// No fim ele devolve o valor introduzido para o ponteiro
void lerFloat(float *n){
	int res;
	float temp;

	// Verifica se o valor introduzido � um float, se n�o for fazer loop at� introduzir um float
	res = scanf("%f", &temp);
	while(res != 1) {
		printf("Tens de escrever um n�mero real.\n");
		printf("Tenta de novo: ");
		fflush(stdin);
		res = scanf("%f", &temp);
	}

	fflush(stdin);

	// Mandar o valor da vari�vel temp para o ponteiro *n
	*n = temp;
}

// Fun��o para aumentar o maximo de registos que pode introduzir (mais 25)
// Primeiro passa os registos ja existentes para um array tempor�rio
// Depois libera o array antigo e cria um novo com mais 25 posi��es
int aumentarMaxRegistos() {
	int res = 1, i;
	
	// Verifica so o maximo de registos n�o � 0, se for � so criar o array com 25 posi��es
	if (maxRegistos == 0) {
		// Adiciona 25 a variavel maxRegistos
		maxRegistos += 25;
		// Calcula a posi��o de memoria nova para ele
		ecopontos = (Ecoponto*) malloc(maxRegistos * sizeof(Ecoponto));
		// Se o ecopontos for igual a NULL, ent�o apresenta uma msg de erro e remove os 25 do maxRegistos
		if (ecopontos == NULL) {
			maxRegistos -= 25;
			ecopontos = (Ecoponto*) malloc(maxRegistos * sizeof(Ecoponto));
			res = -1;
		}
	} else {
		// Criar um array tempor�rio para guardar os registos
		Ecoponto* tempArray = (Ecoponto*)malloc(maxRegistos * sizeof(Ecoponto));
		// Verifica se n�o deu erro
		if (tempArray == NULL) {
			res = -1;
		} else {
			// Copia os registos para o array tempor�rio
			for (i = 0; i < totalRegistosIntroduzidos; i++) {
				tempArray[i] = ecopontos[i];
			}
			// Adiciona 25 a variavel maxRegistos
			maxRegistos += 25;
			// Calcula a posi��o de memoria nova para ele
			ecopontos = (Ecoponto*) malloc(maxRegistos * sizeof(Ecoponto));
			// Se o ecopontos for igual a NULL, ent�o apresenta uma msg de erro e remove os 25 do maxRegistos
			if (ecopontos == NULL) {
				maxRegistos -= 25;
				ecopontos = (Ecoponto*) malloc(maxRegistos * sizeof(Ecoponto));
				res = -1;
			}
			// Copia os registos para o array principal
			for (i = 0; i < totalRegistosIntroduzidos; i++) {
				ecopontos[i] = tempArray[i];
			}
		}
        // Limpa o array temporario
		free(tempArray);
		tempArray = NULL;
	}
	return res;
}

// Fun��o para chamar o menu principal
// N�o recebe nem retorna nenhum valor
// Dentro dela mostramos as op��es do menu principal e pedimos ao utilizador que escolha uma op��o
// Depois verificamos se a op��o � valida e se for mandamos para a devida fun��o
void menuPrincipal() { 
	// Declara��o das variaveis
	int opcao, respCarregarRegistos, respGuardarRegistos;
	char opcaoStr;
	
	// Faz enquanto a op��o for diferente de 0
	do {
	    printf("\n\nOpc�es do MENU:\n");
		printf("Op��o 1: Sub-menu Adicionar\n"); 
		printf("Op��o 2: Sub-menu Editar\n");     
		printf("Op��o 3: Remover\n");
		printf("Op��o 4: Sub-menu Procurar\n");
		printf("Op��o 5: Calcular rota\n");
		printf("Op��o 6: Sub-menu Listar ecopontos\n");
		printf("Op��o 7: Limpar ecoponto\n");
		printf("Op��o 8: Calcular m�dia de res�duos\n");
		printf("Op��o 9: Carregar os registos\n");
		printf("Op��o 10: Guardar os registos\n");
		printf("Op��o 0: Sair\n");
		printf("Escolha uma op��o: ");
		lerInteiro(&opcao);
		switch (opcao) {
			case 1:
				menuAdicionar();
				break;
			case 2:
				// Verifica se existe algum registo, se n�o existir apresenta uma msg de erro
				if (totalRegistosIntroduzidos == 0) {
					printf("Tens de ter pelo menos um ecoponto para poder alterar.");
				} else {
					editarEco();
				}
				break;
			case 3:
				// Verifica se existe algum registo, se n�o existir apresenta uma msg de erro
				if (totalRegistosIntroduzidos == 0) {
					printf("Tens de ter pelo menos um ecoponto para poder remover.");
				} else {
					removerEco();
				}
				break;
			case 4:
				// Verifica se existe algum registo, se n�o existir apresenta uma msg de erro
				if (totalRegistosIntroduzidos == 0) {
					printf("Tens de ter pelo menos um ecoponto para poder procurar.");
				} else {
					menuProcurar();
				}
				break;
			case 5:
				// Verifica se existe algum registo, se n�o existir apresenta uma msg de erro
				if (totalRegistosIntroduzidos == 0) {
					printf("Tens de ter pelo menos um ecoponto para poder calcular a rota.");
				} else {
					calcRota();
				}
				break;
			case 6:
				// Verifica se existe algum registo, se n�o existir apresenta uma msg de erro
				if (totalRegistosIntroduzidos == 0) {
					printf("Tens de ter pelo menos um ecoponto para poder listar.");
				} else {
					menuListar();
				}
				break;
			case 7:
				// Verifica se existe algum registo, se n�o existir apresenta uma msg de erro
				if (totalRegistosIntroduzidos == 0) {
					printf("Tens de ter pelo menos um ecoponto para poder remover res�duos.");
				} else {
					limparEco();
				}
				break;
			case 8:
				// Verifica se existe algum registo, se n�o existir apresenta uma msg de erro
				if (totalRegistosIntroduzidos == 0) {
					printf("Tens de ter pelo menos um ecoponto para poder calcular a media dos residuos.");
				} else {
					calcMediaResiduos();
				}
				break;
			case 9:
				// Verifica se existe algum registo, se existir ele pergunta se quer mesmo carregar os registos do arquivo
				// Pois ao carregar os registos, o array principal � limpo para receber os registos dos ecopontos que se encontram no arquivo
				if (totalRegistosIntroduzidos > 0) {
					printf("Todos os registos que est�o na memoria ser�o perdidos.\nTens a certeza que queres carregar os registos do arquivo [s/S]: ");
					scanf(" %c", &opcaoStr); getchar();
					if (opcaoStr == 's' || opcaoStr == 'S') {
						respCarregarRegistos = carregarRegistos();
					}
				} else {
					respCarregarRegistos = carregarRegistos();
				}
				
				// Verifica se n�o deu nenhum erro ao carregar os registos
				if (respCarregarRegistos == -1) {
					printf("Ocorreu um erro ao carregar os registos.\n");
				} else if (respGuardarRegistos == -2) {
					printf("N�o foi possivel alocar recursos para guardar os registos.\n");	
				} else if (respCarregarRegistos == 0) {
					printf("N�o foi possivel abrir o arquivo para carregar os registos.\n");
				} else {
					printf("Registos carregados com sucesso.\n");
				}
				break;
			case 10:
				// Verifica se existe algum registo, se n�o existir apresenta uma msg de erro
				if (totalRegistosIntroduzidos == 0) {
					printf("Tens de ter pelo menos um ecoponto para poder guardar os registos.");
				} else {
					// Verifica se ele quer mesmo salvar os registos, pois ao salvar os registos que se encontram no arquivos ir�o ser apagados
					printf("Ao guardar os registos no arquivo ir� apagar os que ja est�o la.\nQueres mesmo guardar os registos [s/S]: ");
					scanf(" %c", &opcaoStr); getchar();
					if (opcaoStr == 's' || opcaoStr == 'S') {
						respGuardarRegistos = guardarRegistos(ecopontos, totalRegistosIntroduzidos);

						// Verifica se n�o deu nenhum erro
						if (respGuardarRegistos == -1) {
							printf("Ocorreu um erro ao guardar os registos.\n");
						} else if (respGuardarRegistos == 0) {
							printf("N�o foi possivel abrir o arquivo para guardar os registos.\n");
						} else {
							printf("Registos salvos com sucesso.\n");
						}
					} else {
						printf("A cancelar... \n");
					}
				}
				break;
			case 0:
				printf("A sair...");
				break;
			default:
				printf("Op��o inv�lida, tenta novamente.");
				break;
		}
	} while(opcao != 0);	
}

// Fun��o para mostrar o sub-menu de Adicionar Ecopontos/lixo nos ecopontos
// N�o recebe nenhum parametro nem retorna nenhum valor
// Dentro dela mostramos o sub-menu e pedimos ao utilizador que escolha uma op��o
// Se a op��o escolhida for inv�lida, pedimos ao utilizador que tente novamente
// Se a op��o escolhida for v�lida, chamamos a respetiva fun��o escolhida
void menuAdicionar() {
	// Declara��o da variavel
	int opcao;
	
	// Do while para mostrar sempre o menu at� o utilizador introduzir a op��o 0
	do {
	    printf("\n\nSub-Menu Adicionar\n");
		printf("Op��o 1: Inserir Ecopontos\n");
		printf("Op��o 2: Inserir Res�duos\n");
		printf("Op��o 0: Voltar\n");
		printf("Escolha uma op��o: ");
		lerInteiro(&opcao);
		switch (opcao) {
			case 1:
				// Verifica se o utilizador ja n�o introduziu o maximo de ecopontos que o programa premite
				if (totalRegistosIntroduzidos == maxRegistos) {
					printf("N�o consegues introduzir mais ecopontos.");
				} else {
					adicionarEco();
				}
				break;
			case 2:
				// Verifica se ja introduziu pelo menos um ecoponto, se n�o tiver introduzido retorna mensagem erro
				if (totalRegistosIntroduzidos == 0) {
					printf("Para introduzir res�duos do ecoponto tens de ter pelo menos 1 ecoponto introduzido.");
				} else {
					adicionarResiduos();
				}
				break;	
			case 0:
				printf("A voltar...");
				break;
			default:
				printf("Op��o inv�lida, tenta novamente.");
				break;
		}
	} while(opcao != 0);	
}

// Fun��o para mostrar o sub-menu de Procurar Ecopontos pelo tipo, ou cheios
// N�o recebe nenhum parametro nem retorna nenhum valor
// Dentro dela mostramos o sub-menu e pedimos ao utilizador que escolha uma op��o
// Se a op��o escolhida for inv�lida, pedimos ao utilizador que tente novamente
// Se a op��o escolhida for v�lida, chamamos a respetiva fun��o escolhida
void menuProcurar() {
    // Declara��o das variaveis
	int opcao, tipo;

	do {
	    printf("\n\nSub-Menu Procurar\n");
		printf("Op��o 1: Procurar por tipo\n");
		printf("Op��o 2: Procurar ecopontos cheios\n");
		printf("Op��o 0: Voltar\n");
		printf("Escolha uma op��o: ");
		fflush(stdin);
		lerInteiro(&opcao);
		switch (opcao) {
			case 1:
				// Pergunta o tipo de ecoponto at� o utilizador introduzir um v�lido
				printf("Digite o tipo que pretende procurar (1 - papel�o, 2 - vidr�o, 3 - ole�o): ");
				lerInteiro(&tipo);
				while (tipo < 1 || tipo > 3) {
					printf("ERRO. O tipo tem de ser 1 - papel�o, 2 - vidr�o, 3 - ole�o\n");
					printf("Introduza denovo o tipo: ");
					lerInteiro(&tipo);
				}
				// Chama a fun��o de listar os ecopontos de um certo tipo e passa o tipo escolhido pelo utilizador
				listartEcopontosTipo(tipo);
				break;
			case 2:
				listarEcopontosCheios();
				break;
			case 0:
				printf("A voltar...");
				break;
			default:
				printf("Op��o inv�lida, tenta novamente.");
				break;
		}
	} while(opcao != 0);
}

// Fun��o para mostrar o sub-menu de Listar todos os Ecopontos, ecopontos cheios ou pelo tipo de ecoponto
// N�o recebe nenhum parametro nem retorna nenhum valor
// Dentro dela mostramos o sub-menu e pedimos ao utilizador que escolha uma op��o
// Se a op��o escolhida for inv�lida, pedimos ao utilizador que tente novamente
// Se a op��o escolhida for v�lida, chamamos a respetiva fun��o escolhida
void menuListar() {
    // Declara��o das variaveis
	int opcao, tipoEcoponto;

	do{
		printf("\n\nOp��es de listagem:\n");
		printf("1 - Listar todos os ecopontos\n");
		printf("2 - Listar ecopontos cheios\n");
		printf("3 - Listar ecopontos de um tipo\n");
		printf("0 - Voltar\n");
		printf("Escolha uma op��o: ");
		lerInteiro(&opcao);
		switch (opcao)
		{
		case 1:
			listarEcopontos();
			break;
		case 2:
			listarEcopontosCheios();
			break;
		case 3:
			// Pergunta o tipo de ecoponto at� o utilizador introduzir um v�lido
			printf("Qual � o tipo de ecoponto que queres procurar ? (1 - papel�o, 2 - vidr�o, 3 - ole�o): ");
			lerInteiro(&tipoEcoponto);
			while (tipoEcoponto < 1 || tipoEcoponto > 3) {
				printf("ERRO. O tipo tem de ser 1 - papel�o, 2 - vidr�o, 3 - ole�o\n");
				printf("Introduza denovo o tipo: ");
				lerInteiro(&tipoEcoponto);
			}
			// Chama a fun��o de listar os ecopontos de um certo tipo e passa o tipo escolhido pelo utilizador
			listartEcopontosTipo(tipoEcoponto);
			break;
		case 0:
			printf("A voltar...");
			break;
		default:
			printf("Op��o inv�lida, tenta novamente.");
			break;
		}
	} while (opcao != 0);
}

// Fun��o para adicionar Ecopontos
// N�o recebe nem retorna nenhum valor
// Para adicionar um ecoponto, � necess�rio introduzir o tipo de ecoponto e a localiza��o x e y
// Existem valida��es para verificar se os dados que o utilizador introduzir s�o v�lidos
void adicionarEco() {
    // Declara��o das variaveis
	int respostaAumentarRegistosMaximos;

	ecopontos[totalRegistosIntroduzidos].id = idProximoCliente;

	printf("\nIntroduza os dados do ecoponto [%d]\n", idProximoCliente);
	printf("Introduza o tipo do ecoponto ( 1 - papel�o, 2 - vidr�o, 3 - ole�o ): ");
	lerInteiro(&ecopontos[totalRegistosIntroduzidos].tipo);
	while (ecopontos[totalRegistosIntroduzidos].tipo < 1 || ecopontos[totalRegistosIntroduzidos].tipo > 3) {
		printf("ERRO. A op��o tem de ser 1 - papel�o, 2 - vidr�o, 3 - ole�o.\n");
		printf("Introduza a op��o denovo: ");
		lerInteiro(&ecopontos[totalRegistosIntroduzidos].tipo);
	}

	printf("Introduza as coordenada X do ecoponto: ");
	lerFloat(&ecopontos[totalRegistosIntroduzidos].coordenadas.x);
	while (ecopontos[totalRegistosIntroduzidos].coordenadas.x < 0 || ecopontos[totalRegistosIntroduzidos].coordenadas.x > 1000) {
		printf("ERRO. A coordenada x tem de ser entre 0 e 1000.\n");
		printf("Introduza a nova coordenada x: ");
		lerFloat(&ecopontos[totalRegistosIntroduzidos].coordenadas.x);
	}

	printf("Introduza as coordenada Y do ecoponto: ");
	lerFloat(&ecopontos[totalRegistosIntroduzidos].coordenadas.y);
	while (ecopontos[totalRegistosIntroduzidos].coordenadas.y < 0 || ecopontos[totalRegistosIntroduzidos].coordenadas.y > 1000) {
		printf("ERRO. A coordenada y tem de ser entre 0 e 1000.\n");
		printf("Introduza a nova coordenada y: ");
		lerFloat(&ecopontos[totalRegistosIntroduzidos].coordenadas.y);
	}

	// Coloca a capacidade do ecoponto a 0
	ecopontos[totalRegistosIntroduzidos].capacidadeAtual = 0;

	// Incrementa +1 a varaivel totalRegistosIntroduzidos
	totalRegistosIntroduzidos++;
	// Incrementa +1 a variavel idProximoCliente
	idProximoCliente++;

	// MSG a dizer que o ecoponto foi adicionado
	printf("Ecoponto foi adicionado com sucesso.\n");

	// Se o totalRegistosIntroduzidos for igual a 25, ent�o aumentamos a capacidade do array
	if (totalRegistosIntroduzidos == 25) {
		respostaAumentarRegistosMaximos = aumentarMaxRegistos();
		if (respostaAumentarRegistosMaximos == -1) {
			printf("N�o foi possivel alocar mais espa�o para guardar mais ecopontos.\n");
		}
	}
}

// Fun��o para adicionar residuos
// N�o recebe nem retorna nenhum valor
// Para adicionar um residuo, � necess�rio introduzir o ID do ecoponto, e a quantidade de residuos
// Existem valida��es para verificar se os dados que o utilizador introduzir s�o v�lidos
void adicionarResiduos() {
    // Declara��o das variaveis
	int idProcura, posicaoArray, novaQuantidade = 0;
	float quantidadeResiduos;
	Ecoponto ecopontoProcura;

	printf("Introduza o ID do ecoponto que pretende adicionar res�duos: ");
	lerInteiro(&idProcura);
	while (idProcura < 1 || idProcura >= idProximoCliente) {
		printf("ERRO. O id tem de ser valido, entre 1 e %d\n", idProximoCliente - 1);
		printf("Introduza o novo ID: ");
		lerInteiro(&idProcura);
	}

	posicaoArray = procuraEcoponto(0, totalRegistosIntroduzidos, idProcura );

	if (posicaoArray == -1) {
		printf("N�o existe nenhum ecoponto com esse id.");
	} else {
		ecopontoProcura = ecopontos[posicaoArray];
		printf("Digita a quantidade de res�duos que pretende adicionar ao ecoponto: ");
		lerFloat(&quantidadeResiduos);
		while(quantidadeResiduos < 1) {
			printf("A quantidade tem que ser positiva. Digita novamente a quantidade: ");
			lerFloat(&quantidadeResiduos);
		}

		novaQuantidade = ecopontoProcura.capacidadeAtual + quantidadeResiduos;

		while(novaQuantidade > quantidadeMaximaEcoponto) {
			printf("A quantidade adicionada excede o limite, por favor adiciona um valor inferior a %.2f.\n", quantidadeMaximaEcoponto - ecopontoProcura.capacidadeAtual);
			printf("Introduza novamente a quantidade: ");
			lerFloat(&quantidadeResiduos);
			novaQuantidade = ecopontoProcura.capacidadeAtual + quantidadeResiduos;
		}

		ecopontos[posicaoArray].capacidadeAtual = novaQuantidade;
		printf("Residuos adicionados com sucesso.");
	}	
}

// Fun��o para remover/limpar os res�duos dos ecopontos
// N�o recebe nem retorna nenhum valor
// Para remover os res�duos do ecoponto � necessario informar o id do ecoponto
// Existem valida��es para verificar se os dados que o utilizador introduzir s�o v�lidos
void limparEco() {
    // Declara��o das variaveis
	int idProcura, posicaoArray;
	char opcao;

	printf("Introduza o ID do ecoponto que deseja limpar: ");
	lerInteiro(&idProcura);
	while (idProcura < 1 || idProcura >= idProximoCliente) {
		printf("ERRO. O id tem de ser v�lido, entre 1 e %d\n", idProximoCliente - 1);
		printf("Introduza o novo ID: ");
		lerInteiro(&idProcura);
	}

	posicaoArray = procuraEcoponto(0, totalRegistosIntroduzidos, idProcura);

	if (posicaoArray == -1) {
		printf("N�o existe nenhum ecoponto com esse id.");
	} else {
		if (ecopontos[posicaoArray].capacidadeAtual > 0){
			printf("Quer mesmo limpar o ecoponto %d [s/S]?", ecopontos[posicaoArray].id);
			scanf(" %c", &opcao); getchar();
			if(opcao != 's' && opcao != 'S') {
				printf("A cancelar...");
			} else {
				ecopontos[posicaoArray].capacidadeAtual = 0;
				printf("Ecoponto limpo com sucesso.");
			}
		} else {
			printf("Tu n�o podes limpar um ecoponto vazio.\n");
		}
	}	
}

// Fun��o para procurar um ecoponto pelo id ( Binary Search )
// Parte o array ao meio e compara se o n�mero procurado � o meio menor que o meio ou maior que o meio
// Se for maior ou menor repete novamente a fun��o s� que s� com a parte que est� depois do meio no caso de ser maior ou antes do meio no caso de ser menor
// Repete at� o alvo ser o meio
int procuraEcoponto(int inicio, int fim, int idProcura) {
    // Declara��o das variaveis
	int meio, res = -1;
	
	if (fim >= inicio) {
		meio = inicio + (fim - inicio) / 2;
		
		if (ecopontos[meio].id == idProcura) {
			res = meio; 
		} else if (ecopontos[meio].id > idProcura) {
			res = procuraEcoponto(inicio, meio - 1, idProcura);
		} else if (ecopontos[meio].id < idProcura) {
			res = procuraEcoponto(meio + 1, fim, idProcura);
		}
	}
	return res;
}

// Fun��o para editar os Ecopontos
// N�o recebe nem retorna nenhum valor
// Para editar os ecopontos � necessario introduzir o id do ecoponto
// Depois � mostrado um menu a perguntar o que o utilizador pertende trocar no ecoponto, � possivel trocar a localiza��o/posicao ou o tipo de ecoponto
void editarEco() {
    // Declara��o das variaveis
	int idProcura, posicaoArray, opcao;
	
	printf("Introduza o ID do ecoponto que pretende editar: ");
	lerInteiro(&idProcura);
	
	while (idProcura < 1 || idProcura >= idProximoCliente) {
		printf("O ID n�o pode ser maior que %d. Por favor introduza novamente: ", idProximoCliente - 1);
		lerInteiro(&idProcura);
	}

	posicaoArray = procuraEcoponto(0, totalRegistosIntroduzidos, idProcura);

	if (posicaoArray == -1) {
		printf("N�o existe nenhum ecoponto com esse id.");
	} else {
		// do while para mostrar o menu at� o utilizador introduzir uma op��o correta
	    do {
			printf("\nOpc�es para Alterar:\n");
			printf("Op��o 1: Alterar localiza��o\n");
			printf("Op��o 2: Alterar tipo do ecoponto\n");
			printf("Op��o 0: Voltar\n");
			printf("Escolha uma op��o: ");
			lerInteiro(&opcao);
			switch (opcao) {
				case 1:
					editarCoordenadas(posicaoArray);
					break;
				case 2:
					editarEcoTipo(posicaoArray);
					break;
				case 0:
					printf("A voltar....");
					break;
				default:
					printf("Op��o inv�lida.");
					break;
			}
		} while(opcao != 0);
	}
}

// Fun��o para alterar o tipo do ecoponto
// Recebe como par�metro a posi��o do ecoponto no array, e n�o retorna nenhum valor
// Tem valida��es para verificar o tipo em que tem de ser um dos 3
// Quando � alterado o tipo do ecoponto a quantidade atual de res�duos volta a 0
void editarEcoTipo(int posicaoArray) {
    // Declara��o das variaveis
	Ecoponto ecoponto = ecopontos[posicaoArray];
	int novoTipoEcoponto;

	printf("Introduza o novo tipo do ecoponto ( 1 - papel�o, 2 - vidr�o, 3 - ole�o ): ");
	lerInteiro(&novoTipoEcoponto);
	while (novoTipoEcoponto < 1 || novoTipoEcoponto > 3 || novoTipoEcoponto == ecoponto.tipo) {
		if (novoTipoEcoponto == ecoponto.tipo) {
			printf("Erro. O tipo n�o pode ser igual ao anterior.\n");
		} else {
			printf("O tipo tem de ser 1 - papel�o, 2 - vidr�o, 3 - ole�o\n");
		}

		printf("Introduza o novo tipo: ");
		lerInteiro(&novoTipoEcoponto);
	}

	ecopontos[posicaoArray].capacidadeAtual = 0;
	ecopontos[posicaoArray].tipo = novoTipoEcoponto;
	printf("Tipo de ecoponto editado com sucesso.");
}

// Fun��o para alterar as coordenadas do Ecoponto/posicao do Ecoponto
// Recebe como par�metro a posi��o do Ecoponto no array, e n�o retorna nenhum valor
// Tem um menu a perguntar se o utilizador pertende trocar as coordenadas de x ou y
// Tem valida��es para verificar se as coordenadas s�o v�lidas
// Quando � alterado as coordenadas do Ecoponto a quantidade atual de res�duos volta a 0
void editarCoordenadas(int posicaoArray) {
    // Declara��o das variaveis
	Ecoponto ecoponto = ecopontos[posicaoArray];
	int opcao;
	float novaCoordenada;

	do {
	    printf("\nOpc�es para Alterar:\n");
		printf("Op��o 1: Alterar coordenada X\n");
		printf("Op��o 2: Alterar coordenada Y\n");
		printf("Op��o 0: Voltar\n");
		printf("Escolha uma op��o: ");
		lerInteiro(&opcao);
		switch (opcao) {
			case 1:
                // Pergunta a coordenada do ponto x at� ser v�lida
				printf("Introduza a nova coordenada de x: ");
				lerFloat(&novaCoordenada);
				while(novaCoordenada < 0 || novaCoordenada > 1000 || novaCoordenada == ecoponto.coordenadas.x) {
					if (novaCoordenada == ecoponto.coordenadas.x) {
						printf("A nova coordenada n�o pode ser igual a antiga.\n");
					} else {
						printf("A coordenada tem de ser entre 0 e 1000.\n");
					}
					printf("Introduza a nova coordenada: ");
					lerFloat(&novaCoordenada);
				}
				// Altera a capacidade atual do ecoponto para 0 e a coordenada do ponto x
				ecopontos[posicaoArray].capacidadeAtual = 0;
				ecopontos[posicaoArray].coordenadas.x = novaCoordenada;
				printf("Coordenada x editada com sucesso.");
				break;
			case 2:
                // Pergunta a coordenada do ponto y at� ser v�lida
				printf("Introduza a nova coordenada de y: ");
				lerFloat(&novaCoordenada);
				while(novaCoordenada < 0 || novaCoordenada > 1000 || novaCoordenada == ecoponto.coordenadas.y) {
					if (novaCoordenada == ecoponto.coordenadas.y) {
						printf("A nova coordenada n�o pode ser igual a antiga.\n");
					} else {
						printf("A coordenada tem de ser entre 0 e 1000.\n");
					}
					printf("Introduza a nova coordenada: ");
					lerFloat(&novaCoordenada);
				}
				// Altera a capacidade atual para 0 e a coordenada do ponto y
				ecopontos[posicaoArray].capacidadeAtual = 0;
				ecopontos[posicaoArray].coordenadas.y = novaCoordenada;
				printf("Coordenada y editada com sucesso.");
				break;
			case 0:
				printf("A voltar....");
				break;
			default:
				printf("Op��o inv�lida.");
				break;
		}
	} while(opcao != 0);
}

// Fun��o para apagar um Ecoponto
// N�o recebe nem retorna nenhum parametro
// Primeiro pergunta o id do ecoponto que deseja apagar e verifica se existe
// Depois passa para um array temporario todos os ecopontos menos o que o utilizador deseja apagar
// Depois � limpo o array principal e passa os dados do temporario para o principal
// No fim de tudo o array temporario � apagado
void removerEco() {
    // Declara��o das variaveis
	int idProcura, posicaoArray, i, j = 0, respGuardarRegistos;
	char opcao;

	printf("Introduza o ID do ecoponto que pretende remover: ");
	lerInteiro(&idProcura);
	
	while (idProcura < 1 || idProcura >= idProximoCliente) {
		printf("O ID n�o pode ser maior que %d. Por favor introduza novamente: ", idProximoCliente - 1);
		lerInteiro(&idProcura);
	}

	posicaoArray = procuraEcoponto(0, totalRegistosIntroduzidos, idProcura );

	if (posicaoArray == -1) {
		printf("N�o existe nenhum ecoponto com esse id.");
	} else {
		printf("Queres mesmo apagar o ecoponto com o id %d [s/S]: ", ecopontos[posicaoArray].id);
		scanf(" %c", &opcao); getchar();
		if (opcao != 's' && opcao != 'S') {
			printf("Opera��o cancelada.\n");  
		} else {
			// Cria um array temporario para guardar os ecopontos
			Ecoponto *ecopontosTemp = (Ecoponto*) malloc(sizeof(Ecoponto) * (totalRegistosIntroduzidos - 1));
			if (ecopontosTemp == NULL) {
				printf("Erro ao remover o ecoponto.");
			} else {
				// Copia os ecopontos para o array temporario, menos o ecoponto que queremos apagar
				for (i = 0; i < totalRegistosIntroduzidos; i++) {
					if (i != posicaoArray) {
						ecopontosTemp[j] = ecopontos[i];
						j++;
					}
				}
				// Limpa o array antigo
				free(ecopontos);
				ecopontos = NULL;
				// Cria novamente o array
				ecopontos = (Ecoponto*) malloc(sizeof(Ecoponto) * maxRegistos);
				// Verifica se deu erro
				if (ecopontos == NULL) {
					respGuardarRegistos = guardarRegistos(ecopontosTemp, j);
					if (respGuardarRegistos == 1) {
						printf("Ocorreu um erro interno, por favor inicie denovo o programa e use a op��o de carregar os dados apartir de um arquivo.");
					} else {
						printf("Infelismente n�o conseguimos apagar o ecoponto e perdemos todos os seus registos :(.\n");
					}
				} else {
					// Copia os ecopontos do array temporario
					for (i = 0; i < j; i++) {
						ecopontos[i] = ecopontosTemp[i];
					}
					// Limpa o array temporario
					free(ecopontosTemp);
					ecopontosTemp = NULL;
					// Atualiza a v�rivel totalRegistosIntroduzidos
					totalRegistosIntroduzidos--;
					// Display de uma msg de sucesso
					printf("Ecoponto removido com sucesso.");
				}
			}
		}
	}
}

// Fun��o para calcular a m�dia dos res�duos de um ecoponto
// N�o recebe nem retorna nenhum valor
void calcMediaResiduos() {
    // Declara��o das variaveis
    float soma = 0, media;
    int i, contadorEcopontosTipo = 0, opcao;

    printf("Que tipo de res�duos pretende calcular a m�dia (1 - papel�o, 2 - vidr�o, 3 - ole�o): ");
    lerInteiro(&opcao);
    while (opcao < 1 || opcao > 3) {
        printf("Op��o inv�lida.");
        printf("Que tipo de res�duos pretende calcular a m�dia (1 - papel�o, 2 - vidr�o, 3 - ole�o): ");
        lerInteiro(&opcao);
    }

    // Percorre o array todo para calcular o total de registos existentes
    for(i = 0; i < totalRegistosIntroduzidos; i++) {
        if (ecopontos[i].tipo == opcao) {
            soma += ecopontos[i].capacidadeAtual;
            contadorEcopontosTipo++;
        }
    }

    media = soma / contadorEcopontosTipo;
    printf("A m�dia de res�duos dos ecopontos do tipo %s � %.2f", opcao == 1 ? "papel�o" : opcao == 2 ? "vidr�o" : "ole�o", media);
}

// Fun��o para listar/mostrar todos os ecopontos
// N�o recebe nem retorna nenhum valor
// Mostra o id de cada ecoponto, a capacidade atual, as coordenadas x e y, e o tipo do ecoponto
void listarEcopontos() {
    // Declara��o das variavel
	int i;
	
	for (i = 0; i < totalRegistosIntroduzidos; i++) {
		printf("ID: %d\n", ecopontos[i].id);
		printf("Capacidade atual: %.2f/%d\n", ecopontos[i].capacidadeAtual, quantidadeMaximaEcoponto);
		printf("Coordenadas: X %.2f, Y %.2f\n", ecopontos[i].coordenadas.x, ecopontos[i].coordenadas.y);	
        // Se o tipo for 1: Papel�o, se o tipo for 2: Vidr�o, se n�o o tipo � Ole�o
		printf("Tipo do ecoponto: %s\n\n", ecopontos[i].tipo == 1 ? "Papel�o" : ecopontos[i].tipo == 2 ? "Vidr�o" : "Ole�o");
	}
}

// Fun��o para listar/mostrar todos os ecopontos cheios
// N�o recebe nem retorna nenhum valor
// Mostra o id do ecoponto, as coordenadas x e y, e o tipo do ecoponto
void listarEcopontosCheios() {
    // Declara��o das variaveis
	int i, ecopontosCheios = 0;
	char res;
	Ecoponto* ecopontosCheiosArray;

    // Cria um array temp
	ecopontosCheiosArray = (Ecoponto*) malloc(totalRegistosIntroduzidos * sizeof(Ecoponto));

	if (ecopontosCheiosArray == NULL) {
		printf("Ocorreu um erro, por favor tenta mais tarde");
	} else {
		// Percorre o array todo e verificar quantos ecopontos est�o cheios;
		for (i = 0; i < totalRegistosIntroduzidos; i++) {
			if (ecopontos[i].capacidadeAtual >= quantidadeMaximaEcoponto) {
				ecopontosCheiosArray[ecopontosCheios] = ecopontos[i];
				ecopontosCheios++;
			}
		}

		if (ecopontosCheios == 0) {
			printf("N�o existe nenhum ecoponto cheio na rede.\n");
		} else {
			printf("Existem %d ecopontos cheios na rede.\n", ecopontosCheios);
			printf("Deseja listar os ecopontos cheios [s/S]: ");
			scanf(" %c", &res); getchar();
			if(res != 's' && res != 'S') {
				printf("A cancelar...");
			} else {
				printf("\nDados dos ecopontos cheios: \n\n");
				for (i = 0; i < ecopontosCheios; i++) {
					printf("Id %d\n", ecopontosCheiosArray[i].id);
					printf("Coordenadas: X %.2f, Y %.2f\n", ecopontosCheiosArray[i].coordenadas.x, ecopontosCheiosArray[i].coordenadas.y);	
					printf("Tipo do ecoponto: %s\n\n", ecopontosCheiosArray[i].tipo == 1 ? "Papel�o" : ecopontosCheiosArray[i].tipo == 2 ? "Vidr�o" : "Ole�o");	
				}
			}
		}
	}

	// Limpa o ponteiro
	free(ecopontosCheiosArray);
	ecopontosCheiosArray = NULL;
}

// Fun��o para listar os ecopontos de um tipo espec�fico
// Recebe o tipo do ecoponto e n�o retorna nenhum valor
// Mostra o id do ecoponto, as coordenadas x e y, e capacidade atual do ecoponto
void listartEcopontosTipo(int tipo) {
    // Declara��o das variaveis
	int i, ecopontosTipo = 0;
	char res;
	char* tipoEcoponto;
	Ecoponto* ecopontosTipoArray;

	// Converte o tipo do ecoponto que � numero para string
	tipoEcoponto = tipo == 1 ? "papel�o" : tipo == 2 ? "vidr�o" : "ole�o";

    // Cria um array temp
	ecopontosTipoArray = (Ecoponto*) malloc(totalRegistosIntroduzidos * sizeof(Ecoponto));

	if (ecopontosTipoArray == NULL) {
		printf("Ocorreu um erro, por favor tente mais tarde");
	} else {
		// procurar pelos ecopontos do tipo fornecido
		for(i = 0; i < totalRegistosIntroduzidos; i++) {
			if (tipo == ecopontos[i].tipo) {
				ecopontosTipoArray[ecopontosTipo] = ecopontos[i];
				ecopontosTipo++;
			} 
		}

		if (ecopontosTipo == 0) {
			printf("N�o existe nenhum ecoponto com o tipo %s.", tipoEcoponto);
		} else {
			printf("Existem %d ecopontos do tipo %s.\n", ecopontosTipo, tipoEcoponto);
			printf("Deseja listar os ecopontos do tipo %s [s/S]: ", tipoEcoponto);
			scanf(" %c", &res); getchar();
			if(res != 's' && res != 'S') {
				printf("A cancelar...");
			} else {
				printf("Dados dos ecopontos do tipo %s.\n\n", tipoEcoponto);
				for(i = 0; i < ecopontosTipo; i++) {
					printf("ID: %d\n", ecopontosTipoArray[i].id);
					printf("Capacidade atual: %.2f/%d\n", ecopontosTipoArray[i].capacidadeAtual, quantidadeMaximaEcoponto);
					printf("Coordenadas: X %.2f, Y %.2f\n\n", ecopontosTipoArray[i].coordenadas.x, ecopontosTipoArray[i].coordenadas.y);
				}							
			}
		}
	}

	// Limpa o ponteiro
	free(ecopontosTipoArray);
	ecopontosTipoArray = NULL;
	for (i = 0; i != '\0'; i++) {
		free(&tipoEcoponto[i]);
	}
	tipoEcoponto= NULL;
}

// Fun��o para salvar os ecopontos no arquivo chamado "ecopontos.dat" ( Ficheiro Bin�rio )
// Recebe um array do tipo Ecoponto e o tamanho do mesmo
// Est� fun��o retorna varios valores, dos quais s�o:
// 1 - sucesso
// 0 - 'erro' ao abrir o arquivo
// -1 - 'erro' ao escrever os dados no arquivo
int guardarRegistos(Ecoponto ecopontoToSave[], int tamanho) {
    // Declara��o das variaveis
	int statusCode = 1, i;
	Ecoponto ecopontoTemp;
	FILE *fp;

    // Abre o arquivo apenas com permiss�o de escrever
	fp = fopen("ecopontos.dat", "w+");

	// Verifica se foi possivel abrir o arquivo
	if (fp == NULL) {
		statusCode = 0;
	} else {
		// Adiciona os ecopontos ao arquivo
		for (i = 0; i < tamanho; i++) {
			ecopontoTemp = ecopontoToSave[i];
			fwrite(&ecopontoTemp, sizeof(Ecoponto), 1, fp);
		}

		// Verifica se foi possivel escrever os dados no arquivo
		if (fwrite == 0) {
			statusCode = -1;
		}
	}

	// Fecha o arquivo
	fclose(fp);

	// Retorna o status 
	return statusCode;
}

// Fun��o para carregar os ecpontos do "ecopontos.dat" para a mem�ria
// Est� fun��o tem varios returns, dos quais s�o:
// 1 - sucesso
// 0 - 'erro' ao abrir o arquivo
// -1 - 'erro' ao carregar os dados para o arquivo
// -2 - 'erro' ao alocar a mem�ria para salvar mais registos
int carregarRegistos() {
    // Declara��o das variaveis
	int statusCode = 1, res;
	Ecoponto ecopontoTemp;
	FILE *fp;

    // Abre o arquivo apenas com permiss�o de ler
	fp = fopen("ecopontos.dat", "r");

	// Verifica se foi possivel abrir o arquivo
	if (fp == NULL) {
		statusCode = 0;
	} else {
		// Limpa a tabela para receber os novos registos
		free(ecopontos);
		ecopontos = NULL;
		// Reseta o total de registos e o maximo de registos
		totalRegistosIntroduzidos = 0;
		maxRegistos = 0;
		// Adiciona 20 posi��es ao array de ecopontos
		res = aumentarMaxRegistos();
		
		if (res == 1) {
			while(fread(&ecopontoTemp, sizeof(Ecoponto), 1, fp) || res != 1) {
        		ecopontos[totalRegistosIntroduzidos] = ecopontoTemp;
				idProximoCliente = ecopontoTemp.id + 1;
				totalRegistosIntroduzidos++;

				// Verificar se � preciso adicionar mais registos
				if (totalRegistosIntroduzidos == maxRegistos) {
					res = aumentarMaxRegistos();
					if (res != 1) {
						statusCode = 2;
					}
				}
			}
		} else {
			statusCode = -2;
		}
	}

	// Fecha o arquivo
	fclose(fp);

	// Retorna o status 
	return statusCode;
}

// Fun��o para calcular a rota mais eficiente
// N�o recebe nem retorna nenhum valor
// Na fun��o � perguntado o ponto de partida do utilizador e a percentagem dos ecopontos que ele pertende recolher
// Depois usa a logica do vizinho mais proximo para calcular a rota mais efeciente
// No final � mostrada a rota mais eficiente num arquivo chamado "rota.txt"
// Se tiver dado algum erro a salvar no arquivo � possivel mostrar no ecr� a rota
void calcRota() {
    // Declara��o das variaveis
	FILE *fp;
	int i, j, contadorVerticesPassados = 0, status = 1, vizinhoProximo = 0 , k, totalCoordenadas = 0;
	int* caminhoAPercorrer;
	Coordenadas coordenadaPartida, coordenadasTemp;
	Coordenadas* coordenadasAPerrcorrer;
	float** distancia;
	float km, distanciaVizinhoProximo, percentagemEcopontos, percentagemEcoponto;
	bool* verticesRegistados;
	bool isInArray;
	char resposta;
	float distanciaTotal = 0, ultimaDistancia;

	// Aloca mem�ria para a matriz
	distancia = (float**) malloc(sizeof(float) * (totalRegistosIntroduzidos + 1));
	if (distancia == NULL) {
		printf("N�o foi possivel alocar recursos para calcular o caminho.\n");
	} else {
		// Aloca a memoria para cada coluna da matriz
		for (i = 0; i < totalRegistosIntroduzidos + 1 || status != 1; i++) {
			distancia[i] = (float*) malloc(sizeof(float) * (totalRegistosIntroduzidos + 1));
			if (distancia[i] == NULL) {
				printf("N�o foi possivel alocar recursos para calcular o caminho.\n");
				status = 0;
			}
		}

		if (status = 0) {
			printf("N�o foi possivel calcular o caminho.\n");
		} else {
			// Aloca a memoria para o vetor de vertices registados
			verticesRegistados = (bool*) malloc(sizeof(bool) * (totalRegistosIntroduzidos + 1));
			if (verticesRegistados == NULL) {
				printf("N�o foi possivel alocar recursos para calcular o caminho.\n");
			} else {
				// Aloca a memoria para o vetor de caminho com os pontos
				caminhoAPercorrer = (int*) malloc(sizeof(int) * (totalRegistosIntroduzidos + 1));
				if (caminhoAPercorrer == NULL) {
					printf("N�o foi possivel alocar recursos para calcular o caminho.\n");
				} else {
					// Aloca a memoria para o vetor de todas as coordenadas que ele tem de passar
					coordenadasAPerrcorrer = (Coordenadas*) malloc(sizeof(Coordenadas) * (totalRegistosIntroduzidos + 1));
					if (coordenadasAPerrcorrer == NULL) {
						printf("N�o foi possivel alocar recursos para calcular o caminho.\n");
					} else {
						// Pergunta as coordenadas de partida
						printf("De onde vai sair?\n");
						printf("Qual � a coordenada x: ");
						lerFloat(&coordenadaPartida.x);
						while (coordenadaPartida.x < 0 || coordenadaPartida.x > 1000) {
							printf("Coordenada inv�lida, por favor introduza uma coordenada x entre 0 e 1000.\n");
							printf("Qual � a coordenada x: ");
							lerFloat(&coordenadaPartida.x);
						}

						printf("Qual � a coordenada y: ");
						lerFloat(&coordenadaPartida.y);
						while(coordenadaPartida.y < 0 || coordenadaPartida.y > 1000) {
							printf("Coordenada inv�lida, por favor introduza uma coordenada y entre 0 e 1000.\n");
							printf("Qual � a coordenada y: ");
							lerFloat(&coordenadaPartida.y);
						}

						printf("Quer recolher os ecopontos com quanta percentagem de carga: ");
						lerFloat(&percentagemEcopontos);
						while (percentagemEcopontos < 0 || percentagemEcopontos > 100) {
							printf("Percentagem inv�lida, por favor introduza uma percentagem entre 0 e 100.\n");
							printf("Quer recolher os ecopontos com quanta percentagem de carga: ");
							lerFloat(&percentagemEcopontos);
						}
						
						coordenadasAPerrcorrer[totalCoordenadas] = coordenadaPartida;
						totalCoordenadas++;

						// Percorre todos os ecopontos e verificar quais est�o com capacidade de carga superior a percentagemEcopontos
						// Os que tiverem, nos adicionamos as coordenadas deles ao array de coordenadas a percorrer
						for (i = 0; i < totalRegistosIntroduzidos; i++) {
							percentagemEcoponto = (ecopontos[i].capacidadeAtual * 100) / quantidadeMaximaEcoponto;
							if (percentagemEcoponto >= percentagemEcopontos) {
								coordenadasTemp = ecopontos[i].coordenadas;
								isInArray = false;
								for (j = 0; j < totalCoordenadas; j++) {
									if (coordenadasTemp.x == coordenadasAPerrcorrer[j].x && coordenadasTemp.y == coordenadasAPerrcorrer[j].y){
										isInArray = true;
										j = totalCoordenadas;
									}
								}
								if (!isInArray) {
									coordenadasAPerrcorrer[totalCoordenadas] = coordenadasTemp;
									totalCoordenadas++;
								}
							}
						}

						// Verifica se existe mais alguma coordenada para alem da inicial
						if (totalCoordenadas == 1) {
							printf("N�o existe nenhum ecoponto com essa percentagem ou superior.\n");
						} else {
							for (i = 0; i < totalCoordenadas; i++) {
								verticesRegistados[i] = false;  
								caminhoAPercorrer[i] = -1;
							}
							
							for(i = 0; i < totalCoordenadas; i++) {
								for(j = 0; j < totalCoordenadas; j++) {
									distancia[i][j] = ((coordenadasAPerrcorrer[j].x - coordenadasAPerrcorrer[i].x) * (coordenadasAPerrcorrer[j].x - coordenadasAPerrcorrer[i].x)) + 
													((coordenadasAPerrcorrer[j].y - coordenadasAPerrcorrer[i].y) * (coordenadasAPerrcorrer[j].y - coordenadasAPerrcorrer[i].y));  
									distancia[i][j] = sqrt(distancia[i][j]);
								}
							}
							
							i = 0;
							caminhoAPercorrer[0] = i;
							
							for(k = 0; k < totalCoordenadas -1; k++) {
								int min= INT_MAX;
								i = vizinhoProximo;
								for(j = 0; j < totalCoordenadas; j++) {
									// Valor do I vai ser o nosso segundo ponto onde ficou
									// Descobre a menor distancia do segundo ponto para os outros, mas sem voltar para o primeiro
									if((distancia[i][j] < min) && verticesRegistados[j] == false && i != j) {
										distanciaVizinhoProximo = distancia[i][j];
										vizinhoProximo = j;
										min = distancia[i][j];
									}
								}
								distanciaTotal = distanciaVizinhoProximo + distanciaTotal;
								contadorVerticesPassados++;
								caminhoAPercorrer[contadorVerticesPassados] = vizinhoProximo;
								verticesRegistados[i] = true;
								verticesRegistados[vizinhoProximo] = true;
							}
							
							ultimaDistancia = ((coordenadaPartida.x - coordenadasAPerrcorrer[caminhoAPercorrer[totalCoordenadas-1]].x) * (coordenadaPartida.x - coordenadasAPerrcorrer[caminhoAPercorrer[totalCoordenadas-1]].x)) + 
													((coordenadaPartida.y - coordenadasAPerrcorrer[caminhoAPercorrer[totalCoordenadas-1]].y) * (coordenadaPartida.y - coordenadasAPerrcorrer[caminhoAPercorrer[totalCoordenadas-1]].y));  
							ultimaDistancia = sqrt(ultimaDistancia);
							distanciaTotal = distanciaTotal + ultimaDistancia;
							
							
							fp = fopen("caminho.txt", "w+");
							if (fp == NULL) {
								printf("N�o conseguimos guardar o caminho em um arquivo, quer ver no ecr� [s/S]: ");
								scanf(" %c", &resposta); getchar();
								if (resposta == 's' || resposta == 'S') {
									printf("Coordenadas que deve seguir: \n\n");
									for (i = 1; i < totalCoordenadas; i++) {
										printf("%d - x: %.2f; y: %.2f\n", i, coordenadasAPerrcorrer[caminhoAPercorrer[i]].x, coordenadasAPerrcorrer[caminhoAPercorrer[i]].y);
									}
									printf("Coordenadas iniciais, x: %.2f; y: %.2f\n", coordenadasAPerrcorrer[0].x, coordenadasAPerrcorrer[0].y);
									printf("\nDistancia total a percorrer : %.2f\n", distanciaTotal);
								} else {
									printf("A cancelar ...");
								}
							} else {
								fprintf(fp, "Coordenadas que deve seguir: \n\n");
								for(i = 0; i < totalCoordenadas-1; i++) {
									fprintf(fp, "%d - x: %.2f; y: %.2f\n", i+1, coordenadasAPerrcorrer[caminhoAPercorrer[i+1]].x, coordenadasAPerrcorrer[caminhoAPercorrer[i+1]].y);
								}
								fprintf(fp, "Coordenadas iniciais, x: %.2f; y: %.2f\n", coordenadasAPerrcorrer[0].x, coordenadasAPerrcorrer[0].y);
								fprintf(fp, "\nDistancia total a percorrer : %.2f\n", distanciaTotal);
								printf("Caminho guardado com sucesso no arquivo caminho.txt\n");
							}
							fclose(fp);
						}
					}		
				}
			}
		}
	}
	
	// Limpa os ponteiros
	free(coordenadasAPerrcorrer); coordenadasAPerrcorrer = NULL;
	free(caminhoAPercorrer); caminhoAPercorrer = NULL;
	free(verticesRegistados); verticesRegistados = NULL;
	for (i = 0; i < totalRegistosIntroduzidos + 1; i++) {
			free(distancia[i]);
	} 
    free(distancia);
	distancia = NULL;
}

