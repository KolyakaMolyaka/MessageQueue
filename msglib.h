#ifndef MSGLIB_H_
#define MSGLIB_H_ 

#include <time.h>
#include <sys/ipc.h>

#define MESSAGE_MAX_SIZE 256
struct mymsgbuf {
    long mtype;
    time_t sendtime;
    double salary;
};

int open_queue(key_t keyval);
int send_message(int qid, struct mymsgbuf *qbuf);
int remove_queue(int qid);
int read_message(int qid, long type, struct mymsgbuf *qbuf);
//int peek_message(int qid, long type);
//int get_queue_ds(int qid, struct msgqid_ds *qbuf);
//int change_queue_mode(int qid, char *mode);
int remove_queue(int qid);

#endif



