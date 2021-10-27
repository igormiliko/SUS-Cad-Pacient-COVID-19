#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pwd.h>
#include <unistd.h>
#include <ctype.h>
#include <malloc.h>

int ler_string(char s[], int max)
{
    int i = 0;
    char letra;

    for (i = 0; i < (max - 1); i++) {
   letra = fgetc(stdin);

   if ((letra == '\n') && (i == 0)) {
       i = i - 1;
       continue;
   }

   if (letra == '\n')
       break;
   s[i] = letra;
    }

    s[i] = 0;

    return (i);
}

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

Professional_health cad_user[100];

int user_count = 0;


typedef struct 
{	
		char nome[60];
		char sex[2];
		int age;
		float height;
		float weight;
		char cns[40];
		char consult_data[11];
		char COVID_19[2];
		char last_week_contact[2];
} Patient;

Patient patient_SUS[100];

int patient_count = 0;


Professional_health logged_user;

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
	char *mode;
	mode = malloc(sizeof(char));
	int compare_mode;

	do
	{

		printf("Aperte 0 para se cadastrar, ou 1 para efetuar login: ");
		scanf("%s", mode);
		printf("\n");
		compare_mode = strcmp(mode, "0") == 0 || strcmp(mode, "1") == 0 ? 0 : 1;

	}while(compare_mode != 0 );

	return strcmp(mode, "0") == 0 ? 0 : 1;
}

//////////////////////////////////////    SIGNIN LOGIC    /////////////////////////////////////

