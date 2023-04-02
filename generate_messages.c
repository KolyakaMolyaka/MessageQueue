#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include "message_queue_config.h"
#include "messages_tools.h"
#include "msglib.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Error: invalid input.\n");
        printf("You should give 1 mandatory argument - time in seconds to calculate message queue statistics.\n");
        printf("Example: %s 5\n", argv[0]);
        return 1;
    }

    int statistics_time = atoi(argv[1]);
    srand(time(NULL));

    // create message queue and shared statistics unique keys
    key_t key_msg_queue = ftok(MESSAGES_QUEUE_KEY, 0);

    // create message queue
    int msgqid = open_queue(key_msg_queue);

    start_receive_messages_timer();
    set_receive_messages_timer(statistics_time);

    // generate and send messages with content while not timeout
    while ( !receive_messages_timeout() ) {
        // create random message content
        struct mymsgbuf qbuf;

        // create random message type
        int random_message_type = rand() % MAX_MSG_TYPE;
        qbuf.mtype = random_message_type;
        
        // create time of sending message
        time(&qbuf.sendtime);

        // send random message
        send_message(msgqid, &qbuf); 
    }

    // delete message queue
    remove_queue(msgqid);

    return 0;
}

