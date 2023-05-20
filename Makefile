# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: prachman <prachman@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/18 15:22:43 by prachman          #+#    #+#              #
#    Updated: 2023/05/18 15:36:12 by prachman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAGS = -Wall -Wextra -Werror -pthread

NAME = philo

LIBFT_PATH = libft/
LIBFT_FLAG = -Llibft -lmylib
# LIBFT_HD = -Ilibft

# GNL_PATH = get_next_line/
# GNL_FLAG = -get_next_line -lgnl
# GNL_HD = -Iget_next_line

LIBFT_SRCS = ft_atoi.c

PHILO_SRCS = philo.c

SRCS = $(FDF_SRCS) \
						$(addprefix $(LIBFT_PATH), $(LIBFT_SRCS)) \
						# $(addprefix $(GNL_PATH), $(GNL_SRCS))

OBJS = $(SRCS:.c=.o)

all: $(NAME)

%o:%c
	gcc $(FLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@make -C $(LIBFT_PATH)
	gcc $(OBJS) $(FLAGS) -o $(NAME)

clean:
	@make fclean -C $(LIBFT_PATH)
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: clean all

.PHONY: clean fclean re all bonus