#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

struct reg
{
	char nome[40];
	char destino[40];    
	char tel[40];
	char email[40];
	char origem[40];
	char pessoas[40];
	char status;
};

int tamanho(FILE *);
void cadastrar(FILE *);
void consultar(FILE *);
void consultar_conta(FILE *arq);
void criar_arquivo_txt(FILE *arq);
void excluir(FILE *);
int PS; //passagem

int main()
{
	setlocale(LC_ALL,"Portuguese");
	int OP,i;
	FILE *arq;

	if ((arq = fopen("dados.dat", "rb+")) == NULL)
	{
		if ((arq = fopen("dados.dat", "wb+")) == NULL)
		{
			printf("\nFalha ao abrir o arquivo!\n");
			system("pause");
		}
	}
	
	do{
		system("CLS");
		printf("============ Passagens ==========\n");
		printf("1.Reservar passagem\n");
		printf("2.Consultar todas as passagens\n");
		printf("3.Consultar passagem\n");
		printf("4.Gerar arquivo dos clientes\n");
		printf("5.Excluir cadastro\n");
		printf("6.Sair\n");
		printf("=================================\n");
		printf("Opção: ");
		scanf("%d%*c", &OP);
		
		switch (OP)
		{
		case 1: //cadastrar novo contato
			cadastrar(arq);
			break;
		case 2: //consultar contato por código
			consultar(arq);
			break;
		case 3: //consultar contato por código
			consultar_conta(arq);
			break;
		case 4:
			criar_arquivo_txt(arq);
			break;
		case 5:
			excluir(arq);
			break;
		case 6:
		  	fclose(arq);		  
		}
	}while(OP != 6);
}

void cadastrar(FILE *arq)
{ 
	reg contato; 
	char confirma;
	contato.status = ' ';
	
	fflush(stdin);
	printf("Reserva de passagem: \n");
	printf("\nNúmero do registro: %d\n", tamanho(arq) +1);
	
	printf("Nome.........................: ");
	gets(contato.nome);
	
	printf("E-mail.......................: ");
	gets(contato.email);
	
	printf("Telefone......................:");
	gets(contato.tel);
	
	printf("Origem........................:");
	gets(contato.origem);
	
	printf("Destino.......................:");
	gets(contato.destino);
	
	printf("Número de pessoa(s)...........:");
	gets(contato.pessoas);
	
	printf("\nConfirma <s/n>:");
	scanf("%c", &confirma);

	if (toupper(confirma) == 'S')
	{
		printf("\n gravando ....\n");
		fseek(arq, 0, SEEK_END);
		fwrite(&contato, sizeof(reg), 1, arq);

	}
}

void consultar(FILE *arq){
	
	reg contato; 
	
	if(contato.status = ' ')
		for(int i=0;i<tamanho(arq);i++)
		{	
			fseek(arq,i*sizeof(reg),SEEK_SET);
			fread(&contato, sizeof(reg), 1, arq);
			
			printf("Passagem número (%d)\n",i);
			printf("Nome: %s\n",contato.nome);
			printf("Email: %s\n",contato.email);
			printf("Telefone: %s\n",contato.tel);
			printf("Origem: %s\n",contato.origem);
			printf("Destino: %s\n",contato.destino);
			printf("Número de pessoas: %s\n",contato.pessoas);
			printf("\n----------------------------------\n");
		}
	else
		printf("\nRegistro excluido! \n");
		
	system("pause");
}

void consultar_conta(FILE *arq){
	
	reg contato; 
	
	do
	{
		system("cls");
		printf("Digite o número da passagem:");
        scanf("%d", &PS);
	}while(PS>tamanho(arq) || PS<0);
	
	fseek(arq,PS*sizeof(reg),SEEK_SET);

	fread(&contato, sizeof(reg), 1, arq);
	
	printf("\n----------------------------------\n");
	printf("Passagem %d\n",PS);
	printf("Nome: %s\n",contato.nome);
	printf("Email: %s\n",contato.email);
	printf("Telefone: %s\n",contato.tel);
	printf("Origem: %s\n",contato.origem);
	printf("Destino: %s\n",contato.destino);
	printf("Número de pessoas: %s\n",contato.pessoas);
	printf("\n----------------------------------\n");
	system("pause");
}

