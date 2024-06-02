#ifndef USERINFO_H
#define USERINFO_H

typedef struct
{
    char username[50];
    char name[100];
    int is_admin;
} UserDetails;

extern UserDetails current_user;

#endif 
