#include "main.h"

/**
 * write_with_padding - Writes with left or right padding based on flags
 * @buffer: Buffer to write
 * @main_content: Main content needing padding
 * @main_len: Length of main content
 * @padd: Padding character
 * @width: Desired width
 * @flags: Flags
 * Return: Total characters written
 */
int write_with_padding(char buffer[], char *main_content, int main_len, char padd, int width, int flags)
{
	int i, padding_len = width - main_len;
	int total_written = 0;

	for (i = 0; i < padding_len; i++)
		buffer[i] = padd;

	if (flags & F_MINUS)
	{
		if (write(1, main_content, main_len) == -1)
			return (-1);
		total_written += main_len;

		if (write(1, buffer, padding_len) == -1)
			return (-1);
		total_written += padding_len;
	}
	else
	{
		if (write(1, buffer, padding_len) == -1)
			return (-1);
		total_written += padding_len;

		if (write(1, main_content, main_len) == -1)
			return (-1);
		total_written += main_len;
	}

	return (total_written);
}

/**
 * handle_write_char - Writes a single character to the buffer with possible padding
 * @c: char type parameter
 * @buffer: Buffer to write
 * @flags: flags
 * @width: fetches width
 * Return: Number of chars
 */
int handle_write_char(char c, char buffer[], int flags, int width)
{
	buffer[0] = c;
	buffer[1] = '\0';

	if (width > 1)
		return (write_with_padding(buffer, buffer, 1, (flags & F_ZERO) ? '0' : ' ', width, flags));

	return (write(1, buffer, 1) == -1 ? -1 : 1);
}

/**
 * write_number - responsible for writing numbers
 * @is_negative: checks if value is negative
 * @ind: int type paramater
 * @buffer: Buffer to write
 * @flags: flags
 * @width: fetches width
 * @precision: int type paramater
 * Return:write_num
 */
int write_number(int is_negative, int ind, char buffer[], int flags, int width, int precision)
{
	int length = BUFF_SIZE - ind - 1;
	char padd = (flags & F_ZERO && !(flags & F_MINUS)) ? '0' : ' ';
	char extra_ch = is_negative ? '-' :
				   (flags & F_PLUS) ? '+' : (flags & F_SPCE) ? ' ' : 0;

	return (write_num(ind, buffer, flags, width, precision, length, padd, extra_ch));
}

/**
 * write_num - logic for writing formatted numbers
 * @ind: index
 * @buffer: Buffer to write
 * @flags: flags
 * @width: fetches width
 * @precision: int type paramater
 * @length: gets length
 * @padd: padding
 * @extra_c: char type
 * Return: index
 */
int write_num(int ind, char buffer[], int flags, int width, int precision, int length, char padd, char extra_c)
{
	if (precision == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
	{
		if (width == 0)
			return (0);
		else
			buffer[ind] = ' ';
	}

	while (precision > length)
	{
		buffer[--ind] = '0';
		length++;
	}

	if (extra_c)
	{
		buffer[--ind] = extra_c;
		length++;
	}

	if (width > length)
		return (write_with_padding(buffer, &buffer[ind], length, padd, width, flags));

	return (write(1, &buffer[ind], length) == -1 ? -1 : length);
}

/**
 * write_unsgnd - Writes unsigned integers to standard output
 * @ind: index
 * @buffer: Buffer to write
 * @flags: flags
 * @width: fetches width
 * @precision: int type
 * Return: length
 */

int write_unsgnd(int ind, char buffer[], int flags, int width, int precision)
{
	int length = BUFF_SIZE - ind - 1;
	char padd = (flags & F_ZERO && !(flags & F_MINUS)) ? '0' : ' ';

	if (precision == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		return (0);

	while (precision > length)
	{
		buffer[--ind] = '0';
		length++;
	}

	if (width > length)
		return (write_with_padding(buffer, &buffer[ind], length, padd, width, flags));

	return (write(1, &buffer[ind], length) == -1 ? -1 : length);
}

/**
 * write_pointer - Writes a pointer (address) in a formatted manner
 * @ind: index
 * @buffer: Buffer to write
 * @flags: flags
 * @width: fetches width
 * Return: length
 */
int write_pointer(int ind, char buffer[], int width, int flags)
{
	int length = BUFF_SIZE - ind - 1;

	buffer[--ind] = 'x';
	buffer[--ind] = '0';

	if (width > length + 2)
		return (write_with_padding(buffer, &buffer[ind], length, ' ', width, flags));

	return (write(1, &buffer[ind], BUFF_SIZE - ind - 1) == -1 ? -1 : BUFF_SIZE - ind - 1);
}
