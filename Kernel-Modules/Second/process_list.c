#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/types.h>
#include <linux/list.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>

struct task_struct *task;
struct list_head   *list;

int simple_init(void) {
  list_for_each(list, &(init_task.children)) {
    task = list_entry(list, struct task_struct, sibling);
    for_each_process(task)
      printk(KERN_INFO "Pid: %u - Exe. name: %s - Process state: %d ", task->pid, task->comm, task->state);
  }
}

void simple_exit(void) {
  printk(KERN_INFO "Exiting");
}

module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Process list");
MODULE_AUTHOR("Mattia Lancellotti");
