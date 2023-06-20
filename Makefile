#------------------------------------------------#
#        COMMON VARIABLES, FLAGS, TARGETS        #
#------------------------------------------------#

EXEC := s21_test

TESTS_SOURCE := $(wildcard tests*.cc)
HEADER := $(wildcard s21_*.h)
 

CC := g++ 
STANDART := -std=c++17
CFLAGS := -Wall -Wextra $(STANDART)
VFLAG := -s --quiet --leak-check=full --leak-resolution=med --track-origins=yes --verbose --log-file=RESULT_VALGRIND.txt
CPPCHECKFLAG := --enable=all --language=c++ -$(STANDART) --suppress=missingIncludeSystem 
TFLAGS := -lgtest

OS := $(shell uname)
ifeq ($(OS), Linux)
LEAKS := valgrind $(VFLAG) ./$(EXEC)
TFLAGS += -lpthread -lgtest_main -L/usr/lib
else
LEAKS := leaks --atExit -- ./$(EXEC) 
endif

all: clean test

test: clean ${TESTS_SOURCE} 
	${CC} $(CFLAGS) ${TESTS_SOURCE} $(TFLAGS) -o $(EXEC) 
	./$(EXEC) 

#------------------------------------------------#
#             STYLE AND LEAKS CHECK              #
#------------------------------------------------#

check: linter cppcheck leaks 

linter:
	cp ../materials/linters/.clang-format .
	clang-format -n --verbose $(TEST_SOURCE) $(HEADER) 
	@-rm -rf .clang-format

cppcheck:
	cppcheck $(CPPCHECKFLAG) $(TEST_SOURCE) $(HEADER) 

leaks:
	$(LEAKS)
	
gcov_report: clean 
	$(CC) $(STANDART) --coverage ${TESTS_SOURCE} $(TFLAGS) -o $(EXEC) 
	./$(EXEC) 
	lcov -t "$(EXEC)" -o $(EXEC).info -c --no-external -d .
	genhtml -o report $(EXEC).info
ifeq ($(OS), Darwin)
	open ./report/index-sort-f.html
else
	xdg-open ./report/index-sort-f.html
endif

#------------------------------------------------#
#            CLEANING UP UNUSED FILES            #
#------------------------------------------------#

clean:
	@echo "Cleanup started..."
	@-rm -rf *.o && rm -rf *.gcda && rm -rf *.gcno RESULT_VALGRIND.txt
	@-rm -rf *.info && rm -rf *.gcov
	@-rm -rf ./$(EXEC) && rm -rf ./gcov_report
	@-rm -rf ./report/
	@echo "Done."