FTNAME= test_ft

STDNAME= test_std

SOURCE=	main.cpp \
		test/vector_test.cpp \
		test/stack_test.cpp \
		test/map_test.cpp \
		test/set_test.cpp

FTOSOURCE= $(SOURCE:.cpp=.o)

STDOSOURCE= $(addsuffix s.o, $(basename $(SOURCE)))

all: $(FTNAME) $(STDNAME)

%.o: %.cpp
	clang++ -c $< -o $@

%s.o: %.cpp
	clang++ -c $(patsubst *s.cpp, *.cpp, $<) -o $@ -D STD

$(FTNAME): $(FTOSOURCE)
	clang++ $(FTOSOURCE) -o $(FTNAME)

$(STDNAME): $(STDOSOURCE)
	clang++ $(STDOSOURCE) -o $(STDNAME)

clean:
	rm -rf $(FTOSOURCE) $(STDOSOURCE)

fclean: clean
	rm -rf $(FTNAME) $(STDNAME)

re: fclean all

.PHONY: clean fclean re all bonus
