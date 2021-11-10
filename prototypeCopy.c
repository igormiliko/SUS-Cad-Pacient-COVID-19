#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pwd.h>
#include <math.h>
#include <unistd.h>
#include <ctype.h>
#include <malloc.h>
#include <time.h>

typedef struct 
{
    char street[99];
    char number[9];
    char state[2];
    char district[99];
    char city[99];
    char postal_code[9];
} Adress;

typedef struct 
{	
		char nome[60];
		char cpf[14];
		int age;
		char born_date[11];
		char email[120];
		char disease[20];
		char consult_data[11];
		char phone_number[13];
		char COVID_19[2];
        Adress address;
} Patient;


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
		char nick_name[60];
		char senha[8];
} Professional_health;

Professional_health cad_user[100];

int user_count = 0;

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
	system("clear");
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
				to_compare = strncmp(user_conseil, "CRM", 3) == 0 || strncmp(user_conseil, "CRE", 3) == 0 ? 0 : 1;
			}while(to_compare != 0);


			int confirm_conseil;
			if(strncmp(user_conseil, "CRM", 3) == 0)
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
			}

			int exist_user_name = 0;
			int is_space;
			do{
				is_space = 0;

				printf("Cadastre o seu nome de usuário (sem espaços): ");
				ler_string( registering_user->nick_name, 60);
				printf("\n");
				
				char *temp;
				for(int i = 0; i < strlen(registering_user->nick_name); i++)
				{
					temp = malloc(sizeof(char));
					temp = &registering_user->nick_name[i];
					if(strncmp(temp, " ", 1) == 0)
					{	
						printf("Formato inválido!!!\n");
						is_space = 1;
					}
				}
				if(is_space == 0)
				{
					if(user_count > 0)
					{
						for(int i = 0; i < user_count; i++) 
						{
							if(strcmp(registering_user->nick_name, cad_user[i].nick_name) == 0)
							{
								exist_user_name = 1;
								printf("Nome de usuário já existe!\n");
							}
							else
							{
								exist_user_name = 0;
							}
						}
					}
				}			
			}while(exist_user_name == 1 || is_space == 1);

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
					system("clear");
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
		
					printf("Nome de usuário: %s\n", registering_user->nick_name);

					if(strncmp(user_conseil, "CRM", 3) == 0)
					{
						printf("O seu CRM é: %s", registering_user->CRM);
						printf("\n");
					}
					else
					{
						printf("O seu CRE é: %s", registering_user->CRE);
						printf("\n");
					}
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
			system("clear");
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
	system("clear");
	return 1;
}


///////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////    CADASTRAR PACIENTE   /////////////////////////////////

