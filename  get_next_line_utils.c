/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*    get_next_line_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumsimse@student.42istanbul.com.tr         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/23 19:13:42 by rumsimse          #+#    #+#             */
/*   Updated: 2026/11/23 19:13:59 by rumsimse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* s'nin uzunluğunu döndürür. NULL gelirse 0 döndürür (ilk çağrıda stash NULL). */
size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

/* s içinde c'yi arar. Bulursa adresini, bulamazsa NULL döndürür. */
char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}

/*
** stash ile buf'u yeni bir string'de birleştirir.
** Eski stash, kopyalama bittikten sonra free edilir;
** böylece adresi kaybolmaz ve bellek sızıntısı olmaz.
*/
char	*ft_strjoin_free(char *stash, char *buf)
{
	char	*res;
	size_t	i;
	size_t	j;

	res = malloc(ft_strlen(stash) + ft_strlen(buf) + 1);
	if (!res)
		return (ft_free(stash, NULL));
	i = 0;
	while (stash && stash[i])
	{
		res[i] = stash[i];
		i++;
	}
	j = 0;
	while (buf[j])
	{
		res[i + j] = buf[j];
		j++;
	}
	res[i + j] = '\0';
	free(stash);
	return (res);
}

/* İki işaretçiyi free eder ve NULL döndürür. Hata durumlarını kısaltır. */
char	*ft_free(char *a, char *b)
{
	free(a);
	free(b);
	return (NULL);
}