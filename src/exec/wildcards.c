/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ****** <******@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 18:35:17 by ******            #+#    #+#             */
/*   Updated: 2024/05/29 12:41:09 by ******           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	pattern_match(char *pattern, char *cand)
{
	if (!*cand && !*pattern)
		return (1);
	if ((*pattern == '*' || *pattern == *cand) && (\
		(*cand && pattern_match(pattern, cand + 1)) || \
		(*pattern && *cand && pattern_match(pattern + 1, cand + 1)) || \
		(*pattern == '*' && pattern_match(pattern + 1, cand))))
		return (1);
	return (0);
}
