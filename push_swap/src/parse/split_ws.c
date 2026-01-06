/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_ws.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuriyam <skuriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 12:40:34 by skuriyam          #+#    #+#             */
/*   Updated: 2026/01/06 15:53:39 by skuriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "push_swap.h"


/* -------------------------
   split helpers
   ------------------------- */

static int is_whitespace(char ch)
{
    return (ch == ' ' || (ch >= 9 && ch <= 13));
}

static size_t count_words_ws(const char *p)
{
    size_t word_count;

    word_count = 0;
    while (*p)
    {
        if (*p && !is_whitespace(*p))
        {
            word_count++;
            while (*p && !is_whitespace(*p))
                p++;
        }
        else
            p++;
    }
    return word_count;
}

static char *dup_range(const char *start, size_t length)
{
    char    *copied;
    size_t  i;

    copied = (char *)malloc(sizeof(*copied) * (length + 1));
    if (!copied)
        return NULL;

    i = 0;
    while (i < length)
    {
        copied[i] = start[i];
        i++;
    }
    copied[i] = '\0';
    return copied;
}

static char **free_words(char **words, size_t index)
{
	while (index > 0)
		free(words[--index]);
	free(words);
	return NULL;
}


char **split_ws(const char *p)
{
    char        **words;
    size_t      index;
    const char  *start;
	if (!p)
		return NULL;
    words = (char **)malloc(sizeof(*words) * (count_words_ws(p) + 1));
    if (!words)
        return NULL;
    index = 0;
    while (*p)
    {
        while (*p && is_whitespace(*p))
            p++;
        if (!*p) // *p == '\0'
            break;
        start = p;
        while (*p && !is_whitespace(*p))
            p++;
        words[index] = dup_range(start, (size_t)(p - start));
        if (!words[index])
			return free_words(words, index);
        index++;
    }
    words[index] = NULL; // 配列の終端（センチネル）
    return words;
}
