#include "header.h"

int     count_words(char *str, char sep)
{
    int count;

    count = 0;
    while (*str)
    {
        if (*str != sep && *str)
            if (*(str + 1) == sep || !(*(str + 1)))
                count++;
        str++;
    }
    return (count);
}

char    *new_word(char *str, char sep)
{
    int     i;
    char    *result;

    while (*str == sep)
        str++;
    i = 0;
    while (str[i] && str[i] != sep)
        i++;
    result = ft_substr(str, i);
    return (result);
}

char    **ft_split(char *str, char sep)
{
    char    **result;
    int     count;
    int     i;

    count = count_words(str, sep);
    if (!(result = malloc(sizeof(char *) * (count + 1))))
        return (NULL);
    i = 0;
    while (i < count)
    {
        result[i] = new_word(str, sep);
        while (*str && *str == sep)
            str++;
        while (*str && *str != sep)
            str++;
        i++;
    }
    result[i] = NULL;
    return (result);
}