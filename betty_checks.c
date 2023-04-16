#include <stdio.h>

/**
 * main - Entry point of the program
 *
 * This program prints "command line code that passes the Betty checks" to the standard output.
 *
 * Return: Always 0 (Success)
 */

int main(int argc, char **argv)

{
	if(argc != 2)

	{
		printf("Usage: %s <argument>\n", argv[0]);
		return (1);
	}

	printf("You entered: %s\n", argv[1]);
	return (0);

}
