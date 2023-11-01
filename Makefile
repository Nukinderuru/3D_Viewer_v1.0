CC = gcc
СFLAGS = -std=c11 -Wall -Werror -Wextra
TFLAGS = -lcheck -lpthread -pthread -lm
CGFLAGS = -fprofile-arcs -ftest-coverage --coverage -O0
TARGET = 3D_Viewer
MEMORY_CHECKER = leaks -atExit --

ifeq ($(shell uname -s),Linux)
	TFLAGS += -lsubunit -lrt
	MEMORY_CHECKER = valgrind -s --leak-check=full
endif

all: test

build:
	mkdir build
	cd build && qmake ../$(TARGET)/$(TARGET).pro && make

install: build
	@test -d ~/$(TARGET) || mkdir -p ~/$(TARGET)
	cp ./build/$(TARGET) ~/$(TARGET)

uninstall:
	rm -rf ~/$(TARGET)

dvi: $(TARGET).pdf
	open $(TARGET).pdf

$(TARGET).pdf: info/$(TARGET).tex
	texi2pdf -q -c info/$(TARGET).tex -o $(TARGET).pdf

dist:
	tar -czf $(TARGET).tar.gz $(TARGET)

test:
	$(CC) $(СFLAGS) $(TARGET)/*.c tests/*.c -o tests/test.out $(TFLAGS)
	./tests/test.out

gcov_report:
	$(CC) $(СFLAGS) -c $(CGFLAGS) $(TARGET)/*.c
	$(CC) $(СFLAGS) tests/*.c *.o -o tests/test.out $(TFLAGS) $(CGFLAGS)
	./tests/test.out
	rm -rf tests/*.gcno tests/*.gcda
	lcov -q -o report/report.info -c -d .
	genhtml -o report report/report.info
	rm -rf *.gcno *.gcda *.o
	open report/index.html

style_fix:
	clang-format -style=Google -i $(TARGET)/*.c $(TARGET)/*.h $(TARGET)/*.cpp
	clang-format -style=Google -i tests/*.c tests/*.h

style_check:
	clang-format -style=Google -n $(TARGET)/*.c $(TARGET)/*.h $(TARGET)/*.cpp
	clang-format -style=Google -n tests/*.c tests/*.h

memory_leaks_check: test
	CK_FORK=no $(MEMORY_CHECKER) tests/test.out

clean:
	rm -rf build/
	rm -rf report/*
	rm -rf *.pdf
	rm -rf *.gz
	rm -rf tests/test.out
	rm -rf tests/*.gcda tests/*.gcno
