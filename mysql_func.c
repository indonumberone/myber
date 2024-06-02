#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql.h>
#include "mysql_func.h"
#include "userinfo.h"

MYSQL *conn;
MYSQL_RES *res;
MYSQL_ROW row;
int connect_mysql()
{

    char *server = "localhost";
    char *user = "root";
    char *password = "myber";
    char *database = "myber";

    conn = mysql_init(NULL);

    /* Konek ke database */
    if (!mysql_real_connect(conn, server,
                            user, password, database, 0, NULL, 0))
    {
        fprintf(stderr, "gagal %s\n", mysql_error(conn));
        exit(1);
    }

    printf("[db] Berhasil terhubung ke MySQL....\n");
    return 0;
    // if (mysql_query(conn, "SELECT * FROM users"))
    // {
    //     fprintf(stderr, "mysql_query() failed\n");
    //     mysql_close(conn);
    //     return 1;
    // }
    // if (mysql_query(conn, "SELECT data FROM users"))
    // {
    //     fprintf(stderr, "mysql_query() failed\n");
    //     mysql_close(conn);
    //     return 1;
    // }

    // res = mysql_use_result(conn);

    // if (res == NULL)
    // {
    //     fprintf(stderr, "mysql_use_result() failed\n");
    //     mysql_close(conn);
    //     return 1;
    // }

    // while ((row = mysql_fetch_row(res)) >0)
    // {
    //     // Mengambil data dan menyimpannya ke dalam variabel
    //     // Misalnya:
    //     // int id = atoi(row[0]);
    //     // char *name = row[1];
    //     // ...

    //     // Contoh cetak data
    //     printf("Data: %s\n", row[1]);
    // }

    // mysql_free_result(res);
    // mysql_close(conn);
}
int check_block(char *user)
{

    char query[256];
    sprintf(query, "SELECT blocked FROM users WHERE username = '%s'", user);

    if (mysql_query(conn, query))
    {
        fprintf(stderr, "mysql_query() failed: %s\n", mysql_error(conn));
        return -1;
    }

    res = mysql_store_result(conn);
    MYSQL_ROW row = mysql_fetch_row(res);
    if (row && atoi(row[0]) == 1)
    {
        mysql_free_result(res);
        printf("%s diblokir....\n", user);
        return 1;
    }
    mysql_free_result(res);
    return 0;
}

int check_user(char *user)
{
    char query[256];
    sprintf(query, "SELECT username FROM users WHERE username = '%s'", user);

    if (mysql_query(conn, query))
    {
        fprintf(stderr, "mysql_query() failed: %s\n", mysql_error(conn));
        return -1;
    }

    res = mysql_store_result(conn);
    MYSQL_ROW row = mysql_fetch_row(res);
    int success = (row != NULL);
    mysql_free_result(res);
    return success;
}

// int login_user(char *user, char *pw)
// {
//     char query[256];
//     sprintf(query, "SELECT username FROM users WHERE username = '%s' AND password = '%s' AND blocked = 0 AND admin = 0", user, pw);

//     if (mysql_query(conn, query))
//     {
//         fprintf(stderr, "mysql_query() failed: %s\n", mysql_error(conn));
//         return -1;
//     }

//     res = mysql_store_result(conn);
//     MYSQL_ROW row = mysql_fetch_row(res);
//     int success = (row != NULL);
//     mysql_free_result(res);
//     return success;
// }

int login_user(char *user, char *pw, UserDetails *user_details)
{
    char query[256];
    sprintf(query, "SELECT username, nama, admin FROM users WHERE username = '%s' AND password = '%s' AND blocked = 0 AND admin = 0", user, pw);

    if (mysql_query(conn, query))
    {
        fprintf(stderr, "mysql_query() failed: %s\n", mysql_error(conn));
        return -1;
    }

    res = mysql_store_result(conn);
    MYSQL_ROW row = mysql_fetch_row(res);
    int success = (row != NULL);

    if (success)
    {
        strcpy(user_details->username, row[0]);
        strcpy(user_details->name, row[1]);
        user_details->is_admin = atoi(row[2]);
    }

    mysql_free_result(res);
    return success;
}

int login_admin(char *user, char *pw)
{
    char query[256];
    sprintf(query, "SELECT username FROM users WHERE username = '%s' AND password = '%s' AND admin = 1", user, pw);

    if (mysql_query(conn, query))
    {
        fprintf(stderr, "mysql_query() failed: %s\n", mysql_error(conn));
        return -1;
    }

    res = mysql_store_result(conn);
    MYSQL_ROW row = mysql_fetch_row(res);
    int success = (row != NULL);
    mysql_free_result(res);
    return success;
}

void register_user(char *user, char *nama, char *pw)
{
    char query[256];

    sprintf(query, "INSERT INTO users (username, nama, password) VALUES ('%s', '%s', '%s')", user, nama, pw);
    // sprintf(query, "SELECT username FROM users WHERE username = '%s' AND password = '%s' AND blocked = 0", user, pw);

    if (mysql_query(conn, query))
    {
        fprintf(stderr, "mysql_query() failed: %s\n", mysql_error(conn));
    }
}

int blocked(char *user)
{
    char query[256];
    sprintf(query, "UPDATE users SET blocked =1 ,blocked_until = CURRENT_TIMESTAMP() + INTERVAL 1 MINUTE WHERE username = '%s'", user);
    if (mysql_query(conn, query))
    {
        {
            fprintf(stderr, "mysql_query() failed: %s\n", mysql_error(conn));
            mysql_close(conn);
            return 1;
        }
    }
    return 0;
}

int test()
{
    if (mysql_query(conn, "SELECT * FROM data_penerbangan"))
    {
        fprintf(stderr, "SELECT * FROM data_penerbangan failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    res = mysql_store_result(conn);
    if (res == NULL)
    {
        fprintf(stderr, "mysql_store_result() failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    int num_fields = mysql_num_fields(res);
    while ((row = mysql_fetch_row(res)))
    {
        for (int i = 0; i < num_fields; i++)
        {

            printf("%s i ke %d ", row[i] ? row[i] : "NULL", i);
        }
        printf("\n");
    }
    mysql_free_result(res);
}

// set global event_scheduler = 1;
/* CREATE EVENT check_blocked ON SCHEDULE EVERY 1 MINUTE DO update users set blocked = 0 where blocked_until < current_timestamp();*/