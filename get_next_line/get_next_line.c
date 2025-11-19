
#include "get_next_line.h"

size_t	ft_strlen(char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

size_t	ft_newline_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (++i);
		i++;
	}
	return (i);
}

int	ft_has_newline(char *s)
{
	if (!s)
		return (0);
	while (*s)
	{
		if (*s == '\n')
			return (1);
		s++;
	}
	return (0);
}

char	*gnl_strjoin(char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;
	char	*res;
	size_t	i;
	size_t	j;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	res = (char *)malloc(sizeof(*res) * (len1 + len2 + 1));
	if (!res)
		return (free(s1), NULL);
	i = 0;
	while (i < len1)
	{
		res[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < len2)
		res[i++] = s2[j++];
	res[i] = '\0';
	if (s1)
		free(s1);
	return (res);
}

char	*gnl_get_line(char *stash)
{
	size_t	i;
	size_t	newline_len;
	char	*newline;

	if (!stash)
		return (NULL);
	newline_len = ft_newline_strlen(stash);
	newline = (char *)malloc(sizeof(*newline) * (newline_len + 1));
	if (!newline)
		return (NULL);
	i = 0;
	while (i < newline_len)
	{
		newline[i] = stash[i];
		i++;
	}
	newline[i] = '\0';
	return (newline);
}

char	*gnl_get_rest(char *stash)
{
	size_t	bufsize;
	size_t	newlen;
	char	*rest;
	size_t	i;

	if (!stash)
		return (NULL);
	bufsize = ft_strlen(stash);
	newlen = ft_newline_strlen(stash);
	if (newlen >= bufsize)
	{
		free(stash);
		return (NULL);
	}
	rest = (char *)malloc(sizeof(*rest) * ((bufsize - newlen) + 1));
	if (!rest)
		return (NULL);
	i = 0;
	while (i < (bufsize - newlen))
	{
		rest[i] = stash[newlen + i];
		i++;
	}
	rest[i] = '\0';
	free(stash);
	return (rest);
}

char	*get_next_line(int fd)
{
	ssize_t		n;
	char		*buf;
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = (char *)malloc(sizeof(*buf) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	n = 1;
	while (!ft_has_newline(stash) && n > 0)
	{
		n = read(fd, buf, BUFFER_SIZE); // readでbuf配列にコピー
		if (n < 0)
		{
			free(buf);
			if (stash)
				free(stash);
			stash = NULL;
			return (NULL);
		}
		if (n == 0)
			break ;
		buf[n] = '\0'; // bufを文字列として成立させるためにここですぐにヌル終端
		stash = gnl_strjoin(stash, buf);
		if (!stash)
		{
			free(buf);
			return (NULL);
		}
	}
	free(buf);
	if (!stash)
	{
		stash = NULL;
		return (NULL);
	}
	line = gnl_get_line(stash);
	stash = gnl_get_rest(stash);
	return (line);
}

// int	main(void)
//{
//	int fd;
//	char *p;

//	fd = open("test.txt", O_RDONLY); //読み取り専用

//	while ((p = get_next_line(fd)) != NULL)
//	{
//		printf("%s", p);
//		free(p);
//	}
//	close(fd);
//}