/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptorrao- <ptorrao-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:07:28 by ptorrao-          #+#    #+#             */
/*   Updated: 2025/03/10 14:07:29 by ptorrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	missing_img_file(t_game *game)
{
	ft_printf("Error\n");
	ft_printf("One or more image files are missing\n");
	ft_exit(game, NULL);
}
