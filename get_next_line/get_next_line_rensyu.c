

// open ファイルを開く
// read　ファイルの中身を読み込む　→ get_next_line
// close　ファイルを閉じる
// write　ファイルに書き込む	→ft_printf

// readline = get_next_line みたいなもん

// read(fd, buffer, size) buffer = 読み込んだデータを保存する領域のポインタ。size = ファイルから読み込むバイト数

// gnlはBUFFER_SIZEで指定された文字を読み込み
// 1.改行まで読み込めた場合→その文字列をmallocして返す
// 2.改行まで読み込めなかった場合→その文字列を保持した状態で何も返さない
// static変数　スタック領域ではなく静的領域に変数の情報が保存される

// \nまで読み込む　→　\n を探せばいいい！

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#define BUFFER_SIZE 5
#include <stdlib.h>



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

// int getchar(void)
//{
//	static char buf[BUFSIZ];
//	static char *bufp;
//	static int n = 0;

//	if (n == 0)
//	{
//		n = read(0, buf, sizeof buf);
//		bufp = buf;
//	}

//	if (--n >= 0)
//	{
//		return ((unsigned char)*bufp);
//	}
//	return (EOF);
//}

// int ft_getc(FILE *stream)
//{

//}
