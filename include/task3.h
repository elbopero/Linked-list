#ifndef __TASK3_H__
#define __TASK3_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_L_NAME 75
#define MAX_L_ID 10
#define MAX_L_DEST 50

typedef struct Reservation {
    int seatNumber;
    char name[MAX_L_NAME];
    int age;
    struct Reservation* next;
} Reservation;

typedef struct Flight {
    int flightIndex;
    char id[MAX_L_ID];
    char dest[MAX_L_DEST];
    int seats;
    int time;
    struct Flight* prev;
    struct Flight* next;
    Reservation* reservations;
} Flight;

void PrintMenu();
Flight* AddFlightNode(char* id, char* dest, int seats, int time);
Reservation* AddReservationNode(int seatNumber, char* name, int age);
void AddPassengerToFlight(Flight* head, char* id, char* name, int seatNumber, int age);
void PrintReservations(Flight* head, char* id);
void PrintFlight(Flight* head);
void SearchFlightByIndex(Flight* head, int index);
void SearchFlightByTime(Flight* head, int time);
void DeleteReservation(Reservation* head);
void ChangeSeat(Flight* head, char* id, char* name, int newSeatNumber);
int DeleteFlight(Flight** head, char* id);
void DeleteReservationFromFlight(Flight* head, char* id, char* name);
void SearchFlightsByPassenger(Flight* head, char* name);

#endif
