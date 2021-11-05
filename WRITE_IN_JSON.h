#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct 
{
    char street[99];
    char number[9];
    char district[99];
    char city[99];
    char state[2];
    char postal_code[10];
} Adress;

typedef struct 
{	
		char nome[60];
		char cpf[14];
		char phone_number[14];
		int age;
		char born_date[11];
		char email[120];
		char disease[20];
		char consult_data[11];
		char COVID_19[2];
        Adress address;
} Patient;


int to_JSON(Patient *patient_JSON) {
    char age[2]; sprintf(age, "%d", patient_JSON->age);

  FILE *fp;
    fp = fopen("patient.txt","a+");
    if(fp == NULL)
        printf("Erro ao abrir o arquivo! \n\n");


    fputs("\n{\n", fp);
        fputs("    \"name\":", fp); fputs("\"", fp); fputs(patient_JSON->nome, fp); fputs("\",\n", fp);
        fputs("    \"CPF\":", fp); fputs("\"", fp); fputs(patient_JSON->cpf, fp); fputs("\",\n", fp);
        fputs("    \"phone_number\":", fp); fputs("\"", fp); fputs(patient_JSON->phone_number, fp); fputs("\",\n", fp);
        
        fputs("    \"Adress\": {\n", fp); 
            fputs("        \"street\":", fp); fputs("\"", fp); fputs(patient_JSON->address.street, fp); fputs("\",\n", fp);
            fputs("        \"number\":", fp); fputs("\"", fp); fputs(patient_JSON->address.number, fp); fputs("\",\n", fp);
            fputs("        \"district\":", fp); fputs("\"", fp); fputs(patient_JSON->address.district, fp); fputs("\",\n", fp);
            fputs("        \"city\":", fp); fputs("\"", fp); fputs(patient_JSON->address.city, fp); fputs("\",\n", fp);
            fputs("        \"state\":", fp); fputs("\"", fp); fputs(patient_JSON->address.state, fp); fputs("\",\n", fp);
            fputs("        \"postal_code\":", fp); fputs("\"", fp); fputs(patient_JSON->address.postal_code, fp); fputs("\",\n", fp);
        fputs("    },\n", fp);

        fputs("    \"age\":", fp); fputs("\"", fp); fputs(age, fp); fputs("\",\n", fp);
        fputs("    \"born_date\":", fp); fputs("\"", fp); fputs(patient_JSON->born_date, fp); fputs("\",\n", fp);
        fputs("    \"email\":", fp); fputs("\"", fp); fputs(patient_JSON->email, fp); fputs("\",\n", fp);
        fputs("    \"disease\":", fp); fputs("\"", fp); fputs(patient_JSON->disease, fp); fputs("\",\n", fp);
        fputs("    \"consult_date\":", fp); fputs("\"", fp); fputs(patient_JSON->consult_data, fp); fputs("\",\n", fp);
        fputs("    \"COVID_19\":", fp); fputs("\"", fp); fputs(patient_JSON->COVID_19, fp); fputs("\",\n", fp);
    fputs("},\0", fp);
    
    fclose(fp);

    return 0;
}
