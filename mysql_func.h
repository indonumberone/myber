#ifndef MYSQL_FUNC_H
#define MYSQL_FUNC_H
#include "userinfo.h"

int connect_mysql();
int check_user(char *user);
int login_user(char *user, char *pw, UserDetails *user_details);
int login_admin(char *user, char *pw);
void register_user(char *user, char *nama, char *pw);
int blocked(char *user);
int freeblock(char *user);
int test();

#endif