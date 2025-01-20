#include "../cub3d.h"

static int	check_single_door_position(map_list_t *tmp, int i)
{
	if (tmp->map[i] == '3')
	{
		if (tmp->prev->map[i] == ' ' || tmp->prev->map[i] == '\t'
			|| !tmp->prev->map[i] || tmp->prev->length <= i
			|| tmp->next->length <= i)
		{
			print_error("Door is out");
			return (1);
		}
		if (tmp->map[i + 1] == ' ' || tmp->map[i - 1] == ' ' || tmp->map[i \
			+ 1] == '\t' || tmp->map[i - 1] == '\t')
		{
			print_error("free space Door close");
			return (1);
		}
		if (tmp->map[i + 1] == '1' && tmp->map[i - 1] == '1')
			return (0);
		if (tmp->prev && tmp->next && tmp->prev->map[i] == '1'
			&& tmp->next->map[i] == '1')
			return (0);
		print_error("Door should be between two walls");
	}
	return (0);
}

int	door_check(map_list_t *hd)
{
	map_list_t	*tmp;
	int			i;

	if (hd == NULL)
		return (1);
	tmp = hd;
	while (tmp != NULL)
	{
		i = 0;
		while (tmp->map[i] != '\0')
		{
			if (check_single_door_position(tmp, i) == 1)
				return (1);
			i++;
		}
		tmp = tmp->next;
	}
	return (0);
}
