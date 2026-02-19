# Broken get_next_line — Fixes summary

Summary of what was fixed and what still needs fixing to make the code work.

---

## 1. ft_strchr (fixed)

- **Original bugs:** (1) No check for end of string → could run past buffer. (2) `return s++` returned start of string, not pointer to `c`.
- **Fix:** Loop while `s[i]` (stop at `'\0'`). When `s[i] == c`, return `s + i`. Otherwise return `NULL`.

---

## 2. ft_memcpy (fixed)

- **Original bug:** `while (--n > 0)` with `[n - 1]` — the last byte (index `n - 1`) was never copied; only indices 0..n-2 were written.
- **Fix:** Copy all indices 0 through `n - 1`. Use `while (n-- > 0) ((char *)dest)[n] = ((char *)src)[n];` — the post-decrement means the body runs with the decremented `n`, so the last iteration copies index 0. (Forward loop `for (size_t i = 0; i < n; i++) ...` is equivalent.)
- **Test in GDB:** Use `x/10cb dest` and `x/10cb src` before/after; buffers of size 11 so `dest` stays null-terminated if you copy 10 bytes.

---

## 3. ft_strlen (fixed)

- **Bug:** When `s` is NULL, `ft_strlen(*s1)` in `str_append` would be undefined. If you added `if (!s) return NULL`, that’s wrong: the function returns `size_t`, not a pointer.
- **Fix:** Guard at the start: `if (!s) return (0);` so NULL is treated as length 0. Then `str_append` can safely use `size1 = ft_strlen(*s1)` when `*s1` is NULL (first call from get_next_line).

---

## 4. str_append (fixed)

- **Bug:** Allocates `tmp` and sets the null terminator, but never copies the contents of `*s1` or `s2` into `tmp`.
- **Fix:** Use `ft_memcpy` for both parts, **before** `free(*s1)` and `*s1 = tmp`:
  - `ft_memcpy(tmp, *s1, size1);` — copy the current string (use `*s1`, not `s1`).
  - `ft_memcpy(tmp + size1, s2, size2);` — copy the new part right after the first.
  - `tmp[size1 + size2] = '\0';` (or `= 0`).
  - Then `free(*s1);` and `*s1 = tmp`.
- **Do not free `s2`** — the caller owns it (e.g. static buffer `b`). Only free the old `*s1` block.
- **When `*s1` is NULL:** With `ft_strlen` returning 0 for NULL, `size1 == 0` and `ft_memcpy(tmp, *s1, 0)` runs with length 0 so nothing is dereferenced.

---

## 5. Helpers that still need fixes

### ft_memmove

- **Bug:** `size_t i` is unsigned. `while (i >= 0)` is always true when `i` wraps (after `i--` when `i` is 0 → huge value). Infinite loop.
- **Fix:** Use a signed type for the backward loop, or use a different loop (e.g. count down with a signed counter, or copy forward with a different overlap check). Also: for the “backward” case it uses `ft_strlen(src)` instead of `n` — should use `n` bytes, not strlen.

---

## 6. get_next_line (main function)

- **Missing return:** When the `while (!tmp)` loop exits (newline found or EOF), the function falls through to the closing `}` and returns nothing → “non-void function does not return a value” warning. Must return a value on all paths.
- **When `tmp` is found:** Need to (1) build the line (from start of buffer up to and including `'\n'`), (2) copy the rest of the buffer (after `'\n'`) back into `b` for the next call, (3) return the line (malloc’d, freeable).
- **When EOF (no newline):** If there is accumulated data, return it as the last “line”; then next call should return NULL and free any remaining stash. If buffer is empty at EOF, return NULL.
- **Order of operations in loop:** Currently it appends `b` to `ret`, then reads. So the first time, `b` might still be empty (static init). Typical approach: read into `b` first, then append `b` to stash; or maintain a stash and each iteration read into `b`, append to stash, then check for newline in stash.

---

## 7. Testing helpers (exam strategy)

- **test_helpers.c:** Declarations for each helper (with `;`). Simple `main()` that calls helpers with known inputs and prints or checks results.
- **Compile:** `cc -D BUFFER_SIZE=42 get_next_line.c test_helpers.c -o test_helpers`
- **Run:** `./test_helpers`
- Fix helpers one by one, recompile and run until tests pass, then fix `get_next_line`.

---

## 8. Declarations for test_helpers.c

```c
#include <stdlib.h>

char   *ft_strchr(char *s, int c);
void   *ft_memcpy(void *dest, const void *src, size_t n);
size_t ft_strlen(char *s);
int    str_append(char **s1, char *s2, size_t size2);
int    str_append_str(char **s1, char *s2);
void   *ft_memmove(void *dest, const void *src, size_t n);
```

(End each declaration with `;`.)
