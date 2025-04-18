#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched/signal.h>
#include <linux/mm.h>
#include <linux/slab.h>
#include <linux/timer.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Pranav Hemanth");
MODULE_DESCRIPTION("A kernel module to monitor process tree and memory allocations");

static struct timer_list monitor_timer;
static pid_t target_pid = 1;
module_param(target_pid, int, 0644);
MODULE_PARM_DESC(target_pid, "PID of the parent process to monitor");

static void print_process_info(struct task_struct *task, int depth)
{
    struct task_struct *child;
    struct list_head *list;
    unsigned long vm_size = 0;
    unsigned long stack_vm = 0;
    char indent[256] = "";
    int i;

    // Create indentation
    for (i = 0; i < depth * 2 && i < 254; i += 2)
    {
        indent[i] = '|';
        indent[i + 1] = ' ';
    }
    indent[i] = '\0';

    if (task->mm)
    {
        vm_size = task->mm->total_vm << (PAGE_SHIFT - 10);  // Convert to KB
        stack_vm = task->mm->stack_vm << (PAGE_SHIFT - 10); // Convert to KB
    }

    printk(KERN_INFO "%s├─ Process: %s[%d] (Parent: %d)\n", indent, task->comm, task->pid, task->real_parent->pid);
    printk(KERN_INFO "%s   ├─ Virtual Memory: %lu KB\n", indent, vm_size);
    printk(KERN_INFO "%s   └─ Stack Size: %lu KB\n", indent, stack_vm);

    // Print children recursively
    list_for_each(list, &task->children)
    {
        child = list_entry(list, struct task_struct, sibling);
        print_process_info(child, depth + 1);
    }
}

static void monitor_processes(struct timer_list *t)
{
    struct task_struct *task;
    bool found = false;

    // Find and print process tree for target PID
    for_each_process(task)
    {
        if (task->pid == target_pid)
        {
            printk(KERN_INFO "\n=== Process Tree and Memory Info (Parent PID: %d) ===\n", target_pid);
            print_process_info(task, 0);
            found = true;
            break;
        }
    }

    if (!found)
    {
        printk(KERN_INFO "Process with PID %d not found\n", target_pid);
    }

    // Reschedule timer for next check
    mod_timer(&monitor_timer, jiffies + msecs_to_jiffies(1000));
}

static int __init process_monitor_init(void)
{
    printk(KERN_INFO "Process Monitor Module initialized, monitoring PID: %d\n", target_pid);

    // Setup timer for periodic monitoring
    timer_setup(&monitor_timer, monitor_processes, 0);
    mod_timer(&monitor_timer, jiffies + msecs_to_jiffies(1000));

    return 0;
}

static void __exit process_monitor_exit(void)
{
    del_timer_sync(&monitor_timer);
    printk(KERN_INFO "Process Monitor Module unloaded\n");
}

module_init(process_monitor_init);
module_exit(process_monitor_exit);