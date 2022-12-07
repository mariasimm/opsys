#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include "func.h"

struct map {
	char name[20];
	int* adress;
}map[20];

char assignV[20];
int valueV;

int actualSize = 0; //actual size of the map

int main(int argc, char const *argv[])
{
	extern char **environ;
	strcpy(map[0].name, "argc"); //adding new element to the map
	map[0].adress = &argc;
	actualSize++;

	if(argc == 1) {
		printf("\nEnvironment: ");
		while(**environ != NULL) {
			printf("%d", **environ);
			printf("\n");
			*environ += 1;
		}
		return 0;
	}

	const struct option long_opt[] = {
		{"help", 0, 0, 'h'},
		{"info", 1, 0, 'i'},
		{"set", 1, 0, 's'},
		{"assign", 1, 0, 'a'},
		{"value", 1, 0, 'v'},
		{"del", 1, 0, 'd'},
		{"clear", 1, 0, 'c'},
		{NULL, 0, NULL, 0}
	};//array of options

	int opt;
	strcpy(map[1].name, "opt");
	map[1].adress = &opt;
	actualSize++;

	int variable = 12;
	strcpy(map[2].name, "variable"); //adding new element to the map
	map[2].adress = &variable;
	actualSize++;

	int flA = 0, flV = 0;
	while((opt = getopt_long(argc, argv, "hi:s:a:v:d:c", long_opt, NULL)) != -1) {
	switch(opt) {
		case 'h': 
			help();
			break;
		case 'i': 
			info();
			break;
		case 's':
			printf("\n");
			char nameVar[20]; //name of variable
			char val[10]; //value of variable
			char nameWritten[30]; //what user entered
			strcpy(nameWritten, optarg);
			for(int i = 0; i < strlen(nameWritten); i++) {
				if(nameWritten[i] == '=') break;
				nameVar[i] = nameWritten[i];
			}
			for(int i = 0; i < strlen(nameWritten) - strlen(nameVar) - 1; i++) {
				val[i] = nameWritten[i + strlen(nameVar) + 1];
			}
			int fl = 0;
			for(int i = 0; i < actualSize; i++) {
				if(strcmp(map[i].name, nameVar) == 0) {
					*(map[i].adress) = atoi(val);
					printf("Now the value of variable: %d", *(map[i].adress));
					printf("\n");
					fl = 1;
				}
			}
			if(!fl) printf("There is no variable with such name!\n");
			break;
		case 'a':
			flA = 1;
			strcpy(assignV, optarg);
			break;
		case 'v':
			flV = 1;
			valueV = atoi(optarg);
			break;
		case 'd':
			del();
			break;
		case 'c':
			clear();
			break;
		}
	}
	if(flV && flA) AssignValue();
	else if(flV && !flA) value();
	else if (!flV && flA) assign();
	return 0;
}

void help(){
	printf("\n");
	printf("1) якщо програма запущена без опцій, то в стандартний потік виводу выводиться інформація о поточному оточенні\n");
	printf("2) якщо вказана коротка опція - h або довга -- help, то в стандартний потік виводу буде виведено інформацію по роботі із програмою\n");
	printf("3) якщо вказана коротка опція - i <змінна> або довга -- info <змінна>, то в стандартний потік выводу буде выведено значення вказаної змінної або повідомлення про те, що вказаної змінної в оточенні немає\n");
	printf("4) якщо вказана коротка опція - s <змінна=значення> або довга -- set <змінна=значення>, то вказана змінна оточення отримає нове значення та в стандартний потік виводу буде виведено встановлене значення вказаної змінної\n");
	printf("5) якщо вказані короткі опції - a <змінна> та - v <значення> або довгі -- assign <змінна> та -- value <значення>, то вказана змінна оточення отримає нове значення та в стандартний потік виводу буде виведено встановлене значення вказаної змінної; якщо значення не вказано, то буде присвоєно пустий рядок; якщо же не вказано змінну, то присвоєння не відбудається, а в стандартний потік помилок виводиться відповідне повідомлення\n");
	printf("6) якщо вказана коротка опція - d <змінна> або довга -- del <змінна>, то вказана змінна видаляєтья з оточення\n");
	printf("7) якщо вказана коротка опція - с або довга -- сlear, то програма повністю очищує оточення\n");
}

void info(){
	printf("\n");
	int fl = 0;
	for(int i = 0; i < actualSize; i++) {
		if(strcmp(map[i].name, optarg) == 0) {
			printf("The value of variable: %d", *(map[i].adress));
			printf("\n");
			fl = 1;
		}
	}
	if(!fl) printf("There is no variable with such name!\n");
}

void assign(){
	int fl = 0;
		for(int i = 0; i < actualSize; i++) {
			if(strcmp(map[i].name, assignV) == 0) {
				*(map[i].adress) = 0;
				printf("Now the value of variable: %d", *(map[i].adress));
				printf("\n");
				fl = 1;
			}
		}
	if(!fl) printf("There is no variable with such name!\n");
}

void value(){
	printf("\nYou didn't enter the variable!\n");
}

void AssignValue(){
	int fl = 0;
		for(int i = 0; i < actualSize; i++) {
			if(strcmp(map[i].name, assignV) == 0) {
				*(map[i].adress) = valueV;
				printf("Now the value of variable: %d", *(map[i].adress));
				printf("\n");
				fl = 1;
			}
		}
	if(!fl) printf("There is no variable with such name!\n");
}

void del(){
	printf("\n");
	int fl = 0;
	for(int i = 0; i < actualSize; i++) {
		if(strcmp(map[i].name, optarg) == 0) {
			int var = *(map[i].adress);
			map[i].adress = NULL;
			strcpy(map[i].name, "\0");
			printf("The variable with value %d was deleted", var);
			printf("\n");
			fl = 1;
		}
	}
	if(!fl) printf("There is no variable with such name!\n");
}

void clear(){
	for(int i = 0; i < actualSize; i++) {
		int var = *(map[i].adress);
		map[i].adress = NULL;
		strcpy(map[i].name, "\0");
		printf("The variable with value %d was deleted", var);
		printf("\n");
	}
	extern char **environ;
	while(**environ != NULL) {
		printf("The variable with value %d was deleted", **environ);
		printf("\n");
		*environ += 1;
	}
}
