#include <stdio.h>
#include <stdlib.h>

//Calculate the maximum of two values
int get_max(int a, int b) {
    return (a > b) ? a : b;
}

void print_initial_message() {
    printf("Lamport's Clock\n");
}

//Update receiver's timestamp based on sender's event
void message_update(int sender[], int sender_event, int receiver[], int receiver_event) {
    receiver[receiver_event] = get_max(sender[sender_event], receiver[receiver_event]) + 1;
}

//Increment the event timestamp within a process
void increment_timestamp(int process[], int event_idx) {
    process[event_idx] = process[event_idx - 1] + 1;
}

//Print the timestamps of events for a given process
void display_timestamps(const char *process_name, const int timestamps[], int event_count) {
    printf("The timestamps for events in %s:\n", process_name);
    for (int i = 0; i < event_count; ++i) {
        printf("%d ", timestamps[i]);
    }
    printf("\n");
}

int main() {

    print_initial_message();
    // Initial timestamps for events in P1 and P2
    int p1[7] = {1, 2, 3, 4, 0, 0, 0}; 
    int p2[5] = {0, 0, 0, 0, 0};  

    //Message from P1 to P2
    message_update(p1, 3, p2, 0);

    //Increment internal events in P2
    increment_timestamp(p2, 1); // P2
    increment_timestamp(p2, 2); // P2 

    //Message from P2 to P1
    message_update(p2, 2, p1, 4);

    //Increment internal event in P1
    increment_timestamp(p1, 5); // P1

    //Message from P1 to P2
    message_update(p1, 5, p2, 3);

    //Increment internal event in P2
    increment_timestamp(p2, 4); // P2 

    //Message from P2 to P1
    message_update(p2, 4, p1, 6);

    //Output
    display_timestamps("P1", p1, 7);
    display_timestamps("P2", p2, 5);

    return 0;
}
