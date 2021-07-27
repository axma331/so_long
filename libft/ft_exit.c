/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_msg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feschall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 19:59:38 by feschall          #+#    #+#             */
/*   Updated: 2021/07/16 10:58:20 by feschall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_exit(char *msg, int errno)
{
	write (STDERR_FILENO, msg, ft_strlen(msg));
	write (STDERR_FILENO, "\n", 1);
	exit (errno);
}
