// Assignment name: filter
// Expected files: filter.c
// Allowed functions: read, write, strlen, memmem, memmove, malloc, calloc,
// realloc, free, printf, fprintf, stdout, stderr, perror
// --------------------------------------------------------------------------------

// Write a program that will take one and only one argument.

// Your program will then read from stdin and write all the content read in stdout
// except that every occurrence of s must be replaced by '*' (as many as the length
// of s). Your program will be tested with random buffer sizes, using a custom read
// function. Therefore the buffer being set in your program will be filled with a
// different number of chars each new call.


// For example:

// ./filter bonjour
// will behave in the same way as:
// sed 's/bonjour/*******/g'

// ./filter abc
// will behave in the same way as:
// sed's/abc/***/g'

// More generally your program must be the equivalent of the shell script filter.sh
// present in this directory (you can compare your program with it).

// In case of error during a read or a malloc, you must write "Error: " followed by
// the error message in stderr and return 1.

// If the program is called without arguments or with an empty argument or with multiple
// arguments, it must return 1.

// For example this should work:

// $> echo 'abcdefaaaabcdeabcabcdabc' | ./filter abc | cat -e
// ***defaaa***de******d***$
// $> echo 'ababcabababc' | ./filter ababc | cat -e
// *****ab*****$
// $>

#include <stdio.h>	// printf, perror
#include <unistd.h> // read, STDIN_FILENO, STDOUT_FILENO
#include <stdlib.h> // malloc, free
#include <string.h> // strlen
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
#endif

void	ft_filter(char *str, char *filter)
{
	int len = strlen(filter);
	int i = 0;
	while (str[i])
	{
		int j = 0;
		while (str[i + j] == filter[j])
			j++;
		if (j == len)
		{
			int k = 0;
			while (k++ < len)
				write(1, "*", 1);
			i += j;
		}
		else
			write(1, &str[i++], 1);
	}
}

int	main (int argc, char **argv)
{
	char buffer[999999] = {0};
	int	i = 0;
	int	nb_read = 1;

	if (argc != 2 || argv[1][0] == '\0' || !argv[1])
		return (1);

	while (nb_read > 0)
	{
		nb_read = read(STDIN_FILENO, &buffer[i], BUFFER_SIZE);
		if (nb_read < 0)
		{
			perror("Error");
			return (1);
		}
		i += nb_read;
	}
	ft_filter(buffer, argv[1]);
	return (0);
}
