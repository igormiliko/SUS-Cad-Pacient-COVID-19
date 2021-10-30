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
        if(year % 4 == 0) 
        {
            if(year % 100 == 0)
            {
                if(year % 400 == 0)
                {
                    total_days +=366;
                } else { 
                    total_days +=365; }
            } else{ 
               total_days +=365; }
        }else{ 
            total_days +=365; }
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
    int total_days = 0;
    int ano = 2020;

    ano = calc_days_in_year(ano, 2, 27);

}