#ifndef STRUCT_H
#define STRUCT_H
#include "structs.h"

// Declara��o das fun��es
void lerInteiro(int *n); 				 // Fun��o para ler n�meros inteiros
void lerFloat(float *n); 				 // Fun��o para ler n�meros reais
int aumentarMaxRegistos();               // Aumenta o maximo de registos que o utilizador pode introduzir (mais 25)
void menuPrincipal();					 // Menu principal
void menuAdicionar();				     // Sub-menu para Adicionar
void menuProcurar();                     // Sub-menu para mostrar os varios tipos de pesquisa
void adicionarEco(); 			 	     // Adiciona ecoponto
void adicionarResiduos();				 // Adiciona res�duos ao ecoponto
void limparEco();						 // Remover os res�duos do ecoponto
void editarEco();						 // Edita 'localizacao' do ecoponto
void editarEcoTipo(int posicaoArray);    // Editar o tipo do ecoponto
void editarCoordenadas(int posicaoArray); // Editar as coordenadas do ecoponto
void removerEco();					  	 // Remove um ecoponto
int procuraEcoponto(int inicio, int fim, int idProcura);			// Procurar um ecoponto pelo seu id
void calcRota();						 // Calcula a rota da recolha de res�duos
void menuListar();						 // Menu para listar;
void listarEcopontos();
void listarEcopontosCheios();			 // os cheios, nivel residuo m�dio de um dado tipo, etc
void calcMediaResiduos();				 // Calcula a m�dia dos res�duos dos ecopontos
void listartEcopontosTipo(int tipo); // Lista os ecompontos de x tipo
int guardarRegistos(Ecoponto ecopontoToSave[], int tamanho); // Guarda os registos
int carregarRegistos();					 // L� os registos do ficheiro

#endif
