/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   micro_paint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gt-serst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:51:17 by gt-serst          #+#    #+#             */
/*   Updated: 2023/09/19 18:38:40 by gt-serst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int		width;
int		height;
char	background;

size_t	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int	main(int argc, char **argv)
{
	int		ret;
	FILE	*fd;

	if (argc != 2)
		return (1);
	fd = fopen(argv[1], "r");
	ret = fscanf(fd, "%d %d %c", &width, &height, &background);
	return (0);
}
