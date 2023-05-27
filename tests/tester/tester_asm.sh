#!/usr/bin/bash

cd "$(dirname "$0")"
COMPILATION=$(make -sC ../../asm/ re)
TOTAL_TEST=0
TOTAL_OK=0

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
    ((TOTAL_TEST++))
    FILENAME=$(basename ${file%.*})

    ../../asm/asm $file
    if [ $? -ne 0 ]
    then
        printf "[\033[0;34mTest\033[0m][\033[0;31mKO\033[0m] $file\n"
        continue
    fi
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
        ((TOTAL_OK++))
    fi

    rm -f ${FILENAME}.hex ${FILENAME}.hex.ref ${FILENAME}.cor
done

function handle_error() {
        ../../asm/asm $1
        if [ $? -eq 84 ]
        then
            printf "[\033[0;34mTest\033[0m][\033[0;32mOK\033[0m] $1\n"
            ((TOTAL_OK++))
        else
            printf "[\033[0;34mTest\033[0m][\033[0;31mKO\033[0m] $1\n"
        fi

        rm -f $1.cor
}

for file in ./errors/*
do
    ((TOTAL_TEST++))
    handle_error $file
done

handle_error ./errors/
handle_error undefined

for file in ../champions/src_unrefered/*.s
do
    ((TOTAL_TEST++))
    FILENAME=$(basename ${file%.*})

    ../bin/asm $file
    if [ $? -ne 0 ]
    then
        printf "[\033[0;34mTest\033[0m][\033[0;31mINVALID\033[0m] $file\n"
        rm -f $file
        continue
    fi
    mv ${FILENAME}.cor ${FILENAME}.cor.ref

    ../../asm/asm $file
    if [ $? -ne 0 ]
    then
        printf "[\033[0;34mTest\033[0m][\033[0;31mKO\033[0m] $file\n"
        rm -f ${FILENAME}.cor ${FILENAME}.cor.ref
        continue
    fi

    hexdump -C ${FILENAME}.cor > ${FILENAME}.hex
    hexdump -C ${FILENAME}.cor.ref > ${FILENAME}.hex.ref

    FILEDIFF=$(diff -y --color='always' ${FILENAME}.hex ${FILENAME}.hex.ref)
    if [ $? -ne 0 ]
    then
        printf "[\033[0;34mTest\033[0m][\033[0;31mKO\033[0m] $file\n"
        printf "[\033[0;31mDiff\033[0m] ${FILENAME}.hex | ${FILENAME}.hex.ref\n"
        printf "$FILEDIFF\n"

    else
        printf "[\033[0;34mTest\033[0m][\033[0;32mOK\033[0m] $file\n"
        ((TOTAL_OK++))
    fi

    rm -f ${FILENAME}.cor ${FILENAME}.cor.ref ${FILENAME}.hex ${FILENAME}.hex.ref
done

printf "[\033[0;33mTOTAL\033[0m] $TOTAL_OK/$TOTAL_TEST\n"
