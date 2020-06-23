/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 19:14:43 by mizola            #+#    #+#             */
/*   Updated: 2020/06/23 12:32:03 by mizola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_unsigned_numlen(unsigned long long int n)
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

int	ft_signed_numlen(long long int n)
{
	int i;

	i = (n < 0) ? 1 : 0;
	return (i += ft_unsigned_numlen((n < 0) ? -n : n));
}
