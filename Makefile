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

main: compile run

compile:
	@mkdir -p ${DIST_FOLDER}  # creates if doesn't exist
	@${GCC} ${SRC_FOLDER}/*.c \
		-o ${DIST_FOLDER}/${BIN_OUTPUT_NAME} \
		-Wall -Wextra -Wundef -Wunreachable-code 

run: compile
	@./${DIST_FOLDER}/${BIN_OUTPUT_NAME}

clean:
	@if [ -d ./${DIST_FOLDER} ]; then\
       rm -rvf ${DIST_FOLDER};\
   	fi