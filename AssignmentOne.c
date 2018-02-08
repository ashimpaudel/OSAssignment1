#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/slab.h>

#define NUM_OF_PERSON    5
int hashfunction(char s[]);
/* Example struct we will use. */
typedef struct _birthday {
    char name[100];
    int day;
    int month;
    int year;
    struct list_head list;
}birthday;



typedef struct _bucket{
	//birthday is a doubly-linked list, therefore, the buckets i.e. value of our hash-table(buckets) is doubly linked list
	birthday* value;
	//LIST_HEAD(value);
	//using id, we can locate our bucket
	int id;
	struct list_head bucket_list;
}bucket;


/* Declare and init the head of the linked list. */
LIST_HEAD(birthday_list);
LIST_HEAD(bucket_list_glob);
LIST_HEAD(btt);

/* This function is called when the module is loaded. */
int birthdayList_init(void)
{
           printk(KERN_INFO "Loading Modulen");


    char array_persons[NUM_OF_PERSON][100];
    strcpy(array_persons[0], "Ashim");
    strcpy(array_persons[1], "ram");
    strcpy(array_persons[2], "Prajjwal");
    strcpy(array_persons[3], "Utsab");
    strcpy(array_persons[4], "Ashish");
    
    /* Allocate 5 birthdays from kernel */
    birthday *person;
    bucket *each_bucket;
    int i, hashvalue;
    for(i = 0; i < NUM_OF_PERSON; i++)
    {
        /* Request malloc to the kernel. */
        person = kmalloc(sizeof(*person), GFP_KERNEL);
        /* Assign value to the struct. */
        person->day = i+1;
        person->month = i+1;
        person->year = i+1;
        strcpy(person->name, array_persons[i]);
        /* Init the list within the struct. */
        INIT_LIST_HEAD(&person->list);
        /* Add this struct to the tail of the list. */
        list_add_tail(&person->list, &birthday_list);
    }


    
    
    //describe the array that stores all the person , array of birthday
    birthday birthdays_array[NUM_OF_PERSON];
    i = 0;
    birthday *ptr;
    bucket *bucptr;
    list_for_each_entry(ptr, &birthday_list, list)
    {
        birthdays_array[i].day = ptr->day;
        birthdays_array[i].month = ptr ->month;
        birthdays_array[i].year = ptr ->year;
        strcpy(birthdays_array[i].name, array_persons[i]);
        printk(KERN_INFO "day: %d, month: %d, year: %dn",ptr->day,ptr->month, ptr->year);
        i++;
    }

    //hashtable of buckets with bucket_list_glob pointing at the head of the list
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



    
    


    printk(KERN_INFO "Display the list:n");

    /* Go thru the list and print. */
    i = 0;
    list_for_each_entry(ptr, &birthday_list, list)
    {
        printk(KERN_INFO "name: %s, day: %d, month: %d, year: %d\n",
                ptr->name,
                ptr->day,
                ptr->month,
                ptr->year);
        person = kmalloc(sizeof(*person), GFP_KERNEL);
        /* Assign value to the struct. */
        strcpy(person->name , birthdays_array[i].name);
        person->day = birthdays_array[i].day;
        person->month =birthdays_array[i].month;
        person->year = birthdays_array[i].year;
        /* Init the list within the struct. */
        INIT_LIST_HEAD(&person->list);
         
        hashvalue = hashfunction(ptr->name);
        printk("hahsh value is %d", hashvalue);
        list_for_each_entry(bucptr, &bucket_list_glob, bucket_list)
        {
           if (bucptr->id == hashvalue && bucptr->value != NULL)
                list_add_tail(&person->list, &bucptr->value->list);
           if (bucptr->id == hashvalue && bucptr->value == NULL)
                bucptr->value = person;           
        }
        i++;
    }




    printk(KERN_INFO "It works upto here");
    

    i = 0;


    
    //printing everything, even the collided ones
    birthday* tmp;
    
    list_for_each_entry(bucptr, &bucket_list_glob, bucket_list)
    {
        //ptr = bucptr->value;
        if (bucptr->value != NULL)
        {
            printk("type of bucptr");
            btt = bucptr->value->list;
            printk("type of bucptr %s",bucptr->value->name);
            //ptr = bucptr->value;
            struct list_head* iter;
            list_for_each(iter, &(bucptr->value->list))
            {
                
                //ptr = ptr->list.next;
                birthday* tmp= list_entry(iter, birthday,list );
                printk("name: %s, day: %d, month: %d, year %d",tmp->name, tmp->day, tmp->month, tmp->year);
                
                
                
                
                
            }
         }
            
    } 



    
    printk(KERN_INFO "Display donen");

           return 0;
}


//hashfunction used: sums up the ascii value of all the character and mods it by the size of hash_table
int hashfunction(char s[]){
     int i, m, ascii;
     m = 5;
     while(s[i]!='\0'){
	ascii += (int)s[i];
	i++;
	}
     return ascii%5;
 }



/* This function is called when the module is removed. */
void birthdayList_exit(void)
{
    printk(KERN_INFO "Removing Module");

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

    printk(KERN_INFO "Memory free done");
}

/* Macros for registering module entry and exit points. */
module_init( birthdayList_init );
module_exit( birthdayList_exit );
