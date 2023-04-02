#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "msglib.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Error: invalid input.\n");
        printf("You should give 1 mandatory argument - time in seconds to calculate message queue statistics.\n");
        printf("Example: %s 5\n", argv[0]);
        return 1;
    }
    int timeout_secs = atoi(argv[1]);
    if (timeout_secs == 0) {
        printf("Can't convert argument to integer.\n");
    }

    // create message queue key 
    key_t key_msg_queue = ftok(MESSAGES_QUEUE_KEY, 0);

    // connect to message queue
    int msgqid = open_queue(key_msg_queue);

    // init statistics variables
    double messages_in_queue_time = 0;
    long long received_messages_amount = 0; // total received messages from queue

    // get start time of receiving messages 
    time_t start_receive_messages_time = time(NULL);

    // get end time of receiving messages
    time_t end_receive_messages_time = time(NULL);

    // receive messages and calculate statistics
    while ( difftime(end_receive_messages_time, start_receive_messages_time) < timeout_secs ) {

        // recieve messages with all types
        struct mymsgbuf qbuf;
        read_message(msgqid, 0, &qbuf);
        
        // get recieved message time
        time_t current_time = time(NULL);
        messages_in_queue_time += difftime(current_time, qbuf.sendtime);

        // increase received messages amount
        ++received_messages_amount;

        // calculate time in queue of recieved message
        time(&end_receive_messages_time);
    }
    // calculate receiving messages time
    double recieve_messages_time = difftime(end_receive_messages_time, start_receive_messages_time);

    // print common statistics
    printf("~Total received messages: %lli msgs.\n", received_messages_amount);
    printf("~Total receive time: %lfs\n", recieve_messages_time);

    // calculate and print statistics
    long long bandwidth_of_message_queue =  received_messages_amount / recieve_messages_time;
    printf("Average bandwidth of messages queue channel: %lld msgs/ns.\n", bandwidth_of_message_queue);

    double delay_of_message_queue = messages_in_queue_time / received_messages_amount;
    printf("Average delay of time of messages queue channel: %lfs.\n", delay_of_message_queue);


    return 0;
}


