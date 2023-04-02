#include "receive_messages_tools.h"

void time_ns_diff(struct timespec starttime, struct timespec endtime, long long *delta_ns) {
    // function calculates difference between two times in nanosecs
    *delta_ns = (endtime.tv_sec - starttime.tv_sec) * 1000000000; 
    *delta_ns += (endtime.tv_nsec - starttime.tv_nsec);
}


