# Projeto de Estrutura de Dados

O WorkoutGuru seleciona treinos conforme a sua condição de entrada. Ao escolher entre as opções o WorkoutGuru irá escolher qual se adequa à sua realidade!

### RUN
Após instalar o GTK3.0 (preferencialmente em Ubuntu 21.04), execute o seguinte comando para compilar o arquivo do código:
```
gcc -rdynamic `pkg-config sqlite3 gtk+-3.0 --cflags` main.c tree.c -o WORKOUTGURU `pkg-config sqlite3 gtk+-3.0 --libs`
```
, então execute o WORKOUTGURU.