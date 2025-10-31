#include <stdio.h>

// Simo already did it

int valid_map(char **map)
{
	int i = 0;
	while (map[i] != NULL)
	{
		int j = 0;
		while (map[i][j] != '\0')
		{
			if (map[i][j] == '0')
			{
				if (i == 0 || j == 0)
					return (0);
				if (map[i - 1][j] != '1' || map[i + 1][j] != '1')
					return (0);
				if (map[i][j - 1] != '1' || map[i][j + 1] != '1')
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}
