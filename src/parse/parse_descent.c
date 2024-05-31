/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_descent.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ****** <******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 14:16:51 by ******           #+#    #+#             */
/*   Updated: 2024/05/29 14:18:27 by ******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_word	ttoken(int advance)
{
	static t_word	t = {0, TNONE};

	if (advance)
	{
		t = next_token();
		if (DEBUG)
			tk_print(&t);
	}
	return (t);
}

/* Receive current token
If `advance` is true, advance to next token */
t_word	token(int advance)
{
	return (ttoken(advance));
}

int	accept(int tk)
{
	return (token(0).flags == tk);
}

int	accept_redir(void)
{
	return (accept(TGREAT) || accept(TDGREAT) || \
				accept(TLESS) || accept(TDLESS));
}

int	expect(int tk)
{
	if (token(0).flags == tk)
		return (1);
	printf("Error: Unexpected token (%i: %s)\n", token(0).flags, token(0).word);
	return (0);
}
