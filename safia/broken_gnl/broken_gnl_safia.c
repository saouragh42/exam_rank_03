// Assignment name : broken_gnl
// Expected files : get_next_line.c get_next_line.h
// Allowed functions: read, free, malloc


// Write a function named get_next_line which prototype should be:
// char *get_next_line(int fd);


// Your function must return a line that has been read from the file descriptor passed as parameter. What we call a "line that has been read" is a succesion of 0 to n characters that end with '\n' (ascii code 0x0a) or with End Of File (EOF).

// The line should be returned including the '\n' in case there is one at the end of the line that has been read. When you've reached the EOF, you must store the current buffer in a char * and return it. 
// If the buffer is empty you must return NULL.
// In case of error return NULL. 
// In case of not returning NULL, the pointer should be free-able. 
// Your program will be compiled with the flag -D BUFFER_SIZE=xx, which has to be used as the buffer size for the read calls in your functions.

// Your function must be memory leak free. When you've reached the EOF, your function should keep 0 memory allocated with malloc, except the line that has been returned.

// Calling your function get_next_line in a loop will therefore allow you to read the text available on a file descriptor one line at a time until the end of the text, no matter the size of either the text or one of its lines.

// Make sure that your function behaves well when it reads from a file, from the standard output, from a redirection, etc...

// No call to another function will be done on the file descriptor between 2 calls of get_next_line. Finally we consider that get_next_line has an undefined behaviour when reading from a binary file.

#include "broken_gnl_safia.h"

//  Cherche la première occurrence du caractère c dans la chaîne s
char	*ft_strchr(char *s, int c)
{
	int	i = 0;
	while (s[i] && s[i] != c) //fixed: added check for s[i] not null
		i++;
	if (s[i] == c)
		return (s + i);
	else
		return (NULL);
}

// Copie n octets de src vers dest
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i = 0; //fixed
	while (i < n) // fixed
	{
		((char *)dest)[i] = ((char *)src)[i]; //fixed
		i++; //fixed
	}
	// while (--n > 0)
	// 	((char *)dest)[n - 1] = ((char *)src)[n - 1];
	return (dest);
}

// Calcule la longueur d'une chaîne de caractères
size_t	ft_strlen(char *s)
{
	size_t	ret = 0;
	if (!s) // fixed
		return (0); // fixed 
	while (*s)
	{
		s++;
		ret++;
	}
	return (ret);
}

// Concatène size2 octets de s2 à la fin de s1
int	str_append_mem(char **s1, char *s2, size_t size2)
{
	size_t	size1 = ft_strlen(*s1);
	char	*tmp = malloc(size2 + size1 + 1);
	if (!tmp)
		return (0);
	if (*s1) // fixed
		ft_memcpy(tmp, *s1, size1); //fixed
	//ft_memcpy(tmp, *s1, size1);
	ft_memcpy(tmp + size1, s2, size2);
	tmp [size1 + size2] = 0;
	free(*s1);
	*s1 = tmp;
	return (1);
}

// Concatène la chaîne complète s2 à la fin de s1
int	str_append_str(char **s1, char *s2)
{
	return (str_append_mem(s1, s2, ft_strlen(s2)));
}

// Copie n octets de src vers dest, même si les zones se chevauchent
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	// if (dest > src)
	if (dest < src) // fixed : copie normale pas de chevauchement quand dest est plus petit se trouve a gauche Mémoire:  [dest....][src.....]
		return (ft_memcpy(dest, src, n));
	else if (dest == src)
		return (dest);
	// size_t	i = ft_strlen((char *)src) - 1;
	size_t	i = n; // fixed
	// while (i >= 0)
	while (i > 0) // fixed
	{
		i--; //fixed : before using i
		((char *)dest)[i] = ((char *)src)[i];
		// i--;
	}
	return (dest);
}

char	*get_next_line(int fd)
{
	static char	b[BUFFER_SIZE + 1] = "";
	char	*ret = NULL;
	int		n = 0;

	char	*tmp = ft_strchr(b, '\n'); // cherche le caractère '\n' dans le buffer b
	while (!tmp)
	{
		if (!str_append_str(&ret, b)) // concatène le contenu de b à ret
			return (NULL);
		b[0] = 0; // fixed: vide le buffer b
		int	read_ret = read(fd, b, BUFFER_SIZE);
		if (read_ret == -1)
			return (NULL);
		if (read_ret == 0) // fixed: EOF reached
			break; // fixed
		b[read_ret] = 0;
		tmp = ft_strchr(b, '\n'); // fixed: cherche à nouveau le caractère '\n' dans le buffer b
	}
	if (tmp) // fixed 
	{
		n = tmp - b + 1; // fixed: number of characters to copy INCLUDING \n
		if (!str_append_mem(&ret, b, n)) // concatenate n characters from b to ret
		{
			free(ret);
			return (NULL);
		}
		ft_memmove(b, tmp + 1, ft_strlen(tmp + 1) + 1); // fixed: copie le reste du buffer après le \n au début de b
	}
	else // fixed: si aucun \n n'a été trouvé
	{
		b[0] = 0; // fixed vide le buffer b
		if (!ret || !*ret) // si ret est vide, retourne NULL
		{
			free(ret);
			return (NULL);
		}
	}
	// if (!str_append_mem(&ret, b, tmp - b + 1))
	// {
	// 	free(ret);
	// 	return (NULL);
	// }
	return (ret);
}


#include <fcntl.h>
#include <stdio.h>

int main (void)
{
	int fd = open("test.txt", O_RDONLY);
	char *line;

	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}
