# Linked List Functions - Detailed Explanations

## Table of Contents
1. [Understanding the List Structure](#understanding-the-list-structure)
2. [ft_list_foreach - Traversing a List](#ft_list_foreach---traversing-a-list)
3. [ft_list_remove_if - Removing Nodes](#ft_list_remove_if---removing-nodes)
4. [Pointer to Pointer Explained](#pointer-to-pointer-explained)
5. [Operator Precedence: (*ptr)->field](#operator-precedence-ptr-field)

---

## Understanding the List Structure

### The typedef and struct

```c
typedef struct    s_list
{
    struct s_list *next;
    void          *data;
}                 t_list;
```

This creates **two ways** to refer to the same structure:

- **`s_list`** = the **struct tag name** (the "original" name)
- **`t_list`** = the **typedef alias** (the "shortcut" name we actually use)

### Why both names exist

**Inside the struct definition:**
```c
struct s_list *next;  // We MUST use 'struct s_list' here
```
We have to use `struct s_list` because at this point, the typedef `t_list` doesn't exist yet—we're still defining it!

**Outside (in functions):**
```c
void ft_list_foreach(t_list *begin_list, void (*f)(void *))
//                   ^^^^^^ Using the typedef alias
```
We can use `t_list` because the typedef is complete.

### Practical comparison

**Without typedef** (how it would look):
```c
void ft_list_foreach(struct s_list *begin_list, void (*f)(void *))
                   //^^^^^^^^^^^^^^ Have to write 'struct' every time
```

**With typedef** (much cleaner):
```c
void ft_list_foreach(t_list *begin_list, void (*f)(void *))
                   //^^^^^^ Just the type name
```

### Naming convention

- `s_list` = "**s**truct list" (the struct tag)
- `t_list` = "**t**ype list" (the typedef'd type)

**Bottom line:** In your code, you'll use `t_list` everywhere.

---

## ft_list_foreach - Traversing a List

### The Task

Write a function that applies a function to each element of a linked list.

```c
void ft_list_foreach(t_list *begin_list, void (*f)(void *));
```

### Understanding Linked List Traversal

Imagine a list like this:
```
[Node1] -> [Node2] -> [Node3] -> NULL
```

We need to:
1. Start at `Node1` (which is `begin_list`)
2. Apply function `f` to Node1's data
3. Move to `Node2` (using `next`)
4. Apply function `f` to Node2's data
5. Move to `Node3` (using `next`)
6. Apply function `f` to Node3's data
7. See that `next` is `NULL`, so stop

### The Pattern

```c
// Start at the beginning
// While we haven't reached the end (NULL):
//     Apply function f to current node's data
//     Move to the next node
```

### Implementation

```c
#include "ft_list.h"

void ft_list_foreach(t_list *begin_list, void (*f)(void *))
{
    while (begin_list)
    {
        (*f)(begin_list->data);
        begin_list = begin_list->next;
    }
}
```

### Key Points

1. **`while (begin_list)`** - Loop while not NULL (idiomatic C style)
   - Equivalent to `while (begin_list != NULL)`
   - NULL evaluates to false, non-NULL evaluates to true

2. **`(*f)(begin_list->data)`** - Apply the function to the data
   - `f` is a function pointer
   - We dereference it with `(*f)` and call it

3. **`begin_list = begin_list->next`** - Move to next node
   - This is safe! `begin_list` is a **local copy** of the pointer
   - Modifying it doesn't affect the caller's original pointer

4. **No need for a separate `current` variable**
   - We can reuse `begin_list` directly
   - It's a pass-by-value copy anyway

---

## ft_list_remove_if - Removing Nodes

### The Task

Remove from the list any element whose data is "equal" to the reference data.

```c
void ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)());
```

**Important:** `cmp` returns `0` when both parameters are **equal**.

### Why Pointer to Pointer?

Notice the difference:
```c
// ft_list_foreach:
void ft_list_foreach(t_list *begin_list, ...)
//                          ^ single pointer - can traverse, can't modify head

// ft_list_remove_if:
void ft_list_remove_if(t_list **begin_list, ...)
//                            ^^ pointer to pointer - can modify the head!
```

To remove nodes, especially the **first node**, we need to modify where the caller's pointer points. This requires a pointer to that pointer.

### The Challenges

#### Challenge 1: Removing the first node(s)

What if the list starts with nodes we need to remove?
```
[DELETE] -> [DELETE] -> [KEEP] -> [KEEP] -> NULL
```
We need to update `*begin_list` to point to the first KEEP node.

#### Challenge 2: Linking around removed nodes

When we remove a node in the middle:
```
[A] -> [DELETE] -> [B]  becomes  [A] -> [B]
```
We need to connect A to B before freeing DELETE.

### The Strategy: Two Parts

**Part 1:** Remove all matching nodes from the **beginning** of the list

**Part 2:** Remove matching nodes from the **rest** of the list

### Why Different Approaches?

**The Key Insight:** To remove a node, you need to **update the pointer that points TO it**.

#### Part 1 - Removing from the beginning

```c
while (*begin_list && cmp((*begin_list)->data, data_ref) == 0)
{
    to_delete = *begin_list;
    *begin_list = (*begin_list)->next;  // Update the HEAD pointer
    free(to_delete);
}
```

**What pointer needs updating?** → `*begin_list` (the head of the list)

We have **direct access** to `*begin_list`, so we can modify it directly.

**Visual:**
```
*begin_list → [DELETE] → [B] → [C]

We update: *begin_list to point to [B]
```

#### Part 2 - Removing from the middle/end

```c
current = *begin_list;
while (current && current->next)
{
    if (cmp(current->next->data, data_ref) == 0)
    {
        to_delete = current->next;
        current->next = to_delete->next;  // Update CURRENT's next pointer
        free(to_delete);
        // Don't advance current - check the new next node
    }
    else
    {
        current = current->next;  // Only move if we didn't delete
    }
}
```

**What pointer needs updating?** → `current->next` (the previous node's next pointer)

We need `current` to **stay one step behind** so we can update `current->next`.

**Visual:**
```
*begin_list → [A] → [DELETE] → [C]
              ↑
           current

We update: current->next to point to [C]
```

### Complete Implementation

```c
#include "ft_list.h"
#include <stdlib.h>

void ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)())
{
    t_list *current;
    t_list *to_delete;
    
    if (!begin_list || !*begin_list)
        return;
    
    // Part 1: Remove matching nodes from the beginning
    while (*begin_list && cmp((*begin_list)->data, data_ref) == 0)
    {
        to_delete = *begin_list;
        *begin_list = (*begin_list)->next;
        free(to_delete);
    }
    
    // Part 2: Remove matching nodes from the rest
    current = *begin_list;
    while (current && current->next)
    {
        if (cmp(current->next->data, data_ref) == 0)
        {
            to_delete = current->next;
            current->next = to_delete->next;
            free(to_delete);
            // Don't advance - check the new next node
        }
        else
        {
            current = current->next;
        }
    }
}
```

### Example Trace

List: `[3] -> [5] -> [3] -> [7] -> NULL`, removing all `3`s

**Part 1:**
- `*begin_list` points to `[3]`, matches! Remove it
- `*begin_list` now points to `[5]`, doesn't match
- Move to Part 2

**Part 2:**
- `current = [5]`, check `current->next = [3]`
  - Matches! Link: `[5]->next = [7]`, free `[3]`
  - Don't move current, check again
- `current = [5]`, check `current->next = [7]`
  - Doesn't match, move forward
- `current = [7]`, `current->next = NULL`
  - Exit loop

**Result:** `[5] -> [7] -> NULL` ✓

### Common Mistakes to Avoid

❌ **Wrong comparison:**
```c
if (cmp(data_ref, curr->data))  // Returns 0 when equal!
```
✓ **Correct:**
```c
if (cmp(data_ref, curr->data) == 0)  // Explicitly check for 0
```

❌ **Not unlinking nodes:**
```c
free(curr);  // List still points to freed memory!
```

❌ **Not updating `*begin_list` when removing first node**

❌ **Moving forward after deletion (skips nodes!)**

---

## Pointer to Pointer Explained

### Single Pointer vs. Pointer to Pointer

```c
// Single pointer
t_list *ptr;          // Points to a t_list node
ptr->data             // Access the data
ptr->next             // Access the next pointer

// Pointer to pointer
t_list **ptr;         // Points to a pointer that points to a t_list node
*ptr                  // Dereference once → gives t_list*
(*ptr)->data          // Access the data (need parentheses!)
(*ptr)->next          // Access the next pointer
```

### Why Pointer to Pointer?

When you pass a pointer to a function, you pass a **copy** of the pointer:

```c
void function(t_list *ptr)
{
    ptr = something_else;  // Only changes the LOCAL copy
    // Caller's original pointer is unchanged
}
```

To modify the **caller's pointer**, you need a pointer to it:

```c
void function(t_list **ptr)
{
    *ptr = something_else;  // Modifies the caller's pointer!
}
```

### Visual Example

```c
t_list *my_list = /* some list */;

// Pass by value (single pointer)
void cannot_change_head(t_list *list)
{
    list = NULL;  // Only changes local copy
}
cannot_change_head(my_list);
// my_list is unchanged

// Pass by reference (pointer to pointer)
void can_change_head(t_list **list)
{
    *list = NULL;  // Changes caller's pointer!
}
can_change_head(&my_list);
// my_list is now NULL
```

### When to Use

- **`t_list *`** - When you only need to **traverse** or **read** the list
- **`t_list **`** - When you need to **modify what the head points to** (like removing the first node)

---

## Operator Precedence: (*ptr)->field

### The Problem

The `->` operator has **higher precedence** than `*` (dereference).

### Without Parentheses ❌

```c
t_list **begin_list;

*begin_list->next
```

This is parsed as: `*(begin_list->next)`

What happens:
1. Try to access `begin_list->next` first
2. But `begin_list` is a `t_list **`, which doesn't have a `next` field!
3. **Compiler error!**

### With Parentheses ✓

```c
(*begin_list)->next
```

This is parsed correctly as: `(*begin_list)->next`

What happens:
1. `*begin_list` → dereference to get a `t_list *`
2. `->next` → access the `next` field of that `t_list`
3. **Works correctly!**

### Complete Breakdown

```c
t_list **begin_list;

// Level 1: The pointer to pointer
begin_list           // Type: t_list**

// Level 2: Dereference once
*begin_list          // Type: t_list* (points to a node)

// Level 3: Access fields (NEED PARENTHESES!)
(*begin_list)->data  // Type: void* (the data field)
(*begin_list)->next  // Type: t_list* (the next field)
```

### Rule of Thumb

Whenever you have a **pointer to pointer** (`**`) and want to access a field:

```c
(*ptr)->field    // Correct ✓
*ptr->field      // Wrong ❌ (won't compile)
```

The parentheses force the dereference to happen first!

### Examples

```c
// Correct usage
if (*begin_list)                           // Check if not NULL
    data = (*begin_list)->data;            // Access data
    next = (*begin_list)->next;            // Access next
    *begin_list = (*begin_list)->next;     // Update the pointer

// Common mistakes
if (*begin_list->next)                     // ❌ Won't compile
    data = *begin_list->data;              // ❌ Won't compile
```

---

## Include Guards

Header files should have include guards to prevent multiple inclusion:

```c
#ifndef FT_LIST_H
# define FT_LIST_H

typedef struct    s_list
{
    struct s_list *next;
    void          *data;
}                 t_list;

#endif
```

### What Include Guards Do

- `#ifndef FT_LIST_H` - "if FT_LIST_H is not defined"
- `# define FT_LIST_H` - "define it now"
- ... (your code)
- `#endif` - "end of the conditional"

If the file is included again, `FT_LIST_H` is already defined, so the content gets skipped. This prevents compilation errors from duplicate definitions.

---

## Quick Reference

### Boolean Context in C

```c
// Pointers in conditions
if (ptr)           ≡  if (ptr != NULL)
if (!ptr)          ≡  if (ptr == NULL)
while (ptr)        ≡  while (ptr != NULL)
```

### Include Syntax

```c
#include "my_file.h"    // Your own headers (local files)
#include <stdlib.h>     // System/standard library headers
```

### Function Pointers

```c
void (*f)(void *)       // Pointer to function taking void*, returning void
(*f)(data)              // Call the function
int (*cmp)()            // Pointer to function returning int
```

---

**Happy coding!** 🚀


