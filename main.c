#include "shell.h"

/**
 * main - Entry point
 * @argc: unused
 * @argv: arguments vector
 *
 * Return: 0
 */
int main(int argc, char **argv)
{
	(void)argc;
	return (shell_loop(argv[0]));
}
