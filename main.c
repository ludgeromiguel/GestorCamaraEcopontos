#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#include "functions.c"  // Importa as funções para o código 


// Função principal (primeira a ser chamada quando o programa inicia)
int main() {
	int respostaAumentarRegistos;
	// Coloca o idioma do programa em português
	setlocale(LC_ALL, "Portuguese");

	// Chama a função para aumentar o maximo de registos que pode introduzir
	respostaAumentarRegistos = aumentarMaxRegistos();
	// Verifica se não ocorreu nenhum erro a aumentar o maximo de registos
	if (respostaAumentarRegistos == 1) {
		// Chama a função para mostrar o menu principal
		menuPrincipal();
	}
	else {
		printf("Ocorreu algum erro a iniciar o programa, por favor tente novamente mais tarde.\n");
	}
	return 0;
}

