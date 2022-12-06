#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>
#include "data.h"
#include "sqlite-amalgamation-3400000\sqlite3.h"

#define GRAU 6

typedef struct tipo_no {
    int *treino;
    struct tipo_no *aponta[GRAU+1];
} tipo_no;

tipo_no *raiz;

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

void cria_arvore(tipo_no *no){
	tipo_no *aux = no;
	
	for (i = 0; i < recordcount; i++){
		for(j = 0; j < get_possibleanswers(); j++){
			aux->aponta[j] = novoNodo();
			aux->aponta[j]->treino = NULL;
		}
	}
}

void criar_treino(tipo_no *no){
	int answer, i, j, recordcount;
	
	abre_db();
	recordcount = get_recordcount();
	sql_possibleanswers();
	cria_arvore(no);
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
