int ft_unsigned_numlen(unsigned long long int n)
{
	int i;

	i = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

int ft_signed_numlen(long long int n)
{
	int i;

	i = (n < 0) ? 1 : 0;
	return (i += ft_unsigned_numlen((n < 0) ? -n : n));
}