void criar_arquivo_txt(FILE *arq){
	char nome_arquivo[40];
	reg contato; 
	
	system("cls");
	printf("Digite o nome do arquivo: ");
	gets(nome_arquivo);
	
	strcat(nome_arquivo,".txt");
    FILE *arquivo_txt;
    
	arquivo_txt = fopen(nome_arquivo, "w");
	
	if (arquivo_txt == NULL){
		
		printf("\nOcorreu um erro ao criar o arquivo\n");
		system("pause");
		return;
	}
		
	fprintf(arquivo_txt,"================================================================================================================================================================\n");
	fprintf(arquivo_txt,"NOME                          EMAIL                          TELEFONE                      ORIGEM                      DESTINO               PESSOAS     STATUS      ");
	fprintf(arquivo_txt,"\n--------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	
	for(int i=0;i<tamanho(arq);i++){
		
		char numero[10] = {'\0'} ;
		
		itoa(i, numero, 10);
    
			
		fseek(arq,i*sizeof(reg),SEEK_SET);
	
		fread(&contato, sizeof(reg), 1, arq);
		fprintf(arquivo_txt,"%-30s%-30s%-30s%-30s%-25s%-10s -%c\n",contato.nome,contato.email,contato.tel,contato.origem,contato.destino,contato.pessoas,contato.status);
	}
	fprintf(arquivo_txt,"===============================================================================================================================================================");
	fclose(arquivo_txt);
	system("pause");
}

void excluir_conta(FILE *arq){
	char nome_cliente[40];
	reg contato; 
	
	system("cls");
	printf("Digite o nome do cliente: ");
	gets(nome_cliente);
	
	for(int i=0;i<tamanho(arq);i++)
	{	
		fseek(arq,i*sizeof(reg),SEEK_SET);
	
		fread(&contato, sizeof(reg), 1, arq);
		
		if(strcasecmp(nome_cliente,contato.nome))
		{	
			printf("Nome: %s\n",contato.nome);
			printf("Email: %s\n",contato.email);
			printf("Telefone: %s\n",contato.tel);
			printf("Origem: %s\n",contato.origem);
			printf("Destino: %s\n",contato.destino);
			printf("Número de pessoas: %s\n",contato.pessoas);	
		}
	}
}

void excluir(FILE *arq)
{
	reg contato;
	char confirma;
	int nr;

	printf("\nInforme o codigo do registro para excluir\n");
	scanf("%d", &nr);
	if ((nr <= tamanho(arq)) && (nr>0))
	{
		fseek(arq, (nr - 1) * sizeof(reg), SEEK_SET);
		fread(&contato, sizeof(reg), 1, arq);
		if (contato.status == ' ')
		{
			printf("\nNome......:%s", contato.nome);
			printf("\nTelefone..:%s", contato.tel);
			printf("\ne-mail....:%s\n", contato.email);
			printf("\nConfirma a exclusao: <s/n>\n");
			getchar();
			scanf("%c", &confirma);

			if (toupper(confirma) == 'S')
			{
				printf("\nexcluindo...\n\n");
				fseek(arq, (nr - 1) * sizeof(reg), SEEK_SET);
				contato.status = '*';
				fwrite(&contato, sizeof(reg), 1, arq);
			}
		}
	else
		printf("Registro inexistente! \n");
	}
	else
	{
		printf("\nNumero de registro invalido!\n");
	}
	system("pause");
}

int tamanho(FILE *arq)
{
	fseek(arq, 0, SEEK_END);
	return ftell(arq) / sizeof(reg);
}
