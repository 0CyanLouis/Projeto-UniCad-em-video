#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql.h>
#include <locale.h>

// Função para exibir os dados dos usuários cadastrados
void exibir_cadastros()
{
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);

    // Definindo os parâmetros de conexão
    const char *server = "127.0.0.1";  // Servidor MySQL
    const char *user = "root";         // Usuário do MySQL
    const char *password = "";         // Senha do MySQL (em XAMPP, geralmente está vazia)
    const char *database = "cadastro"; // Nome do banco de dados que você criou
    unsigned int port = 3333;          // Porta MySQL especificada no my.ini

    // Conectando ao banco de dados
    if (mysql_real_connect(conn, server, user, password, database, port, NULL, 0) == NULL)
    {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>Erro ao conectar ao banco de dados: %s</body></html>\n", mysql_error(conn));
        mysql_close(conn);
        return;
    }

    // Executando a consulta SQL para selecionar todos os registros
    if (mysql_query(conn, "SELECT nome, cpf, email, matricula FROM usuarios"))
    {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>Erro ao executar a consulta SQL: %s</body></html>\n", mysql_error(conn));
        mysql_close(conn);
        return;
    }

    // Obtendo o resultado da consulta
    res = mysql_store_result(conn);
    if (res == NULL)
    {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>Erro ao obter o resultado da consulta: %s</body></html>\n", mysql_error(conn));
        mysql_close(conn);
        return;
    }

    // Exibindo os resultados em formato de tabela HTML
    printf("Content-Type: text/html\n\n");
    printf("<html>\n");
    printf("<head>\n");
    printf("<title>Lista de Cadastros</title>\n");
    printf("<style>\n");
    printf("table { width: 80%%; border-collapse: collapse; margin: 20px auto; }\n");
    printf("th, td { border: 1px solid #ddd; padding: 8px; text-align: left; }\n");
    printf("th { background-color: #f2f2f2; }\n");
    printf("</style>\n");
    printf("</head>\n");
    printf("<body>\n");
    printf("<h2 style='text-align: center;'>Lista de Cadastros</h2>\n");
    printf("<table>\n");
    printf("<tr><th>Nome</th><th>CPF</th><th>Email</th><th>Matricula</th></tr>\n");

    // Iterando sobre os resultados e exibindo cada registro
    while ((row = mysql_fetch_row(res)) != NULL)
    {
        printf("<tr>");
        printf("<td>%s</td>", row[0]); // Nome
        printf("<td>%s</td>", row[1]); // CPF
        printf("<td>%s</td>", row[2]); // Email
        printf("<td>%s</td>", row[3]); // Matrícula
        printf("</tr>\n");
    }

    printf("</table>\n");
    printf("</body>\n");
    printf("</html>\n");

    // Liberando o resultado e fechando a conexão
    mysql_free_result(res);
    mysql_close(conn);
}

int main(void)
{
    setlocale(LC_ALL, "portuguese.UTF-8");
    exibir_cadastros();
    return 0;
}
