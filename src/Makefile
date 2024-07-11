CC = g++
FLAGS = -std=c++17 -Wall -Werror -Wextra 
CPPFLAGS = -lgtest
LEAKS = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose -q
GCOV_FLAGS = -L. --coverage -lgcov

OS :=$(shell uname -s)
ifeq ($(OS), Darwin)
CPPFLAGS = -lgtest -lpthread
GCOV_FLAGS =-fprofile-arcs -ftest-coverage
LEAKS =leaks -atExit --
else
CFLAGS_TEST =-pthread -lcheck -lrt -lm -lsubunit
GCOV_FLAGS =-L. -lsubunit --coverage
LEAKS =valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose -q	
	ifeq ($(NAME_LINUX), "Alpine Linux")
		CFLAGS_TEST =-pthread -lcheck -lrt -lm
		GCOV_FLAGS =-L. --coverage
	endif

endif

all: clean test

test:
	${CC} ${FLAGS} tests/*.cc ${CPPFLAGS} -lgtest_main -o all_tests
	./all_tests

gcov_report:
	rm -rf *.g*
	${CC} tests/*.cc -lgtest -lgtest_main -lgmock ${GCOV_FLAGS} ${FLAGS} ${CPPFLAGS}
	./a.out
	lcov -t "t" -o test.info -c -d . --ignore-errors mismatch,mismatch
	genhtml -o report test.info
	open ./report/index.html

style:
	clang-format --style=Google -n s21_containers/*.h s21_containers/*.tpp s21_containersplus/*.h tests/*.cc tests/*.h

leaks: test
	$(LEAKS) ./all_tests

clean:
	rm -rf *.o
	rm -rf *.a
	rm -rf *.out
	rm -rf *.dSYM
	rm -rf test_me all_tests
	rm -rf *.gcda *.gcno *.info report
	rm -rf main all_tests
