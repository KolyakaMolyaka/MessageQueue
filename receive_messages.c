#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include "receive_messages_tools.h"

// define message queue settings 
#define MESSAGES_QUEUE_KEY "message_secret"
#define MAX_MSG_SIZE 256 
#define MAX_MSG_TYPE 5

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Error: invalid input.\n");
        printf("You should give 1 mandatory argument - time in seconds to calculate message queue statistics.\n");
        printf("Example: %s 5\n", argv[0]);
        return 1;
    }
    int statistics_time = atoi(argv[1]);

    // create message queue key 
    key_t key_msg_queue = ftok(MESSAGES_QUEUE_KEY, 0);

    // connect to message queue
    int msgqid = msgget(key_msg_queue, 0666);
    if (msgqid == -1) {
        printf("Can't connect to message queue.\n");
        return 1;
    }

    long long messages_in_queue_time = 0;   // total messages time in queue
    long long received_messages_amount = 0; // total received messages from queue


    start_receive_messages_timer();
    set_receive_messages_timer(statistics_time);

    // get start time of receiving messages 
    struct timespec start_receive_messages_time;
    clock_gettime(CLOCK_REALTIME, &start_receive_messages_time);

    // receive messages and calculate statistics
    while ( !receive_messages_timeout() ) {
        // recieve messages with all types
        msgrcv(msgqid, (&Message), MAX_MSG_SIZE, 0, 0);

        // get recieved message time
        struct timespec receivetime;
        clock_gettime(CLOCK_REALTIME, &receivetime);

        // increase received messages amount
        ++received_messages_amount;

        // calculate time in queue of recieved message
        time_ns_diff(Message.sendtime, receivetime, &messages_in_queue_time);
    }

    // get end time of receiving messages
    struct timespec end_receive_messages_time;
    clock_gettime(CLOCK_REALTIME, &end_receive_messages_time);

    // calculate receiving messages time
    long long recieve_messages_time;
    time_ns_diff(start_receive_messages_time, end_receive_messages_time, &recieve_messages_time);

    // calculate and print statistics
    long long bandwidth_of_message_queue = received_messages_amount / recieve_messages_time;
    printf("Average bandwidth of messages queue channel: %lld msgs/ns.\n", bandwidth_of_message_queue);

    long long delay_of_message_queue = messages_in_queue_time / received_messages_amount;
    printf("Average delay of time of messages queue channel: %lld ns.\n", delay_of_message_queue);


    return 0;
}


