/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strreplace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:56:07 by bszabo            #+#    #+#             */
/*   Updated: 2024/03/24 14:09:25 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

// replace 'old' substring with 'new' substring in 'str'
// ft_strreplace("echo "$USER'", "$USER", "username") -> "echo username'"
// it will free the original string 'str' and return a new string, or NULL
char	*ft_strreplace(char *str, char *old, char *new)
{
	int		result_len;
	char	*ptr;
	char	*result;

	result_len = ft_strlen(str) - ft_strlen(old) + ft_strlen(new) + 1;
	ptr = ft_strnstr(str, old, ft_strlen(str));
	if (!ptr)
		return (NULL);
	result = (char *)malloc(result_len * sizeof(char));
	if (!result)
		return (NULL);
	ft_strlcpy(result, str, ptr - str + 1);
	ft_strlcat(result, new, result_len);
	ft_strlcat(result, ptr + ft_strlen(old), result_len);
	free(str);
	return (result);
}

/*
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
int main(void)
{
	char *str = strdup("echo \"$USER\'\"");
	char replace[] = "username";

	printf("Original string: %s\n", str);
	printf("Substring to replace: $USER\n");

	char *result = ft_strreplace(str, "$USER", replace);
	if (result == NULL) {
		printf("Failed to replace. Memory allocation error.\n");
		return 1;
	}

	printf("Modified string: %s\n", result);

	free(result); // Free the memory allocated by ft_strreplace

	return 0;
}
*/