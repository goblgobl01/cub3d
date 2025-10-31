#include <stdlib.h>
#include <stdio.h>

char	*getred(char *str)
{
	char	*r;
	int		i;

	r = malloc(4);
	i = 0;
	while (str[i] != ',')
	{
		r[i] = str[i];
		i++;
	}
	r[i] = '\0';
	return (r);
}

char	*getgreen(char *str)
{
	char	*g;
	int		i;
	int		j;

	g = malloc(4);
	i = 0;
	while (str[i] != ',')
		i++;
	i++;
	j = 0;
	while (str[i] != ',')
	{
		g[j] = str[i];
		i++;
		j++;
	}
	g[j] = '\0';
	return (g);
}

char	*getblue(char *str)
{
	char	*b;
	int		i;
	int		j;

	b = malloc(4);
	i = 0;
	while (str[i] != ',')
		i++;
	i++;
	while (str[i] != ',')
		i++;
	i++;
	j = 0;
	while (str[i] != '\0')
	{
		b[j] = str[i];
		i++;
		j++;
	}
	b[j] = '\0';
	return (b);
}

int	rgb2hex(char *str)
{
	char	*red;
	char	*green;
	char	*blue;
	int		color;

	red = getred(str);
	green = getgreen(str);
	blue = getblue(str);
	color = atoi(red);
	color <<= 8;
	color += atoi(green);
	color <<= 8;
	color += atoi(blue);
	free(red);
	free(green);
	free(blue);
	return (color);
}

void	main(void)
{
	int	i;

	i = rgb2hex("145,0,255");
	printf("%d\n", i);
}
