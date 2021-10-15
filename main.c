#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pwd.h>
#include <unistd.h>
#include <ctype.h>
#include <malloc.h>

float *strongness_pass(char *str, float *pn)
{
    int i= 0;
	float n = 0;

    for (i = 0; i < strlen(str); i++)
    {
        if(str[i] == *"!" || str[i] == *"@" || str[i] == *"#" ||
		   str[i] == *"$" || str[i] == *"%" || str[i] == *"&" ||
		   str[i] == *"*" || str[i] == *"?" || str[i] == *"/" ||
		   str[i] == *"." || str[i] == *"," || str[i] == *":" ||
		   str[i] == *"_" || str[i] == *"+" || str[i] == *"-" ||
		   str[i] == *"=" || str[i] == *"^" || str[i] == *"~" ||
		   str[i] == *"`" || str[i] == *"´")
        {
            n++;
        }

		if(str[i] == *"0" || str[i] == *"1" || str[i] == *"2" || 
		   str[i] == *"3" || str[i] == *"4" || str[i] == *"5" || 
		   str[i] == *"6" || str[i] == *"7" || str[i] == *"8" || 
		   str[i] == *"9")
		{
			n += 0.25;
		}
    }

    *pn = n / 10;
	return 0;
}

struct Professional_health
{	
		char CRE[22];
		char CRM[22];
		char name[60];
		char estado[16];
		char municipio[30];
		char unidade_SUS[30];
		char senha[8];
		char type[10];

} cad_user[100];
int user_count = 0;


struct Pacient
{	
		char nome[22];
		int age;
		float height;
		float weight;
		char cns[40];
		char consult_data[11];
		int COVID_19;
		char last_week_contact[4];
} pacient_SUS[100];

int pacient_count = 0;


struct Professional_health logged_user;

static int banner() {
	printf(" -------             -------     ________________________________\n");
	printf("|         |       | |           |                                |\n");
	printf("|         |       | |           | Bem vindo ao susC-1.0,software |\n");
	printf(" -------  |       |  -------    | para registrar  pacientes  com |\n");
	printf("        | |       |         |   | sintomas de COVID-19.Por favor |\n");
	printf("        | |       |         |   | efetue seu cadastro no sistema |\n");
	printf(" -------   -------   -------    |________________________________|\n");
	printf("\n\n\n");

	return 0;
}


static int get_mode(){
	char mode;
	int compare_mode;

	do
	{
		memset(&mode, 0, sizeof(char));
		printf("Aperte 0 para se cadastrar, ou 1 para efetuar login: ");
		scanf("%s", &mode);
		printf("\n");
		compare_mode = strcmp(&mode, "0") == 0 || strcmp(&mode, "1") == 0 ? 0 : 1;

	}while(compare_mode != 0 );
	
	return strcmp(&mode, "0") == 0 ? 0 : 1;
}

//////////////////////////////////////    SIGNIN LOGIC    /////////////////////////////////////

