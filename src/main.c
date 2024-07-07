#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <task3.h>

int main(){
    Flight* flight = NULL;
    char id[MAX_L_ID];
    char dest[MAX_L_DEST];
    char name[MAX_L_NAME];
    char *p;
    int seats, time, departureTime, seatNumber, age, index, newSeatNumber;

    int userChoice = 0;
    while(userChoice != 9){
        PrintMenu();
        printf("Enter number: ");
        scanf("%d", &userChoice);
        getchar();
        
        switch(userChoice){
            case 1:
                printf("\nEnter departure ID: ");
                fgets(id, sizeof(id) - 1, stdin);
                strtok(id, "\n");
                
                printf("Enter destination: ");
                fgets(dest, sizeof(dest) - 1, stdin);
                strtok(dest, "\n");
               
                printf("Enter amount of seats on airplane: ");
                scanf("%d", &seats);
                printf("Enter departure time: ");
                scanf("%d", &time);
                
                Flight* newFlight = AddFlightNode(id, dest, seats, time);
                newFlight->next = flight;
                if(flight != NULL){
                    flight->prev = newFlight;
                }
                
                flight = newFlight;
                
                break;
            case 2:
                printf("Enter Flight ID: ");
                fgets(id, sizeof(id) - 1, stdin);
                strtok(id ,"\n");
                
                printf("Enter seat number: ");
                scanf("%d", &seatNumber);
                getchar();
                
                printf("Enter passenger name: ");
                fgets(name, sizeof(name) - 1, stdin);
                strtok(name, "\n");
                
                printf("Enter passenger age: ");
                scanf("%d", &age);
                
                AddPassengerToFlight(flight, id, name, seatNumber, age);
                break;
            case 3:
                printf("\nEnter index number to search for: ");
                scanf("%d", &index);
                getchar();
            
                SearchFlightByIndex(flight, index);
                break;
                
            case 4:
                printf("Enter time to search for flights: ");
                scanf("%d", &departureTime);
                getchar();
                
                SearchFlightByTime(flight, departureTime);
                break;
            case 5:
                printf("Enter Flight ID: ");
                fgets(id, sizeof(id) - 1, stdin);
                strtok(id, "\n");
                
                if(DeleteFlight(&flight, id) == 1){
                    printf("\nFlight %s and reservations removed.", id);
                } else {
                    printf("\nFlight not found.\n");
                }
                break;
            case 6:
                printf("Enter Flight ID: ");
                fgets(id, sizeof(id) - 1, stdin);
                strtok(id, "\n");
                
                printf("Enter passenger name: ");
                fgets(name, sizeof(name) - 1, stdin);
                strtok(name, "\n");
                
                DeleteReservationFromFlight(flight, id, name);
                break;
            case 7:
                printf("Enter Flight ID: ");
                fgets(id, sizeof(id) - 1, stdin);
                strtok(id, "\n");
                
                printf("Enter passenger name: ");
                fgets(name, sizeof(name) - 1, stdin);
                strtok(name, "\n");
                
                printf("Enter new seat number: ");
                scanf("%d", &newSeatNumber);
                getchar();
                
                ChangeSeat(flight, id, name, newSeatNumber);
                break;
                
            case 8:
                printf("Enter passenger name: ");
                fgets(name, sizeof(name) - 1, stdin);
                strtok(name, "\n");
                
                SearchFlightsByPassenger(flight, name);
                break;
                
            case 9:
                printf("Exiting. Bye\n");
                break;
            default:
                printf("Invalid number entered.\n");
        }
    }
    return 0;
}
