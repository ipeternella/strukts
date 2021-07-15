ROOT_DIR := $(dir $(abspath $(firstword $(MAKEFILE_LIST))))
CC := gcc
CPP := g++

LIB := -Llib # directories for looking for compiled libs (passed to the linker)
INC := -Iinclude/internal/vendor -Iinclude # directories for looking for header files in preprocessing

CFLAGS := -g -Wall -Wextra -c -fpic  # pic mode without linking for shared lib
CPPFLAGS := -Wall -Wextra -std=c++11 -lgtest -lgtest_main -Wno-deprecated # 3rd party libs specification with -l for the linker

# src folders
SRC_FOLDER := src
TEST_FOLDER := tests

# dist/build folders for compiled code
DIST_FOLDER := build
TEST_DIST_FOLDER := tmp

# bin output names
BIN_OUTPUT_NAME := libstrukts.a  # .a for static libraries
TEST_BIN_OUTPUT_NAME := teststrukts

# no echo'ing commands
.SILENT: compile test clean

main: compile

compile:
	mkdir -p $(DIST_FOLDER)

	tput setaf 3; echo "🔨 Compiling lib in pic mode..."
	$(CC) $(CFLAGS) $(INC) $(SRC_FOLDER)/*.c # compiles without linking
	mv *.o $(DIST_FOLDER)

	echo "🪚  Producing final static library with archive..."
	ar -rc $(DIST_FOLDER)/$(BIN_OUTPUT_NAME) $(DIST_FOLDER)/*.o
	rm -f $(DIST_FOLDER)/*.o

	echo "📦 Static library has been successfully packed!"

test:
	tput setaf 3; echo "🔨 Compiling tests..."
	mkdir -p $(TEST_DIST_FOLDER)

	$(CPP) $(INC) $(LIB) $(CPPFLAGS) $(TEST_FOLDER)/*.cpp $(SRC_FOLDER)/*.c \
		-o $(TEST_DIST_FOLDER)/$(TEST_BIN_OUTPUT_NAME)

	echo "🔨 Running tests..."
	./$(TEST_DIST_FOLDER)/$(TEST_BIN_OUTPUT_NAME) || rm -rf $(TEST_DIST_FOLDER)
	rm -rf $(TEST_DIST_FOLDER)

clean:
	tput setaf 3; echo "🧹 Cleaning dist folder..."
	if [ -d ./$(DIST_FOLDER) ]; then\
		rm -rvf $(DIST_FOLDER);\
	fi
    
	echo "🧼 Cleaning test folder..."
	if [ -d ./$(TEST_DIST_FOLDER) ]; then\
		rm -rvf $(TEST_DIST_FOLDER);\
	fi