int cadastrar_paciente() 
{
	

	printf("|------------------ CADASTRAR PACIENTE -----------------|\n\n");

		Patient registering_patient;

			//a função ler_string aceita espaços
			printf("Nome: ");
			ler_string(registering_patient.nome, 60);
			printf("\n");

			printf("\nCadastrar endereço:\n");

			int confirm_state;
			do{
				confirm_state = 1;
				printf("Estado(Utilize a forma abreviada 'DF')? ");
				scanf("%s", registering_patient.address.state);
				printf("\n");
				
				int len = strlen(registering_patient.address.state);
				if(len == 2)
				{
					confirm_state = isupper(registering_patient.address.state[0]) != 0 &&
									isupper(registering_patient.address.state[1]) != 0 ? 0 : 1;
				}
			}while(confirm_state == 1);

			printf("Rua: ");
			ler_string(registering_patient.address.street, 99);
			printf("\n");

			printf("Número: ");
			ler_string(registering_patient.address.number, 99);
			printf("\n");

			printf("Bairro: ");
			ler_string(registering_patient.address.district, 99);
			printf("\n");

			printf("Cidade: ");
			ler_string(registering_patient.address.city, 99);
			printf("\n");


			int correct_typed_cep;
			do{
				printf("Digite o cep do paciente no formato XXXXX-XXX: ");
				ler_string(registering_patient.address.postal_code, 10);
				printf("\n");

				correct_typed_cep = strlen(registering_patient.address.postal_code) == 9 && 
									strncmp(&registering_patient.address.postal_code[5], "-", 1) == 0 ? 0 : 1; 
			}while(correct_typed_cep == 1);


			// Capturar a data de nascimentio do paciente e calcular sua idade
			int confirm_born_date = 0;
			do{
				printf("Data de nascimento:(__/__/__) ");
				scanf("%s", registering_patient.born_date);
				printf("\n");
				//scanf("%d", &registering_patient.age);
				int len = strlen(registering_patient.born_date);
				
				int const_bar = strcmp(&registering_patient.born_date[2], "/")  &&
								strcmp(&registering_patient.born_date[5], "/")  ? 0 : 1;

				confirm_born_date = const_bar == 0 && len == 10 ? 0 : 1;

				if(confirm_born_date == 1)
				{
					printf("Formato inválido!!\n");
				}
				else
				{
					//Se a data digitada estiver no formato válido fará o cálculo da idade
					struct tm *local;
					local = (struct tm*)malloc(sizeof(struct tm));
					time_t t;
					t= time(NULL);
					local=localtime(&t);
					char *to_int = malloc(sizeof(char) * 4);

					int patient_born_day, patient_born_month, patient_born_year;
					int current_day, current_month, current_year;
					int computing_age;

					//Pegando a data atual
					current_day = local->tm_mday;
					current_month = local->tm_mon+1;
					current_year = local->tm_year+1900;    

					// Transformando o dia em inteiro
					to_int[0] = registering_patient.born_date[0];
					to_int[1] = registering_patient.born_date[1];
					patient_born_day = atoi(to_int);

					// Transformando o mês em inteiro
					to_int[0] = registering_patient.born_date[3];
					to_int[1] = registering_patient.born_date[4];
					patient_born_month = atoi(to_int);

					// Transformando o ano em inteiro
					to_int[0] = registering_patient.born_date[6];
					to_int[1] = registering_patient.born_date[7];
					to_int[2] = registering_patient.born_date[8];
					to_int[3] = registering_patient.born_date[9];
					patient_born_year = atoi(to_int);
					
					// Calculando a idade do paciente
					computing_age = current_year - patient_born_year;

					if(current_month == patient_born_month)
					{
						if(current_day < patient_born_day)
						{
							computing_age--;
						}
					}
					else if(current_month < patient_born_month)
					{
						computing_age--;
					}
					registering_patient.age = computing_age;
					printf("Idade: %d\n\n", registering_patient.age);
					
				}

			}while(confirm_born_date == 1);

			// REGRA PARA CAPTURAR O TELEFONE DO PACIENTE (XX)98590-8989
			int confirm_phone_typed;
			do
			{
				printf("Digite o número de telefone do paciente no formato (XX)9XXXX-XXXX: ");
				scanf("%s", registering_patient.phone_number);
				printf("\n");

				confirm_phone_typed = strlen(registering_patient.phone_number) == 14 &&
						              strncmp(&registering_patient.phone_number[0], "(", 1) == 0 &&
						              strncmp(&registering_patient.phone_number[3], ")", 1) == 0 &&
						              strncmp(&registering_patient.phone_number[4], "9", 1) == 0 &&
						              strncmp(&registering_patient.phone_number[9], "-", 1) == 0 ? 0 : 1;
				if(confirm_phone_typed == 1)
				{
					printf("Formato de telefone inválido!\n");
				}


			}while(confirm_phone_typed == 1);

			// TODO
			int correct_typed_cpf;
			do{
				printf("Digite o CPF do paciente no formato XXX.XXX.XXX-XX: ");
				scanf("%s", registering_patient.cpf);
				printf("\n");

				correct_typed_cpf = strlen(registering_patient.cpf) == 14 && 
									strncmp(&registering_patient.cpf[3], ".", 1) == 0 && 
									strncmp(&registering_patient.cpf[7], ".", 1) == 0 &&
									strncmp(&registering_patient.cpf[11], "-", 1) == 0 ? 0 : 1; 
			}while(correct_typed_cpf == 1);


			// REGRA PARA CAPTURAR O EMAIL DO PACIENTE E VERIFICAR SE ELE EXISTE NO BANCO DE DADOS
			int confirm_email_typed = 1;
			int find_arr, find_dote = 1;
			char email[70];
			do{
				printf("Digite o email do paciente: ");
				scanf("%s", email);
				printf("\n");
				for(int i = 0; i < strlen(email); i++)
				{
					if(strncmp(&email[i], "@",1) == 0)
					{
						find_arr = 0;
					}
					if(strncmp(&email[i], ".",1) == 0)
					{
						find_dote = 0;
					}
				}
				confirm_email_typed = find_arr == 0 && find_dote == 0 ? 0 : 1;
				if(confirm_email_typed == 1)
				{
					printf("Email inválido!!\n");
				}
				else
				{
					strcpy(registering_patient.email, email);
				}
			}while(confirm_email_typed == 1);

			//REGRA PARA CAPTURAR DOENÇAS DO PACIENTE E VERIFICAR SE ELE EXISTE NO BANCO DE DADOS
			int confirm_disease;
			do{

				char disease[12];
				char typed_number[1];
				confirm_disease = 0;
				printf("O paciente possui alguma doença listada a baixo? \nSe sim Digite o número correspondente, caso ao contrário digite 0:\n");
				printf("1- Hipertensão    2- Diabetes    3- Obesidade    4- Asma\n");
				printf("5- AIDS           6- Câncer      7- Depressão    8- Tuberculose\n\n");
				printf("Digite: ");
				scanf("%s", typed_number);
				if(	strcmp(typed_number, "1") == 0 || strcmp(typed_number, "2") == 0 || strcmp(typed_number, "3") == 0 || 
					strcmp(typed_number, "4") == 0 || strcmp(typed_number, "5") == 0 || strcmp(typed_number, "") == 0 ||
					strcmp(typed_number, "7") == 0 || strcmp(typed_number, "8") == 0 )
				{

					switch (atoi(typed_number))
					{
					case 1:  
						strcpy(registering_patient.disease, "Hipertensão");
						break;
					case 2:  
						strcpy(registering_patient.disease, "Diabetes");
						break;
					case 3:  
						strcpy(registering_patient.disease, "Obesidade");
						break;
					case 4:  
						strcpy(registering_patient.disease, "Asma");
						break;
					case 5:  
						strcpy(registering_patient.disease, "AIDS");
						break;
					case 6:  
						strcpy(registering_patient.disease, "Câncer");
						break;
					case 7:  
						strcpy(registering_patient.disease, "Depressão");
						break;
					case 8:  
						strcpy(registering_patient.disease, "Tuberculose");
						break;
					
					default:
						break;
					}
				}
			}while(confirm_disease == 1);

			// Alghoritimo para confirmar se o usuário digitou o resultado de COVID-19
			// no formato correto.
			int type_confirm_plus_minus;
			do{
				printf("Resultado COVID-19: +/- ");
				scanf("%s", registering_patient.COVID_19);
				printf("\n");

				type_confirm_plus_minus = strcmp(registering_patient.COVID_19, "+") == 0 || 
								strcmp(registering_patient.COVID_19, "-") == 0 ? 0 : 1;
			}while(type_confirm_plus_minus == 1);

			// Algoritimo para confirmar se o usuário digitou a data no formato correto
			int confirm_type_date;
			do{
				printf("Data do diagnósticode COVID-19(__/__/__): ");
				scanf("%s",registering_patient.consult_data);
				printf("\n");

				int len = strlen(registering_patient.consult_data);
				
				int const_bar = strcmp(&registering_patient.consult_data[2], "/")  &&
								strcmp(&registering_patient.consult_data[5], "/")  ? 0 : 1;

				confirm_type_date = const_bar == 0 && len == 10 ? 0 : 1;

				if(confirm_type_date == 1)
				{
					printf("Formato inválido!!\n");
				}
			}while(confirm_type_date == 1);
			
			system("clear");

	//Gravar em arquivo .json
	char age[2]; sprintf(age, "%d", registering_patient.age);

  	FILE *fp;
    fp = fopen("patient.json","a");
	int success_close;
    
	// Checar se não ocorreu nenhum erro ao abrir o arquivo
	if(fp == NULL)
	{
		printf("\nErro ao abrir o arquivo!\n");
	}
	else{
		//Registrando pacientes que estão em grupo de risco
		if(registering_patient.age > 65)
		{
			FILE *rf;
			rf = fopen("risk.json","w");
			int success_close;
	
			if(rf == NULL)
			{
				printf("\nErro ao abrir o arquivo!\n");
			}
			else
			{
				// Formatação para JSON
				fputs("\n{\n", rf);
					fputs("    \"name\":", rf); fputs("\"", rf); fputs(registering_patient.nome, rf); fputs("\",\n", rf);
					fputs("    \"Age\":", rf); fputs("\"", rf); fputs(age, rf); fputs("\",\n", rf);
					fputs("    \"CEP\":", rf); fputs("\"", rf); fputs(registering_patient.address.postal_code, rf); fputs("\"\n", rf);
				fputs("},\0", rf);

				fclose(rf);

			}
		}
		// Formatação para JSON
        fputs("\n{\n", fp);
            fputs("    \"name\":", fp); fputs("\"", fp); fputs(registering_patient.nome, fp); fputs("\",\n", fp);
            fputs("    \"CPF\":", fp); fputs("\"", fp); fputs(registering_patient.cpf, fp); fputs("\",\n", fp);
            fputs("    \"phone_number\":", fp); fputs("\"", fp); fputs(registering_patient.phone_number, fp); fputs("\",\n", fp);
				fputs("    \"Adress\": {\n", fp); 
					fputs("        \"street\":", fp); fputs("\"", fp); fputs(registering_patient.address.street, fp); fputs("\",\n", fp);
					fputs("        \"number\":", fp); fputs("\"", fp); fputs(registering_patient.address.number, fp); fputs("\",\n", fp);
					fputs("        \"district\":", fp); fputs("\"", fp); fputs(registering_patient.address.district, fp); fputs("\",\n", fp);
					fputs("        \"city\":", fp); fputs("\"", fp); fputs(registering_patient.address.city, fp); fputs("\",\n", fp);
					fputs("        \"state\":", fp); fputs("\"", fp); fputs(registering_patient.address.state, fp); fputs("\",\n", fp);
					fputs("        \"postal_code\":", fp); fputs("\"", fp); fputs(registering_patient.address.postal_code, fp); fputs("\"\n", fp);
				fputs("    },\n", fp);
            fputs("    \"age\":", fp); fputs("\"", fp); fputs(age, fp); fputs("\",\n", fp);
            fputs("    \"born_date\":", fp); fputs("\"", fp); fputs(registering_patient.born_date, fp); fputs("\",\n", fp);
            fputs("    \"email\":", fp); fputs("\"", fp); fputs(registering_patient.email, fp); fputs("\",\n", fp);
            fputs("    \"disease\":", fp); fputs("\"", fp); fputs(registering_patient.disease, fp); fputs("\",\n", fp);
            fputs("    \"consult_date\":", fp); fputs("\"", fp); fputs(registering_patient.consult_data, fp); fputs("\",\n", fp);
            fputs("    \"COVID_19\":", fp); fputs("\"", fp); fputs(registering_patient.COVID_19, fp); fputs("\"\n", fp);
        fputs("},", fp);
	}
    success_close = fclose(fp);

	if(success_close == 0) printf("\nPaciente salvo com sucesso\n");
	else printf("\nErro ao salvar paciente\n");

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

			//logged_user = log_in();
			logged_user = 2;

			if(logged_user > -1) 
			{
					printf("___________________________________________\n");
					printf("                                           \n");
					printf(" NOME: %s         ", cad_user[logged_user].nick_name);

					if(strcmp(cad_user[logged_user].CRM, "") == 0)
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
					printf("         |    Sistema de cadastro de pacientes com  COVID-19   |\n");
					printf("         |_____________________________________________________|\n\n");
					char program_action[1];
					int confirm_type_program_action;

					do{
					printf("Escolha uma das opções do programa e digite o seu número correspondente: \n\n ");
					printf("1- Cadastrar paciente com COVID-19    2- Sair\n\n");					
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