#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct 
{	
		char nome[60];
		char sex[2];
		char cpf[14];
		char phone_number[14];
		int age;
		char born_date[11];
		char email[120];
		char disease[20];
		float height;
		float weight;
		char cns[40];
		char consult_data[11];
		char COVID_19[2];
		char last_week_contact[2];
} Patient;


int to_JSON(Patient *patient_JSON) {
    char age[2]; sprintf(age, "%d", patient_JSON->age);
    char height[5]; sprintf(height, "%.2f", patient_JSON->height);
    char weight[5]; sprintf(weight, "%.2f", patient_JSON->weight);

  FILE *fp;
    fp = fopen("patient.txt","a+");
    if(fp == NULL)
        printf("Erro ao abrir o arquivo! \n\n");


    fputs("\n{\n", fp);
        fputs("    \"name\":", fp); fputs("\"", fp); fputs(patient_JSON->nome, fp); fputs("\",\n", fp);
        fputs("    \"sex\":", fp); fputs("\"", fp); fputs(patient_JSON->sex, fp); fputs("\",\n", fp);
        fputs("    \"CPF\":", fp); fputs("\"", fp); fputs(patient_JSON->cpf, fp); fputs("\",\n", fp);
        fputs("    \"phone_number\":", fp); fputs("\"", fp); fputs(patient_JSON->phone_number, fp); fputs("\",\n", fp);
        fputs("    \"age\":", fp); fputs("\"", fp); fputs(age, fp); fputs("\",\n", fp);
        fputs("    \"born_date\":", fp); fputs("\"", fp); fputs(patient_JSON->born_date, fp); fputs("\",\n", fp);
        fputs("    \"email\":", fp); fputs("\"", fp); fputs(patient_JSON->email, fp); fputs("\",\n", fp);
        fputs("    \"disease\":", fp); fputs("\"", fp); fputs(patient_JSON->disease, fp); fputs("\",\n", fp);
        fputs("    \"height\":", fp); fputs("\"", fp); fputs(height, fp); fputs("\",\n", fp);
        fputs("    \"weight\":", fp); fputs("\"", fp); fputs(weight, fp); fputs("\",\n", fp);
        fputs("    \"cns\":", fp); fputs("\"", fp); fputs(patient_JSON->cns, fp); fputs("\",\n", fp);
        fputs("    \"consult_date\":", fp); fputs("\"", fp); fputs(patient_JSON->consult_data, fp); fputs("\",\n", fp);
        fputs("    \"COVID_19\":", fp); fputs("\"", fp); fputs(patient_JSON->COVID_19, fp); fputs("\",\n", fp);
        fputs("    \"last_week_contact\":", fp); fputs("\"", fp); fputs(patient_JSON->last_week_contact, fp); fputs("\",\n", fp);
    fputs("},\0", fp);
    
    fclose(fp);

    return 0;
}
