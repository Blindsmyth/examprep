/*

Assignment name  : ft_list_remove_if
Expected files   : ft_list_remove_if.c
Allowed functions: free
--------------------------------------------------------------------------------

Write a function called ft_list_remove_if that removes from the
passed list any element the data of which is "equal" to the reference data.

It will be declared as follows :

void ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)());

cmp takes two void* and returns 0 when both parameters are equal.

You have to use the ft_list.h file, which will contain:

$>cat ft_list.h
typedef struct      s_list
{
    struct s_list   *next;
    void            *data;
}                   t_list;
$>

*/
void ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)())
{
    t_list *curr;
    t_list *prev;
    t_list *next_node;

    if (!begin_list || !*begin_list)
        return;

    curr = *begin_list;
    prev = NULL;

    while (curr)
    {
        if (cmp(curr->data, data_ref) == 0)
        {
            next_node = curr->next;
            if (prev)
                prev->next = next_node;
            else
                *begin_list = next_node;
            free(curr);
            curr = next_node;
        }
        else
        {
            prev = curr;
            curr = curr->next;
        }
    }
}
/*
void ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)())
{
	t_list	*current;
	t_list	*to_delete;

	while ((cmp)((*begin_list)->next, data_ref))
	{
		to_delete = *begin_list;
		*begin_list = (*begin_list) ->next;
		free(to_delete);
	}

	current = *begin_list;
		if (cmp(current->next->data, data_ref) == 0)
		{
			to_delete = to_delete->next;
			current->next = to_delete->next;
			free(to_delete);
		}
			current = current->next;
}

void ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)())
{
    t_list **current;
    t_list *to_delete;
    
    current = begin_list;  // Start with pointer to the head pointer
    
    while (*current)
    {
        if (cmp((*current)->data, data_ref) == 0)
        {
            to_delete = *current;
            *current = (*current)->next;  // Update whatever current points to
            free(to_delete);
            // Don't advance current - check the new node at this position
        }
        else
        {
            current = &((*current)->next);  // Move to next pointer
        }
    }
}
*/

