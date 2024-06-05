#ifndef FLIGHTDATA_H
#define FLIGHTDATA_H

typedef struct
{
    int no_id;
    char no_penerbangan[50];
    char maskapai[50];
    char kelas[50];
    char asal[50];
    char tujuan[50];
    char tgl_berangkat[50];
    char waktu_keberangkatan[50];
    char waktu_kedatangan[50];
    char harga[50];
} FlightDetails;

extern FlightDetails current_flight;

#endif
