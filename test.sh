#!/usr/bin/bash

BinName="./Result.out"

#example: ./test.sh ./tests/lab1/ClosestZero/ ./inputs/lab1/ClosestZero

if [[ $1 == "" ]]; then
    echo "Please give a directory"
    exit 1
fi
if [[ $2 == "" ]]; then
    echo "Please give an input file"
    exit 1
fi

InpFile=$2

# Pass the name of the file as the param, result as second and app input file as third
RunTest() {
    echo "Running the test \"${1}\""
    cat $1 > $InpFile
    result="${BinName}"
    if [[ $($BinName | sed -e 's/[[:space:]]*$//') == $(cat $2 | sed -e 's/[[:space:]]*$//') ]]; then
        echo Test passed
    else 
        echo "Test failed."
        echo "Result/expected"
        $BinName
        echo --------------------
        cat $2
    fi
    echo ====================
}


for test in $(ls $1 | grep .in)
do
    OutFile=$(echo $test | sed -e 's/in/res/g')
    RunTest "${1}${test}" "${1}${OutFile}"  
done
