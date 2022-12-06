#include <stdio.h>
#include <stdlib.h>
#include "sqlite-amalgamation-3400000\sqlite3.h"

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
/*
int main(){
	select_perguntas();
	return 0;
}
*/
