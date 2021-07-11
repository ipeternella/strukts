# the first goal becomes the main goal -> run by default (.DEFAULT_GOAL)
# @ => supresses echoing the executed command!
# 
# target: prereq1 prereq2
# 	recipe

# variables
GCC := gcc

MAIN_FILE := main.c
BIN_OUTPUT_NAME := main

SRC_FOLDER := src
DIST_FOLDER := dist

TEST_FOLDER := tests
TEST_DIST_FOLDER := tmp
TEST_BIN_OUTPUT_NAME := tests

main: compile run

compile:
	@mkdir -p ${DIST_FOLDER}  # creates if doesn't exist
	@${GCC} ${SRC_FOLDER}/*.c \
		-o ${DIST_FOLDER}/${BIN_OUTPUT_NAME} \
		-Wall -Wextra -Wundef -Wunreachable-code

run: compile
	@./${DIST_FOLDER}/${BIN_OUTPUT_NAME}

test:
	@mkdir -p ${TEST_DIST_FOLDER}  # creates if doesn't exist
	@${GCC} ${TEST_FOLDER}/*.c \
		-o ${TEST_DIST_FOLDER}/${TEST_BIN_OUTPUT_NAME} \
		-Wall -Wextra -Wundef -Wunreachable-code 

	@./${TEST_DIST_FOLDER}/${TEST_BIN_OUTPUT_NAME} || rm -rf ${TEST_DIST_FOLDER}
	@rm -rf ${TEST_DIST_FOLDER}

clean:
	@if [ -d ./${DIST_FOLDER} ]; then\
       rm -rvf ${DIST_FOLDER};\
   	fi

	@if [ -d ./${TEST_DIST_FOLDER} ]; then\
       rm -rvf ${TEST_DIST_FOLDER};\
   	fi