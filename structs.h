// Declara��o das estruturas
typedef struct {
	float x;
	float y;
} Coordenadas;

typedef struct {
	int id;
	int tipo; // 1 - papel�o, 2 - vidr�o, 3 - ole�o
	float capacidadeAtual;
	Coordenadas coordenadas;
} Ecoponto;
