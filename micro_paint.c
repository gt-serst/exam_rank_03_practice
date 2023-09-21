/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   micro_paint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gt-serst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:51:17 by gt-serst          #+#    #+#             */
/*   Updated: 2023/09/20 21:30:27 by gt-serst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int		width;
int		height;
char	background;
char	**tab;

char	type;
float	x;
float	y;
float	horizontal;
float	vertical;
char	color;

float	sqr;
int		row;
int		col;
int		res;
FILE 	*fd;


int	msg_error(FILE *fd, int error)
{
	int	i;

	if (fd)
		fclose(fd);
	if (error == 1)
		write(1, "Error: argument\n", 16);
	else if (error == 2)
	{
		write (1, "Error: Operation file corrupted\n", 32);
		return(1);
	}
	else
	{
		i = 0;
		while (i < height)
		{
			write(1, tab[i], width);
			write(1, "\n", 1);
			i++;
		}
	}
	return (error);
}

float in_rectangle(float row, float col)
{
	if (col < x || (x + horizontal) < col || row < y || (y + vertical) < row)
		return (0);
	else if (col - x < 1.0 || (x + horizontal) - col < 1.0 || row - y < 1.0 || (y + vertical) - row < 1.0)
		return (2);
	return (1);
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
			res = fscanf(fd, " %c %f %f %f %f %c", &type, &x, &y, &horizontal, &vertical, &color);
			if(res == -1)
				return (msg_error(fd, 0));
			else if (res != 6 || horizontal <= 0 || vertical <= 0 || (type != 'r' && type != 'R'))
				break;
			row = 0;
			while (row < height)
			{
				col = 0;
				while (col < width)
				{
					sqr = in_rectangle(row, col);
					if (type == 'r' && sqr == 2)
						tab[row][col] = color;
					else if (type == 'R' && sqr)
						tab[row][col] = color;
					col++;
				}
				row++;
			}
		}
	}
	return (msg_error(fd, 2));
}
