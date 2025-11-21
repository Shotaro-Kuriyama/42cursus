/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 12:41:59 by skuriyam          #+#    #+#             */
/*   Updated: 2025/11/21 15:46:35 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	cleanup(char **stash, t_gnl *g)
{
	if (g && g->buf)
	{
		free(g->buf);
		g->buf = NULL;
	}
	/*
	stash
	→ 「stash というポインタ引数そのものが NULL じゃないか？」をチェック
	→ つまり 「呼び出し元から、ちゃんと &stash_outside が渡されているか？」
	*stash
	→ 「stash が指している char * が NULL じゃないか？」
	→ つまり 「今、スタッシュ用のポインタが何かを指しているか？」（malloc 済みかどうか）
	*/
	if (stash && *stash)
	{
		free(*stash);
		*stash = NULL;
	}
	return (0);
}

/* fd から読んで *stash に貯める。失敗したら stash も含めて片付けて 0 を返す */
static int	read_and_stash(int fd, char **stash)
{
	t_gnl	g;

	g.buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!g.buf)
		return (cleanup(stash, &g));
	g.n = 1;
	while (!ft_has_newline(*stash) && g.n > 0)
	{
		g.n = read(fd, g.buf, BUFFER_SIZE);
		if (g.n < 0)
			return (cleanup(stash, &g));
		if (g.n == 0)
			break ;
		g.buf[g.n] = '\0';
		*stash = gnl_strjoin(*stash, g.buf);
		if (!*stash)
			return (cleanup(stash, &g));
	}
	free(g.buf);
	g.buf = NULL;
	/* もう何も残っていない（NULL or 空文字列）のなら stash も捨てる */
	if (!*stash || !**stash)
		return (cleanup(stash, NULL));
	return (1);
}

char	*get_next_line(int fd)
{
	static char	*stash = NULL;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	/* 読み込み & stash 更新。エラー時は stash も解放済みで NULL */
	if (!read_and_stash(fd, &stash))
		return (NULL);
	/* ここまで来た時点で stash は「中身ありの文字列」であることが保証されている想定 */
	line = gnl_get_line(stash);
	if (!line)
	{
		/* 行バッファが確保できなかったら stash ごと諦める */
		cleanup(&stash, NULL);
		return (NULL);
	}
	/* 1 行目を切り出した残りを新しい stash にする（内部で古い stash は free） */
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