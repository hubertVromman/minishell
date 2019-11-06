/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 14:48:02 by hvromman          #+#    #+#             */
/*   Updated: 2019/10/14 14:48:04 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPES_H
# define PROTOTYPES_H

/*
**              **
**     core     **
**              **
*/

/*
** argument_parser.c
*/
int			parse_arguments(void);

/*
** char_action.c
*/
int			realloc_line(void);
int			append_to_line(char ch, int pos);
int			get_escape(int *free_base);
int			add_character(char ch);
int			back_space(void);

/*
** command_handler.c
*/
int			command_handler(void);

/*
** dollar_parser.c
*/
char		*replace_dollar(char *line, int dollar_pos, int end);
char		*search_dollar(char *line);

/*
** error.c
*/
int			error(char *error_msg, char *details);

/*
** exit.c
*/
int			free_all(void);
int			exit_func(int exit_code);
int			exit_no_error(int exit_code);

/*
** line_parser.c
*/
int			line_parser(void);

/*
** main.c
*/
int			main(int ac, char **av, char **env);

/*
** reader.c
*/
int			getch_killable(void);
int			deal_with_this(char ch);

/*
** signal.c
*/
void		sig_winch(int c);
void		sig_int(int c);

/*
** term_util.c
*/
int			get_pos_reader(char *buf, int *x, int *y, int i);
int			get_pos(int *y, int *x);
int			move_to(int new_pos);
int			start_line(void);

/*
** util.c
*/
void		*realloc_buffer(void *prev_buf, int prev_size, int new_size);
int			friint(void *ptr);
char		*read_full_file(int fd);
char		*get_dir(char *path);
int			free_lines(void);

/*
**                 **
**     builtin     **
**                 **
*/

/*
** builtin_dispatcher.c
*/
int			builtin_dispatcher(void);

/*
** cd_builtin.c
*/
char		*replace_home(char *arg, int *is_to_free);
int			get_error(char *buf, char *arg, int is_to_free);
int			cd_builtin(void);

/*
** echo_builtin.c
*/
int			echo_builtin(void);

/*
** env_builtin.c
*/
int			env_builtin(void);

/*
** exit_builtin.c
*/
int			ft_atol_modified(char *str, long *nbr);
int			exit_builtin(void);

/*
** pwd_builtin.c
*/
int			pwd_builtin(void);

/*
** setenv_builtin.c
*/
int			setenv_builtin(void);

/*
** unsetenv_builtin.c
*/
int			unsetenv_builtin(void);

/*
**             **
**     env     **
**             **
*/

/*
** get_env.c
*/
char		*get_env_var(char *var);
int			get_env_pos(char *var);
int			print_env(void);

/*
** set_env.c
*/
int			delete_env_var(int pos);
int			modify_env_var(int pos, char *name, char *value);
int			add_env_var(char *name, char *value);
int			init_env(char **env);

/*
**                 **
**     history     **
**                 **
*/

/*
** get_history.c
*/
char		*get_history(int new_pos);
int			check_move_history(char *compare, int new_history_pos);
int			get_previous_pos_of(int direction);

/*
** history_reader.c
*/
int			get_line_size(char *file_content, int size);
int			get_history_size(char *file_content);
char		*get_line(char *file_content, int *line_size);
int			read_all_history_file(void);

/*
** set_history.c
*/
int			init_history(void);
int			add_to_history(char *data);

/*
**             **
**     var     **
**             **
*/

/*
** get_var.c
*/
char		*get_var(char *var);
int			get_var_pos(char *var);
int			print_var(void);

/*
** init_var.c
*/
int			init_var(void);

/*
** set_var.c
*/
int			delete_var(int pos);
int			add_var(char *name, char *value);
int			change_or_add_var(char *name, char *value);
int			change_or_add_var_int(char *name, int value);

#endif
