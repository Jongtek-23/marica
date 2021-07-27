#include "philo.h"

int	ft_atoi(const char *str)
{
	long int	res;
	long int	sign;

	res = 0;
	sign = 1;
	while (*str == '\t' || *str == '\n' || *str == '\v'
		|| *str == '\f' || *str == '\r' || *str == ' ')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		res = (res * 10) + (*str - 48);
		if (res * sign > INT_MAX)
			return (-1);
		if (res * sign < INT_MIN)
			return (0);
		str++;
	}
	return (res * sign);
}

int ft_is_str_number(char *str)
{
    int i;

    i = 0;
    while ('0' <= str[i] && str[i] <= '9')
        i++;
    if (str[i] != '\0')
        return (1);
    return (0);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_error(char *str)
{
	int	len;

	len = ft_strlen(str);
	write(2, str, len);
	return (1);
}

