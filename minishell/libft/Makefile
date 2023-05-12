#_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_ COLORS _/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_
RESET	= \033[0m
BLACK 	= \033[1;30m
RED 	= \033[1;31m
GREEN 	= \033[1;32m
YELLOW 	= \033[1;33m
BLUE	= \033[1;34m
PURPLE 	= \033[1;35m
CYAN 	= \033[1;36m
WHITE 	= \033[1;37m

#_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_ COMMANDS _/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_
CC = cc
RM = rm -rf
AR = ar -rcs

#_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_ FLAGS _/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_
CFLAGS	= -Wall -Wextra -Werror
MKFLAGS = --no-print-directory

#_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_ FOLDERS _/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_
DEPS 	= ../inc
OBJ_DIR = ../bin

#_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_ FILES _/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_
NAME			= libft.a
_FILES			= ft_atoi ft_atoull ft_bzero ft_calloc ft_isalnum ft_isalpha ft_isascii ft_isdigit \
					ft_isnum ft_isprint ft_itoa ft_memchr ft_memcmp ft_memcpy ft_memmove ft_memset \
					ft_putchar_fd ft_putendl_fd ft_putnbr_fd ft_putstr_fd ft_split ft_strchr \
					ft_strdup ft_striteri ft_strjoin ft_strlcat ft_strlcpy ft_strlen ft_strmapi ft_strcmp\
					ft_strncmp ft_strnstr ft_strrchr ft_strreplace ft_strtrim ft_substr ft_tolower ft_toupper\
					ft_lstadd_back ft_lstadd_front ft_lstclear ft_lstdelone ft_lstiter ft_lstlast \
					ft_lstmap ft_lstnew ft_lstremove ft_lstsize
OBJS			= $(_FILES:%=%.o)
TARGET			= $(addprefix $(OBJ_DIR)/, $(OBJS))

#_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_ RULES _/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_

all: $(NAME)

$(NAME): $(OBJ_DIR) $(TARGET)
	$(AR) $(NAME) $(TARGET)

$(OBJ_DIR)/%.o : %.c 
	$(CC) $(CFLAGS) -c $< -o $@ -I $(DEPS)

$(OBJ_DIR) :
	mkdir -p $(OBJ_DIR)

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.SILENT:

