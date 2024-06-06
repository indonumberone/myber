#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql.h>
#include "mysql_func.h"
#include "userinfo.h"
#include "flightdata.h"

MYSQL *conn;
MYSQL_RES *res;
MYSQL_ROW row;
// // turu
// struct data_penerbangan
// {
//     char no_penerbangan[NULL],
//         char makapai[NULL],
//         char kelas[NULL],
//         char asal[NULL],
//         char tujuan[NULL],
//         // char date[NULL],
//         char pukul[NULL],
//         int harga,
// };

int connect_mysql()
{

    char *server = "localhost";
    char *user = "root";
    char *password = "myber";
    char *database = "miber";

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

int get_order_history(char *name, TicketDetails *ticket_details)
{
    char query[256];
    sprintf(query, "SELECT id_tiket, nama, no_penerbangan FROM tiket WHERE nama = '%s', name);

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


void create_orders(char *username)
{
    char query[256];
    sprintf(query, "INSERT INTO orders values(NULL, CURRENT_DATE(), '%s');", username);
    if (mysql_query(conn, query))
    {
        fprintf(stderr, "mysql_query() failed: %s\n", mysql_error(conn));
    }
}

int get_jumlah_orders()
{
    unsigned int num_fields;
    unsigned int num_rows;
    unsigned int i;

    if (mysql_query(conn, "SELECT * FROM orders"))
    {
        fprintf(stderr, "SELECT * FROM orders failed: %s\n", mysql_error(conn));
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

    num_rows = mysql_num_rows(res);
    return num_rows;
}

void create_ticket(char *nama, char *no_penerbangan)
{
    char query[256];
    sprintf(query, "INSERT INTO tiket values(NULL, '%s', '%s');", nama, no_penerbangan);
    if (mysql_query(conn, query))
    {
        fprintf(stderr, "mysql_query() failed: %s\n", mysql_error(conn));
    }

    // res = mysql_store_result(conn);
    // MYSQL_ROW row = mysql_fetch_row(res);
    // int success = (row != NULL);

    // if (success)
    // {
    //     strcpy(user_details->username, row[0]);
    //     strcpy(user_details->name, row[1]);
    //     user_details->is_admin = atoi(row[2]);
    // }

    // mysql_free_result(res);
    // return success;
}

void insert_flight_data(char *no_pener, char *maskapai, char *kelas, char *asal, char *tujuan, char *tgl_berangkat, char *waktu_ber, char *tgl_datang, char *waktu_kedatang, char *harga)
{
    char query[256];
    sprintf(query, "INSERT INTO data_penerbangan values(NULL,'%s', '%s', '%s', '%s', '%s','%s','%s','%s','%s','%s');", no_pener, maskapai, kelas, asal, tujuan, tgl_berangkat, waktu_ber, tgl_datang, waktu_kedatang, harga);
    if (mysql_query(conn, query))
    {
        fprintf(stderr, "mysql_query() failed: %s\n", mysql_error(conn));
    }

    // res = mysql_store_result(conn);
    // MYSQL_ROW row = mysql_fetch_row(res);
    // int success = (row != NULL);

    // if (success)
    // {
    //     strcpy(user_details->username, row[0]);
    //     strcpy(user_details->name, row[1]);
    //     user_details->is_admin = atoi(row[2]);
    // }

    // mysql_free_result(res);
    // return success;
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

int register_user(char *user, char *nama, char *pw)
{
    char query[256];

    sprintf(query, "INSERT INTO users (username, nama, password) VALUES ('%s', '%s', '%s')", user, nama, pw);
    // sprintf(query, "SELECT username FROM users WHERE username = '%s' AND password = '%s' AND blocked = 0", user, pw);

    if (mysql_query(conn, query))
    {
        fprintf(stderr, "mysql_query() failed: %s\n", mysql_error(conn));
        return 1;
    }
    return 0;
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

int get_jumlah_penerbangan()
{
    unsigned int num_fields;
    unsigned int num_rows;
    unsigned int i;

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

    num_rows = mysql_num_rows(res);
    return num_rows;
}

int get_data_penerbangan(FlightDetails *flight_details)
{
    unsigned int num_fields;
    unsigned int num_rows;
    unsigned int count;
    unsigned int i;

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

    num_fields = mysql_num_fields(res);
    num_rows = mysql_num_rows(res);

    // FlightDetails flight_details[num_fields];

    for (int j = 0; j < num_rows; j++)
    // while ((row = mysql_fetch_row(res)))
    {
        row = mysql_fetch_row(res);
        // count = 0;
        // unsigned long *lengths;
        // lengths = mysql_fetch_lengths(res);

        // for (int j = 0; j < num_rows; j++) {

        for (i = 0; i < num_fields; i++)
        {
            flight_details[j].no_id = atoi(row[0] ? row[0] : 0);
            strcpy(flight_details[j].no_penerbangan, row[1] ? row[1] : "NULL");
            strcpy(flight_details[j].maskapai, row[2] ? row[2] : "NULL");
            strcpy(flight_details[j].kelas, row[3] ? row[3] : "NULL");
            strcpy(flight_details[j].asal, row[4] ? row[4] : "NULL");
            strcpy(flight_details[j].tujuan, row[5] ? row[5] : "NULL");
            strcpy(flight_details[j].tgl_berangkat, row[6] ? row[6] : "NULL");
            strcpy(flight_details[j].waktu_keberangkatan, row[7] ? row[7] : "NULL");
            strcpy(flight_details[j].tgl_datang, row[8] ? row[8] : "NULL");
            strcpy(flight_details[j].waktu_kedatangan, row[9] ? row[9] : "NULL");
            flight_details[j].harga = atoi(row[10] ? row[10] : 0);

            // printf("%s", row[i] ? row[i] : "NULL");
            // printf("[%.*s] ", (int)lengths[i],
            //        row[i] ? row[i] : "NULL");
        }
        printf("\n");
        // count++;
        // }
    }

    // printf("%d", count);

    mysql_free_result(res);
    // printf("%s", flight_details[0].no_penerbangan);
    // printf("%s", flight_details[1].no_penerbangan);
    // printf("%s", flight_details[2].no_penerbangan);
    // printf("%s", flight_details[3].no_penerbangan);
}

int test()
{
    char *inilo;
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
        int itu = 0;
        for (int i = 0; i < num_fields; i++)
        {

            printf("%s i ke %d ", row[i] ? row[i] : "NULL", i);
            // memcpy(&inilo[itu][i], row[i], sizeof(inilo));
        }
        printf("\n");
        // printf("iki %d ,&s", strlen(inilo), test[1]);
        itu++;
    }

    mysql_free_result(res);
}

// set global event_scheduler = 1;
/* CREATE EVENT check_blocked ON SCHEDULE EVERY 1 MINUTE DO update users set blocked = 0 where blocked_until < current_timestamp();*/