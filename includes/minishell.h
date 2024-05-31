/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ****** <******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 12:41:34 by ******            #+#    #+#             */
/*   Updated: 2024/05/30 17:31:35 by ******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include "ft_destructor/ft_alloc.h"
# include "colors.h"
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/stat.h>
# include <termios.h>
# include <readline/history.h>
# include <readline/readline.h>

# define NAME "minishell"
# define DEFAULT_PATH "/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/bin"

/* -DDEBUG=1 enables debugging */
# ifndef DEBUG
#  define DEBUG 0
# endif

# define MAX_SHLVL 1000
# define FT_DESTRUCTOR 1

# ifndef FORCE_TTY
#  define FORCE_TTY 1
# endif

/* character constants used (in place of '$') to mark variable expansion */
# define VARSTART -1
# define VAREND -2
/* home directory of the current user. */
# define VARHOME -3
/* decimal process ID of the invoked shell. */
# define VARPID -4
/* name of the shell or shell script. */
# define VARNAME -5
/* decimal exit status of the most recent foreground pipeline. */
# define VARSTATUS -6
/* Flags that variable is quoted */
# define VARQUOTE -7

/* Error codes */
# define PENDING -1
# define SUCCESS 0
# define FAILED 1
# define MISUSED 2
# define PERM_DENIED 126
# define NOT_FOUND 127
# define SIGNALED 128
# define STATUS_OUT_OF_RANGE 255

/* Internal return codes */
# define OK 0
# define ERR 1
# define NOTFOUND 2

# define HEREDOC_DIR	"/tmp/"
# define HEREDOC_PREFIX	"minishell_tmpfile_"

/* t_word: string with description */
typedef struct s_word
{
	char				*word;
	int					flags;
}						t_word;

/* word list */
typedef struct s_wlist
{
	t_word				word;
	struct s_wlist		*next;
}						t_wlist;

// Enviorment variables
typedef struct s_env
{
	char				*key;
	char				*value;
	struct s_env		*next;
}						t_env;

typedef struct s_shell
{
	char				**envp;
	t_env				*l_envp;
	char				*current_dir;
	int					exit_status;
	int					interactive;
	int					input_fd;
	char				*input_str;
	t_wlist				*heredocs;
	int					heredoc_count;
	char				*home;
	int					stdin_dup;
	int					stdout_dup;
	char				*username;
	char				*hostname;
	t_allocs			*allocs;
}						t_shell;

/*  ===== basic data structures ===== */
/* t_token: identifies token type */
typedef enum e_token
{
	/* error token */
	TERR = -1,
	/* none token */
	TNONE = 0,
	/* word */
	TWORD = 1,
	/* operators */
	TOP,
	TAND,
	TOR,
	TSAND,
	TPIPE,
	TLESS,
	TGREAT,
	TDLESS,
	TDGREAT,
	TNEWLINE
}						t_token;

/* The tokenizer maintinas a small buffer of three characters.
This is necessary for lookbehind capability */
# define TOKBUF_SIZE 3

/* tokenizer state */
typedef struct s_tokstate
{
	char				*input;			/* current character */
	char				buffer[TOKBUF_SIZE];
	int					rule_applied;
	t_buffer			*ctoken;		/* characters of token */
	int					flags;			/* flags for current token */
	int					flags_next;		/* flags for next token*/
	char				quote;			/* quoting state */
	int					delimit;		/* whether to delimit and break out */
	int					*cont;			/* pointer to where to indicate cont */
	bool				is_variable;	/* check for varible */
}						t_tokstate;

typedef int				(*t_builtin)(t_shell *, t_wlist *);

/* assigns builtin name to internal function */
typedef struct s_builtin_mapping
{
	char				*name;
	t_builtin			fun;
}						t_builtin_mapping;

typedef struct s_vars
{
	size_t	i;

	char	*word;
	char	*str;
	char	*varname;
	char	*temp;

	bool	is_var;
	bool	is_quote;

	t_wlist	*current;
}			t_vars;

/* ===== AST data structures ===== */
typedef struct s_cmd
{
	t_wlist				*words;
	int					input[2];
	int					output[2];
	int					flags;
}						t_cmd;

typedef enum e_nodetype
{
	TREE,
	CMD
}						t_nodetype;

typedef struct s_ast	t_ast;

/* tree node */
typedef struct s_asttree
{
	t_token				op;
	t_ast				*left;
	t_ast				*right;
}						t_asttree;

/* AST node */
typedef struct s_ast
{
	t_nodetype			type;
	union				u_data
	{
		t_asttree		tree;
		t_cmd			cmd;
	} data;
}						t_ast;

