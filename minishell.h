/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 13:50:21 by belguabd          #+#    #+#             */
/*   Updated: 2024/03/08 14:52:42 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>
#define COLOR_RESET "\x1b[0m"
#define COLOR_GREEN "\x1b[32m"

typedef struct command_node // start line cmd
{
	char *cmd;
	char *arg;
	struct command_node *next;
} t_cmd;

typedef enum tokenize
{
	SPACE,			//" "
	STRING,			//"belguabd"
	PIPE,			//"|"
	DOUBLE_Q,		//""
	SINGLE_Q,		//''
	REDIRECT_IN,	// <
	REDIRECT_OUT,	// >
	HEREDOC,		// <<
	REDIRECT_APPEND, // >>
	VAR//variable
} t_token;

typedef struct token_node
{
	t_token type;
	char *value;
	struct token_node *next;
} t_tkn_node;

typedef struct s_vars
{
	char **res;
	size_t i;
	int j;
	int flage;
	int start;
} t_vars;

/*ft_split*/
char **ft_split(char const *str, char c);
size_t ft_strlen(const char *s);

char *ft_strdup(const char *s1);
// char *ft_strdup(const char *cmd, int start, int end);
/*libft*/
char *ft_substr(char const *s, unsigned int start, size_t len);
#endif