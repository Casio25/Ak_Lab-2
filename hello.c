#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/ktime.h>
#include <linux/slab.h>

struct head_list {
struct head_list *next;
	ktime_t time;
};

static struct head_list *head;

static int amount = 1;
module_param(amount, uint, 0444);
MODULE_PARM_DESC(amount, "Amount of outputs");

static int __init thisinit(void)
{
uint i;

struct head_list *first, *second;

head = kmalloc(sizeof(struct head_list *), GFP_KERNEL);

first = head;
if (amount == 0) {
	pr_warn("Amount equals 0");
} else if (amount >= 5 && amount <= 10) {
	pr_warn("Amount value between 5 and 10");
} else if (amount > 10) {
	pr_warn("Amount biger than 10");
return -EINVAL;
}

for (i = 0; i < amount; i++) {
	first->next = kmalloc(sizeof(struct head_list), GFP_KERNEL);
	first->time = ktime_get();
	pr_info("Hello World!");
	second = first;
	first = first->next;
}

if (amount != 0) {
	kfree(second->next);
	second->next = NULL;
}

pr_info("Amount: %d\n", amount);

return 0;
}

static void __exit thisexit(void)
{
struct head_list *var;

while (head != NULL && amount != 0) {
	var = head;
	pr_info("Time: %lld", var->time);
	head = var->next;
	kfree(var);
}
pr_info("");
}

module_init(thisinit);
module_exit(thisexit);

MODULE_AUTHOR("Kolomiets Michael IO-06");
MODULE_DESCRIPTION("lab 6");
MODULE_LICENSE("Dual BSD/GPL");
