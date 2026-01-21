# GDB Recursion Debugging Guide

## Essential Commands

### 1. View Call Stack
```gdb
(gdb) backtrace          # or: bt
(gdb) backtrace full     # Shows all local variables at each frame
(gdb) bt 5               # Show only first 5 frames
```

### 2. Navigate Between Stack Frames
```gdb
(gdb) frame 0            # Go to current frame (most recent call)
(gdb) frame 1            # Go to caller (one level up)
(gdb) frame 2            # Go two levels up
(gdb) up                 # Go up one frame
(gdb) down               # Go down one frame (deeper into recursion)
(gdb) select-frame 3     # Alternative way to select frame
```

### 3. See Variables at Each Level
```gdb
(gdb) info locals        # Show all local variables in current frame
(gdb) info args          # Show function arguments in current frame
(gdb) print nbr          # Print variable in current frame
(gdb) print c            # Print another variable
```

### 4. Auto-display Stack Info on Each Step
```gdb
# Show depth on each stop
(gdb) define hook-stop
>bt 3
>info locals
>end

# Or simpler - just show backtrace depth
(gdb) define hook-stop
>printf "Depth: %d frames\n", $_streq("bt", "bt") ? $__frame_level : 0
>bt 5
>end
```

## Practical Example with print_hex

### Setup
```gdb
(gdb) break print_hex
(gdb) run 255
(gdb) display nbr        # Show nbr at current frame
(gdb) display c          # Show c at current frame
```

### During Execution
```gdb
# After breaking, see the stack
(gdb) bt                 # See all recursive calls
(gdb) frame 0            # Current call (deepest)
(gdb) print nbr          # nbr value at this level
(gdb) continue

# Next break - see how stack grew
(gdb) bt                 # Now deeper!
(gdb) frame 0            # Deepest call
(gdb) info locals        # All locals here
(gdb) frame 1            # One level up
(gdb) info locals        # Locals at parent level
```

## Advanced Techniques

### Conditional Breakpoints
```gdb
# Break only at certain recursion depth
(gdb) break print_hex if $_caller_is("print_hex", 2)
# This breaks on second recursive call

# Break when nbr reaches certain value
(gdb) break print_hex if nbr == 0
```

### Track Recursion Depth
```gdb
# Set up automatic depth tracking
(gdb) define recurse_debug
>set $depth = 0
>bt
>set $i = 0
>while $i < 10
>  if $_any_caller_matches("print_hex")
>    set $depth = $depth + 1
>  end
>  set $i = $i + 1
>end
>printf "Recursion depth: %d\n", $depth
>end
```

### Compare Variables Across Frames
```gdb
(gdb) frame 0
(gdb) set $current_nbr = nbr
(gdb) frame 1
(gdb) set $parent_nbr = nbr
(gdb) printf "Current: %d, Parent: %d\n", $current_nbr, $parent_nbr
```

## Quick Workflow for print_hex

```gdb
# 1. Start debugging
gdb ./print_hex
break print_hex
run 255

# 2. Set up auto-display
display nbr
display c
define hook-stop
  bt 3
  printf "Current frame: "
  frame 0
  info locals
end

# 3. Step through
step    # Step into recursive call
continue # Continue to next break
```


