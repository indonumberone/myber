#include <stdio.h>
#include <string.h>
#include "mysql_func.h"

int main()
{
    // printf();
    char *user[256];
    char *pw[256];
    int try = 0;
    if (connect_mysql() != 0)
        return 1;
    test();
    // printf("masukan username:");
    // scanf(" %s", user);
    // if (check_block(user) == 1)
    //     return 0;
    // while (1)
    // {
    //     printf("masukan password:");
    //     scanf("%255s", pw);
    //     if (login(user, pw) == 1)
    //     {
    //         printf("Login successful......\n");
    //         return 0;
    //     }
    //     else
    //     {
    //         printf("coba lagi\n");
    //         try++;
    //     }

    //     if (try > 3)
    //     {
    //         printf("di blokir");
    //         blocked(user);
    //         return -1;
    //     }
    //     // printf("try %d\n", try);
    // }
}
