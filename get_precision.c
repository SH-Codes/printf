#include "main.h"

/**
 * get_precision - Calculates the precision for printing
 * @format: Formatted string in which to print the arguments
 * @i: Current index in the format string.
 * @list: List of arguments.
 *
 * Return: Precision.
 */
int get_precision(const char *format, int *i, va_list list)
{
	int precision = -1;

	if (format[*i + 1] != '.')
	{
		return (precision);
	}

	int curr_i = *i + 2;

	while (format[curr_i] != '\0')
	{
		if (is_digit(format[curr_i]))
		{
			if (precision == -1)
			{
				precision = 0;
				precision = (precision * 10) + (format[curr_i] - '0');
			}
		}
		else if (format[curr_i] == '*')
		{
			precision = va_arg(list, int);
			curr_i++;
			break;
		}
		else
			break;

		curr_i++;
	}

	*i = curr_i - 1;

	return (precision);
}
