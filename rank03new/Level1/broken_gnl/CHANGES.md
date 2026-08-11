# broken_gnl → fixed_broken_gnl

Summary of what was wrong in `broken_gnl.c` and how `fixed_broken_gnl.c` fixes it.

## `ft_strchr`

| Broken | Fixed |
|--------|--------|
| `while (s[i] != c)` — no end check | `while (s[i] && s[i] != c)` |
| Walks past `\0` if `c` is missing → UB | Stops at end of string |

## `ft_memcpy`

| Broken | Fixed |
|--------|--------|
| `while (--n > 0)` | `while (i < n)` with index `i` |
| Skips the last byte (`n == 0` never copied) | Copies all `n` bytes |
| Off-by-one indexing (`n - 1` after `--n`) | Straightforward forward copy |

## `str_append_mem`

| Broken | Fixed |
|--------|--------|
| `ft_strlen(*s1)` when `*s1` is `NULL` | `*s1 ? ft_strlen(*s1) : 0` |
| Always `ft_memcpy(tmp, *s1, …)` on NULL | Only memcpy from `*s1` if it is non-NULL |

Needed because `ret` starts as `NULL` in `get_next_line`.

## `ft_memmove`

| Broken | Fixed |
|--------|--------|
| `if (dest > src) return ft_memmove(dest, src, n)` | No recursive self-call |
| Infinite recursion on overlap | Backward copy with `i = n` when `dest > src` |
| Uses `ft_strlen(src)` and `i >= 0` on `size_t` | Copies exactly `n` bytes |
| Wrong branch / wrong length | `dest < src` → forward via `ft_memcpy` |

## `get_next_line`

| Broken | Fixed |
|--------|--------|
| Never updates `tmp` inside the read loop | `tmp = ft_strchr(b, '\n')` after each read |
| Infinite loop when no `\n` in a chunk | Loop exits once `\n` is found (or EOF) |
| No EOF handling (`read_ret == 0`) | `break` on EOF |
| Does not clear `b` before `read` | `b[0] = '\0'` before reading (and on EOF path) |
| Never shifts leftover after `\n` | `ft_memmove(b, tmp + 1, …)` keeps remainder for next call |
| Assumes a `\n` always exists | Separate path when `tmp` is NULL (last line / empty) |
| Empty EOF can leak / return empty string | `free(ret)` and return `NULL` if nothing was read |

## Unchanged

- `ft_strlen` — already correct
- `str_append_str` — already correct (thin wrapper)
