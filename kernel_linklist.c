#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/list.h>
#include<linux/slab.h>
#include<linux/string.h>
#include"kernel_linklist.h"

MODULE_AUTHOR("Venkatesh Parthasarathy");
MODULE_DESCRIPTION("Linux kernel linked list implementation");
MODULE_LICENSE("GPL");

void create_list(void) {
	int i;
	struct message *tmp;

	MYDEBUG("******************* CREATING LIST *******************\n");

	INIT_LIST_HEAD(&msg.klist);
	MYDEBUG("Address of list head : %p\n", &(msg.klist));
	MYDEBUG("Address of list head prev : %p\n", msg.klist.prev);
	MYDEBUG("Address of list head next : %p\n", msg.klist.next);
	MYDEBUG("Address of list head data : %d |%s| \n", msg.msg_id, msg.data);

	for( i = 0; i < NUM; i++) {

		tmp = kmalloc(sizeof(struct message), GFP_KERNEL);
		tmp->msg_id = i;
		sprintf(tmp->data, "DATA%d", i);

		list_add(&(tmp->klist),&(msg.klist));
//		MYDEBUG("Address of Node%d : %p\n", i, tmp);
//		MYDEBUG("Node%d -> prev value : %p\n", i, tmp->klist.prev);
//		MYDEBUG("Node%d -> next value : %p\n", i, tmp->klist.next);
	display_list();
	}

}

void delete_list(void) {
	struct message *tmp;
	struct list_head *pos, *q;
	
	MYDEBUG("******************* DELETING LIST *******************\n");

	list_for_each_safe(pos, q, &(msg.klist)) {
		tmp = list_entry(pos, struct message, klist);
		printk("Deleting :: msg_id %d msg_data : %s \n",tmp->msg_id, tmp->data);
		list_del(pos);
		kfree(tmp);
	display_list();
	}
}

void display_list(void) {
	struct message *tmp;
	int flag = 0;

	MYDEBUG("******************* DISPLAYING LIST *******************\n");

	list_for_each_entry(tmp,&(msg.klist),klist) {
		if (!flag) flag = 1;
		printk("node : %p msg_id: %d msg_data : %s prev : %p  next %p \n",tmp, tmp->msg_id, tmp->data, tmp->klist.prev, tmp->klist.next);
		MYDEBUG("Address of list head : %p\n", &(msg.klist));
		MYDEBUG("Address of list head prev : %p\n", msg.klist.prev);
		MYDEBUG("Address of list head next : %p\n", msg.klist.next);
		MYDEBUG("Address of list head data : %d |%s| \n", msg.msg_id, msg.data);
	}
	if(!flag) printk("Nothing to disaply...\n");
}


static int __init my_list_init(void) {
	printk("\n\n******************* kernel_linklist.ko :: %s - LINUX KERNEL LINKED LIST *******************\n", __func__);
	create_list();
	display_list();
	delete_list();
	display_list();
	return 0;
}
static void __exit my_list_exit(void) {
	printk("******************* kernel_linklist.ko :: %s - LINUX KERNEL LINKED LIST *******************\n", __func__);
}

module_init(my_list_init);
module_exit(my_list_exit);