/* command execution info */
typedef struct s_execinfo
{
	char		*cmdstr;
	t_cmd		*cmd;
	char		*prog;
	t_builtin	builtin;
	int			newenv;
	int			s;
	pid_t		*pid;
}	t_execinfo;

/* pipe execution info */
typedef struct s_pipeinfo
{
	int		len;
	pid_t	*pids;
	int		*pipes;
}	t_pipeinfo;

/* src/builtins/_handler.c */
int			util_test(t_shell *shl, t_wlist *args);
t_builtin	builtin_find(char *s);
/* src/builtins/_options.c */
bool		is_option_valid(char *str);
bool		invalid_option(t_wlist *args, char *usage);
/* src/builtins/cd.c */
int			util_cd(t_shell *shl, t_wlist *args);
/* src/builtins/echo.c */
bool		is_newline(t_wlist **args);
int			util_echo(t_shell *shl, t_wlist *args);
/* src/builtins/env.c */
int			util_env(t_shell *shl, t_wlist *args);
/* src/builtins/exit.c */
void		ft_exit(int status);
int			util_exit(t_shell *shl, t_wlist *args);
/* src/builtins/export.c */
int			export_var(t_shell *shl, char *var);
int			util_export(t_shell *shl, t_wlist *args);
/* src/builtins/pwd.c */
int			util_pwd(t_shell *shl, t_wlist *args);
/* src/builtins/tests.c */
/* src/builtins/unset.c */
int			util_unset(t_shell *shl, t_wlist *args);
/* src/utils/cwd.c */
char		*getcwd_converted(t_shell *shell);
/* src/utils/error.c */
int			errset(int s);
/* src/utils/exit_status.c */
void		set_exit_status(int value);
int			get_exit_status(void);
char		*get_exit_status_str(void);
/* src/utils/ft_close.c */
void		ft_close(int fd);
/* src/utils/ft_stderr.c */
void		ft_stderr(char *msg);
void		ft_stderro(char **arg);
/* src/utils/history.c */
void		ft_addhistory(void);
void		ft_addinput(char *str);
/* src/utils/hostname.c */
char		*get_hostname(void);
/* src/utils/prompt.c */
char		*get_prompt(void);
/* src/utils/signals.c */
void		signal_reset_prompt(int signo);
void		ignore_sigquit(void);
void		signal_set_on_newline(int signal);
void		set_signals_interactive(void);
void		set_signals_noninteractive(void);
/* src/exec/ast.c */
int			ast_list_exec(t_ast *n, t_shell *shell);
int			ast_exec(t_ast *n, t_shell *shell);
void		ast_del(t_ast *n);
/* src/exec/ast_pipe.c */
int			ast_pipe_exec_elem(t_ast *p, int i, t_pipeinfo *pi);
int			ast_pipe_await(t_pipeinfo *pi);
int			ast_pipe_exec(t_ast *p, t_shell *shell);
/* src/exec/ast_print.c */
void		indent(int i);
void		ast_print_lvl_tree(t_ast *a, int lvl);
void		ast_print_lvl(t_ast *a, int lvl);
void		ast_print(t_ast *a);
/* src/exec/ast_utils.c */
t_ast		*ast_tree_new(t_token op);
t_ast		*ast_cmd_new(void);
int			ast_pipelen(t_ast *p);
void		cmd_print(t_ast *n);
/* src/exec/cmd.c */
void		cmd_exec_inner(t_execinfo *einfo);
void		cmd_exec_redirect(t_execinfo *einfo);
int			cmd_exec(t_cmd *cmd, pid_t *pid, int newenv);
int			cmd_wait(pid_t pid, int last);
/* src/exec/cmd_utils.c */
int			run_env(char *cmd, t_wlist *argv);
char		*ft_pathjoin(char *p1, char *p2);
char		*cmd_locate(char *cmdstr);
/* src/exec/redirect.c */
int			redirect_input(t_cmd *cmd, t_wlist *cur, int *remove);
int			redirect_output(t_cmd *cmd, t_wlist *cur, int *remove);
int			redirect(t_cmd *cmd);
void		redirect_restore(t_shell *shl, t_cmd *cmd);
/* src/exec/wildcards.c */
int			pattern_match(char *pattern, char *cand);
/* src/parse/input/cont.c */
int			inccont(int inc);
void		cont(void);
void		nocont(void);
/* src/parse/input/get.c */
char		getinput(char *init_input, int init_fd, int pos, int unget);
/* src/parse/input/shortcuts.c */
char		gch(int i);
char		ch(void);
void		ungch(void);
void		input_init_fd(int fd);
void		input_init_str(char *s);
/* src/parse/input/types.c */
void		input_str(char *buffer, char **input);
void		input_term(char *buffer, char **input);
int			input_fd(char *buffer, int fd);
/* src/parse/parse.c */
int			is_pattern(char *s);
t_wlist		*wlist_from_pattern(char *ptn);
t_ast		*parse(char *s);
t_ast		*parse_error(void);
/* src/parse/parse_descent.c */
t_word		ttoken(int advance);
t_word		token(int advance);
int			accept(int tk);
int			accept_redir(void);
int			expect(int tk);
/* src/parse/symbols.c */
int			nt_command_word(t_ast *n, t_word *word_new, int *valid);
t_ast		*nt_command(void);
t_ast		*nt_pipe(void);
t_ast		*nt_cmdlist(void);
/* src/parse/tokenize/print.c */
void		tk_print2(t_word *tk);
void		tk_print(t_word *tk);
/* src/parse/tokenize/rules1.c */
void		tok_input_end(t_tokstate *t);
void		tok_operator_append(t_tokstate *t);
void		tok_operator_split(t_tokstate *t);
void		tok_quoting(t_tokstate *t);
/* src/parse/tokenize/rules2.c */
void		tok_varinternal(t_tokstate *t);
void		tok_variables(t_tokstate *t);
/* src/parse/tokenize/rules3.c */
void		tok_operator_new(t_tokstate *t);
void		tok_blank(t_tokstate *t);
void		tok_word_append(t_tokstate *t);
void		tok_comment(t_tokstate *t);
void		tok_word_new(t_tokstate *t);
/* src/parse/tokenize/tokenize.c */
t_word		next_token(void);
t_word		ntoken(void);
/* src/shell/destroy.c */
void		shell_errexit(void);
void		shell_destroy(t_shell *shl);
/* src/shell/heredoc.c */
char		*heredoc_filename(int id);
void		heredoc_read(int fd, char *d);
void		heredoc_clean(void);
void		shell_heredoc(t_shell *s);
/* src/shell/init.c */
t_shell		*shell_init(int argc, char **argv, char **envp);
t_shell		*shell(void);
/* src/shell/run.c */
void		shell_run(void);
/* src/variables/add.c */
void		init_var(char *key, char *value, t_env **head);
int			add_var(char *key, char *value);
void		update_var(char *key, char *value);
/* src/variables/envp.c */
t_env		*init_env(char **envp);
void		env_del(t_env *l_envp);
char		**lenvpstr(t_env *l_envp);
char		**lenvp_to_strarr(t_env *l_envp);
/* src/variables/expand.c */
void		exp_variable(t_wlist **lst);
void		ast_expand(t_ast *a);
/* src/variables/expand_extra.c */
bool		exp_internal(t_vars *v);
void		exp_wildcard(t_wlist **lst);
/* src/variables/expand_utils.c */
t_vars		*exp_init(char *word);
bool		var_start(t_vars *v);
void		handle_var_value(t_vars *v, t_wlist **new_words, char **value);
bool		var_end(t_vars *v, t_wlist **new_words);
/* src/variables/get.c */
t_env		*get_var(char *key);
char		*get_varval(char *key);
char		*get_varform(char *str);
char		*get_home(void);
char		*ft_getpid(void);
/* src/variables/print.c */
void		print_env(void);
t_env		*exported_vars(t_env *envp);
void		print_export(void);
/* src/variables/remove.c */
void		remove_var(char *key);
/* src/variables/verify.c */
bool		is_varstart(char c);
bool		is_varchar(char c);
bool		is_param(char c);
bool		verify_var_name(char *env_var);
/* src/wlist/add.c */
t_wlist		*wlist_new(t_word word);
void		wlist_add(t_wlist **l, t_word w);
void		wlist_adds(t_wlist **l, char *s);
void		wlist_addl(t_wlist **lst, char *s, int flags);
/* src/wlist/extra.c */
int			wlist_eq(t_wlist *l, int num, ...);
t_wlist		*wlist(int n, ...);
/* src/wlist/remove.c */
t_wlist		*wlist_remove(t_wlist **lst, t_wlist *item);
void		wlist_del(t_wlist *l);
/* src/wlist/update.c */
void		wlist_update(t_wlist *l, char *s);
void		wlist_replace(t_wlist *l, char *s);
/* src/wlist/utils.c */
size_t		wlist_len(t_wlist *l);
char		**wlist_to_strarr(t_wlist *l);
void		wlist_print(t_wlist *l);
t_wlist		*wlist_last(t_wlist *l);
int			wlist_cmp(t_wlist *a, t_wlist *b);

#endif