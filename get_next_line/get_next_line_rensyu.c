

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




size_t find_newline_index(const char *buf)
{
	size_t i;

	i = 0;
	while (buf[i])
	{
		if (buf[i] == '\n')
			return i;
		i++;
	}
	return (0);
}

char *extract_line_from_buf(char *buf, ssize_t n)
{
	size_t idx;
	size_t len;
	char *line;
	size_t i;
	
	idx = find_newline_index(buf);
	if (idx == 0)
		len = (size_t)n; //改行がない場合：全部を１行とみなす。
	else
		len = idx + 1;
		
	line = malloc(len + 1);
	if (!line)
		return (NULL);

	i = 0;
	while (i < len)
	{
		line[i] = buf[i];
		i++;
	}
	line[i] = '\0';

	return (line);
}

char	*get_next_line(int fd)
{
	ssize_t	n;
	char	*buf;
	char *line;
	static char *stash;

	buf = (char *)malloc(sizeof(*buf) * (BUFFER_SIZE));
	if (!buf)
		return (NULL);
	n = read(fd, buf, BUFFER_SIZE); //そのmallocした配列の先頭を筆頭にファイルの文字を格納している。
	if (n <= 0)
	{
		// エラーまたはEOF
		free(buf);
		return (NULL);
	}

	buf[n] = '\0';

	line = extract_line_from_buf(buf, n);
	return (line);
}

#include <stdio.h>

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
