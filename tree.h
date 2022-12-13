#include <sqlite3.h>
#define GRAU 6

typedef struct tipo_no {
	int codigo;
    int treino;
    char pergunta[100];
    struct tipo_no *sube;
    struct tipo_no *subd;
} tipo_no;

tipo_no *raiz;
sqlite3 *db;
sqlite3_stmt *stmt;

const char* carrega(tipo_no **p,int *respostas);