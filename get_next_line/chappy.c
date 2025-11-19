#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>

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

// 改行を含めた「1行」の長さを返す
// 例: "abc\ndef" → 4 ("abc\n")
//     "abc"      → 3
size_t	ft_newline_strlen(char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (++i); // 改行も含める
		i++;
	}
	return (i); // 改行がなければ全体長
}

// s の中に改行があるか？
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

// stash から「1行分」だけ取り出してmallocして返す
// （stash の中身はまだ触らない）
char	*gnl_get_line(char *stash)
{
	char	*line;
	size_t	i;
	size_t	len;

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

// stash から「行の残り部分」を新しく作り直す
// 例: stash = "aaa\nbbbccc"
//     → line部 = "aaa\n"
//     → この関数の返り値 = "bbbccc"
char	*gnl_get_rest(char *stash)
{
	char	*rest;
	size_t	line_len;
	size_t	stash_len;
	size_t	i;

	if (!stash)
		return (NULL);
	line_len = ft_newline_strlen(stash);
	stash_len = ft_strlen(stash);
	if (line_len >= stash_len)
	{
		// 残りがない
		free(stash);
		return (NULL);
	}
	rest = (char *)malloc(sizeof(*rest) * (stash_len - line_len + 1));
	if (!rest)
	{
		free(stash);
		return (NULL);
	}
	i = 0;
	while (stash[line_len + i])
	{
		rest[i] = stash[line_len + i];
		i++;
	}
	rest[i] = '\0';
	free(stash);
	return (rest);
}

// s1 と s2 をつなげた新しい文字列を返す。s1 は free する。
char	*gnl_strjoin(char *s1, char *s2)
{
	char	*res;
	size_t	len1;
	size_t	len2;
	size_t	i;
	size_t	j;

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

char	*get_next_line(int fd)
{
	static char	*stash; //staticは最初はNULL
	char		*buf;
	ssize_t		n;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);

	buf = (char *)malloc(sizeof(*buf) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);

	n = 1;
	// stash に改行が出るまで、または read が 0/マイナスになるまで読む
	while (!ft_has_newline(stash) && n > 0)
	{
		n = read(fd, buf, BUFFER_SIZE);
		if (n < 0)
		{
			free(buf);
			if (stash)
				free(stash);
			stash = NULL;
			return (NULL);
		}
		if (n == 0)
			break;
		buf[n] = '\0';
		stash = gnl_strjoin(stash, buf);
		if (!stash)
		{
			free(buf);
			return (NULL);
		}
	}
	free(buf);

	// 読むものもstashも何もなければ終了
	if (!stash || *stash == '\0')
	{
		if (stash)
			free(stash);
		stash = NULL;
		return (NULL);
	}

	// 1行分取り出す
	line = gnl_get_line(stash);
	// 残りを次回のための stash として保存
	stash = gnl_get_rest(stash);
	return (line);
}


int	main(void)
{
	int		fd;
	int		c;
	char	*p;

	fd = open("test.txt", O_RDONLY); //読み取り専用

	while((p = get_next_line(fd)) != NULL)
	{
		printf ("%s", p);
		free(p);
	}
	close(fd);

	
}
