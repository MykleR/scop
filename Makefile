NAME			:= scop

DIR_LIBS		:= lib
DIR_HEADERS		:= headers
DIR_SOURCES		:= sources
DIR_OBJECTS		:= .objs

TARGET			:= $(NAME)
SOURCES			:= $(wildcard $(DIR_SOURCES)/*.cpp)
OBJECTS			:= $(SOURCES:%.cpp=$(DIR_OBJECTS)/%.o)
DEPENDENCIES	:= $(OBJECTS:.o=.d)

CXX				:= -g++
CXXFLAGS 		:= -pedantic-errors -Wall -Wextra -Werror -std=c++20
LDFLAGS  		:= -lstdc++ -lm -lglfw -lvulkan -lpthread
IFLAGS			:= -I $(DIR_HEADERS)
DIR_DUP			= mkdir -p $(@D)

all: $(TARGET)

-include $(DEPENDENCIES)

$(TARGET): $(OBJECTS)
	@$(DIR_DUP)
	@$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)
	@printf " $(MSG_COMPILED)"

$(DIR_OBJECTS)/%.o: %.cpp
	@$(DIR_DUP)
	@$(CXX) $(CXXFLAGS) $(IFLAGS) -c $< -MMD -o $@
	@printf " $(MSG_COMPILING)"

clean:
	@rm -rf $(DIR_OBJECTS)
	@printf " $(MSG_CLEANING)"

fclean: clean
	@rm -rf $(TARGET)
	@printf " $(MSG_DELETED)"

re: fclean all

.PHONY: clean fclean re all


BLACK		=	\033[30m
RED			=	\033[31m
GREEN		=	\033[32m
YELLOW		=	\033[33m
BLUE		=	\033[34m
MAGENTA		=	\033[35m
CYAN		=	\033[36m
WHITE		=	\033[37m
GRAY		=	\033[90m
BOLD		=	\033[1m
ITALIC		=	\033[3m
RESET		=	\033[0m
LINE_CLR	=	\33[2K\r

MSG_COMPILED	= $(CYAN)$(BOLD)$(ITALIC)■$(RESET)  compiled	$(BOLD)$@$(RESET) $(CYAN)successfully$(RESET)\n
MSG_COMPILING	= $(BLUE)$(BOLD)$(ITALIC)■$(RESET)  compiling	$(GRAY)$(BOLD)$(ITALIC)$<$(RESET)\n
MSG_CLEANING	= $(GRAY)$(BOLD)$(ITALIC)■$(RESET)  cleaning	$(RED)$(BOLD)$(ITALIC)$(BUILD)$(RESET)\n
MSG_DELETED		= $(GRAY)$(BOLD)$(ITALIC)■$(RESET)  deleted 	$(GRAY)$(BOLD)$(ITALIC)$(NAME)$(RESET)\n
