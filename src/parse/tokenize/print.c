/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ****** <******@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 18:05:33 by ******            #+#    #+#             */
/*   Updated: 2024/05/29 12:44:40 by ******           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* print token as readable name */

void	tk_print2(t_word *tk)
{
	if (tk->flags == TDLESS)
		printf("TDLESS\n");
	else if (tk->flags == TGREAT)
		printf("TGREAT\n");
	else if (tk->flags == TDGREAT)
		printf("TDGREAT\n");
	else if (tk->flags == TNEWLINE)
		printf("TNEWLINE\n");
	else
		printf("TOKEN unrecognized: %i\n", tk->flags);
}

void	tk_print(t_word *tk)
{
	if (tk->flags == TNONE)
		printf("TNONE\n");
	else if (tk->flags == TWORD)
	{
		printf("TWORD");
		printf(": '%s'\n", tk->word);
	}
	else if (tk->flags == TAND)
		printf("TAND\n");
	else if (tk->flags == TOR)
		printf("TOR\n");
	else if (tk->flags == TOP)
		printf("TOP\n");
	else if (tk->flags == TPIPE)
		printf("TPIPE\n");
	else if (tk->flags == TLESS)
		printf("TLESS\n");
	else
		tk_print2(tk);
}

// void	print_tokens(char *s)
// {
// 	t_word	tk;

// 	printf("=== tokenization ===\n");
// 	if (s)
// 		next_token(s, NULL);
// 	while (1)
// 	{
// 		tk = next_token(NULL, NULL);
// 		tk_print(&tk);
// 		if (tk.flags == TNONE)
// 			break ;
// 	}
// 	printf("\n");
// }
