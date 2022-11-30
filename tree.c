#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>
#include "data.h"

char menu_workout(){
	printf("================================================\n");
	printf("|                 WORKOUT GURU                 |\n");
	printf("| [1] TESTE                                    |\n");
	printf("| [2] Banco de dados [ADM]                     |\n");
	printf("| [0] Sair                                     |\n");
	printf("================================================\n");
	
	select_perguntas();
}

char clicou_treino(){
	return '1';
	
}

void menu_principal(){
	char op;
	
	printf("================================================\n");
	printf("|                 WORKOUT GURU                 |\n");
	printf("| [1] Treinos                                  |\n");
	printf("| [2] Banco de dados [ADM]                     |\n");
	printf("| [0] Sair                                     |\n");
	printf("================================================\n");
	
	op = clicou_treino();
	
	switch(op){
		case '0':
			exit(0);
		case '1':
			menu_workout();
			break;
		case '2':
			break;
	}
}

void get_perguntas(){
	
}

int main (void){
	setlocale(LC_ALL, "Portuguese");

	menu_principal();
	
	sleep(20);
	
	return 0;
}
