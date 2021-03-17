/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchevet <jchevet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 10:13:41 by jchevet           #+#    #+#             */
/*   Updated: 2020/11/30 13:00:56 by jchevet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_issep(char s, char c)
{
	return (s == c);
}

int	ft_strcount(char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] && ft_issep(s[i], c))
		i++;
	if (s[i] == '\0')
		return (count);
	while (s[i])
	{
		if (ft_issep(s[i], c) && !ft_issep(s[i + 1], c) && s[i + 1] != '\0')
			count++;
		i++;
	}
	return (count + 1);
}

int	ft_wordlen(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && !ft_issep(s[i], c))
		i++;
	return (i);
}

void	ft_free_tab(char **t, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		free(t[j]);
		j++;
	}
	free(t);
}

int ft_calloc_check(char **tomalloc, int count, int size)
{
	*tomalloc = ft_calloc(count, size);
	if (!*tomalloc)
		return (-1);
	return (1);
}

char	**ft_split(const char *s, char c)
{
	char	**t;
	int		size;
	int		i;
	int		len;

	if (!s)
		return (NULL);
	size = ft_strcount((char *)s, c);
//	t = (char **)ft_calloc(size + 1, sizeof(char *));
//	if (!t)
//		return (NULL);
	t = NULL;
	if (!ft_calloc_check(t, size + 1, sizeof(char *)))
		return (NULL);
	i = -1;
	while (++i < size)
	{
		while (ft_issep(*s, c))
			s++;
		len = ft_wordlen((char *)s, c);
		if (!ft_calloc_check(&t[i], len + 1, sizeof(char)))
		{
			ft_free_tab(t, i);
			return (NULL);
		}
		ft_strlcpy(t[i], s, len + 1);
		s += len;
	}
	return (t);
}
