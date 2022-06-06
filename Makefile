NAME        :=  ft_containers

CXX         :=  ~/goinfre/clang14/bin/clang++
CXXFLAGS    :=  -std=c++98 -Wall -Wextra -Werror -g3 -pedantic -fsanitize=undefined -fsanitize=address

CLASS       :=
INTERFACE   :=
TEMPLATE    :=  pair red_black_tree

SRCS        :=  map_test.cpp $(addsuffix .cpp, $(CLASS))
OBJS        :=  $(SRCS:.cpp=.o)

INCLUDES    :=  $(addsuffix .hpp, $(CLASS)) $(addsuffix .hpp, $(INTERFACE)) \
                $(addsuffix .hpp, $(TEMPELATE))

RM          :=  rm -f

ifeq ($(DEBUG), 1)
  CXXFLAGS  :=  -std=c++98 -g
endif

.PHONY      :    all
all         :    $(NAME)

$(NAME)     :    $(OBJS) $(INCLUDES)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@

%.o         :    %.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@

.PHONY      :    clean
clean       :
	$(RM) $(OBJS)

.PHONY      :    fclean
fclean      :    clean
	$(RM) $(NAME)

.PHONY      :    re
re          :
	make fclean
	make all
