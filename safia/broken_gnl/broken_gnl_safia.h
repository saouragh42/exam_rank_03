#ifndef GNL
# define GNL

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

#include <stdlib.h> // malloc, free, size_t, NULL
#include <unistd.h> // read
char	*get_next_line(int fd);

#endif