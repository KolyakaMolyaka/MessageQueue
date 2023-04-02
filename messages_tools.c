#include "messages_tools.h"

void time_ns_diff(struct timespec starttime, struct timespec endtime, long long *delta_ns) {
    // function calculates difference between two times in nanosecs
    *delta_ns += (endtime.tv_sec - starttime.tv_sec) * 1000000000; 
    *delta_ns += (endtime.tv_nsec - starttime.tv_nsec);
}

void start_receive_messages_timer(){
    // function sets start time of timer
    time(&TIMER_START_TIME);
}

void set_receive_messages_timer(int seconds) {
    // function sets timer duration
    TIMER_DURATION = seconds;
}

int receive_messages_timeout() {
    // function returns 1 if timer is timeout, else 0.
    time_t current_time;
    time(&current_time);

    double elapsed_time = difftime(current_time, TIMER_START_TIME);
    if (elapsed_time > TIMER_DURATION) return 1;
    return 0;
}
