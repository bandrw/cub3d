/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfriese <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 03:12:14 by kfriese           #+#    #+#             */
/*   Updated: 2021/02/05 03:12:18 by kfriese          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOOKS_H
# define HOOKS_H

int		key_press(int key, t_mlx *mlx_info);
int		key_release(int key, t_mlx *mlx_info);
int		key_handle(t_mlx *mlx_info);
int		mouse_movement(int x, int y, t_mlx *mlx_info);

#endif
