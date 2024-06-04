#ifndef FLIGHTDATA_H
#define FLIGHTDATA_H

typedef struct
{
    char asal[50];
    char tujuan[100];
} FlightDetails;

extern FlightDetails current_data;

#endif
