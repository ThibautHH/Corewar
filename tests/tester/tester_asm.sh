#!/usr/bin/bash

cd "$(dirname "$0")"
COMPILATION=$(make -sC ../../asm/ re)

if [ $? -ne 0 ]
then
    printf "$COMPILATION\n"
    printf "[\033[0;33mCompilation\033[0m][\033[0;31mKO\033[0m]\n"
    exit 1
else
    printf "[\033[0;33mCompilation\033[0m][\033[0;32mOK\033[0m]\n"
fi

for file in ../champions/src/*.s
do
    ../../asm/asm $file
    if [ $? -ne 0 ]
    then
        printf "[\033[0;34mTest\033[0m][\033[0;31mKO\033[0m] $file\n"
        continue
    fi
    FILENAME=$(basename ${file%.*})
    hexdump -C ${FILENAME}.cor > ${FILENAME}.hex
    hexdump -C ../champions/${FILENAME}.cor > ${FILENAME}.hex.ref

    FILEDIFF=$(diff -y --color='always' ${FILENAME}.hex ${FILENAME}.hex.ref)
    if [ $? -ne 0 ]
    then
        printf "[\033[0;34mTest\033[0m][\033[0;31mKO\033[0m] $file\n"
        printf "[\033[0;31mDiff\033[0m] ${FILENAME}.hex | ${FILENAME}.hex.ref\n"
        printf "$FILEDIFF\n"

    else
          printf "[\033[0;34mTest\033[0m][\033[0;32mOK\033[0m] $file\n"
    fi

    rm ${FILENAME}.hex ${FILENAME}.hex.ref ${FILENAME}.cor
done

function handle_error() {
        ../../asm/asm $1
        if [ $? -eq 84 ]
        then
            printf "[\033[0;34mTest\033[0m][\033[0;32mOK\033[0m] $1\n"
        else
            printf "[\033[0;34mTest\033[0m][\033[0;31mKO\033[0m] $1\n"
        fi
}

for file in ./errors/*
do
    handle_error $file
done

handle_error ./errors/
handle_error undefined
