#include "shell.h"

/**
 * _memset - fills memory with a constant byte
 * @mem_area: the pointer to the memory area
 * @byte: the byte to fill *mem_area with
 * @num_bytes: the amount of bytes to be filled
 * Return: (mem_area) a pointer to the memory area mem_area
 */
char *_memset(char *mem_area, char byte, unsigned int num_bytes)
{
	unsigned int i;

	for (i = 0; i < num_bytes; i++)
		mem_area[i] = byte;
	return (mem_area);
}

/**
 * ffree - frees a string of strings
 * @str_array: string of strings
 */
void ffree(char **str_array)
{
	char **temp = str_array;

	if (!str_array)
		return;
	while (*str_array)
		free(*str_array++);
	free(temp);
}

/**
 * _realloc - reallocates a block of memory
 * @previous_ptr: pointer to previous malloc'ated block
 * @previous_size: byte size of previous block
 * @new_size: byte size of new block
 *
 * Return: pointer to the resized memory block.
 */
void *_realloc(void *previous_ptr, unsigned int previous_size, unsigned int new_size)
{
	char *new_ptr;

	if (!previous_ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(previous_ptr), NULL);
	if (new_size == previous_size)
		return (previous_ptr);

	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);

	previous_size = previous_size < new_size ? previous_size : new_size;
	while (previous_size--)
		new_ptr[previous_size] = ((char *)previous_ptr)[previous_size];
	free(previous_ptr);
	return (new_ptr);
}

