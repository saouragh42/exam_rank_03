#include <stdio.h>    // printf, perror
#include <unistd.h>   // read
#include <stdlib.h>   // malloc, free

int ft_strlen(char *s)
{
    int i;

    if (!s)
        return (0);
    i = 0;
    while (s[i])
        i++;
    return (i);
}

int ft_strncmp(const char *s1, const char *s2, size_t n)
{
    size_t i;

    i = 0;
    if (!s1 || !s2)
        return (0);
    if (n == 0)
        return (0);
    while (s1[i] && s2[i] && i < (n - 1) && s1[i] == s2[i])
        i++;
    return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int main(int argc, char *argv[])
{
    if (argc != 2 || argv[1][0] == '\0')
        return (1);

    char *buffer;
    char c;
    int i = 0;
    int j = 0;
    int k;
    int len;
    int be_read;

    buffer = malloc(1000000);
    if (!buffer)
    {
        perror("Error");
        return (1);
    }

    while ((be_read = read(0, &c, 1)) > 0)
        buffer[i++] = c;

    if (be_read < 0)
    {
        perror("Error");
        free(buffer);
        return (1);
    }

    buffer[i] = '\0';
    len = ft_strlen(argv[1]);

    while (buffer[j])
    {
        if (ft_strncmp(&buffer[j], argv[1], (size_t)len) == 0)
        {
            k = 0;
            while (k < len)
            {
                printf("*");
                k++;
            }
            j += len;
        }
        else
        {
            printf("%c", buffer[j]);
            j++;
        }
    }

    free(buffer);
    return (0);
}
