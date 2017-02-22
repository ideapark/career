/*
 * Memory Segments
 *
 * - stack
 * - heap
 * - static
 * - text
 *
 * The text segment is near the "bottom" of memory; that is at addresses near
 * zero.
 *
 * The static segment is often just above the text segment.
 *
 * The stack is near the top of memory; that is, near the highest addresses in
 * the virtual address space. As the stack expand, it grows down toward smaller
 * addresses.
 *
 * The heap is often above the static segment. As it expands, it grows up toward
 * larger addresses.
 */
#include <stdio.h>
#include <stdlib.h>

int global;

int main()
{
	int local = 5;
	void *p = malloc(8);

	printf("Address of   main is %p\n", main);
	printf("Address of global is %p\n", &global);
	printf("Address of  local is %p\n", &local);
	printf("Address of      p is %p\n", p);

	return 0;
}
