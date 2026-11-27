/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumsimse@student.42istanbul.com.tr         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/23 19:12:26 by rumsimse          #+#    #+#             */
/*   Updated: 2026/11/23 19:13:17 by rumsimse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
** 1. OKU: stash'te '\n' bulunana ya da read 0 döndürene (dosya bitti)
** kadar BUFFER_SIZE'lık parçalar okuyup stash'in sonuna ekler.
** Hata olursa (read -1) her şeyi free edip NULL döndürür.
** bytes_read = 1: döngüye en az bir kez girmek için.
*/
static char	*ft_read_to_stash(int fd, char *stash)
{
	char	*buf;
	ssize_t	bytes_read;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (ft_free(stash, NULL));
	bytes_read = 1;
	while (!ft_strchr(stash, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read == -1)
			return (ft_free(buf, stash));
		buf[bytes_read] = '\0';
		stash = ft_strjoin_free(stash, buf);
		if (!stash)
			return (ft_free(buf, NULL));
	}
	free(buf);
	return (stash);
}

/*
** 2. SATIRI AL: stash'in başından '\n' dahil olan kısmı kopyalar.
** Son satırda '\n' yoksa '\0'a kadar kopyalar.
** stash boşsa ("") döndürülecek satır yok: NULL.
** malloc(i + 1): i karakter + '\0'.
*/
static char	*ft_get_line(char *stash)
{
	char	*line;
	size_t	i;
	size_t	j;

	if (!stash[0])
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	j = 0;
	while (j < i)
	{
		line[j] = stash[j];
		j++;
	}
	line[j] = '\0';
	return (line);
}

/*
** 3. GÜNCELLE: '\n'den sonraki kısmı yeni bir string'e kopyalar,
** eski stash'i free eder. new_stash[j] = stash[i + j]
** '\n' yoksa (son satırdı) geriye bir şey kalmaz: NULL.
*/
static char	*ft_update_stash(char *stash)
{
	char	*new_stash;
	size_t	i;
	size_t	j;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
		return (ft_free(stash, NULL));
	i++;
	new_stash = malloc(ft_strlen(stash) - i + 1);
	if (!new_stash)
		return (ft_free(stash, NULL));
	j = 0;
	while (stash[i + j])
	{
		new_stash[j] = stash[i + j];
		j++;
	}
	new_stash[j] = '\0';
	free(stash);
	return (new_stash);
}

/*
** stash static: fonksiyon bitince silinmez, bir sonraki çağrıda
** '\n'den sonra artan kısım hâlâ orada durur.
** Sıra: oku -> satırı al -> güncelle. Dışarıya line döner,
** stash içeride kalır.
*/
char	*get_next_line(int fd)
{
	static char *stash;
	char *line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = ft_read_to_stash(fd, stash);
	if (!stash)
		return (NULL);
	line = ft_get_line(stash);
	if (!line)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	stash = ft_update_stash(stash);
	return (line);
}