NAME := pipex
BONUS_NAME := pipex
.DEFAULT_GOAL := all
CC := cc
RM := rm -rf

################################################################################
###############                  DIRECTORIES                      ##############
################################################################################

# OBJ_DIR := _obj
# INC_DIRS := . libft
# SRC_DIRS := . 
# BONUS_DIR := checker_bonus/_obj_bonus
OBJ_DIR := _obj
BONUS_DIR := bonus/_obj_bonus
INC_DIRS := . libft
SRC_DIRS := .

# Tell the Makefile where headers and source files are
vpath %.h $(INC_DIRS)
vpath %.c $(SRC_DIRS) bonus

################################################################################
###############                  SOURCE FILES                     ##############
################################################################################

SRCS := main.c split_with_quotes.c exec_command.c exec_command_helpers.c \
		pipex_utils.c pipex.c process_management.c file_operations.c \
		error_exit.c parse_command.c parse_command_helpers.c process_family.c \
		search_and_exec.c


BONUS_SRCS := 	bonus/main_bonus.c bonus/split_with_quotes_bonus.c \
				bonus/exec_command_bonus.c bonus/exec_command_helpers_bonus.c \
				bonus/pipex_utils_bonus.c bonus/pipex_bonus.c \
				bonus/process_management_bonus.c bonus/file_operations_bonus.c \
				bonus/error_exit_bonus.c bonus/parse_command_bonus.c \
				bonus/parse_command_helpers_bonus.c bonus/process_family_bonus.c \
				bonus/search_and_exec_bonus.c bonus/add_token_to_args_bonus.c \
				bonus/get_env_helpers_bonus.c bonus/handle_heredoc_bonus.c 

# BONUS_SRCS := 	cps_convert_args.c cps_helpers.c cps_initialize.c \
# 				cps_main.c cps_operations.c cps_parse_validate.c \
# 				cps_sort_assign_indices.c 

################################################################################
###############                  OBJECT FILES                     ##############
################################################################################

# Common object files used by both main and bonus
COMMON_OBJS := $(addprefix $(OBJ_DIR)/, $(SRCS:%.c=%.o))

# Main program object files
# MAIN_OBJS := $(addprefix $(OBJ_DIR)/, $(MAIN_SRCS:%.c=%.o))

# Bonus program object files
# BONUS_OBJS := $(addprefix $(BONUS_DIR)/, $(notdir $(BONUS_SRCS:%.c=%.o)))
BONUS_OBJS := $(BONUS_SRCS:bonus/%.c=$(BONUS_DIR)/%.o)

LIBFT := libft/libft.a


# OBJS := $(addprefix $(OBJ_DIR)/, $(SRCS:%.c=%.o) $(MAIN_SRCS:%.c=%.o))
# # BONUS_OBJS := $(addprefix $(BONUS_DIR)/, $(SRCS:%.c=%.o) $(BONUS_SRCS:%.c=%.o) $(BONUS_MAIN_SRCS:%.c=%.o))
# BONUS_OBJS := $(addprefix $(BONUS_DIR)/, $(notdir $(SRCS:%.c=%.o) $(BONUS_SRCS:%.c=%.o) $(BONUS_MAIN_SRCS:%.c=%.o)))
# # GNL_OBJS := $(addprefix $(OBJ_DIR)/, $(GNL_SRCS:%.c=%.o))
# # GC_OBJS := $(addprefix $(OBJ_DIR)/, $(GC_SRCS:%.c=%.o))

# LIBFT := libft/libft.a

################################################################################
########                         COMPILING                      ################
################################################################################

# CFLAGS := -Wall -Wextra -Werror -g -MMD -MP -I$(INC_DIRS)
CFLAGS := -Wall -Wextra -Werror -g -MMD -MP $(addprefix -I, $(INC_DIRS))
LDFLAGS := -Llibft -lft
#ARFLAGS := -rcs

all: $(LIBFT) $(NAME)

$(NAME): $(OBJ_DIR) $(COMMON_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(COMMON_OBJS) $(LDFLAGS) -o $(NAME)

bonus: $(LIBFT) $(BONUS_DIR) $(BONUS_OBJS)
	$(CC) $(CFLAGS) $(BONUS_OBJS) $(LDFLAGS) -o $(BONUS_NAME)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BONUS_DIR)/%.o: bonus/%.c | $(BONUS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BONUS_DIR):
	mkdir -p $(BONUS_DIR)

clean:
	$(RM) $(OBJ_DIR) $(BONUS_DIR)

fclean: clean
	$(RM) $(NAME) $(BONUS_NAME)
	$(RM) libft/_obj libft/libft.a

re: fclean all

$(LIBFT):
	make -C libft

help:
	@echo "Makefile for $(NAME)"
	@echo "Usage:"
	@echo "	make						Build the project"
	@echo "	make bonus					Build the project with bonus functions"
	@echo "	make clean					Remove object files in the main project"
	@echo "	make fclean					Remove all build files, including libft's objects"
	@echo "	make re						Clean and rebuild the project"
	@echo "	make help					Display this help message"

-include $(OBJS:%.o=%.d)
# -include $(BONUS_OBJS:%.o=%.d)
# -include $(GNL_OBJS:%.o=%.d)

.PHONY: all bonus clean fclean re help