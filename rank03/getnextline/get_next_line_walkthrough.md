# get_next_line Detailed Walkthrough

## Key Concepts

1. **Static variable `stash`**: Persists between function calls, holds leftover data
2. **Buffer reading**: Reads `BUFFER_SIZE` bytes at a time from file
3. **Line extraction**: Extracts one line (up to and including `\n`) from stash
4. **Leftover management**: Saves what's after `\n` for next call

---

## Example File

Let's use this file content (assume BUFFER_SIZE = 5):
```
Hello\nWorld\nTest
```

Visual representation:
```
H e l l o \n W o r l d \n T e s t
```

---

## Call 1: get_next_line(fd) - Getting "Hello\n"

### Initial State:
```
stash = NULL
File position: start
```

### Step 1: Check if stash has newline
```c
while (!stash || !ft_strchr(stash, '\n'))
```
- `stash` is `NULL`, so condition is true → enter loop

### Step 2: Read from file (read_and_append)
```c
read(fd, buffer, 5)  // BUFFER_SIZE = 5
```
**What happens:**
- Allocates `buffer[6]` (BUFFER_SIZE + 1)
- Reads 5 bytes: `"Hello"`
- `bytes_read = 5`
- `buffer = "Hello\0"` (null-terminated)

**After read_and_append:**
```
stash = NULL (initially)
stash = ft_strdup("Hello")  // Since stash was NULL
stash = "Hello\0"
```

**Current state:**
```
stash: "Hello\0"
File position: after 'o'
```

### Step 3: Check for newline again
```c
while (!stash || !ft_strchr(stash, '\n'))
```
- `stash` exists but has no `\n` → condition true → continue loop

### Step 4: Read again
```c
read(fd, buffer, 5)
```
**What happens:**
- Reads next 5 bytes: `"\nWorl"`
- `bytes_read = 5`
- `buffer = "\nWorl\0"`

**After read_and_append:**
```
stash = "Hello\0"  (old)
buffer = "\nWorl\0"  (new)
stash = ft_strjoin("Hello", "\nWorl")
stash = "Hello\nWorl\0"
```

**Current state:**
```
stash: "Hello\nWorl\0"
File position: after 'l' in "Worl"
```

### Step 5: Check for newline
```c
while (!stash || !ft_strchr(stash, '\n'))
```
- `ft_strchr(stash, '\n')` finds `\n` at position 5 → condition false → exit loop

### Step 6: Extract line
```c
newline = ft_strchr(stash, '\n')  // Points to position 5 in stash
line = extract_line(stash, newline)
```
**extract_line does:**
- `line_len = newline - stash + 1 = 5 - 0 + 1 = 6`
- Allocates `line[7]`
- Copies 6 characters: `"Hello\n"`
- `line = "Hello\n\0"`

**Current state:**
```
line: "Hello\n\0"
stash: "Hello\nWorl\0"  (still has leftover)
```

### Step 7: Update stash (save leftover)
```c
stash = update_leftover(stash, newline)
```
**update_leftover does:**
- `newline` points to `\n` in stash
- `newline + 1` points to `"Worl"`
- `leftover = ft_strdup("Worl")`
- Free old stash
- `stash = "Worl\0"`

**Final state after Call 1:**
```
Return: "Hello\n\0"
stash: "Worl\0"  (saved for next call)
File position: after 'l' in "Worl"
```

---

## Call 2: get_next_line(fd) - Getting "World\n"

### Initial State:
```
stash = "Worl\0"  (from previous call)
File position: after 'l' in "Worl"
```

### Step 1: Check if stash has newline
```c
while (!stash || !ft_strchr(stash, '\n'))
```
- `stash` exists but has no `\n` → condition true → enter loop

### Step 2: Read from file
```c
read(fd, buffer, 5)
```
**What happens:**
- Reads next 5 bytes: `"d\nTes"`
- `bytes_read = 5`
- `buffer = "d\nTes\0"`

**After read_and_append:**
```
stash = "Worl\0"  (old)
buffer = "d\nTes\0"  (new)
stash = ft_strjoin("Worl", "d\nTes")
stash = "World\nTes\0"
```

**Current state:**
```
stash: "World\nTes\0"
File position: after 's' in "Tes"
```

### Step 3: Check for newline
```c
while (!stash || !ft_strchr(stash, '\n'))
```
- `ft_strchr(stash, '\n')` finds `\n` at position 5 → condition false → exit loop

