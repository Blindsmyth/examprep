# Broken GNL Fixes Guide

This guide maps your `broken_get_next_line.c` issues to a clean helper-first fix.
Use it as exam revision material.

## 1) `ft_strchr`

### What was broken
- No NULL check.
- Loop condition could run forever.
- Returned `s++` instead of pointer to the found index.

### Correct behavior
- Return pointer to first match.
- Return pointer to `'\0'` if `c == '\0'`.
- Return `NULL` if not found.

## 2) `ft_memcpy`

### What was broken
- Reverse loop with `--n` was off-by-one and unsafe for `n == 0`.

### Correct behavior
- Copy forward from index `0` to `n - 1`.

## 3) `ft_strlen`

### What was broken
- No NULL safety.

### Correct behavior
- Return `0` when input is `NULL` (helps append helpers work safely).

## 4) `str_append` / `str_append_str`

### What was broken
- Missing semicolon.
- Allocated but never copied old/new content.
- Freed old string before preserving content.

### Correct behavior
- Compute old length + new length.
- Allocate combined buffer.
- Copy old string first, then new chunk.
- Free old string after copying.
- Assign the new pointer back to `*s1`.

## 5) `ft_memmove`

### What was broken
- Misspelled name (`ft_memmmove`).
- Used `ft_strlen(src)` for copy size (wrong for binary/partial copy).
- Reverse loop with `size_t i >= 0` can underflow forever.

### Correct behavior
- Use exact `n` bytes requested.
- Copy forward if `dest < src`, backward otherwise.

## 6) `get_next_line` structure

### What was broken
- Syntax errors (`ft_strchr(b; '\n')`, missing semicolons).
- Never built final line and never returned correctly.
- Read loop order was fragile.

### Stable exam flow
1. Keep static `buffer[BUFFER_SIZE + 1]`.
2. Start with `newline = ft_strchr(buffer, '\n')`.
3. While no newline in `buffer`:
   - append current `buffer` to `stash`
   - read next chunk into `buffer`
   - on read error: free, clear static buffer, return `NULL`
   - if EOF: break
4. Append current `buffer` one final time.
5. If stash empty: return `NULL`.
6. If no newline in stash:
   - return whole stash (last line at EOF), clear static buffer.
7. If newline exists:
   - allocate exact line size including `'\n'`
   - copy line out
   - move leftover into static buffer
   - return line

## 7) New reference implementation

See:
- `get_next_line/get_next_line_reuse_helpers.c`

This version stays close to your helper style and is intentionally exam-friendly.
