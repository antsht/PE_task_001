BUILD_PATH=../bin/
CC=gcc
CFLAGS=-g -Wall -Wextra -Werror
EXTRAFLAGS=-fsanitize=leak -fsanitize=address -fsanitize=undefined -fsanitize=unreachable -fno-sanitize-recover -fstack-protector 

all: check rebuild

build: clean roman_to_arabic

rebuild: clean_all roman_to_arabic universal_convert clean

roman_to_arabic: clean roman_to_arabic.c 
	$(CC) $(CFLAGS) roman_to_arabic.c -o  $(BUILD_PATH)roman_to_arabic  -lm
	$(CC) $(CFLAGS) $(EXTRAFLAGS)  roman_to_arabic.c  -o  $(BUILD_PATH)roman_to_arabic_extra  -lm

universal_convert: clean universal_convert.c 
	$(CC) $(CFLAGS) universal_convert.c -o  $(BUILD_PATH)universal_convert  -lm
	$(CC) $(CFLAGS) $(EXTRAFLAGS)  universal_convert.c  -o  $(BUILD_PATH)universal_convert_extra  -lm

clean_all:
	rm -rf *.o *.a *.so $(BUILD_PATH)*
	
clean:
	rm -rf *.o *.a

check:
	clang-format -n *.c
#	clang-format -n *.h
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h

run:
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes $(BUILD_PATH)roman_to_arabic
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes $(BUILD_PATH)universal_convert

run_no_valgrind:
	$(BUILD_PATH)roman_to_arabic_extra
	$(BUILD_PATH)universal_convert_extra



