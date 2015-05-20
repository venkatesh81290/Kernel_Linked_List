#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/list.h>
#include<linux/slab.h>
#include<linux/string.h>

MODULE_AUTHOR("Venkatesh Parthasarathy");
MODULE_DESCRIPTION("Linux kernel linked list implementation");
MODULE_LICENSE("GPL");

#define BUF_LEN 16
#define NUM 5

struct message {
	int msg_id;
	char data[BUF_LEN];
	struct list_head klist;
}msg;

void create_list(void) {
	int i;
	struct message *tmp;

	INIT_LIST_HEAD(&msg.klist);

	for( i = 0; i < NUM; i++) {

		tmp = kmalloc(sizeof(struct message), GFP_KERNEL);
		tmp->msg_id = i;
		sprintf(tmp->data, "DATA%d", i);

		list_add(&(tmp->klist),&(msg.klist));
	}

}

void delete_list(void) {
	struct message *tmp;
	struct list_head *pos, *q;

	list_for_each_safe(pos, q, &(msg.klist)) {
		tmp = list_entry(pos, struct message, klist);
		printk("Deleting :: msg_id %d msg_data : %s \n",tmp->msg_id, tmp->data);
		list_del(pos);
		kfree(tmp);
	}
}

void display_list(void) {
	struct message *tmp;

	list_for_each_entry(tmp,&(msg.klist),klist) {
		printk("msg_id: %d msg_data : %s \n",tmp->msg_id, tmp->data);
	}
}


static __init int my_list_init(void) {
	printk("%s :: Linux kernel linked list implementation...\n", __func__);
	create_list();
	display_list();
	delete_list();
	display_list();
	return 0;
}
static __exit int my_list_exit(void) {
	printk("kernel_linklist.ko - my_list_exit() :: Linux kernel linked list implementation...\n");
	return 0;
}

module_init(my_list_init);
module_exit(my_list_exit);
