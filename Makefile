NAME	:= ft_traceroute

SRCS	:= ft_traceroute.c \
			parser.c \
			error.c \
			init.c \
			print.c \
			send.c \
			recv.c \
			utils_time.c

# ---------------------------------------------------------------------------- #
#                                     PATHS                                    #
# ---------------------------------------------------------------------------- #

DIR_INCLUDES:= includes
DIR_OBJS	:= objs
VPATH		:= srcs
LIBFT		:= libft

# ---------------------------------------------------------------------------- #
#                                   VARIABLES                                  #
# ---------------------------------------------------------------------------- #

OBJS	= $(addprefix $(DIR_OBJS)/, $(SRCS:.c=.o))
DEPS	:= $(OBJS:.o=.d)
CC		:= gcc
CFLAGS	:= -Wall -Wextra -Werror
INCLUDES:= -I $(DIR_INCLUDES) -I $(LIBFT)

ifdef BONUS
	CFLAGS	+= -D BONUS
endif

# ---------------------------------------------------------------------------- #
#                                     RULES                                    #
# ---------------------------------------------------------------------------- #

.PHONY: all
all		: $(NAME)

-include $(DEPS)

$(NAME)	: $(DIR_OBJS) $(OBJS)
	$(MAKE) -C $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L$(LIBFT) -lft

$(DIR_OBJS)/%.o: %.c
	$(CC) $(CFLAGS) -MMD -MP $(INCLUDES) -o $@ -c $<

$(DIR_OBJS):
	@mkdir $@

.PHONY: clean
clean	:
	$(MAKE) clean -C $(LIBFT)
	$(RM) -R $(DIR_OBJS)

.PHONY: fclean
fclean	: clean
	$(MAKE) fclean -C $(LIBFT)
	$(RM) $(NAME)

.PHONY: re
re		: fclean
	$(MAKE) all

.PHONY	: bonus
bonus	:
	make BONUS=1

# ---------------------------------------------------------------------------- #
#                                    DOCKER                                    #
# ---------------------------------------------------------------------------- #

.PHONY:	docker
docker :
	docker build . -t $(NAME)_ctn
	docker run -d --cap-add=NET_ADMIN -v "$(shell pwd)":/workdir --name $(NAME)_img $(NAME)_ctn

.PHONY:	conn
conn	:
	docker exec -it $(NAME)_img /bin/bash

# ---------------------------------------------------------------------------- #
#                                     TEST                                     #
# ---------------------------------------------------------------------------- #

.PHONY: test
test	: all
	cd ./test && ./test_compare.sh test_option_param.sh