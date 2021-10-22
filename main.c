#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pwd.h>
#include <unistd.h>
#include <ctype.h>
#include <malloc.h>

typedef struct 
{	
		char CRE[22];
		char CRM[22];
		char name[60];
		char nick_name[60];
		char estado[16];
		char municipio[30];
		char unidade_SUS[30];
		char senha[8];
		char type[10];

} Professional_health;

Professional_health user_register[100];

int main(void) {
   Professional_health *user = (Professional_health*) malloc(sizeof(Professional_health));
   if(user)
   {    
       printf("Digite seu nome: ");
       scanf("%s",user->name);
       printf("\n");
       user_register[0] = *user;
       free(user);   
   }

   printf("Seu nome no cadastro é: %s", user_register[0].name);

}

