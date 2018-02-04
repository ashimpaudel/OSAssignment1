#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include<linux/slab.h>
struct birthday{
	char name[100];
	int day;
	int month;
	int year;
	struct list_head list;
};

/* This function is called when the module is loaded. */
int create_list_init(void){
	// defines and initializes the variable birthday_list
	// and the type of birthday_list is struct list_head

	static LIST_HEAD(birthday_list);
	//or, we could do: 
	// struct list_head birthday_list;
	struct birthday *person1,*person2,*person3,*person4,*person5,*entry;

	person1 = kmalloc(sizeof(*person1), GFP_KERNEL);
	person2 = kmalloc(sizeof(*person2), GFP_KERNEL);
	person3 = kmalloc(sizeof(*person3), GFP_KERNEL);
	person4 = kmalloc(sizeof(*person4), GFP_KERNEL);
	person5 = kmalloc(sizeof(*person5), GFP_KERNEL);

	strcpy(person1->name, "Ashim");
	person1->day = 14;
	person1->month = 6;
	person1->year = 1994;

	strcpy(person2->name, "Utsab");
	person2->day = 23;
	person2->month = 7;
	person2->year = 1993;

	strcpy(person3->name, "Prajjwal");
	person3->day = 24;
	person3->month = 8;
	person3->year = 1992;

	strcpy(person4->name, "Ram");
	person4->day = 25;
	person4->month = 9;
	person4->year = 1991;

	strcpy(person5->name, "Linus");
	person5->day = 28;
	person5->month = 12;
	person5->year = 1969;

	//INIT_LIST_HEAD(&person->list);
	INIT_LIST_HEAD(&birthday_list);

	list_add(&person1->list, &birthday_list);
	list_add(&person2->list, &birthday_list);
	list_add(&person3->list, &birthday_list);
	list_add(&person4->list, &birthday_list);
	list_add(&person5->list, &birthday_list);

	//list_add_tail(&person->list, &birthday_list);

	//traversing a list
	struct list_head *ptr;

	list_for_each(ptr, &birthday_list){
		entry = list_entry(ptr, struct birthday, list);
		printk(KERN_INFO  "\n Name %s \n", entry->name);
		printk(KERN_INFO  "\n birthday %d \n", entry->day);
		printk(KERN_INFO  "\n birthmonth %d \n", entry->month);
		printk(KERN_INFO  "\n birthyear %d \n", entry->year);
	}

}
/* This function is called when the module is removed. */
void simple_exit(void)
{
printk(KERN_INFO "Removing Module\n");
}
/* Macros for registering module entry and exit points. */
module_init(create_list_init);
module_exit(simple_exit);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");
