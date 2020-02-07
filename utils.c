#include "header.h"

int		ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *str1, char *str2)
{
	char	*result;
	int		len1;
	int		len2;
	int		i;
	int		j;

	len1 = str1 ? ft_strlen(str1) : 0;
	len2 = str2 ? ft_strlen(str2) : 0;
	if (!(result = malloc(sizeof(char) * (len1 + len2 + 1))))
		return (NULL);
	i = 0;
	while (i < len1)
	{
		result[i] = str1[i];
		i++;
	}
	j = 0;
	while (j < len2)
	{
		result[i + j] = str2[j];
		j++;
	}
	result[i + j] = '\0';
	return (result);
}

char	*ft_substr(char *str, int len)
{
	char	*result;
	int		length;
	int		i;

	length = (len > ft_strlen(str)) ? ft_strlen(str) : len;
	if (!(result = malloc(sizeof(char) * (length + 1))))
		return (NULL);
	i = 0;
	while (i < length)
	{
		result[i] = str[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

int		ft_strncmp(char *str1, char *str2, char max)
{
	int i;

	i = 0;
	while (str1[i] && i < max)
	{
		if (str1[i] != str2[i])
			return (1);
		i++;
	}
	return (0);
}
