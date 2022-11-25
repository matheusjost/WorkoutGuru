#include <stdio.h>
#include <stdlib.h>
#include "sqlite-amalgamation-3400000\sqlite3.h"

int main(){
	sqlite3 *db;
	int exit = 0;
	
	exit = sqlite3_open("workout_guru.db", &db);
	
    return (0);
}
