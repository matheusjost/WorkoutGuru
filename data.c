#include <stdio.h>
#include <stdlib.h>
#include "sqlite-amalgamation-3400000\sqlite3.h"

void print_col_value(sqlite3_stmt* stmt, int col) {

  	int colType = sqlite3_column_type(stmt, col);

	switch(colType){

		case SQLITE_INTEGER:
	         printf("  %3d   ", sqlite3_column_int(stmt, col));
	         break;
	
	    case SQLITE_FLOAT:
	         printf("  %5.2f", sqlite3_column_double(stmt, col));
	         break;
	
	    case SQLITE_TEXT:
	         printf("  %-5s", sqlite3_column_text(stmt, col));
	         break;
	
	    case SQLITE_NULL:
	         printf("  null");
	         break;
	
	    case SQLITE_BLOB:
	         printf("  blob");
	         break;
	}
}

void select_perguntas(){
	sqlite3 *db;
	int saida = 0;
	
	saida = sqlite3_open("workout_guru.db", &db);
	
	if (saida){
		printf("NAO FOI POSSIVEL CONECTAR AO BANCO: %s\n", sqlite3_errmsg(db));
		exit(0);
	}
	printf("CONECTADO AO BANCO\n");
	
	sqlite3_stmt *stmt;
	
    if (sqlite3_prepare_v2(db, "SELECT * FROM PERGUNTAS", -1, &stmt, NULL)){
       printf("Error executing sql statement\n");
       sqlite3_close(db);
       exit(-1);
    }
	
    sqlite3_bind_int (stmt, 1, 2);
    
    if (sqlite3_step(stmt) != SQLITE_DONE){
     	int col;
		for (col=0; col<sqlite3_column_count(stmt); col++){
          print_col_value(stmt, col);
        }
        printf("\n");
    }
    
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}
/*
int main(){
	select_perguntas();
	return 0;
}
*/
