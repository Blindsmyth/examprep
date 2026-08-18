/*
 * STUDY COPY of broken_gnl.c
 * Code below is still BROKEN. FIX comments show what to change.
 * See also: CHANGES.md, fixed_broken_gnl.c
 */

#include "get_next_line.h"

char *ft_strchr(char *s, int c)
{
  int i = 0;
  /* FIX: while (s[i] && s[i] != c)
   *      stop at '\0' or you walk past the string forever if c is missing */
  while(s[i] != c)
    i++;
  if (s[i] == c)
    return s + i;
  else
    return NULL;
}

void *ft_memcpy(void *dest, const void *src, size_t n)
{
  /* FIX: copy forward with index i:
   *      size_t i = 0;
   *      while (i < n) {
   *        ((char *)dest)[i] = ((char *)src)[i];
   *        i++;
   *      }
   *      --n > 0 skips the last byte and uses wrong indices */
  while(--n > 0)
    ((char *)dest)[n - 1] = ((char *)src)[n - 1];
  return dest;
}

size_t ft_strlen(char *s)
{
  /* OK: no fix needed (but *s1 == NULL is handled in str_append_mem) */
  size_t res = 0;
  while (*s)
  {
    s++;
    res++;
  }
  return res;
}

int str_append_mem(char **s1, char *s2, size_t size2)
{
  /* FIX: size_t size1 = 0;
   *      if (*s1)
   *        size1 = ft_strlen(*s1);
   *      ret starts as NULL in get_next_line → ft_strlen(NULL) crashes */
  size_t size1 = ft_strlen(*s1);
  char *tmp = malloc(size2 + size1 + 1);
  if (!tmp)
    return 0;
  /* FIX: if (*s1) ft_memcpy(tmp, *s1, size1);
   *      do not memcpy from NULL */
  ft_memcpy(tmp, *s1, size1);
  ft_memcpy(tmp + size1, s2, size2);
  tmp[size1 + size2] = '\0';
  free(*s1);
  *s1 = tmp;
  return 1; 
}

int str_append_str(char **s1, char *s2)
{
  /* OK: no fix needed */
  return str_append_mem(s1, s2, ft_strlen(s2));
}

void *ft_memmove(void *dest, const void *src, size_t n)
{
  /* FIX: if (dest < src) return ft_memcpy(dest, src, n);
   *      dest > src must NOT call ft_memmove again → infinite recursion */
  if (dest > src)
    return ft_memmove(dest, src, n);
  else if (dest == src)
    return dest;
  /* FIX: copy exactly n bytes backwards:
   *      size_t i = n;
   *      while (i > 0) {
   *        i--;
   *        ((char *)dest)[i] = ((char *)src)[i];
   *      }
   *      Do not use ft_strlen(src) (wrong length) or size_t i >= 0 (never ends) */
  size_t i = ft_strlen((char *)src) - 1;
  while (i >= 0)
  {
    ((char *)dest)[i] = ((char *)src)[i];
    i--;
  }
  return dest;
}

char *get_next_line(int fd)
{
  static char b[BUFFER_SIZE + 1] = "";
  char *ret = NULL;
  char *tmp = ft_strchr(b, '\n');
  while(!tmp)
  {
    if (!str_append_str(&ret, b))
      return (NULL);
    /* FIX: b[0] = '\0'; before read — clear leftover before filling b again */
    int read_ret = read(fd, b, BUFFER_SIZE);
    if (read_ret == -1)
      return (NULL);
    /* FIX: if (read_ret == 0) break; — EOF: stop looping */
    b[read_ret] = 0;
    /* FIX: tmp = ft_strchr(b, '\n');
     *      without this, tmp stays NULL forever → infinite loop */
  }
  /* FIX: only take the "through newline" path when tmp is set:
   *
   *   if (tmp)
   *   {
   *     if (!str_append_mem(&ret, b, tmp - b + 1))
   *     {
   *       free(ret);
   *       return NULL;
   *     }
   *     // keep bytes after '\n' for the next call
   *     ft_memmove(b, tmp + 1, ft_strlen(tmp + 1) + 1);
   *   }
   *   else
   *   {
   *     b[0] = '\0';
   *     if (!ret || !*ret)   // empty EOF → NULL
   *     {
   *       free(ret);
   *       return NULL;
   *     }
   *     // else: last line with no '\n' — return ret as-is
   *   }
   *
   * BROKEN below assumes tmp always points at '\n' after the loop
   * (false on EOF / last line without newline). */
  if (!str_append_mem(&ret, b, tmp - b + 1))
  {
    free(ret);
    return NULL;
  }
  return ret;
}