static int sign_in()
{
	int to_compare;

	char user_conseil[3];
	char compare_pass[8];
	int confirm_datas;

	do{
	printf("|--------------- CADASTRAR USUÁRIO ---------------|\n\n");
		do{
			printf("Digite 'CRM' para médico ou 'CRE' para Enfermeiro: ");
			scanf("%s", user_conseil);
			printf("\n");
			to_compare = strcmp(user_conseil, "CRM") == 0 || strcmp(user_conseil, "CRE") == 0 ? 0 : 1;
		}while(to_compare != 0);



		if(strcmp(user_conseil, "CRM") == 0)
		{
			printf("Digite o seu CRM: ");
			scanf("%s", cad_user[user_count].CRM);
			printf("\n");
			strcpy(cad_user[user_count].type, "MÉDICO");

		}
		else
		{
			printf("Digite o seu CRE: ");
			scanf("%s", cad_user[user_count].CRE);
			printf("\n");
			strcpy(cad_user[user_count].type, "ENFERMEIRO");
		}




		printf("Cadastre o seu nome de usuário: ");
		scanf("%s", cad_user[user_count].name);
		printf("\n");
		//printf("%s", cad_user[user_count].name);

		do{
			printf("Qual o estado onde você trabalha(Utilize a forma abreviada 'DF')? ");
			scanf("%s", cad_user[user_count].estado);
			printf("\n");
		}while(strlen(cad_user[user_count].estado) != 2);

		printf("Qual o município onde você trabalha? ");
		scanf("%s", cad_user[user_count].municipio);
		printf("\n");

		printf("Qual sua unidade de saúde? ");
		scanf("%s", cad_user[user_count].unidade_SUS);

		printf("\n");
		printf("          ___________________________________________\n");
		printf("         |   _____________________________________   |\n");
		printf("         |  |                                     |  |\n");
		printf("         |  | ATENÇÃO !! Cadastre uma senha forte |  |\n");
		printf("         |  | com  no   mínimo  8  caracteres ,   |  |\n");
		printf("         |  | constando  dentre eles  números  e  |  |\n");
		printf("         |  | caracteres especiais !!!!!          |  |\n");
		printf("         |  |_____________________________________|  |\n");
		printf("         |___________________________________________|\n");

		printf("\n");


		//LOGIC TO COMPARE AND ASSINGMENT THE PASSWORD
		do{
			float strong_ix = 0;

			strcpy(cad_user[user_count].senha, getpass("Cadastre sua senha: "));
			printf("\n");

			strongness_pass(cad_user[user_count].senha, &strong_ix);

				strcpy(compare_pass, getpass("Confirme sua senha: "));
				printf("\n");

				
			if(strong_ix > 0.325)
			{
					if(strncmp(cad_user[user_count].senha, compare_pass, 8) == 0)
					{
						to_compare = 0;
						printf("          ___________________________________________\n");
						printf("         |                                           |\n");
						printf("         |             Senha correta!                |\n");
						printf("         |___________________________________________|\n");
					}
					else
					{
						to_compare = 1;
						printf("          ___________________________________________\n");
						printf("         |                                           |\n");
						printf("         |      Senha inválida, tente novamente      |\n");
						printf("         |___________________________________________|\n");
					}
			}
			else
			{
				printf("Cadastre uma senha mais forte!");
				printf("\n");
				printf("Dica: Coloque 4 caracteres especiais e pelo menos 1 número");

				to_compare = 1;
			}
			printf("\n");

		}while(to_compare == 1);
		
			char confirm_type_char;
	
				printf("NOME: %s\n", cad_user[user_count].name);
				if(strcmp(user_conseil, "CRM") == 0)
				{
					printf("O seu CRM é: %s", cad_user[user_count].CRM);
					printf("\n");
					printf("Você é um: %s",cad_user[user_count].type);
					printf("\n");
				}
				else
				{
					printf("O seu seu CRE é: %s", cad_user[user_count].CRE);
					printf("\n");
					printf("Você é um : %s",cad_user[user_count].type);
					printf("\n");
				}

				printf("ESTADO: %s\n", cad_user[user_count].estado);
				printf("MUNICIPIO: %s\n", cad_user[user_count].municipio);
				printf("UNIDADE DE SAÚDE: %s\n", cad_user[user_count].unidade_SUS);
				printf("\n");

			do{
				printf("Os seus dados estão corretos? Digite y/n -> ");
				scanf("%s", &confirm_type_char);
				printf("\n");

				confirm_datas = strcmp(&confirm_type_char, "y") == 0 || strcmp(&confirm_type_char, "n") == 0 ? 0 : 1;

			}while(confirm_datas == 1);

			confirm_datas = strcmp(&confirm_type_char, "y") == 0 ? 0 : 1;

	}while(confirm_datas == 1);

	user_count++;
	return 0;	
}



