FTNAME= test_ft

STDNAME= test_std

SOURCE=	main.cpp \
		test/vector_test.cpp \
		test/stack_test.cpp \
		test/map_test.cpp \
		test/set_test.cpp

FTOSOURCE= $(SOURCE:.cpp=.o)

STDOSOURCE= $(addsuffix _std.o, $(basename $(SOURCE)))

all: $(FTNAME) $(STDNAME)

%.o: %.cpp
	clang++ -Wall -Werror -Wextra --std=c++98 -c $< -o $@

%_std.o: %.cpp
	clang++ -Wall -Werror -Wextra --std=c++98 -c $< -o $@ -D STD

$(FTNAME): $(FTOSOURCE)
	clang++ $(FTOSOURCE) -o $(FTNAME)

$(STDNAME): $(STDOSOURCE)
	clang++ $(STDOSOURCE) -o $(STDNAME)

clean:
	rm -rf $(FTOSOURCE) $(STDOSOURCE)

fclean: clean
	rm -rf $(FTNAME) $(STDNAME)

re: fclean all

.PHONY: clean fclean re all
