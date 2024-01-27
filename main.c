#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <conio.h>
#include <locale.h>
#include <windows.h>
#include<time.h>
#include<stdbool.h>
FILE *ficheiro;

void header ()
{
    system("cls");
    printf( "========================================================================================================\n");
    printf( "                                          SIG / BAI                        \n");
    printf( "========================================================================================================\n\n");
}
void continuar ()
{
    char tecla;
    printf( "\n\tClique qualquer tecla para voltar ao menu: ");
    scanf("%c", &tecla);
    system("cls");
}
int anoA;
void dataA()
{
    time_t tempo=time(NULL);
    struct tm tm=*localtime(&tempo);
    anoA=tm.tm_year+1900;
    printf(" %d/%d/%d\n", tm.tm_mday, tm.tm_mon+01,anoA);

}
struct pessoa
{
    int codCli, tipoCli, telefone, idade;
    char nome[50], dataN[11], di[16];
};
typedef struct pessoa Pessoa;
struct conta
{
    int tipoConta, codCli, numConta;
    char estado[11];
    double saldo;
};
typedef struct conta Conta;
Pessoa cli[10];
Conta cont[10];
int cliCad=0, contCri=0;
bool valDI(char c[], int cli)
{
    int n, verif=0;
    int t = strlen (c);
    if (cli==0)
    {
        if (t==15)
        {
            for (n=0; n<=8; n++)
            {
                if(isdigit(c[n]))
                {
                    verif ++;
                }
            }
            if (verif==9)
            {
                if (c[0]=='0'&& c[1]=='0'&& c[2]!='0')
                {
                    for (n=9; n<=10; n++)
                    {
                        if(isalpha(c[n]))
                        {
                            verif ++;
                        }
                    }
                    if (verif==11)
                    {
                        for (n=11; n<=13; n++)
                        {
                            if(isdigit(c[n]))
                            {
                                verif ++;
                            }
                        }
                        if (verif==14)
                        {
                            return true;
                        }
                        else
                        {
                            return false;
                        }
                    }
                    else
                    {
                        return false;
                    }
                }
                else
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        if(t==11)
        {
            for (n=0; n<=9; n++)
            {
                if(isdigit(c[n]))
                {
                    verif ++;
                }
            }
            if (verif==10)
            {
                if (c[0]=='5')
                {
                    if (c[1]=='4' || c[1]=='1'|| c[1]=='7' || c[1]=='0')
                    {
                        return true;
                    }
                    else
                    {
                        return false;
                    }
                }
                else
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    return true;
}
void mostrarDados(Pessoa p)
{
    system("cls");
    header();
    printf("--------------------------------------- FORMULÁRIO DE CADASTRO ----------------------------------------\n\n");
    if (p.tipoCli==1)
    {
        printf("\tCódigo: %d\n\tTipo de Cliente: %d\n\tNome da Empresa: %s\tNIF: %s", p.codCli, p.tipoCli, p.nome, p.di);
    }
    else
    {
        printf("\tCódigo: %d\n\tTipo de Cliente: %d\n\tNome do Cliente: %s\tBI: %s", p.codCli, p.tipoCli, p.nome, p.di);
    }
}
int valData(int dia, int mes, int ano)
{
    if( ano>1910 && ano<2024)
    {
        if(mes==2)
        {
            if(dia>28  || dia<1)
            {

                if (dia==29)
                {
                    if ((ano% 4==0 && ano%100!=0) || ano%400== 0)
                    {
                        return 1;
                    }
                }
                printf("\n\tDia inserido é inválido, digite novamente\n");
                return 0;

            }

        }
        else
        {
            if( mes==4 || mes==6 || mes==9 || mes==11)
            {
                if (dia<1 || dia>30)
                {
                    printf("\n\tDia inserido é inválido, digite novamente\n");
                    return 0;
                }
            }
            else
            {
                if (mes==1 || mes==3 || mes==5 || mes==7 || mes==8 || mes==10 || mes==12)
                {
                    if (dia>31  || dia<1)
                    {
                        return 0;
                    }
                }
                else
                {
                    printf( "\n\tMes inserido é inválido, digite novamente\n");
                    return 0;
                }
            }
        }
    }
    else
    {
        printf("\n\tO ano de nascimento/Criação desta entidade, torna-o ilegível a ser um cliente, impossivel cadastrar");
        return -1;
    }



    return 1;

}
int valTelefone(int t)
{
    if (t<910000000 || t>999999999)
    {
        if (t<910000000)
        {
            if (t>222000000 && t<222999999)
            {
                return 0;
            }
            else
            {
                printf("Nao 900000");
                return -1;
            }
        }
        printf("Nao 9999");
        return -1;


    }
    else
    {
        if (t>960000000 && t<989999999 )
        {
            printf("Nao 9666");
            return -1;
        }
        else
        {
            return 0;
        }
    }
    return 0;
}
bool cadastro( Pessoa p)
{
    cli[cliCad]=p;
    cont[cliCad].codCli=p.codCli;
    cont[cliCad].saldo=-1;
    strcpy(cont[cliCad].estado, "Inexistente");
    cliCad++;
    return true;
}
bool listaDeClientes(int opc)

{
    switch (opc)
    {
    case 1:
        printf("\n------------------------------------Lista de Clientes Particulares----------------------------------\n");
        for (int i=0; i<cliCad; i++)
        {
            Pessoa p = cli[i];
            Conta c= cont[i];
            if (cliCad!=0)
            {
                if (p.tipoCli==0)
                {
                    printf("\n\tCódigo do Cliente: %d\n", p.codCli);
                    printf("\tNome do Cliente: %s", p.nome);
                    printf("\tBilhete de Identidade: %s", p.di);
                    printf("\tData de Nascimento: %s", p.dataN);
                    printf("\tTelefone: %d\n", p.telefone);

                    if (c.codCli==p.codCli)
                    {
                        if (c.numConta!=0)
                        {
                            printf("\tNúmero da Conta: %d\n", c.numConta);
                            printf("\tSaldo: %.2f\n", c.saldo);
                            printf("\tEstado: %s\n\n", c.estado);

                        }
                        else
                        {
                            printf("\tNúmero de Conta: Nenhuma Conta associada\n\n");
                        }
                    }
                    printf("----------------------------------------------------------------------------------------------------------");
                }
            }
        }

        break;
    case 2:
        printf("\n------------------------------------Lista de Clientes Empresariais----------------------------------\n");
        for (int i=0; i<cliCad; i++)
        {
            Pessoa p = cli[i];
            Conta c= cont[i];
            if (cliCad!=0)
            {
                if (p.tipoCli==1)
                {
                    printf("\n\tCódigo: %d\n", p.codCli);
                    printf("\tNome da empresa: %s", p.nome);
                    printf("\tNIF: %s", p.di);
                    printf("\tData de Criação: %s", p.dataN);
                    printf("\n\tTelefone: %d\n", p.telefone);
                    if (c.codCli==p.codCli)
                    {
                        if (c.numConta!=0)
                        {
                            printf("\tNúmero da Conta: %d\n", c.numConta);
                            printf("\tSaldo: %.2f\n", c.saldo);
                            printf("\tEstado: %s\n\n", c.estado);

                        }
                        else
                        {
                            printf("\tNúmero de Conta: Nenhuma Conta associada\n\n");
                        }
                    }
                    printf("----------------------------------------------------------------------------------------------------------");
                }
            }
        }
        break;
    case 3:
        for (int i=0; i<cliCad; i++)
        {
            Pessoa p = cli[i];
            Conta c= cont[i];
            if (cliCad!=0)
            {
                if (p.tipoCli==0)
                {

                    printf("\n\tCódigo do Cliente: %d\n", p.codCli);
                    printf("\tNome do Cliente: %s", p.nome);
                    printf("\tBilhete de Identidade: %s", p.di);
                    printf("\tData de Nascimento: %s", p.dataN);
                    printf("\n\tTelefone: %d\n", p.telefone);
                }
                else
                {
                    printf("\n\tCódigo: %d\n", p.codCli);
                    printf("\tNome da empresa: %s", p.nome);
                    printf("\tNIF: %s", p.di);
                    printf("\tData de Criação: %s", p.dataN);
                    printf("\n\tTelefone: %d\n", p.telefone);
                }
                if (c.codCli==p.codCli)
                {
                    if (c.numConta!=0)
                    {
                        printf("\tNúmero da Conta: %d\n", c.numConta);
                        printf("\tSaldo: %.2f\n", c.saldo);
                        printf("\tEstado: %s\n\n", c.estado);

                    }
                    else
                    {
                        printf("\tNúmero de Conta: Nenhuma Conta associada\n\n");
                    }
                }
                printf("----------------------------------------------------------------------------------------------------------");
            }
        }


        break;
    default:
        printf("\n\tEscolha Inválida");
    }
    return true;
}
int pesquisarClientes(int codCli)
{
    int posicao;
    for (posicao=0; posicao<=cliCad; posicao++)
    {
        Pessoa p = cli[posicao];
        if (p.codCli==codCli)
        {
            return posicao;
        }
    }
    return -1;
}
bool aberturaDeConta(Pessoa p, int tipoConta)
{
    Conta c= cont[pesquisarClientes(p.codCli)];
    if(p.tipoCli==tipoConta)
    {
        c.numConta=1000+p.codCli;
        c.tipoConta=p.tipoCli;
        c.saldo=0;
        strcat(c.estado, "Activa");
        cont[pesquisarClientes(p.codCli)]=c;
    }
    else
    {
        printf("\tO Tipo de conta selecionado não é compativel ao tipo de cliente");
        sleep(2);
        return false;

    }
    return true;
}
int pesquisarConta(int num)
{
    int posicao, nenhuma=0;
    for (posicao=0; posicao<cliCad; posicao++)
    {
        Conta c=cont[posicao];
        if (c.numConta == num)
        {
            return posicao;
        }
        else
        {
            if (c.numConta==0)
            {
                nenhuma++;
            }
            if (nenhuma==cliCad)
            {
                return -2;
            }
        }
    }


    return -1;
}
bool depositar (int num, float s)
{
    int i= pesquisarConta(num);
    if (cont[i].saldo==-1)
    {
        cont[i].saldo=0;
    }
    cont[i].saldo=cont[i].saldo + s;
    printf("\n---------------------------------------------------------------------------\n");
    printf("\n\tOBS: Depósito feito com sucesso!\n");
    sleep(2);
    return true;
}
bool levantar (int num, float s)
{
    int i= pesquisarConta(num);
    if (cont[i].saldo==-1)
    {
        cont[i].saldo=0;
    }
    if (cont[i].saldo>s )
    {
        cont[i].saldo=cont[i].saldo - s;
        printf("\n---------------------------------------------------------------------------\n");
        printf("\n\tOBS: Depósito feito com sucesso!\n");
        sleep(2);
    }
    else
    {
        printf("\n---------------------------------------------------------------------------\n");
        printf("\n\tOBS: Impossivel realizar Levantamento, saldo insuficiente!\n");
        sleep(2);
    }

    return true;
}
float consultar(int n)
{
    int i= pesquisarConta(n);
    printf("\n-----------------------------------------------------------------------------------------------\n");
    return cont[i].saldo;

}
bool transferencia(int c1, int c2, float s)
{
    int i = pesquisarConta(c1);
    int j = pesquisarConta(c2);


    if (cont[i].saldo>=s && cont[i].saldo!=0)
    {
        cont[i].saldo=cont[i].saldo - s;
        cont[j].saldo=cont[j].saldo + s;
        printf("\n---------------------------------------------------------\n");
        printf ("\n\tOBS: Transferência feita com sucesso!\n");
        sleep(2);
    }
    else
    {
        printf("\n---------------------------------------------------------\n");
        printf ("\n\tOBS: Impossivel realizar transferência, saldo insuficiente!\n");
        sleep(2);
    }
    return true;
} void backup (){

 	ficheiro = fopen("bdtes.txt","w");
 	if (ficheiro==NULL) {
 		printf(" Nao foi possivel abrir ficheiro ERRO\n");
	 }
	 else{
        int ln;
	 	for (int i=0; i<=cliCad-1; i++){
	 		 Pessoa p;
	 		 Conta c;
	 		 p=cli[i];
	 		 c=cont[i];
              ln = strlen(p.nome) - 1;
            if (p.nome[ln] == '\n')
            p.nome[ln] = '\0';
             ln = strlen(p.dataN) - 1;
            if (p.dataN[ln] == '\n')
            p.dataN[ln] = '\0';
             ln = strlen(p.di) - 1;
            if (p.di[ln] == '\n')
            p.di[ln] = '\0';
	 		fprintf(ficheiro,"%d;%d;%s;%s;%s;%d;%d;%d;%f;%s",p.codCli,p.tipoCli,p.nome,p.di,p.dataN,p.idade,p.telefone,c.numConta,c.saldo,c.estado);
			fprintf(ficheiro,"\n");
        }

		 fclose(ficheiro);
	 }
 }

int main()
{
    setlocale(LC_ALL, "portuguese");
    Pessoa p;
    dataA();
    int opcao,opc, escolha, codCli, retorno, dia, mes, ano, erro;
    char d[5], m[6], a[6];
    bool rtrno;
    system("color f0");
    system("cursorColor 3");

    do
    {
        header();
        printf ("\t1-Cadastrar Cliente\n\t2-Listar Clientes\n\t3-Abertura de Conta\n\t4-Depositar dinheiro\n\t5-Levantar dinheiro\n\t6-Consultar Saldo\n\t7-Transferir Dinheiro\n\t8-Actualizar dados do Cliente\n\t9-Sair\n\n");
        printf("\tOpção: ");
        scanf("%d", &opcao);
        switch (opcao)
        {
        case 1:
            p.codCli=cliCad+1;
            system("csl");
            header();
            printf("\t1-Cadastrar Cliente\n\t2-Voltar ao Menu\n\tOpção: ");
            scanf("%d", &escolha);
            if  (escolha ==1)
            {
                printf("\n\tProcessando...");
                sleep(1.5);
                do
                {
                    system("csl");
                    header();
                    printf("--------------------------------------- FORMULÁRIO DE CADASTRO ----------------------------------------\n\n");
                    printf( "\tSelecione o tipo de cliente com base nas opções abaixo: \n\n\t0-Particular\n\t1-Empresarial\n\n\tOpção: ");
                    scanf("%d", &p.tipoCli);
                    fflush(stdin);
                    switch (p.tipoCli)
                    {
                    case 0:
                        system("csl");
                        header();
                        printf("--------------------------------------- FORMULÁRIO DE CADASTRO ----------------------------------------\n\n");
                        printf("\tCódigo: %d\n\tTipo de Cliente: %d\n\tNome: ", p.codCli, p.tipoCli);
                        fgets(p.nome, 60, stdin);
                        do
                        {
                            system("csl");
                            header();
                            printf("--------------------------------------- FORMULÁRIO DE CADASTRO ----------------------------------------\n\n");
                            printf("\tCódigo: %d\n\tTipo de Cliente: %d\n\tNome Completo: %s ", p.codCli, p.tipoCli, p.nome);
                            printf("\tBI: ");
                            fgets(p.di, 16, stdin);
                            rtrno=valDI(p.di, p.tipoCli);
                            if (rtrno==false)
                            {
                                printf("\n\tBI inválido, digite novamente.");
                                sleep(2);
                            }
                            int i;
                            for (i=0; i<=cliCad; i++)
                            {
                                Pessoa t = cli[i];
                                if (strcmp(t.di,p.di)==0)
                                {
                                    printf("\n\tJá existe um Cliente com esse BI.\n\t1-Redigitar\n\t2-Cancelar Cadastro\n\tOpção: ");
                                    scanf("%d", &opc);
                                    fflush(stdin);
                                    switch (opc)
                                    {
                                    case 1:
                                        rtrno=false;
                                        break;
                                    case 2:
                                        printf ("\n\tCadastro Cancelado!");
                                        sleep(2);
                                        break;
                                    default:
                                        printf("Opção Iválida");
                                    }

                                }
                            }
                        }
                        while(rtrno==false);
                        if (opc!=2)
                        {
                            do
                            {
                                do
                                {
                                    mostrarDados(p);
                                    printf("\tData de Nascimento (dd/mm/aaaa): ");
                                    scanf("%d", &dia);
                                    fflush(stdin);
                                    mostrarDados(p);
                                    printf("\tData de Nascimento (dd/mm/aaaa): %d/", dia);
                                    scanf("%d", &mes);
                                    fflush(stdin);
                                    mostrarDados(p);
                                    printf("\tData de Nascimento (dd/mm/aaaa): %d/%d/", dia, mes);
                                    scanf("%d", &ano);
                                    fflush(stdin);
                                    rtrno = (dia>99 || dia<1 || mes>99 || mes<1 || ano>9999 || ano<1000);
                                    if (rtrno==true)
                                    {
                                        printf("Formato de Data Inválido, tente novamente");
                                        sleep(3);

                                    }
                                }
                                while(rtrno==true);
                                erro=valData(dia, mes, ano);
                                if (erro==0)
                                {
                                    sleep(2);
                                }
                            }
                            while(erro==0);
                            if (erro!=0 && erro!=-1)
                            {
                                p.idade = (anoA-ano);
                                sprintf(d, "%d", dia);
                                sprintf(m, "%d", mes);
                                sprintf(a, "%d", ano);
                                strcat(d,"/");
                                strcat(d,m);
                                strcat(d,"/");
                                strcat(d,a);
                                strcpy(p.dataN,d);
                            }
                            do
                            {
                                mostrarDados(p);
                                printf("\tData de Nascimento: %s", p.dataN);
                                printf("\n\tTelefone: ");
                                scanf("%d", &p.telefone);
                                fflush(stdin);
                                erro=valTelefone(p.telefone);
                                if (erro==-1)
                                {
                                    printf("\n\tContacto Inválido, digite novamente");
                                    sleep(2);
                                }
                            }
                            while(erro==-1);

                            cadastro(p);
                            printf("-------------------------------------------------------------------------------------------------------\n\n");
                            printf("\tCliente Cadastrado com sucesso! \n");
                            continuar();
                        }

                        break;
                    case 1:
                        system("csl");
                        header();
                        printf("--------------------------------------- FORMULÁRIO DE CADASTRO ----------------------------------------\n\n");
                        printf("\tCódigo: %d\n\tTipo de Cliente: %d\n\tNome da Empresa: ", p.codCli, p.tipoCli);
                        fgets(p.nome, 60, stdin);
                        do
                        {
                            system("csl");
                            header();
                            printf("--------------------------------------- FORMULÁRIO DE CADASTRO ----------------------------------------\n\n");
                            printf("\tCódigo: %d\n\tTipo de Cliente: %d\n\tNome da Empresa: %s ", p.codCli, p.tipoCli, p.nome);
                            printf("\tNIF: ");
                            fgets(p.di, 16, stdin);
                            rtrno=valDI(p.di, p.tipoCli);
                            if (rtrno==false)
                            {
                                printf("\n\tNIF inválido, digite novamente.");
                                sleep(2);
                            }
                            int i;
                            for (i=0; i<=cliCad; i++)
                            {
                                Pessoa t = cli[i];
                                if (strcmp(t.di,p.di)==0)
                                {
                                    printf("\n\tJá existe um Cliente com esse NIF.\n\t1-Redigitar\n\t2-Cancelar Cadastro\n\tOpção: ");
                                    scanf("%d", &opc);
                                    fflush(stdin);
                                    switch (opc)
                                    {
                                    case 1:
                                        rtrno=false;
                                        break;
                                    case 2:
                                        printf ("\n\tCadastro Cancelado!");
                                        sleep(2);
                                        break;
                                    default:
                                        printf("Opção Iválida");
                                    }

                                }
                            }
                        }
                        while(rtrno==false);
                        if (opc!=2)
                        {
                            do
                            {
                                do
                                {
                                    mostrarDados(p);
                                    printf("\tData de Criação (dd/mm/aaaa): ");
                                    scanf("%d", &dia);
                                    fflush(stdin);
                                    mostrarDados(p);
                                    printf("\tData de Criação (dd/mm/aaaa): %d/", dia);
                                    scanf("%d", &mes);
                                    fflush(stdin);
                                    mostrarDados(p);
                                    printf("\tData de Criação (dd/mm/aaaa): %d/%d/", dia, mes);
                                    scanf("%d", &ano);
                                    fflush(stdin);
                                    rtrno = (dia>99 || dia<1 || mes>99 || mes<1 || ano>9999 || ano<1000);
                                    if (rtrno==true)
                                    {
                                        printf("Formato de Data Inválido, tente novamente");
                                        sleep(3);

                                    }
                                }
                                while(rtrno==true);
                                erro=valData(dia, mes, ano);
                                if (erro==0)
                                {
                                    sleep(2);
                                }
                            }
                            while(erro==0);
                            if (erro!=0 && erro!=-1)
                            {
                                p.idade = (anoA-ano);
                                sprintf(d, "%d", dia);
                                sprintf(m, "%d", mes);
                                sprintf(a, "%d", ano);
                                strcat(d,"/");
                                strcat(d,m);
                                strcat(d,"/");
                                strcat(d,a);
                                strcpy(p.dataN,d);
                            }
                            do
                            {
                                mostrarDados(p);
                                printf("\tData de Criação: %s", p.dataN);
                                printf("\n\tTelefone: ");
                                scanf("%d", &p.telefone);
                                fflush(stdin);
                                erro=valTelefone(p.telefone);
                                if (erro==-1)
                                {
                                    printf("\n\tContacto Inválido, digite novamente");
                                    sleep(2);
                                }
                            }
                            while(erro==-1);
                            cadastro(p);
                            printf("-------------------------------------------------------------------------------------------------------\n\n");
                            printf("\tCliente Cadastrado com sucesso! \n");
                            continuar();
                        }
                        break;
                    default:
                        printf("\tEscolha um tipo de Cliente Válido.");
                        sleep(2);
                        printf("%d", p.tipoCli);
                    }
                }
                while(p.tipoCli!=0 && p.tipoCli !=1);

            }
            else
            {
                printf("\n\tVoltando...");
                sleep(1.5);
            }
            break;
        case 2:
            system("csl");
            header();
            printf("\t1-Listar Clientes\n\t2-Voltar ao Menu\n\tOpção: ");
            scanf("%d", &escolha);
            fflush(stdin);
            if  (escolha==1)
            {
                printf("\n\tProcessando...");
                sleep(1.5);
                system("csl");
                header();
                printf("Data: ");
                dataA();
                printf("-------------------------------------------------------------------------------------------------------------\n");
                if (cliCad==0)
                {
                    printf("\n\tNão Existem Clientes cadastrados ainda.\n\n");
                    printf("----------------------------------------------------------------------------------------------------------");
                    continuar();
                    continue;

                }
                else
                {
                    printf("\n\t1-Listar Clientes Particulares\n\t2-Listar Clientes Empresariais\n\t3-Listar todos os Clientes\n\tOpção: ");
                    int choice;
                    scanf("%d", &choice);
                    fflush(stdin);
                    system("csl");
                    header();
                    printf("Data: ");
                    dataA();
                    printf("-------------------------------------------------------------------------------------------------------------\n");
                    listaDeClientes(choice);

                }

                continuar();


            }
            else
            {
                printf("\n\tVoltando...");
                sleep(1.5);
            }
            break;
        case 3:
            system("csl");
            header();
            printf("\t1-Abertura de Conta\n\t2-Bloquear Conta\n\t3-Voltar ao Menu\n\tOpção: ");
            scanf("%d", &escolha);
            fflush(stdin);
            int  opc, tent=0;
            if  (escolha==1)
            {
                printf("\n\tProcessando...");
                sleep(1.5);
                do
                {
                    system("csl");
                    header();
                    printf("--------------------------------------- Abertura de Conta -----------------------------------\n");
                    if (cliCad==0)
                    {
                        printf("\n\tVocê precisa cadastrar Clientes para abrir uma conta.\n\n");
                        printf("------------------------------------------------------------------------------------------------------");
                        continue;
                    }
                    printf("\tDigite o Código do Cliente que pretende atribuir a conta: \n\tCódigo do Cliente: ");
                    scanf("%d", &codCli);
                    fflush(stdin);
                    pesquisarClientes(codCli);
                    retorno=pesquisarClientes(codCli);
                    if (retorno ==-1)
                    {
                        tent++;
                        printf("----------------------------------------------------------------------------------------------------------");
                        if (tent<=2)
                        {
                            printf("\n\tCliente não encontrado.\n\tDeseja sair desta página ou continuar a tentar?\n\t1- Sair da Página\n\t2- Continuar a Tentar");
                            scanf("%d", &opc);
                            fflush(stdin);
                            switch (opc)
                            {
                            case 1:
                                continue;
                                break;
                            case 2:
                                break;
                            default:
                                printf("\n\tDigitou uma opção inválida, consideramos que deseja voltar.");
                            }
                        }
                    }
                    else
                    {
                        p=cli[retorno];
                        bool ab;
                        int e;
                        if (cont[retorno].saldo!=-1)
                        {
                            printf("\n\tCliente já possui uma conta.\n\tDeseja sair desta página ou continuar a tentar?\n\t1- Sair da Página\n\t2- Continuar a Tentar");
                            scanf("%d", &opc);
                            fflush(stdin);
                            switch (opc)
                            {
                            case 1:
                                continue;
                                break;
                            case 2:
                                break;
                            default:
                                printf("\n\tDigitou uma opção inválida, consideramos que deseja voltar.");
                            }
                        }
                        else
                        {
                            do
                            {
                                header();
                                printf("-------------------------------------Abertura de conta----------------------------------------------\n");
                                printf("\tCódigo do Cliente: %d\n\tNome: %s ", p.codCli, p.nome);
                                printf("\n\tTem certeza de que este é o cliente que procura?\n\t1-SIM\n\t2-Não: ");
                                scanf("%d", &e );
                                fflush(stdin);
                                switch(e)
                                {
                                case 2:

                                    break;
                                case 1:
                                    printf("----------------------------------------------------------------------------------------------------\n\n");
                                    printf("\n\tSelecione o tipo de Conta: \n\t0-Particular\n\t1-Empresarial: \n\tOpção: ");
                                    scanf("%d", &codCli);
                                    fflush(stdin);
                                    ab= aberturaDeConta(p, codCli);
                                    break;

                                default:
                                    printf("Opção inválida");
                                    sleep(2);
                                }


                            }
                            while(ab==false && e!=1 && e!=2 );
                            if (e==1)
                            {
                                Conta c=cont[retorno];
                                contCri++;
                                system("cls");
                                header();
                                printf("------------------------------------------------Abertura de conta---------------------------------------\n");
                                printf("\tCódigo do Cliente: %d\n\tNome: %s\n------------------------------------------------DADOS DA CONTA---------------------------------------\n\n\tNúmero da Conta: %d\n\tSaldo: %.2f\n\tEstado: %s", p.codCli, p.nome,  c.numConta, c.saldo, c.estado);
                                printf("\n-----------------------------------------------------------------------------------------------\n\tConta Aberta Com Sucesso!\n");
                            }
                        }

                    }

                }
                while (retorno==-1 || opc==2);
                continuar();
            }
            else
            {
                if (escolha==2)
                {
                    printf("------------------------------------------------Bloquear Conta---------------------------------------\n");
                    printf("\n\tProcessando...");
                    sleep(1.5);
                    do
                    {
                        system("csl");
                        header();
                        printf("--------------------------------------- Bloquear Conta -----------------------------------\n");
                        if (cliCad==0)
                        {
                            printf("\n\tVocê precisa cadastrar Clientes para bloquear uma conta.\n\n");
                            printf("------------------------------------------------------------------------------------------------------");
                            continue;
                        }
                        printf("\tDigite o Código do proprietário da conta a bloquear: \n\tCódigo do Cliente: ");
                        scanf("%d", &codCli);
                        fflush(stdin);
                        pesquisarClientes(codCli);
                        retorno=pesquisarClientes(codCli);
                        if (retorno ==-1)
                        {
                            tent++;
                            printf("----------------------------------------------------------------------------------------------------------");
                            if (tent<=2)
                            {
                                printf("\n\tCliente não encontrado.\n\tDeseja sair desta página ou continuar a tentar?\n\t1- Sair da Página\n\t2- Continuar a Tentar");
                                scanf("%d", &opc);
                                fflush(stdin);
                                switch (opc)
                                {
                                case 1:
                                    continue;
                                    break;
                                case 2:
                                    break;
                                default:
                                    printf("\n\tDigitou uma opção inválida, consideramos que deseja voltar.");
                                }
                            }
                        }
                        else
                        {
                            p=cli[retorno];
                            int e;
                            if (cont[retorno].saldo!=-1)
                            {



                                if (strcmp(cont[retorno].estado, "Bloqueada")==0)
                                {
                                    header();
                                    printf("-------------------------------------Bloqueio de Conta----------------------------------------------\n");
                                    printf("\tCódigo do Cliente: %d\n\tNome: %s ", p.codCli, p.nome);
                                    printf("\n\tEsta conta já se encontra Bloqueada. Deseja Desbloquear?\n\t1-SIM\n\t2-Não");
                                    scanf("%d", &opc);
                                    fflush(stdin);
                                    switch (opc)
                                    {
                                    case 1:
                                        strcpy(cont[retorno].estado, "Activa");
                                        break;
                                    case 2:
                                        break;
                                    default:
                                        printf("\n\tDigitou uma opção inválida, consideramos que deseja voltar.");
                                    }
                                }
                                else
                                {

                                    do
                                    {
                                        header();
                                        printf("-------------------------------------Bloqueio de Conta----------------------------------------------\n");
                                        printf("\tCódigo do Cliente: %d\n\tNome: %s ", p.codCli, p.nome);
                                        printf("\n\tTem certeza de que deseja bloquear este cliente?\n\t1-SIM\n\t2-Não: ");
                                        scanf("%d", &e );
                                        fflush(stdin);
                                        switch(e)
                                        {
                                        case 2:

                                            break;
                                        case 1:
                                            printf("----------------------------------------------------------------------------------------------------\n\n");
                                            strcpy(cont[retorno].estado, "Bloqueada");
                                            break;

                                        default:
                                            printf("Opção inválida");
                                            sleep(2);
                                        }


                                    }
                                    while( e!=1 && e!=2 );
                                    if (e==1)
                                    {

                                        printf("\n-----------------------------------------------------------------------------------------------\n\tConta Bloqueada Com Sucesso!\n");
                                    }
                                }
                            }
                            else
                            {
                                printf("\n\tNenhuma Conta associada à esse cliente.\n\n");
                                printf("------------------------------------------------------------------------------------------------------");

                            }

                        }

                    }
                    while (retorno==-1 && opc==1);
                    continuar();



                }
                else
                {
                    printf("\n\tVoltando...");
                    sleep(1.5);
                }

            }
            break;
        case 4:
            system("cls");
            header();
            int num;
            float saldo;
            printf("------------------------------------------------Depósito Bancário---------------------------------------\n");
            if (contCri==0)
            {
                printf("\n\tNenhuma Conta Criada!");
                sleep(2);
            }
            else
            {
                do
                {
                    printf("------------------------------------------------Depósito Bancário---------------------------------------\n");
                    system("cls");
                    header();
                    printf("\n\tNúmero da Conta a depositar: ");
                    scanf("%d", &num);
                    fflush(stdin);
                    retorno=pesquisarConta(num);
                    if (retorno==-1)
                    {
                        printf("\n\tConta não Encontrada.\n\t1-Continuar a tentar\n\t2-Sair desta Página");
                        scanf("%d", &opc);
                        fflush(stdin);
                        switch(opc)
                        {
                        case 1:
                            break;
                        case 2:
                            printf("Depósito Cancelado.");
                            break;
                        default:
                            printf("Opçao errada");
                        }
                    }
                    else
                    {

                        if (strcmp(cont[retorno].estado, "Bloqueada")==0)
                        {
                            printf("\n\tConta Bloqueada, e não ser movimentada. ");
                            sleep(2);
                        }
                        else
                        {

                            do
                            {

                                printf("\n\tValor a depositar: ");
                                scanf("%f", &saldo);
                                fflush(stdin);
                                if (saldo>0)
                                {
                                    rtrno= depositar (num, saldo);
                                    if (rtrno==false)
                                    {
                                        printf("\n\tDepósito não pode ser efectuado!");
                                        sleep(2);
                                    }
                                }
                                else
                                {
                                    printf("\n\tDigite uma quantia Válida.");
                                    sleep(2);
                                }
                            }
                            while(saldo<0);
                        }
                    }
                }
                while(retorno==-1 && opc==1);

            }
            break;
        case 5:
            system("cls");
            header();
            printf("------------------------------------------------Levantar Dinheiro---------------------------------------\n");
            if (contCri==0)
            {
                printf("\n\tNenhuma Conta Criada!");
                sleep(2);
            }
            else
            {
                do
                {
                    printf("------------------------------------------------Levantar Dinheiro---------------------------------------\n");
                    system("cls");
                    header();
                    printf("\n\tNúmero da Conta a retirar valores: ");
                    scanf("%d", &num);
                    fflush(stdin);
                    retorno=pesquisarConta(num);
                    if (retorno==-1)
                    {
                        printf("\n\tConta não Encontrada.\n\t1-Continuar a tentar\n\t2-Sair desta Página");
                        scanf("%d", &opc);
                        fflush(stdin);
                        switch(opc)
                        {
                        case 1:
                            break;
                        case 2:
                            printf("Levantamento Cancelado.");
                            break;
                        default:
                            printf("Opçao errada");
                        }
                    }
                    else
                    {
                        if (strcmp(cont[retorno].estado, "Bloqueada")==0)
                        {
                            printf("\n\tConta Bloqueada, e não ser movimentada. ");
                        }
                        else
                        {
                            printf("\n\tValor a Levantar: ");
                            scanf("%f", &saldo);
                            fflush(stdin);
                            if (saldo>0)
                            {
                                rtrno= levantar (num, saldo);
                                if (rtrno==false)
                                {
                                    printf("\n\tLevantamento não pode ser efectuado!");
                                    sleep(2);
                                }
                            }
                            else
                            {
                                printf("\n\tDigite uma quantia Válida.");
                                sleep(2);
                                opc=1;
                            }
                        }
                    }
                }
                while(retorno==-1 && opc==1);

            }
            break;
        case 6:
            system("cls");
            header();
            printf("------------------------------------------------Consulta de Saldo---------------------------------------\n");
            if (contCri==0)
            {
                printf("\n\tNenhuma Conta Criada!");
                sleep(2);
            }
            else
            {
                do
                {
                    printf("--------------------------------------------Consulta de Saldo-------------------------------------------\n");
                    system("cls");
                    header();
                    printf("\n\tNúmero da Conta a consultar: ");
                    scanf("%d", &num);
                    fflush(stdin);
                    retorno=pesquisarConta(num);
                    if (retorno==-1)
                    {
                        printf("\n\tConta não Encontrada.\n\t1-Continuar a tentar\n\t2-Sair desta Página");
                        scanf("%d", &opc);
                        fflush(stdin);
                        switch(opc)
                        {
                        case 1:
                            break;
                        case 2:
                            printf("Consulta Cancelada.");
                            break;
                        default:
                            printf("Opçao errada, saindo...");
                            sleep(2);

                        }
                    }
                    else
                    {
                        saldo=consultar(num);
                        printf("\n\tSaldo Disponível: %.2f", saldo );
                    }
                }
                while(retorno==-1 && opc==1);
            }
            continuar();
            break;
        case 7:
            system("cls");
            int cRet, cRec;
            header();
            printf("------------------------------------------------Transferir Dinheiro---------------------------------------\n");
            if (contCri==0)
            {
                printf("\n\tNenhuma Conta Criada!");
                sleep(2);
            }
            else
            {
                do
                {
                    printf("------------------------------------------------Transferir Dinheiro---------------------------------------\n");
                    system("cls");
                    header();
                    printf("\n\tNúmero da Conta a retirar valores: ");
                    scanf("%d", &cRet);
                    fflush(stdin);
                    retorno=pesquisarConta(cRet);
                    if (retorno==-1)
                    {
                        printf("\n\tConta não Encontrada.\n\t1-Continuar a tentar\n\t2-Sair desta Página");
                        scanf("%d", &opc);
                        fflush(stdin);
                        switch(opc)
                        {
                        case 1:
                            break;
                        case 2:
                            printf("Transferência Cancelada.");
                            break;
                        default:
                            printf("Opçao errada");
                        }
                    }
                    else
                    {
                        if (opc==1)
                             printf("Opçao errada");
                        {
                            if (strcmp(cont[retorno].estado, "Bloqueada")==0)
                            {
                                printf("\n\tConta Bloqueada, e não ser movimentada. ");
                                sleep(2);
                            }
                            else
                            {
                                do
                                {
                                    printf("\n\tNúmero da Conta a receber valores: ");
                                    scanf("%d", &cRec);
                                    fflush(stdin);
                                    retorno=pesquisarConta(cRec);
                                    if (retorno==-1)
                                    {
                                        printf("\n\tConta não Encontrada.\n\t1-Continuar a tentar\n\t2-Sair desta Página");
                                        scanf("%d", &opc);
                                        fflush(stdin);
                                        switch(opc)
                                        {
                                        case 1:
                                            break;
                                        case 2:
                                            printf("Transferência Cancelada.");
                                            break;
                                        default:
                                            printf("Opçao errada");
                                        }

                                    }
                                    else
                                    {
                                        if (opc==1)
                                        {
                                            if (strcmp(cont[retorno].estado, "Bloqueada")==0)
                                            {
                                                printf("\n\tConta Bloqueada, e não ser movimentada. ");
                                                sleep(2);
                                            }
                                            else
                                            {
                                                do
                                                {
                                                    printf("\n\tValor a transferir: ");
                                                    scanf("%f", &saldo);
                                                    fflush(stdin);
                                                    if (saldo>0)
                                                    {
                                                        rtrno= transferencia (cRet, cRec, saldo);
                                                        if (rtrno==false)
                                                        {

                                                            printf("\n\t não pode ser efectuado!");
                                                            sleep(2);
                                                        }
                                                    }
                                                    else
                                                    {
                                                        printf("\n\tDigite uma quantia Válida.");
                                                        sleep(2);
                                                    }
                                                }
                                                while(saldo<0);
                                            }
                                        }
                                    }
                                }
                                while (opc!=2 && retorno==-1);
                            }
                        }
                    }
                }
                while(retorno==-1 && opc!=2);
            }
            break;
        case 8:
            header();
            printf("------------------------------------------------Actualização de Dados--------------------------------------\n");
            opc=1;
            if (cliCad==0)
            {
                printf("\n\tVocê precisa cadastrar Clientes para poder actualizar dados.\n\n");
                printf("------------------------------------------------------------------------------------------------------");
                continue;
            }
            do
            {
                printf("\tDigite o Código do Cliente que pretende actualizar os seus dados: \n\tCódigo do Cliente: ");
                scanf("%d", &codCli);
                fflush(stdin);
                pesquisarClientes(codCli);
                retorno=pesquisarClientes(codCli);
                if (retorno ==-1)
                {
                    tent++;
                    printf("----------------------------------------------------------------------------------------------------------");
                    if (tent<=2)
                    {
                        printf("\n\tCliente não encontrado.\n\tDeseja sair desta página ou continuar a tentar?\n\t1- Sair da Página\n\t2- Continuar a Tentar");
                        scanf("%d", &opc);
                        fflush(stdin);
                        switch (opc)
                        {
                        case 1:
                            continue;
                            break;
                        case 2:
                            break;
                        default:
                            printf("\n\tDigitou uma opção inválida, consideramos que deseja voltar.");
                        }
                    }
                }
                else
                {

                    int e;
                    header();
                    printf("-------------------------------------Actualização dos Dados----------------------------------------------\n");
                    printf("\tCódigo do Cliente: %d\n\tNome: %s ", cli[retorno].codCli, cli[retorno].nome);
                    printf("\n\tTem certeza de que este é o cliente que procura?\n\t1-SIM\n\t2-Não: ");
                    scanf("%d", &e );
                    fflush(stdin);
                    switch(e)
                    {
                    case 2:
                        printf("Voltando para o Menu\n\n");
                        break;
                    case 1:
                        printf("----------------------------------------------------------------------------------------------------\n\n");
                        printf("\n\tSelecione o campo que pretende actualizar: \n\t1-Nome\n\t2-Data de Nascimento\n\t3-BI\n\t4-Telefone: \n\tOpção: ");
                        scanf("%d", &codCli);
                        fflush(stdin);

                        switch(codCli)
                        {
                        case 1:
                            printf("-------------------------------------Actualização dos Dados----------------------------------------------\n");
                            printf("\tCódigo do Cliente: %d\n\tNome Actual: %s ", cli[retorno].codCli, cli[retorno].nome);
                            printf("\tNovo Nome: ");
                            fgets(cli[retorno].nome, 50, stdin);
                            printf("---------------------------------------------------------------------------------------------------------\n");
                            printf("\tNome Actualizado com sucesso!");
                            sleep(2);
                            break;

                        case 2:
                            printf("-------------------------------------Actualização dos Dados----------------------------------------------\n");
                            printf("\tNome: %s\n\tData de Nascimento/Criação actual: %s ", cli[retorno].nome, cli[retorno].dataN);
                            do
                            {
                                do
                                {
                                    header();
                                    printf("-------------------------------------Actualização dos Dados----------------------------------------------\n");
                                    printf("\tNome: %s\n\tData de Nascimento/Criação actual: %s ", cli[retorno].nome, cli[retorno].dataN);
                                    printf("\n\tNova Data de Nascimento/Criação (dd/mm/aaaa): ");
                                    scanf("%d", &dia);
                                    fflush(stdin);
                                    header();
                                    printf("-------------------------------------Actualização dos Dados----------------------------------------------\n");
                                    printf("\tNome: %s\n\tData de Nascimento/Criação actual: %s ", cli[retorno].nome, cli[retorno].dataN);
                                    printf("\n\tNova Data de Nascimento/Criação (dd/mm/aaaa): %d/", dia);
                                    scanf("%d", &mes);
                                    fflush(stdin);
                                    header();
                                    printf("-------------------------------------Actualização dos Dados----------------------------------------------\n");
                                    printf("\tNome: %s\n\tData de Nascimento/Criação actual: %s ", cli[retorno].nome, cli[retorno].dataN);
                                    printf("\n\tNova Data de Nascimento/Criação (dd/mm/aaaa): %d/%d/", dia, mes);
                                    scanf("%d", &ano);
                                    fflush(stdin);
                                    rtrno = (dia>99 || dia<1 || mes>99 || mes<1 || ano>9999 || ano<1000);
                                    if (rtrno==true)
                                    {
                                        printf("\tFormato de Data Inválido, tente novamente");
                                        sleep(3);

                                    }
                                }
                                while(rtrno==true);
                                erro=valData(dia, mes, ano);
                                if (erro==0)
                                {
                                    sleep(2);
                                }
                            }
                            while(erro==0);
                            if (erro!=0 && erro!=-1)
                            {
                                cli[retorno].idade = (anoA-ano);
                                sprintf(d, "%d", dia);
                                sprintf(m, "%d", mes);
                                sprintf(a, "%d", ano);
                                strcat(d,"/");
                                strcat(d,m);
                                strcat(d,"/");
                                strcat(d,a);
                                strcpy(cli[retorno].dataN,d);
                                printf("---------------------------------------------------------------------------------------------------------\n");
                                printf("\tDados Actualizados com sucesso!");
                                sleep(2);
                            }

                            break;
                        case 3:
                            do
                            {
                                system("csl");
                                header();

                                printf("--------------------------------------- FORMULÁRIO DE CADASTRO ----------------------------------------\n\n");
                                printf("\tNome: %s\n\tNIF/BI Actual: %s", cli[retorno].nome, cli[retorno].di);
                                printf("\tNIF: ");
                                fgets(p.di, 16, stdin);
                                rtrno=valDI(p.di, cli[retorno].tipoCli);
                                if (rtrno==false)
                                {
                                    printf("\n\tNIF inválido, digite novamente.");
                                    sleep(2);
                                }
                                int i;
                                for (i=0; i<=cliCad; i++)
                                {
                                    Pessoa t = cli[i];
                                    if (strcmp(t.di,p.di)==0)
                                    {
                                        printf("\n\tJá existe um Cliente com esse NIF.\n\t1-Redigitar\n\t2-Cancelar Actualização\n\tOpção: ");
                                        scanf("%d", &opc);
                                        fflush(stdin);
                                        switch (opc)
                                        {
                                        case 1:
                                            rtrno=false;
                                            break;
                                        case 2:
                                            printf ("\n\tCadastro Actualização!");
                                            sleep(2);
                                            break;
                                        default:
                                            printf("Opção Iválida");
                                        }
                                    }
                                }
                            }
                            while(rtrno==false);
                            strcpy(cli[retorno].di, p.di);
                            continuar();
                            break;
                        case 4:
                            header();
                            do
                            {
                                printf("-------------------------------------Actualização dos Dados----------------------------------------------\n");
                                printf("\tNome: %s\n\tTelefone Actual: %d ", cli[retorno].nome, cli[retorno].telefone);
                                printf("\n\tNovo Telefone: ");
                                scanf("%d", &p.telefone);
                                fflush(stdin);
                                erro=valTelefone(p.telefone);
                                if (erro==-1)
                                {
                                    printf("\n\tContacto Inválido, digite novamente");
                                    sleep(2);
                                }
                            }
                            while(erro==-1);
                            cli[retorno].telefone=p.telefone;
                            printf("---------------------------------------------------------------------------------------------------------\n");
                            printf("\tDados Actualizados com sucesso!");
                            sleep(2);
                            break;
                        default:
                            printf("Opção inválida, voltando para o menu...");
                            sleep(2);
                        }

                        break;
                    default:
                        printf("Opção inválida, voltando para o menu...");
                        sleep(2);
                    }
                }
            }
            while( retorno==-1 && opc!=1);
            break;
        default:
            printf(" ggggg ");
        }
        backup();
    }
    while(opcao!=9);
    return 0;
}
