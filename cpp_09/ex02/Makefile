# definitions
INC_DIR			=		inc
SRC_DIR			=		src
OBJ_DIR			=		obj
BIN_DIR			=		bin
NAME			=		PmergeMe
CXX				=		c++
CXXFLAGS		=		-Wall -Wextra -Werror -std=c++98 -I$(INC_DIR)

# debug flag
ifdef DEBUG
CXXFLAGS += -DDEBUG
endif


# sources and objects
SRCS			=		main.cpp	\
						PmergeMe.cpp

OBJS			=		$(SRCS:%.cpp=$(OBJ_DIR)/%.o)

# compilation rule
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
						mkdir -p $(OBJ_DIR)
						$(CXX) $(CXXFLAGS) -c $< -o $@

# default target
all: $(BIN_DIR)/$(NAME)

# must fclean before `make debug` if not debug
.PHONY: debug
debug:
						$(MAKE) fclean
						$(MAKE) DEBUG=1 all


# linking binary
$(BIN_DIR)/$(NAME): $(OBJS)
						mkdir -p $(BIN_DIR)
						$(CXX) $(CXXFLAGS) $(OBJS) -o $@
						ln -sf $@ ./$(NAME)

# create symlink in sources/ to access binary
link:					$(BIN_DIR)/$(NAME)
#						ln -sf $(BIN_DIR)/$(NAME) ./$(NAME)

# cleaning
#removes content of /bin and /obj directories
clean:
						rm -rf $(OBJ_DIR)/*
						rm -rf $(BIN_DIR)/*
						
#removes content and directories /bin and /obj
fclean: clean
						rm -rf $(OBJ_DIR)
						rm -rf $(BIN_DIR)
						rm -rf $(NAME)

re: fclean all

# phony targets
.PHONY: all clean fclean re link