static int sign_in()
{	

	int to_compare;
	//to_compare = malloc(sizeof(int));

	char user_conseil[3];
	//user_conseil = malloc(3 * sizeof(char) + 1);

	char compare_pass[8];
	//compare_pass = malloc(8 * sizeof(char) + 1);

	int confirm_datas;
	//confirm_datas = malloc(sizeof(int)	);

	Professional_health *registering_user = (Professional_health*) malloc(sizeof(Professional_health));

	if(registering_user)
	{
		do{
		printf("|--------------- CADASTRAR USUÁRIO ---------------|\n\n");
			do{
				printf("Digite 'CRM' para médico ou 'CRE' para Enfermeiro: ");
				scanf("%s", user_conseil);
				printf("\n");
				to_compare = strcmp(user_conseil, "CRM") == 0 || strcmp(user_conseil, "CRE") == 0 ? 0 : 1;
			}while(to_compare != 0);


			int confirm_conseil;
			if(strcmp(user_conseil, "CRM") == 0)
			{	
				do{
					confirm_conseil = 0;
					printf("Digite o seu CRM: ");
					scanf("%s", registering_user->CRM);
					printf("\n");
					if(user_count > 0) {
						for(int i = 0; i < user_count; i++ )
						{
							if(strcmp(registering_user->CRM, cad_user[i].CRM) == 0)
							{
								confirm_conseil = 1;
							}
						}
					}
					if(confirm_conseil == 1)
					{
						printf("Este CRM já está cadastrado!\n");
					}
				}while(confirm_conseil == 1);
				strcpy(registering_user->type, "MÉDICO");
			}
			else
			{
				do{
					confirm_conseil = 0;
					printf("Digite o seu CRE: ");
					scanf("%s", registering_user->CRE);
					printf("\n");
					if(user_count > 0) {
						for(int i = 0; i < user_count; i++ )
						{
							if(strcmp(registering_user->CRE, cad_user[i].CRE) == 0)
							{
								confirm_conseil = 1;
							}
						}
					}
					if(confirm_conseil == 1)
					{
						printf("Este CRE já está cadastrado!\n");
					}
				}while(confirm_conseil == 1);
				strcpy(registering_user->type, "ENFERMEIRO");
			}



			//TODO
			printf("Cadastre o seu nome completo: ");
			ler_string( registering_user->name, 60);
			printf("\n");
			//printf("%s", registering_user->name);

			int exist_user_name;
			do{
				exist_user_name = 0;
				printf("Cadastre o seu nome de usuário (sem espaços): ");
				ler_string( registering_user->nick_name, 60);
				printf("\n");
				if(user_count > 0)
				{
					for(int i = 0; i < user_count; i++) 
					{
						if(strcmp(registering_user->nick_name, cad_user[i].nick_name) == 0)
						{
							exist_user_name = 1;
							printf("Nome de usuário já existe!\n");
						}
					}
				}
			}while(exist_user_name == 1);

			do{
				printf("Qual o estado onde você trabalha(Utilize a forma abreviada 'DF')? ");
				scanf("%s", registering_user->estado);
				printf("\n");
			}while(strlen(registering_user->estado) != 2);

			printf("Qual o município onde você trabalha? ");
			ler_string(registering_user->municipio,30);
			printf("\n");

			printf("Qual sua unidade de saúde? ");
			scanf("%s", registering_user->unidade_SUS);

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

				strcpy(registering_user->senha, getpass("Cadastre sua senha: "));
				printf("\n");

				strongness_pass(registering_user->senha, &strong_ix);

					strcpy(compare_pass, getpass("Confirme sua senha: "));
					printf("\n");

					
				if(strong_ix > 0.325)
				{
						if(strncmp(registering_user->senha, compare_pass, 8) == 0)
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
		
					printf("NOME: %s\n", registering_user->name);
					printf("Nome de usuário: %s\n", registering_user->nick_name);
					if(strcmp(user_conseil, "CRM") == 0)
					{
						printf("O seu CRM é: %s", registering_user->CRM);
						printf("\n");
						printf("Você é um: %s",registering_user->type);
						printf("\n");
					}
					else
					{
						printf("O seu CRE é: %s", registering_user->CRE);
						printf("\n");
						printf("Você é um : %s",registering_user->type);
						printf("\n");
					}

					printf("ESTADO: %s\n", registering_user->estado);
					printf("MUNICIPIO: %s\n", registering_user->municipio);
					printf("UNIDADE DE SAÚDE: %s\n", registering_user->unidade_SUS);
					printf("\n");

				do{
					printf("Os seus dados estão corretos? Digite s/n -> ");
					scanf("%s", &confirm_type_char);
					printf("\n");

					confirm_datas = strcmp(&confirm_type_char, "s") == 0 || strcmp(&confirm_type_char, "n") == 0 ? 0 : 1;

				}while(confirm_datas == 1);

				confirm_datas = strcmp(&confirm_type_char, "s") == 0 ? 0 : 1;

		}while(confirm_datas == 1);

		cad_user[user_count] = *registering_user;

		free(registering_user);
	}
	user_count++;
	return 0;	
}



///////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////    LOGIN LOGIC    /////////////////////////////////////
int log_in()
{	
	int i;
	char user_name[60];
	char user_password[8];

	int user_name_in_DB = 1;
	int user_password_correct;

	int user_to_compare_password;

	printf("|------------------------ LOGIN ------------------------|\n\n");
	do{
		printf("Nome de usuário: ");
		scanf("%s", user_name);
		printf("\n");

		for(i = 0; i < user_count; i++)
		{
			if(strcmp(user_name, cad_user[i].nick_name) == 0)
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
			
			return user_to_compare_password;
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

	return 1;
}


///////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////    CADASTRAR PACIENTE   /////////////////////////////////

int cadastrar_paciente() 
{
	int confirm_pacient_datas;
	Patient *registering_patient = (Patient*)malloc(sizeof(Patient));

	printf("|------------------ CADASTRAR PACIENTE -----------------|\n\n");
	if(registering_patient)
	{	
		do{
			// a função ler_string aceita espaços
			printf("Nome: ");
			ler_string(registering_patient->nome, 60);
			printf("\n");

			int confirm_typed_sex;
			do{
				printf("Sexo: M/F ");
				ler_string(registering_patient->sex, 2);
				printf("\n");
				confirm_typed_sex = strcmp(registering_patient->sex, "M") == 0 ||
								strcmp(registering_patient->sex, "F") == 0 ? 0 : 1;
			}while(confirm_typed_sex == 1);


				printf("Idade: ");
				scanf("%d", &registering_patient->age);
				printf("\n");
			
			int exist_cns;
			do{
				exist_cns = 0;

				printf("CNS (Cartão Nacional de Saúde): ");
				scanf("%s", registering_patient->cns);
				printf("\n");
				if(patient_count > 0)
				{	
					for(int i = 0; i < patient_count; i++)
					{
						if(strcmp(registering_patient->cns, patient_SUS[i].cns) == 0)
						{
							exist_cns = 1;
						}
					}
				}
				if(exist_cns == 1)
				{
					printf("Este CNS já está cadastrado!\n\n");
				}
			}while(exist_cns == 1);

				printf("Altura em metros: ");
				scanf("%f", &registering_patient->height);
				printf("\n");
				
				printf("Peso em quilogramas: ");
				scanf("%f", &registering_patient->weight);
				printf("\n");

			// Algoritimo para confirmar se o usuário digitou a data no formato correto
			int confirm_type_date;
			do{
				printf("Data da consulta(__/__/__): ");
				scanf("%s",registering_patient->consult_data);
				printf("\n");

				int len = strlen(registering_patient->consult_data);
				
				int const_bar = strcmp(&registering_patient->consult_data[2], "/")  &&
								strcmp(&registering_patient->consult_data[5], "/")  ? 0 : 1;

				confirm_type_date = const_bar == 0 && len == 10 ? 0 : 1;

				if(confirm_type_date == 1)
				{
					printf("Formato inválido!!\n");
				}
			}while(confirm_type_date == 1);

			// Alghoritimo para confirmarse o usuário digitou S ou N
			int type_confirm_y_n;
			do{
				printf("Esteve em contato com alguém que contraiu COVID-19 na última semana? Digite s/n ");
				scanf("%s", registering_patient->last_week_contact);
				printf("\n");

				type_confirm_y_n = strcmp(registering_patient->last_week_contact, "s") == 0 || 
								strcmp(registering_patient->last_week_contact, "n") == 0 ? 0 : 1;

			}while(type_confirm_y_n == 1);

			// Alghoritimo para confirmar se o usuário digitou o resultado de COVID-19
			// no formato correto.
			int type_confirm_plus_minus;
			do{
				printf("Resultado COVID-19: +/- ");
				scanf("%s", registering_patient->COVID_19);
				printf("\n");

				type_confirm_plus_minus = strcmp(registering_patient->COVID_19, "+") == 0 || 
								strcmp(registering_patient->COVID_19, "-") == 0 ? 0 : 1;
			}while(type_confirm_plus_minus == 1);
			
			

			char confirm_char;
			do{
				printf("Os dados do paciente estão corretos? Digite s/n -> ");
				scanf("%s", &confirm_char);
				printf("\n");

				confirm_pacient_datas = strcmp(&confirm_char, "s") == 0 || strcmp(&confirm_char, "n") == 0 ? 0 : 1;

			}while(confirm_pacient_datas == 1);

			confirm_pacient_datas = strcmp(&confirm_char, "s") == 0 ? 0 : 1;

		}while(confirm_pacient_datas == 1);

		patient_SUS[patient_count] = *registering_patient;
		free(registering_patient);
	}
	
	patient_count++;
	return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////    PESQUIAR PACIENTE    /////////////////////////////////

int pesquisar_paciente() 
{
	char program_action[1];
	int confirm_type_program_action;

	printf("|------------------ PESQUISAR PACIENTE -----------------|\n\n");
	printf("Digite o número correspondente ao modo de pesquisa:\n\n");
	printf("1- Por nome    2- Por CNS   3- Por resultado de COVID-19\n\n");
	printf("4- Voltar\n\n");
	
	do{
		printf("Digite o número correspondente à ação: ");
		scanf("%s", program_action);
		printf("\n");
		confirm_type_program_action = strcmp(program_action, "1") == 0 || strcmp(program_action, "2") ||
									  strcmp(program_action, "3") == 0 || strcmp(program_action, "4") ? 0 : 1;
	}while(confirm_type_program_action == 1);
	
	if(strcmp(program_action, "1") == 0)
	{
		char *name_to_search;
		name_to_search = malloc(60 * sizeof(char));
		int finding_pacient;
		int pacient_finded_ix = -1;


		printf("Digite o nome do paciente: ");
		ler_string(name_to_search, 60);
		printf("\n");

		for(int i = 0; i < patient_count; i++)
		{
			finding_pacient = strcmp(patient_SUS[i].nome, name_to_search) == 0 ? 0 : 1;
			if(finding_pacient == 0)
			{
				pacient_finded_ix = i;
			}
		}
		if(pacient_finded_ix == -1)
		{
			printf("          _____________________________________________________\n");
			printf("         |                                                     |\n");
			printf("         |    Nome do paciente não consta na base de dados     |\n");
			printf("         |_____________________________________________________|\n\n");
		}
		else
		{
			printf("NOME: %s\n", patient_SUS[pacient_finded_ix].nome);
			printf("CNS: %s\n", patient_SUS[pacient_finded_ix].cns);
			printf("IDADE: %d\n", patient_SUS[pacient_finded_ix].age);
			printf("ALTURA: %.2fm\n", patient_SUS[pacient_finded_ix].height);
			printf("PESO: %.2fkg\n", patient_SUS[pacient_finded_ix].weight);
			printf("DATA DA CONSULTA: %s\n", patient_SUS[pacient_finded_ix].consult_data);
			printf("CONTATO COM INFECTADO? %s\n", patient_SUS[pacient_finded_ix].last_week_contact);
			printf("RESULTADO COVID-19: %s\n\n", patient_SUS[pacient_finded_ix].COVID_19);
		}
	}
	else if (strcmp(program_action, "2") == 0)
	{
		char cns_to_search[40];
		int finding_pacient;
		int pacient_finded_ix = -1;


		printf("Digite o CNS do paciente: ");
		scanf("%s",cns_to_search);
		printf("\n");

		for(int i = 0; i < patient_count; i++)
		{
			finding_pacient = strcmp(patient_SUS[i].cns, cns_to_search) == 0 ? 0 : 1;
			if(finding_pacient == 0)
			{
				pacient_finded_ix = i;
			}
			
		}
		if(pacient_finded_ix == -1)
		{
			printf("          _____________________________________________________\n");
			printf("         |                                                     |\n");
			printf("         |    CNS  do paciente não consta na base de dados     |\n");
			printf("         |_____________________________________________________|\n\n");
		}
		else
		{
			printf("NOME: %s\n", patient_SUS[pacient_finded_ix].nome);
			printf("CNS: %s\n", patient_SUS[pacient_finded_ix].cns);
			printf("IDADE: %d\n", patient_SUS[pacient_finded_ix].age);
			printf("ALTURA: %.2fm\n", patient_SUS[pacient_finded_ix].height);
			printf("PESO: %.2fkg\n", patient_SUS[pacient_finded_ix].weight);
			printf("DATA DA CONSULTA: %s\n", patient_SUS[pacient_finded_ix].consult_data);
			printf("CONTATO COM INFECTADO? %s\n", patient_SUS[pacient_finded_ix].last_week_contact);
			printf("RESULTADO COVID-19: %s\n\n", patient_SUS[pacient_finded_ix].COVID_19);
		}

	}
	else if (strcmp(program_action, "3") == 0)
	{
		char covid_result;
		int confirm_right_type;
		int count_result = 0;

		do
		{
			printf("Digite + (sinal de adição) para listar pacientes com resultado positivo ou \n");
			printf("digite - (sinal de subtração) para listar os pacientes com resultado negativo: -> ");
			scanf("%s", &covid_result);
			printf("\n");
			confirm_right_type = strcmp(&covid_result, "+") == 0 || strcmp(&covid_result, "-") == 0 ? 0 : 1;
		} while (confirm_right_type == 1);

		if(strcmp(&covid_result, "+") == 0)
		{
			printf("          ___________________________________________\n");
			printf("         |                                           |\n");
			printf("         |    Pacientes com resultados positivos     |\n");
			printf("         |___________________________________________|\n\n");
			for(int i = 0; i < patient_count; i++)
			{
				if(strcmp(patient_SUS[i].COVID_19, "+") == 0)
				{
					printf("%d- Nome do paciente: %s", i + 1, patient_SUS[i].nome);
					printf("    Resultado: %s\n\n", patient_SUS[i].COVID_19);
					count_result++;
				}
			}
			if(count_result > 0)
			{
				printf("______________________________________________________________\n");
				printf("                                                              \n");
				printf("  Total de pacientes positivos para COVID-19 encontrados: %d  \n", count_result);
				printf("______________________________________________________________\n\n");
			}
			else
			{
				printf("          _____________________________________________\n");
				printf("         |                                             |\n");
				printf("         |    Não foi encontrado nenhum paciente com   |\n");
				printf("         |    resultado  positivo  para COVID-19  na   |\n");
				printf("         |                base de dados.               |\n");
				printf("         |_____________________________________________|\n\n");
			}
		}

		else if(strcmp(&covid_result, "-") == 0)
		{
			printf("          ___________________________________________\n");
			printf("         |                                           |\n");
			printf("         |    Pacientes com resultados negativos     |\n");
			printf("         |___________________________________________|\n\n");
			for(int i = 0; i < patient_count; i++)
			{
				if(strcmp(patient_SUS[i].COVID_19, "-") == 0)
				{
					printf("%d- Nome do paciente: %s", i + 1, patient_SUS[i].nome);
					printf("    Resultado: %s\n\n", patient_SUS[i].COVID_19);
					count_result++;
				}
			}
			if(count_result > 0)
			{
				printf("______________________________________________________________\n");
				printf("                                                              \n");
				printf("  Total de pacientes neagtivos para COVID-19 encontrados: %d  \n", count_result);
				printf("______________________________________________________________\n\n");
			}
			else
			{
				printf("          _____________________________________________\n");
				printf("         |                                             |\n");
				printf("         |    Não foi encontrado nenhum paciente com   |\n");
				printf("         |    resultado  negativo  para COVID-19  na   |\n");
				printf("         |                base de dados.               |\n");
				printf("         |_____________________________________________|\n\n");
			}
		}	
		
	}

	else if (strcmp(program_action, "4") == 0)
	{
		return 1;
	}
	return 2;
}
//////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////    PESQUIAR PACIENTE    /////////////////////////////////

int calculos_estatisticos() 
{
	printf("          ________________________________________\n");
	printf("         |                                        |\n");
	printf("         |    Sistema de cálculos estatísticos    |\n");
	printf("         |________________________________________|\n\n");

	char number_typed[1];
	int confirm_typed;
		printf("Digite o número correspondente ao cálculo estatístico:\n\n");
		printf(" 1- Média do peso     2- Média da altura     3- Média da idade\n\n");
		printf(" 4- Voltar\n\n");
	do{
		printf("Digite o número: ");
		scanf("%s", number_typed);
		printf("\n");

		confirm_typed = strcmp(number_typed, "1") == 0 || strcmp(number_typed, "2") == 0 ||
						strcmp(number_typed, "3") == 0 || strcmp(number_typed, "4") == 0  ? 0 : 1;

	}while(confirm_typed == 1);


	char type_of_pacient[1];
	int confirm_pacient_type;
	if(strcmp(number_typed, "1") == 0 || strcmp(number_typed, "2") == 0 || strcmp(number_typed, "3") == 0)
	{
		printf("Digite o número correspondente ao tipo de amostra populacional:\n\n");
		printf("1- Pacientes com COVID-19    2- Pacientes sem COVID-19\n\n");
		do{
			printf("Digite o número: ");
			scanf("%s", type_of_pacient);
			printf("\n");

			confirm_pacient_type = strcmp(type_of_pacient, "1") == 0 || strcmp(type_of_pacient, "2") == 0 ? 0 : 1;

		}while(confirm_pacient_type == 1);

		if(strcmp(number_typed, "1") == 0)
		{
			if(strcmp(type_of_pacient, "1") == 0)
			{
				int i;
				int positive_pacient = 0;
				float weight_media = 0.00;
				for(i = 0; i < patient_count; i++)
				{	
					if(strcmp(patient_SUS[i].COVID_19, "+") == 0)
					{
						weight_media += patient_SUS[i].weight;
						positive_pacient++;
					}
				}
					weight_media = positive_pacient > 0 ? weight_media / (float) positive_pacient : weight_media;
					printf("Foram encontrados um total de %d pacientes com resultado positivo para COVID-19.\n\n", positive_pacient);
					printf("Media do peso corresponde a: %.2fkg\n\n", weight_media);
			}

			else
			{
				float weight_media = 0.00;
				int negative_pacient = 0;
				for(int i = 0; i < patient_count; i++)
				{	
					if(strcmp(patient_SUS[i].COVID_19, "-") == 0)
					{
						weight_media += patient_SUS[i].weight;
						negative_pacient++;
					}
				}
					weight_media = negative_pacient > 0 ? weight_media / (float) negative_pacient : weight_media;
					printf("Foram encontrados um total de %d pacientes com resultado negativo para COVID-19.\n\n", negative_pacient);
					printf("Media do peso: %.2fkg\n\n", weight_media);
			}

			return 1;
		}
		else if(strcmp(number_typed, "2") == 0)
		{
			if(strcmp(type_of_pacient, "1") == 0)
			{
				int i;
				int positive_pacient = 0;
				float height_media = 0.00;
				for(i = 0; i < patient_count; i++)
				{	
					if(strcmp(patient_SUS[i].COVID_19, "+") == 0)
					{
						height_media += patient_SUS[i].height;
						positive_pacient++;
					}
				}
					height_media = positive_pacient > 0 ? height_media / (float) positive_pacient : height_media;
					printf("Foram encontrados um total de %d pacientes com resultado positivo para COVID-19.\n\n", positive_pacient);
					printf("Media da altura corresponde a: %.2fm\n\n", height_media);
			}

			else
			{
				float height_media = 0.00;
				int negative_pacient = 0;
				for(int i = 0; i < patient_count; i++)
				{	
					if(strcmp(patient_SUS[i].COVID_19, "-") == 0)
					{
						height_media += patient_SUS[i].height;
						negative_pacient++;
					}
				}
					height_media = negative_pacient > 0 ? height_media / (float) negative_pacient : height_media;
					printf("Foram encontrados um total de %d pacientes com resultado negativo para COVID-19.\n\n", negative_pacient);
					printf("Media da altura corresponde a: %.2fkg\n\n", height_media);
			}
			return 1;
		}
		else if(strcmp(number_typed, "3") == 0)
		{
			if(strcmp(type_of_pacient, "1") == 0)
			{
				int i;
				int positive_pacient = 0;
				float age_media = 0.00;
				for(i = 0; i < patient_count; i++)
				{	
					if(strcmp(patient_SUS[i].COVID_19, "+") == 0)
					{
						age_media += (float)patient_SUS[i].age;
						positive_pacient++;
					}
				}
					age_media = positive_pacient > 0 ? age_media / (float) positive_pacient : age_media;
					printf("Foram encontrados um total de %d pacientes com resultado positivo para COVID-19.\n\n", positive_pacient);
					printf("Media da idade corresponde a: %.2fkg\n\n", age_media);
			}

			else
			{
				float age_media = 0.00;
				int negative_pacient = 0;
				for(int i = 0; i < patient_count; i++)
				{	
					if(strcmp(patient_SUS[i].COVID_19, "-") == 0)
					{
						age_media += (float)patient_SUS[i].age;
						negative_pacient++;
					}
				}
					age_media = negative_pacient > 0 ? age_media / (float) negative_pacient : age_media;
					printf("Foram encontrados um total de %d pacientes com resultado negativo para COVID-19.\n\n", negative_pacient);
					printf("Media da idade corresponde a: %.2fkg\n\n", age_media);
			}
			return 1;
		}
		else{
			return 2;
		}
	}
	else if(strcmp(number_typed, "4") == 0)
	{
		return 1;
	}
	return 2;
}

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

			logged_user = log_in();
			//to_cycle = 2;

			if(logged_user > -1) 
			{
					printf("___________________________________________\n");
					printf("                                           \n");
					printf(" NOME: %s         ", cad_user[logged_user].nick_name);

					if(strcmp(cad_user[logged_user].type, "MÉDICO") == 0)
					{
						printf("  CRM: %s\n", cad_user[logged_user].CRM);
					}
					else{
						printf("  CRE: %s\n", cad_user[logged_user].CRE);
					}
					printf("___________________________________________\n\n");

				do{
					printf("          _____________________________________________________\n");
					printf("         |                                                     |\n");
					printf("         |    Sistema de cadastro e pesquisa  de pacientes     |\n");
					printf("         |_____________________________________________________|\n\n");
					char program_action[1];
					int confirm_type_program_action;

					do{
					printf("Escolha uma das opções do programa e digite o seu número correspondente: \n\n ");
					printf("1- Cadastrar paciente com COVID-19    2- Pesquisar paciente com COVID-19\n\n");
					printf(" 3- Cálculos estatísticos              4- Sair\n\n");
					
						printf("Digite o número: ");
						scanf("%s", program_action);
						printf("\n");
						confirm_type_program_action = strcmp(program_action, "1") == 0 || strcmp(program_action, "2") == 0 || 
													  strcmp(program_action, "3") == 0 || strcmp(program_action, "4") == 0 ? 0 : 1;
					}while(confirm_type_program_action == 1);


					if(strcmp(program_action, "1") == 0)
					{
						cadastrar_paciente();
						to_cycle = 1;
					}
					else if(strcmp(program_action, "2") == 0)
					{	
						do
						{
							to_cycle = pesquisar_paciente();
						}while(to_cycle == 2);
					}
					else if(strcmp(program_action, "3") == 0)
					{
						do
						{
							to_cycle = calculos_estatisticos();
						} while (to_cycle == 2);					
					}
					else if(strcmp(program_action, "4") == 0)
					{
						printf("Sair\n");
						to_cycle = 0;
					}
					else
					{
						to_cycle = 1;
					}

				}while(to_cycle == 1);
			}
		}

	}while(to_cycle == 0);
	
}
