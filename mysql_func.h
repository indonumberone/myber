
int connect_mysql();
int check_user(char *user);
int login_user(char *user, char *pw);
int register_user(char *user, char *nama, char *pw);
int blocked(char *user);
int freeblock(char *user);
int test();