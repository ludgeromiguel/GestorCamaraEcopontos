#ifndef STRUCT_H
#define STRUCT_H
#include "structs.h"

// Declaração das funções
void lerInteiro(int *n); 				 // Função para ler números inteiros
void lerFloat(float *n); 				 // Função para ler números reais
int aumentarMaxRegistos();               // Aumenta o maximo de registos que o utilizador pode introduzir (mais 25)
void menuPrincipal();					 // Menu principal
void menuAdicionar();				     // Sub-menu para Adicionar
void menuProcurar();                     // Sub-menu para mostrar os varios tipos de pesquisa
void adicionarEco(); 			 	     // Adiciona ecoponto
void adicionarResiduos();				 // Adiciona resíduos ao ecoponto
void limparEco();						 // Remover os resíduos do ecoponto
void editarEco();						 // Edita 'localizacao' do ecoponto
void editarEcoTipo(int posicaoArray);    // Editar o tipo do ecoponto
void editarCoordenadas(int posicaoArray); // Editar as coordenadas do ecoponto
void removerEco();					  	 // Remove um ecoponto
int procuraEcoponto(int inicio, int fim, int idProcura);			// Procurar um ecoponto pelo seu id
void calcRota();						 // Calcula a rota da recolha de resíduos
void menuListar();						 // Menu para listar;
void listarEcopontos();
void listarEcopontosCheios();			 // os cheios, nivel residuo médio de um dado tipo, etc
void calcMediaResiduos();				 // Calcula a média dos resíduos dos ecopontos
void listartEcopontosTipo(int tipo); // Lista os ecompontos de x tipo
int guardarRegistos(Ecoponto ecopontoToSave[], int tamanho); // Guarda os registos
int carregarRegistos();					 // Lê os registos do ficheiro

#endif
