/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tonken.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 09:36:33 by belguabd          #+#    #+#             */
/*   Updated: 2024/03/23 12:26:24 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#define REDIRECT_APPEND 0 // >>
#define REDIRECT_OUT 1    // >
#define REDIRECT_IN 2     // <
#define HEREDOC 3         // <<
#define SPACE_ 4
#define STRING 5   //"belguabd"
#define PIPE 6     //"|"
#define DOUBLE_Q 7 //""
#define SINGLE_Q 8 //''
#define VAR 9      // variable
#define EXIT_STATUS 10

void ft_process_odd(const char *cmd, token_node **head, int start)
{
    size_t j = start;
    char *str;

    while (cmd[j] && cmd[j] == '$')
        j++;
    if (cmd[j] >= '0' && cmd[j] <= '9')
    {
        str = ft_substr(cmd, start, (j + 1) - start);
        lstadd_back(head, addnew_tkn_node(VAR, str));
    }
    else
    {
        if (is_var(cmd[j]))
        {
            while (ft_isalnum(cmd[j]) || cmd[j] == '_')
                j++;
            str = ft_substr(cmd, start, j - start);
            lstadd_back(head, addnew_tkn_node(VAR, str));
        }
        else
            lstadd_back(head, addnew_tkn_node(STRING, "$"));
    }
}
void ft_process_vars(const char *cmd, token_node **head, int i)
{
    size_t start;
    char *str;

    start = i;
    while (cmd[start] && cmd[start] == '$')
        start++;
    if ((start - i) % 2 != 0)
        ft_process_odd(cmd, head, i);
    else
    {
        start = i;
        while (cmd[i] && cmd[i] == '$')
            i++;
        if (cmd[i] >= '0' && cmd[i] <= '9')
            str = ft_substr(cmd, start, (i + 1) - start);
        else
        {
            while (cmd[i] && (ft_isalnum(cmd[i]) || cmd[i] == '_'))
                i++;
            str = ft_substr(cmd, start, i - start);
        }
        lstadd_back(head, addnew_tkn_node(STRING, str));
    }
}

void handle_single_quotes(int start, const char *cmd, token_node **head)
{
    int j = start;
    char *str;

    j++;
    while (cmd[j])
    {
        if (cmd[j] == '\'')
            break;
        j++;
    }
    str = ft_substr(cmd, start, (j + 1) - start);
    lstadd_back(head, addnew_tkn_node(SINGLE_Q, str));
}
void handle_double_quotes(int start, const char *cmd, token_node **head)
{
    int j = start;
    char *str;

    j++;
    while (cmd[j])
    {
        if (cmd[j] == '\"')
            break;
        j++;
    }
    str = ft_substr(cmd, start, (j + 1) - start);
    lstadd_back(head, addnew_tkn_node(DOUBLE_Q, str));
}
void handle_non_special_chars(int start, const char *cmd, token_node **head)
{
    char *str;
    int j;

    j = start;
    while (cmd[j] && !is_string(cmd[j]))
        j++;
    str = ft_substr(cmd, start, j - start);
    lstadd_back(head, addnew_tkn_node(STRING, str));
}
token_node *tokenization(const char *cmd, token_node **head)
{
    size_t i = 0;
    size_t len;

    len = ft_strlen(cmd);
    while (cmd[i] == ' ' || (cmd[i] >= 9 && cmd[i] <= 13))
        i++;
    while (i < len)
    {
        if (cmd[i] == '|')
            lstadd_back(head, addnew_tkn_node(PIPE, "|"));
        else if (cmd[i] == '$' && cmd[i + 1] == '?')
            lstadd_back(head, addnew_tkn_node(EXIT_STATUS, "$?"));
        else if (cmd[i] == '$')
            ft_process_vars(cmd, head, i);
        else if (cmd[i] == '>' && cmd[i + 1] == '>')
            lstadd_back(head, addnew_tkn_node(REDIRECT_APPEND, ">>"));
        else if (cmd[i] == '<' && cmd[i + 1] == '<')
            lstadd_back(head, addnew_tkn_node(HEREDOC, "<<"));
        else if (cmd[i] == ' ' || (cmd[i] >= 9 && cmd[i] <= 13))
        {
            lstadd_back(head, addnew_tkn_node(SPACE_, " "));
            while (cmd[i] == ' ' || (cmd[i] >= 9 && cmd[i] <= 13))
                i++;
            i--;
        }
        else if (cmd[i] == '\'')
            handle_single_quotes(i, cmd, head);
        else if (cmd[i] == '\"')
            handle_double_quotes(i, cmd, head);
        else if (cmd[i] == '>')
            lstadd_back(head, addnew_tkn_node(REDIRECT_OUT, ">"));
        else if (cmd[i] == '<')
            lstadd_back(head, addnew_tkn_node(REDIRECT_IN, "<"));
        else
            handle_non_special_chars(i, cmd, head);
        i += ft_strlen(ft_lstlast(*head)->value);
    }
    return (*head);
}