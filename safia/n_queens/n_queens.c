// Assignement name : n_queens

// Expected files : *.c *.h

// Allowed functions : atoi, fprintf, write, calloc, malloc, free, realloc, stdout, stderr

// -------------------------------------------------------------------------

// Write a program that will print all the solutions to the n queens problem
// for a n given as argument.
// We will not test with negative values.
// The order of the solutions is not important.

// You will display the solutions under the following format :
// <p1> <p2> <p3> ... \n
// where pn are the line index of the queen in each colum starting from 0.

// For example this should work :
// $> ./n_queens 2 | cat -e

// $> ./n_queens 4 | cat -e
// 1 3 0 2$
// 2 0 3 1$

// $> ./n_queens 7 | cat -e
// 0 2 4 6 1 3 5$
// 0 3 6 2 5 1 4$
// etc...

#include <stdio.h>
#include <stdlib.h>

int ft_abs(int n)
{
	return (n < 0 ? -n : n);
}

int is_safe(int *board, int col, int row)
{
	int	prev = 0;

	while (prev < col)
	{
		if (board[prev] == row) // pourquoi
			return (0);
		if (ft_abs(board[prev] - row) == col - prev) // pourquoi
			return (0);
		prev++;
	}
	return (1);
}

void	print_solution(int *board, int n)
{
	int i = 0;

	while (i < n)
	{
		fprintf(stdout, "%d", board[i]); //pourquoi fprintf plutot que printf
		if (i < n - 1)
			fprintf(stdout, " ");
		i++;
	}
	fprintf(stdout, "\n");
}

void	solve(int *board, int col, int n)
{
	int row = 0;

	if (col == n)
	{
		print_solution(board, n);
		return;
	}
	while (row < n)
	{
		if (is_safe(board, col, row))
		{
			board[col] = row;
			solve(board, col + 1, n);
		}
		row++;
	}

}

int	main(int argc, char **argv)
{
	int	*board;

	// 1. VÉRIFICATION ARGUMENTS
	if (argc != 2)
		return (1);
	int n = atoi(argv[1]);
	if (n <= 0)
		return (1);

	// 2. ALLOCATION
	board = malloc(sizeof(int) * n);
	if (!board)
		return (1);

	// 3. RÉSOLUTION
	solve(board, 0, n);

	// 4. LIBÉRATION
	free(board);
	return (0);
}