/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strreplace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:56:07 by bszabo            #+#    #+#             */
/*   Updated: 2024/03/14 18:12:06 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	get_len(char *str, int start)
{
	int	len;

	len = 0;
	while (str[start + len] && str[start + len] != ' ')
		len++;
	return (len);
}

// replace the word which starts at index 'start' with 'replace' in the 'str'
// free the memory of 'str' and return a pointer to the new string, or NULL
// example: ft_strreplace("hello world", 6, "there") -> "hello there"
char	*ft_strreplace(char *str, int start, char *replace)
{
	char	*new;
	int		i;
	int		j;
	int		len;

	new = (char *)malloc(ft_strlen(str) + ft_strlen(replace) + 1);
	if (!new)
		return (NULL);
	i = -1;
	while (str[++i] && (i < start))
		new[i] = str[i];
	len = get_len(str, start);
	j = 0;
	while (replace[j])
		new[i++] = replace[j++];
	j = start + len;
	while (str[j])
		new[i++] = str[j++];
	new[i] = '\0';
	free(str);
	return (new);
}
/*
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
int main(void)
{
	char *str = strdup("echo $USER");
	int start = 5;
	char replace[] = "username";

	printf("Original string: %s\n", str);
	printf("Replacing \"%s\" starting from index %d\n", replace, start);

	char *result = ft_strreplace(str, start, replace);
	if (result == NULL) {
		printf("Failed to replace. Memory allocation error.\n");
		return 1;
	}

	printf("Modified string: %s\n", result);

	free(result); // Free the memory allocated by ft_strreplace

	return 0;
}
*/