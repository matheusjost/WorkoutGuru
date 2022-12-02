#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>
#include "data.h"

#define GRAU 6

typedef struct tipo_no {
    int resposta;
    struct tipo_no *aponta[GRAU+1];
    int x, y;
} tipo_no;

tipo_no *raiz;

void inicializaArvore(){
    raiz = malloc( sizeof( tipo_no ) );
    memset( raiz, 0, sizeof( tipo_no ) );
}

void criar_treino(){
	char answer;
	
	abre_db();
	select_perguntas();
	while(printa_perguntas()){
		answer = getche();	
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
			criar_treino();
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

	menu_principal();
	
	sleep(20);
	
	return 0;
}
