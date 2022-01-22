#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#include "functions.c"  // Importa as fun��es para o c�digo 


// Fun��o principal (primeira a ser chamada quando o programa inicia)
int main() {
	int respostaAumentarRegistos;
	// Coloca o idioma do programa em portugu�s
	setlocale(LC_ALL, "Portuguese");

	// Chama a fun��o para aumentar o maximo de registos que pode introduzir
	respostaAumentarRegistos = aumentarMaxRegistos();
	// Verifica se n�o ocorreu nenhum erro a aumentar o maximo de registos
	if (respostaAumentarRegistos == 1) {
		// Chama a fun��o para mostrar o menu principal
		menuPrincipal();
	}
	else {
		printf("Ocorreu algum erro a iniciar o programa, por favor tente novamente mais tarde.\n");
	}
	return 0;
}

