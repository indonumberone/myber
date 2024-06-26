#ifndef MYSQL_FUNC_H
#define MYSQL_FUNC_H
#include "userinfo.h"
#include "flightdata.h"

int connect_mysql();
int check_user(char *user);
int login_user(char *user, char *pw, UserDetails *user_details);
int login_admin(char *user, char *pw);
int register_user(char *user, char *nama, char *pw);
void insert_flight_data(char *no_pener, char *maskapai, char *kelas, char *asal, char *tujuan, char *tgl_berangkat, char *waktu_ber, char *tgl_datang, char *waktu_kedatang, char *harga);
void create_orders(char *username);
void create_ticket(char *nama, char *no_penerbangan);
int blocked(char *user);
int freeblock(char *user);
int test();
int get_jumlah_penerbangan();
int get_jumlah_orders();
int get_data_penerbangan(FlightDetails *flight_details);
#endif