/*
 * Commented study copy of fixed_broken_gnl.c
 * Same logic — comments only for learning.
 */

#include "broken_gnl.h"

/*
 * Find the first occurrence of character c in string s.
 * Returns a pointer to that character, or NULL if not found.
 */
char	*ft_strchr(char *s, int c)
{
	int	i = 0;						/* index into s */

	/* advance while not at '\0' and current char is not c */
	while (s[i] && s[i] != c)
		i++;
	if (s[i] == c)					/* found c (could be c == '\0') */
		return (s + i);				/* address of the match */
	else
		return (NULL);				/* hit '\0' without finding c */
}

/*
 * Copy n bytes from src to dest (regions must not overlap).
 * Cast to char* so we can copy byte by byte.
 */
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i = 0;					/* byte index */

	while (i < n)					/* copy exactly n bytes */
	{
		((char *)dest)[i] = ((char *)src)[i];
		i++;
	}
	return (dest);					/* standard memcpy return value */
}

/*
 * Return the length of null-terminated string s (not counting '\0').
 */
size_t	ft_strlen(char *s)
{
	size_t	ret = 0;				/* running length */

	while (*s)						/* until we hit '\0' */
	{
		s++;						/* move to next char */
		ret++;						/* count one more */
	}
	return (ret);
}

/*
 * Append size2 bytes from s2 onto the string pointed to by *s1.
 * *s1 may be NULL (treated as empty). On success *s1 is replaced
 * by a new malloc'd string; old *s1 is freed. Returns 1 ok / 0 fail.
 */
int	str_append_mem(char **s1, char *s2, size_t size2)
{
	/* if *s1 is NULL, length is 0; else measure it */
	size_t	size1 = *s1 ? ft_strlen(*s1) : 0;
	/* room for old + new + terminating '\0' */
	char	*tmp = malloc(size2 + size1 + 1);

	if (!tmp)						/* allocation failed */
		return (0);
	if (*s1)						/* copy old content if any */
		ft_memcpy(tmp, *s1, size1);
	ft_memcpy(tmp + size1, s2, size2);	/* append new bytes after old */
	tmp[size1 + size2] = 0;			/* null-terminate the result */
	free(*s1);						/* free old string (free(NULL) is ok) */
	*s1 = tmp;						/* caller now owns the new buffer */
	return (1);
}

/*
 * Append whole C-string s2 onto *s1 (wrapper around str_append_mem).
 */
int	str_append_str(char **s1, char *s2)
{
	return (str_append_mem(s1, s2, ft_strlen(s2)));
}

/*
 * Copy n bytes from src to dest; safe even if the regions overlap.
 * If dest is before src → copy forward (via memcpy).
 * If dest is after src  → copy backward so we don't overwrite unread bytes.
 */
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	if (dest < src)					/* no harmful overlap if we go forward */
		return (ft_memcpy(dest, src, n));
	else if (dest == src)			/* nothing to do */
		return (dest);
	/* dest > src: overlapping, must copy from the end backwards */
	size_t	i = n;

	while (i > 0)
	{
		i--;
		((char *)dest)[i] = ((char *)src)[i];
	}
	return (dest);
}

/*
 * Read one line from fd (including the '\n' if present).
 *
 * static buffer b keeps leftover bytes after a '\n' for the next call.
 * ret is the line being built (malloc'd, grown with str_append_*).
 * tmp points to '\n' in b when found; NULL while still searching.
 */
char	*get_next_line(int fd)
{
	/* persists between calls; +1 for the '\0' we store after each read */
	static char	b[BUFFER_SIZE + 1] = "";
	char	*ret = NULL;			/* line accumulator; starts empty */
	char	*tmp = ft_strchr(b, '\n');	/* leftover may already contain '\n' */

	/* keep reading until we find '\n' or hit EOF / error */
	while (!tmp)
	{
		/* add current buffer contents to the line so far */
		if (!str_append_str(&ret, b))
			return (NULL);			/* malloc failed */
		b[0] = '\0';				/* clear buffer before next read */
		int	read_ret = read(fd, b, BUFFER_SIZE);

		if (read_ret == -1)			/* read error */
			return (NULL);
		if (read_ret == 0)			/* EOF: no more data */
			break ;
		b[read_ret] = 0;			/* null-terminate what we just read */
		tmp = ft_strchr(b, '\n');	/* look for newline in this chunk */
	}
	if (tmp)						/* we found a '\n' in b */
	{
		/* append from start of b through the '\n' (tmp - b + 1 bytes) */
		if (!str_append_mem(&ret, b, tmp - b + 1))
		{
			free(ret);
			return (NULL);
		}
		/* shift bytes after '\n' to the start of b for the next call */
		ft_memmove(b, tmp + 1, ft_strlen(tmp + 1) + 1);
	}
	else							/* EOF with no newline in this round */
	{
		b[0] = '\0';				/* nothing left to keep */
		if (!ret || !*ret)			/* no line content at all → done */
		{
			free(ret);				/* free(NULL) is fine if ret is NULL */
			return (NULL);			/* GNL returns NULL at true EOF */
		}
		/* else: last line without '\n' — return what we accumulated */
	}
	return (ret);					/* caller must free this string */
}