### Step 4: Extract line
```c
newline = ft_strchr(stash, '\n')  // Points to position 5
line = extract_line(stash, newline)
```
**extract_line does:**
- `line_len = 5 - 0 + 1 = 6`
- Allocates `line[7]`
- Copies: `"World\n"`
- `line = "World\n\0"`

### Step 5: Update stash
```c
stash = update_leftover(stash, newline)
```
- `leftover = ft_strdup("Tes")`
- `stash = "Tes\0"`

**Final state after Call 2:**
```
Return: "World\n\0"
stash: "Tes\0"  (saved for next call)
File position: after 's' in "Tes"
```

---

## Call 3: get_next_line(fd) - Getting "Test" (EOF case)

### Initial State:
```
stash = "Tes\0"
File position: after 's' in "Tes"
```

### Step 1: Check if stash has newline
```c
while (!stash || !ft_strchr(stash, '\n'))
```
- `stash` exists but has no `\n` → condition true → enter loop

### Step 2: Read from file
```c
read(fd, buffer, 5)
```
**What happens:**
- No more data → `bytes_read = 0` (EOF)
- `buffer` is freed, stash returned as-is

**After read_and_append:**
```
stash = "Tes\0"  (unchanged, no new data)
bytes_read = 0
```

### Step 3: Check condition and break
```c
if (bytes_read == 0)
    break;
```
- Loop exits because we hit EOF

### Step 4: Extract line (no newline case)
```c
newline = ft_strchr(stash, '\n')  // Returns NULL (no \n found)
line = extract_line(stash, newline)
```
**extract_line does:**
- `newline` is `NULL`
- `line_len = ft_strlen(stash) = 3`
- Allocates `line[4]`
- Copies: `"Tes"`
- `line = "Tes\0"`

### Step 5: Update stash (EOF case)
```c
stash = update_leftover(stash, newline)
```
**update_leftover does:**
- `newline` is `NULL`
- Frees stash
- Returns `NULL`
- `stash = NULL`

**Final state after Call 3:**
```
Return: "Tes\0"
stash: NULL  (cleaned up, no leftover)
File position: EOF
```

---

## Call 4: get_next_line(fd) - EOF, return NULL

### Initial State:
```
stash = NULL
File position: EOF
```

### Step 1: Check if stash has newline
```c
while (!stash || !ft_strchr(stash, '\n'))
```
- `stash` is `NULL` → condition true → enter loop

### Step 2: Read from file
```c
read(fd, buffer, 5)
```
- `bytes_read = 0` (EOF)
- Returns stash (which is `NULL`)

### Step 3: Check condition
```c
if (!stash)
    return (NULL);
```
- `stash` is `NULL` → return `NULL`

**Final state:**
```
Return: NULL
stash: NULL
```

---

## Visual Summary

### File Content:
```
H e l l o \n W o r l d \n T e s t
```

### Call 1 Timeline:
```
Read 1: "Hello"     → stash: "Hello"
Read 2: "\nWorl"    → stash: "Hello\nWorl"
Extract: "Hello\n"  → line: "Hello\n"
Leftover: "Worl"    → stash: "Worl"
```

### Call 2 Timeline:
```
Read 1: "d\nTes"    → stash: "World\nTes"
Extract: "World\n"  → line: "World\n"
Leftover: "Tes"     → stash: "Tes"
```

### Call 3 Timeline:
```
Read 1: EOF         → stash: "Tes" (unchanged)
Extract: "Tes"      → line: "Tes"
Leftover: NULL      → stash: NULL
```

### Call 4 Timeline:
```
Read 1: EOF         → stash: NULL
Return: NULL
```

---

## Key Points

1. **Static stash persists**: Data saved between calls
2. **Reads in chunks**: BUFFER_SIZE bytes at a time
3. **Accumulates data**: Joins new reads with existing stash
4. **Extracts one line**: Up to and including `\n`
5. **Saves leftover**: Everything after `\n` stays in stash
6. **EOF handling**: Returns final data, then NULL
7. **Memory management**: Frees old stash when updating

---

## Edge Cases

### Empty file:
- First read returns 0 bytes
- stash stays NULL
- Returns NULL immediately

### File with only newlines:
- `"\n\n\n"` → Returns `"\n"` three times

### Very long line (longer than BUFFER_SIZE):
- Keeps reading and joining until `\n` found
- stash grows: "chunk1" → "chunk1chunk2" → "chunk1chunk2chunk3\n"

### Line exactly BUFFER_SIZE:
- May need multiple reads if `\n` is in next buffer
