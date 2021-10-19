#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pwd.h>
#include <unistd.h>
#include <ctype.h>
#include <malloc.h>

typedef struct {
    char CRE[7];
    char CRM[7];
    char name[60];
    char *user_name;
    char *federal_state;
    char *municipio;
    char *sus_unity;
    char *password;
    char *type;
}doctor_nurse;

static int get_mode();
void banner();

int main(void) {
   float we = 1.23;
   float um = 1.00;

   printf("%.2f", um * we);
}

void banner() {
    printf("\n\n\n");
	printf(" -------             -------     ________________________________\n");
	printf("|         |       | |           |                                |\n");
	printf("|         |       | |           | Bem vindo ao susC-1.0,software |\n");
	printf(" -------  |       |  -------    | para registrar  pacientes  com |\n");
	printf("        | |       |         |   | sintomas de COVID-19.Por favor |\n");
	printf("        | |       |         |   | efetue seu cadastro no sistema |\n");
	printf(" -------   -------   -------    |________________________________|\n");
	printf("\n\n\n");
}

static int get_mode(){
	char *mode;
	mode = (char *)malloc(sizeof(char));
    if(mode)
    {
    	int *compare_mode = (int *) malloc(sizeof(int));
        if(compare_mode)
        {
            do
            {

                printf("Aperte 0 para se cadastrar, ou 1 para efetuar login: ");
                scanf("%s", mode);
                printf("\n");
                *compare_mode = strcmp(mode, "0") == 0 || strcmp(mode, "1") == 0 ? 1 : 0;

            }while(*compare_mode == 0 );
        }
    }

	return strcmp(mode, "0") == 0 ? 1 : 0;
}

//clang -ggdb3 -O0 -std=c11 -Wall -Werror -Wextra -Wno-sign-compare -Wno-unused-parameter -Wno-unused-variable -Wshadow    main.c  -lcrypt -lcs50 -lm -o run