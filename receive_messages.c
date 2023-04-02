#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdio.h>
#include <string.h>

// define message queue settings 
#define MESSAGES_QUEUE_KEY "message_secret"
#define MAX_MSG_SIZE 256 
#define MAX_MSG_TYPE 5
//#define MIN_SEND_MSG_INTERVAL_SECS 1
//#define MAX_SEND_MSG_INTERVAL_SECS 3

// declaration of message struct
struct {
    long mtype; 
    char Data[MAX_MSG_SIZE];
    struct timespec sendtime;
} Message;

int main(int argc, char **argv) {
    // create message queue key 
    key_t key_msg_queue = ftok(MESSAGES_QUEUE_KEY, 0);

    // connect to message queue
    int msgqid = msgget(key_msg_queue, 0666);
    if (msgqid == -1) {
        printf("Can't connect to message queue.\n");
        return 1;
    }

    long long messages_in_queue_time = 0;
    long long received_messages_amount = 0;

    // get start time of receiving messages 
    struct timespec start_receive_messages_time;
    clock_gettime(CLOCK_REALTIME, &start_receive_messages_time);
    // receive messages and calculate statistics
    for (;;) {
        // recieve messages with all types
        struct timespec receivetime;
        msgrcv(msgqid, (&Message), MAX_MSG_SIZE, 0, 0);

        // get recieved message time
        clock_gettime(CLOCK_REALTIME, &receivetime);

        // increase received message amount
        ++received_messages_amount;

        // calculate time in queue of recieved message
        messages_in_queue_time = (receivetime.tv_sec - Message.sendtime.tv_sec);
        messages_in_queue_time += (receivetime.tv_nsec - Message.sendtime.tv_nsec);
    }

    // get end time of receiving messages
    struct timespec end_receive_messages_time;
    clock_gettime(CLOCK_REALTIME, &end_receive_messages_time);

    // calculate receiving messages time
    long long recieve_messages_time = (end_receive_messages_time.tv_sec - start_receive_messages_time.tv_sec);
    recieve_messages_time += (end_receive_messages_time.tv_nsec - start_receive_messages_time.tv_nsec);

    // calculate and print statistics
    long long bandwidth_of_message_queue = received_messages_amount / recieve_messages_time;
    printf("Average bandwidth of messages queue channel: %lld msgs/ns.\n", bandwidth_of_message_queue);
    long long delay_of_message_queue = messages_in_queue_time / received_messages_amount;
    printf("Average delay of time of messages queue channel: %lld ns.\n", delay_of_message_queue);


    return 0;
}


