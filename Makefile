main: main.c functions.o
	gcc main.c functions.o -o campo -W -gcc

objeto: functions.c
	gcc -c functions.c -W -g
