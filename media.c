#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pwd.h>
#include <math.h>
#include <unistd.h>
#include <ctype.h>
#include <malloc.h>
#include <time.h>



int calc_days_in_year(int year, int month, int day)
{
    int total_days = 0;

// Loop para verificar se o ano é bissexto ou normal e adicioná-lo
// ao total de dias para ter uma precisão melhor na hora de calcular
    for(int i = 0; i < year; i++)
    {   
        if(i % 4 == 0) 
        {
            if(i % 100 == 0)
            {
                if(i % 400 == 0)
                {
                    total_days +=366;
                    
                }
                else { 
                    total_days +=365;
                }
            }
            else{ 
               total_days +=365;
            }
        }
        else{ 
            total_days +=365;
        }
    }

// Adicionando os dias nos meses até o mês anterior
    for(int i = 1; i < month; i++)
    {
        if(month % 2 == 0)
        {
            if(month == 2)
            {
                total_days += 28;
            }
            else
            {
                total_days += 30;
            }
        }
        else
        {
            total_days += 31;
        }
    }

    return total_days;
}




int main(void)
{
    int confirm_cpf = 0;
    do{
        char c = ".";
        char u = "-";
        char cpf[14];

        printf("Data de nascimento:(__/__/__) ");
        scanf("%s", cpf);
        printf("\n");

        char um = cpf[3];
        char dois = cpf[7];
        char tres = cpf[11];        
        
        int len = strlen(cpf);
        
        int right_format = strcmp(&um , &c) == 0 &&
                            strcmp(&dois, &c) == 0 &&
                             strcmp(&tres, &u) == 0 ? 0 : 1;

        printf("Desgraça: %d\n",strcmp("a" , "b"));
        printf("Desgraça: %d\n",strcmp(&dois, &c));
        printf("Desgraça: %d\n",strcmp(&tres, &u));

        confirm_cpf = right_format == 0 && len == 14 ? 0 : 1;
    }while(confirm_cpf == 1);

    printf("Ok\n");

}