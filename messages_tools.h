#ifndef RECEIVE_MESSAGES_TOOLS_H_
#define RECEIVE_MESSAGES_TOOLS_H_

#include <time.h>
#define MAX_MSG_SIZE 256

// declaration of message struct
struct {
    long mtype; 
    char Data[MAX_MSG_SIZE];
    struct timespec sendtime;
} Message;

void time_ns_diff(struct timespec starttime, struct timespec endtime, long long *delta_ns);

double TIMER_DURATION;
time_t TIMER_START_TIME;

void start_receive_messages_timer();
void set_receive_messages_timer(int seconds);
int receive_messages_timeout();

#endif
