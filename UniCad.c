/*
No começo do projeto adicionamos as bibliotecas <stdio.h> referentes a entradas e saídas, <string.h> referente à manipulação de strings,
<stdlib.h> referente a alocação de memória e controle de processos, conversões. A biblioteca <locale.h> serve para acentuação de caracteres.
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

/*
Declaração de variáveis e funções: Reservamos espaço em uma matriz de memória para "nome", "email", e "cpf". 
Também declaramos funções como "menu", "cadastro", "pesquisa", "lista", "gravarcsv", "lercsv". Funções de pesquisa específicas para as variáveis declaradas.
*/
char nome[45][65];
char email[45][65];
char cpf[45][14];

void menu();
void cadastro();
void pesquisa();

void pesquisaNome(char nomeP[65]);
void pesquisaCpf(char cpfP[14]);
void pesquisaEmail(char emailP[65]);

void lista();
void gravarcsv();
void lercsv();
void cabecalho(char Titulo[50]);

int main(void) {
setlocale(LC_ALL, "Portuguese_Brazil.1252");
    menu();
}

void delete() {
    FILE *file = fopen("aluno.csv", "r"), *temp = fopen("aluno.csv", "w");
    char line[150], target[50];    
    if (!file || !temp) { 
        printf("Erro ao abrir arquivo!\n");
        return;
    }

    printf("1 - Remover todos os registros \n2 - Remover apenas um registro\n");
    scanf("%s", target);
    if(target == 1){
            while (fgets(line, sizeof(line), file))
            if (!strstr(line, target))
            fputs(line, temp);

            fclose(file);
            fclose(temp);
            remove("aluno.csv");
            rename("temp.csv", "aluno.csv");
            printf("Todos os registros removidos!\n");
    }
    else{
            printf("Em programacao...");
            system("pause");
            menu();    
}}


void cabecalho(char Titulo[50]) {
    system("cls");
    printf("|--------------------------------------------------------------------------------|\n");

    if (strlen(Titulo) == 0) {
        printf("\t\t\tCADASTRO DE ALUNO UniCad 2024\n");
    } else {
        printf(" %sUniCad 2024\n", Titulo);
    }

    printf("|--------------------------------------------------------------------------------|\n");
}

void menu() {
    setlocale(LC_ALL, "Portuguese_Brazil.1252");

    int menu;
    char t[50] = "";
    system("cls");
    cabecalho(t);
    printf("Informe sua opcao: \n\n \t 1 = Cadastro; \n\t 2 = Pesquisa; \n\t 3 = listar alunos; \n\t 4 = Gravar Dados; \n\t 5 = Ler Dados; \n\t 6 = Apagar dados\n");
    printf("\r|--------------------------------------------------------------------------------|\n");

    do {
        scanf("%d", &menu);
        printf("|--------------------------------------------------------------------------------|\n");

        switch (menu) {
            case 1:
                cadastro();
                break;
            case 2:
                pesquisa();
                break;
            case 3:
                lista();
                break;
            case 4:
                gravarcsv();
                break;
            case 5:
                lercsv();
                break;
            case 6:
                delete();
                break;
            case 0:
                exit(0);
                break;
            default:
                exit(0);
                break;
        }
    } while (menu < 4);
}

void cadastro() {
    static int linha;
    int opc;
CAD:
    printf("Informe o nome do aluno: ");
    scanf("\n%65[^\n]s", nome[linha]);

    printf("Informe o E-mail do aluno: ");
    scanf("\n%65[^\n]s", email[linha]);

    printf("Informe o cpf do aluno: ");
    scanf("\n%14[^\n]s", cpf[linha]);

    printf("Para continuar digite 1. \nPara Sair digite qualquer outro numero.\n");
    scanf("\n%d", &opc);

    linha++;

    if (opc == 1) {
        goto CAD;
    } else {
        menu();
    }
}

