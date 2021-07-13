ROOT_DIR := $(dir $(abspath $(firstword $(MAKEFILE_LIST))))
CC := gcc
CCP := g++

LIB := -Llib # directories for looking for compiled libs (passed to the linker)
INC := -Iinclude/internal/vendor -Iinclude # directories for looking for header files in preprocessing

CFLAGS := -g -Wall -Wextra -c -fpic  # pic mode without linking for shared lib
CCPFLAGS := -Wall -Wextra -std=c++11 -lgtest -lgtest_main  # 3rd party libs specification with -l for the linker

# src folders
SRC_FOLDER := src
TEST_FOLDER := tests

# dist/build folders for compiled code
DIST_FOLDER := build
TEST_DIST_FOLDER := tmp

# bin output names
BIN_OUTPUT_NAME := libstrukts
TEST_BIN_OUTPUT_NAME := teststrukts

main: compile

compile:
    @mkdir -p $(DIST_FOLDER)

    @tput setaf 3; echo "🔨 Compiling shared lib in pic mode..."
    @$(CC) $(CFLAGS) $(INC) $(SRC_FOLDER)/*.c # compiles without linking
    @mv *.o $(DIST_FOLDER)

    @echo "🔨 Producing final shared object..."
    @$(CC) -shared -o $(DIST_FOLDER)/libstrukts.so $(DIST_FOLDER)/*.o

    @rm -f $(DIST_FOLDER)/*.o
    @echo "🔨 Compilation successful!";

test:
    @tput setaf 3; echo "🔨 Compiling tests..."
    @mkdir -p $(TEST_DIST_FOLDER)

    @$(CCP) $(INC) $(LIB) $(CCPFLAGS) $(TEST_FOLDER)/*.cc $(SRC_FOLDER)/*.c \
        -o $(TEST_DIST_FOLDER)/$(TEST_BIN_OUTPUT_NAME)

    @echo "🔨 Running tests..."
    @./$(TEST_DIST_FOLDER)/$(TEST_BIN_OUTPUT_NAME) || rm -rf $(TEST_DIST_FOLDER)
    @rm -rf $(TEST_DIST_FOLDER)

clean:
    @tput setaf 3; echo "🔨 Cleaning dist folder..."
    @if [ -d ./$(DIST_FOLDER) ]; then\
        rm -rvf $(DIST_FOLDER);\
    fi
    
    @echo "🔨 Cleaning test folder..."
    @if [ -d ./$(TEST_DIST_FOLDER) ]; then\
        rm -rvf $(TEST_DIST_FOLDER);\
    fi