#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>
#include <conio.h>
#include "db.h"

void first_menu(){
	char op;
	
	printf("================================================\n");
	printf("|                 WORKOUT GURU                 |\n");
	printf("| [1] Treinos                                  |\n");
	printf("| [2] Banco de dados [ADM]                     |\n");
	printf("| [0] Sair                                     |\n");
	printf("================================================\n");
	
	op = getche();
	system("cls");
	
	switch(op){
		case '0':
			exit(0);
		case '1':
			workout_menu();
			break;
		case '2':
			break;
	}
	
}

void workout_menu(){
	char op;
	
	printf("================================================\n");
	printf("|                 WORKOUT GURU                 |\n");
	printf("| [1] Consultar Treinos                        |\n");
	printf("| [2] Criar Treino                             |\n");
	printf("| [3] Excluir Treino                           |\n");
	printf("| [0] Voltar                                   |\n");
	printf("================================================\n");
	
	op = getche();
	system("cls");
	
	switch(op){
		case '0':
			exit(0);
		case '1':
			consultar_treino();
			break;
		case '2':
			criar_treino();
			break;
		case '3':
			excluir_treino();
			break;
	}
}

void criar_treino(){
	
}

void get_answers(){
	
}

int main (void){
	setlocale(LC_ALL, "Portuguese");

	first_menu();
	
	return 0;
}
