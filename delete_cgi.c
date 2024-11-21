#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql.h>
#include <locale.h>

// Função para deletar um cadastro do banco de dados com base no CPF
void deletar_cadastro(const char *cpf)
{
    MYSQL *conn;
    conn = mysql_init(NULL);

    // Definindo os parâmetros de conexão
    const char *server = "127.0.0.1";  // Servidor MySQL
    const char *user = "root";         // Usuário do MySQL
    const char *password = "";         // Senha do MySQL (em XAMPP, geralmente está vazia)
    const char *database = "cadastro"; // Nome do banco de dados que você criou
    unsigned int port = 3333;          // Porta MySQL especificada no my.ini

    // Estabelecendo a conexão com o banco de dados
    if (mysql_real_connect(conn, server, user, password, database, port, NULL, 0) == NULL)
    {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>Erro ao conectar ao banco de dados: %s</body></html>\n", mysql_error(conn));
        mysql_close(conn);
        return;
    }

    // Criando a consulta SQL para deletar o registro
    char query[256];
    snprintf(query, sizeof(query), "DELETE FROM usuarios WHERE cpf='%s'", cpf);

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

    // Exibindo mensagem de sucesso e redirecionamento
    printf("Content-Type: text/html\n\n");
    printf("<html>\n");
    printf("<head>\n");
    printf("<title>Deletado com sucesso !</title>\n");
    printf("</head>\n");
    printf("<body>\n");
    printf("<p>Cadastro com CPF %s deletado com sucesso!</p>\n", cpf);

    // Adicionando o redirecionamento após o sucesso
    printf("<p>Voce sera redirecionado para a pagina de cadastro em segundos.</p>\n");
    printf("<script>\n");
    printf("    setTimeout(function() {\n");
    printf("        window.location.href = 'http://localhost:8080/formulario/index.html';\n");
    printf("    }, 5000); // Tempo de atraso em milissegundos\n");
    printf("</script>\n");
    printf("</body>\n");
    printf("</html>\n");
}

int main(void)
{
    setlocale(LC_ALL, "portuguese.UTF-8");
    char *data;
    char cpf[15];

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
        printf("Comprimento do conteudo inválido!\n");
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

    // Decodifica os dados do formulário para extrair o CPF
    sscanf(data, "cpf=%s", cpf);

    // Deleta o cadastro com base no CPF
    deletar_cadastro(cpf);

    free(data);
    return 0;
}
