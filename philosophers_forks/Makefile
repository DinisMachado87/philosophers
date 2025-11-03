NAME        = philo
CC          = cc
CFLAGS      = -Wall -Werror -Wextra -pthread
DEBUGFLAGS  = -g
HEADER      = philo_bonus.h
INCLUDES    = .

SRC			= src/main_bonus.c \
			  src/routine_bonus.c \
			  src/monitor_bonus.c \
			  src/free_all_bonus.c \
			  src_init/init_state_bonus.c \
			  src_init/init_semaphores_bonus.c \
			  src_init/init_philosophers_bonus.c \
			  src_utils/ft_atoll_bonus.c \
			  src_utils/sem_utils_bonus.c \
			  src_utils/utils_bonus.c

OBJDIR      = obj
OBJDIR_DEBUG= obj_debug

OBJ         = $(addprefix $(OBJDIR)/,$(notdir $(SRC:.c=.o)))
OBJ_DEBUG   = $(addprefix $(OBJDIR_DEBUG)/,$(notdir $(SRC:.c=.o)))

$(shell mkdir -p $(OBJDIR) $(OBJDIR_DEBUG))

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -I$(INCLUDES) $(OBJ) -o $(NAME)

debug: $(OBJ_DEBUG)
	$(CC) $(CFLAGS) $(DEBUGFLAGS) -I$(INCLUDES) $(OBJ_DEBUG) -o $(NAME)_debug

$(OBJDIR)/%.o: src/%.c $(HEADER)
	$(CC) $(CFLAGS) -I$(INCLUDES) -c $< -o $@

$(OBJDIR)/%.o: src_init/%.c $(HEADER)
	$(CC) $(CFLAGS) -I$(INCLUDES) -c $< -o $@

$(OBJDIR)/%.o: src_utils/%.c $(HEADER)
	$(CC) $(CFLAGS) -I$(INCLUDES) -c $< -o $@

$(OBJDIR_DEBUG)/%.o: src/%.c $(HEADER)
	$(CC) $(CFLAGS) $(DEBUGFLAGS) -I$(INCLUDES) -c $< -o $@

$(OBJDIR_DEBUG)/%.o: src_init/%.c $(HEADER)
	$(CC) $(CFLAGS) $(DEBUGFLAGS) -I$(INCLUDES) -c $< -o $@

$(OBJDIR_DEBUG)/%.o: src_utils/%.c $(HEADER)
	$(CC) $(CFLAGS) $(DEBUGFLAGS) -I$(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(OBJDIR_DEBUG)

fclean: clean
	rm -f $(NAME) $(NAME)_debug

re: fclean all

.PHONY: all clean fclean re debug
