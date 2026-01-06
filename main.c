#include "shell.h"

/**
 * main - Entry point
 * @argc: argument count (unused)
 * @argv: argument vector
 *
 * Return: 0 on success
 */
int main(int argc, char **argv)
{
	(void)argc;
	return (shell_loop(argv[0]));
}
