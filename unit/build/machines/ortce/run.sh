#!/bin/bash

config="pvc"
unit="FFT"
iter=2
legacy_umd=0
debugger=0

if [[ $1 == '-h' || $1 == '--help' || $1 == '-help' ]]; then
    echo "Run as follows:"
    echo "./generate_cases.sh [options]"
    echo
    echo "    -c <pvc>"
    echo "        hardware configuration environment variables to source, indicated by {config}-env.sh (default: ${config})"
    echo
    echo "    -u"
    echo "        unit test to run (default: ${unit})"
    echo
    echo "    -i"
    echo "        iterations to run (default: ${unit})"
    echo
    echo "    -l"
    echo "        run with legacy UMD (default: off)"
    echo
    echo "    -d"
    echo "        run with onapi-gdb debugger (default: off)"
    echo
    exit 0
fi

# fetch input arguments, if any
while getopts "c:u:i:ld" flag
do
    case "${flag}" in
        c) config=${OPTARG};;
        u) unit=${OPTARG};;
        i) iter=${OPTARG};;
        l) legacy_umd=1;;
        d) debugger=1;;
    esac
done


SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

source ${SCRIPT_DIR}/${config}-env.sh

if [[ ${legacy_umd} = 1 && ${config} =~ "pvc" ]]
then
  module switch -f intel-comp-rt/ci-neo-master intel-comp-rt
fi

module list

rm -rf cl_cache
rm -rf l0_cache
mkdir -p cl_cache
mkdir -p l0_cache

if [[ ${debugger} = 1 ]]
then
  module load intel/debugger/GDB10_20230302_160920
  export ZET_ENABLE_PROGRAM_DEBUGGING=1
  export IGC_EnableGTLocationDebugging=1
  gdb-oneapi --args ./${unit}/${unit}
else
  for (( c=1; c<=${iter}; c++ ))
  do
    echo "Iteration ${c}"
    ./${unit}/${unit}
  done
fi
