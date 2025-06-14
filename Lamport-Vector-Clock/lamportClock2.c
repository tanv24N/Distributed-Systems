#include <stdio.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int main() {
    // Initial timestamps for P1 and P2 events
    int p1[7] = {1, 2, 3, 4, 0, 0, 0}; // P1 has 7 events
    int p2[5] = {0, 0, 0, 0, 0};       // P2 has 5 events

    // Message passing from P1 to P2 after the 4th event of P1
    p2[0] = max(p1[3], 0) + 1;  // P2 e21, after P1 e14
    p2[1] = p2[0] + 1;          // P2 e22
    p2[2] = p2[1] + 1;          // P2 e23

    // Message passing from P2 to P1 after the 3rd event of P2
    p1[4] = max(p1[3], p2[2]) + 1;  // P1 e15, after P2 e23

    // Further events in P1
    p1[5] = p1[4] + 1;          // P1 e16

    // Message passing from P2 to P1 after the 5th event of P2
    p2[3] = max(p2[2], p1[5]) + 1;  // P2 e24, after P1 e16
    p2[4] = p2[3] + 1;          // P2 e25

    // Further events in P1
    p1[6] = max(p1[5], p2[4]) + 1;  // P1 e17, after P2 e25

    // Output the timestamps
    printf("The timestamps of events in P1:\n");
    for (int i = 0; i < 7; i++) {
        printf("%d ", p1[i]);
    }
    printf("\nThe timestamps of events in P2:\n");
    for (int i = 0; i < 5; i++) {
        printf("%d ", p2[i]);
    }
    printf("\n");

    return 0;
}
