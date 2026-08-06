/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 08:50:33 by texenber          #+#    #+#             */
/*   Updated: 2026/07/13 09:18:27 by texenber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int validate_textures(char *arg)
{
	int	len;
	char *tex_str;

	len = ft_strlen(arg);
	if (len < 4)
		return (EXIT_FAILURE);
	tex_str = ft_strrchr(arg, '.');
	if (tex_str == NULL)
		return (EXIT_FAILURE);
	if (ft_strcmp(tex_str, ".xpm") != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	texture_extraction(char **target, char *line)
{
	int		i;
	char	*s;
	
	i = 2;
	if (*target != NULL)
		return(print_error(TEXT_DUP), EXIT_FAILURE);
	while (ft_is_space(line[i]) != 0)
		i++;
	if ((s = ft_strrchr(line, '\n')) != 0)
		*s = '\0';
	*target = ft_strdup(line + i);
	if (*target == NULL)
		return (print_error(STRDUP_FAIL), EXIT_FAILURE);
	if (validate_textures(*target) != EXIT_SUCCESS)
		return (print_error(INV_TEXT), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	parse_textures(t_game *data, char *line)
{
	if (ft_strncmp(line, "NO", 2) == 0)
	{	
		if (texture_extraction(&data->map.north, line) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
		printf("%s\n", data->map.north); // FOR TESTING ONLY
	}
	if (ft_strncmp(line, "SO", 2) == 0)
	{	
		if (texture_extraction(&data->map.south, line) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
		printf("%s\n", data->map.south); // FOR TESTING ONLY
	}
	if (ft_strncmp(line, "EA", 2) == 0)
	{	
		if (texture_extraction(&data->map.east, line) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
		printf("%s\n", data->map.east); // FOR TESTING ONLY
	}
	if (ft_strncmp(line, "WE", 2) == 0)
	{	
		if (texture_extraction(&data->map.west, line) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
		printf("%s\n", data->map.west); // FOR TESTING ONLY
	}
	return(EXIT_SUCCESS);
}