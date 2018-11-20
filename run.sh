#!/bin/sh
if test $# -eq 2
then
    hw=$1
    p=$2
    file=HW${hw}/HW${hw}P${p}
    g++ ${file}.cpp -o $file
    if test $? -eq 0
    then
        ./$file < HW${hw}_input/HW${hw}P${p}.txt
    fi
elif test $# -eq 1
then
    hw=$1
    for file in $(find ./HW${hw} -name "HW${hw}P?.cpp")
    do
        g++ ${file} -o ${file%.cpp}
        if test $? -eq 0
        then
            name=${file##*/}
            name=${name%.cpp}
            echo $name
            ${file%.cpp} < ${file%/*}_input/${name}.txt
            echo
        fi
    done
else
    echo Usage:./run.sh homework problem
    echo ./run.sh homework
fi