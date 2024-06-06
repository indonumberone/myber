#ifndef TIKETINFO_H
#define TIKETINFO_H

typedef struct
{
    int id_tiket;
    char nama[50];
    char no_penerbangan[50];
} TicketDetails;

extern TicketDetails current_ticket;

#endif
