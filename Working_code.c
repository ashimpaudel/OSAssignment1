#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/slab.h>

#define NUM_OF_PERSON    5

/* Example struct we will use. */
typedef struct _birthday {
    int day;
    int month;
    int year;
    struct list_head list;
}birthday;



typedef struct _bucket{
	//birthday is a doubly-linked list, therefore, the buckets i.e. value of our hash-table(buckets) is doubly linked list
	struct _birthday* value;
	//LIST_HEAD(value);
	//using id, we can locate our bucket
	int id;
	struct list_head bucket_list;
}bucket;


/* Declare and init the head of the linked list. */
LIST_HEAD(birthday_list);
LIST_HEAD(bucket_list_glob);

/* This function is called when the module is loaded. */
int birthdayList_init(void)
{
           printk(KERN_INFO "Loading Modulen");

    /* Allocate 5 birthdays from kernel */
    birthday *person;
    bucket *each_bucket;
    int i;
    for(i = 0; i < NUM_OF_PERSON; i++)
    {
        /* Request malloc to the kernel. */
        person = kmalloc(sizeof(*person), GFP_KERNEL);
        /* Assign value to the struct. */
        person->day = i+1;
        person->month = i+1;
        person->year = i+1;
        /* Init the list within the struct. */
        INIT_LIST_HEAD(&person->list);
        /* Add this struct to the tail of the list. */
        list_add_tail(&person->list, &birthday_list);
    }


    //hashtable of buckets with bucket_list_glob pointing at the head of the list
    birthday birthdays_array[NUM_OF_PERSON];
    i = 0;
    birthday *ptr;
    list_for_each_entry(ptr, &birthday_list, list)
    {
        birthdays_array[i].day = ptr->day;
        birthdays_array[i].month = ptr ->month;
        birthdays_array[i].year = ptr ->year
        printk(KERN_INFO "day: %d, month: %d, year: %dn",
                ptr->day,
                ptr->month,
                ptr->year);
    }

    for(i = 0; i < NUM_OF_PERSON; i++)
    {
        /* Request malloc to the kernel. */
        each_bucket = kmalloc(sizeof(*each_bucket), GFP_KERNEL);
        /* Assign value to the struct. */
        each_bucket->id = i+1;
	    each_bucket->value = NULL;
        
        /* Init the list within the struct. */
        INIT_LIST_HEAD(&each_bucket->bucket_list);
        /* Add this struct to the tail of the list. */
        list_add_tail(&each_bucket->bucket_list, &bucket_list_glob);
    }



    //describe the array that stores all the person , array of birthday
    
    


    printk(KERN_INFO "Display the list:n");

    /* Go thru the list and print. */
    birthday *ptr;
    list_for_each_entry(ptr, &birthday_list, list)
    {
        printk(KERN_INFO "day: %d, month: %d, year: %dn",
                ptr->day,
                ptr->month,
                ptr->year);
    }


        /* Go thru the list and print. */
    bucket *ptr1;
    list_for_each_entry(ptr1, &bucket_list_glob, bucket_list)
    {
        printk(KERN_INFO "id: %d, ",ptr1->id);
    }




            /* Go thru the list and print. */
    bucket *ptr2;
    list_for_each_entry(ptr2, &bucket_list_glob, bucket_list)
    {
        person = kmalloc(sizeof(*person), GFP_KERNEL);
        /* Assign value to the struct. */
        person->day = 69;
        person->month =70;
        person->year = 55;
        /* Init the list within the struct. */
        INIT_LIST_HEAD(&person->list);
        ptr2->value = person;
    }
    
    bucket *ptr3;
    list_for_each_entry(ptr3, &bucket_list_glob, bucket_list)
    {
        printk(KERN_INFO "month: %d, ",ptr3->value->month);
    }


    printk(KERN_INFO "Display donen");

           return 0;
}

/* This function is called when the module is removed. */
void birthdayList_exit(void)
{
    printk(KERN_INFO "Removing Modulen");

    /* Go thru the list and free the memory. */
    birthday *ptr, *next;
    list_for_each_entry_safe(ptr, next, &birthday_list, list)
    {
        printk(KERN_INFO "Removing – day: %d, month: %d, year: %dn",
                ptr->day,
                ptr->month,
                ptr->year);
        list_del(&ptr->list);
        kfree(ptr);
    }

    printk(KERN_INFO "Memory free donen");
}

/* Macros for registering module entry and exit points. */
module_init( birthdayList_init );
module_exit( birthdayList_exit );
