#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include<linux/slab.h>
#define SIZE 5
int hashfunction(char s[]);

struct birthday{
	char name[100];
	int day;
	int month;
	int year;
	struct list_head list;
};


struct bucket{
	//birthday is a doubly-linked list, therefore, the buckets i.e. value of our hash-table(buckets) is doubly linked list
	struct birthday* value;
	//using id, we can locate our bucket
	int id;
	struct list_head bucket_list;
};

/* This function is called when the module is loaded. */
int create_list_init(void){
	int i;
	//create the hash table buckets
	struct bucket bucket_head;
	LIST_HEAD(bucket_head); // declare a list head
	
	for(int i=0; i<size; i++){
    		struct bucket curr_bucket = {
        		.id = i+1,
        		.value = NULL,
    		};
    		list_add(&curr_bucket.bucket_list, &bucket_head); // add a new entry in the list
	}

	
	



	








	int size, temp1, j, i;
	//declare the size of the hash table, in our case 5
	size = 5;
	j =0;
	struct pair *tmp;
	struct pair hash_list;
	//struct pair hash_table[size];
	//initialize the next field of every pair in hash table to null
	// initialize every value inside hash table to be 0
	
	/* it is essential only if collision is needed to be taken care of.
	while(j < size){
		hash_table[j].value = -1;
		hash_table[j].next = NULL; 
		j++;
	}
	*/

	// defines and initializes the variable birthday_list
	// and the type of birthday_list is struct list_head
	
	INIT_LIST_HEAD(&hash_list.pair_list);
	//static LIST_HEAD(birthday_list);
	//LIST_HEAD(hash_list);
	//or, we could do: 
	// struct list_head birthday_list;
	struct birthday *person1,*person2,*person3,*person4,*person5,*entry,*temp;

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

	
	struct birthday* birthdays[5] =  {person1, person2, person3, person4, person5};
	//INIT_LIST_HEAD(&hash_list_head.pair_list);
	//adding elements in the hash table
	for(i=0; i<size; i++){
		tmp = (struct pair *)kmalloc(sizeof(struct pair), GFP_KERNEL);
		//key of hash table
		strcpy(tmp->key, birthdays[i]->name);
		//value of hash table
		tmp->value = birthdays[i];
		
		list_add(&(tmp->pair_list), &(hash_list.pair_list));
				
	}
	/*
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
	*/
	//traversing a hash_table
	struct list_head *ptr;
	
	list_for_each(ptr, &(hash_list.pair_list)){
		tmp = list_entry(ptr, struct pair, pair_list);
		printk(KERN_INFO  "\n key of hash table (ie. Name) %s \n", tmp->key);
		
	}
	

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

void insert_to_hashtable(struct list_head *head_table, struct birthday *entries){
	int hash_value;
	struct list_head *ptr;
	//
	hash_value = hashfunction(entries->name);
	//traversing our hashtable to find the apppropriate location to add the entry
	list_for_each(ptr, &head_table){
		//check to see wheather this is the right bucket
		struct bucket* curr_bucket = list_entry(ptr, struct bucket, bucket_list)
		if(curr_bucket->id == hash_value){
			// call a function to add entry on bucket
			list_add(*curr_bucket.value), head pointer..		
		}
	}

}

list_empty(head) - tests whether a list is empty
list_add(new_entry, head) - adds a new entry. Insert a new entry after the specified head.
list_del(entry) - deletes entry from list.
list_for_each(pos, head) - iterate over a list





	
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
