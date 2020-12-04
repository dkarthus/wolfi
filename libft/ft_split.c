/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkarthus <dkarthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 13:11:58 by dkarthus          #+#    #+#             */
/*   Updated: 2020/12/02 20:03:43 by dkarthus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_cnt(char const *s, char c)
{
	size_t count;

	count = 0;
	while (*s)
	{
		while (*s == c)
		{
			s++;
			if (!(*s))
				return (count);
		}
		count++;
		while (*s != c)
		{
			if (!(*s))
				return (count);
			s++;
		}
	}
	return (count);
}

static size_t	ft_wlen(const char *w, char c)
{
	size_t len;

	len = 0;
	while (*w != c && *w)
	{
		w++;
		len++;
	}
	return (len);
}

static char		**ft_letitfree(char **src)
{
	while (*src)
		free(*src++);
	free(src);
	return (NULL);
}

char			**ft_split(const char *s, char c)
{
	char	**dst;
	size_t	count;
	size_t	i;
	size_t	wlen;

	i = 0;
	if (s == NULL)
		return (NULL);
	if (!(count = ft_cnt(s, c)))
		return ((char **)ft_calloc(1, sizeof(char *)));
	if (!(dst = (char **)ft_calloc((count + 1), sizeof(char *))))
		return (NULL);
	while (i < count && *s)
	{
		while (*s && *s == c)
			s++;
		wlen = ft_wlen(s, c);
		if (!(*(dst + i) = ft_substr(s, 0, wlen)))
			return (ft_letitfree(dst));
		i++;
		while (*s && (*s != c))
			s++;
	}
	return (dst);
}
