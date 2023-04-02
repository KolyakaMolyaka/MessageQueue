#ifndef MESSAGE_QUEUE_CONFIG_H_
#define MESSAGE_QUEUE_CONFIG_H_

// define message queue settings 
#define MESSAGES_QUEUE_KEY "message_secret"
#define MAX_MSG_SIZE 256 
#define MAX_MSG_TYPE 5

// declaration of message struct
struct {
    long mtype; 
    char Data[MAX_MSG_SIZE];
    struct timespec sendtime;
} Message;

#endif


