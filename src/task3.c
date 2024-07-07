#include <task3.h>

void PrintMenu(){
    printf("\n---------------------------------------------------------\n");
    printf("\nEnter one of the numbers to perform the following actions\n");
    printf("\n----------------------------------------------------------\n");
    printf("\n1. Insert a departure");
    printf("\n2. Insert passenger reservation to a departure");
    printf("\n3. Get departure information");
    printf("\n4. Get departures based on departure time");
    printf("\n5. Delete a departure");
    printf("\n6. Delete a passengers reservation");
    printf("\n7. Change seat for a passenger");
    printf("\n8. Search for passenger name in departures");
    printf("\n9. Exit");
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}

Flight* AddFlightNode(char* id, char* dest, int seats, int time){
    static int index = 1;
    Flight* newNode = (Flight*) malloc(sizeof(Flight));
    newNode->flightIndex = index;
    strcpy(newNode->id, id);
    strcpy(newNode->dest, dest);
    newNode->seats = seats;
    newNode->time = time;
    newNode->reservations = NULL;
    newNode->prev = NULL;
    newNode->next = NULL;
    
    index++;
    
    return newNode;
}

Reservation* AddReservationNode(int seatNumber, char* name, int age){
    Reservation* newNode = (Reservation*) malloc (sizeof(Reservation));
    newNode->seatNumber = seatNumber;
    strcpy(newNode->name, name);
    newNode->age = age;
    newNode->next = NULL;
    
    return newNode;
}

void AddPassengerToFlight(Flight* head, char* id, char* name, int seatNumber, int age){
    Flight* current = head;
    while(current != NULL){
        if(strcmp(current->id, id) == 0){
            Reservation* reservation = AddReservationNode(seatNumber, name, age);
            
            if(current->reservations == NULL || current->reservations->seatNumber > seatNumber) {
                reservation->next = current->reservations;
                current->reservations = reservation;
            } else {
                Reservation* currentRes = current->reservations;
                while(currentRes->next != NULL && currentRes->next->seatNumber < seatNumber){
                    currentRes = currentRes->next;
                }
                reservation->next = currentRes->next;
                currentRes->next = reservation;
            }
            printf("\nReservation added to departure: %s.\n", id);        
            return;
        }
        current = current->next;
    }
    printf("Could not find departure.\n");
}

void PrintReservations(Flight* head, char* id){
    Flight* current = head;
    
    while(current != NULL){
        if(strcmp(current->id, id) == 0){
            printf("\n\nReservations for flight %s:\n", id);
            
            Reservation* currentRes = current->reservations;
            while(currentRes != NULL){
                printf("Name: %s\t|Seat: %d\t| Age: %d\n", currentRes->name, currentRes->seatNumber, currentRes->age);
                currentRes = currentRes->next;
            }
            return;
        }
        current = current->next;
    }
    printf("Flight not found.\n");
}


void PrintFlight(Flight* head){
    Flight* current = head;
    
    printf("Flight: %s | Index: %d | Destination: %s | Seats: %d | Departure: %d\n", current->id, current->flightIndex, current->dest, current->seats, current->time);
}

void SearchFlightByIndex(Flight* head, int index){
    Flight* current = head;
    int counter = 1;
    
    while(current != NULL){
        if(current->flightIndex == index){
            PrintFlight(current);
            PrintReservations(current, current->id);
            return;
        }
        current = current->next;
        counter++;
    }
    printf("\nNo flights found with index %d.\n", index);
}

void SearchFlightByTime(Flight* head, int searchTime){
    Flight* current = head;
    int flag = 0;
     
    while(current != NULL){
        if(current->time == searchTime){
            PrintFlight(current);
            PrintReservations(current, current->id);
            flag = 1;
        }
        current = current->next; 
    }
    if(flag == 0){
        printf("No flights found at that time\n");
    }
}

void DeleteReservation(Reservation* head){
    Reservation* current = head;
    
    while(current != NULL){
        Reservation* temp = current;
        current = current->next;
        free(temp);
    }
}

void ChangeSeat(Flight* head, char* id, char* name, int newSeatNumber){
    Flight* current = head;
    while(current != NULL){
        if(strcmp(current->id, id) == 0){
            Reservation* currentRes = current->reservations;
            
            while(currentRes != NULL){
                if(strcmp(currentRes->name, name) == 0){
                    currentRes->seatNumber = newSeatNumber;
                    printf("\nMr/Mrs %s seat for flight %s has now changed to number %d.\n", name, id, newSeatNumber);
                    return;
                }
                currentRes = currentRes->next;
            }
            printf("Reservation not found.\n");
            return;
        }
        current = current->next;
    }
    printf("Flight not found.\n");
}


int DeleteFlight(Flight** head, char* id){
    Flight* current = *head;
    Flight* prev = NULL;
    
    while(current != NULL){
        if(strcmp(current->id, id) == 0){
            if(prev == NULL){
                *head = current->next;
            } else {
                prev->next = current->next;
            }
            DeleteReservation(current->reservations);
            free(current);
            return 1;
        }
        prev = current;
        current = current->next;
    }
    return 0;
}

void DeleteReservationFromFlight(Flight* head, char* id, char* name){
    Flight* current = head;
    
    while(current != NULL){
        if(strcmp(current->id, id) == 0){
            Reservation* currentRes = current->reservations;
            
            if(currentRes != NULL && strcmp(currentRes->name, name) == 0){
                
                current->reservations = currentRes->next;
                free(currentRes);
                printf("Reservation deleted for %s in flight %s.\n", name, id);
                return;
            }
        
        while(currentRes != NULL && currentRes->next != NULL){
            if(strcmp(currentRes->next->name, name) == 0){
                Reservation* deleteRes = currentRes->next;
                currentRes->next = currentRes->next->next;
                free(deleteRes);
                printf("Reservation deleted for %s in flight %s.\n", name, id);
                return;
            }
            currentRes = currentRes->next;
        }
        printf("Reservation not found.\n");
        return;    
        }
        current = current->next;
    }
    printf("Flight not found.\n");
}


void SearchFlightsByPassenger(Flight* head, char* name){
    Flight* current = head;
    int flag = 0, count = 0;
    
    printf("Showing all flights for passenger %s:\n", name);
    
    while(current != NULL){
        Reservation* currentRes = current->reservations;
        
        while(currentRes != NULL){
            if(strcmp(currentRes->name, name) == 0){
                printf("\nFlight: %s | Destination: %s | Seat: %d | Departure: %d", current->id, current->dest, currentRes->seatNumber, current->time);
                flag = 1;
                count++;
                break;
            }
            currentRes = currentRes->next;
        }
        current = current->next;
    }
    
    if(flag == 0){
        printf("\nNo reservation found for passenger %s.\n", name);
    } else {
        printf("\nPassenger %s found in %d flights.\n", name, count);
    }
}
