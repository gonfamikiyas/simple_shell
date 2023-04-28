#include "shell.h"

/**
 * _myhistory - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - sets alias to string
 * @info: parameter struct
 * @alias_str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info_t *info, char *alias_str)
{
	char *alias_pointer, alias_char;
	int result;

	alias_pointer = _strchr(alias_str, '=');
	if (!alias_pointer)
		return (1);
	alias_char = *alias_pointer;
	*alias_pointer = 0;
	result = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, alias_str, -1)));
	*alias_pointer = alias_char;
	return (result);
}

/**
 * set_alias - sets alias to string
 * @info: parameter struct
 * @alias_str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *info, char *alias_str)
{
	char *alias_pointer;

	alias_pointer = _strchr(alias_str, '=');
	if (!alias_pointer)
		return (1);
	if (!*++alias_pointer)
		return (unset_alias(info, alias_str));

	unset_alias(info, alias_str);
	return (add_node_end(&(info->alias), alias_str, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @alias_node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *alias_node)
{
	char *pointer = NULL, *alias = NULL;

	if (alias_node)
	{
		pointer = _strchr(alias_node->str, '=');
		for (alias = alias_node->str; alias <= pointer; alias++)
			_putchar(*alias);
		_putchar('\'');
		_puts(pointer + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _myalias(info_t *info)
{
	int index = 0;
	char *alias_pointer = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (index = 1; info->argv[index]; index++)
	{
		alias_pointer = _strchr(info->argv[index], '=');
		if (alias_pointer)
			set_alias(info, info->argv[index]);
		else
			print_alias(node_starts_with(info->alias, info->argv[index], '='));
	}

	return (0);
}