void pesquisa() {
    int opc;
    char emailP[65], nomeP[65], cpfP[14];
    char t[50] = "\t\t\tPESQUISA ";
    system("cls");
    cabecalho(t);

    do {
        printf("\n1 - Para pesquisa por cpf \n2 - Para pesquisa por email \n3 - Para pesquisa pelo nome:\n");
        printf("Qual opcao desejada?: ");
        scanf("%d", &opc);

        switch (opc) {
            case 1:
                printf("\nInforme o CPF: ");
                scanf("%s", cpfP);
                pesquisaCpf(cpfP);
                break;
            case 2:
                printf("\nInforme o e-mail: ");
                scanf("%s", emailP);
                pesquisaEmail(emailP);
                break;
            case 3:
                printf("\nInforme o Nome: ");
                scanf("%s", nomeP);
                pesquisaNome(nomeP);
                break;
            default:
                printf("\nOpcao Invalida.");
                break;
        }

        printf("\nPara continuar digite 1. \nPara Sair digite qualquer outro número.");
        scanf("%d", &opc);
    } while (opc == 1);
}

void pesquisaCpf(char cpfP[14]) {
    char t[50] = "PESQUISA CPF ";
    system("cls");
    cabecalho(t);
    printf("buscando por CPF:[ %s ];\n", cpfP);
    int i;
    for (i = 0; i < 45; i++) {
        if (strcmp(cpf[i], cpfP) == 0) {
            printf("\n NOME: %s \n E-MAIL: %s \n CPF: %s", nome[i], email[i], cpf[i]);
        }
    }
}

void pesquisaEmail(char emailP[65]) {
    char t[50] = "PESQUISA EMAIL ";
    system("cls");
    cabecalho(t);
    int i;
    for (i = 0; i < 45; i++) {
        if (strcmp(email[i], emailP) == 0) {
            printf("\n NOME: %s \n E-MAIL: %s \n CPF: %s", nome[i], email[i], cpf[i]);
        }
    }
}

void pesquisaNome(char nomeP[65]) {
    char t[50] = "PESQUISA NOME ";
    system("cls");
    cabecalho(t);
    int i;
    for (i = 0; i < 45; i++) {
        if (strcmp(nome[i], nomeP) == 0) {
            printf("\n NOME: %s \n E-MAIL: %s \n CPF: %s", nome[i], email[i], cpf[i]);
        }
    }
}

void lista() {
    int i;
    int opc;
    char t[50] = "LISTA COMPLETA DE ALUNOS ";
    system("cls");
    cabecalho(t);
    for (i = 0; i < 45; i++) {
        if (strlen(cpf[i]) > 0) {
            printf(" NOME: %s \n E-MAIL: %s \n CPF: %s \n", nome[i], email[i], cpf[i]);
            printf("|--------------------------------------------------------------------------------|\n");
        }
    }

    printf("Pressione a tecla 1 para retornar ao Menu \n");
    scanf("%d", &opc);

    if (opc == 1) {
        menu();
    } else {
        printf("\n Opcao Invalida.");
    }
}

void gravarcsv() {
    int i = 0;
    char str[144] = "";

    FILE *file;
    file = fopen("aluno.csv", "a");
    if (file == NULL) {
        printf("Erro no Arquivo de dados!");
    }

    for (i = 0; i < 45; i++) {
        memset(&str, 0, sizeof(str));
        if (strlen(nome[i]) > 0) {
            strcat(str, nome[i]);
            strcat(str, ",");
            strcat(str, email[i]);
            strcat(str, ",");
            strcat(str, cpf[i]);
            strcat(str, "\n");
            fputs (str, file);
        }  
    }

    fclose(file);
    menu();
}

void lercsv() {
    FILE *file;
    char linha[150];
    int l = 0;
    system("cls");
    file = fopen("aluno.csv", "r");

    if (file == NULL) {
        printf("Erro no Arquivo de dados!");
        return;
    }

    char t[50] = "ARQUIVO ALUNO.CSV";
    cabecalho(t);

    char *result;

    while (!feof(file)) {
        if ((result = fgets(linha, 150, file)) != NULL) {
            printf("Linha %s", linha);
        }
    }

    fclose(file);

    do {
        printf("\nPara voltar ao menu, pressione a tecla 1 ");
        scanf("%d", &l);
    } while (l != 1);
    menu();
}