///////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////    LOGIN LOGIC    /////////////////////////////////////
int log_in(int *user_id)
{	
	char user_name[60];
	char user_password[8];

	int user_name_in_DB;
	int user_password_correct;

	int user_to_compare_password;

	printf("|------------------------ LOGIN ------------------------|\n\n");
	do{
		printf("Nome de usuário: ");
		scanf("%s", user_name);
		printf("\n");

		for(int i = 0; i < user_count; i++)
		{
			if(strcmp(user_name, cad_user[i].name) == 0)
			{	
				user_name_in_DB = 0;
				user_to_compare_password = i;
			}
		}
		if(user_name_in_DB == 1)
		{
			printf("          ___________________________________________\n");
			printf("         |                                           |\n");
			printf("         | Usuário não  encontrado, tente novamente! |\n");
			printf("         |___________________________________________|\n\n");
		}

	}while(user_name_in_DB == 1);

	do{
		strcpy(user_password, getpass("Senha: "));
		printf("\n");

		if(strcmp(user_password, cad_user[user_to_compare_password].senha) == 0)
		{
			user_password_correct = 0;
			printf("          ___________________________________________\n");
			printf("         |                                           |\n");
			printf("         |        Login efetuado com sucesso!        |\n");
			printf("         |___________________________________________|\n\n");
		}
		else
		{
			user_password_correct = 1;
			printf("          ___________________________________________\n");
			printf("         |                                           |\n");
			printf("         |     Senha incorreta, tente novamente!     |\n");
			printf("         |___________________________________________|\n\n");
		}
	}while(user_password_correct == 1);

	user_id = &user_to_compare_password;
	return user_password_correct == 0 ? 2 : 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////    CADASTRAR PACIENTE   /////////////////////////////////

int cadastrar_paciente() 
{
	printf("|------------------ CADASTRAR PACIENTE -----------------|\n\n");
	
	printf("Nome: ");
	scanf("%s", pacient_SUS[pacient_count].nome);
	printf("\n");

	printf("Idade: ");
	scanf("%d", &pacient_SUS[pacient_count].age);
	printf("\n");

	printf("CNS (Cartão Nacional de Saúde): ");
	scanf("%s", pacient_SUS[pacient_count].cns);
	printf("\n");

		printf("Altura em metros: ");
		scanf("%f", &pacient_SUS[pacient_count].height);
		printf("\n");

		printf("Peso em quilogramas: ");
		scanf("%f", &pacient_SUS[pacient_count].weight);
		printf("\n");

		printf("Data da consulta(__/__/__): ");
		scanf("%s", pacient_SUS[pacient_count].consult_data);
		printf("\n");

		printf("Esteve em contato com alguém que contraiu COVID-19 na última semana? SIM/NÃO ");
		scanf("%s", pacient_SUS[pacient_count].last_week_contact);
		printf("\n");

		printf("Resultado COVID-19: ");
		scanf("%d", &pacient_SUS[pacient_count].COVID_19);
		printf("\n");
	return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////    PESQUIAR PACIENTE    /////////////////////////////////

int pesquisar_paciente() 
{
	printf("Pesquisar Paciente\n");
	return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////


int main(void) {
	
	int to_cycle = 1;

	do
	{
		banner();
		int logged_user;
		int mode = get_mode();

		//printf("MODE: %d\n", mode);
		
		if(mode == 0)
		{
			to_cycle = sign_in();
		}
		else
		{	

			//to_cycle = log_in(&logged_user);
			to_cycle = 2;
			if(to_cycle == 2) 
			{
				char program_action[1];
				int confirm_type_program_action;

				printf("          ___________________________________________\n");
				printf("                                                    \n");
				printf("               NOME: %s         ", cad_user[logged_user].name);

				if(strcmp(cad_user[logged_user].type, "MÉDICO") == 0)
				{
					printf("CRM: %s\n", cad_user[logged_user].CRM);
				}
				else{
					printf("CRE: %s\n", cad_user[logged_user].CRE);
				}
				printf("          ___________________________________________\n\n");
				
				
				printf("Escolha uma das opções do programa e digite o seu número correspondente: \n\n ");
				printf("1- Cadastrar paciente com COVID-19    2- Pesquisar paciente com COVID-19\n\n");
				
				do{
					printf("Digite o número: ");
					scanf("%s", program_action);
					confirm_type_program_action = strcmp(program_action, "1") == 0 || strcmp(program_action, "2") == 0 ? 0 : 1;
				}while(confirm_type_program_action == 1);

				if(strcmp(program_action, "1") == 0)
				{
					cadastrar_paciente();
					to_cycle = 0;
				}
				else
				{
					printf("Pesquisar paciente\n");
					to_cycle = 0;
				}			
			}
		}

		printf("Peso: %.2f\n",pacient_SUS[pacient_count].weight);

	}while(to_cycle == 0);
	
}

