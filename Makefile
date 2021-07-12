ROOT_DIR := $(dir $(abspath $(firstword $(MAKEFILE_LIST))))
CC := gcc
CCP := g++

LIB := -Llib # directories for looking for compiled libs (passed to the linker)
INC := -Iinclude -Isrc # directories for looking for header files in preprocessing

CFLAGS := -Wall -Wextra -v
CCPFLAGS := -Wall -Wextra -std=c++11 -lgtest -lgtest_main

# src folders
SRC_FOLDER := src
TEST_FOLDER := tests

# dist/build folders
DIST_FOLDER := dist
TEST_DIST_FOLDER := tmp

# bin output names
BIN_OUTPUT_NAME := main
TEST_BIN_OUTPUT_NAME := tests

main: compile run

compile:
	@tput setaf 3; echo "🔨 Compiling code..."
	@mkdir -p $(DIST_FOLDER)

	@$(CC) $(CFLAGS) $(INC) $(LIB) $(SRC_FOLDER)/*.c -o $(DIST_FOLDER)/$(BIN_OUTPUT_NAME)
	@echo "🔨 Compilation successful...";

run: compile
	@echo "🔨 Running..."; tput init
	@./$(DIST_FOLDER)/$(BIN_OUTPUT_NAME)

test:
	@tput setaf 3; echo "🔨 Compiling tests..."
	@mkdir -p $(TEST_DIST_FOLDER)
	@$(CCP) $(INC) $(LIB) $(CCPFLAGS) $(TEST_FOLDER)/*.cc -o $(TEST_DIST_FOLDER)/$(TEST_BIN_OUTPUT_NAME)

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