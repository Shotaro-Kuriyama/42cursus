
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

size_t ft_newline_strlen(char *s)
{
	size_t i;

	i = 0;
	while(s[i])
	{
		if (s[i] == '\n')
			return (++i);
		i++;
	}
	return (i);
}

int ft_has_newline(char *s)
{
	while(*s)
	{
		if (*s == '\n')
			return (1);
		s++;
	}
	return (0);
}

char *newline_malloc(char *stash)
{
	char *line;
	size_t i;
	size_t newline_len;
	newline_len = ft_newline_strlen(stash);

	line = (char *)malloc(sizeof(*line) * (newline_len + 1));
	if (!line)
		return (NULL);
	i = 0;

	while(i < newline_len)
	{
		line[i] = stash[i];
		i++;
	}

	line[i] = '\0';

	return (line);
}

char *gnl_strjoin(char *s1, char *s2)
{
	size_t len1;
	size_t len2;
	char *res;
	size_t i;
	size_t j;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);

	res = (char *)malloc(sizeof(*res) * (len1 + len2 + 1));
	if (!res)
	{
		free(s1);
		return (NULL);
	}

	i = 0;
	while (i < len1)
		res[i++] = s1[i++];
	j = 0;
	while (j < len2)
		res[i++] = s2[j++];
	res[i] = '\0';
	if (s1)
		free(s1);
	return (res);
}

char *gnl_get_line(char *stash)
{
	size_t i;
	size_t newline_len;
	char *newline;

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

char *get_next_line(int fd)
{
	ssize_t n;
	char *buf;
	static char *stash;
	size_t i;
	char *line;

	buf = (char *)malloc(sizeof(*buf) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);

	n = 1;

	while (!ft_has_newline(stash) && n > 0)
	{
		n = read(fd, buf, BUFFER_SIZE); //readでbuf配列にコピー
		if (n < 0)
		{
			free(buf);
			if (stash)
				free(stash);
			stash = NULL;
			return (NULL);
		}
		buf[n] = '\0'; //bufを文字列として成立させるためにここですぐにヌル終端

		stash = gnl_strjoin(stash, buf);
		if (!stash)
		{
			free(buf);
			return (NULL);
		}

		line = gnl_get_line(stash);

		stash = gnl_get_rest(stash);
	}
	if (n <= 0) //エラーまたはEOFより、bufはfreeしてリターンでいい。
	{
		free(buf);
		return (NULL);
	}
	buf[n] = '\0';

	i = 0;
	if (ft_has_newline(buf))
	{
		line = newline_malloc(buf);
		free(buf);
		return (line);
	}

	return (buf);

}


int main(void)
{
	int fd;

	fd = open("test.txt", O_RDONLY); //失敗時は-1が返る
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
}