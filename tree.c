#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>
#include "sqlite-amalgamation-3400000\sqlite3.h"

#define GRAU 6

typedef struct tipo_no {
    int *treino;
    int nro_repostas;
    struct tipo_no *aponta[GRAU+1];
} tipo_no;

tipo_no *raiz;
sqlite3 *db;
sqlite3_stmt *stmt;
sqlite3_stmt *stmtaux;

void print_col_value(sqlite3_stmt* stmt, int col) {

  	int colType = sqlite3_column_type(stmt, col);

	switch(colType){

		case SQLITE_INTEGER:
	         printf("%3d", sqlite3_column_int(stmt, col));
	         break;
	
	    case SQLITE_FLOAT:
	         printf("%5.2f", sqlite3_column_double(stmt, col));
	         break;
	
	    case SQLITE_TEXT:
	         printf("%-5s", sqlite3_column_text(stmt, col));
	         break;
	
	    case SQLITE_NULL:
	         printf("null");
	         break;
	
	    case SQLITE_BLOB:
	         printf("blob");
	         break;
	}
}

int abre_db(){
	int saida = 0;
	
	saida = sqlite3_open("workout_guru.db", &db);
	
	if (saida){
		printf("NAO FOI POSSIVEL CONECTAR AO BANCO: %s\n", sqlite3_errmsg(db));
		return 0;
	}
	printf("CONECTADO AO BANCO.\n");	
}

void fecha_db(){	    
    sqlite3_finalize(stmt);
    sqlite3_close(db);	
}

void select_perguntas(){
    if (sqlite3_prepare_v2(db, "SELECT Q FROM PERGUNTAS", -1, &stmt, NULL)){
       printf("Erro ao executar o select.\n");
       sqlite3_close(db);
       exit(-1);
    }	
}

int printa_perguntas(){
	if (sqlite3_step(stmt) != SQLITE_DONE){
     	printf("\n");
        print_col_value(stmt, 0);
        return 1;
    }
    else
    	return 0;
}

int get_recordcount(){
	if (sqlite3_prepare_v2(db, "SELECT COUNT(Q) FROM PERGUNTAS", -1, &stmt, NULL)){
       printf("Erro ao executar o select.\n");
       sqlite3_close(db);
       return -1;
    }
	else{
		sqlite3_step(stmt);
		return sqlite3_column_int(stmt, 0);	
	}	
}

int sql_possibleanswers(){
	if (sqlite3_prepare_v2(db, "SELECT QTDANSWERS FROM PERGUNTAS", -1, &stmtaux, NULL)){
       printf("Erro ao executar o select.\n");
       sqlite3_close(db);
       return 0;
    }
    else
    	return 1;
}

int get_possibleanswers(){
	if (sqlite3_step(stmtaux) != SQLITE_DONE)
		return sqlite3_column_int(stmtaux, 0);	
	else
		return -1;
}

void inicializaArvore(){
    raiz = malloc( sizeof( tipo_no ) );
    memset( raiz, 0, sizeof( tipo_no ) );
}

/*void inserir( const int chave ){
    int i;

    inserirRecursivo( NULL, raiz, chave );
}

void inserirChaveNaFolha( tipo_no *folha, const int chave ){
    int i, j, posicao;

    posicao = folha->nro_chaves;
    if( folha->nro_chaves>0 ){
        for( i = 0; i < folha->nro_chaves; i++ ){
            if( chave < folha->chaves[i] ){
                posicao = i;
                for( j = folha->nro_chaves; j > i; j-- ){
                    folha->chaves[j] = folha->chaves[j-1];
                    folha->aponta[j+1] = folha->aponta[j];
                }
                break;
            }
        }
    }
    folha->chaves[posicao] = chave;
    folha->nro_chaves++;
}

void inserirRecursivo( tipo_no *paiRef, tipo_no *no, const int chave ){

    bool isFolha = ( no->aponta[0] == NULL );
    bool precisaDividir = false;
    bool achouPelaEsquerda = false;

    if( isFolha ){
        inserirChaveNaFolha( no, chave );
        precisaDividir = ( no->nro_chaves > MAX_ELEMENTOS );
        if( precisaDividir ){
            dividir( paiRef, no );
        }
        return;
    } else {
        int i;
        for(i = 0; i < no->nro_chaves; i++ ){
            if( chave < no->chaves[i] ){
                achouPelaEsquerda = true;
                inserirRecursivo( no, no->aponta[i], chave );
                precisaDividir = ( no->nro_chaves > MAX_ELEMENTOS );
                if(precisaDividir) dividir( paiRef, no );
                break;
            }
        }
        if( !achouPelaEsquerda ){
            int ultimo = no->nro_chaves;
            inserirRecursivo( no, no->aponta[ultimo], chave );
            precisaDividir = ( no->nro_chaves > MAX_ELEMENTOS );
            if( precisaDividir ) 
				dividir( paiRef, no );
        }
    }
}*/

tipo_no* novoNodo() {
    tipo_no *novo = malloc( sizeof( tipo_no ) );
    memset( novo, 0, sizeof( tipo_no ) );
    return novo;
}

void cria_arvore(tipo_no *no, sqlite3_stmt *stmts){
	int i;
	sqlite3_stmt *stmt1 = stmts;
	
	if(sqlite3_step(stmtaux) == SQLITE_ROW){
		no->nro_repostas = sqlite3_column_int(stmtaux,0);
		for(i = 0; i < no->nro_repostas; i++){
			no->aponta[i] = novoNodo();
			no->aponta[i]->treino = 0;
			cria_arvore(no->aponta[i],stmtaux);
		}
		//sqlite3_step(stmts);
		/*for (i = 0; i < no->nro_repostas; i++){
			cria_arvore(no->aponta[i],stmts);
		}*/
	}
	else{
	}		
}

void criar_treino(tipo_no *no){
	int answer, i, j, recordcount;
	
	abre_db();
	recordcount = get_recordcount();
	sql_possibleanswers();
	cria_arvore(no,stmtaux);
	select_perguntas();
	while(printa_perguntas()){
		answer = scanf("%i");	
	}
	
	fecha_db();	
}

void consultar_treino(){
	
}

void excluir_treino(){
	
}

char menu_workout(){
	char op;
	
	system("cls");
	
	printf("================================================\n");
	printf("|                 WORKOUT GURU                 |\n");
	printf("| [1] Criar treino                             |\n");
	printf("| [2] Consultar treinos                        |\n");
	printf("| [3] Excluir treino                           |\n");
	printf("| [0] Sair                                     |\n");
	printf("================================================\n");
	
	op = getche();
	
	switch(op){
		case '0':
			exit(0);
		case '1':
			criar_treino(raiz);
			break;
		case '2':
			consultar_treino();
			break;
		case '3':
			excluir_treino();
			break;
	}
}

void menu_db(){
	
}

void menu_principal(){
	char op;
	
	printf("\n");
	printf("================================================\n");
	printf("|                 WORKOUT GURU                 |\n");
	printf("| [1] Treinos                                  |\n");
	printf("| [2] Banco de dados [ADM]                     |\n");
	printf("| [0] Sair                                     |\n");
	printf("================================================\n");
	
	op = getche();
	
	switch(op){
		case '0':
			exit(0);
		case '1':
			menu_workout();
			break;
		case '2':
			menu_db();
	}
}


int main (void){
	setlocale(LC_ALL, "Portuguese");
	
	inicializaArvore();

	menu_principal();
	
	sleep(20);
	
	return 0;
}
