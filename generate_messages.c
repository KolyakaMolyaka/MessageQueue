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
#define MIN_SEND_MSG_INTERVAL_SECS 1
#define MAX_SEND_MSG_INTERVAL_SECS 3

// declaration of message struct
struct {
    long mtype; 
    char Data[MAX_MSG_SIZE];
    struct timespec sendtime;
} Message;

// declaration of tools
void generate_random_message(char *msg, int length);

int main(int argc, char **argv) {
    srand(time(NULL));

    // create message queue and shared statistics unique keys
    key_t key_msg_queue = ftok(MESSAGES_QUEUE_KEY, 0);

    // create message queue
    int msgqid = msgget(key_msg_queue, 0666 | IPC_CREAT | IPC_EXCL);
    if (msgqid == -1) {
        printf("Can't create message queue.\n");
        return 1;
    }

    // generate and send messages with 
    for (;;) {
        // create random message content
        int random_message_length = rand() % MAX_MSG_SIZE;
        char *random_msg = (char*)malloc(random_message_length * sizeof(char));
        memset(random_msg, 0, random_message_length);
        generate_random_message(random_msg, random_message_length);
        strcpy(Message.Data, random_msg);

        // create random message type
        int random_message_type = rand() % MAX_MSG_TYPE;
        Message.mtype = random_message_type;

        // set message's send time
        clock_gettime(CLOCK_REALTIME, &Message.sendtime);

        // send random message
        msgsnd(msgqid, &Message, random_message_length+1, 0);

        // free memory of last message content
        free(random_msg);

        // sleep before send new message
        int sleep_time = rand() % (MAX_SEND_MSG_INTERVAL_SECS - MIN_SEND_MSG_INTERVAL_SECS);
        sleep(sleep_time);
    }

    // delete message queue
    msgctl(msgqid, IPC_RMID, NULL);

    return 0;
}
void generate_random_message(char *msg, int length) {
    for (int i = 0; i < length; ++i) {
        msg[i] = 'a' + rand() % ('z' - 'a');
    }
}
