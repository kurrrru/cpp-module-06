NAME = dynamic_cast

# source files
SRCS = main.cpp \
		funcs.cpp \
		Base.cpp \
		../toolbox/StepMark.cpp \
		../toolbox/color.cpp
OBJS = $(SRCS:.cpp=.o)

# compiler
CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -I..

# rules
all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
