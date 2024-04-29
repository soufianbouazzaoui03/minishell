/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soel-bou <soel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 02:48:20 by soel-bou          #+#    #+#             */
/*   Updated: 2024/04/29 16:52:23 by soel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void handler(int sig)
{
    rl_catch_signals = 0;
    // add a variable to check if you are in line or in execution and check if the variable is 0 or no if 0 execute the if condition else don't
    if (sig == SIGINT)
    {
        write(1, "\n", 1); // Print a newline to ensure a new prompt starts on a new line
        rl_replace_line("", 0);
        rl_on_new_line(); // Reset readline's internal state
        rl_redisplay();
    }
}