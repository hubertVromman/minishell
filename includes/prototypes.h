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
**                **
**     projet     **
**                **
*/

/*
** command_handler.c
*/
int			dispatcher();

/*
** error.c
*/
int			error(char *error_msg, char *details);

/*
** exit.c
*/
int			exit_func(int exit_code);
int			exit_no_error(int exit_code);

/*
** reader.c
*/
int			getch_killable(void);
int			realloc_line();
int			append_to_line(char ch, int pos);
int			deal_with_this(char ch);

/*
** signal.c
*/
void		sig_winch(int c);
void		sig_int_child(int c);
void		sig_int(int c);

/*
** term_util.c
*/
int			get_pos(int *y, int *x);
int			move_to(int new_pos);
int			start_line();

/*
** util.c
*/
char		*get_dir(char *path);
char		*read_full_file(int fd);
void		*realloc_buffer(void *prev_buf, int prev_size, int new_size);
int			free_lines();

/*
**                 **
**     builtin     **
**                 **
*/

/*
** builtin_dispatcher.c
*/
int			builtin_dispatcher();

/*
** cd_builtin.c
*/
int			cd_builtin();

/*
** echo_builtin.c
*/
int			echo_builtin();

/*
** env_builtin.c
*/
int			env_builtin();

/*
** exit_builtin.c
*/
int			exit_builtin();

/*
** pwd_builtin.c
*/
int			pwd_builtin();

/*
** setenv_builtin.c
*/
int			setenv_builtin();

/*
** unsetenv_builtin.c
*/
int			unsetenv_builtin();


/*
**             **
**     env     **
**             **
*/

/*
** get_env.c
*/
int			get_env_pos(char *var);
char		*get_env_var(char *var);
int			print_env();

/*
** set_env.c
*/
int			add_env_var(char *name, char *value);
int			delete_env_var(int pos);
int			init_env(char **env);
int			modify_env_var(int pos, char *name, char *value);

/*
**                 **
**     history     **
**                 **
*/

/*
** get_history.c
*/

/*
** get_history.c
*/
char		*get_history(int new_pos);
int			get_previous_pos_of(int direction);

/*
** set_history.c
*/
int			init_history();
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
int			print_var();

/*
** set_var.c
*/
int			delete_var(int pos);
int			modify_var(int pos, char *name, char *value);
int			add_var(char *name, char *value);
int			change_or_add_var(char *name, char *value);
int			change_or_add_var_int(char *name, int value);
int			init_var();

#endif
