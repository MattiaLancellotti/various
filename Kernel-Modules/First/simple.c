#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/types.h>
#include <linux/slab.h>

#define ARR_SIZE 5

struct birthday {
  int day, month, year;
  struct list_head list;
};

static LIST_HEAD(birthday_list);  //MACRO to define a new list_head type

struct birthday *create_birth(int, int, int);

/* Questa funzine viene chiamata quando viene caricato il modulo. */
int simple_init(void)
{
  struct birthday *person;
  size_t i;

  printk(KERN_INFO "Inizializzazione della struttura dati");

  for (i=0; i<ARR_SIZE; i++) {
    person = create_birth(i, i, i);
    list_add_tail(&person->list, &birthday_list);
  }

  return 0;
}

struct birthday *create_birth(int day, int month, int year)
{
  struct birthday *new = kmalloc(sizeof(struct birthday), GFP_KERNEL);
  new->day = day;
  new->month = month;
  new->year = year;

  INIT_LIST_HEAD(&new->list);

  return new;
}

/* Questa funzione viene chiamata quando il modulo viene rimosso. */
void simple_exit(void)
{
  struct birthday *ptr, *next;

  list_for_each_entry_safe(ptr, next, &birthday_list, list) {
    printk(KERN_INFO "Day: %d\nMonth: %d\nYear: %d\n", ptr->day, ptr->month, ptr->year);
    list_del(&ptr->list);
    kfree(ptr);
  }
}

/* Macro per la registrazione di ingresso e di uscita del modulo. */
module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("Mattia Lancellotti");
