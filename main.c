#include "libft/libft.h"

int main(int argc, char *argv[])
{
	ft_printf("str = %s\n", argv[1]);
	ft_printf("<%s>\n", ft_strtrim2(argv[1], "'\""));
	return (0);
}
