/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 09:27:11 by texenber          #+#    #+#             */
/*   Updated: 2026/07/13 12:09:50 by texenber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	color_extraction(char **target, bool *flag,char *line)
{
	int		i;
	char	**s;
	
	i = 1;
	if (*flag != 0)
		return (print_error(COLOR_DUP), EXIT_FAILURE);
	while (ft_is_space(line[i]) != 0)
		i++;
	if (line[i] == '\0')
		return (print_error(INV_COLOR), EXIT_FAILURE);
	s = ft_split(line + i, ',');
	if (s == NULL)
		return (print_error(SPLIT_FAIL), EXIT_FAILURE);
	i = 0;
	while (s[i] != NULL)
		i++;
	if (i != 3)
		return (free_array(s), print_error(INV_COLOR), EXIT_FAILURE);
	// validate_and_store_color(); ****** WIP *******
	*flag = true;
}

int	parse_colors(t_game *data, char *line)
{
	if ((ft_strncmp(line, "C", 1) == 0) && (ft_is_space(line[1]) != 0))
	{	
		if (color_extraction(&data->map.c_color, &data->map.has_ceiling, line) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
		printf("%d\n", data->map.c_color); //TESTING ONLY
	}
	if (ft_strncmp(line, "F", 1) == 0)
	return (EXIT_SUCCESS);
}