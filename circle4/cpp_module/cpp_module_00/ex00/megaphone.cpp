#include <iostream>
#include <cctype>

int main(int ac, char **av)
{
	char	c;

	if (ac == 1)
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
	else
	{
		for (int i = 1; av[i]; i++)
		{
			for (int j = 0; av[i][j] != '\0'; j++)
			{
				c = toupper(av[i][j]);
				std::cout << c;
			}
			if (i < ac - 1)
				std::cout << " ";
		}
		std::cout << std::endl;
	}
}