
#include "get_next_line.h"

char	*gnl_get_line(char *stash)
{
	size_t	i;
	size_t	len;
	char	*line;

	if (!stash || !*stash)
		return (NULL);
	len = ft_newline_strlen(stash);
	line = (char *)malloc(sizeof(*line) * (len + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (i < len)
	{
		line[i] = stash[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*gnl_get_rest(char *stash)
{
	size_t	total;
	size_t	len;
	char	*rest;
	size_t	i;

	if (!stash)
		return (NULL);
	total = ft_strlen(stash);
	len = ft_newline_strlen(stash);
	if (len >= total)
		return (free(stash), NULL);
	rest = (char *)malloc(sizeof(*rest) * ((total - len) + 1));
	if (!rest)
		return (NULL);
	i = 0;
	while (i < (total - len))
	{
		rest[i] = stash[len + i];
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