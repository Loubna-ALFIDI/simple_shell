#include "shell.h"

/**
 * reverse - reverse a string
 * @str: string
 * @length: length of string
 */
void reverse(char str[], int length)
{
	int start = 0;
	int end = length - 1;
	char temp;

	while (start < end)
	{
		temp = str[start];
		str[start] = str[end];
		str[end] = temp;
		start++;
		end--;
	}
}

/**
 * _itoa - convert an integer into its ASCII string representation.
 * @num: The integer value that you want to convert to a string.
 * @str: A character array where the resulting ASCII string will be stored.
 * @base: The numeric base used for conversion.
 * Return: returns the constructed ASCII string.
 */
char *_itoa(int num, char *str, int base)
{
	int i = 0;
	int isNegative = 0;
	int rem;

	if (num == 0)
	{
		str[i++] = '0';
		str[i] = '\0';
		return (str);
	}
	if (num < 0 && base == 10)
	{
		isNegative = 1;
		num = -num;
	}
	while (num != 0)
	{
		rem = num % base;
		str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
		num = num / base;
	}


	if (isNegative)
		str[i++] = '-';

	str[i] = '\0';
	reverse(str, i);
	return (str);
}
int my_atoi(const char *str)
{
	int result = 0;
	bool negative = false;

	if (*str == '-')
	{
		negative = true;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return negative ? -result : result;
}
