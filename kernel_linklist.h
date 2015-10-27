/*kernel_linklist.h*/

#define BUF_LEN 16
#define NUM 5

#define DEBUG           //Comment to disable debug messages

#ifdef DEBUG
#define MYDEBUG(fmt, args...) printk(fmt, ##args);
#else
#define MYDEBUG(fmt, args...)
#endif

struct message {
        int msg_id;
        char data[BUF_LEN];
        struct list_head klist;
}msg;

void create_list(void);
void delete_list(void);
void display_list(void);
