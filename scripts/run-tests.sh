#!/bin/bash
set -euo pipefail

assert_installed_program() {
    PROGRAM=$1

    if ! command -v "${PROGRAM}" &> /dev/null; then
        echo "${PROGRAM} program is required and was not found on PATH! Is it installed and on PATH?"
        exit 1
    fi
}

main() {
    BUILD_DIR=build
    COVERAGE_DIR=coverage

    assert_installed_program cmake
    assert_installed_program gcov
    assert_installed_program lcov
    assert_installed_program genhtml

    echo "[Strukts] => Ajusting build folders..."
    rm -rf ${BUILD_DIR} && mkdir ${BUILD_DIR} && cd ${BUILD_DIR}
    mkdir ${COVERAGE_DIR}

    echo "[Strukts] => CMaking project and running tests with coverage..."
    cmake -DWITH_TEST=ON .. && make test && ./bin/test

    echo "[Strukts] => Running lcov to gather .gcno files..."
    lcov --capture --directory src --output-file ${COVERAGE_DIR}/coverage.info

    echo "[Strukts] => Running gcov on .gcno files (can be useful)..."
    cd src/CMakeFiles/strukts.dir
    gcov *.gcno
    cd ../../../

    echo "[Strukts] => Running genhtml..."
    cd ${COVERAGE_DIR}
    genhtml coverage.info --output-directory .

    echo "[Strukts] => All Done!"
}

main