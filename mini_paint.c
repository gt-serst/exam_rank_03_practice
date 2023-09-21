/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_paint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gt-serst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 19:48:25 by gt-serst          #+#    #+#             */
/*   Updated: 2023/09/20 21:30:30 by gt-serst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int		width;
int		height;
char	background;

char	type;
float	x;
float	y;
float	radius;
char	color;

FILE	*fd;
int		res;
char	**tab;
int		row;
int		col;
float	sqr;

int	msg_error(FILE *fd, int error)
{
	int	i;

	if (fd)
		fclose(fd);
	if (error == 1)
		write(1, "Error: argument\n", 16);
	else if (error == 2)
	{
		write(1, "Error: Operation file corrupted\n", 32);
		return (1);
	}
	else
	{
		i = 0;
		while (tab[i])
		{
			write(1, tab[i], width);
			write(1, "\n", 1);
			i++;
		}
	}
	return (error);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (msg_error(fd, 1));
	if (!(fd = fopen(argv[1], "r")))
		return (msg_error(fd, 2));
	if ((res = fscanf(fd, "%d %d %c", &width, &height, &background)) != 3)
		return (msg_error(fd, 2));
	if (width <= 300 && width > 0 && height <= 300 && height > 0)
	{
		tab = malloc(sizeof(char *) * height + 1);
		if (!tab)
			return (1);
		row = 0;
		while (row < height)
		{
			tab[row] = malloc(sizeof(char) * width + 1);
			if (!tab[row])
				return (1);
			memset(tab[row], background, width);
			row++;
		}
		while (1)
		{
			res = fscanf(fd, " %c %f %f %f %c", &type, &x, &y, &radius, &color);
			if (res == -1)
				return (msg_error(fd, 0));
			if (res != 5 || radius <= 0 || (type != 'c' && type != 'C'))
				break;
			row = 0;
			while (row < height)
			{
				col = 0;
				while (col < width)
				{
					sqr = sqrtf((col - x) * (col - x) + (row - y) * (row - y));
					if (sqr <= radius)
					{
						if (type == 'c' && sqr + 1 > radius)
							tab[row][col] = color;
						else if (type == 'C')
							tab[row][col] = color;
					}
					col++;
				}
				row++;
			}
		}
	}
	return (msg_error(fd, 2));
}
