#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/slab.h>       // For kmalloc, kzalloc
#include <linux/vmalloc.h>    // For vmalloc
#include <linux/gfp.h>        // For GFP_KERNEL
#include <linux/mm.h>         // For get_free_pages
#include <linux/highmem.h>    // For free_pages

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Kernel Memory Allocator Tester");
MODULE_VERSION("0.1");

#define ALLOC_SIZE 1024 // 1 KB for testing allocation sizes

// Function pointers for memory allocation
static void *kmalloc_ptr;
static void *kzalloc_ptr;
static void *vmalloc_ptr;
static unsigned long page_ptr;

// init function for the module
static int __init allocator_init(void)
{
    printk(KERN_INFO "Allocator Tester: Module loaded\n");

    // Test kmalloc
    kmalloc_ptr = kmalloc(ALLOC_SIZE, GFP_KERNEL);
    if (kmalloc_ptr)
        printk(KERN_INFO "kmalloc: allocated %d bytes\n", ALLOC_SIZE);

    // Test kzalloc
    kzalloc_ptr = kzalloc(ALLOC_SIZE, GFP_KERNEL);
    if (kzalloc_ptr)
        printk(KERN_INFO "kzalloc: allocated %d zeroed bytes\n", ALLOC_SIZE);

    // Test vmalloc
    vmalloc_ptr = vmalloc(ALLOC_SIZE);
    if (vmalloc_ptr)
        printk(KERN_INFO "vmalloc: allocated %d bytes\n", ALLOC_SIZE);

    // Test get_free_pages (1 page)
    page_ptr = __get_free_pages(GFP_KERNEL, 0); // 2^0 = 1 page
    if (page_ptr)
        printk(KERN_INFO "get_free_pages: allocated 1 page\n");

    return 0;  // Return 0 indicates successful module loading
}

// exit function for the module
static void __exit allocator_exit(void)
{
    if (kmalloc_ptr)
        kfree(kmalloc_ptr);

    if (kzalloc_ptr)
        kfree(kzalloc_ptr);

    if (vmalloc_ptr)
        vfree(vmalloc_ptr);

    if (page_ptr)
        free_pages(page_ptr, 0);

    printk(KERN_INFO "Allocator Tester: Module unloaded\n");
}

module_init(allocator_init);
module_exit(allocator_exit);