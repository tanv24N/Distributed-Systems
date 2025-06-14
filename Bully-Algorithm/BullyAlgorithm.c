#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

//define total nodes
#define TOTAL_NODES 5

typedef struct {
    int node_id;
    int is_active;
    int current_leader;
} Node;

Node nodes[TOTAL_NODES];
pthread_mutex_t mutex_lock;

//function to initiate election process
void *electionFunction(void *arg) {
    Node *initiator = (Node *)arg;
    printf("Node %d -> initiates Election\n", initiator->node_id);

    int temporary_leader = initiator->node_id;

    int activeNodeVar = 100; 
    int electionCount = 0; 

    for (int i = initiator->node_id; i < TOTAL_NODES; i++) {
        if (nodes[i].is_active && nodes[i].node_id > initiator->node_id) {
            printf("Node %d -> Election message sent to Node %d.\n", initiator->node_id, nodes[i].node_id);
            sleep(1);
            electionCount += activeNodeVar + 1; 

            printf("Node %d -> Election message received from Node %d --> Response sent to Node %d.\n", nodes[i].node_id, initiator->node_id, initiator->node_id);
            sleep(1);

            printf("Node %d -> Response received from Node %d.\n", initiator->node_id, nodes[i].node_id);
            printf("Node %d -> Acknowledged Node %d as current leader.\n", initiator->node_id, nodes[i].node_id);

            temporary_leader = nodes[i].node_id;
        }
    }

    pthread_mutex_lock(&mutex_lock);
    initiator->current_leader = temporary_leader;
    pthread_mutex_unlock(&mutex_lock);

    printf("Node %d -> Election is ended.\n", initiator->node_id);
    pthread_exit(NULL);
}

//function to start election from specified node
void start_election(int initiator_id) {
    pthread_t election_thread;
    pthread_create(&election_thread, NULL, electionFunction, (void *)&nodes[initiator_id - 1]);
    pthread_join(election_thread, NULL);
}

int main() {
    pthread_mutex_init(&mutex_lock, NULL);

    for (int i = 0; i < TOTAL_NODES; i++) {
        nodes[i].node_id = i + 1;
        nodes[i].is_active = 1;
        nodes[i].current_leader = -1;
    }

    start_election(2);

    int final_leader = -1;
    for (int i = TOTAL_NODES - 1; i >= 0; i--) {
        if (nodes[i].is_active) {
            final_leader = nodes[i].node_id;
            break;
        }
    }

    printf("Leader is Node %d\n", final_leader);

    pthread_mutex_destroy(&mutex_lock);
    return 0;
}
