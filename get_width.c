#include "main.h"

/**
 * get_width - Calculates the width for printing
 * @format: Formatted string in which to print the arguments.
 * @i: Pointer to current index in the formatted string.
 * @list: List of arguments.
 *
 * Return: width.
 */
int get_width(const char *format, int *i, va_list list)
{
	int width = 0;
	int curr_i = *i + 1;

	if (format[curr_i] == '*')
	{
		*i = curr_i;
		return (va_arg(list, int));
	}
	while (is_digit(format[curr_i]))
	{
		width = width * 10 + (format[curr_i] - '0');
		curr_i++;
	}
	*i = curr_i - 1;
	return (width);
}
