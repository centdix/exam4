#include "header.h"

t_lst	*new_cmd(int type, char **args)
{
	t_lst	*new;

	if (!(new = malloc(sizeof(t_lst))))
		return (NULL);
	new->type = type;
	new->args = args;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

void	add_cmd(t_lst **lst_cmd, int type, char **args)
{
	t_lst	*begin;
	t_lst	*to_add;

	begin = *lst_cmd;
	to_add = new_cmd(type, args);
	if (begin)
	{
		while (begin->next)
			begin = begin->next;
		to_add->prev = begin;
		begin->next = to_add;
	}
	else
		*lst_cmd = to_add;
}
