#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

size_t ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (s[i])
		i++;
	return i;
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{

	unsigned char *p;
	const unsigned char *q;
	size_t i;

	p = (unsigned char*)dest;
	q = (const unsigned char*)src;


	i = 0;
	while (i < n)
	{
		p[i] = q[i];
		i++;
	}
	return (dest);
}

char *ft_strdup(const char *s)
{
	size_t s_len;
	char *p;
	size_t i;

	s_len = ft_strlen(s);

	p = malloc(sizeof(*p) *(s_len + 1));
	if (!p)
		return NULL;

	ft_memcpy(p, s, s_len + 1);
	return p;
}

int main(void)
{
	char s[] = "42Tokyo";


	char *p = ft_strdup(s);
	printf("%s\n", p);

	free(p);
	return 0;
}