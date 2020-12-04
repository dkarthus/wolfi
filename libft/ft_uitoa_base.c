/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkarthus <dkarthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 17:17:20 by dkarthus          #+#    #+#             */
/*   Updated: 2020/12/02 20:03:43 by dkarthus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_num_lng(uintmax_t i, int base)
{
	int len;

	len = 0;
	while (i)
	{
		i = i / (uintmax_t)base;
		len++;
	}
	return ((len == 0) ? 1 : len);
}

char		*ft_uitoa_base(uintmax_t num, int base)
{
	const char			*ref = "0123456789abcdef";
	char				*dst;
	int					len;

	len = ft_num_lng(num, base);
	if (!(dst = ft_calloc((len + 1), 1)))
		return (NULL);
	if (num == 0)
		return (ft_strdup("0"));
	len--;
	while (len >= 0)
	{
		dst[len] = ref[num % (uintmax_t)base];
		num = num / (uintmax_t)base;
		len--;
	}
	return (dst);
}
