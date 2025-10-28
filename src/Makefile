CC=gcc
FLAGS = -Werror -Wall -Wextra -std=c11

OS = $(shell uname)

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	FLAGS_LCHECK = -lcheck -pthread -lrt -lm -lsubunit
	OPEN_CMD = xdg-open
else
endif
ifeq ($(UNAME_S),Darwin)
	FLAGS_LCHECK = -lcheck
	OPEN_CMD = open
endif

SOURCES = $(filter-out tests.c, $(wildcard *.c))
TEST_SOURCES = tests.c

all: matrix.a

test: matrix.a
	rm -rf matrix_test
	$(CC) $(FLAGS) *.c $(FLAGS_LCHECK) matrix.a -L . -o matrix_test
	./matrix_test


gcov_report: matrix.a
	rm -f *.g*
	$(CC) $(FLAGS) *.c $(FLAGS_LCHECK) -L. --coverage -o matrix_test_with_gcov
	./matrix_test_with_gcov
	lcov -t "test" -o rep.info -c -d .
	genhtml -o report rep.info
	$(OPEN_CMD) ./report/index.html
	rm -rf *.gcda *.gcno *.o


matrix.a: objects
	ar rcs matrix.a *.o
	ranlib matrix.a

clean:
	@rm -rf *.o *.a
	@rm -rf matrix_test
	@rm -rf *.gcda *.gcno *.gch matrix_test_with_gcov *.css
	@rm -rf *.info *.html
	@rm -rf ./report
	@rm -rf *.gcov

re:
	make clean
	make all

clang:
	@cp ../materials/linters/.clang-format .
	clang-format -n *.c *.h
	@rm -rf .clang-format

objects:
	$(CC) $(FLAGS) $(SOURCES) -c $<
