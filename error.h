#ifndef ERROR_H
# define ERROR_H

# define MSG_SYNX		"syntax error near unexpected token"
# define MSG_QUOTE		"unexpected EOF while looking for matching"
# define MSG_PARSE		"parse error near"
# define MSG_CMD		"command not found"
# define MSG_PERM		"Permission denied"
# define MSG_FLDR		"Is a directory"
# define MSG_FILE		"No such file or directory"
# define MSG_MEM		"Out of memory"
# define MSG_FORK		"Could not fork"
# define MSG_PIPE		"Could not pipe"

enum e_errcodes
{
	ERR_FILE = 1,
	ERR_PERM = 126,
	ERR_CMD = 127,
	ERR_SIG = 128,
	ERR_SYNX = 258
};

#endif
