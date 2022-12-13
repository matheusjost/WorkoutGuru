#!bin/bash
gcc -rdynamic `pkg-config sqlite3 gtk+-3.0 --cflags` main.c tree.c -o WORKOUTGURU `pkg-config sqlite3 gtk+-3.0 --libs`
