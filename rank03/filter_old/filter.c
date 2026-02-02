#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 42
#endif

/*
 * ft_filter: Removes all occurrences of 'pattern' from 'str' and outputs the result
 * 
 * This function performs a find-and-replace operation where the pattern is replaced
 * with nothing (effectively removing it). It processes the string character by
 * character, skipping over any occurrences of the pattern.
 * 
 * @param str: The input string to filter
 * @param pattern: The pattern to remove from the string
 */
void ft_filter(char *str, char *pattern)
{
    char *result;
    size_t pattern_len;
    size_t str_len;
    size_t i, j;  // i: index in original string, j: index in result string

    // Validate input parameters
    if (!str || !pattern)
        return;

    pattern_len = strlen(pattern);
    // If pattern is empty, nothing to filter
    if (pattern_len == 0)
        return;

    str_len = strlen(str);
    // Allocate buffer for filtered result (worst case: same size as input)
    result = (char *)malloc(str_len + 1);
    if (!result)
        return;

    // Process string character by character
    i = 0;  // Position in original string
    j = 0;  // Position in result string
    while (i < str_len)
    {
        // Check if pattern matches at current position
        if (strncmp(str + i, pattern, pattern_len) == 0)
        {
            // Pattern found: skip over it (don't copy to result)
            i += pattern_len;
        }
        else
        {
            // No match: copy character to result
            result[j] = str[i];
            j++;
            i++;
        }
    }
    result[j] = '\0';  // Null-terminate the result string

    // Write filtered result to stdout (file descriptor 1)
    write(1, result, j);
    free(result);
}

/*
 * main: Reads input from stdin, accumulates it in a buffer, then filters it
 * 
 * Program flow:
 * 1. Check command-line arguments (must have exactly 1 argument: the filter pattern)
 * 2. Read input from stdin in chunks of BUFFER_SIZE bytes
 * 3. Accumulate all input into a dynamically allocated buffer
 * 4. Call ft_filter to remove all occurrences of the pattern
 * 5. Clean up and exit
 */
int main(int argc, char **argv)
{
    char temp[BUFFER_SIZE];      // Temporary buffer for reading chunks
    char *buffer;                 // Temporary pointer for realloc result
    char *res = NULL;             // Accumulated input buffer
    int total_read = 0;           // Total bytes read so far
    ssize_t bytes_current;       // Bytes read in current iteration

    // Validate: program must be called with exactly one argument (the pattern)
    if(argc != 2)
        return 1;

    // Read input from stdin (file descriptor 0) in chunks
    // Continue reading until EOF (read returns 0) or error (read returns -1)
    while((bytes_current = read(0, temp, BUFFER_SIZE)) > 0)
    {
        // Reallocate buffer to accommodate new data
        // +1 for null terminator
        buffer = realloc(res, (total_read + bytes_current + 1));
        if(!buffer)
        {
            perror("realloc");
            free(res);  // Free old buffer on realloc failure
            return 1;
        }
        res = buffer;  // Update pointer to new buffer location
        
        // Copy newly read data to the end of accumulated buffer
        memmove((res + total_read), temp, bytes_current);
        total_read = total_read + bytes_current;
        res[total_read] = '\0';  // Null-terminate (for string functions)
    }

    // Check if read() encountered an error (returns -1)
    if(bytes_current < 0)
    {
        free(res);
        perror("read");
        return 1;
    }
    
    // Check if no input was read at all
    if(!res)
    {
        return 1;
    }
    
    // Filter the accumulated input: remove all occurrences of argv[1]
    ft_filter(res, argv[1]);
    
    // Clean up allocated memory
    free(res);
    return 0;
}