/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptorrao- <ptorrao-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 15:58:10 by ptorrao-          #+#    #+#             */
/*   Updated: 2025/03/10 14:14:30 by ptorrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_words(char const *s, char c, char x)
{
	int	i;
	int	c_words;

	i = 0;
	c_words = 0;
	while (*s)
	{
		if (*s != c && *s != x && i == 0)
		{
			i = 1;
			c_words++;
		}
		else if (*s == c || *s == x)
			i = 0;
		s++;
	}
	return (c_words);
}

char	*fill_word(const char *str, int start, int end)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((end - start + 1) * sizeof(char));
	if (!word)
		return (NULL);
	while (start < end)
	{
		word[i] = str[start];
		i++;
		start++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_free(char **str, int j)
{
	while (j--)
	{
		free(str[j]);
		str[j] = NULL;
	}
	free(str);
	str = NULL;
	return (NULL);
}

char	**ft_makesplit(char const *s, char c, char x, char **lst_str)
{
	size_t	i;
	int		j;
	int		s_word;

	i = -1;
	j = 0;
	s_word = -1;
	while (++i <= ft_strlen(s))
	{
		if (s[i] != c && s[i] != x && s_word < 0)
			s_word = i;
		else if ((s[i] == c || s[i] == x || i == ft_strlen(s)) && s_word >= 0)
		{
			lst_str[j] = fill_word(s, s_word, i);
			if (!(lst_str[j]))
				return (ft_free(lst_str, j));
			s_word = -1;
			j++;
		}
	}
	lst_str[j] = NULL;
	return (lst_str);
}

char	**ft_cub_split(char const *s, char c, char x)
{
	char	**lst_str;

	if (!s)
		return (NULL);
	lst_str = malloc((ft_words(s, c, x) + 1) * sizeof(char *));
	if (!lst_str)
		return (NULL);
	lst_str = ft_makesplit(s, c, x, lst_str);
	return (lst_str);
}
