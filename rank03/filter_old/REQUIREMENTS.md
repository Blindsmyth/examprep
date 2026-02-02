# Filter - Exam Rank 03 Requirements (Reconstructed)

Based on the solution code analysis, here are the likely requirements for the `filter` exam topic:

## Program Name
`filter`

## Description
A program that reads input from stdin, performs a filtering/find-and-replace operation based on a command-line argument, and outputs the result.

## Requirements

### 1. Command-Line Arguments
- The program must take **exactly one argument** (the filter pattern/replacement string)
- If the number of arguments is incorrect, the program should return with exit code 1

### 2. Input Reading
- Read input from **stdin** (file descriptor 0)
- Read in chunks of `BUFFER_SIZE` bytes (default: 42, but should be configurable via `-DBUFFER_SIZE` during compilation)
- Accumulate all input into a single dynamically allocated buffer
- Handle read errors appropriately

### 3. Core Functionality
- Implement a function `ft_filter` that performs find-and-replace operations
- The function signature appears to be: `void ft_filter(char *str, char *pattern)`
- The function should modify the string in-place or output the filtered result

### 4. Memory Management
- Use dynamic memory allocation (`malloc`/`realloc`) to store the input
- Properly free all allocated memory before program exit
- Handle allocation failures with appropriate error handling

### 5. Error Handling
- Return exit code 1 on errors (wrong arguments, read errors, allocation failures)
- Return exit code 0 on success
- Use `perror` for system error messages

### 6. Allowed Functions
Based on the includes used:
- `read()` - for reading from stdin
- `malloc()` / `realloc()` / `free()` - for memory management
- `memmove()` - for copying data
- `perror()` - for error messages
- Standard string functions from `<string.h>`

### 7. Implementation Details
- The program should handle input of any size by dynamically reallocating the buffer
- The buffer should be null-terminated after reading
- The `ft_filter` function should process the entire input string

## Notes
- The solution shows `ft_filter` is called with the accumulated input string and the command-line argument
- The comment suggests it's a "find and replace" function, but the exact filtering logic would need to be determined from the exam specification
- The program likely outputs the filtered result to stdout (though not shown in the main function)

## Example Usage
```bash
echo "Hello World" | ./filter "pattern"
cat file.txt | ./filter "replacement"
```

## Code Issues in Solution
The provided solution has some issues that should be fixed:
1. Missing `#include <stdlib.h>` for `malloc`, `realloc`, `free`
2. `char *temp[BUFFER_SIZE]` should be `char temp[BUFFER_SIZE]` (array, not pointer array)
3. `ft_filter` function signature is incomplete and the function is not implemented
4. `total_read` should be initialized to 0
5. The program doesn't output the filtered result (likely missing `write()` or `printf()` after `ft_filter`)

