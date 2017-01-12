#/bin/bash

rootDir=`pwd`
testsDir=tests
cpuDir="${testsDir}/CPU"

printUsage() {
    echo "Usage: run_tests.sh <project>"
    echo "To get a list of available projects check the content of this file (run_tests.sh)"
}

if test $# -ne 1
then
    printUsage
fi

while test $# -eq 1
do
    case "$1" in
        cpu)
            make test-cpu

            cd "${cpuDir}"
            for t in `ls tests_*.asm`
            do
                testname=$(basename $t .asm)
                echo Test: $testname
                dasm $testname.asm -o$testname.out
            done

            cd "${rootDir}"
            build/testcpu

            cd "${cpuDir}"
            rm *.out
            ;;
        *)
            printUsage
            ;;
    esac
    shift
done
