/*
stdio.h: Para entrada/saída padrão (como printf).
stdlib.h: Para funções como alocação de memória e conversões.
string.h: Para manipulação de strings.
mysql.h: Para interagir com o banco de dados MySQL.
locale.h: Para configurar a localização, como suporte a caracteres acentuados.  
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql.h>
#include <locale.h>

// Função para decodificar caracteres especiais de URL (como %40 para @)
void url_decode(char *src, char *dest)
{
    char hex[3];
    while (*src)
    {
        if (*src == '%')
        {
            hex[0] = *(src + 1);
            hex[1] = *(src + 2);
            hex[2] = '\0';
            *dest = (char)strtol(hex, NULL, 16); // Converte de hexadecimal para caractere
            src += 3;
        }
        else if (*src == '+')
        {
            *dest = ' '; // '+' em URL encoding vira espaço
            src++;
        }
        else
        {
            *dest = *src;
            src++;
        }
        dest++;
    }
    *dest = '\0'; // Finaliza a string
}

// Função para decodificar os dados enviados pelo formulário
void decode_form_data(char *data, char *nome, char *cpf, char *email, char *matricula)
{
    char decoded_data[1024];        // Buffer temporário para dados decodificados
    url_decode(data, decoded_data); // Decodifica a string inteira

    // Agora podemos usar sscanf nos dados já decodificados
    sscanf(decoded_data, "nome=%[^&]&cpf=%[^&]&email=%[^&]&matricula=%s", nome, cpf, email, matricula);
}

// Função para salvar os dados no banco de dados MySQL
void salvar_dados_no_banco(const char *nome, const char *cpf, const char *email, const char *matricula)
{
    MYSQL *conn;
    conn = mysql_init(NULL);

    // Definindo os parâmetros de conexão
    const char *server = "127.0.0.1";  // Servidor MySQL
    const char *user = "root";         // Usuário do MySQL
    const char *password = "";         // Senha do MySQL (em XAMPP, geralmente está vazia)
    const char *database = "cadastro"; // Nome do banco de dados que você criou
    unsigned int port = 3333;          // Porta MySQL especificada no my.ini

    // Estabelecendo a conexão com o banco de dados na porta 3333
    if (mysql_real_connect(conn, server, user, password, database, port, NULL, 0) == NULL)
    {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>Erro ao conectar ao banco de dados: %s</body></html>\n", mysql_error(conn));
        mysql_close(conn);
        return;
    }

    // Criando a consulta SQL para inserir os dados
    char query[512];
    snprintf(query, sizeof(query),
             "INSERT INTO usuarios (nome, cpf, email, matricula) VALUES ('%s', '%s', '%s', '%s')",
             nome, cpf, email, matricula);

    // Executando a consulta
    if (mysql_query(conn, query))
    {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>Erro ao executar a consulta SQL: %s</body></html>\n", mysql_error(conn));
        mysql_close(conn);
        return;
    }

    // Fechando a conexão com o MySQL
    mysql_close(conn);

    // Exibindo uma mensagem de sucesso
    printf("Content-Type: text/html\n\n");
    printf("<html>\n");
    printf("<head>\n");
    printf("<title>Sucesso!</title>\n");
    printf("</head>\n");
    printf("<body>\n");
    printf("<p>Dados salvos com sucesso no banco de dados!</p>\n");

    // Adicionando o redirecionamento após o sucesso
    printf("<p>Você será redirecionado para a página de cadastro em breve.</p>\n");
    printf("<script>\n");
    printf("    setTimeout(function() {\n");
    printf("        window.location.href = 'http://localhost:8080/formulario/index.html';\n");
    printf("    }, 10000); // Tempo de atraso em milissegundos\n");
    printf("</script>\n");
    printf("</body>\n");
    printf("</html>\n");
}

int main(void)
{
    setlocale(LC_ALL, "portuguese.UTF-8");
    char *data;
    char nome[100], cpf[15], email[100], matricula[20];

    // Obtém o comprimento dos dados enviados pelo formulário
    char *content_length_str = getenv("CONTENT_LENGTH");
    if (content_length_str == NULL)
    {
        printf("Content-Type: text/plain\n\n");
        printf("Nenhum dado recebido!\n");
        return 1;
    }

    int content_length = atoi(content_length_str);
    if (content_length <= 0)
    {
        printf("Content-Type: text/plain\n\n");
        printf("Comprimento do conteúdo inválido!\n");
        return 1;
    }

    // Aloca espaço para os dados recebidos
    data = (char *)malloc(content_length + 1);
    if (data == NULL)
    {
        printf("Content-Type: text/plain\n\n");
        printf("Erro de alocação de memória!\n");
        return 1;
    }

    // Lê os dados enviados pelo formulário
    fread(data, 1, content_length, stdin);
    data[content_length] = '\0'; // Adiciona o terminador de string

    // Decodifica os dados do formulário
    decode_form_data(data, nome, cpf, email, matricula);

    // Salva os dados no banco de dados MySQL
    salvar_dados_no_banco(nome, cpf, email, matricula);

    free(data);
    return 0;
    perror("Error Message");

}
