ASM = nasm
ASMFLAGS = -f elf64

CC = cc
CFLAGS = -Wall -Wextra -Werror

NAME = libasm.a
HEADER = libasm.h

ASM_SRCS = ft_strlen.s ft_strcpy.s ft_strcmp.s ft_write.s ft_read.s ft_strdup.s
 
ASM_BONUS_SRCS = ft_atoi_base_bonus.s ft_list_push_front_bonus.s ft_list_size_bonus.s \
				 ft_list_sort_bonus.s ft_list_remove_if_bonus.s

MAIN_SRC = main.c

OBJDIR = obj
ASM_OBJS = $(patsubst %.s,$(OBJDIR)/%.o,$(ASM_SRCS))
ASM_BONUS_OBJS = $(patsubst %.s,$(OBJDIR)/%.o,$(ASM_BONUS_SRCS))
MAIN_OBJ = $(OBJDIR)/main.o

RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
RESET = \033[0m

all: $(NAME)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: %.s | $(OBJDIR)
	@echo "$(YELLOW)Assembling $<...$(RESET)"
	@$(ASM) $(ASMFLAGS) $< -o $@

$(OBJDIR)/%.o: %.c $(HEADER) | $(OBJDIR)
	@echo "$(YELLOW)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) -I. -c $< -o $@

$(NAME): $(ASM_OBJS)
	@echo "$(BLUE)Creating library $(NAME)...$(RESET)"
	@ar rcs $(NAME) $(ASM_OBJS)
	@echo "$(GREEN)✓ $(NAME) created successfully$(RESET)"

bonus: $(ASM_OBJS) $(ASM_BONUS_OBJS)
	@echo "$(BLUE)Creating library $(NAME) with bonus...$(RESET)"
	@ar rcs $(NAME) $(ASM_OBJS) $(ASM_BONUS_OBJS)
	@echo "$(GREEN)✓ $(NAME) with bonus created successfully$(RESET)"

clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@rm -rf $(OBJDIR)

fclean: clean
	@echo "$(RED)Cleaning library and executable files...$(RESET)"
	@rm -f $(NAME)
	@rm -f $(TEST_NAME)

re: fclean all

.PHONY: all bonus clean fclean re