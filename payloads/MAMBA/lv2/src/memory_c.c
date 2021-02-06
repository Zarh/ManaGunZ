#include <lv2/memory.h>

void *malloc(size_t size)
{
	return alloc(size, 0x27);
}

void free(void *ptr)
{
	dealloc(ptr, 0x27);
}

void *kalloc(size_t size)
{
	return alloc(size, 0x35);
}

void kfree(void *ptr)
{
	dealloc(ptr, 0x35);
}

