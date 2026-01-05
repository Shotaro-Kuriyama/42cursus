

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


char **split_ws(const char *p)
{
    size_t      word_count;
    char        **words;
    size_t      index;
    const char  *start;
    size_t      len;

    word_count = count_words_ws(p);

    words = (char **)malloc(sizeof(*words) * (word_count + 1));
    
    if (!words)
        return NULL;

    index = 0;
    while (*p)
    {
        while (*p && is_whitespace(*p))
            p++;

        if (!*p)
            break;

        start = p;
        while (*p && !is_whitespace(*p))
            p++;
        len = (size_t)(p - start);

        words[index] = dup_range(start, len);
        if (!words[index])
        {
            while (index > 0)
                free(words[--index]);
            free(words);
            return NULL;
        }
        index++;
    }
    words[index] = NULL; // 配列の終端（センチネル）
    return words;
}

void free_split(char **words)
{
    size_t index;

    if (!words)
        return;

    index = 0;
    while (words[index])
    {
        free(words[index]);
        index++;
    }
    free(words);
}