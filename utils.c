#include "main.h"

/**
 * is_printable - Check if a char is printable.
 * @c: Char to evaluate.
 * Return: 1 if printable, 0 otherwise.
 */
int is_printable(char c)
{
	return ((c >= 32 && c < 127) ? 1 : 0);
}

/**
 * append_hexa_code - Append ASCII value in hexadecimal code to buffer.
 * @ascii_code: ASCII value.
 * @buffer: Char array.
 * @i: Starting index.
 * Return: Always 3.
 */
int append_hexa_code(char ascii_code, char buffer[], int i)
{
	static const char map_to[] = "0123456789ABCDEF";

	ascii_code = (ascii_code < 0) ? -ascii_code : ascii_code;

	buffer[i++] = '\\';
	buffer[i++] = 'x';
	buffer[i++] = map_to[ascii_code / 16];
	buffer[i] = map_to[ascii_code % 16];

	return (3);
}

/**
 * is_digit - Check if a char is a digit.
 * @c: Char to evaluate.
 * Return: 1 if a digit, 0 otherwise.
 */
int is_digit(char c)
{
	return ((c >= '0' && c <= '9') ? 1 : 0);
}

/**
 * convert_size_number - Cast a number to the specified size.
 * @num: Number for casting.
 * @size: Type for casting.
 * Return: Casted value.
 */
long int convert_size_number(long int num, int size)
{
	if (size == S_LONG)
	{return (num);
	}
	return ((size == S_SHORT) ? (short)num : (int)num);
}

/**
 * convert_size_unsgnd - Cast a number to the specified unsigned size.
 * @num: Number for casting.
 * @size: Type for casting.
 * Return: Casted value.
 */
long int convert_size_unsgnd(unsigned long int num, int size)
{
	if (size == S_LONG)
	{return (num);
	}
	return ((size == S_SHORT) ? (unsigned short)num : (unsigned int)num);
}
