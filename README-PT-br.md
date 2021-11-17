# SUS-Cad-Pacient-COVID-19 (susC-1.0.0)
## Trabalho acadêmico para a UNIP, no segundo semestre do curso de analise e desenvolvimento de sistemas.
   O SUS-Cad-Pacient-COVID-19 é um sistema fictício para ajudar o SUS à registrar pacientes 
que foram diagnosticados com COVID-19 ou não, com o principal intuito de registrar o resultado do exame.
   Este programa foi desenvolvido em linguagem C e utiliza duas structs, o usuário que pode 
ser um médico(a) ou um enfermeiro(a) que precisam fazer o cadastro no sistema com o seu 
nome, o número de registro profissional e uma senha.
   A segunda struct é o paciente, que apenas o usuário poderá fazer o registro deste paciente.
O paciente tem um nome, CPF, idade, data de nascimento, email, comorbidade, data do diagnóstico de COVID-19, número de telefone, o resultado de COVID-19 e o seu endereço.
   Após o registro do paciente o sistema irá salvá-lo em um arquivo com extensão .json para 
facilitar a comunicação com outras plataformas e linguagens de programação. Caso o paciente 
se encontre em um grupo de risco e tenha o resultado e COVID-19 positivo será salvo à parte 
em um arquivo chamado "risk" em formato .json, o nome do paciente, idade e CEP para ser 
"enviado" à Secretaria de Saúde e infomá-los sobre a situação do paciente.
   O programa deve ser compilado e executado em sua máquina local. Para compila-lo basta 
abrir a linha de comando e ir até o caminho da pasta do programa e executar o comando "gcc 
main.c -o sc19" que transformará o código fonte em um arquivo binário para ser lido pelo sistema operacional. Para executá-lo basta continuar na linha de comando e estar no local do arquivo e executar o comando "sc19".
   O programa irá abrir com uma interface solicitando o seu cadastramento ou login, apertando 
0 ou 1 respectivamente, após o cadastro você poderá fazer o login e cadastrar um paciente que 
será salvo em um arquivo chamado patient.json.






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
  
