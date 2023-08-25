#include "main.h"

/************************* PRINT CHAR *************************/
/**
 * print_chars - Prints a character
 * @types: List of arguments
 * @buffer: Buffer array to handle print
 * @flags:  to Calculate active flags
 * @width: the Width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */

int print_chars(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	char c = va_arg(types, int);
	return (handle_write_char(c, buffer, flags, width, precision, size));
}

/************************* PRINT A STRING *************************/
/**
 * print_string - Prints a string
 * @types: List of arguments
 * @buffer: Buffer array to handle print
 * @flags: to Calculate active flags
 * @width: the width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */

int print_string(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	int length = 0, j;
	char *str = va_arg(types, char *);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = "      ";
	}
	while (str[length] != '\0')
		length++;
	if (precision >= 0 && precision < length)
		length = precision;
	if (width > length)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], length);
			for (j = width - length; j > 0; j--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (j = width - length; j > 0; j--)
				write(1, " ", 1);
			write(1, &str[0], length);
			return (width);
		}
	}
	return (write(1, str, length));
}

/************************* PRINT PERCENT SIGN *************************/
/**
 * print_percent - Prints a percent sign
 * @types: List of arguments
 * @buffer: Buffer array to handle print
 * @flags:  to Calculate active flags
 * @width: to get the width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */

int print_percent(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}

/************************* PRINT INT *************************/
/**
 * print_int - Print int
 * @types: List of arguments
 * @buffer: Buffer array to handle print
 * @flags:  to Calculate active flags
 * @width: to get the width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */

int print_int(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	int j = BUFF_SIZE - 2;
	int is_negative = 0;
	long int ln = va_arg(types, long int);
	unsigned long int num;
	ln = convert_size_number(ln, size);
	if (ln == 0)
		buffer[j--] = '0';
	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)ln;
	if (ln < 0)
	{
		num = (unsigned long int)((-1) * ln);
		is_negative = 1;
	}
	while (num > 0)
	{
		buffer[j--] = (num % 10) + '0';
		num /= 10;
	}
	j++;
	return (write_number(is_negative, i, buffer, flags, width, precision, size));
}

/************************* PRINT BINARY *************************/
/**
 * print_binary - Prints an unsigned number
 * @types: List of arguments
 * @buffer: Buffer array to handle print
 * @flags: to Calculate active flags
 * @width: to get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Numbers of char printed.
 */

int print_binary(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	unsigned int i, j, k, sum;
	unsigned int a[32];
	int count;
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	i = va_arg(types, unsigned int);
	j = 2147483648; /* (2 ^ 31) */
	a[0] = i / j;
	for (k = 1; k < 32; k++)
	{
		j /= 2;
		a[k] = (i / j) % 2;
	}
	for (k = 0, sum = 0, count = 0; k < 32; k++)
	{
		sum += a[k];
		if (sum || k == 31)
		{
			char z = '0' + a[k];
			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}
