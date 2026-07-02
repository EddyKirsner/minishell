CC=		clang
CFLAGS=		-Wall -Werror -Wextra
INC=		./libft.h

SRCLIB=	ft_atoi.c \
		ft_isalpha.c \
		ft_itoa.c \
		ft_memmove.c \
		ft_putnbr_fd.c \
		ft_strdup.c \
		ft_strlcpy.c \
		ft_strnstr.c \
		ft_tolower.c \
		ft_bzero.c \
		ft_isascii.c \
		ft_memchr.c \
		ft_memset.c \
		ft_putstr_fd.c \
		ft_striteri.c \
		ft_strlen.c \
		ft_strrchr.c \
		ft_toupper.c \
		ft_calloc.c \
		ft_isdigit.c \
		ft_memcmp.c \
		ft_putchar_fd.c \
		ft_split.c \
		ft_strjoin.c \
		ft_strmapi.c \
		ft_strtrim.c \
		ft_isalnum.c \
		ft_isprint.c \
		ft_memcpy.c \
		ft_putendl_fd.c \
		ft_strchr.c \
		ft_strlcat.c \
		ft_strncmp.c \
		ft_strcmp.c \
		ft_substr.c \
		ft_lstnew.c \
		ft_lstadd_front.c \
		ft_lstsize.c \
		ft_lstlast.c \
		ft_lstadd_back.c \
		ft_lstdelone.c \
		ft_lstclear.c \
		ft_lstiter.c \
		ft_lstmap.c

SRCPTF=	ft_printf/ft_printf.c \
		ft_printf/ft_printf_utils.c

SRCGNL= get_next_line/get_next_line.c

SRC=	$(SRCLIB) $(SRCPTF) $(SRCGNL)

NAME=	libft.a
AR=		ar rc
OBJ=	$(wildcard *.o)
all:	$(NAME)

$(NAME):
	$(CC) $(CFLAGS) -c $(SRC) -I $(INC)
	$(AR) $(NAME) *.o
	ranlib $(NAME)

clean:
	/bin/rm -f $(OBJ)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY : all clean fclean re
