.PHONY : all check-build real-all debug clean fclean re

MAKEFLAGS += --no-print-directory

NAME = philo
CC = cc
CFLAGS = -Werror -Wextra -Wall
CFLAGS += 											\
						-Iinclude/init				\
						-Iinclude/parsing			\
						-Iinclude/philo				\
						-Iinclude/routine			\
						-Iinclude/threads
DFLAGS = -MMD -MF
#------------------------------------DEBUG------------------------------------#
CFLAGS_DEBUG = -g3 -Wuninitialized -fno-inline -O0
DEBUG_MODE =
#-------------------------------------SRC-------------------------------------#
SRC 			= 									\
						src
SRC_DIR 		=									\
						init						\
						main						\
						parsing						\
						routine						\
						threads
init_SRCS		=									\
						all_free.c					\
						init.c						\
						set_malloc.c
main_SRCS		=									\
						main.c
parsing_SRCS	=									\
						lib.c						\
						parsing.c
routine_SRCS	=									\
						actions.c					\
						eat_utils.c					\
						routine.c					\
						timestamp.c
threads_SRCS	=									\
						manage_threads.c			\
						state_of_philo.c

SRCS =	$(foreach dir,$(SRC_DIR), $(addprefix $(SRC)/$(dir)/,$($(dir)_SRCS)))
#-----------------------------------OBJECTS-----------------------------------#
OBJ_DIR = 											\
					obj
OBJS = $(patsubst $(SRC)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
#-------------------------------------DEPS------------------------------------#
DEPS_DIR = deps
DEPS = $(patsubst $(SRC)/%.c, $(DEPS_DIR)/%.d, $(SRCS))
#-----------------------------------INCLUDE-----------------------------------#
INCLUDE			=		 							\
						include
HEADER_DIR		=									\
						init						\
						parsing						\
						philo						\
						routine						\
						threads
init_HDR		=									\
						init.h
parsing_HDR		=									\
						parsing.h
philo_HDR		=									\
						philo.h
routine_HDR		=									\
						actions.h					\
						routine.h
threads_HDR	=										\
						my_threads.h
#------------------------------------RULES------------------------------------#
all : check-build

check-build :
	@if [ -f "$(NAME)" ] \
		&& [ -z "$$(find "$(OBJ_DIR)" -type f -newer "$(NAME)")" ] \
		&& [ -z "$$(find "$(SRC)" -name "*.c" -newer "$(NAME)")" ] \
		&& [ -z "$$(find "$(INCLUDE)" -name "*.h" -newer "$(NAME)")" ] \
		&& [ -z "$$(find . -name "Makefile" -newer "$(NAME)")" ]; then \
		echo "✅ Project is already up to date!"; \
	else \
		$(MAKE) real-all; \
	fi

real-all : $(OBJS) $(NAME) $(HEADER)

$(OBJ_DIR)/%.o : $(SRC)/%.c Makefile
	@mkdir -p $(dir $@) $(dir $(DEPS))
	@$(CC) $(CFLAGS) $(DFLAGS) $(DEPS_DIR)/$*.d -c $< -o $@
	

$(NAME) : $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "🚀 Executable is ready to run."

-include $(DEPS)

debug :
	@echo "🎯 Compiling for debug: $(CFLAGS) $(CFLAGS_DEBUG)"
	@$(MAKE) re CFLAGS="$(CFLAGS) $(CFLAGS_DEBUG)" DEBUG_MODE=debug

clean :
	@rm -rf $(OBJ_DIR) $(DEPS_DIR)
	@echo "🧹 Object files removed."

fclean : clean
	@rm -rf $(NAME)
	@echo "🧼 Full clean complete."

re : fclean all
