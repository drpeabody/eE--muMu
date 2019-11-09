#!/bin/bash

## Change this paramter to point to your pythia installation

PYTHIA="/home/abhishek/hep/pythia8240/"

## Do not change anything below this

OUTPUT_DIR="$(pwd)/out"
BUILD_DIR="${PYTHIA}examples/"

if [ ! -f ./main-1.cc ]; then
    echo "Main PYTHIA code not found! Aborting."
else
    echo "Building PYTHIA code..."

    if [ ! -d $BUILD_DIR ]; then
        echo "PYTHIA installation not found! Aborting."
    else
        mkdir -p $OUTPUT_DIR
        cp main-1.cc "${BUILD_DIR}main-1.cc"
        cd $BUILD_DIR
        make main-1 || exit 1
        echo "Build complete, running code"
        for (( i=5; i<=14000; i+=1 ))
        do 
            # ./main-1 $i $OUTPUT_DIR/pythia-E-$i > $OUTPUT_DIR/output
            ./main-1 $i $OUTPUT_DIR/pythia-E-$i > /dev/null
        done

        # Testing
        
        # ./main-1 500 $OUTPUT_DIR/pythia-E-500 > $OUTPUT_DIR/output
        # ./main-1 1000 $OUTPUT_DIR/pythia-E-1000 > /dev/null
        # ./main-1 13000 $OUTPUT_DIR/pythia-E-13000 > /dev/null

        echo "Done, output saved as ${OUTPUT_DIR}/"
    fi
fi
