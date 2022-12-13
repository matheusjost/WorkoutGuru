#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>
#include <sqlite3.h>
#define GRAU 6

// estrutura para perguntas e treinos.
typedef struct tipo_no {
	int codigo;
    int treino;
    char pergunta[100];
    struct tipo_no *aponta[GRAU+1];
    int nro_chaves;
} tipo_no;

tipo_no *raiz;
sqlite3 *db; // variavel do banco de dados
sqlite3_stmt *stmt; // variavel do statement do banco de dados

void inicializa_arvore(tipo_no**p){
	// alocar memoria para iniciar a arvore
    *p = NULL;
} 

void insere_recursivo(tipo_no **p, int codigo, int treino, const char *pergunta){
	int i;
	// insere
	if((*p) == NULL)	{
		tipo_no *no = (tipo_no*) malloc(sizeof(tipo_no));
		strcpy(no->pergunta,pergunta);
		no->codigo = codigo;
		no->treino = treino;
		for(i=0;i<GRAU;i++)
			no->aponta[i] = NULL;
		no->nro_chaves = 0;
		*p = no;
	}
	else{
		for( i = 0; i < (*p)->nro_chaves; i++ ){
			if (codigo < (*p)->aponta[i]->codigo){
				insere_recursivo(&(*p)->aponta[i],codigo,treino,pergunta);
				return;	
			}
		}
		if (codigo < (*p)->codigo){
			insere_recursivo(&(*p)->aponta[(*p)->nro_chaves],codigo,treino,pergunta);	
			(*p)->nro_chaves++;
		}
	}
}

void inserir_dados(tipo_no **p){
	// abre conexão com o db.
	int saida = 0;
	saida = sqlite3_open("workout_guru.db", &db);
	if (saida){
		printf("NAO FOI POSSIVEL CONECTAR AO BANCO: %s\n", sqlite3_errmsg(db));
		exit(0);
	}
	//printf("CONECTADO AO BANCO.\n");
	
	// executa o sql para pegar as perguntas
	if (sqlite3_prepare_v2(db, "SELECT Q FROM PERGUNTAS ORDER BY SEQ", -1, &stmt, NULL)){
       printf("Erro ao executar o select.\n");
       sqlite3_close(db);
       exit(0);
    }
	sqlite3_step(stmt); // prox linha
	insere_recursivo(&(*p),43,0,(const char *)sqlite3_column_text(stmt,0)); // adiciona pergunta
	sqlite3_step(stmt);	// prox linha
	insere_recursivo(&(*p),7,0,(const char *)sqlite3_column_text(stmt,0)); // adiciona perguna
	insere_recursivo(&(*p),14,0,(const char *)sqlite3_column_text(stmt,0)); // adiciona pergunta
	insere_recursivo(&(*p),21,0,(const char *)sqlite3_column_text(stmt,0)); // adiciona pergunta
	insere_recursivo(&(*p),28,0,(const char *)sqlite3_column_text(stmt,0)); // adiciona pergunta
	insere_recursivo(&(*p),35,0,(const char *)sqlite3_column_text(stmt,0)); // adiciona pergunta
	insere_recursivo(&(*p),42,0,(const char *)sqlite3_column_text(stmt,0)); // adiciona pergunta
	sqlite3_step(stmt); // prox linha
	insere_recursivo(&(*p),3,0,(const char *)sqlite3_column_text(stmt,0)); // adiciona pergunta
	insere_recursivo(&(*p),6,0,(const char *)sqlite3_column_text(stmt,0)); // adiciona pergunta
	insere_recursivo(&(*p),10,0,(const char *)sqlite3_column_text(stmt,0)); // adiciona pergunta
	insere_recursivo(&(*p),13,0,(const char *)sqlite3_column_text(stmt,0)); // adiciona pergunta
	insere_recursivo(&(*p),17,0,(const char *)sqlite3_column_text(stmt,0)); // adiciona pergunta
	insere_recursivo(&(*p),20,0,(const char *)sqlite3_column_text(stmt,0)); // adiciona pergunta
	insere_recursivo(&(*p),24,0,(const char *)sqlite3_column_text(stmt,0)); // adiciona pergunta
	insere_recursivo(&(*p),27,0,(const char *)sqlite3_column_text(stmt,0)); // adiciona pergunta
	insere_recursivo(&(*p),31,0,(const char *)sqlite3_column_text(stmt,0)); // adiciona pergunta
	insere_recursivo(&(*p),34,0,(const char *)sqlite3_column_text(stmt,0)); // adiciona pergunta
	insere_recursivo(&(*p),38,0,(const char *)sqlite3_column_text(stmt,0)); // adiciona pergunta
	insere_recursivo(&(*p),41,0,(const char *)sqlite3_column_text(stmt,0)); // adiciona pergunta	
	
	insere_recursivo(&(*p),1,1,"");
	insere_recursivo(&(*p),2,2,"");
	insere_recursivo(&(*p),4,3,"");
	insere_recursivo(&(*p),5,4,"");
	insere_recursivo(&(*p),8,5,"");
	insere_recursivo(&(*p),9,6,"");
	insere_recursivo(&(*p),11,7,"");
	insere_recursivo(&(*p),12,8,"");
	insere_recursivo(&(*p),15,9,"");
	insere_recursivo(&(*p),16,10,"");
	insere_recursivo(&(*p),18,11,"");
	insere_recursivo(&(*p),19,12,"");
	insere_recursivo(&(*p),22,13,"");
	insere_recursivo(&(*p),23,14,"");
	insere_recursivo(&(*p),25,15,"");
	insere_recursivo(&(*p),26,16,"");
	insere_recursivo(&(*p),29,17,"");
	insere_recursivo(&(*p),30,18,"");
	insere_recursivo(&(*p),32,19,"");
	insere_recursivo(&(*p),33,20,"");
	insere_recursivo(&(*p),36,21,"");
	insere_recursivo(&(*p),37,22,"");
	insere_recursivo(&(*p),39,23,"");
	insere_recursivo(&(*p),40,24,"");	
	
	sqlite3_close(db);
}
int gera_treino(tipo_no *p, int *respostas, int i){
	// verifica se a arvore contem treino	
	if (p != NULL){
		if (p->treino != 0)
			return p->treino;
		else
			gera_treino	(p->aponta[respostas[i]],respostas,i+1);
	}	
}

const char* retorna_treino(tipo_no *p,int *respostas){
	int treino;
	// pega o sequencial do treino registrado no banco.
	treino = gera_treino(p,respostas,0);
	
	// abre conexão com o db.
	int saida = 0;
	saida = sqlite3_open("workout_guru.db", &db);
	if (saida){
		printf("NAO FOI POSSIVEL CONECTAR AO BANCO: %s\n", sqlite3_errmsg(db));
		exit(0);
	}
	//printf("CONECTADO AO BANCO.\n");
	
	// executa o sql.
	if (sqlite3_prepare_v2(db, "SELECT DESCRICAO FROM TREINOS WHERE SEQ=?", -1, &stmt, NULL)){
       printf("Erro ao executar o select.\n");
       sqlite3_close(db);
       exit(0);
    }
    //adiciona o valor no parametro
    sqlite3_bind_int(stmt,1,treino);
    // acha a proxima linha
	sqlite3_step(stmt);
	return (const char *)sqlite3_column_text(stmt,0);	// retorna o valor contido em texto.
}


const char* carrega(tipo_no **p,int *respostas){
	// função para ser chamada pela interface
	inicializa_arvore(&(*p)); // inicia a arvore
	inserir_dados(&(*p));
	return retorna_treino(*p,respostas); // retorna o treino definido
}