FT= test_ft

STD= test_std

SOURCE=	main.cpp \
		test/vector_test.cpp \
		test/stack_test.cpp \
		test/map_test.cpp \
		test/set_test.cpp

OSOURCE= $(SOURCE:.cpp=.o)

all: $(FT) $(STD)

%.o: %.cpp
	gcc -Wall -Werror -Wextra -c $< -o $@

$(FT): $(OSOURCE)
	gcc $(OSOURCE) -o $(FT)

$(STD): $(OSOURCE)
	gcc $(OSOURCE) -o $(STD) -D STD

clean:
	rm -rf $(OSOURCE)

fclean: clean
	rm -rf $(STD) $(STD)

re: fclean all

.PHONY: clean fclean re all bonus
