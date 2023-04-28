#include "shell.h"

/**
 * interactive - returns true if shell is in interactive mode
 * @info: struct address
 * Return: 1 if interactive mode, 0 otherwise
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}
/**
 * is_delim - checks if character is a delimiter
 * @character: the char to check
 * @delimiter: the delimiter string
 * Return: 1 if true, 0 if false
 */
int is_delim(char character, char *delimiter)
{
	while (*delimiter)
		if (*delimiter++ == character)
			return (1);
	return (0);
}
/**
 * _isalpha - checks for alphabetic character
 * @character: The character to input
 * Return: 1 if c is alphabetic, 0 otherwise
 */
int _isalpha(int character)
{
	if ((character >= 'a' && character <= 'z') || (character >= 'A' && character <= 'Z'))
		return (1);
	else
		return (0);
}
/**
 * _atoi - converts a string to an integer
 * @string: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */
int _atoi(char *string)
{
	int index, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (index = 0;  string[index] != '\0' && flag != 2; index++)
	{
		if (string[index] == '-')
			sign *= -1;

		if (string[index] >= '0' && string[index] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (string[index] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
