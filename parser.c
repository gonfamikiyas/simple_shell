#include "shell.h"

/**
 * is_cmd - determines if a file is an executable command
 * @info: the information struct
 * @file_path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(info_t *info, char *file_path)
{
	struct stat st;

	(void)info;
	if (!file_path || stat(file_path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - duplicates characters
 * @path_string: the PATH string
 * @start_idx: starting index
 * @end_idx: stopping index
 *
 * Return: pointer to new buffer
 */
char *dup_chars(char *path_string, int start_idx, int end_idx)
{
	static char buffer[1024];
	int i = 0, j = 0;

	for (j = 0, i = start_idx; i < end_idx; i++)
		if (path_string[i] != ':')
			buffer[j++] = path_string[i];
	buffer[j] = 0;
	return (buffer);
}

/**
 * find_path - finds this command in the PATH string
 * @info: the information struct
 * @path_string: the PATH string
 * @command: the command to find
 *
 * Return: full path of command if found or NULL
 */
char *find_path(info_t *info, char *path_string, char *command)
{
	int i = 0, current_position = 0;
	char *path;

	if (!path_string)
		return (NULL);
	if ((_strlen(command) > 2) && starts_with(command, "./"))
	{
		if (is_cmd(info, command))
			return (command);
	}
	while (1)
	{
		if (!path_string[i] || path_string[i] == ':')
		{
			path = dup_chars(path_string, current_position, i);
			if (!*path)
				_strcat(path, command);
			else
			{
				_strcat(path, "/");
				_strcat(path, command);
			}
			if (is_cmd(info, path))
				return (path);
			if (!path_string[i])
				break;
			current_position = i;
		}
		i++;
	}
	return (NULL);
}

