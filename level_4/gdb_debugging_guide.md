# GDB Debugging Guide for Exam

## Compilation with Debug Information
```bash
gcc -g your_program.c -o your_program
```

## Starting GDB
```bash
gdb ./your_program
```

## Setting Command Line Arguments
```bash
(gdb) set args 42        # Set arguments
(gdb) run 42            # Alternative: run with arguments directly
```

## Essential GDB Commands

### Setting Breakpoints
```bash
(gdb) break main                    # Break at main function
(gdb) break filename.c:line_number  # Break at specific line
(gdb) break function_name           # Break at function
```

### Running the Program
```bash
(gdb) run              # Start the program
(gdb) continue         # Continue until next breakpoint
(gdb) finish           # Run until current function returns
```

### Stepping Through Code
```bash
(gdb) next             # Execute next line (step over functions)
(gdb) step             # Execute next line (step into functions)
```

### Inspecting Variables
```bash
(gdb) print variable_name          # Print variable value
(gdb) print *pointer              # Print value pointed to by pointer
(gdb) info locals                 # Show all local variables
(gdb) info args                   # Show function arguments
(gdb) info variables              # Show all variables (global and static)
```

### Automatic Variable Display
```bash
(gdb) display variable_name       # Automatically print variable every step
(gdb) undisplay 1                 # Remove display (1 is the display number)
```

### Examining Memory and Code
```bash
(gdb) list                        # Show source code around current line
(gdb) list 50                     # Show 10 lines around line 50
(gdb) list main                   # Show main function
(gdb) x/10x $rsp                  # Examine 10 words in hex from stack
(gdb) x/10c string_var            # Examine 10 characters from string
```

### Call Stack and Functions
```bash
(gdb) backtrace                   # Show call stack (or just 'bt')
(gdb) info stack                  # More detailed stack information
```

### Watching Variables Change
```bash
(gdb) watch variable_name         # Break when variable changes
(gdb) rwatch variable_name        # Break when variable is read
(gdb) awatch variable_name        # Break when variable is read or written
```

## Complete Program Runthrough Methods

### Method 1: Step-by-step with automatic printing (RECOMMENDED FOR EXAMS)
```bash
(gdb) set args 42
(gdb) break main
(gdb) run
(gdb) display num                 # Auto-print num every step
(gdb) display i                   # Auto-print i every step
(gdb) display argc                # Auto-print argc every step
(gdb) next                        # Execute line by line
(gdb) next                        # Keep pressing next to see each step
```

### Method 2: Use step to see function calls
```bash
(gdb) step                        # Step INTO functions like atoi()
(gdb) finish                      # Run until current function returns
(gdb) next                        # Continue with main function
```

### Method 3: Set breakpoints at key points
```bash
(gdb) break 47                    # Break at specific line
(gdb) break 50                    # Break at while loop
(gdb) break 52                    # Break at if condition
(gdb) run
(gdb) continue                    # Will stop at each breakpoint
```

### Method 4: Watch variables change
```bash
(gdb) watch num                   # Break whenever num changes
(gdb) watch i                     # Break whenever i changes
(gdb) run
(gdb) continue                    # Will stop each time variables change
```

## Useful Commands for Exams

### Print Everything at Once
```bash
(gdb) info locals                 # Print all local variables
(gdb) info args                   # Print function arguments
(gdb) backtrace                   # Print call stack
(gdb) list                        # Print current code
```

### Debugging Common Issues
```bash
(gdb) print *pointer              # Check if pointer is NULL
(gdb) x/20c string                # Examine string contents
(gdb) info registers              # Show CPU registers
(gdb) where                       # Show current location in stack
```

### Exit GDB
```bash
(gdb) quit                        # Exit GDB
```

## Advanced Debugging: Logic Statements and Expressions

### Evaluate Logic Statements
```bash
(gdb) print (num % i == 0)        # Shows true/false result
(gdb) print (argc == 2)           # Shows true/false result
(gdb) print (num != i)            # Shows true/false result
(gdb) print (i <= num)            # Shows true/false result
```

### See Variable Values in Context
```bash
(gdb) print num                   # Shows current value of num
(gdb) print i                     # Shows current value of i
(gdb) print num / i               # Shows result of division
(gdb) print num % i               # Shows remainder
(gdb) print num, i, (num % i == 0) # Print multiple values at once
```

### Conditional Breakpoints (Break when condition is true)
```bash
(gdb) break 52 if (num % i == 0)  # Only break when condition is true
(gdb) break 50 if (i > 5)         # Break when i becomes greater than 5
(gdb) break 54 if (num == 1)      # Break when num equals 1
```

### Display Logic Results Automatically
```bash
(gdb) display (num % i == 0)      # Shows if condition is true/false every step
(gdb) display (num / i)           # Shows division result every step
(gdb) display (i <= num)          # Shows loop condition every step
```

### Print Formatted Output
```bash
(gdb) print "num=%d, i=%d, condition=%d", num, i, (num % i == 0)
(gdb) printf "Current values: num=%d, i=%d\n", num, i
```

## Pro Tips for Exams

1. **Always compile with `-g` flag first**
2. **Use `display` to automatically show key variables AND logic results**
3. **Set breakpoints before running**
4. **Use `list` frequently to see your code**
5. **Print pointer values to check if they're NULL**
6. **Use `backtrace` if you get segmentation faults**
7. **Use `info locals` to see all variables in current scope**
8. **Use `step` to debug function calls, `next` to skip over them**
9. **Use `print (condition)` to see if logic statements are true/false**
10. **Use conditional breakpoints to stop only when conditions are met**

## Example Debugging Session for prime.c

```bash
# Compile
gcc -g prime.c -o prime

# Start debugging
gdb ./prime

# Set up debugging session
(gdb) set args 42
(gdb) break main
(gdb) run

# Set up automatic display
(gdb) display num
(gdb) display i
(gdb) display argc

# Step through the program
(gdb) next                        # i = 2
(gdb) next                        # if (argc == 2)
(gdb) next                        # num = atoi(argv[1])
(gdb) next                        # if (num == 1)
(gdb) next                        # while (i <= num)
(gdb) next                        # if (num % i == 0)
(gdb) next                        # printf("%d", i)
(gdb) next                        # if (num != i)
(gdb) next                        # printf("*")
(gdb) next                        # num = num / i
(gdb) next                        # else i++

# Continue stepping to see the complete prime factorization
```

This guide will help you debug any C program during your exam!
