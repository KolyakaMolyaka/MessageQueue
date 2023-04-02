#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include "msglib.h"

#define MAX_MSG_TYPE 5

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

    srand(time(NULL));

    // create message queue and shared statistics unique keys
    key_t key_msg_queue = ftok(MESSAGES_QUEUE_KEY, 0);

    // create message queue
    int msgqid = open_queue(key_msg_queue);

    // get start time of sending messages 
    time_t start_receive_messages_time = time(NULL);

    // get end time of sending messages
    time_t end_receive_messages_time = time(NULL);

    // generate and send messages with content while not timeout
    while ( difftime(end_receive_messages_time, start_receive_messages_time) < timeout_secs ) {
        // create random message content
        struct mymsgbuf qbuf;

        // create random message type
        int random_message_type = rand() % MAX_MSG_TYPE;
        qbuf.mtype = random_message_type;
        
        // create time of sending message
        time(&qbuf.sendtime);

        // send random message
        send_message(msgqid, &qbuf); 

        time(&end_receive_messages_time);
    }

    // delete message queue
    remove_queue(msgqid);

    return 0;
}

