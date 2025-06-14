#include <stdio.h>

// Function to update vector clocks after internal events
void increment_clock(int *clock, int index) {
    clock[index]++;
}

// Function to update vector clocks upon receiving a message
void update_on_receive(int *receiver, int *sender) {
    for (int i = 0; i < 2; i++) {
        if (sender[i] > receiver[i]) {
            receiver[i] = sender[i];
        }
    }
}

// Function to print the vector clock
void print_clock(int *clock) {
    printf("[%d %d] ", clock[0], clock[1]);
}

int main() {
    int P0[2] = {0, 0}; // Vector clock for P0 (Process 1)
    int P1[2] = {0, 0}; // Vector clock for P1 (Process 2)

    printf("The timestamps of events in P1:\n");

    // Handling events in P0 (Process 1)
    increment_clock(P0, 0); print_clock(P0);  // Event 1 in P0: [1 0]
    increment_clock(P0, 0); print_clock(P0);  // Event 2 in P0: [2 0]
    increment_clock(P0, 0); print_clock(P0);  // Event 3 in P0: [3 0]

    // P0 sends message to P1 after event 3
    int message_to_P1[2] = {P0[0], P0[1]}; // Message after event 3

    increment_clock(P0, 0); print_clock(P0);  // Event 4 in P0: [4 0]

    increment_clock(P0, 0); print_clock(P0);  // Event 5 in P0: [5 0]

    // P0 sends another message to P1 after event 5
    int message_to_P1_2[2] = {P0[0], P0[1]}; // Message after event 5

    increment_clock(P0, 0); print_clock(P0);  // Event 6 in P0: [6 0]
    increment_clock(P0, 0); print_clock(P0);  // Event 7 in P0: [7 0]

    printf("\nThe timestamps of events in P2:\n");

    // Handling events in P1 (Process 2)
    increment_clock(P1, 1); print_clock(P1);  // Event 1 in P1: [0 1]
    increment_clock(P1, 1); print_clock(P1);  // Event 2 in P1: [0 2]
    increment_clock(P1, 1); print_clock(P1);  // Event 3 in P1: [0 3]

    // P1 receives the first message from P0 after event 3
    update_on_receive(P1, message_to_P1);
    increment_clock(P1, 1); print_clock(P1);  // Event 4 in P1: [5 4]

    // P1 receives the second message from P0 after event 5
    update_on_receive(P1, message_to_P1_2);
    increment_clock(P1, 1); print_clock(P1);  // Event 5 in P1: [6 5]

    return 0;
}
