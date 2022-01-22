// Declaração das estruturas
typedef struct {
	float x;
	float y;
} Coordenadas;

typedef struct {
	int id;
	int tipo; // 1 - papelão, 2 - vidrão, 3 - oleão
	float capacidadeAtual;
	Coordenadas coordenadas;
} Ecoponto;
